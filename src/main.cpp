#include <iostream>
#include <vector>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtx/string_cast.hpp"

#include "Shader.hpp"

using namespace std;
using namespace glm;

const int screenX = 1000;
const int screenY = 1000;

GLFWwindow* window;

struct Vertex  {
    vec3 pos;
    vec3 color;
    Vertex(vec3 p, vec3 c) {
        this->pos = p;
        this->color = c;
    }
};

void initializeOpenGL() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, 1);
    glfwWindowHint(GLFW_SAMPLES, 16);
    window = glfwCreateWindow(screenX, screenY, "Title Goes here", NULL, NULL);

    if (window == NULL)
    {
        cout << "Window creation failed" << endl;
        exit(-1);
    }

    glfwMakeContextCurrent(window);
    printf("window creation succeeded?????\n");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "GLAD init failed" << endl;
        exit(-1);
    }
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_DEPTH_TEST);
}


int main() {
    initializeOpenGL();
    Shader shader("basic.vert", "basic.frag");
    printf("made shader\n");

    vector<Vertex> vertices = {
        Vertex(vec3(0.0, 0.0, 0.0), vec3(1.0, 0.0, 0.0)),
        Vertex(vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0)),
        Vertex(vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0)),
    };
    vector<int> indices = {
        0, 1, 2
    };



    unsigned int VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glBindVertexArray(0);

    while(!glfwWindowShouldClose(window)) {
        
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        shader.setMatFour("projection", mat4(1.0));
        shader.setMatFour("view", mat4(1.0));
        shader.setMatFour("model", mat4(1.0));
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        
        //processInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}