#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

int main(int argc, char** argv) {
	/* Initialize the library */
    if (!glfwInit())
        return -1;
    
    /* Setup OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 60, "Hello World", NULL, NULL);
    
    if(!window){
    	glfwTerminate();
        return -1;	
	}
	
	/* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    	glfwTerminate();
    	return -1;
	}
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    
    glfwTerminate();
	return 0;
}
