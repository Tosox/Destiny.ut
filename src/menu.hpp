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

namespace gui
{
	bool generateWindow();
	bool windowNotClosed();

	void initilize();
	void render();
	void shutdown();
}
