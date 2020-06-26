#include <Cajo.h>

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Cajo::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		////////////////////////////////////////////////
		m_VertexArray.reset(Cajo::VertexArray::Create());

		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Cajo::Ref<Cajo::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cajo::VertexBuffer::Create(vertices, sizeof(vertices)));
		Cajo::BufferLayout layout = {
			{ Cajo::ShaderDataType::Float3, "a_Position" },
			{ Cajo::ShaderDataType::Float2, "a_TextureCoord" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		Cajo::Ref<Cajo::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cajo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		////	Flat Color Shader		////
		std::string flatColorShaderVertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(Cajo::Shader::Create(flatColorShaderVertexSource, flatColorShaderFragmentSource));

		////	Texture Shader		////
		std::string textureShaderVertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TextureCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec2 v_TextureCoord;
			
			void main()
			{
				v_TextureCoord = a_TextureCoord;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string textureShaderFragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec2 v_TextureCoord;
			uniform sampler2D u_Texture;
			
			void main()
			{
				color = texture(u_Texture, v_TextureCoord);
			}
		)";

		m_TextureShader.reset(Cajo::Shader::Create(textureShaderVertexSource, textureShaderFragmentSource));

		m_Texture2D = Cajo::Texture2D::Create("assets/textures/checker_board.png");

		m_TextureShader->Bind();
		m_TextureShader->UploadUniformInt("u_Texture", 0);
		////////////////////////////////////////////////
	}

	void OnUpdate(Cajo::Timestep ts) override
	{
		if (Cajo::Input::IsKeyPressed(CAJO_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		
		else if (Cajo::Input::IsKeyPressed(CAJO_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Cajo::Input::IsKeyPressed(CAJO_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		else if (Cajo::Input::IsKeyPressed(CAJO_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (Cajo::Input::IsKeyPressed(CAJO_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;

		else if (Cajo::Input::IsKeyPressed(CAJO_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		/////////////////////////////////////////////////
		Cajo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cajo::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Cajo::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		m_FlatColorShader->Bind();
		m_FlatColorShader->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
			for (int x = 0; x < 20; x++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0.11f * x, 0.11f * y, 0.0f });
				Cajo::Renderer::Submit(m_FlatColorShader, m_VertexArray, transform * scale);
			}

		m_Texture2D->Bind();
		Cajo::Renderer::Submit(m_TextureShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Cajo::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Checker Board Settings");
		ImGui::ColorPicker3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Cajo::Event& event) override
	{

	}

private:
	Cajo::Ref<Cajo::Shader> m_FlatColorShader;
	Cajo::Ref<Cajo::Shader> m_TextureShader;
	Cajo::Ref<Cajo::VertexArray> m_VertexArray;

	Cajo::Ref<Cajo::Texture2D> m_Texture2D;

	Cajo::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 65.0f;

	glm::vec3 m_SquareColor;
};

class Sandbox : public Cajo::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//PushOverlay(new Cajo::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Cajo::Application* Cajo::CreateApplication()
{
	return new Sandbox();
}