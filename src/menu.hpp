#pragma once

enum IMGUI_WND_PAGES : short
{
	P_NONE = 0,
	P_LEGIT,
	P_VISUALS,
	P_MISC,
	P_COLORS,
	P_SETTINGS
};

namespace Glfw
{
	bool GenerateWindow();
	bool WindowNotClosed();
}

namespace Gui
{
	void InitImGui();
	void Render();
	void Shutdown();
}