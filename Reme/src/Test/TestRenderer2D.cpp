#include "RemePCH.h"

#ifdef TEST
#include "Catch2/catch.hpp"

#include "Reme.h"
#include "Reme/Renderer/Renderer.h"

#include "Impl/Test/Test_Buffers.h"
#include "Impl/Test/Test_Texture.h"

using namespace Reme;


const Renderer2D::Vertex* GetVerticies()
{
	auto* vbo = static_cast<Test_VertexBuffer*>(AssetManager::GetAsset(Test_VertexBuffer::BindedVBO).lock().get());
	return (const Renderer2D::Vertex*) vbo->GetData().data();
}

SCENARIO("Renderer2D can render", "[renderer2d]")
{
	Renderer::Init();
	auto cam = CreateRef<OrthographicCamera>(0, 100, 0, 100);
	auto texture = Texture::Create(4, 4);
	Color c[] = {
		Color::Red, Color::Red   , Color::Red   , Color::Red,
		Color::Red, Color::Yellow, Color::Yellow, Color::Red,
		Color::Red, Color::Yellow, Color::Yellow, Color::Red,
		Color::Red, Color::Red   , Color::Red   , Color::Red,
	};
	texture->SetData(c);

	GIVEN("A Initalized Renderer2D with default state")
	{		
		Test_Texture::BindedTexture = 0;
		Test_VertexBuffer::BindedVBO = 0;

		WHEN("drawing a simple 10x10 rectangle")
		{
			Renderer2D::Begin(cam);
			Renderer2D::FillRect(Color::Red, 0, 0, 10, 10);
			Renderer2D::End();

			const Renderer2D::Vertex* verticies = GetVerticies();
			THEN("all the verticies should be correct")
			{
				REQUIRE(verticies[0].Position == glm::vec2( 0,  0));
				REQUIRE(verticies[1].Position == glm::vec2(10,  0));
				REQUIRE(verticies[2].Position == glm::vec2( 0, 10));
				REQUIRE(verticies[3].Position == glm::vec2(10, 10));				
			}

			THEN("the tint color should be Red")
			{
				REQUIRE(verticies[0].Color == glm::vec4(1, 0, 0, 1));
				REQUIRE(verticies[1].Color == glm::vec4(1, 0, 0, 1));
				REQUIRE(verticies[2].Color == glm::vec4(1, 0, 0, 1));
				REQUIRE(verticies[3].Color == glm::vec4(1, 0, 0, 1));
			}

			THEN("the white texture should be bind")
			{
				REQUIRE(static_cast<Test_Texture*>(Texture::White.get())->IsBinded());
			}
		}

		WHEN("drawing a full texture")
		{
			Renderer2D::Begin(cam);
			Renderer2D::DrawTexture(texture, 0, 0);
			Renderer2D::End();

			const Renderer2D::Vertex* verticies = GetVerticies();
			THEN("all the vertex position should be correct")
			{
				REQUIRE(verticies[0].Position == glm::vec2(0, 0));
				REQUIRE(verticies[1].Position == glm::vec2(texture->GetWidth(), 0));
				REQUIRE(verticies[2].Position == glm::vec2(0, texture->GetHeight()));
				REQUIRE(verticies[3].Position == glm::vec2(texture->GetWidth(), texture->GetHeight()));
			}

			THEN("all the UV should be correct")
			{
				REQUIRE(verticies[0].UV == glm::vec2(0, 0));
				REQUIRE(verticies[1].UV == glm::vec2(1, 0));
				REQUIRE(verticies[2].UV == glm::vec2(0, 1));
				REQUIRE(verticies[3].UV == glm::vec2(1, 1));
			}

			THEN("the correct texture should be binded")
			{
				REQUIRE(static_cast<Test_Texture*>(texture.get())->IsBinded());
			}

			THEN("the tint color should be default White")
			{
				REQUIRE(verticies[0].Color == glm::vec4(1, 1, 1, 1));
				REQUIRE(verticies[1].Color == glm::vec4(1, 1, 1, 1));
				REQUIRE(verticies[2].Color == glm::vec4(1, 1, 1, 1));
				REQUIRE(verticies[3].Color == glm::vec4(1, 1, 1, 1));
			}
		}

		WHEN("drawing a down-scaled texture")
		{
			Renderer2D::Begin(cam);
			Renderer2D::DrawTexture(texture, 0, 0, 10, 10);
			Renderer2D::End();

			const Renderer2D::Vertex* verticies = GetVerticies();
			THEN("all the vertex position should be correct")
			{
				REQUIRE(verticies[0].Position == glm::vec2( 0,  0));
				REQUIRE(verticies[1].Position == glm::vec2(10,  0));
				REQUIRE(verticies[2].Position == glm::vec2( 0, 10));
				REQUIRE(verticies[3].Position == glm::vec2(10, 10));
			}

			THEN("all the UV should be correct")
			{
				REQUIRE(verticies[0].UV == glm::vec2(0, 0));
				REQUIRE(verticies[1].UV == glm::vec2(1, 0));
				REQUIRE(verticies[2].UV == glm::vec2(0, 1));
				REQUIRE(verticies[3].UV == glm::vec2(1, 1));
			}

			THEN("the correct texture should be binded")
			{
				REQUIRE(static_cast<Test_Texture*>(texture.get())->IsBinded());
			}

			THEN("the tint color should be default White")
			{
				REQUIRE(verticies[0].Color == glm::vec4(1, 1, 1, 1));
				REQUIRE(verticies[1].Color == glm::vec4(1, 1, 1, 1));
				REQUIRE(verticies[2].Color == glm::vec4(1, 1, 1, 1));
				REQUIRE(verticies[3].Color == glm::vec4(1, 1, 1, 1));
			}
		}

		WHEN("drawing a partial texture")
		{
			auto tW = texture->GetWidth();
			auto tH = texture->GetHeight();

			Renderer2D::Begin(cam);
			Renderer2D::DrawPartialTexture(texture, tW / 2, tH / 2, tW / 2, tH / 2, 0, 0, 10, 10);
			Renderer2D::End();

			const Renderer2D::Vertex* verticies = GetVerticies();
			THEN("all the vertex position should be correct")
			{
				REQUIRE(verticies[0].Position == glm::vec2(0, 0));
				REQUIRE(verticies[1].Position == glm::vec2(10, 0));
				REQUIRE(verticies[2].Position == glm::vec2(0, 10));
				REQUIRE(verticies[3].Position == glm::vec2(10, 10));
			}

			THEN("all the UV should be correct")
			{
				REQUIRE(verticies[0].UV == glm::vec2(0.5, 0.5));
				REQUIRE(verticies[1].UV == glm::vec2(1.0, 0.5));
				REQUIRE(verticies[2].UV == glm::vec2(0.5, 1.0));
				REQUIRE(verticies[3].UV == glm::vec2(1.0, 1.0));
			}

			THEN("the correct texture should be binded")
			{
				REQUIRE(static_cast<Test_Texture*>(texture.get())->IsBinded());
			}

			THEN("the tint color should be default White")
			{
				REQUIRE(verticies[0].Color == glm::vec4(1, 1, 1, 1));
				REQUIRE(verticies[1].Color == glm::vec4(1, 1, 1, 1));
				REQUIRE(verticies[2].Color == glm::vec4(1, 1, 1, 1));
				REQUIRE(verticies[3].Color == glm::vec4(1, 1, 1, 1));
			}
		}	

		WHEN("drawing a partial tinted texture")
		{
			auto tW = texture->GetWidth();
			auto tH = texture->GetHeight();

			Renderer2D::Begin(cam);
			Renderer2D::DrawPartialTexture(texture, tW / 2, tH / 2, tW / 2, tH / 2, 0, 0, 10, 10, Color::Blue);
			Renderer2D::End();

			const Renderer2D::Vertex* verticies = GetVerticies();
			THEN("all the vertex position should be correct")
			{
				REQUIRE(verticies[0].Position == glm::vec2(0, 0));
				REQUIRE(verticies[1].Position == glm::vec2(10, 0));
				REQUIRE(verticies[2].Position == glm::vec2(0, 10));
				REQUIRE(verticies[3].Position == glm::vec2(10, 10));
			}

			THEN("all the UV should be correct")
			{
				REQUIRE(verticies[0].UV == glm::vec2(0.5, 0.5));
				REQUIRE(verticies[1].UV == glm::vec2(1.0, 0.5));
				REQUIRE(verticies[2].UV == glm::vec2(0.5, 1.0));
				REQUIRE(verticies[3].UV == glm::vec2(1.0, 1.0));
			}

			THEN("the correct texture should be binded")
			{
				REQUIRE(static_cast<Test_Texture*>(texture.get())->IsBinded());
			}

			THEN("the tint color should be default White")
			{
				REQUIRE(verticies[0].Color == glm::vec4(0, 0, 1, 1));
				REQUIRE(verticies[1].Color == glm::vec4(0, 0, 1, 1));
				REQUIRE(verticies[2].Color == glm::vec4(0, 0, 1, 1));
				REQUIRE(verticies[3].Color == glm::vec4(0, 0, 1, 1));
			}
		}

		WHEN("using translate")
		{
			Renderer2D::Begin(cam);
			Renderer2D::PushState();
			Renderer2D::Translate(50, 50);
			Renderer2D::FillRect(Color::Green, 0, 0, 10, 10);
			Renderer2D::PopState();
			Renderer2D::End();

		}
	}
}
#endif // TEST