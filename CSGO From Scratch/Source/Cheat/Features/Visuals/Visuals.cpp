#include "Visuals.h"

#include <Volvo/Classes/CEntity.h>
#include <Core/Interfaces/Interfaces.h>

Visuals* GetVisuals()
{
	static Visuals GVisuals{};
	return &GVisuals;
}

void Visuals::OnPaintTraverse()
{
	this->ESP();
}

void Visuals::ESP()
{
	if (!GetInterfaces()->Engine->IsInGame()) return;

	auto pLocal = CEntity::GetLocalPlayer();

	auto LocalPos = pLocal->GetAbsOrigin();

	for (int i = 1; i < 64; i++)
	{
		auto Entity = GetInterfaces()->EntityList->GetClientEntity(i);
		if (!Entity || !Entity->IsAlive() || Entity == pLocal) continue;

		auto EntityPos = Entity->GetAbsOrigin();

		Vector ScreenPos;
		if (GetInterfaces()->DebugOverlay->ScreenPosition(EntityPos, ScreenPos)) continue; // returns true if pos is out of fov

		int W, H;
		GetInterfaces()->Engine->GetScreenSize(W, H);

		GetInterfaces()->Surface->DrawSetColor(255, 255, 255, 255);
		GetInterfaces()->Surface->DrawLine(W / 2, H, static_cast<int>(ScreenPos.X), static_cast<int>(ScreenPos.Y));
	}
}
