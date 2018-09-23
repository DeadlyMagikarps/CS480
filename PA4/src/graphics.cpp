#include "graphics.h"

Graphics::Graphics()
{
    
}

Graphics::~Graphics()
{
    
}

bool Graphics::Initialize(int width, int height, const std::vector<pair<GLenum, std::string>>& shaderInfo)
{
    // Used for the linux OS
#if !defined(__APPLE__) && !defined(MACOSX)
    // cout << glewGetString(GLEW_VERSION) << endl;
    glewExperimental = GL_TRUE;
    
    auto status = glewInit();
    
    // This is here to grab the error that comes from glew init.
    // This error is an GL_INVALID_ENUM that has no effects on the performance
    glGetError();
    
    //Check for error
    if (status != GLEW_OK)
    {
        std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
        return false;
    }
#endif
    
    // For OpenGL 3
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
    int index;
    
    // Init Camera
    m_camera = new Camera();
    if(!m_camera->Initialize(width, height))
    {
        printf("Camera Failed to Initialize\n");
        return false;
    }
    
    // Create the object (2 for this one)
    objects.push_back(Object());
    objects.push_back(Object());
    
    // Initialize default speeds of these objects
    objects[0].UpdateOrbitSpeed(0.4f);
    objects[0].UpdateRotationSpeed(1.0f);
    objects[0].SetOrbitRadius(6.0f);
    
    objects[1].UpdateOrbitSpeed(0.5f);
    objects[1].UpdateRotationSpeed(0.5f);
    objects[1].SetOrbitRadius(4.0f);
    
    // Add the moon and set the scale
    objects[0].AddObjectChild(1);
    objects[1].SetMoonStatus(true);
    objects[1].SetScale(glm::vec3(0.6, 0.63, 0.6));
    
    // Set up the shaders
    m_shader = new Shader();
    if(!m_shader->Initialize())
    {
        printf("Shader Failed to Initialize\n");
        return false;
    }
    
    // Add the two shaders
    for(index = 0; index < shaderInfo.size(); index++)
    {
        if(!m_shader->AddShader(shaderInfo[index].first, shaderInfo[index].second))
        {
            if(shaderInfo[index].first == GL_VERTEX_SHADER)
            {
                printf("Vertex Shader failed to Initialize\n");
            }
            
            else
            {
                printf("Fragment Shader failed to Initialize\n");
            }
            
            return false;
        }
    }
    
    // Connect the program
    if(!m_shader->Finalize())
    {
        printf("Program to Finalize\n");
        return false;
    }
    
    // Locate the projection matrix in the shader
    m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
    if (m_projectionMatrix == INVALID_UNIFORM_LOCATION)
    {
        printf("m_projectionMatrix not found\n");
        return false;
    }
    
    // Locate the view matrix in the shader
    m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
    if (m_viewMatrix == INVALID_UNIFORM_LOCATION)
    {
        printf("m_viewMatrix not found\n");
        return false;
    }
    
    // Locate the model matrix in the shader
    m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
    if (m_modelMatrix == INVALID_UNIFORM_LOCATION)
    {
        printf("m_modelMatrix not found\n");
        return false;
    }
    
    //enable depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    return true;
}

void Graphics::Update(unsigned int dt)
{
    int index;
    
    // Update the objects
    for(index = 0; index < objects.size(); index++)
    {
        if(!objects[index].IsObjectMoon())
        {
            objects[index].Update(dt);
            objects[index].UpdateMoonData(dt, objects, true);
        }
    }
}

void Graphics::Render()
{
    int index;
    
    //clear the screen
    glClearColor(0.0, 0.0, 0.2, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Start the correct program
    m_shader->Enable();
    
    // Send in the projection and view to the shader
    glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetProjection()));
    glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE, glm::value_ptr(m_camera->GetView()));
    
    // Render the objects
    for(index = 0; index < objects.size(); index++)
    {
        glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE, glm::value_ptr(objects[index].GetModel()));
        objects[index].Render();
    }
    
    // Get any errors from OpenGL
    auto error = glGetError();
    if ( error != GL_NO_ERROR )
    {
        string val = ErrorString( error );
        std::cout<< "Error initializing OpenGL! " << error << ", " << val << std::endl;
    }
}

std::string Graphics::ErrorString(GLenum error)
{
    if(error == GL_INVALID_ENUM)
    {
        return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
    }
    
    else if(error == GL_INVALID_VALUE)
    {
        return "GL_INVALID_VALUE: A numeric argument is out of range.";
    }
    
    else if(error == GL_INVALID_OPERATION)
    {
        return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
    }
    
    else if(error == GL_INVALID_FRAMEBUFFER_OPERATION)
    {
        return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
    }
    
    else if(error == GL_OUT_OF_MEMORY)
    {
        return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
    }
    else
    {
        return "None";
    }
}

void Graphics::ToggleRotationDirection(int object)
{
    if(object < objects.size())
    {
        objects[object].ToggleRotationDirection();
    }
}

void Graphics::ToggleOrbitDirection(int object)
{
    if(object < objects.size())
    {
       objects[object].ToggleOrbitDirection();
    }
}

void Graphics::TogglePauseRotation(int object)
{
    if(object < objects.size())
    {
        objects[object].TogglePauseRotation();
    }
}

void Graphics::TogglePauseOrbit(int object)
{
    if(object < objects.size())
    {
        objects[object].TogglePauseOrbit();
    }
}

void Graphics::TogglePauseAll(int object)
{
    if(object < objects.size())
    {
        objects[object].TogglePauseAll();
    }
}

void Graphics::TogglePauseAllObjects()
{
    bool allPaused = true;
    int index;
    
    for(index = 0; index < objects.size(); index++)
    {
        if(!objects[index].IsPaused())
        {
            objects[index].TogglePauseAll();
            allPaused = false;
        }
    }
    
    if(!allPaused)
    {
        return;
    }
    
    for(index = 0; index < objects.size(); index++)
    {
        if(objects[index].IsPaused())
        {
            objects[index].TogglePauseAll();
        }
    }
}
