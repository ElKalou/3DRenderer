#include <GL/glew.h>
#include "GLErrorManager.h"

#include "imgui/imgui.h"

#include "ClearColorTest.h"

namespace test {
	ClearColorTest::ClearColorTest()
		: m_ClearColor{0.0f, 0.0f, 0.0f, 0.0f}
	{
	}

	ClearColorTest::~ClearColorTest()
	{
	}

	void ClearColorTest::OnUpdate(float deltaTime)
	{
	}

	void ClearColorTest::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	}

	void ClearColorTest::OnGuiRender()
	{
		ImGui::ColorEdit4("Clear color", &m_ClearColor[0]);
	}
}
