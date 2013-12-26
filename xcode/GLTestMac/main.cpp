//
//  main.cpp
//  GLTestMac
//
//  Created by おもちメタル on 2013/12/26.
//  Copyright (c) 2013年 omochimetaru. All rights reserved.
//

#include <GLFW/glfw3.h>

int main(int argc, const char * argv[]){
    GLFWwindow* window;
	
    /* Initialize the library */
    if (!glfwInit())
        return -1;
	
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
	
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
		
        /* Poll for and process events */
        glfwPollEvents();
    }
	
    glfwTerminate();
    return 0;

}

