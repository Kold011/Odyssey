#include "IDComponent.h"

namespace Odyssey
{
	CLASS_DEFINITION(Odyssey, IDComponent);

	IDComponent::IDComponent(const GameObject& gameObject)
		: m_GameObject(gameObject)
	{
	}

	IDComponent::IDComponent(const GameObject& gameObject, Odyssey::GUID guid)
		: m_GameObject(gameObject), GUID(guid)
	{
	}

	IDComponent::IDComponent(const GameObject& gameObject, Odyssey::GUID guid, const std::string& name)
		: m_GameObject(gameObject), GUID(guid), Name(name)
	{
	}
}