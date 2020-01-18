#include "TestSquare.h"

namespace test {

	TestSquare::TestSquare()
		:m_SquareColor {0.2f, 0.3f, 0.8f, 1.0f}
	{
		float positions[] = {
			-0.5f, -0.5f,
			 0.5f, -0.5f,
			 0.5f,  0.5f,
			-0.5f, 0.5f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		IndexBuffer ib(indices, 6);
		m_ib = &ib;

		VertexBuffer vb(positions, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);

		VertexArray va;
		va.AddBuffer(vb, layout);
		m_va = &va;

		Shader shader("res/shaders/TestSquare.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", m_SquareColor[0], m_SquareColor[1], m_SquareColor[2], m_SquareColor[3]);
		m_shader = &shader;

	}

	TestSquare::~TestSquare()
	{

	}


	void TestSquare::OnUpdate(float deltaTime)
	{
	}

	void TestSquare::OnRender()
	{
		Renderer renderer;
		renderer.Draw(*m_va, *m_ib, *m_shader);
	}

	void TestSquare::OnImGuiRender()
	{

	}
}