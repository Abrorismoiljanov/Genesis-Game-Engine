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
            
            bool A_found = false;
            bool B_found = false;
 
            for (auto& s: Proj->SceneList) {
                if (s.ID == Proj->activeSceneID) {
                    for (auto& eID: s.EntityIDs) {
                        if (A.ID == eID) A_found = true;
                        if (B.ID == eID) B_found = true;
                    }
                    break;
                }
            }
            if (!(A_found && B_found)) {
                continue;
            }

            glm::vec2 posA = glm::vec2(A.transform->position.x, A.transform->position.y) +
                glm::vec2(A.collider->offset.x * A.transform->scale.x,
                          A.collider->offset.y * A.transform->scale.y);


            glm::vec2 posB = glm::vec2(B.transform->position.x, B.transform->position.y) +
                glm::vec2(B.collider->offset.x * B.transform->scale.x,
                           B.collider->offset.y * B.transform->scale.y);

            glm::vec2 halfA = glm::vec2(
                A.collider->halfSize.x * A.transform->scale.x,
                A.collider->halfSize.y * A.transform->scale.y
            );

            glm::vec2 halfB = glm::vec2(
                B.collider->halfSize.x * B.transform->scale.x,
                B.collider->halfSize.y * B.transform->scale.y
            );

            glm::vec2 delta = posB - posA;

            glm::vec2 intersect = glm::vec2(
                halfA.x + halfB.x - abs(delta.x),
                halfA.y + halfB.y - abs(delta.y)
            );


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



