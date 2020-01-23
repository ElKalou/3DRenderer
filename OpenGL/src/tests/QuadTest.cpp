#include "QuadTest.h"
#include "imgui/imgui.h"

namespace test {
	QuadTest::QuadTest(const Renderer& renderer) :
		m_Vb(m_Pos, 4 * 2 * sizeof(float)),
		m_Ib(m_Index, 6),
		m_Shader("res/shader/quadTest.shader"),
		m_Renderer{ renderer }
	{
		m_Layout.AddAttribute<float>(2);
		m_Va.AddBuffer(m_Vb, m_Layout);
	}

	QuadTest::~QuadTest()
	{
	}

	void QuadTest::OnUpdate(float deltaTime)
	{
	}

	void QuadTest::OnRender()
	{
		m_Renderer.Draw(m_Va, m_Ib, m_Shader);
	}
	
	void QuadTest::OnGuiRender()
	{
		//ImGui::SliderFloat2("Bottom left", &m_Pos[0], -1.0f, 1.0f);
		//ImGui::SliderFloat2("Bottom right", &m_Pos[2], -1.0f, 1.0f);
		//ImGui::SliderFloat2("Top right", &m_Pos[4], -1.0f, 1.0f);
		//ImGui::SliderFloat2("Top left", &m_Pos[6], -1.0f, 1.0f);
	}
}