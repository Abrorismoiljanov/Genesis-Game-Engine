#pragma once
#include "imgui.h"
#include "memory"
#include "unordered_map"
#include "vector"
#include "Assets/Asset.h"
#include "Components/components.h"
#include "iostream"

class AssetManager{
public:
    AssetManager() = default;

    AssetHandle RegisterAsset( const std::shared_ptr<Asset>& asset);
    AssetHandle RegisterAssetWithHandle(const std::shared_ptr<Asset>& asset, AssetHandle forcedHandle);

    template<typename T>
    std::shared_ptr<T> Get(AssetHandle handle) const {
        auto it = m_HandleToIndex.find(handle);
        if (it == m_HandleToIndex.end()) return nullptr;
 
        uint32_t index = it->second;
        auto asset = m_Assets[index];

        std::shared_ptr<T> casted = std::dynamic_pointer_cast<T>(asset);
        if (!casted) {
            std::cerr << "AssetManager: Handle " << handle << " is not a " 
                << typeid(T).name() << "\n";
        }
        return casted;
    }
        

    void DeleteAsset(AssetHandle handle);
    
    AssetHandle GenerateHandle();
 //   void CleanupUnusedAssets(const std::vector<std::unique_ptr<Component>>& components);

    std::vector<std::shared_ptr<Asset>> m_Assets;
    std::unordered_map<AssetHandle, uint32_t> m_HandleToIndex;
    std::unordered_map<std::string, AssetHandle> m_PathRegistry;

    AssetHandle m_LastHandle = 1;
};
