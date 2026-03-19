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
            
            glm::vec2 delta = posB - posA; 
            glm::vec2 intersect = glm::vec2(halfA.x + halfB.x - abs(delta.x),
                                halfA.y + halfB.y - abs(delta.y)); 

        for (size_t i = 0; i < bodies.size(); i++) {
        for (size_t j = i + 1; j < bodies.size(); j++) {

            auto& A = bodies[i];
            auto& B = bodies[j];

            // Skip triggers for now
            if (A.collider->isTrigger || B.collider->isTrigger)
                continue;

            glm::vec2 posA = glm::vec2(A.transform->position) + glm::vec2(A.collider->offset);
            glm::vec2 posB = glm::vec2(B.transform->position) + glm::vec2(B.collider->offset);

            glm::vec2 halfA = glm::vec2(A.collider->halfSize);
            glm::vec2 halfB = glm::vec2(B.collider->halfSize);

            glm::vec2 delta = posB - posA;
            glm::vec2 intersect = glm::vec2(halfA.x + halfB.x - abs(delta.x),
                                            halfA.y + halfB.y - abs(delta.y));

            bool overlapX = intersect.x > 0.0f;
            bool overlapY = intersect.y > 0.0f;

                
                    if (overlapX && overlapY) {
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
            }
        }
    }
};



