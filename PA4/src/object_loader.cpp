//
//  object_loader.cpp
//  
//
//  Created by Hadi Rumjahn on 9/23/18.
//

#include "object_loader.h"
#include "object.h"
#include "graphics_headers.h"

void LoadOBJ(const std::string &path)
{
    Object o;
    
    printf("Loading OBJ file %s...\n", path.c_str());
    
    // Open file
    FILE * fin = fopen(path.c_str(), "r");
    std::cerr << "File Opened: " << path.c_str() << std::endl;
    std::cerr << fin;
    
    if(fin == NULL)
    {
        std::cerr << "File is Empty" << std::endl;
        return;
    }
    
    // Read in the file
    while(1)
    {
        char head[128];
        
        int res = fscanf(fin, "%s", head);
        
        if(res == EOF)
        {
            break;
        }
        
        if(strcmp(head, "v") == 0)
        {
            glm::vec3 vertex;
            glm::vec3 color;
            
            fscanf(fin, "%f %f %f \n", &vertex.x, &vertex.y, &vertex.z);
            
            color.x = (float)(rand() % 2);
            color.y = (float)(rand() % 2);
            color.z = (float)(rand() % 1);
            
            Vertex *temp = new Vertex(vertex, color);
            
            // Push the vertices
            o.SetVerticies(*temp);
        }
        
        else if(strcmp(head, "f") == 0)
        {
            unsigned int firstVal[3], secondVal[3];
            
            fscanf(fin, "%i//%i %i//%i %i//%i\n", &firstVal[0], &secondVal[0], &firstVal[1], &secondVal[1], &firstVal[2], &secondVal[2]);
            
            // Push the indicies
            o.SetIndices(firstVal[0]);
            o.SetIndices(firstVal[1]);
            o.SetIndices(firstVal[2]);
        }
    }
}
