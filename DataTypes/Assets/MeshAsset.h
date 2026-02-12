#include "unordered_map"
#include "string"

struct MeshData{
    unsigned int VAO, VBO, EBO;
    size_t IndexCount;
};
std::unordered_map<std::string, MeshData> MeshCache;
