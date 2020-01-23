#include "TestMenu.h"
#include "imgui/imgui.h"


namespace test {

	TestMenu::TestMenu(Test *& currentTest)
		: m_currentTest{currentTest}
	{
	}
	
	void TestMenu::OnGuiRender()
	{
		for (unsigned int i = 0; i < m_Tests.size(); i++)
		{
			if (ImGui::Button(m_Tests[i].first.c_str()))
				m_currentTest = m_Tests[i].second();
		}
	}
	
	void TestMenu::AddTest(const std::string & name, std::function<Test*(void)> test)
	{
		m_Tests.push_back({ name, test });
	}
}

