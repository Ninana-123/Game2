#include "pch.h"
#include "GraphicsSystem.h"

namespace Engine {

	class RenderData {

	public:
		RenderData() {}

		void SetColor(glm::vec4 color)
		{
			m_Color = color;
		}

		glm::vec4& GetColor() { return m_Color; };

	private:
		glm::vec4 m_Color; //colour for texture
		
	};
}