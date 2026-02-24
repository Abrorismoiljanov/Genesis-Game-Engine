#pragma once
#include "string"
#include "vector"
#include "cstdint"

class entity{
public:
    std::string name;
    uint32_t ID = 0;
    std::vector<uint32_t> ComponentIDs; 

    void DrawInfoUI();


private:


};
