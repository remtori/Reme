#include "RemePCH.h"
#include "Reme/Core/AssetManager.h"

namespace Reme
{
    static uint32_t GlobalAssetID = 1;

    uint32_t AssetManager::GenerateAssetID()
    {
        return GlobalAssetID++;
    }
}
