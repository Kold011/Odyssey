#pragma once
#include "Scene.h"

namespace Odyssey
{
	struct OnBuildFinished;
	struct OnAssembliesReloaded;

	class SceneManager
	{
	public:
		static void ListenForEvents();

		static void LoadScene(const std::string& filename);
		static void SaveActiveScene(const std::string& filename);

		static Scene* GetActiveScene();

	public:
		static void Update();

	private:
		static void BuildFinished(OnBuildFinished* onBuildFinished);
		static void AssembliesReloaded(OnAssembliesReloaded* reloadedEvent);

	private:
		inline static std::vector<std::shared_ptr<Scene>> scenes;
		inline static int activeScene = -1;
		inline static const std::string tempSaveFilename = "tmps.yaml";

	};
}