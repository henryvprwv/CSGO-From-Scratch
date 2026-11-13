#pragma once
#include <cstdint>

enum class ESendPropType : std::int32_t
{
	INT = 0,
	FLOAT,
	VECTOR,
	VECTOR2D,
	STRING,
	ARRAY,
	DATATABLE,
	INT64,
	SENDPROPTYPEMAX
};

class CDataVariant
{
	union
	{
		float Float;
		std::int32_t Int;
		char* String;
		void* Data;
		float Vector[3];
		std::int64_t Int64;
	};

	ESendPropType Type;
};

class CRecvProp;
class CRecvProxyData
{
public:
	CRecvProp* Prop;
	CDataVariant Value;
	std::int32_t Element;
	std::int32_t ObjectID;
};

class CRecvTable
{
public:
	CRecvProp* Props;
	std::int32_t Count;
	void* Decoder;
	char* Name;
	bool IsInitialized;
	bool InMainList;
};

class CRecvProp
{
public:
	char* Name;
	ESendPropType Type;
	std::int32_t Flags;
	std::int32_t StringBufferSize;
	bool IsInsideArray;
	const void* ExtraData;
	CRecvProp* Prop;
	void* ArrayLengthProxyFn;
	void* ProxyFn;
	void* DataTableProxyFn;
	CRecvTable* Table;
	unsigned int Offset;
	std::int32_t Stride;
	std::int32_t Elements;
	const char* ParentPropName;
};
