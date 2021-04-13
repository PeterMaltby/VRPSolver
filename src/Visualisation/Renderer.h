#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "GL/glew.h"

//GL related helpers
#include "shader.h"
#include "GLhelper.h"
#include "Layer.h"

class Renderer {
private:
	Shader shader = Shader("resources/shaders/BasicVertex.Shader", "resources/shaders/BasicFragment.Shader");
	
	//Background data
	float bgvertex[8] = { -1.0f,-1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f,-1.0f };
	Layer background = Layer(&shader, bgvertex, sizeof(float) * 8);

	unsigned int bgindex[6] = { 0,1,2,0,2,3 };
	Color white{ 1.0f,0.0f,0.0f,1.0f };
	DrawProp backgroundProp = DrawProp(bgindex, 6, GL_TRIANGLES, white, 1);

	Layer* points;

	std::vector<DrawProp> pointsProperties;
	std::vector<DrawProp> linesProperties;
public:
	Renderer(std::vector<double> points, Color bgC = { 1.0f,1.0f,1.0f,1.0f });
	~Renderer();
	/*
	void pointsProperties(std::vector<unsigned int>, Color color, float scale);
	void pointsPropertiesClear();

	void AddLine(std::vector<unsigned int>, Color color, float scale);
	void LinesClear();
	*/
	void Draw();
};