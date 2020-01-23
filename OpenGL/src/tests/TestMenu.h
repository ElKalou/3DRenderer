#pragma once
#include <vector>
#include <string>
#include <functional>
#include "Test.h"

namespace test {

	class TestMenu : public Test {
	private:
		std::vector<std::pair<std::string, std::function<Test*(void)>>> m_Tests;
		Test*& m_currentTest;
	public:
		TestMenu(Test*& currentTest);
		void OnGuiRender() override;
		void AddTest(const std::string& testName, std::function<Test*(void)> test);
	};
}