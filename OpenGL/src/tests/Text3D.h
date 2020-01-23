#pragma once
#include "Test.h"
#include "Renderer.h"
#include "Texture.h"
#include "Model.h"


namespace test {
	class Text3D : public Test {
	private:
		std::unique_ptr<VertexBuffer> m_Vb;
		std::unique_ptr<IndexBuffer> m_Ib;
		std::unique_ptr<VertexArray> m_Va;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<Model> m_Model;
		Renderer& m_Renderer;
		glm::vec3 m_TranslationA;
		glm::mat4 m_Proj;
		glm::vec3 m_CamPos;

	public:
		Text3D(Renderer& r);
		~Text3D() override;
		void OnUpdate(float deltaTime);
		void OnRender();
		void OnGuiRender();
	};
}
