#include "Runtime/include/CollisionSystem.h"
#include "DataTypes/entity.h"
#include "DataTypes/Components/CollisionComponent.h"

struct Body {
    TransformData* transform;
    CollisionComponent* collider;
    uint32_t ID;
};

void CollisionSystem::Update(float dt){
    std::vector<Body> bodies;
    for (auto& e: Proj->EntityList) {
        auto& t = e.transform;

        for (auto& cID: e.ComponentIDs) {
            auto c = Proj->GetComponentByID(cID);

            if (c->Getname() == "Collision") {
                auto col = static_cast<CollisionComponent*>(c);
                uint32_t id = e.ID;
                bodies.push_back({ &t, col, id});
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

 
            glm::vec2 delta = posB - posA; 
            
            glm::vec2 intersect = glm::vec2(halfA.x + halfB.x - abs(delta.x),
                                            halfA.y + halfB.y - abs(delta.y));

            bool overlapX = intersect.x > 0.0f;
            bool overlapY = intersect.y > 0.0f;
            if (!(overlapX && overlapY)) continue;
            
            if (A.collider->isTrigger || B.collider->isTrigger){
                if (overlapX && overlapY) {
                    Smanager->CallEvent(A.ID, "OnTriggerEnter", B.ID);
                    Smanager->CallEvent(B.ID, "OnTriggerEnter", A.ID);
                }
                continue;
            }

            if (intersect.x < intersect.y) {

                float dir = (delta.x > 0) ? -1.0f : 1.0f;
                    
                if (!A.collider->isStatic && B.collider->isStatic) {
                    A.transform->position.x += intersect.x * dir;
                } else if (A.collider->isStatic && !B.collider->isStatic) {
                    B.transform->position.x -= intersect.x * dir;
                } else if (!A.collider->isStatic && !B.collider->isStatic) {
                    A.transform->position.x += intersect.x * dir * 0.5f;
                    B.transform->position.x -= intersect.x * dir * 0.5f;
                }
            } else {
                float dir = (delta.y > 0) ? -1.0f : 1.0f;
                if (!A.collider->isStatic && B.collider->isStatic) {
                    A.transform->position.y += intersect.y * dir;
                } else if (A.collider->isStatic && !B.collider->isStatic) {
                    B.transform->position.y -= intersect.y * dir;
                } else if (!A.collider->isStatic && !B.collider->isStatic) {
                    A.transform->position.y += intersect.y * dir * 0.5f;
                    B.transform->position.y -= intersect.y * dir * 0.5f;
                }
            }
        }
    }
};



