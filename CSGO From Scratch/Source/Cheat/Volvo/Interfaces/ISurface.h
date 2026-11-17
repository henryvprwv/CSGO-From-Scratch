#pragma once

#include <Utility/Memory/Memory.h>

// https://github.com/ValveSoftware/source-sdk-2013/blob/e1f1fd42271805072f052051c26c21caa2c87b04/src/public/vgui/ISurface.h#L120-L403

class ISurface
{
public:
	void DrawSetColor(int r, int g, int b, int a)
	{
		return GetMemory()->Call<void>(this, 15, r, g, b, a);
	}

	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		return GetMemory()->Call<void>(this, 16, x0, y0, x1, y1);
	}

	void DrawOutlinedRect(int x0, int y0, int x1, int y1)
	{
		return GetMemory()->Call<void>(this, 18, x0, y0, x1, y1);
	}

	void DrawLine(int x0, int y0, int x1, int y1)
	{
		return GetMemory()->Call<void>(this, 19, x0, y0, x1, y1);
	}
};