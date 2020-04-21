#include "RemePCH.h"
#include "Reme/Core/AssetManager.h"

namespace Reme
{
    static uint32_t GlobalAssetID = 1;
    std::unordered_map<uint32_t, WeakRef<Asset>> AssetMap;
    WeakRef<Asset> NULL_ASSET;

    uint32_t AssetManager::GenerateAssetID()
    {
        return GlobalAssetID++;
    }

    WeakRef<Asset> AssetManager::GetAsset(uint32_t id)
    {
        auto it = AssetMap.find(id);
        if (it == AssetMap.end())
            return NULL_ASSET;

        return it->second;
    }

    void AssetManager::PutAsset(const Ref<Asset>& asset)
    {
        AssetMap[asset->GetAssetID()] = asset;
    }
}
