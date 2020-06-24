#include <Cajo.h>

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Cajo::Layer
{
public:
	ExampleLayer()
		: Layer("Example Layer"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		////////////////////////////////////////////////
		m_VertexArray.reset(Cajo::VertexArray::Create());

		float vertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
		};

		std::shared_ptr<Cajo::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Cajo::VertexBuffer::Create(vertices, sizeof(vertices)));
		Cajo::BufferLayout layout = {
			{ Cajo::ShaderDataType::Float3, "a_Position" },
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Cajo::IndexBuffer> indexBuffer;
		indexBuffer.reset(Cajo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			
			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fargmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;
			
			void main()
			{
				color = u_Color;
			}
		)";

		m_FlatColorShader.reset(Cajo::Shader::Create(vertexSource, fargmentSource));
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

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), { 0.1f, 0.1f, 0.1f });

		for (int y = 0; y < 20; y++)
			for (int x = 0; x < 20; x++)
			{
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), { 0.11f * x, 0.11f * y, 0.0f });
				if (x % 2 == 0 && y % 2 != 0 || x % 2 != 0 && y % 2 == 0)
					m_FlatColorShader->UploadUniformVec4("u_Color", { 0.8f, 0.3f, 0.4f, 1.0f });
				else
					m_FlatColorShader->UploadUniformVec4("u_Color", { 0.3f, 0.4f, 0.8f, 1.0f });
				Cajo::Renderer::Submit(m_FlatColorShader, m_VertexArray, transform * scale);
			}

		Cajo::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Cajo::Event& event) override
	{

	}

private:
	std::shared_ptr<Cajo::Shader> m_FlatColorShader;
	std::shared_ptr<Cajo::VertexArray> m_VertexArray;

	Cajo::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 65.0f;
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