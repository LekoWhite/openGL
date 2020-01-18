#pragma once

#include "Test.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"

namespace test {

	class TestSquare : public Test
	{
	public:
		TestSquare();
		~TestSquare();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		VertexArray m_va;
		IndexBuffer m_ib;
		Shader m_shader;
		Renderer renderer;
	};
}

