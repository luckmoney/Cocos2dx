#include "asteroids.h"

void Asteroids::Init()
{
	
	aster_shader = new Shader("../OpenGlLearn/src/Instancing/asteroids_shader.vs", "../OpenGlLearn/src/Instancing/asteroids_shader.fs");
	planet_shader = new Shader("../OpenGlLearn/src/Instancing/planet.vs", "../OpenGlLearn/src/Instancing/planet.fs");

	
	rock = new Model("../OpenGlLearn/res/objects/rock/rock.obj");
	planet = new Model("../OpenGlLearn/res/objects/planet/planet.obj");

	unsigned int amount = 10000;
	modelMatrices = new glm::mat4[amount];

	srand(glfwGetTime());
	float radius = 150.0;
	float offset = 25.0f;

	for (unsigned int i = 0 ; i < amount; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		// 1. translation: displace along circle with 'radius' in range [-offset, offset]
		float angle = (float)i / (float)amount * 360.0f;
		float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float x = sin(angle) * radius + displacement;
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float y = displacement * 0.4f; // keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		// 2. scale: Scale between 0.05 and 0.25f
		float scale = (rand() % 20) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		// 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
		float rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. now add to list of matrices
		modelMatrices[i] = model;
	}

	unsigned int buffer;
	glGenBuffers(1,&buffer);
	glBindBuffer(GL_ARRAY_BUFFER,buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	for (unsigned int i = 0 ; i < rock->meshees.size();i++)
	{
		unsigned int VAO = rock->meshees[i].VAO;
		glBindVertexArray(VAO);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(6);
		glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

		glVertexAttribDivisor(3,1);
		glVertexAttribDivisor(4,1);
		glVertexAttribDivisor(5, 1);
		glVertexAttribDivisor(6, 1);

		glBindVertexArray(0);

	}
}

void Asteroids::Render(Camera *camera)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::mat4 projection = glm::perspective(glm::radians(45.0f),
		float(SCR_WIDTH) / float(SCR_HEIGHT),0.1f,1000.0f);

	glm::mat4 view = camera->GetViewMatrix();
	aster_shader->use();
	aster_shader->setMat4("projection", projection);
	aster_shader->setMat4("view", view);
	planet_shader->use();
	planet_shader->setMat4("projection", projection);
	planet_shader->setMat4("view", view);


	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(0.0f,-3.0f,0.0f));
	model = glm::scale(model,glm::vec3(4.0f,4.0f,4.0f));
	planet_shader->setMat4("model", model);
	planet->Draw(*planet_shader);


	aster_shader->use();
	aster_shader->setInt("texture_diffuse1", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, rock->textures_loaded[0].id);
	unsigned int amount = 10000;
	for (unsigned int  i = 0; i < rock->meshees.size(); i++)
	{
		glBindVertexArray(rock->meshees[i].VAO);
		glDrawElementsInstanced(GL_TRIANGLES, rock->meshees[i].indices.size(), GL_UNSIGNED_INT, 0, amount);
		glBindVertexArray(0);
	}


}

