#include <cstdlib>
#include <chrono>
#include <iostream>
#include "simulation.h"
#include "pipeline/Allocator.h"
#include "../math/glm.h"
#include "element/State.h"
#include "element/RigidBoby.h"
#include "element/Collidable.h"
#include "element/Pair.h"
#include "pipeline/Integrate.h"
#include "pipeline/Broadphase.h"
#include "pipeline/CollisionDetection.h"
#include "pipeline/ConstraintSolver.h"
#include "base.h"

using glm::vec3;
using glm::quat;
using glm::mat3;

namespace {
  constexpr int maxRigidBodies = 500;
  constexpr int maxJoints = 100;
  constexpr int maxPairs = 5000;
  constexpr float timeStep = 0.016f;
  constexpr float contactBias = 0.1f;
  constexpr float contactSlop = 0.001f;
  constexpr int iteration = 10;
  constexpr vec3 gravity(0.f, -9.8f, 0.f);
}

namespace labo::physics {

State states[maxRigidBodies];
RigidBody bodies[maxRigidBodies];
Collidable collidables[maxRigidBodies];
uint32_t numRigidBodies = 0;

unsigned int pairSwap;
uint32_t numPairs[2];
Pair pairs[2][maxPairs];

class DefaultAllocator : public Allocator {
public:
  void *allocate(size_t bytes) override {
    return malloc(bytes);
  }

