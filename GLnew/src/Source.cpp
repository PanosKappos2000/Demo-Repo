#include "Window/window.h"
#include "Shader/Shader.h"
#include "Entities/cube.h"
#include "Entities/Vegetation.h"
#include "Renderer/Renderer.h"
#include "Memory/Memory.h"

#include <vector>

int main()
{
	Window* window = new Window();
	Renderer* renderer = new Renderer();
	Shader::Init();
	CEMemoryArenaAllocator();

	renderer->Append(new RotatingCube("res/Textures/Container.png",
		"res/Textures/Container_specular.png",glm::vec3(0.0f, 0.0f, 0.0f)));
	renderer->Append(new RotatingCube("res/Textures/Container.png",
		"res/Textures/Container_specular.png",glm::vec3(1.0f, -2.2f, -6.3f)));
	renderer->Append(new RotatingCube("res/Textures/Container.png",
		"res/Textures/Container_specular.png",glm::vec3(2.2f, -2.1, -3.4f)));
	renderer->Append(new RotatingCube("res/Textures/Container.png",
		"res/Textures/Container_specular.png",glm::vec3(-3.7f, -4.0f, -8.9f)));
	renderer->Append(new RotatingCube("res/Textures/Container.png",
		"res/Textures/Container_specular.png",glm::vec3(-2.7f, -2.0f, -7.2f)));
	renderer->Append(new RotatingCube("res/Textures/Container.png",
		"res/Textures/Container_specular.png",glm::vec3(-4.7f, 4.0f, -11.5f)));
	renderer->Append(new RotatingCube("res/Textures/Container.png",
		"res/Textures/Container_specular.png",glm::vec3(-1.7f, 2.4f, -6.9f)));
	renderer->Append(new RotatingCube("res/Textures/Container.png",
		"res/Textures/Container_specular.png",glm::vec3(2.2f, 2.5f, -13.1f)));
	renderer->Append(new RotatingCube("res/Textures/Container.png",
		"res/Textures/Container_specular.png",glm::vec3(0.7f, 3.9f, -6.3f)));

	renderer->AddLightCube(new LightCube());
	renderer->AddLightCube(new LightCube(glm::vec3(8.0f, 6.0f, -4.0f)));
	renderer->AddLightCube(new LightCube(glm::vec3(8.0f, 6.0f, -8.0f)));
	renderer->AddLightCube(new LightCube(glm::vec3(-8.0f, 6.0f, -4.0f)));
	renderer->AddLightCube(new LightCube(glm::vec3(-8.5f, 6.0f, -8.0f)));

	std::string modelFilepath("res/Models/backpack/backpack.obj");
	renderer->Append(new Model(modelFilepath));

	std::string vegetationFilepath("res/Textures/Vegetation.png");
	renderer->Append(new Vegetation(glm::vec3(0.0f, -2.0f, 2.0f), vegetationFilepath));

	Material mat1(MaterialType::MT_BlackPlastic);
	renderer->GetRotatingCube(2)->SetMaterial(mat1);
	Material mat2(MaterialType::MT_Ruby);
	renderer->GetRotatingCube(3)->SetMaterial(mat2);
	Material mat3(MaterialType::MT_Obsidian);
	renderer->GetRotatingCube(4)->SetMaterial(mat3);
	Material mat4(MaterialType::MT_Silver);
	renderer->GetRotatingCube(5)->SetMaterial(mat4);
	Material mat5(MaterialType::MT_Gold);
	renderer->GetRotatingCube(6)->SetMaterial(mat5);
	Material mat6(MaterialType::MT_Emerald);
	renderer->GetRotatingCube(7)->SetMaterial(mat6);
	Material mat7(MaterialType::MT_CyanRubber);
	renderer->GetRotatingCube(8)->SetMaterial(mat7);
	Material mat8(MaterialType::MT_Brass);
	renderer->GetRotatingCube(9)->SetMaterial(mat8);
	Material mat9(MaterialType::MT_Pearl);
	renderer->GetRotatingCube(10)->SetMaterial(mat9);

	unsigned int shadowFramebufferTag;
	glGenFramebuffers(1, &shadowFramebufferTag);

	unsigned int depthMapTextureTag;
	glGenTextures(1, &depthMapTextureTag);
	glActiveTexture(GL_TEXTURE0 + 30);
	glBindTexture(GL_TEXTURE_2D, depthMapTextureTag);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0,
		GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowFramebufferTag);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTextureTag, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (window->IsOpen())
	{
		window->OnBufferUpdate();

		glViewport(0, 0, 1024, 1024);
		glBindFramebuffer(GL_FRAMEBUFFER, shadowFramebufferTag);
		glClear(GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glViewport(0, 0, window->GetWidth(), window->GetHeight());

		renderer->OnUpdate();
		renderer->Draw();
		window->OnUpdate();
	}

	delete window;
	delete renderer;
	Shader::DeInit();
}