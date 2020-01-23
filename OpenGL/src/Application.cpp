#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ScreenDef.h"

#include "GLErrorManager.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "tests/ClearColorTest.h"
#include "tests/QuadTest.h"
#include "tests/TestMenu.h"
#include "tests/Text2D.h"
#include "tests/Text3D.h"



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error: GLEW did not init" << std::endl;

	{ 
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		Renderer renderer;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		test::Test* currentTest = nullptr;
		test::TestMenu testMenu(currentTest);
		currentTest = &testMenu;
		testMenu.AddTest("clearColorTest", []() {return new test::ClearColorTest; });
		testMenu.AddTest("quadTest", [&renderer]() {return new test::QuadTest(renderer); });
		testMenu.AddTest("Texture Test", [&renderer]() {return new test::Text2D(renderer); });
		testMenu.AddTest("3D test", [&renderer]() {return new test::Text3D(renderer); });

		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			if (currentTest) {
				currentTest -> OnUpdate(0.0f);
				currentTest -> OnRender();
				ImGui::Begin("Test window");
				if (currentTest != &testMenu && ImGui::Button("<-")) {
					delete currentTest;
					currentTest = &testMenu;
				}
				currentTest -> OnGuiRender();
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
		if (currentTest != &testMenu)
			delete currentTest;
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}


