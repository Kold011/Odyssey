#include "ComponentManager.h"

namespace Odyssey::Entities
{
	std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> ComponentManager::componentArrays;
	std::unordered_map<unsigned int, std::vector<std::pair<std::type_index, unsigned int>>> ComponentManager::gameObjectToComponentArrayIndex;

	void ComponentManager::ExecuteOnGameObjectComponents(const GameObject& gameObject, std::function<void(Component*)> func)
	{
		// For each game object
			// For each component assigned to the game object
		for (const auto& pair : gameObjectToComponentArrayIndex[gameObject.id])
		{
			// Get the component array and run the component for this game object's Awake
			func(componentArrays[pair.first]->componentData[pair.second].get());
		}
	}

	void ComponentManager::RemoveGameObject(const GameObject& gameObject)
	{
		// For each component assigned to the game object
		if (gameObjectToComponentArrayIndex.find(gameObject.id) != gameObjectToComponentArrayIndex.end())
		{
			for (const auto& pair : gameObjectToComponentArrayIndex[gameObject.id])
			{
				// Remove the game object from each component array
				componentArrays[pair.first]->RemoveGameObject(gameObject.id);
			}

			gameObjectToComponentArrayIndex.erase(gameObject.id);
		}
	}
}