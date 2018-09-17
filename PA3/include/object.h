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
    
    void UpdateMoonData(unsigned int dt,
                        std::vector<Object> &objectsTable,
                        bool parentOrigin = true);
    
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
    
    // PA3 Moon Handler Functions
    void SetOrbitRadius(float radius);
    void SetObjectOrigin(const glm::mat4 &newOrigin);
    void AddObjectChild(int worldMoonID);
    int GetMoonID(int localMoonID);
    int GetNumberOfMoons();
    void SetMoonStatus(bool flag);
    bool IsObjectMoon();
    void SetScale(const glm::vec3 &scale);
    glm::vec3 GetScale();
    bool IsPaused();
    
    void UpdateOrbitSpeed(float orbSpeed);
    void UpdateRotationSpeed(float rotSpeed);

  private:
    glm::mat4 origin;
    glm::vec3 myScale;
    glm::mat4 model;
    glm::mat4 rotation;
    glm::vec3 rotationAxis;
    glm::mat4 translate;
    
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    GLuint VB;
    GLuint IB;

    float orbitAngle;
    float orbitRadius;
    float angle;
    
    float rotationSpeed;
    float orbitSpeed;
    
    float rotationSpeedMultiplier;
    float orbitSpeedMultiplier;
    
    // Vector of childs that can be contained within the parent
    std::vector<int> moonVector;
    
    bool isMoon;
};

#endif /* OBJECT_H */
