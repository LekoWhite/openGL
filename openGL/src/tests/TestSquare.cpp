#include "TestSquare.h"

namespace test {

	TestSquare::TestSquare() 
	{
		float positions[

		];
	}

	TestSquare::~TestSquare()
	{

	}


	void TestSquare::OnUpdate(float deltaTime)
	{
		renderer.Draw(m_va, m_ib, m_shader);
	}

	void TestSquare::OnRender()
	{

	}

	void TestSquare::OnImGuiRender()
	{

	}
}