#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

#include <vector>

// Implement load triangle mesh
void loadTriangleMesh(
					const std::string & filename,
					std::vector<glm::vec3> & positions,
					std::vector<glm::vec3> & normals,
					std::vector<glm::vec2> & textureCoordinates,
					std::vector<size_t> & positionIndices,
					std::vector<size_t> & normalsIndices,
					std::vector<size_t> & textureCoordinates){
	
}

bool BACKGROUND_STATE = false;

// Resize event
void  resize(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

// Keyboard event
void keyboard(GLFWwindow* window, int key, int scancode, int action, int modifier){
	if(key == GLFW_KEY_A && action == GLFW_PRESS){
		BACKGROUND_STATE = !BACKGROUND_STATE;
	}
}

int main(int argc, char** argv) {
	glm::vec3 u(1.0f, 0, 0);
	glm::vec3 v(0, 1.0f, 0);
	
	/* PONTOS E VETORES */
	// float d = glm::dot(u, v);
	// glm::vec3 c = glm::cross(u, v);
	// glm::vec3 n = glm::normalize(u);
	
	// std::cout << d << std::endl;
	// std::cout << glm::to_string(d) << std::endl;
	
	/* MATRIZES */
	glm::mat3 m(  // COLUNA, e não LINHA (COLUNA MAJORITÁRIA)
		1, 2, 3,  // first column
		4, 5, 6,  // second column
		7, 8, 9); // third column
	
	// std::cout << glm::to_string(m) << std::endl;
	std::cout << glm::to_string(m[0]) << std::endl;
	
	/* Initialize the library */
    if (!glfwInit())
    {
    	std::cout << "Cannot create window." << std::endl;
    	return -1;
	}

    /* Setup OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);

    if(!window){
    	glfwTerminate();
    	
    	std::cout << "Cannot create window." << std::endl;
        return -1;	
	}

	// Register callbacks
	glfwSetFramebufferSizeCallback(window, resize);
	glfwSetKeyCallback(window, keyboard);

	/* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
    	glfwTerminate();
    	
    	std::cout << "Cannot load OpenGL procedures." << std::endl;
    	return -1;
	}

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        if(BACKGROUND_STATE)
        	glClearColor(1.0f, 0.5f, 0.7f, 1.0f);
        else
        	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

	// Destroy window
	glfwDestroyWindow(window);
	
    glfwTerminate();
	return 0;
}
