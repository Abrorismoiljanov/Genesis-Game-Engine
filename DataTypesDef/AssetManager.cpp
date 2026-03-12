#include "AssetManager.h"
#include <filesystem>

AssetHandle AssetManager::GenerateHandle(){
    return m_LastHandle++;
};

AssetHandle AssetManager::RegisterAsset(const std::shared_ptr<Asset>& asset) {
    AssetHandle handle = GenerateHandle();
    asset->Handle = handle;

    uint32_t index = static_cast<uint32_t>(m_Assets.size());
    m_Assets.push_back(asset);
    m_HandleToIndex[handle] = index;

    if (!asset->Path.empty()) {
        m_PathRegistry[asset->Path] = handle;
    }

    return handle;
}

AssetHandle AssetManager::RegisterAssetWithHandle(const std::shared_ptr<Asset>& asset, AssetHandle forcedHandle) {
    asset->Handle = forcedHandle;

    uint32_t index = static_cast<uint32_t>(m_Assets.size());
    m_Assets.push_back(asset);
    m_HandleToIndex[forcedHandle] = index;

    m_LastHandle = std::max(m_LastHandle, forcedHandle + 1);

    if (!asset->Path.empty()) {
        m_PathRegistry[asset->Path] = forcedHandle;
    }

    return forcedHandle;
}
void AssetManager::DeleteAsset(AssetHandle handle) {
    auto it = m_HandleToIndex.find(handle);
    if (it == m_HandleToIndex.end()) return;

    uint32_t index = it->second;

    // Remove from map
    m_HandleToIndex.erase(handle);

    // Remove from path registry if needed
    for(auto itPath = m_PathRegistry.begin(); itPath != m_PathRegistry.end(); ++itPath){
        if(itPath->second == handle){
            m_PathRegistry.erase(itPath);
            break;
        }
    }

    // Remove from vector
    m_Assets.erase(m_Assets.begin() + index);

    // Update indices of remaining assets
    for(uint32_t i = index; i < m_Assets.size(); ++i){
        m_HandleToIndex[m_Assets[i]->Handle] = i;
    }
}

// void AssetManager::CleanupUnusedAssets(const std::vector<std::unique_ptr<Component>>& components) {}
    

