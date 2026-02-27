#pragma once
#include "string"
#include "vector"
#include "cstdint"


class scene{
 public:
    std::string Scenename;
    uint32_t ID = 0;
    std::vector<uint32_t> EntityIDs;

    scene(){};

};


