#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <iostream>
#include <vector>
using namespace std;

#include "graphics_headers.h"
#include "camera.h"
#include "shader.h"
#include "object.h"

class Graphics
{
  public:
    Graphics();
    ~Graphics();
    bool Initialize(int width, int height, const std::vector<pair<GLenum, std::string>>& shaderInfo);
    void Update(unsigned int dt);
    void Render();
    
    // PA2 Keyboard Input Funtionality + PA3 Modfications
    void ToggleRotationDirection(int object);
    void ToggleOrbitDirection(int object);
    void TogglePauseRotation(int object);
    void TogglePauseOrbit(int object);
    void TogglePauseAll(int object);
    void TogglePauseAllObjects();
    
    bool UpdateRotation(int object, float speed);
    bool UpdateOrbit(int object, float speed);

  private:
    std::string ErrorString(GLenum error);

    Camera *m_camera;
    Shader *m_shader;

    GLint m_projectionMatrix;
    GLint m_viewMatrix;
    GLint m_modelMatrix;

    std::vector<Object> objects;
    
};

#endif /* GRAPHICS_H */
