#include "object.h"

Object::Object()
{  
    /*
     # Blender File for a Cube
     o Cube
     v 1.000000 -1.000000 -1.000000
     v 1.000000 -1.000000 1.000000
     v -1.000000 -1.000000 1.000000
     v -1.000000 -1.000000 -1.000000
     v 1.000000 1.000000 -0.999999
     v 0.999999 1.000000 1.000001
     v -1.000000 1.000000 1.000000
     v -1.000000 1.000000 -1.000000
     s off
     f 2 3 4
     f 8 7 6
     f 1 5 6
     f 2 6 7
     f 7 8 4
     f 1 4 8
     f 1 2 4
     f 5 8 6
     f 2 1 6
     f 3 2 7
     f 3 7 4
     f 5 1 8
     */
    
    Vertices = {
        {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 0.0f}},
        {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}},
        {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}},
        {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}},
        {{-1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}}
    };
    
    Indices = {
        2, 3, 4,
        8, 7, 6,
        1, 5, 6,
        2, 6, 7,
        7, 8, 4,
        1, 4, 8,
        1, 2, 4,
        5, 8, 6,
        2, 1, 6,
        3, 2, 7,
        3, 7, 4,
        5, 1, 8
    };
    
    // The index works at a 0th index
    for(unsigned int i = 0; i < Indices.size(); i++)
    {
        Indices[i] = Indices[i] - 1;
    }
    
    angle = 0.0f;
    orbitAngle = 0.0f;
    rotationSpeed = 1.0f;
    orbitSpeed = 1.0f;
    rotationSpeedMultiplier = 1.0f;
    orbitSpeedMultiplier = -1.0f;
    
    // Adding reference to parent object (PA3)
    origin = glm::mat4(1.0);
    isMoon = false;
    myScale = glm::vec3(1.0f, 1.0f, 1.0f);
    
    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::~Object()
{
    Vertices.clear();
    Indices.clear();
}

void Object::Update(unsigned int dt)
{
    // Defined new variables rotation, translate, and rotationAxis
    angle += rotationSpeedMultiplier * rotationSpeed * dt * M_PI/1000;
    orbitAngle += orbitSpeedMultiplier * orbitSpeed * dt * M_PI/8500;
    rotation = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    rotationAxis = glm::vec3(0.0, 1.0, 0.0);
    
    // The cube will rotate at delta time speed on the y axis while spinning at delta time
    // and translating it's position by a 7 float offset from the origin axis
    model = glm::translate(translate,
                           glm::vec3(7.0f * cos(orbitAngle),
                                     0.0f,
                                     7.0f * sin(orbitAngle)))
                           * glm::rotate(rotation, (angle), rotationAxis) * glm::scale(myScale);
    
}

void Object::UpdateMoonData(unsigned int dt,
                    std::vector<Object> &objectsTable,
                    bool parentOrigin)
{
    int index, worldIndex;
    
    for(index = 0; index < moonVector.size(); index++)
    {
        worldIndex = GetMoonID(index);
        
        if((worldIndex >= 0) && (worldIndex < objectsTable.size()))
        {
            if(parentOrigin)
            {
                objectsTable[worldIndex].SetObjectOrigin(model);
            }
            
            objectsTable[worldIndex].Update(dt);
            
            // Call for n amount of moons to set
            objectsTable[worldIndex].UpdateMoonData(dt, objectsTable, parentOrigin);
        }
    }
}

glm::mat4 Object::GetModel()
{
    return model;
}

void Object::Render()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,color));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void Object::ToggleRotationDirection()
{
    if(rotationSpeedMultiplier == 0.0)
    {
        rotationSpeedMultiplier = 1.0;
    }
    
    rotationSpeed *= -1.0;
}

void Object::ToggleOrbitDirection()
{
    if(orbitSpeedMultiplier == 0.0)
    {
        orbitSpeedMultiplier = -1.0;
    }
    
    orbitSpeed *= -1.0;
}

void Object::TogglePauseRotation()
{
    if(rotationSpeedMultiplier == 0.0)
    {
        rotationSpeedMultiplier = 1.0;
    }
    
    else
    {
        rotationSpeedMultiplier = 0.0;
    }
}

void Object::TogglePauseOrbit()
{
    if(orbitSpeedMultiplier == 0.0)
    {
        orbitSpeedMultiplier = -1.0;
    }
    
    else
    {
        orbitSpeedMultiplier = 0.0;
    }
}

void Object::TogglePauseAll()
{
    if((rotationSpeedMultiplier == 0.0) && (orbitSpeedMultiplier == 0.0))
    {
        rotationSpeedMultiplier = 1.0;
        orbitSpeedMultiplier = 1.0;
    }
    
    else
    {
        rotationSpeedMultiplier = 0.0;
        orbitSpeedMultiplier = 0.0;
    }
}

float Object::GetOrbitSpeed()
{
    return orbitSpeed;
}

float Object::GetRotationSpeed()
{
    return rotationSpeed;
}

void Object::SetOrbitRadius(float radius)
{
    orbitRadius = radius;
}

void Object::SetObjectOrigin(const glm::mat4 &newOrigin)
{
    origin = newOrigin;
}

void Object::AddObjectChild(int worldMoonID)
{
    moonVector.push_back(worldMoonID);
}

int Object::GetMoonID(int localMoonID)
{
    if((localMoonID >= 0) && (localMoonID < moonVector.size()))
    {
        return moonVector[localMoonID];
    }
    
    return -1; // error
}

int Object::GetNumberOfMoons()
{
    return moonVector.size();
}

void Object::SetMoonStatus(bool flag)
{
    isMoon = flag;
}

bool Object::IsObjectMoon()
{
    return isMoon;
}

void Object::SetScale(const glm::vec3 &scale)
{
    myScale = scale;
}

glm::vec3 Object::GetScale()
{
    return myScale;
}

void Object::UpdateOrbitSpeed(float orbSpeed)
{
    orbitSpeed = orbSpeed;
}

void Object::UpdateRotationSpeed(float rotSpeed)
{
    rotationSpeed = rotSpeed;
}

bool Object::IsPaused()
{
    return ((rotationSpeedMultiplier == 0.0)
            && orbitSpeedMultiplier == 0.0);
}

