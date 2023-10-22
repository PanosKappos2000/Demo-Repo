#include "FlashLight.h"

Flashlight::Flashlight(const glm::vec3& position, const glm::vec3& direction,
	float innerCutoff, float outerCutoff, const glm::vec3& amb, 
	const glm::vec3& diff, const glm::vec3& spec, float lin, float quad, float cnst)

	:m_light(innerCutoff, outerCutoff, position, direction, amb, diff, spec, lin, quad, cnst)
{

}

Flashlight::~Flashlight()
{

}

void Flashlight::OnUpdate()
{
	m_light.position = Window::GetWindowInstance()->GetCamera()->GetPosition();
	m_light.direction = Window::GetWindowInstance()->GetCamera()->GetDirection();
}

void Flashlight::Draw()
{

}