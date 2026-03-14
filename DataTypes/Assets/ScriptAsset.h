#pragma once
#include "Asset.h"


class ScriptAsset: public Asset{    
public:
    AssetHandle Handle = INVALID_ASSET;
    AssetType Type  = AssetType::Script;

    std::string Path = "";
};
