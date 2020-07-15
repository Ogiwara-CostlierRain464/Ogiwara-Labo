#include "Contact.h"

using glm::length;
using glm::vec3;
using glm::mat3;
using glm::cross;
using glm::dot;
using glm::rotate;

namespace {
  constexpr float CONTACT_SAME_POINT = 0.01f;
  // 衝突点の閾値(法線方向)
  constexpr float CONTACT_THRESHOLD_NORMAL = 0.01f;
  // 衝突点の閾値(平面上)
  constexpr float CONTACT_THRESHOLD_TANGENT = 0.002f;
}

static inline float calcArea4Point(
  const vec3 &p0,
  const vec3 &p1,
  const vec3 &p2,
  const vec3 &p3
  ){
  float areaSqrA = length(cross(p0-p1, p2-p3));
  float areaSqrB = length(cross(p0-p2, p1-p3));
  float areaSqrC = length(cross(p0-p3, p1-p2));
  return std::max(std::max(areaSqrA, areaSqrB), areaSqrC);
}

int labo::physics::Contact::findNearestContactPoint(const glm::vec3 &newPointA, const glm::vec3 &newPointB, const glm::vec3 &newNormal) {
  int nearestIdx = -1;

  float minDiff = CONTACT_SAME_POINT;
  for(size_t i=0; i<numContacts;i++){
    float diffA = length(contactPoints[i].pointA - newPointA);
    float diffB = length(contactPoints[i].pointB - newPointB);
    if(diffA < minDiff && diffB < minDiff && dot(newNormal, contactPoints[i].normal) > 0.99f){
      minDiff = std::max(diffA, diffB);
      nearestIdx = i;
    }
  }

  return nearestIdx;
}

int labo::physics::Contact::sort4ContactPoints(const glm::vec3 &newPoint, float newDistance) {
  int maxPenetrationIndex = -1;
  float maxPenetration = newDistance;

  for(size_t i=0; i< numContacts; i++){
    if(contactPoints[i].distance < maxPenetration){
      maxPenetrationIndex = i;
      maxPenetration = contactPoints[i].distance;
    }
  }

  float res[4] = {0.f};

  vec3 newP(newPoint);
  vec3 p[] = {
    contactPoints[0].pointA,
    contactPoints[1].pointA,
    contactPoints[2].pointA,
    contactPoints[3].pointA
  };

  if(maxPenetrationIndex != 0){
    res[0] = calcArea4Point(newP, p[1], p[2], p[3]);
  }
  if(maxPenetrationIndex != 1){
    res[1] = calcArea4Point(newP, p[0], p[2], p[3]);
  }
  if(maxPenetrationIndex != 2){
    res[2] = calcArea4Point(newP, p[0], p[1], p[3]);
  }
  if(maxPenetrationIndex != 3){
    res[3] = calcArea4Point(newP, p[0], p[1], p[2]);
  }

  int maxIndex = 0;
  float maxVal = res[0];

  if(res[1] > maxVal){
    maxIndex = 1;
    maxVal = res[1];
  }
  if(res[2] > maxVal){
    maxIndex = 2;
    maxVal = res[2];
  }
  if(res[3] > maxVal){
    maxIndex = 3;
    maxVal = res[3];
  }

  return  maxIndex;
}

void labo::physics::Contact::reset() {
  numContacts = 0;
  for(int i=0; i < NUM_CONTACTS; i++){
    contactPoints[i].reset();
  }
}

void labo::physics::Contact::removeContactPoint(int i) {
  contactPoints[i] = contactPoints[numContacts-1];
  numContacts--;
}

void labo::physics::Contact::refresh(const glm::vec3 &pA, const glm::quat &qA, const glm::vec3 &pB, const glm::quat &qB) {
  for(int i=0; i<(int)numContacts; i++){
    vec3 normal = contactPoints[i].normal;
    vec3 cpA = pA + rotate(qA, contactPoints[i].pointA);
    vec3 cpB = pB + rotate(qB, contactPoints[i].pointB);

    float distance = dot(normal, cpA - cpB);
    if(distance > CONTACT_THRESHOLD_NORMAL){
      removeContactPoint(i);
      i--;
      continue;
    }
    contactPoints[i].distance = distance;

    cpA = cpA - contactPoints[i].distance * normal;
    float distanceAB = length(cpA - cpB);
    if(distanceAB > CONTACT_THRESHOLD_TANGENT){
      removeContactPoint(i);
      i--;
      continue;
    }
  }
}

void labo::physics::Contact::merge(const Contact &contact) {
  for(size_t i=0; i < contact.numContacts; i++){
    auto &cp = contactPoints[i];

    int id = findNearestContactPoint(cp.pointA, cp.pointB, cp.normal);

    if(id >= 0){
      if(std::abs(dot(cp.normal, contactPoints[id].normal)) > 0.99f){
        contactPoints[id].distance = cp.distance;
        contactPoints[id].pointA = cp.pointA;
        contactPoints[id].pointB = cp.pointB;
        contactPoints[id].normal = cp.normal;
      }else{
        contactPoints[id] = cp;
      }
    } else if (numContacts < NUM_CONTACTS){
      contactPoints[numContacts++] = cp;
    }else{
      id = sort4ContactPoints(cp.pointA, cp.distance);

      contactPoints[id] = cp;
    }
  }
}

void labo::physics::Contact::addContact(
  float penetrationDepth,
  const glm::vec3 &normal,
  const glm::vec3 &contactPointA,
  const glm::vec3 &contactPointB) {
  int id = findNearestContactPoint(contactPointA, contactPointB, normal);

  if(id < 0 && numContacts < NUM_CONTACTS){
    id = numContacts++;
    contactPoints[id].reset();
  } else if (id < 0){
    id = sort4ContactPoints(contactPointA, penetrationDepth);
    contactPoints[id].reset();
  }

  contactPoints[id].distance = penetrationDepth;
  contactPoints[id].pointA = contactPointA;
  contactPoints[id].pointB = contactPointB;
  contactPoints[id].normal = normal;
}
