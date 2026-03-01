#pragma once
#include "cstdint"

struct SelectedEntity{

    uint32_t EntityID = UINT32_MAX;

    bool hasEntity() const { return EntityID != UINT32_MAX;};

    void ClearEntity(){
        EntityID = UINT32_MAX;
    }
};

struct SelectedScene{

    uint32_t SceneID = UINT32_MAX;

    bool hasEntity() const { return SceneID != UINT32_MAX;};

    void ClearEntity(){
        SceneID = UINT32_MAX;
    }
};
