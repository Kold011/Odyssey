#include "ContentBrowserWindow.h"
#include "imgui.h"
#include "Input.h"
#include "SceneManager.h"
#include "AssetManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Project.h"
#include "EventSystem.h"
#include "EditorEvents.h"
#include "GUIManager.h"
#include "Renderer.h"
#include "Preferences.h"
#include "ThumbnailManager.h"

namespace Odyssey
{
	ContentBrowserWindow::ContentBrowserWindow(size_t windowID)
		: DockableWindow("Content Browser", windowID,
			glm::vec2(0, 0), glm::vec2(500, 500), glm::vec2(2, 2))
	{
		m_AssetsPath = windowID % 2 == 0 ? Project::GetActiveAssetsDirectory() : "Resources";
		m_CurrentPath = m_AssetsPath;

		FolderTracker::Options options;
		options.Extensions = { ".asset", ".glsl", ".meta" };
		options.Recursive = true;
		options.IncludeDirectoryChanges = true;
		options.Callback = [this](const Path& oldPath, const Path& newPath, FileActionType fileAction)
			{ OnFileAction(oldPath, newPath, fileAction); };
		m_FileTrackingID = FileManager::Get().TrackFolder(m_AssetsPath, options);

		UpdatePaths();
	}

	void ContentBrowserWindow::Destroy()
	{
		m_FoldersToDisplay.clear();
		m_FilesToDisplay.clear();
		FileManager::Get().UntrackFolder(m_FileTrackingID);
	}

	bool ContentBrowserWindow::Draw()
	{
		bool modified = false;

		if (!Begin())
			return modified;

		if (m_CurrentPath != m_AssetsPath)
		{
			if (ImGui::Button("<-"))
			{
				m_CurrentPath = m_CurrentPath.parent_path();
				UpdatePaths();
			}
		}

		// Draw folders first
		for (size_t i = 0; i < m_FolderDrawers.size(); i++)
		{
			SelectableInput& drawer = m_FolderDrawers[i];
			if (drawer.Draw() == SelectableInput::Result::DoubleClick)
			{
				m_CurrentPath = m_FoldersToDisplay[i];
				m_UpdatePaths = true;
			}
		}

		// Now files
		for (size_t i = 0; i < m_AssetDrawers.size(); i++)
		{
			SelectableInput& drawer = m_AssetDrawers[i];
			Path& path = m_FilesToDisplay[i];

			bool isScene = path.extension() == ".scene";
			bool isSourceAsset = AssetManager::IsSourceAsset(path);

			SelectableInput::Result drawStatus = drawer.Draw();

			switch (drawStatus)
			{
				case Odyssey::SelectableInput::Result::Selected:
				{
					// Dispatch a GUI selection event to update the rest of the UI
					GUISelection selection;
					selection.GUID = AssetManager::PathToGUID(path);
					selection.Type = AssetManager::GUIDToAssetType(selection.GUID);
					selection.FilePath = path;
					EventSystem::Dispatch<GUISelectionChangedEvent>(selection);

					if (!isSourceAsset && !isScene)
					{
						// Allow for this asset to be a potential drag/drop payload
						if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
						{
							GUID guid = AssetManager::PathToGUID(path);
							ImGui::SetDragDropPayload("Asset", &guid, sizeof(GUID));
							ImGui::EndDragDropSource();
						}
					}

					break;
				}
				case Odyssey::SelectableInput::Result::DoubleClick:
				{
					if (isScene)
						SceneManager::LoadScene(path);

					break;
				}
				case Odyssey::SelectableInput::Result::TextModified:
				{
					// Generate a new path for the asset
					std::string newFileName(drawer.GetText());
					Path newPath = path.parent_path() / (newFileName + path.extension().string());

					// Rename the file
					std::filesystem::rename(path, newPath);

					// Mark our current path as dirty so we update
					m_UpdatePaths = true;
					break;
				}
			}
		}

		if (m_CursorInContentRegion)
			HandleContextMenu();

		if (m_UpdatePaths)
			UpdatePaths();

		End();
		return modified;
	}

	void ContentBrowserWindow::OnWindowClose()
	{
		GUIManager::DestroyDockableWindow(this);
	}

