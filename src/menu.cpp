#include "menu.hpp"
#include "settings/globals.hpp"
#include "helpers/utils.hpp"
#include "../sdk/sdk.hpp"

#include <shellapi.h>
#include <glfw/include/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl2.h>

#pragma comment(lib, "glfw3.lib")

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static const char* bones[6]{ "Pelvic", "Stomach", "Lower Chest", "Upper Chest", "Neck", "Head" };

GLFWwindow* window = nullptr;

bool gui::generateWindow()
{
	glfwSetErrorCallback(nullptr);
	if (glfwInit() == GLFW_FALSE)
		return false;

	// Create Window
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(1000, 560, utils::randomString(12).c_str(), nullptr, nullptr);
	if (!window)
		return false;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	return true;
}

bool gui::windowNotClosed()
{
	return !glfwWindowShouldClose(window);
}

void gui::initilize()
{
	// Set ImGui Flags
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;

	// Preset style
	ImGuiStyle& style = ImGui::GetStyle();
	{
		style.Alpha = 0.75f;
		style.WindowRounding = 1.f;
		style.FrameRounding = 2.f;
		style.ScrollbarSize = 2.f;
		style.ScrollbarRounding = 12.f;
		style.GrabMinSize = 5.f;
		style.FramePadding = ImVec2(3.f, 2.f);
		style.WindowPadding = ImVec2(8.f, 8.f);
		style.ItemSpacing = ImVec2(8.f, 4.f);
		style.ItemInnerSpacing = ImVec2(4.f, 4.f);

		style.Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		style.Colors[ImGuiCol_TextDisabled] = ImColor(128, 128, 128);
		style.Colors[ImGuiCol_WindowBg] = ImColor(0, 0, 0);
		style.Colors[ImGuiCol_ChildBg] = ImColor(0, 0, 0);
		style.Colors[ImGuiCol_Border] = ImColor(255, 0, 0);
		style.Colors[ImGuiCol_FrameBg] = ImColor(75, 75, 75);
		style.Colors[ImGuiCol_FrameBgHovered] = ImColor(155, 155, 155);
		style.Colors[ImGuiCol_FrameBgActive] = ImColor(80, 90, 100);
		style.Colors[ImGuiCol_TitleBg] = ImColor(255, 50, 50);
		style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(255, 0, 0);
		style.Colors[ImGuiCol_TitleBgActive] = ImColor(255, 0, 0);
		style.Colors[ImGuiCol_MenuBarBg] = ImColor(128, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrab] = ImColor(255, 0, 0);
		style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImColor(255, 50, 50);
		style.Colors[ImGuiCol_ScrollbarGrabActive] = ImColor(128, 0, 0);
		style.Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 0);
		style.Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 50, 50);
		style.Colors[ImGuiCol_Button] = ImColor(255, 0, 0);
		style.Colors[ImGuiCol_ButtonHovered] = ImColor(200, 50, 50);
		style.Colors[ImGuiCol_ButtonActive] = ImColor(128, 0, 0);
	}

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL2_Init();
}

