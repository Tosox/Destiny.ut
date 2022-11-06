#include <Windows.h>
#include <shellapi.h>
#include <glfw/include/glfw3.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl2.h>
#include "menu.hpp"
#include "settings/globals.hpp"
#include "helpers/utils.hpp"
#include "sdk/Structs.hpp"

#pragma comment(lib, "glfw3.lib")

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

GLFWwindow* window;

static const char* bones[6]{ "Pelvic", "Stomach", "Lower Chest", "Upper Chest", "Neck", "Head" };

bool Glfw::GenerateWindow()
{
	// Use 'SW_SHOW' for debugging
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	glfwSetErrorCallback(NULL);
	if (!glfwInit())
		return false;

	// Create Window
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	window = glfwCreateWindow(800, 450, utils::randomString(12).c_str(), nullptr, nullptr);
	if (!window)
		return false;

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	return true;
}

bool Glfw::WindowNotClosed()
{
	return !glfwWindowShouldClose(window);
}

void Gui::InitImGui()
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
		style.WindowRounding = 1.0f;
		style.FrameRounding = 2.0f;
		style.ScrollbarSize = 2.0f;
		style.ScrollbarRounding = 12.0f;
		style.GrabMinSize = 5.0f;
		style.FramePadding = ImVec2(3.0f, 2.0f);
		style.WindowPadding = ImVec2(8.0f, 8.0f);
		style.ItemSpacing = ImVec2(8.0f, 4.0f);
		style.ItemInnerSpacing = ImVec2(4.0f, 4.0f);

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

