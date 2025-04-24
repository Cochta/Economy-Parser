#pragma once
#include <string>
#include <iostream>
#include <raylib.h>
#include "MyImage.h"
#include <vector>
#include "Parser.h"
#include "raymath.h"
#include <map>

class Network;

class Renderer {
public:
	Parser parser;
	static constexpr int kFontSize = 30;
	std::map<std::string,MyImage> images{};


	float maxHeight = Metrics::HEIGTH;

	Vector2 mousePos = { 0,0 };

	// Scrollbar sizing
	float scrollbarWidth = 20.0f;
	float scrollbarHeight = Metrics::HEIGTH * (Metrics::HEIGTH / maxHeight);
	float scrollbarY = (scroll / (maxHeight - Metrics::HEIGTH)) * (Metrics::HEIGTH - scrollbarHeight);
	Rectangle scrollbar = { Metrics::WIDTH - scrollbarWidth, scrollbarY, scrollbarWidth, scrollbarHeight };

	float scroll = 0.0f;

	// Scrollbar state
	bool isDragging = false;
	float dragOffsetY = 0.0f;

	void Setup();

	void TearDown();

	void Draw(void);
	void DrawMenu();
	void DrawScrollBar();

};