void gui::render()
{
	static int tab = IMGUI_WND_PAGES::P_LEGIT;

	glfwPollEvents();

	// Show window on key press
	if (GetAsyncKeyState(VK_INSERT) & 1)
		glfwShowWindow(window);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
	ImGui::SetNextWindowSize(ImVec2(1000.f, 560.f));

	// Render ImGui
	ImGui::Begin("Destiny.ut", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
	{
		ImGui::SetCursorPos(ImVec2(12.5f, 25.f));
		ImGui::BeginChild("Features", ImVec2(175.f, 560.f), false);
		{
			if (ImGui::Button("Legit", ImVec2(155.f, 50.f)))
				tab = IMGUI_WND_PAGES::P_LEGIT;
			if (ImGui::Button("Visuals", ImVec2(155.f, 50.f)))
				tab = IMGUI_WND_PAGES::P_VISUALS;
			if (ImGui::Button("Misc", ImVec2(155.f, 50.f)))
				tab = IMGUI_WND_PAGES::P_MISC;
			if (ImGui::Button("Colors", ImVec2(155.f, 50.f)))
				tab = IMGUI_WND_PAGES::P_COLORS;
			if (ImGui::Button("Settings", ImVec2(155.f, 50.f)))
				tab = IMGUI_WND_PAGES::P_SETTINGS;
		}
		ImGui::EndChild();

		ImGui::SameLine();
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(180.f, 25.f), ImVec2(180.f, 550.f), ImColor(255, 0, 0));
		ImGui::SameLine();

		ImGui::BeginChild("Options", ImVec2(825.f, 560.f), false);
		{
			if (tab == IMGUI_WND_PAGES::P_LEGIT)
			{
				ImGui::BeginChild("Aimbot", ImVec2(390.f, 525.f), true);
				{
					ImGui::Text("Aimbot");
					ImGui::Separator();
					ImGui::Checkbox("Enable###AimbotEnable", &g_Options.Legit.Aimbot.Enable);
					ImGui::Checkbox("Auto Aim###AimbotAutoAim", &g_Options.Legit.Aimbot.AutoAim);
					ImGui::Checkbox("Deathmatch###AimbotDeathmatch", &g_Options.Legit.Aimbot.Deathmatch);
					ImGui::Checkbox("Visible###AimbotVisible", &g_Options.Legit.Aimbot.Visible);
					ImGui::Checkbox("Scoped###AimbotScoped", &g_Options.Legit.Aimbot.Scoped);
					ImGui::Checkbox("Flashed###AimbotFlashed", &g_Options.Legit.Aimbot.Flashed);
					ImGui::Checkbox("In Air###AimbotInAir", &g_Options.Legit.Aimbot.InAir);
					ImGui::Combo("Target Bone###TargetBone", &g_Options.Legit.Aimbot.TargetBone, bones, IM_ARRAYSIZE(bones));
					ImGui::SliderInt("Smoothing###AimbotSmoothing", &g_Options.Legit.Aimbot.Smoothing, 1, 25);
					ImGui::SliderInt("FOV###AimbotFov", &g_Options.Legit.Aimbot.Fov, 1, 1000);
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild("Triggerbot", ImVec2(390.f, 305.f), true);
				{
					ImGui::Text("Triggerbot");
					ImGui::Separator();
					ImGui::Checkbox("Enable###TriggerbotEnable", &g_Options.Legit.Triggerbot.Enable);
					ImGui::Checkbox("Auto Fire###TriggerbotAutoFire", &g_Options.Legit.Triggerbot.AutoFire);
					ImGui::Checkbox("Deathmatch###TriggerbotDeathmatch", &g_Options.Legit.Triggerbot.Deathmatch);
					ImGui::Checkbox("Scoped###TriggerbotScoped", &g_Options.Legit.Triggerbot.Scoped);
					ImGui::Checkbox("Flashed###TriggerbotFlashed", &g_Options.Legit.Triggerbot.Flashed);
					ImGui::Checkbox("In Air###TriggerbotInAir", &g_Options.Legit.Triggerbot.InAir);
					ImGui::SliderInt("Delay###TriggerbotDelay", &g_Options.Legit.Triggerbot.Delay, 0, 500);
					ImGui::Separator();
					ImGui::Checkbox("Exclude Guns###TriggerbotExcludeGuns", &g_Options.Legit.Triggerbot.ExcludeGuns);
					ImGui::Checkbox("Auto Knife###HelpersAutoKnife", &g_Options.Legit.Triggerbot.AutoKnife);
					ImGui::Checkbox("Auto Taser###HelpersAutoTaser", &g_Options.Legit.Triggerbot.AutoTaser);
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(398.5f, 315.f));

				ImGui::BeginChild("RCS", ImVec2(390.f, 210.f), true);
				{
					ImGui::Text("RCS");
					ImGui::Separator();
					ImGui::Checkbox("Enable###RCSEnable", &g_Options.Legit.RCS.Enable);
					ImGui::SliderFloat("###RCSAmount", &g_Options.Legit.RCS.Amount, 0.f, 100.f, "%.f");
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_VISUALS)
			{
				ImGui::BeginChild("Glow", ImVec2(390.f, 305.f), true);
				{
					ImGui::Text("Glow");
					ImGui::Separator();
					ImGui::Checkbox("Enable###GlowEnable", &g_Options.Visuals.Glow.Enable);
					ImGui::Checkbox("Visible###GlowVisible", &g_Options.Visuals.Glow.Visible);
					ImGui::Checkbox("Healthbased###GlowHealthbased", &g_Options.Visuals.Glow.Healthbased);
					ImGui::Checkbox("Defusing###GlowDefusing", &g_Options.Visuals.Glow.Defusing);
					ImGui::Checkbox("Scoped###GlowScoped", &g_Options.Visuals.Glow.Scoped);
					ImGui::Checkbox("Flashed###GlowFlashed", &g_Options.Visuals.Glow.Flashed);
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild("ColorChams", ImVec2(390.f, 305.f), true);
				{
					ImGui::Text("Color Chams");
					ImGui::Separator();
					ImGui::Checkbox("Enable###ChamsEnable", &g_Options.Visuals.Chams.Enable);
					if (ImGui::Button("Clear###ChamsClear"))
					{
						g_Options.Visuals.Chams.Enable = false;
						ClrRender_t clearClr = { 255, 255, 255 };
						for (short i = 0; i < 64; ++i)
						{
							CEntity entity = g_Client.getEntityFromList(i + 1);
							entity.setClrRender(clearClr);
						}
					}
				}
				ImGui::EndChild();

				ImGui::BeginChild("World", ImVec2(390.f, 210.f), true);
				{
					ImGui::Text("World");
					ImGui::Separator();
					ImGui::Checkbox("Radar###WorldRadar", &g_Options.Visuals.World.Radar);
					ImGui::SliderFloat("Brightness###WorldBrightness", &g_Options.Visuals.World.Brightness, 0.f, 20.f, "%.0f");
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_MISC)
			{
				ImGui::BeginChild("Helpers", ImVec2(390.f, 305.f), true);
				{
					ImGui::Text("Helpers");
					ImGui::Separator();
					ImGui::Checkbox("Bunnyhop###HelpersBunnyhop", &g_Options.Misc.Helpers.Bunnyhop);
					ImGui::Checkbox("Auto Pistol###HelpersAutoPistol", &g_Options.Misc.Helpers.AutoPistol);
					ImGui::Checkbox("No Flash###VisualsNoFlash", &g_Options.Misc.Helpers.NoFlash);
					ImGui::SliderInt("FOV###VisualsFOV", &g_Options.Misc.Helpers.Fov, 50, 150);
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_COLORS)
			{
				ImGui::BeginChild("Glow", ImVec2(390.f, 305.f), true);
				{
					ImGui::Text("Glow");
					ImGui::Separator();
					ImGui::ColorEdit3("Teammates###GlowTeammates", reinterpret_cast<float*>(&g_Options.Colors.Glow.Teammates), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Enemies###GlowEnemy", reinterpret_cast<float*>(&g_Options.Colors.Glow.Enemies), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Enemies Visible###GlowEnemiesVisible", reinterpret_cast<float*>(&g_Options.Colors.Glow.EnemiesVisible), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Defusing###GlowDefusing", reinterpret_cast<float*>(&g_Options.Colors.Glow.Defusing), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Scoped###GlowScoped", reinterpret_cast<float*>(&g_Options.Colors.Glow.Scoped), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Flashed###GlowFlashed", reinterpret_cast<float*>(&g_Options.Colors.Glow.Flashed), ImGuiColorEditFlags_NoInputs);
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild("ColorChams", ImVec2(390.f, 305.f), true);
				{
					ImGui::Text("Color Chams");
					ImGui::Separator();
					ImGui::ColorEdit3("Teammates###ChamsTeammates", reinterpret_cast<float*>(&g_Options.Colors.Chams.Teammates), ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Enemies###ChamsEnemies", reinterpret_cast<float*>(&g_Options.Colors.Chams.Enemies), ImGuiColorEditFlags_NoInputs);
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_SETTINGS)
			{
				ImGui::BeginChild("Info", ImVec2(790.f, 180.f), true);
				{
					ImGui::Text("Info");
					ImGui::Separator();
					ImGui::Text("Source code:");
					ImGui::SameLine();
					if (ImGui::Button("GitHub", ImVec2(100.f, 17.5f)))
						ShellExecuteA(nullptr, nullptr, "https://www.github.com/TosoxDev/Destiny.ut", nullptr, nullptr, SW_SHOW);
					ImGui::Spacing();
					ImGui::Text("Credits");
					ImGui::Separator();
					ImGui::Text("-Special thanks to the GuidedHacking community");
					ImGui::Text("-Offsets provided by: hazedumper");
					ImGui::Text("-GUI powered by: ImGui and GLFW");
					ImGui::Text("-JSON library by: Niels Lohmann");
					ImGui::Separator();
					ImGui::Checkbox("Enable Developer", &g_Options.Developer.Enable);
				}
				ImGui::EndChild();

				if (g_Options.Developer.Enable)
				{
					ImGui::BeginChild("Developer", ImVec2(790.f, 235.f), true);
					{
						ImGui::Text("Developer");
						ImGui::Separator();
						ImGui::SliderFloat("Glow Alpha", &g_Options.Developer.GlowAlpha, 0.f, 1.f, "%.2f");
						ImGui::SliderInt("Glow Style", &g_Options.Developer.GlowStyle, 0, 3);
						ImGui::Separator();
						if (ImGui::Button("Reset"))
						{
							g_Options.Developer.GlowAlpha = 0.65f;
							g_Options.Developer.GlowStyle = 0;
						}
					}
					ImGui::EndChild();
				}
			}
		}
		ImGui::EndChild();
	}
	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();

	int displayWidth, displayHeight;
	glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
	glViewport(0, 0, displayWidth, displayHeight);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);

}

void gui::shutdown()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}