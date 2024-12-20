#pragma once
#include "Ref.h"
#include "Asset.h"
#include "AssetSerializer.h"
#include "FileManager.h"

namespace Odyssey
{
	struct AssetEntry
	{
	public:
		std::string Name;
		std::string Type;
		Path Path;
		GUID Guid;
	};

	class AssetRegistry
	{
	public:
		AssetRegistry() = default;
		AssetRegistry(const Path& registryPath);
		~AssetRegistry();

	public:
		void AddAsset(const std::string& name, const std::string& type, const Path& path, GUID guid);
		void UpdateAssetName(GUID guid, const std::string& name);
		void UpdateAssetPath(GUID guid, const Path& path);
		void UpdateAssetPath(const Path& oldPath, const Path& newPath);

	public:
		void Save();
		void SaveTo(const Path& path);
		void Load();

	private:
		void PruneEntries();
		void OnFileAction(const Path& oldFilename, const Path& newFilename, FileActionType fileAction);

	public:
		Path RootDirectory;
		Path RegistryPath;
		std::vector<AssetEntry> Entries;
		TrackingID m_TrackingID;
	};
}