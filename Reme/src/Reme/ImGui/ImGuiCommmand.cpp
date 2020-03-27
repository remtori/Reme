#include "pch.h"
#include "Reme/ImGui/ImGuiCommand.h"
#include "Reme/Core/Application.h"
#include "Reme/Core/Core.h"

#include <imgui.h>

#if defined(_REME_USE_GLFW) && defined(_REME_USE_OPENGL)
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#endif

namespace Reme
{
    void ImGuiCommand::Init()
    {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		ImGui::StyleColorsDark();
		ImGui::GetStyle().WindowRounding = 0.0f;

#if defined(_REME_USE_GLFW) && defined(_REME_USE_OPENGL)
		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*) Application::Get().GetWindow().GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
#endif
    }

    void ImGuiCommand::Shutdown()
    {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
    }

    void ImGuiCommand::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiCommand::End()
    {
	    ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float) app.GetWindow().GetWidth(), (float) app.GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			app.GetWindow().MakeContextCurrent();
		}
    }

	bool ImGuiCommand::ShouldSwallowEvent(Event& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		return (
			(event.IsInCategory(EventCategoryMouse) && io.WantCaptureMouse) ||
			(event.IsInCategory(EventCategoryKeyboard) && io.WantCaptureKeyboard)
		);
	}
}
