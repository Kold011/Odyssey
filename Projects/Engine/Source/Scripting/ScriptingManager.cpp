#include "ScriptingManager.h"
#include <Logger.h>
#include "Events.h"
#include "Globals.h"
#include "ScriptCompiler.h"
#include "ScriptBindings.h"

namespace Odyssey
{
	void ExceptionCallback(std::string_view exception)
	{
		Logger::LogError(exception.data());
	}

	void ScriptingManager::Initialize()
	{
		// Initialize Coral
		std::filesystem::path appPath = Globals::GetApplicationPath();
		std::string coralDir = appPath.string();
		hostSettings =
		{
			.CoralDirectory = coralDir,
			.ExceptionCallback = ExceptionCallback
		};
		hostInstance.Initialize(hostSettings);

		LoadFrameworkAssembly();

		ScriptBindings::Initialize(s_FrameworkAssembly);
	}

	void ScriptingManager::LoadFrameworkAssembly()
	{
		s_FrameworkLoadContext = hostInstance.CreateAssemblyLoadContext("Odyssey.FrameworkContext");

		Path frameworkPath = std::filesystem::current_path() / "Resources/scripts/Odyssey.Framework.dll";
		s_FrameworkAssembly = s_FrameworkLoadContext.LoadAssembly(frameworkPath.string());
	}

	void ScriptingManager::LoadUserAssemblies()
	{
		if (!s_UserAssembliesLoaded)
		{
			// Load the assembly
			s_AppLoadContext = hostInstance.CreateAssemblyLoadContext("Odyssey.AppContext");
			appAssembly = s_AppLoadContext.LoadAssembly(s_UserAssemblyPath.string());
			s_UserAssembliesLoaded = true;
		}
	}

	void ScriptingManager::UnloadUserAssemblies()
	{
		if (s_UserAssembliesLoaded)
		{
			for (Coral::ManagedObject& object : managedObjects)
			{
				object.Destroy();
			}
			managedObjects.clear();

			hostInstance.UnloadAssemblyLoadContext(s_AppLoadContext);
			s_UserAssembliesLoaded = false;
		}
	}

	void ScriptingManager::ReloadUserAssemblies()
	{
		UnloadUserAssemblies();
		LoadUserAssemblies();
		EventSystem::Dispatch<OnAssembliesReloaded>();
	}

	Coral::ManagedObject ScriptingManager::CreateManagedObject(std::string_view fqManagedClassName, uint64_t entityGUID)
	{
		Coral::Type& managedType = appAssembly.GetType(fqManagedClassName);
		Coral::ManagedObject managedObject = managedType.CreateInstance((uint64_t)entityGUID);

		managedObjects.push_back(managedObject);
		return managedObject;
	}
}