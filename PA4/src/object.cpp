#include "object.h"
#include "object_loader.h"

Object::Object()
{
    for(unsigned int i = 0; i < Indices.size(); i++)
    {
        Indices[i] = Indices[i] - 1;
    }
    
    // Load obj file information into VBO
    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * Indices.size(), &Indices[0], GL_STATIC_DRAW);
}

Object::Object(const std::string &fileName)
{
    
    LoadOBJ(fileName);
    
    for(unsigned int i = 0; i < Indices.size(); i++)
    {
        Indices[i] = Indices[i] - 1;
    }
    
    // Load obj file information into VBO
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
    model = glm::mat4(1.0f);
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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

std::vector<Vertex> Object::GetVertices()
{
    return Vertices;
}

std::vector<unsigned int> Object::GetIndicies()
{
    return Indices;
}

void Object::SetVerticies(Vertex v)
{
    Vertices.push_back(v);
}

void Object::SetIndices(unsigned int i)
{
    Indices.push_back(i);
}
