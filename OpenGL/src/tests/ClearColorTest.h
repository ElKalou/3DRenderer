#pragma once
#include "Test.h"

namespace test {
	class ClearColorTest : public Test {
	private:
		float m_ClearColor[4];

	public:
		ClearColorTest();
		~ClearColorTest() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGuiRender() override;
	};
}
