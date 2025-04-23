#pragma once
#include <raylib.h>

enum class Offset {
	Center,
	TopLeft,
	TopRight,
	DownLeft,
	DownRight,
	DownCenter,
	BackGround
};
class MyImage {
public:
	Texture2D tex;
	Vector2 pos;
	Vector2 origin;
	Rectangle source;
	Rectangle dest;

	void Setup(const char* path, Vector2 size, Offset = Offset::Center);
	void TearDown();
	void Draw(Vector2 position, float rotation = 0);
};