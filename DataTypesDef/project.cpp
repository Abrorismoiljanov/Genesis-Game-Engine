#include "project.h"
#include <filesystem>
#include <random>

project project::Clone() const{
    project copy;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    std::string tempName = "genesis_clone_" + std::to_string(dis(gen)) + ".json";

    std::string tempPath = (std::filesystem::temp_directory_path() / tempName).string();
    SaveToFile(tempPath);
    copy.LoadFromFile(tempPath);
    std::filesystem::remove(tempPath);
    
    return copy;
};
