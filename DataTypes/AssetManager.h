#pragma once
#include "imgui.h"
#include "memory"
#include "unordered_map"
#include "vector"
#include "Assets/Asset.h"
#include "components.h"

class AssetManager{
public:
    AssetManager() = default;

    AssetHandle RegisterAsset( const std::shared_ptr<Asset>& asset);

    template<typename T>
    std::shared_ptr<T> Get(AssetHandle handle) const{
        auto it = m_HandleToIndex.find(handle);
        if (it == m_HandleToIndex.end()) 
            return nullptr;


        uint32_t index = it->second;
        return std::static_pointer_cast<T>(m_Assets[index]);
    
    };

    AssetHandle RegisterAssetWithHandle(const std::shared_ptr<Asset>& asset,AssetHandle forcedHandle);
    void DeleteAsset(AssetHandle handle);
    
    AssetHandle GenerateHandle();
 //   void CleanupUnusedAssets(const std::vector<std::unique_ptr<Component>>& components);

    std::vector<std::shared_ptr<Asset>> m_Assets;
    std::unordered_map<AssetHandle, uint32_t> m_HandleToIndex;
    std::unordered_map<std::string, AssetHandle> m_PathRegistry;

    AssetHandle m_LastHandle = 1;
};
