#include "cajopch.h"
#include "Renderer2D.h"

#include "Cajo/Renderer/RenderCommand.h"
#include "Cajo/Renderer/VertexArray.h"
#include "Cajo/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Cajo {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TextureCoord;
		float     TextureSlot;
		float     TileFactor;
	};

	struct Renderer2DData
	{
		static const uint32_t MAX_QUADS = 10000;
		static const uint32_t MAX_VERTICES = 4 * MAX_QUADS;
		static const uint32_t MAX_INDECIES = 6 * MAX_QUADS;
		static const uint32_t MAX_TEXTURE_SLOTS = 32;	// Renderer Capability

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> ColorTextureShader;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBasePtr = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		uint32_t TextureSlot = 1;	// 0 reserved for WHITE texture
		std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> Textures;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer = VertexBuffer::Create(Renderer2DData::MAX_VERTICES * sizeof(QuadVertex));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TextureCoord" },
			{ ShaderDataType::Float,  "a_TextureSlot" },
			{ ShaderDataType::Float,  "a_TileFactor" },
		};
		s_Data.QuadVertexBuffer->SetLayout(layout);
		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBasePtr = new QuadVertex[Renderer2DData::MAX_VERTICES];

		uint32_t indices[Renderer2DData::MAX_INDECIES];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < Renderer2DData::MAX_INDECIES; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;
								 
			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}
		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, Renderer2DData::MAX_INDECIES);
		s_Data.QuadVertexArray->SetIndexBuffer(indexBuffer);

		s_Data.ColorTextureShader = Shader::Create("assets/shaders/ColorTexture.glsl");
		s_Data.ColorTextureShader->Bind();

		int32_t samplers[Renderer2DData::MAX_TEXTURE_SLOTS];
		for (int32_t i = 0; i < Renderer2DData::MAX_TEXTURE_SLOTS; ++i)
			samplers[i] = i;

		s_Data.ColorTextureShader->SetIntArray("u_Texture", samplers, Renderer2DData::MAX_TEXTURE_SLOTS);

		Ref<Texture2D> whiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteData = 0xFFFFFFFF;
		whiteTexture->SetData(&whiteData, sizeof(uint32_t));
		s_Data.Textures[0] = whiteTexture;
	}

	void Renderer2D::Shutdown()
	{
		//delete s_Data;
		delete[] s_Data.QuadVertexBufferBasePtr;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.ColorTextureShader->Bind();
		s_Data.ColorTextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBasePtr;
		s_Data.QuadIndexCount = 0;
		s_Data.TextureSlot = 1;
	}

	void Renderer2D::EndScene()
	{
		Flush();
	}

	bool Renderer2D::IsBatchFull()
	{
		if (s_Data.QuadIndexCount == Renderer2DData::MAX_INDECIES || s_Data.TextureSlot == Renderer2DData::MAX_TEXTURE_SLOTS)
			return true;
		return false;
	}

	void Renderer2D::Flush()
	{
		uint32_t size = (uint8_t*)(s_Data.QuadVertexBufferPtr) - (uint8_t*)(s_Data.QuadVertexBufferBasePtr);
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBasePtr, size);

		for (uint32_t i = 0; i < s_Data.TextureSlot; ++i)
			s_Data.Textures[i]->Bind(i);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.QuadIndexCount);

		s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBasePtr;
		s_Data.QuadIndexCount = 0;
		s_Data.TextureSlot = 1;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		const float textureSlot = 0.0f;	// White texture [default texture]
		const float tileFactor = 1.0f;

		s_Data.QuadVertexBufferPtr->Position        = position;
		s_Data.QuadVertexBufferPtr->Color           = color;
		s_Data.QuadVertexBufferPtr->TextureCoord    = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TextureSlot     = textureSlot;
		s_Data.QuadVertexBufferPtr->TileFactor      = tileFactor;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position        = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color           = color;
		s_Data.QuadVertexBufferPtr->TextureCoord    = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TextureSlot     = textureSlot;
		s_Data.QuadVertexBufferPtr->TileFactor      = tileFactor;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position        = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color           = color;
		s_Data.QuadVertexBufferPtr->TextureCoord    = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TextureSlot     = textureSlot;
		s_Data.QuadVertexBufferPtr->TileFactor      = tileFactor;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position        = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color           = color;
		s_Data.QuadVertexBufferPtr->TextureCoord    = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TextureSlot     = textureSlot;
		s_Data.QuadVertexBufferPtr->TileFactor      = tileFactor;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadIndexCount += 6;

		if (IsBatchFull())
			Flush();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& tileFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tileFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const float& tileFactor, const glm::vec4& tintColor)
	{
		float textureSlot = 0.0f;
		// Check if the texture is already there in Renderer2DData
		for (uint32_t i = 0; i < s_Data.TextureSlot; ++i)
		{
			if (*s_Data.Textures[i].get() == *texture.get())
			{
				textureSlot = static_cast<float>(i);
				break;
			}
		}

		// Texture not a duplicate and is new
		if (!textureSlot)
		{
			textureSlot = static_cast<float>(s_Data.TextureSlot++);
			s_Data.Textures[static_cast<uint32_t>(textureSlot)] = texture;
		}

		s_Data.QuadVertexBufferPtr->Position        = position;
		s_Data.QuadVertexBufferPtr->Color           = tintColor;
		s_Data.QuadVertexBufferPtr->TextureCoord    = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TextureSlot     = textureSlot;
		s_Data.QuadVertexBufferPtr->TileFactor      = tileFactor;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position        = { position.x + size.x, position.y, position.z };
		s_Data.QuadVertexBufferPtr->Color           = tintColor;
		s_Data.QuadVertexBufferPtr->TextureCoord    = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferPtr->TextureSlot     = textureSlot;
		s_Data.QuadVertexBufferPtr->TileFactor      = tileFactor;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position        = { position.x + size.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color           = tintColor;
		s_Data.QuadVertexBufferPtr->TextureCoord    = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TextureSlot     = textureSlot;
		s_Data.QuadVertexBufferPtr->TileFactor      = tileFactor;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadVertexBufferPtr->Position        = { position.x, position.y + size.y, position.z };
		s_Data.QuadVertexBufferPtr->Color           = tintColor;
		s_Data.QuadVertexBufferPtr->TextureCoord    = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferPtr->TextureSlot     = textureSlot;
		s_Data.QuadVertexBufferPtr->TileFactor      = tileFactor;
		++s_Data.QuadVertexBufferPtr;

		s_Data.QuadIndexCount += 6;

		if (IsBatchFull())
			Flush();
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float& rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float& rotation, const glm::vec4& color)
	{
		s_Data.ColorTextureShader->SetFloat4("u_Color", color);
		s_Data.ColorTextureShader->SetFloat("u_TileFactor", 1.0f);
		//s_Data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.ColorTextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, const float& rotation, const Ref<Texture2D>& texture, const float& tileFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tileFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, const float& rotation, const Ref<Texture2D>& texture, const float& tileFactor, const glm::vec4& tintColor)
	{
		s_Data.ColorTextureShader->SetFloat4("u_Color", tintColor);
		s_Data.ColorTextureShader->SetFloat("u_TileFactor", tileFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.ColorTextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data.QuadVertexArray);
	}

}