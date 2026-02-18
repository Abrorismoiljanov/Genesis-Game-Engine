#include "AssetManager.h"
#include <filesystem>

AssetHandle AssetManager::GenerateHandle(){
    return m_LastHandle++;
};

AssetHandle AssetManager::RegisterAsset(const std::shared_ptr<Asset>& asset){
    AssetHandle handle = GenerateHandle();
    asset->Handle = handle;

    uint32_t index = (uint32_t)m_Assets.size();

    m_Assets.push_back(asset);
    m_HandleToIndex[handle] = index;



    if (!asset->Path.empty()) {
        m_PathRegistry[asset->Path] = handle;
    }
    return handle;
};

void AssetManager::CleanupUnusedAssets(const std::vector<std::unique_ptr<Component>>& components) {}
    

