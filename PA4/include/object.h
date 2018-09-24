#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "graphics_headers.h"
#include "SDL.h"

class Object
{
  public:
    Object();
    Object(const std::string &path);
    ~Object();
    void Update(unsigned int dt);
    void Render();
    
    // PA4 Specific
    std::vector<Vertex> GetVertices();
    std::vector<unsigned int> GetIndicies();
    void SetVerticies(Vertex v);
    void SetIndices(unsigned int i);
    
    glm::mat4 GetModel();

  private:
    glm::mat4 model;
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    
    GLuint VB;
    GLuint IB;
};

#endif /* OBJECT_H */
