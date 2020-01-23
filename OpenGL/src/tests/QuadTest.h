#pragma once

#include <iostream>
#include "Test.h"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

namespace test {
	class QuadTest : public Test {

	private:
		float m_Pos[8] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f,  0.5f
		};
		unsigned int m_Index[6] = {
			0, 1, 2,
			2, 3, 0
		};

		VertexBuffer m_Vb;
		VertexBufferLayout m_Layout;
		const Renderer& m_Renderer;
		IndexBuffer m_Ib;
		VertexArray m_Va;
		Shader m_Shader;

	public:
		QuadTest(const Renderer& renderer);
		~QuadTest() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGuiRender() override;
	};
}
