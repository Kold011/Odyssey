#pragma once
#include "uuid_v4.h"
#include "AssetHandle.h"
#include "DynamicList.h"
#include "Enums.h"

namespace Odyssey
{
	class Material;
	class Mesh;
	class Shader;

	class AssetManager
	{
	public:
		static void CreateDatabase();

	public:
		static AssetHandle<Mesh> LoadMesh(const std::string& assetPath);
		static AssetHandle<Shader> LoadShader(const std::string& assetPath);
		static AssetHandle<Material> LoadMaterial(const std::string& assetPath);

	public:
		static AssetHandle<Shader> LoadShaderByUUID(const std::string& uuid);
		static AssetHandle<Material> LoadMaterialByGUID(const std::string& guid);
		static AssetHandle<Mesh> LoadMeshByGUID(const std::string& guid);

	private:
		static std::string GenerateUUID();
	private:
		inline static DynamicList<Mesh> m_Meshes;
		inline static DynamicList<Shader> m_Shaders;
		inline static DynamicList<Material> s_Materials;
		inline static UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

		// Asset Database
		inline static std::unordered_map<std::string, std::filesystem::path> s_AssetDatabase;
		inline static std::unordered_map<std::string, uint32_t> s_LoadedAssets;
	};
}