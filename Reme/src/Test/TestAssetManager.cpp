#include "RemePCH.h"

#include "Reme.h"
#include "Catch2/catch.hpp"

using namespace Reme;

class A : public Asset
{
public:
    A(uint32_t v) : Value(v) {}
    uint32_t Value;
};

TEST_CASE("AssetManager can manage asset", "[asset]")
{
    SECTION("hold and get weak_ptr to object")
    {
        auto a = AssetManager::Create<A>(322);
        auto weak_a = AssetManager::GetAsset(a->GetAssetID());
        REQUIRE(!weak_a.expired());

        auto strong_a = weak_a.lock();
        REQUIRE(strong_a != nullptr);

        REQUIRE(static_cast<A*>(strong_a.get())->Value == a->Value);
    }

    SECTION("turn to nullptr when host object is unreferenced")
    {
        uint32_t id;

        {
            auto a = AssetManager::Create<A>(322);
            id = a->GetAssetID();

            auto weak_a = AssetManager::GetAsset(id);
            REQUIRE(!weak_a.expired());
            REQUIRE(weak_a.lock() != nullptr);
            REQUIRE(static_cast<A*>(weak_a.lock().get())->Value == a->Value);
        }

        auto weak_a = AssetManager::GetAsset(id);
        REQUIRE(weak_a.expired());

        auto strong_a = weak_a.lock();
        REQUIRE(strong_a == nullptr);
    }
}
