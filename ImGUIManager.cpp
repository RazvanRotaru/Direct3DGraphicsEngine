#include "ImGUIManager.h"
#include "include\imgui\imgui.h"
#include "include\imgui\imgui_impl_dx11.h"
#include "include\imgui\imgui_impl_win32.h"
#include "MinWindows.h"

bool ImGUIManager::show_demo = false;

ImGUIManager::ImGUIManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
}

ImGUIManager::~ImGUIManager()
{
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
}

void ImGUIManager::DrawGui()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (show_demo) {
		ImGui::ShowDemoWindow(&show_demo);
	}

	ImGui::Begin("Settings");
	if (ImGui::Button("Show Demo")) {
		show_demo = !show_demo;
	}
	ImGui::End();


	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
