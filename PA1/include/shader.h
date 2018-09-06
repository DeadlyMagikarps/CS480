#ifndef SHADER_H
#define SHADER_H

#include <vector>
#include <fstream>
#include <string>

#include "graphics_headers.h"

class Shader
{
  public:
    Shader();
    ~Shader();
    bool Initialize();
    void Enable();
    bool AddShader(GLenum ShaderType, const std::string &filename);
    bool Finalize();
    GLint GetUniformLocation(const char* pUniformName);

  private:
    GLuint m_shaderProg;    
    std::vector<GLuint> m_shaderObjList;
    
    std::string LoadFile(const std::string &filename, std::string &shaderFileType);
    bool ShaderSourceLoaded(const std::string &filename, std::string &shaderFileType);
};

#endif  /* SHADER_H */
