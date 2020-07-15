#ifndef LABO_SIMULATION_H
#define LABO_SIMULATION_H

#include <vector>
#include "../minecraft/entity/item_entity.h"

namespace labo::physics{

void physicsSimulate();
void applySimulationResult(std::vector<std::shared_ptr<minecraft::Entity>> &entities);
void addCube(glm::vec3 &position, bool static_ = false);

}

#endif //LABO_SIMULATION_H
