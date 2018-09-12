#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include "SDL.h"

class Object
{
  public:
    Object();
    ~Object();
    void Update(unsigned int dt);
    void Render();
    
    glm::mat4 GetModel();
    
    // PA2 Keyboard Functionality
    void ToggleRotationDirection();
    void ToggleOrbitDirection();
    void TogglePauseRotation();
    void TogglePauseOrbit();
    void TogglePauseAll();
    float GetOrbitSpeed();
    float GetRotationSpeed();

  private:
    glm::mat4 model;
    glm::mat4 rotation;
    glm::vec3 rotationAxis;
    glm::mat4 translate;
    
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float orbitAngle;
    float angle;
    
    float rotationSpeed;
    float orbitSpeed;
    
    float rotationSpeedMultiplier;
    float orbitSpeedMultiplier;
};

#endif /* OBJECT_H */
