#pragma once
#include "Asset.h"
#include "BinaryBuffer.h"
#include "Enums.h"
#include "FileManager.h"

namespace Odyssey
{
	class SourceShader : public SourceAsset
	{
		CLASS_DECLARATION(Odyssey, SourceShader)
	public:
		SourceShader() = default;
		SourceShader(const Path& sourcePath);
		~SourceShader()
		{
			FileManager::Get().UntrackFile(m_TrackingID);
		}

	public:
		bool Compile();
		bool Compile(ShaderType shaderType, BinaryBuffer& codeBuffer);

	public:
		const std::string& GetShaderLanguage() { return m_ShaderLanguage; }
		bool IsCompiled() { return m_Compiled; }
		std::vector<ShaderType> GetShaderTypes();

	private:
		void ParseShaderFile(const Path& path);
		void ParseShaderCode(const std::string& fileContents);
		void OnFileAction(const Path& oldFilename, const Path& newFilename, FileActionType fileAction);

	private:
		std::string m_ShaderName;
		std::string m_ShaderLanguage;
		std::string m_VertexShaderCode;
		std::string m_FragmentShaderCode;
		std::map<ShaderType, std::string> m_ShaderCode;
		TrackingID m_TrackingID;
		bool m_Compiled = false;

	private:
		inline static std::unordered_map<ShaderType, std::string> ShaderPragmaMap =
		{
			{ ShaderType::Vertex, "#pragma Vertex\n" },
			{ ShaderType::Fragment, "#pragma Fragment\n" },
			{ ShaderType::Compute, "#pragma Compute\n" },
			{ ShaderType::Geometry, "#pragma Geometry\n" }
		};
	};
}