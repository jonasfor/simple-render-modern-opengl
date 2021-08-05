#include <iostream>
#include <GL/glew.h>
#include "display.h"
#include "shaders.h"


int main()
{
    Display display(1000, 1000, "Testing Shaders");
    
    
    Shader shader("/home/jonas/Mynotes/ModernOpenGl/res/basicShader");


    while (!display.isClosed())
    {

        glClearColor(0.2f, 0.3f, 0.1f, 1.0f);

        shader.Bind();

        display.Update();
    }
    
}