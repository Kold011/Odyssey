#pragma once
#include "ManagedObject.hpp"
#include "Array.hpp"
#include "Type.hpp"
#include "DataType.h"
#include "RawBuffer.h"

namespace Odyssey
{
	struct FieldMetadata
	{
		std::string Name;
		DataType Type;
		Coral::Type* ManagedType;
		RawBuffer DefaultValue;

	private:
		friend class ScriptingManager;

		template<typename T>
		void SetDefaultValue(Coral::ManagedObject& temp)
		{
			if (ManagedType->IsSZArray())
			{
				auto value = temp.GetFieldValue<Coral::Array<T>>(Name);
				RawBuffer::Copy(DefaultValue, value.Data(), value.ByteLength());
				Coral::Array<T>::Free(value);
			}
			else
			{
				DefaultValue.Allocate(sizeof(T));
				auto value = temp.GetFieldValue<T>(Name);
				DefaultValue.Write(&value, sizeof(T));
			}
		}
	};

	struct ScriptMetadata
	{
		std::string Name;
		uint32_t ScriptID;
		Coral::Type* Type;
		std::unordered_map<uint32_t, FieldMetadata> Fields;
	};
}