void Gui::Render()
{
	static int tab = IMGUI_WND_PAGES::P_LEGIT;

	glfwPollEvents();

	// Show window on key press
	if (GetAsyncKeyState(VK_INSERT) & 1)
	{
		glfwShowWindow(window);
	}

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2(800.0f, 450.0f));

	// Render ImGui
	ImGui::Begin("Destiny.ut", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar| ImGuiWindowFlags_NoScrollWithMouse);
	{
		ImGui::SetCursorPos(ImVec2(12.5f, 25.0f));
		ImGui::BeginChild("Features", ImVec2(175.0f, 450.0f), false);
		{
			if (ImGui::Button("Legit", ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_LEGIT;
			if (ImGui::Button("Visuals", ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_VISUALS;
			if (ImGui::Button("Misc", ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_MISC;
			if (ImGui::Button("Colors", ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_COLORS;
			if (ImGui::Button("Settings", ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_SETTINGS;
		}
		ImGui::EndChild();

		ImGui::SameLine();
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(180.0f, 25.0f), ImVec2(180.0f, 440.0f), ImColor(255, 0, 0));
		ImGui::SameLine();

		ImGui::BeginChild("Options", ImVec2(625.0f, 450.0f), false);
		{
			if (tab == IMGUI_WND_PAGES::P_LEGIT)
			{
				ImGui::BeginChild("Aimbot", ImVec2(290.0f, 415.0f), true);
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
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild("Triggerbot", ImVec2(290.0f, 250.0f), true);
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

				ImGui::SetCursorPos(ImVec2(298.5f, 260.0f));

				ImGui::BeginChild("RCS", ImVec2(290.0f, 155.0f), true);
				{
					ImGui::Text("RCS");
					ImGui::Separator();
					ImGui::Checkbox("Enable###RCSEnable", &g_Options.Legit.RCS.Enable);
					ImGui::SliderFloat("###RCSAmount", &g_Options.Legit.RCS.Amount, 0.0f, 100.0f, "%.0f");
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_VISUALS)
			{
				ImGui::BeginChild("Glow", ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text("Glow");
					ImGui::Separator();
					ImGui::Checkbox("Enable###GlowEnable", &g_Options.Visuals.Glow.Enable);
					ImGui::Checkbox("Teammates###GlowTeammates", &g_Options.Visuals.Glow.Teammates);
					ImGui::Checkbox("Visible###GlowVisible", &g_Options.Visuals.Glow.Visible);
					ImGui::Checkbox("Healthbased###GlowHealthbased", &g_Options.Visuals.Glow.Healthbased);
					ImGui::Checkbox("Defusing###GlowDefusing", &g_Options.Visuals.Glow.Defusing);
					ImGui::Checkbox("Scoped###GlowScoped", &g_Options.Visuals.Glow.Scoped);
					ImGui::Checkbox("Flashed###GlowFlashed", &g_Options.Visuals.Glow.Flashed);
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild("ColorChams", ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text("Color Chams");
					ImGui::Separator();
					ImGui::Checkbox("Enable###ChamsEnable", &g_Options.Visuals.Chams.Enable);
					ImGui::Checkbox("Teammates###ChamsTeammates", &g_Options.Visuals.Chams.Teammates);
					if (ImGui::Button("Clear###ChamsClear"))
					{
						g_Options.Visuals.Chams.Enable = false;
						CEntity entity{};
						ClrRender_t clearClr = { 255, 255, 255 };
						for (short i = 0; i < 64; ++i)
						{
							entity = g_Client.getEntityFromList(i + 1);
							entity.setClrRender(clearClr);
						}
					}
				}
				ImGui::EndChild();

				ImGui::BeginChild("World", ImVec2(290.0f, 155.0f), true);
				{
					ImGui::Text("World");
					ImGui::Separator();
					ImGui::Checkbox("Radar###WorldRadar", &g_Options.Visuals.World.Radar);
					ImGui::SliderFloat("Brightness###WorldBrightness", &g_Options.Visuals.World.Brightness, 0.0f, 20.0f, "%.0f");
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_MISC)
			{
				ImGui::BeginChild("Helpers", ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text("Helpers");
					ImGui::Separator();
					ImGui::Checkbox("Bunnyhop###HelpersBunnyhop", &g_Options.Misc.Helpers.Bunnyhop);
					ImGui::Checkbox("Fake Lag###HelpersFakeLag", &g_Options.Misc.Helpers.FakeLag);
					ImGui::Checkbox("Auto Pistol###HelpersAutoPistol", &g_Options.Misc.Helpers.AutoPistol);
					ImGui::Checkbox("No Flash###VisualsNoFlash", &g_Options.Misc.Helpers.NoFlash);
					ImGui::SliderInt("FOV###VisualsFOV", &g_Options.Misc.Helpers.Fov, 50, 150);
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_COLORS)
			{
				ImGui::BeginChild("Glow", ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text("Glow");
					ImGui::Separator();
					ImGui::ColorEdit3("Teammates###GlowTeammates", (float*)&g_Options.Colors.Glow.Teammates, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Enemies###GlowEnemy", (float*)&g_Options.Colors.Glow.Enemies, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Enemies Visible###GlowEnemiesVisible", (float*)&g_Options.Colors.Glow.EnemiesVisible, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Defusing###GlowDefusing", (float*)&g_Options.Colors.Glow.Defusing, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Scoped###GlowScoped", (float*)&g_Options.Colors.Glow.Scoped, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Flashed###GlowFlashed", (float*)&g_Options.Colors.Glow.Flashed, ImGuiColorEditFlags_NoInputs);
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild("ColorChams", ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text("Color Chams");
					ImGui::Separator();
					ImGui::ColorEdit3("Teammates###ChamsTeammates", (float*)&g_Options.Colors.Chams.Teammates, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3("Enemies###ChamsEnemies", (float*)&g_Options.Colors.Chams.Enemies, ImGuiColorEditFlags_NoInputs);
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_SETTINGS)
			{
				ImGui::BeginChild("Info", ImVec2(590.0f, 180.0f), true);
				{
					ImGui::Text("Info");
					ImGui::Separator();
					ImGui::Text("Source code:");
					ImGui::SameLine();
					if (ImGui::Button("GitHub", ImVec2(100.0f, 17.5f)))
						ShellExecuteA(nullptr, nullptr, "http://www.github.com/TosoxDev/Destiny.ut", nullptr, nullptr, SW_SHOW);
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
					ImGui::BeginChild("Developer", ImVec2(590.0f, 235.0f), true);
					{
						ImGui::Text("Developer");
						ImGui::Separator();
						ImGui::Checkbox("Unload on Exit", &g_Options.Developer.UnloadOnExit);
						ImGui::Separator();
						ImGui::SliderFloat("Glow Alpha", &g_Options.Developer.GlowAlpha, 0.0f, 1.0f, "%.2f");
						ImGui::SliderInt("Glow Style", &g_Options.Developer.GlowStyle, 0, 3);
						ImGui::Separator();
						ImGui::SliderFloat("Player Flash Trigger", &g_Options.Developer.LocalPlayerFlashFlagAmount, 0.0f, 10.0f, "%.2f");
						ImGui::SliderFloat("Enemy Flash Trigger", &g_Options.Developer.EntityFlashFlagAmount, 0.0f, 10.0f, "%.2f");
						ImGui::Separator();
						ImGui::SliderInt("RCS Trigger", &g_Options.Developer.RcsShotsTrigger, 0, 10);
						ImGui::Separator();
						if (ImGui::Button("Reset"))
						{
							g_Options.Developer.UnloadOnExit = true;
							g_Options.Developer.GlowAlpha = 0.85f;
							g_Options.Developer.GlowStyle = 0;
							g_Options.Developer.LocalPlayerFlashFlagAmount = 2.5f;
							g_Options.Developer.EntityFlashFlagAmount = 2.5f;
							g_Options.Developer.RcsShotsTrigger = 3;
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

	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}

void Gui::Shutdown()
{
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}