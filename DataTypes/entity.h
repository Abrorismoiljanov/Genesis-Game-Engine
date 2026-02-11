#pragma once
#include "string"
#include "vector"
#include "cstdint"

class entity{
public:
    std::string name;
    uint32_t ID = GenerateID();
    std::vector<uint32_t> ComponentIDs; 

    void DrawInfoUI();


private:

    uint32_t GenerateID() {
        static uint32_t currentID = 0;
        return currentID++;
    }

};
