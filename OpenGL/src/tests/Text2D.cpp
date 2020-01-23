#include "Text2D.h"
#include "imgui/imgui.h"
#include "ScreenDef.h"
#include <iostream>
#include "Model.h"

namespace test {
	Text2D::Text2D(Renderer& r)
		:m_Renderer(r), 
		m_TranslationA(0.0f), m_TranslationB(0.0f),
		m_RotateA(0.0f), m_RotateB(0.0f),
		m_ScaleA(1.0f), m_ScaleB(1.0f),
		m_Proj(glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f)),
		m_CamPos(glm::vec3(0.0f, 0.0f, 3.0f)),
		m_CamRot(0.0f)
	{
		float vertexData[] = {
			-0.5f,	-0.5f,	0.0f, 0.0f,
			0.5f, -0.5f,	1.0f, 0.0,
			0.5f, 0.5f, 1.0f, 1.0f,
			-0.5f,	0.5f, 0.0f, 1.0f
		};

		unsigned int indexData[] = {
			0, 1, 2,
			2, 3, 0
		};


		m_Vb = new VertexBuffer(vertexData, 16 * sizeof(float));

		m_Ib = new IndexBuffer(indexData, 6);

		VertexBufferLayout layout;
		layout.AddAttribute<float>(2);
		layout.AddAttribute<float>(2);

		m_Va = new VertexArray();
		m_Va -> AddBuffer(*m_Vb, layout);

		m_Shader = new Shader("res/shader/text2DTest.shader");

		m_Texture = new Texture("res/tex/spriteMale.png");
		m_Texture->Bind(0);
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);
	}

	Text2D::~Text2D()
	{
		delete m_Vb;
		delete m_Ib;
		delete m_Va;
		delete m_Shader;
		delete m_Texture;
	}

	void Text2D::OnUpdate(float deltaTime)
	{
	}

	void Text2D::OnRender()
	{
		glm::mat4 view = glm::translate(glm::mat4(1.0f), -m_CamPos);
		view = glm::rotate(view, glm::radians(m_CamRot), glm::vec3(0, 0, 1.0f));
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			model = glm::rotate(model, glm::radians(m_RotateA[2]), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, glm::radians(m_RotateA[1]), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(m_RotateA[0]), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(m_ScaleA[0], m_ScaleA[1], 0.0f));
			glm::mat4 mvp = m_Proj * view * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Renderer.Draw(*m_Va, *m_Ib, *m_Shader);
		}
		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			model = glm::rotate(model, glm::radians(m_RotateB[2]), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::rotate(model, glm::radians(m_RotateB[1]), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::rotate(model, glm::radians(m_RotateB[0]), glm::vec3(1.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(m_ScaleB[0], m_ScaleB[1], 0.0f));
			glm::mat4 mvp = m_Proj * view * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Renderer.Draw(*m_Va, *m_Ib, *m_Shader);
		}
	}

	void Text2D::OnGuiRender()
	{
		ImGui::SliderFloat3("Texture A Pos", &m_TranslationA[0], -3.0f, 3.0f);
		ImGui::SliderFloat3("Texture A Rot", &m_RotateA[0], 0.0f, 360.0f);
		ImGui::SliderFloat2("Texture A Scale", &m_ScaleA[0], 0.0f, 5.0f);

		ImGui::SliderFloat3("Texture B Pos", &m_TranslationB[0], -3.0f, 3.0f);
		ImGui::SliderFloat3("Texture B Rot", &m_RotateB[0], 0.0f, 360.0f);
		ImGui::SliderFloat2("Texture B Scale", &m_ScaleB[0], 0.0f, 5.0f);

		ImGui::SliderFloat3("Camera Pos", &m_CamPos[0], -5.0f, 5.0f);
		ImGui::SliderFloat("Camera Rot", &m_CamRot, 0.0f, 360.0f);

	}
}
