#pragma once

namespace Odyssey
{
	class AssetManager;

	template<typename T>
	struct AssetHandle
	{
	public:
		AssetHandle()
		{
			m_ID = -1;
			m_Ptr = nullptr;
		}

		AssetHandle(uint64_t id, T* ptr)
		{
			m_ID = id;
			m_Ptr = ptr;
		}

	public:
		T* Get() { return m_Ptr; }
		uint64_t GetID() { return m_ID; }
		bool IsValid() { return m_ID != (uint64_t)(-1); }
		void Reset() { m_ID = -1; m_Ptr = nullptr; }

	private:
		friend class AssetManager;
		uint64_t m_ID = (uint64_t)(-1);
		T* m_Ptr = nullptr;
	};
}