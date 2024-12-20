#pragma once
#include "Inspector.h"
#include "SourceShader.h"
#include "PropertyDrawers.h"

namespace Odyssey
{
	class SourceShaderInspector : public Inspector
	{
	public:
		SourceShaderInspector() = default;
		SourceShaderInspector(GUID guid);

	public:
		virtual bool Draw() override;

	private:
		void OnDstAssetPathChanged(std::string_view assetPath) { m_DstAssetPath = assetPath; }

	private:
		Ref<SourceShader> m_Shader;
		std::string m_DstAssetPath;
		StringDrawer m_ShaderNameDrawer;
		StringDrawer m_ShaderLanguageDrawer;
		StringDrawer m_DstAssetPathDrawer;
		BoolDrawer m_CompiledDrawer;
	};
}