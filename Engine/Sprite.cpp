#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

#include <cstddef>


namespace Engine {

	Sprite::Sprite()
	{
		_vboID = 0;
	}
	Sprite::~Sprite()
	{
		// free BUFFER - free VRAM!
		if (_vboID != 0)
			glDeleteBuffers(1, &_vboID);		// deallocate VBO on GPU - (memory leak, can be HERE!)
	}

	void Sprite::init(float x, float y, float width, float height, std::string texturePath)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		_texture = ResourceManager::getTexture(texturePath);

		// tell GPU "take vboID & allocate to a VBO"! 
		if (_vboID == 0)		// (0 - indicates no buffer)
			glGenBuffers(1, &_vboID);		// every NEW vboID - unique ID

		// upload data to that buffer - use ARRAY!		(TASK !!! - make for loop to upload array of vertex)
		Vertex vertexData[6];
		// first triangle
		vertexData[0].setPosition(x + width, y + height);
		vertexData[0].setUV(1.0f, 1.0f);

		vertexData[1].setPosition(x, y + height);
		vertexData[1].setUV(0.0f, 1.0f);

		vertexData[2].setPosition(x, y);
		vertexData[2].setUV(0.0f, 0.0f);
		// second triangle
		vertexData[3].setPosition(x, y);
		vertexData[3].setUV(0.0f, 0.0f);

		vertexData[4].setPosition(x + width, y);
		vertexData[4].setUV(1.0f, 0.0f);

		vertexData[5].setPosition(x + width, y + height);
		vertexData[5].setUV(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			vertexData[i].setColor(255, 0, 255, 255);
		}
		vertexData[1].setColor(0, 0, 255, 255);
		vertexData[4].setColor(0, 255, 0, 255);


		// bind the buffer
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);		// specify as - ARRAY BUFFER
		// upload the data (vertexArray) to VBO
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		// unbind buffer!
		glBindBuffer(GL_ARRAY_BUFFER, 0);		// VBO - NOT ACTIVE!
	}
	void Sprite::draw()	// gen VBO!
	{

		glBindTexture(GL_TEXTURE_2D, _texture.id);
		// NOW we need DRAW SPRITE!
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);		// bind AGAIN!

		// tell GL "DRAW"
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);

		glDisableVertexAttribArray(1);

		glDisableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);		// VBO - NOT ACTIVE!
	}
}
