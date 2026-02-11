#pragma once

struct SelectedEntity{

    uint32_t EntityID = UINT32_MAX;

    bool hasEntity() const { return EntityID != UINT32_MAX;};

    void ClearEntity(){
        EntityID = UINT32_MAX;
    }
};
