#include <iostream>
#include <vector>
#include <string>

#include "engine.h"

// Global Constants
const string FRAG_SHADER_OP = "-f";
const string VERT_SHADER_OP = "-v";

const char TAB = '\t';

bool CheckCommandLineParamaters(int argumentCount, char **argumentVector, vector<pair<GLenum, string>>& shaderVector);

int main(int argc, char **argv)
{
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("Menu, Keyboard, and Mouse Interaction", 800, 600);
  vector<pair<GLenum, string>> shaderVector;
    
  if(!CheckCommandLineParamaters(argc, argv, shaderVector))
  {
      std::cout << std::endl;
      
      delete engine;
      engine = NULL;
      return 1;
  }
    
  if(!engine->Initialize(shaderVector))
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = NULL;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = NULL;
  return 0;
}

bool CheckCommandLineParamaters(int argumentCount, char **argumentVector, vector<pair<GLenum, string>>& shaderVector)
{
    GLenum shaderType;
    string temp;
    int index;
    bool isVertexGiven = false;
    bool isFragGiven = false;
    
    for(index = 1; index < argumentCount; index++)
    {
        temp = argumentVector[index];
        
        if(temp == VERT_SHADER_OP || temp == FRAG_SHADER_OP)
        {
            if(temp == VERT_SHADER_OP)
            {
                shaderType = GL_VERTEX_SHADER;
                isVertexGiven = true;
            }
            
            else
            {
                shaderType = GL_FRAGMENT_SHADER;
                isFragGiven = true;
            }
            
            index++;
            temp = argumentVector[index];
            
            shaderVector.push_back(pair<GLenum, string>(shaderType, temp));
        }
        
        else
        {
            std::cout << "Invalid command line parameters: " << temp << std::endl;
            return false;
        }
    }
    
    return (isVertexGiven && isFragGiven);
}
