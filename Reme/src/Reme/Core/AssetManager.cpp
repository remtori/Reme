#include "RemePCH.h"
#include "Reme/Core/AssetManager.h"

namespace Reme
{
    static uint32_t GlobalAssetID = 0;

    uint32_t AssetManager::GenerateAssetID()
    {
        return GlobalAssetID++;
    }
}
