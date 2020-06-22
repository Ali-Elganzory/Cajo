#include <Cajo.h>

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
			out vec3 v_Position;

			uniform mat4 u_ViewProjection;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fargmentSource = R"(
			#version 330 core
			
			in vec3 v_Position;
			layout(location = 0) out vec4 color;
			
			void main()
			{
				color = vec4((v_Position + 1) / 2, 1.0);
			}
		)";

		m_Shader.reset(Cajo::Shader::Create(vertexSource, fargmentSource));
		////////////////////////////////////////////////
	}

	void OnUpdate() override
	{
		if (Cajo::Input::IsKeyPressed(CAJO_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		
		if (Cajo::Input::IsKeyPressed(CAJO_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;

		if (Cajo::Input::IsKeyPressed(CAJO_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (Cajo::Input::IsKeyPressed(CAJO_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;

		if (Cajo::Input::IsKeyPressed(CAJO_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;

		if (Cajo::Input::IsKeyPressed(CAJO_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		/////////////////////////////////////////////////
		Cajo::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Cajo::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Cajo::Renderer::BeginScene(m_Camera);

		Cajo::Renderer::Submit(m_Shader, m_VertexArray);

		Cajo::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Cajo::Event& event) override
	{

	}

private:
	std::shared_ptr<Cajo::Shader> m_Shader;
	std::shared_ptr<Cajo::VertexArray> m_VertexArray;

	Cajo::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.01f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 3.0f;
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