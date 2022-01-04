#include <Windows.h>
#include <shellapi.h>
#include <xor/xor.hpp>
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

#define MAX_PLAYERS 64

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
	window = glfwCreateWindow(800, 450, XorStr(Utils::random_string(12).c_str()), NULL, NULL);
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
	ImGui::Begin(XorStr("Destiny.ut"), nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar| ImGuiWindowFlags_NoScrollWithMouse);
	{
		ImGui::SetCursorPos(ImVec2(12.5f, 25.0f));
		ImGui::BeginChild(XorStr("Features"), ImVec2(175.0f, 450.0f), false);
		{
			if (ImGui::Button(XorStr("Legit"), ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_LEGIT;
			if (ImGui::Button(XorStr("Visuals"), ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_VISUALS;
			if (ImGui::Button(XorStr("Misc"), ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_MISC;
			if (ImGui::Button(XorStr("Colors"), ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_COLORS;
			if (ImGui::Button(XorStr("Settings"), ImVec2(155.0f, 50.0f)))
				tab = IMGUI_WND_PAGES::P_SETTINGS;
		}
		ImGui::EndChild();

		ImGui::SameLine();
		ImGui::GetForegroundDrawList()->AddLine(ImVec2(180.0f, 25.0f), ImVec2(180.0f, 440.0f), ImColor(255, 0, 0));
		ImGui::SameLine();

		ImGui::BeginChild(XorStr("Options"), ImVec2(625.0f, 450.0f), false);
		{
			if (tab == IMGUI_WND_PAGES::P_LEGIT)
			{
				ImGui::BeginChild(XorStr("Aimbot"), ImVec2(290.0f, 415.0f), true);
				{
					ImGui::Text(XorStr("Aimbot"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Enable###AimbotEnable"), &g_Options.Legit.Aimbot.Enable);
					ImGui::Checkbox(XorStr("Auto Aim###AimbotAutoAim"), &g_Options.Legit.Aimbot.AutoAim);
					ImGui::Checkbox(XorStr("Deathmatch###AimbotDeathmatch"), &g_Options.Legit.Aimbot.Deathmatch);
					ImGui::Checkbox(XorStr("Visible###AimbotVisible"), &g_Options.Legit.Aimbot.Visible);
					ImGui::Checkbox(XorStr("Scoped###AimbotScoped"), &g_Options.Legit.Aimbot.Scoped);
					ImGui::Checkbox(XorStr("Flashed###AimbotFlashed"), &g_Options.Legit.Aimbot.Flashed);
					ImGui::Checkbox(XorStr("In Air###AimbotInAir"), &g_Options.Legit.Aimbot.InAir);
					ImGui::Combo(XorStr("Target Bone###TargetBone"), &g_Options.Legit.Aimbot.TargetBone, bones, IM_ARRAYSIZE(bones));
					ImGui::SliderInt(XorStr("Smoothing###AimbotSmoothing"), &g_Options.Legit.Aimbot.Smoothing, 1, 25);
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild(XorStr("Triggerbot"), ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text(XorStr("Triggerbot"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Enable###TriggerbotEnable"), &g_Options.Legit.Triggerbot.Enable);
					ImGui::Checkbox(XorStr("Auto Fire###TriggerbotAutoFire"), &g_Options.Legit.Triggerbot.AutoFire);
					ImGui::Checkbox(XorStr("Deathmatch###TriggerbotDeathmatch"), &g_Options.Legit.Triggerbot.Deathmatch);
					ImGui::Checkbox(XorStr("Scoped###TriggerbotScoped"), &g_Options.Legit.Triggerbot.Scoped);
					ImGui::Checkbox(XorStr("Flashed###TriggerbotFlashed"), &g_Options.Legit.Triggerbot.Flashed);
					ImGui::Checkbox(XorStr("In Air###TriggerbotInAir"), &g_Options.Legit.Triggerbot.InAir);
					ImGui::SliderInt(XorStr("Delay###TriggerbotDelay"), &g_Options.Legit.Triggerbot.Delay, 0, 500);
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Exclude Guns###TriggerbotExcludeGuns"), &g_Options.Legit.Triggerbot.ExcludeGuns);
					ImGui::Checkbox(XorStr("Auto Knife###HelpersAutoKnife"), &g_Options.Legit.Triggerbot.AutoKnife);
					ImGui::Checkbox(XorStr("Auto Taser###HelpersAutoTaser"), &g_Options.Legit.Triggerbot.AutoTaser);
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(298.5f, 260.0f));

				ImGui::BeginChild(XorStr("RCS"), ImVec2(290.0f, 155.0f), true);
				{
					ImGui::Text(XorStr("RCS"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Enable###RCSEnable"), &g_Options.Legit.RCS.Enable);
					ImGui::SliderFloat(XorStr("###RCSAmount"), &g_Options.Legit.RCS.Amount, 0.0f, 100.0f, "%.0f");
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_VISUALS)
			{
				ImGui::BeginChild(XorStr("Glow"), ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text(XorStr("Glow"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Enable###GlowEnable"), &g_Options.Visuals.Glow.Enable);
					ImGui::Checkbox(XorStr("Teammates###GlowTeammates"), &g_Options.Visuals.Glow.Teammates);
					ImGui::Checkbox(XorStr("Visible###GlowVisible"), &g_Options.Visuals.Glow.Visible);
					ImGui::Checkbox(XorStr("Healthbased###GlowHealthbased"), &g_Options.Visuals.Glow.Healthbased);
					ImGui::Checkbox(XorStr("Defusing###GlowDefusing"), &g_Options.Visuals.Glow.Defusing);
					ImGui::Checkbox(XorStr("Scoped###GlowScoped"), &g_Options.Visuals.Glow.Scoped);
					ImGui::Checkbox(XorStr("Flashed###GlowFlashed"), &g_Options.Visuals.Glow.Flashed);
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild(XorStr("ColorChams"), ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text(XorStr("Color Chams"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Enable###ChamsEnable"), &g_Options.Visuals.Chams.Enable);
					ImGui::Checkbox(XorStr("Teammates###ChamsTeammates"), &g_Options.Visuals.Chams.Teammates);
					if (ImGui::Button(XorStr("Clear###ChamsClear")))
					{
						g_Options.Visuals.Chams.Enable = false;
						CEntity entity{};
						ClrRender_t clearClr = { 255, 255, 255 };
						for (short i = 0; i < MAX_PLAYERS; ++i)
						{
							entity.Set(g_Client.GetEntityFromList(i + 1));
							entity.SetClrRender(clearClr);
						}
					}
				}
				ImGui::EndChild();

				ImGui::BeginChild(XorStr("World"), ImVec2(290.0f, 155.0f), true);
				{
					ImGui::Text(XorStr("World"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Radar###WorldRadar"), &g_Options.Visuals.World.Radar);
					ImGui::SliderFloat(XorStr("Brightness###WorldBrightness"), &g_Options.Visuals.World.Brightness, 0.0f, 20.0f, "%.0f");
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_MISC)
			{
				ImGui::BeginChild(XorStr("Helpers"), ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text(XorStr("Helpers"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Bunnyhop###HelpersBunnyhop"), &g_Options.Misc.Helpers.Bunnyhop);
					ImGui::Checkbox(XorStr("Fake Lag###HelpersFakeLag"), &g_Options.Misc.Helpers.FakeLag);
					ImGui::Checkbox(XorStr("Auto Pistol###HelpersAutoPistol"), &g_Options.Misc.Helpers.AutoPistol);
					ImGui::Checkbox(XorStr("No Flash###VisualsNoFlash"), &g_Options.Misc.Helpers.NoFlash);
					ImGui::SliderInt(XorStr("FOV###VisualsFOV"), &g_Options.Misc.Helpers.Fov, 50, 150);
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_COLORS)
			{
				ImGui::BeginChild(XorStr("Glow"), ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text(XorStr("Glow"));
					ImGui::Separator();
					ImGui::ColorEdit3(XorStr("Teammates###GlowTeammates"), (float*)&g_Options.Colors.Glow.Teammates, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3(XorStr("Enemies###GlowEnemy"), (float*)&g_Options.Colors.Glow.Enemies, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3(XorStr("Enemies Visible###GlowEnemiesVisible"), (float*)&g_Options.Colors.Glow.EnemiesVisible, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3(XorStr("Defusing###GlowDefusing"), (float*)&g_Options.Colors.Glow.Defusing, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3(XorStr("Scoped###GlowScoped"), (float*)&g_Options.Colors.Glow.Scoped, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3(XorStr("Flashed###GlowFlashed"), (float*)&g_Options.Colors.Glow.Flashed, ImGuiColorEditFlags_NoInputs);
				}
				ImGui::EndChild();

				ImGui::SameLine();

				ImGui::BeginChild(XorStr("ColorChams"), ImVec2(290.0f, 250.0f), true);
				{
					ImGui::Text(XorStr("Color Chams"));
					ImGui::Separator();
					ImGui::ColorEdit3(XorStr("Teammates###ChamsTeammates"), (float*)&g_Options.Colors.Chams.Teammates, ImGuiColorEditFlags_NoInputs);
					ImGui::ColorEdit3(XorStr("Enemies###ChamsEnemies"), (float*)&g_Options.Colors.Chams.Enemies, ImGuiColorEditFlags_NoInputs);
				}
				ImGui::EndChild();
			}
			if (tab == IMGUI_WND_PAGES::P_SETTINGS)
			{
				ImGui::BeginChild(XorStr("Info"), ImVec2(590.0f, 180.0f), true);
				{
					ImGui::Text(XorStr("Info"));
					ImGui::Separator();
					ImGui::Text(XorStr("Source code:"));
					ImGui::SameLine();
					if (ImGui::Button(XorStr("GitHub"), ImVec2(100.0f, 17.5f)))
						ShellExecute(0, 0, L"http://www.github.com/TosoxDev/Destiny.ut", 0, 0, SW_SHOW);
					ImGui::Spacing();
					ImGui::Text(XorStr("Credits"));
					ImGui::Separator();
					ImGui::Text(XorStr("-Special thanks to the GuidedHacking community"));
					ImGui::Text(XorStr("-Offsets provided by: hazedumper"));
					ImGui::Text(XorStr("-GUI powered by: ImGui and GLFW"));
					ImGui::Text(XorStr("-JSON library by: Niels Lohmann"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Enable Developer"), &g_Options.Developer.Enable);
				}
				ImGui::EndChild();

				if (g_Options.Developer.Enable)
				{
					ImGui::BeginChild(XorStr("Developer"), ImVec2(590.0f, 235.0f), true);
					{
						ImGui::Text(XorStr("Developer"));
						ImGui::Separator();
						ImGui::Checkbox(XorStr("Unload on Exit"), &g_Options.Developer.UnloadOnExit);
						ImGui::Separator();
						ImGui::Checkbox(XorStr("Loop 32 entities"), &g_Options.Developer.Use32EntityLoop);
						ImGui::Separator();
						ImGui::SliderFloat(XorStr("Glow Alpha"), &g_Options.Developer.GlowAlpha, 0.0f, 1.0f, "%.2f");
						ImGui::SliderInt(XorStr("Glow Style"), &g_Options.Developer.GlowStyle, 0, 3);
						ImGui::Separator();
						ImGui::SliderFloat(XorStr("Player Flash Trigger"), &g_Options.Developer.LocalPlayerFlashFlagAmount, 0.0f, 10.0f, "%.2f");
						ImGui::SliderFloat(XorStr("Enemy Flash Trigger"), &g_Options.Developer.EntityFlashFlagAmount, 0.0f, 10.0f, "%.2f");
						ImGui::Separator();
						ImGui::SliderInt(XorStr("RCS Trigger"), &g_Options.Developer.RcsShotsTrigger, 0, 10);
						ImGui::Separator();
						if (ImGui::Button(XorStr("Reset")))
						{
							g_Options.Developer.UnloadOnExit = true;
							g_Options.Developer.Use32EntityLoop = false;
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