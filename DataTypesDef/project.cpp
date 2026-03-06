#include "project.h"

project project::Clone() const{
    project copy;
    SaveToFile("temp_proj.json");
    copy.LoadFromFile("temp_proj.json");
    
    return copy;
};
