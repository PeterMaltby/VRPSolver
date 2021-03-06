#pragma once
#include "GLhelper.h"

class VertexBuffer
{
private:
	unsigned int rendererID;
public:
	VertexBuffer(const void* bufferData, unsigned int size);
	~VertexBuffer();

	void Bind();
	void Unbind();
};

