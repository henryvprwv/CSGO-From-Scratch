#include <Volvo/Classes/CEntity.h>
#include <Core/Interfaces/Interfaces.h>

CEntity* CEntity::GetLocalPlayer() noexcept
{
	auto pLocal = GetInterfaces()->EntityList->GetClientEntity(GetInterfaces()->Engine->GetLocalPlayer());
	if (!pLocal) return nullptr;

	return pLocal;
}