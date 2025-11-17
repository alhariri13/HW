
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_m.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Polygon.cpp"

using namespace glm;

int width = 800;
int height = 600;

vec3 cameraPos = vec3(0.0f, 0.0f, 4.0f);
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);
vec3 cameraUp = vec3(0.0f, 1.0f, 0.0f);

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 0.001f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= cross(cameraFront, normalize(cross(cameraFront, cameraUp))) * cameraSpeed;

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        mat4 r = rotate(mat4(1.0f), 0.001f, vec3(0.0f, 1.0f, 0.0f));
        vec4 v = r * vec4(cameraFront, 1.0f);
        cameraFront = vec3(v);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        mat4 r = rotate(mat4(1.0f), 0.001f, vec3(0.0f, -1.0f, 0.0f));
        vec4 v = r * vec4(cameraFront, 1.0f);
        cameraFront = vec3(v);
    }
}

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(width, height, "Wall Clock", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("./shaders/vs/L3.vs", "./shaders/fs/L3.fs");

    
    std::vector<vec3> v_body;
    v_body.push_back(vec3(-0.4f, -0.85f, -0.25f));
    v_body.push_back(vec3(0.4f, -0.85f, -0.25f));
    v_body.push_back(vec3(0.4f, 0.85f, -0.25f));
    v_body.push_back(vec3(-0.4f, 0.85f, -0.25f));
    Polygon fBody(v_body, vec3(0.5f, 0.5f, 0.5f));
    std::vector<vec3> b_body;
    b_body.push_back(vec3(-0.4f, -0.85f, -0.32f));
    b_body.push_back(vec3(0.4f, -0.85f, -0.32f));
    b_body.push_back(vec3(0.4f, 0.85f, -0.32f));
    b_body.push_back(vec3(-0.4f, 0.85f, -0.32f));
    Polygon bBody(b_body, vec3(0.5f, 0.5f, 0.5f));

    std::vector<vec3> e1_body;
    e1_body.push_back(vec3(-0.4f, -0.85f, -0.25f));
    e1_body.push_back(vec3(0.4f, -0.85f, -0.25f));
    e1_body.push_back(vec3(-0.4f, -0.85f, -0.32f));
    e1_body.push_back(vec3(0.4f, -0.85f, -0.32f));
    Polygon e1Body(e1_body, vec3(0.5f, 0.5f, 0.5f));

    std::vector<vec3> e2_body;
    e2_body.push_back(vec3(0.4f, -0.85f, -0.25f));
    e2_body.push_back(vec3(0.4f, 0.85f, -0.25f));
    e2_body.push_back(vec3(0.4f, 0.85f, -0.32f));
    e2_body.push_back(vec3(0.4f, -0.85f, -0.32f));
    Polygon e2Body(e2_body, vec3(0.5f, 0.5f, 0.5f));

    std::vector<vec3> e3_body;
    e3_body.push_back(vec3(0.4f, 0.85f, -0.25f));
    e3_body.push_back(vec3(-0.4f, 0.85f, -0.25f));
    e3_body.push_back(vec3(-0.4f, 0.85f, -0.32f));
    e3_body.push_back(vec3(0.4f, 0.85f, -0.32f));
    Polygon e3Body(e3_body, vec3(0.5f, 0.5f, 0.5f));

    std::vector<vec3> e4_body;
    e4_body.push_back(vec3(-0.4f, 0.85f, -0.25f));
    e4_body.push_back(vec3(-0.4f, -0.85f, -0.25f));
    e4_body.push_back(vec3(-0.4f, -0.85f, -0.32f));
    e4_body.push_back(vec3(-0.4f, 0.85f, -0.32f));
    Polygon e4Body(e4_body, vec3(0.5f, 0.5f, 0.5f));
    
    float centerY = 0.4f;
    float radiusOuter = 0.30f;
    float radiusInner = 0.26f;
    int seg = 50;

    std::vector<vec3> v_circleOuter;
    for (int i = 0; i < seg; i++)
    {
        float a = 2.0f * 3.14159f * (float)i / (float)seg;
        float x = radiusOuter * cos(a);
        float y = radiusOuter * sin(a);
        v_circleOuter.push_back(vec3(x, y + centerY, -0.23f));
    }
    Polygon clock_ring(v_circleOuter, vec3(0.3f, 0.3f, 0.3f));
    
    std::vector<vec3> v_mark_dot;
    float dotRadius = 0.01f;
    int dotSegments = 20;

    for (int i = 0; i < dotSegments; ++i) {
        float angle = 2.0f * 3.14159f * i / dotSegments;
        float x = dotRadius * cos(angle);
        float y = dotRadius * sin(angle);
        v_mark_dot.push_back(vec3(x, y, -0.21f)); 
    }
   
    Polygon mark(v_mark_dot, vec3(0.9f, 0.75f, 0.3f));

    
    std::vector<vec3> v_min;
    v_min.push_back(vec3(-0.01f, 0.0f, -0.20f));
    v_min.push_back(vec3(0.01f, 0.0f, -0.20f));
    v_min.push_back(vec3(0.01f, 0.28f, -0.20f));
    v_min.push_back(vec3(-0.01f, 0.28f, -0.20f));
    Polygon hand_min(v_min, vec3(0.0f, 0.0f, 0.0f));

 
    std::vector<vec3> v_hour;
    v_hour.push_back(vec3(-0.015f, 0.0f, -0.20f));
    v_hour.push_back(vec3(0.015f, 0.0f, -0.20f));
    v_hour.push_back(vec3(0.015f, 0.22f, -0.20f));
    v_hour.push_back(vec3(-0.015f, 0.22f, -0.20f));
    Polygon hand_hour(v_hour, vec3(0.1f, 0.1f, 0.4f));

    
    std::vector<vec3> v_centerDot;
    v_centerDot.push_back(vec3(-0.02f, -0.02f, -0.19f));
    v_centerDot.push_back(vec3(0.02f, -0.02f, -0.19f));
    v_centerDot.push_back(vec3(0.02f, 0.02f, -0.19f));
    v_centerDot.push_back(vec3(-0.02f, 0.02f, -0.19f));
    Polygon center_dot(v_centerDot, vec3(0.3f, 0.2f, 0.1f));

    
    std::vector<vec3> v_pend_stick;
    v_pend_stick.push_back(vec3(-0.012f, 0.0f, -0.20f));
    v_pend_stick.push_back(vec3(0.012f, 0.0f, -0.20f));
    v_pend_stick.push_back(vec3(0.012f, -0.55f, -0.20f));
    v_pend_stick.push_back(vec3(-0.012f, -0.55f, -0.20f));
    Polygon pend_stick(v_pend_stick, vec3(0.0f, 0.0f, 0.0f)); 
  
    std::vector<vec3> v_pend_bob;
    float radius1 = 0.11f;
    int segments1 = 32; 
    float centerY1 = 0.0f;
    float centerX1 = 0.0f;
    float z = -0.20f;

    for (int i = 0; i < segments1; ++i) {
        float angle = 2.0f * 3.14159f * i / segments1;
        float x = centerX1 + radius1 * cos(angle);
        float y = centerY1 + radius1 * sin(angle);
        v_pend_bob.push_back(vec3(x, y, z));
    }

    Polygon pend_bob(v_pend_bob, vec3(0.9f, 0.85f, 0.4f));
    

    
    ourShader.use();
    mat4 projection = perspective(radians(45.0f),
        (float)width / (float)height,
        0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4 view = lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);

        float t = (float)glfwGetTime();
        float pend_angle = sin(t) * 0.5f;
        float angle_min = -t * 0.9f;
        float angle_hour = -t * 0.6f;

        mat4 m = mat4(1.0f);


        
        bBody.transformation(m);
        bBody.draw(ourShader);

        fBody.transformation(m);
        fBody.draw(ourShader);

        e1Body.transformation(m);
        e1Body.draw(ourShader);

        e2Body.transformation(m);
        e2Body.draw(ourShader);

        e3Body.transformation(m);
        e3Body.draw(ourShader);

        e4Body.transformation(m);
        e4Body.draw(ourShader);

       
        clock_ring.transformation(m);
        clock_ring.draw(ourShader);

        
        for (int i = 0; i < 12; i++)
        {
            mat4 mm = m;
            mm = translate(mm, vec3(0.0f, centerY, 0.0f));
            mm = rotate(mm, radians(30.0f * (float)i), vec3(0.0f, 0.0f, 1.0f));
            mm = translate(mm, vec3(0.0f, radiusInner * 0.85f, 0.0f));
            mark.transformation(mm);
            mark.draw(ourShader);
        }
        
        {
            mat4 mh = m;
            mh = translate(mh, vec3(0.0f, centerY, 0.0f));
            mh = rotate(mh, angle_min, vec3(0.0f, 0.0f, 1.0f));
            hand_min.transformation(mh);
            hand_min.draw(ourShader);
        }

        {
            mat4 mh = m;
            mh = translate(mh, vec3(0.0f, centerY, 0.0f));
            mh = rotate(mh, angle_hour, vec3(0.0f, 0.0f, 1.0f));
            hand_hour.transformation(mh);
            hand_hour.draw(ourShader);
        }
        {
            mat4 mc = m;
            mc = translate(mc, vec3(0.0f, centerY, 0.0f));
            center_dot.transformation(mc);
            center_dot.draw(ourShader);
        }

        {
            mat4 mp = m;
            mp = translate(mp, vec3(0.0f, -0.05f, 0.0f)); 
            mp = rotate(mp, pend_angle, vec3(0.0f, 0.0f, 1.0f));

            pend_stick.transformation(mp);
            pend_stick.draw(ourShader);

            mat4 mb = mp;
            mb = translate(mb, vec3(0.0f, -0.65f, 0.0f));
            pend_bob.transformation(mb);
            pend_bob.draw(ourShader);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
