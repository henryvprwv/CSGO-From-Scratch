#include <Core/Netvars/Netvars.h>
#include <Core/Interfaces/Interfaces.h>
#include <Volvo/Classes/CClientClass.h>

#include <format>
#include <fstream>
#include <shlobj.h>

Netvars* GetNetVars()
{
	static Netvars GNetVars{};
	return &GNetVars;
}

void Netvars::Setup() noexcept
{
	for (CClientClass* Client = GetInterfaces()->Client->GetAllClasses(); Client; Client = Client->Next)
		if (CRecvTable* Table = Client->Table)
			Dump(Client->NetworkName, Table, 0);

	// hardcoded netvars
	Data[FNV::HashConst("C_BaseEntity->m_MoveType")] = 0x25C;
}

void Netvars::Dump(const std::string_view Base, CRecvTable* Table, const std::uint32_t Offset) noexcept
{
	std::string TableKey;
	{
		std::string_view Name = Table->Name ? Table->Name : "";
		if (Name.size() > 3 && Name[0] == 'D' && Name[1] == 'T' && Name[2] == '_')
			Name.remove_prefix(3);
		TableKey = std::format("C{}", Name);
	}

	// loop through props
	for (auto I = 0; I < Table->Count; ++I) {
		const CRecvProp* Prop = &Table->Props[I];

		if (!Prop)
			continue;

		if (std::isdigit(Prop->Name[0]))
			continue;

		if (FNV::Hash(Prop->Name) == FNV::HashConst("baseclass"))
		{
			if (Prop->Type == ESendPropType::DATATABLE && Prop->Table)
				Dump(Base, Prop->Table, Offset + Prop->Offset);
			continue;
		}

		// not a root table, dump again
		if (Prop->Type == ESendPropType::DATATABLE &&
			Prop->Table && Prop->Table->Name[0] == 'D')
				Dump(Base, Prop->Table, Offset + Prop->Offset);

		// place offset in netvar map under both the network name
		const std::uint32_t Total = Offset + Prop->Offset;
		Data[FNV::Hash(std::format("{}->{}", Base, Prop->Name).c_str())] = Total;
		Data[FNV::Hash(std::format("{}->{}", TableKey, Prop->Name).c_str())] = Total;
	}
}
