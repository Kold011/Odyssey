#pragma once
#include <EventSystem.h>
#include <FileWatcherHandle.h>
#include <Scene.h>

namespace Odyssey::Editor
{
	struct OnUserFilesModified : public Framework::Event
	{
	public:
		OnUserFilesModified(const Framework::NotificationSet& notificationSet)
		{
			changedFileSet = notificationSet;
		}

		Framework::NotificationSet changedFileSet;
	};

	struct OnBuildStart : public Framework::Event
	{

	};

	struct OnBuildFinished : public Framework::Event
	{
	public:
		OnBuildFinished(bool succeeded)
		{
			success = succeeded;
		}

		bool success = false;
	};

	struct OnSceneLoaded : public Framework::Event
	{
	public:
		OnSceneLoaded(Entities::Scene* scene)
		{
			loadedScene = scene;
		}

		Entities::Scene* loadedScene;
	};
}