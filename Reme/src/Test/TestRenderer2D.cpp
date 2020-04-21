#include "RemePCH.h"

#ifdef TEST
#include "Catch2/catch.hpp"

#include "Reme.h"
#include "Reme/Renderer/Renderer.h"
#include "Impl/Test/Test_Buffers.h"

using namespace Reme;


const std::vector<float>& GetVerticies()
{
    auto drawCall = RenderCommand::GetDrawData();
    VertexArray* vao = static_cast<VertexArray*>(AssetManager::GetAsset(drawCall.bindedVAO).lock().get());
    Test_VertexBuffer* VBO = static_cast<Test_VertexBuffer*>(vao->GetVertexBuffers()[0].get());
    return VBO->GetData();
}

TEST_CASE("Renderer2D can render", "[renderer2d]")
{
    Renderer::Init();
    Ref<OrthographicCamera> cam = CreateRef<OrthographicCamera>(0, 100, 0, 100);        

    SECTION("drawing a simple 10x10 rectangle")
    {
        Renderer2D::Begin(cam);
        Renderer2D::FillRect(Color::Red, 0, 0, 10, 10);
        Renderer2D::End();

        const std::vector<float>& verticies = GetVerticies();
    }
}
#endif // TEST