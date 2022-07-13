
#include "GLManager.h"

#ifdef OPENGL

#include "Managers/WindowManager.h"
#include "Managers/ModelManager.h"
#include "Managers/MaterialManager.h"
#include "Material.h"
#include "Model.h"

#include <cstdio>
#include <iostream>
#include <vector>

namespace GLManager
{
	void Init() 
	{
		if (glewInit() != GLEW_OK)
		{
			printf("Error starting glew");
		}

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl;
	};

	void Destroy() 
	{
		
	};

	void DrawFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//glBegin(GL_TRIANGLES);
		//glVertex2f(-0.5f, -0.5f);
		//glVertex2f(0.0f, 0.0f);
		//glVertex2f(0.5f, -0.5f);
		//glEnd();
		ModelManager::Update(DeltaTime, imageIndex);

		std::vector<Material*> materials = MaterialManager::GetMaterials();
		for (Material* mat : materials)
		{
			for (Model* model : mat->m_pModels)
			{
				//TODO: Textures and camera UBO
				glBindBuffer(GL_ARRAY_BUFFER, model->vertexBufferID);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indexBufferID);
				glDrawElements(GL_TRIANGLES, model->indices.size(), GL_UNSIGNED_INT, (void*)0);
			}
		}

		glfwSwapBuffers(WindowManager::GetWindow());
	}
}
#endif // OPENGL