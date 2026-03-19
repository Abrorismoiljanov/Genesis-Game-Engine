#include "Runtime/include/CollisionSystem.h"
#include "DataTypes/entity.h"
#include "DataTypes/Components/CollisionComponent.h"

struct Body {
    TransformData* transform;
    CollisionComponent* collider;
};

void CollisionSystem::Update(float dt){
    std::vector<Body> bodies;
    for (auto& e: Proj->EntityList) {
        auto& t = e.transform;


        for (auto& cID: e.ComponentIDs) {
            auto c = Proj->GetComponentByID(cID);

            if (c->Getname() == "Collision") {
                auto col = static_cast<CollisionComponent*>(c);
                bodies.push_back({ &t, col });
            }
        }
    }
     for (size_t i = 0; i < bodies.size(); i++) {
          for (size_t j = i + 1; j < bodies.size(); j++) {
    
            auto& A = bodies[i];
            auto& B = bodies[j];
 
            glm::vec2 posA = A.transform->position + A.collider->offset;
            glm::vec2 posB = B.transform->position + B.collider->offset;

            glm::vec2 halfA = A.collider->halfSize;
            glm::vec2 halfB = B.collider->halfSize;

            bool overlapX = abs(posA.x - posB.x) <= (halfA.x + halfB.x);
            bool overlapY = abs(posA.y - posB.y) <= (halfA.y + halfB.y);
                
            if (overlapX && overlapY) {
                std::stringstream ss;
                ss << "Checking A (" << posA.x << "," << posA.y << ") vs B (" << posB.x << "," << posB.y << ")";
                log->Info(LogSystem::Physics, ss.str());
            }
        }
    }
};



