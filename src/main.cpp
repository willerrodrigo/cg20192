#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>

// Implement load triangle mesh
void loadTriangleMesh(
		const char * path, 
		std::vector<glm::vec3> & out_vertices, 
		std::vector<glm::vec2> & out_uvs,
		std::vector<glm::vec3> & out_normals){

		printf("Loading OBJ file %s...\n", path);

		std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
		std::vector<glm::vec3> temp_vertices; 
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;


		FILE * file = fopen(path, "r");
		if( file == NULL ){
			printf("Impossible to open the file ! Are you in the right path ?\n");
			getchar();
		}

		while( 1 ){
	
			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);
			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.
	
			// else : parse lineHeader
			
			if ( strcmp( lineHeader, "v" ) == 0 ){
				glm::vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
				temp_vertices.push_back(vertex);
			}else if ( strcmp( lineHeader, "vt" ) == 0 ){
				glm::vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y );
				uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
				temp_uvs.push_back(uv);
			}else if ( strcmp( lineHeader, "vn" ) == 0 ){
				glm::vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
				temp_normals.push_back(normal);
			}else if ( strcmp( lineHeader, "f" ) == 0 ){
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
				if (matches != 9){
					printf("File can't be read by our simple parser :-( Try exporting with other options\n");
					fclose(file);
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices    .push_back(uvIndex[0]);
				uvIndices    .push_back(uvIndex[1]);
				uvIndices    .push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}else{
				// Probably a comment, eat up the rest of the line
				char stupidBuffer[1000];
				fgets(stupidBuffer, 1000, file);
			}
	
		}
	
		// For each vertex of each triangle
		for( unsigned int i=0; i<vertexIndices.size(); i++ ){
	
			// Get the indices of its attributes
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];
			
			// Get the attributes thanks to the index
			glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
			glm::vec2 uv = temp_uvs[ uvIndex-1 ];
			glm::vec3 normal = temp_normals[ normalIndex-1 ];
			
			// Put the attributes in buffers
			out_vertices.push_back(vertex);
			out_uvs     .push_back(uv);
			out_normals .push_back(normal);
		
		}
		fclose(file);
};

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
	// std::cout << glm::to_string(m[0]) << std::endl;
	
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
	
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	loadTriangleMesh("../res/meshes/object.obj", vertices, uvs, normals);
	
    glfwTerminate();
	return 0;
}
