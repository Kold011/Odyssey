#include "ScriptBindings.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "ScriptComponent.h"
#include "Transform.h"
#include "InternalCalls.hpp"

namespace Odyssey
{
#define ADD_INTERNAL_CALL(func) frameworkAssembly.AddInternalCall("Odyssey.InternalCalls", #func, (void*)InternalCalls::func)

	void ScriptBindings::Initialize(Coral::ManagedAssembly frameworkAssembly)
	{
		RegisterComponentType<Camera>(frameworkAssembly, Camera::Type);
		RegisterComponentType<MeshRenderer>(frameworkAssembly, MeshRenderer::Type);
		RegisterComponentType<Transform>(frameworkAssembly, Transform::Type);
		RegisterComponentType<ScriptComponent>(frameworkAssembly, ScriptComponent::Type);

		ADD_INTERNAL_CALL(GameObject_Create);
		ADD_INTERNAL_CALL(GameObject_GetName);
		ADD_INTERNAL_CALL(GameObject_SetName);
		ADD_INTERNAL_CALL(GameObject_AddComponent);
		ADD_INTERNAL_CALL(GameObject_HasComponent);
		ADD_INTERNAL_CALL(GameObject_RemoveComponent);

		frameworkAssembly.UploadInternalCalls();
	}
}