	void ContentBrowserWindow::UpdatePaths()
	{
		m_UpdatePaths = false;
		m_FilesToDisplay.clear();
		m_FoldersToDisplay.clear();

		m_FolderDrawers.clear();
		m_AssetDrawers.clear();

		for (auto& iter : std::filesystem::directory_iterator(m_CurrentPath))
		{
			if (iter.is_directory())
			{
				m_FoldersToDisplay.push_back(iter.path());
				m_FolderDrawers.push_back(SelectableInput(iter.path().filename().string(), ThumbnailManager::LoadThumbnail(Preferences::GetFolderIcon())));
			}
			else if (iter.is_regular_file())
			{
				const std::string& extension = iter.path().extension().string();
				const std::vector<std::string>& assetExtensions = Preferences::GetAssetExtensions();
				const std::vector<std::string>& sourceExtensions = Preferences::GetSourceExtensions();

				// || Contains(sourceExtensions, extension.string()
				if (extension == ".scene" || extension == ".cs" || Contains(assetExtensions, extension) || Contains(sourceExtensions, extension))
				{
					Path path = iter.path();
					Path extension = path.extension();

					m_FilesToDisplay.push_back(path);

					uint64_t icon = 0;
					float aspectRatio = 1.0f;

					if (extension == ".cs")
					{
						icon = ThumbnailManager::LoadThumbnail(Preferences::GetScriptIcon());
						Ref<Texture2D> texture = ThumbnailManager::GetTexture(icon);
						aspectRatio = (float)texture->GetWidth() / (float)texture->GetHeight();
					}
					else if (extension == ".tex2D")
					{
						icon = ThumbnailManager::LoadThumbnail(path);
						Ref<Texture2D> texture = ThumbnailManager::GetTexture(icon);
						aspectRatio = (float)texture->GetWidth() / (float)texture->GetHeight();
					}
					else if (extension == ".mat")
					{
						icon = ThumbnailManager::LoadThumbnail(Preferences::GetMaterialIcon());
						Ref<Texture2D> texture = ThumbnailManager::GetTexture(icon);
						aspectRatio = (float)texture->GetWidth() / (float)texture->GetHeight();
					}
					else
					{
						icon = ThumbnailManager::LoadThumbnail(Preferences::GetAssetIcon());
						Ref<Texture2D> texture = ThumbnailManager::GetTexture(icon);
						aspectRatio = (float)texture->GetWidth() / (float)texture->GetHeight();
					}

					m_AssetDrawers.push_back(SelectableInput(path.filename().replace_extension("").string(), icon, aspectRatio));
				}
			}
		}
	}

	void ContentBrowserWindow::HandleContextMenu()
	{
		if (!m_ContextMenuOpen && Input::GetMouseButtonDown(MouseButton::Right) && !ImGui::IsAnyItemHovered())
			ImGui::OpenPopup("Context Menu: Content Browser", ImGuiPopupFlags_NoOpenOverExistingPopup);

		// TODO: Check its inside content area
		if (m_ContextMenuOpen = ImGui::BeginPopup("Context Menu: Content Browser"))
		{
			if (ImGui::BeginMenu("Create"))
			{
				if (ImGui::MenuItem("Material"))
				{
					const Path& path = GetUniquePath("Material", ".mat");
					AssetManager::CreateAsset<Material>(path);
					m_UpdatePaths = true;
				}
				if (ImGui::MenuItem("Scene"))
				{

				}
				if (ImGui::MenuItem("Shader"))
				{
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Import"))
			{
				ImGui::EndMenu();
			}
			ImGui::EndPopup();
		}
	}

	void ContentBrowserWindow::OnFileAction(const Path& oldPath, const Path& newPath, FileActionType fileAction)
	{
		UpdatePaths();
	}

	Path ContentBrowserWindow::GetUniquePath(const Path& filename, const Path& extension)
	{
		Path path = m_CurrentPath / Path(filename.string() + extension.string());

		uint32_t fileCount = 0;

		while (std::filesystem::exists(path))
			path = m_CurrentPath / Path(filename.string() + std::to_string(++fileCount) + extension.string());

		return path;
	}
}