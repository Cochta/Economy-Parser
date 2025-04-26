#pragma once
#include <string>
#include <iostream>
#include <raylib.h>
#include "MyImage.h"
#include <vector>
#include "Parser.h"
#include "raymath.h"
#include <map>
#include <fmt/core.h>

using namespace Metrics;

class Renderer {
public:
	Parser parser;

	std::map<std::string,MyImage> images{};


	float maxHeight = Metrics::HEIGTH;

	Vector2 mousePos = { 0,0 };

	float scroll = 0.0f;

	// Scrollbar state
	bool isDragging = false;
	float dragOffsetY = 0.0f;

	void Setup();

	void TearDown();

	void Draw(void);
	void DrawMenu();
	void DrawScrollBar();
	void DrawHeader();

};