  void deallocate(void *p) override {
    free(p);
  }
} allocator;

void physicsSimulate() {
  pairSwap = 1 - pairSwap;

  for (size_t i = 0; i < numRigidBodies; i++) {
    vec3 externalForce = gravity * bodies[i].mass;
    vec3 externalTorque(0.f);
    applyExternalForce(states[i], bodies[i], externalForce, externalTorque, timeStep);
  }

  broadPhase(
    states, collidables, numRigidBodies,
    pairs[1 - pairSwap], numPairs[1 - pairSwap],
    pairs[pairSwap], numPairs[pairSwap],
    maxPairs, &allocator
  );

  detectionCollision(
    states, collidables, numRigidBodies,
    pairs[pairSwap], numPairs[pairSwap]
  );


  solveConstrains(
    states, bodies, numRigidBodies,
    pairs[pairSwap], numPairs[pairSwap],
    iteration, contactBias, contactSlop, timeStep, &allocator
  );


  integrate(states, numRigidBodies, timeStep);
}

void applySimulationResult(std::vector<std::shared_ptr<minecraft::Entity>> &entities) {
  if (numRigidBodies != entities.size()) {
    return;
  }

  for (size_t i = 0; i < numRigidBodies; i++) {

    auto &target = entities.at(i);

    float size = 0.5;
    target->setPosition(states[i].position /*+ vec3(size, size, size)*/ );
//    target->setRotation(glm::eulerAngles(states[i].orientation) * 3.14159f / 180.f);
    target->setRotation(glm::eulerAngles(states[i].orientation));
  }
}

static inline
glm::mat3 calcInertiaBox(const glm::vec3 &halfExtent, float mass) {
  glm::vec3 sqrSz = halfExtent * 2.0f;
  sqrSz = mulPerElem(sqrSz, sqrSz);
  glm::mat3 inertia = glm::mat3(1);
  inertia[0][0] = (mass * (sqrSz[1] + sqrSz[2])) / 12.0f;
  inertia[1][1] = (mass * (sqrSz[0] + sqrSz[2])) / 12.0f;
  inertia[2][2] = (mass * (sqrSz[0] + sqrSz[1])) / 12.0f;
  return inertia;
}

const int box_numVertices = 8;
const int box_numIndices = 36;
const float box_vertices[] = {
  -1.000000, -1.000000, 1.000000, 1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000, 1.000000, 1.000000,
  1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000, -1.000000, -1.000000, -1.000000, -1.000000, 1.000000,
  -1.000000, -1.000000
};
const unsigned short box_indices[] = {
  0, 1, 2, 2, 1, 3, 2, 3, 4, 4, 3, 5, 4, 5, 6, 6, 5, 7, 6, 7, 0, 0, 7, 1, 1, 7, 3, 3, 7, 5, 6, 0, 4, 4, 0, 2
};

void addCube2(glm::vec3 &pos, bool static_) {
  float size = 0.25;
  glm::vec3 scale(0.25f, 0.25f, 0.25f);

  int id = numRigidBodies++;

  states[id].reset();
  states[id].position = pos;
  states[id].motionType = static_ ? Static : Active;

  bodies[id].reset();
  bodies[id].mass = 0.3f;

  float diag = (1.f / 12) * (2 * powf(size, 2));

//  bodies[id].inertia = calcInertiaBox(scale, 0.3);
  bodies[id].inertia = mat3(
    vec3(diag, 0, 0),
    vec3(0, diag, 0),
    vec3(0, 0, diag)
  );

  collidables[id].reset();

  Shape shape{};
  shape.reset();

  createConvexMesh(&shape.geometry, box_vertices, box_numVertices, box_indices, box_numIndices, scale);

  collidables[id].addShape(shape);
  collidables[id].finish();
}

void addStaticCube(glm::vec3 &pos){
  addCube(pos, true, 0.5);
}

void addCube(glm::vec3 &position, bool static_, float size) {
  State state{
    position /*- vec3(size, size, size)*/,
    glm::quat(),
    vec3(),
    vec3(),
    static_ ? Static : Active
  };

  float diag = (1.f / 12) * (2 * powf(size, 2));

  RigidBody body{
    mat3(
      vec3(diag, 0, 0),
      vec3(0, diag, 0),
      vec3(0, 0, diag)
    ),
    1,
    0.2,
    0.6
  };

  Collidable collidable{
    1,
    {
      Shape{
        ConvexMesh{
          8,
          12,
          18,
          // vertices
          {
            vec3(0, size, 0),
            vec3(size, size, 0),
            vec3(0, size, size),
            vec3(size, size, size),
            vec3(0, 0, 0),

            vec3(size, 0, 0),
            vec3(0, 0, size),
            vec3(size, 0, size),
          },
          // edges
          {
            Edge{Convex, {0, 1}, {1, 4}},
            Edge{Convex, {0, 2}, {3, 4}},
            Edge{Convex, {1, 3}, {5, 6}},
            Edge{Convex, {2, 3}, {5, 10}},
            Edge{Convex, {0, 4}, {0, 2}},

            Edge{Convex, {1, 5}, {1, 6}},
            Edge{Convex, {2, 6}, {3, 10}},
            Edge{Convex, {3, 7}, {7, 11}},
            Edge{Convex, {4, 5}, {0, 8}},
            Edge{Convex, {4, 6}, {2, 9}},

            Edge{Convex, {5, 7}, {7, 8}},
            Edge{Convex, {6, 7}, {9, 11}},
            Edge{Flat, {0, 5}, {0, 1}},
            Edge{Flat, {0, 6}, {2, 3}},
            Edge{Flat, {1, 2}, {4, 5}},

            Edge{Flat, {3, 5}, {6, 7}},
            Edge{Flat, {4, 7}, {8, 9}},
            Edge{Flat, {3, 6}, {10, 11}},
          },
          // facets
          {
            Facet{{0, 5, 4}, {4, 8, 12}, vec3(0, 0, -1)},
            Facet{{0, 1, 5}, {0, 5, 12}, vec3(0, 0, -1)},
            Facet{{0, 4, 6}, {4, 9, 13}, vec3(-1, 0, 0)},
            Facet{{0, 6, 2}, {1, 6, 13}, vec3(-1, 0, 0)},
            Facet{{0, 2, 1}, {0, 1, 14}, vec3(0, 1, 0)},

            Facet{{1, 2, 3}, {2, 3, 14}, vec3(0, 1, 0)},
            Facet{{1, 3, 5}, {2, 5, 15}, vec3(1, 0, 0)},
            Facet{{3, 7, 5}, {7, 10, 15}, vec3(1, 0, 0)},
            Facet{{4, 5, 7}, {8, 10, 16}, vec3(0, -1, 0)},
            Facet{{4, 7, 6}, {9, 11, 16}, vec3(0, -1, 0)},

            Facet{{2, 6, 3}, {3, 6, 17}, vec3(0, 0, 1)},
            Facet{{3, 6, 7}, {7, 11, 17}, vec3(0, 0, 1)}
          }
        }
      } //Shape
    },
    vec3(0,0,0),
    vec3(size / 2, size / 2, size / 2)
  };

  states[numRigidBodies] = state;
  bodies[numRigidBodies] = body;
  collidables[numRigidBodies] = collidable;

  numRigidBodies++;
}

}
