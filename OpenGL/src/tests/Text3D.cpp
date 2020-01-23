#include <GL/glew.h>
#include "GLErrorManager.h"

#include "imgui/imgui.h"

#include "Text3D.h"
#include "VertexBuffer.h"
#include "ScreenDef.h"
#include "glm/gtx/transform.hpp"

namespace test {
	Text3D::Text3D(Renderer& r)
		: m_Renderer(r),
		m_TranslationA(0.0f),
		m_Proj(glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f)),
		m_CamPos(0.0f, 0.0f, 50.0f)
	{
		m_Model = std::make_unique<Model>("res/model/robot.obj");

		m_Vb = std::make_unique<VertexBuffer>(m_Model->m_VertexData.get(), m_Model->m_VertexDataCount * sizeof(float));
		m_Ib = std::make_unique<IndexBuffer>(m_Model->m_IndexData.get(), m_Model->m_IndexDataCount);
		
		VertexBufferLayout layout;
		layout.AddAttribute<float>(3);
		layout.AddAttribute<float>(2);
		layout.AddAttribute<float>(3);

		m_Va = std::make_unique<VertexArray>();
		m_Va->AddBuffer(*m_Vb, layout);

		m_Shader = std::make_unique<Shader>("res/shader/text3DTest.shader");

		m_Texture = std::make_unique<Texture>("res/tex/Drone_diff.png");

		m_Texture->Bind(0);
		m_Shader->Bind();
		m_Shader->SetUniform1i("u_Texture", 0);

	}

	Text3D::~Text3D()
	{
	}

	void Text3D::OnUpdate(float deltaTime)
	{
	}

	void Text3D::OnRender()
	{
		//TODO : cam.getViewMat
		glm::mat4 view = glm::translate(glm::mat4(1.0f), -m_CamPos);

		{
			glm::mat4 modelMat = m_Model->GetModelMat();
			glm::mat4 mvp = m_Proj * view *  modelMat;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			m_Renderer.Draw(*m_Va, *m_Ib, *m_Shader);
		}
		
	}

	void Text3D::OnGuiRender()
	{
		ImGui::SliderFloat3("pos", &m_Model->m_Pos[0], -5.0f, 5.0f);
		ImGui::SliderFloat3("rot", &m_Model->m_Rot[0], 0.0f, 360.0f);
		ImGui::SliderFloat("scl", &m_Model->m_Scl[0], -5.0f, 5.0f);
		m_Model->m_Scl[1] = m_Model->m_Scl[0];
		m_Model->m_Scl[2] = m_Model->m_Scl[0];
		ImGui::SliderFloat3("cam", &m_CamPos[0], 20.0f, 100.0f);
	}
}
