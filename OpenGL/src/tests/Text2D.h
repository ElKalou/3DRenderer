#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace test {
	class Text2D : public Test {
	private:
		VertexBuffer* m_Vb;
		IndexBuffer* m_Ib;
		VertexArray* m_Va;
		Shader* m_Shader;
		Texture* m_Texture;
		Renderer& m_Renderer;
		glm::vec3 m_TranslationA, m_TranslationB;
		glm::vec3 m_RotateA, m_RotateB;
		glm::vec2 m_ScaleA, m_ScaleB;
		glm::vec3 m_CamPos;
		float m_CamRot;
		glm::mat4 m_Proj;

	public:
		Text2D(Renderer& r);
		~Text2D() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnGuiRender() override;
	};
}
