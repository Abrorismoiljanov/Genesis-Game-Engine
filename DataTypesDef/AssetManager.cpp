#include "AssetManager.h"
#include "MeshComponent.h"
#include "MeshLoader.h"

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

void AssetManager::CleanupUnusedAssets(const std::vector<std::unique_ptr<Component>>& components) {
    std::unordered_set<AssetHandle> usedHandles;

    for (auto& comp : components) {
        if (auto* mesh = dynamic_cast<MeshComponent*>(comp.get())) {
            usedHandles.insert(mesh->HandleMesh);
        }
    }

    for (auto it = m_Assets.begin(); it != m_Assets.end(); ) {
        if (usedHandles.find((*it)->Handle) == usedHandles.end()) {
            m_PathRegistry.erase((*it)->Path);
            m_HandleToIndex.erase((*it)->Handle);
            it = m_Assets.erase(it); // this will free memory if no other shared_ptr exists
        } else {
            ++it;
        }
    }
}


void AssetManager::Update(const std::vector<std::unique_ptr<Component>>& components){
    for (auto& compPtr : components) {
        auto* meshComp = dynamic_cast<MeshComponent*>(compPtr.get());
        if (!meshComp) continue;
        if (!meshComp->NeedsLoad()) continue;

        std::shared_ptr<MeshAsset> newAsset = MeshLoader().Load(meshComp->MeshPath.c_str());
        if (!newAsset) continue;

        AssetHandle handle = RegisterAsset(newAsset);
        meshComp->HandleMesh = handle;
        meshComp->MarkLoaded();

        std::cout << "Model Loaded: " << meshComp->MeshPath << "\n";
    }

};
