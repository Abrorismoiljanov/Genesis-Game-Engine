#pragma once
#include "string"
#include "vector"
#include "cstdint"


class scene{
 public:
    std::string Scenename;
    uint32_t ID = 0;
    std::vector<uint32_t> EntityIDs;

    scene(){
        GenerateSceneID();
    };

    uint32_t GenerateSceneID() {
        static uint32_t nextSceneID = 1;
        return ++nextSceneID;
    }
};


