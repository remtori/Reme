#pragma once

namespace Reme
{    
    class AssetManager
    {
    public:
        static uint32_t GenerateAssetID();
    };

    class Asset
    {
    public:
        template<class T>
        static bool Equals(T left, T right)
        {
            return left->GetAssetID() == right->GetAssetID();
        }
    public:
        inline uint32_t GetAssetID() const { return m_AssetID; }
    private:
        uint32_t m_AssetID = AssetManager::GenerateAssetID();
    };
}
