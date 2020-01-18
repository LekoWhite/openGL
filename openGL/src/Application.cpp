#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Renderer.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

//struct WindowSize
//{
//	unsigned int height;
//    unsigned int width;
//    unsigned int x_aspect_ratio;
//    unsigned int y_aspect_ratio;
//    
//    WindowSize(unsigned int height, unsigned int x_aspect_ratio, unsigned int y_aspect_ratio)
//        :height(height), x_aspect_ratio(x_aspect_ratio), y_aspect_ratio(y_aspect_ratio)
//    {
//        width =(int)(height * ((float)x_aspect_ratio / (float)y_aspect_ratio));
//    }
//
//    WindowSize()
//        :height(640 * 2), width(480 * 2), x_aspect_ratio(4), y_aspect_ratio(3) {}
//};

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // WindowSize windowSize(960, 16, 9);

    static float windowScale = 1;
	static int width = (int)(960 * windowScale);
    static int height = (int)(540 * windowScale);
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "OpenGL Babyyyyyyyyyy", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    
    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }

    GLCall(std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl);
    GLCall(std::cout << "OpenGL Vendor : " << glGetString(GL_VENDOR) << std::endl);

    {

        float positions[] = {
            000.0f, 000.0f, 0.0f, 0.0f, // 0
            100.0f, 000.0f, 1.0f, 0.0f, // 1
            100.0f, 100.0f, 1.0f, 1.0f, // 2
            000.0f, 100.0f, 0.0f, 1.0f  // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va;

        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        //glm::mat4 proj = glm::ortho((-1.0f * windowSize.x_aspect_ratio)/scale, (1.0f * windowSize.x_aspect_ratio)/scale,
        //    (-1.0f * windowSize.y_aspect_ratio)/scale, (1.0f * windowSize.y_aspect_ratio)/scale, -1.0f, 1.0f);

        Shader shader("res/shaders/Basic.shader");
        shader.Bind();
        // shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        Texture texture("res/textures/TestTexture.png");
        texture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();

        Renderer renderer;

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init((char*)glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS));

        bool show_demo_window = true;
        //bool show_another_window = false;
        //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		float r = 0.0f;
		float increment = 0.05f;

        glm::vec3 translationA(200, 100, 0);
        glm::vec3 translationB(400, 100, 0);


        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();

            // New IMGUI frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // HL2 Lambda 1
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }

            // HL2 Lambda 2
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                shader.Bind();
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, shader);
            }


            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;


            


            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                /*static float f = 0.0f;
                static int counter = 0;*/

                ImGui::Begin("Framerate");                          // Create a window called "Hello, world!" and append into it.

                //ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

                //ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
                ImGui::SliderFloat3("TranslationA", &translationA.x, 0.0f, 960.0f);
                ImGui::SliderFloat3("TranslationB", &translationB.x, 0.0f, 960.0f);
                //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                //if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                //    counter++;
                //ImGui::SameLine();
                //ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}