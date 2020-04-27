#pragma once

namespace Reme
{    
    class Asset;

    class AssetManager
    {
    public:
        static uint32_t GenerateAssetID();
        static WeakRef<Asset> GetAsset(uint32_t id);

        template<class T, typename ... Args>
        static Ref<T> Create(Args&& ... args)
        {
            Ref<T> ptr = std::make_shared<T>(std::forward<Args>(args)...);
            PutAsset(ptr);
            return ptr;
        }

    private:
        static void PutAsset(const Ref<Asset>& asset);
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
