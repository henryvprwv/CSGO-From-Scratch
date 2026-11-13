#pragma once

#pragma once
#include <Utility/Memory/FNV.h>

#include <unordered_map>
#include <type_traits>
#include <cstdint>
#include <fstream>

//https://www.youtube.com/watch?v=VCsNZ0GRVzo

class CRecvTable;
class Netvars
{
public:
	void Setup() noexcept;

	void Dump(const std::string_view Base, CRecvTable* Table, const std::uint32_t Offset) noexcept;

	std::unordered_map<std::uint32_t, std::uint32_t> Data = { };
};

Netvars* GetNetVars();

#define NETVAR(Name, Var, ...) \
inline std::add_lvalue_reference_t<__VA_ARGS__> Name() noexcept \
{ \
	static constexpr std::uint32_t HashVal = FNV::HashConst(Var); \
	const auto& NetVarData = GetNetVars()->Data; \
	if (const auto It = NetVarData.find(HashVal); It != NetVarData.end()) \
		return *reinterpret_cast<std::add_pointer_t<__VA_ARGS__>>(reinterpret_cast<std::uintptr_t>(this) + It->second); \
	static std::decay_t<__VA_ARGS__> Dummy{ }; \
	return Dummy; \
}
