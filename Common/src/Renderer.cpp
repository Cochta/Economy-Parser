#include "Renderer.h"


void Renderer::Setup() {
	//goal_left_.Setup("minecraft_tnt.png", { 200, 200 }, Offset::DownLeft);

	parser.Setup();
	Loader loader;
	for (auto row : parser.Data)
	{
		MyImage image = loader.loadImage("Release/ressource/1.21.5/" + row[1], {Metrics::IMAGE_SIZE, Metrics::IMAGE_SIZE}, Offset::DownLeft);
		printf("%s\n", row[1].c_str());
		images.emplace(row[0], image);
	}

	maxHeight = images.size() * Metrics::IMAGE_SIZE + 10;
}

void Renderer::TearDown() {
	CloseWindow();
}

void Renderer::Draw(void) {
	BeginDrawing();
	{
		ClearBackground(GRAY);
		mousePos = GetMousePosition();

		float wheelMove = GetMouseWheelMove();
		if (wheelMove != 0.0f) {
			scroll -= wheelMove * 50;
		}
		// Clamp scroll value
		scroll = Clamp(scroll, 0.0f, maxHeight - Metrics::HEIGTH);

		int i = 0;
		float y = 0;

		for (auto data : parser.Data) {
			float imageY = 60 + y - scroll;

			Color rectColor = (i % 2 == 0) ? Color{ 245, 245, 220, 255 } : Color{ 84, 70, 58, 255 };

			// Draw background behind each image
			DrawRectangle(0, imageY, Metrics::WIDTH, Metrics::IMAGE_SIZE, rectColor);

			// Draw the image itself
			images.find(data[0])->second.Draw({ 0, imageY });

			//draw text
			Color textColor = (i % 2 == 0) ? BLACK : WHITE;
			DrawText(data[2].c_str(), 70, imageY + 20, kFontSize, textColor);
			DrawText(data[3].c_str(), 600, imageY + 20, kFontSize, textColor);
			DrawText(data[4].c_str(), 700, imageY + 20, kFontSize, textColor);
			

			y += Metrics::IMAGE_SIZE;
			i++;
		}

		DrawMenu();
		DrawScrollBar();
		//Draw
	}
	EndDrawing();
}


void Renderer::DrawMenu() {
	const float buttonWidth = 150.0f;
	const float buttonHeight = 40.0f;
	const float margin = 10.0f;

	const char* labels[] = { "Feur", "Poubelle", "Exit" };
	const int buttonCount = sizeof(labels) / sizeof(labels[0]);

	// Draw background bar
	DrawRectangle(0, 0, Metrics::WIDTH, 60, LIGHTGRAY); // or any color you like

	for (int i = 0; i < buttonCount; ++i) {
		float x = margin + i * (buttonWidth + margin);
		float y = 10.0f;

		Rectangle button = { x, y, buttonWidth, buttonHeight };

		// Hover color
		Color color = CheckCollisionPointRec(mousePos, button) ? DARKGRAY : GRAY;
		DrawRectangleRec(button, color);

		// Centered text
		int textWidth = MeasureText(labels[i], 20);
		DrawText(labels[i], x + buttonWidth / 2 - textWidth / 2, y + 10, 20, WHITE);

		// Handle click
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, button)) {
			switch (i) {
			case 0:
				// Handle Start Game
				TraceLog(LOG_INFO, "Feur Clicked");
				break;
			case 1:
				// Handle Settings
				TraceLog(LOG_INFO, "Poubelle Clicked");
				break;
			case 2:
				// Handle Exit
				CloseWindow(); // or trigger exit from game loop
				break;
			}
		}
	}
}

void Renderer::DrawScrollBar() {
	const float scrollbarWidth = 20.0f;

	if (maxHeight <= Metrics::HEIGTH) return; // No need to scroll

	float scrollbarHeight = Metrics::HEIGTH * (Metrics::HEIGTH / maxHeight);
	float scrollbarY = (scroll / (maxHeight - Metrics::HEIGTH)) * (Metrics::HEIGTH - scrollbarHeight);
	Rectangle scrollbar = { Metrics::WIDTH - scrollbarWidth, scrollbarY, scrollbarWidth, scrollbarHeight };

	// Start drag
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, scrollbar)) {
		isDragging = true;
		dragOffsetY = mousePos.y - scrollbarY;
	}

	// Continue drag
	if (isDragging) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			float newY = mousePos.y - dragOffsetY;
			newY = Clamp(newY, 0.0f, Metrics::HEIGTH - scrollbarHeight);
			scroll = (newY / (Metrics::HEIGTH - scrollbarHeight)) * (maxHeight - Metrics::HEIGTH);
		}
		else {
			isDragging = false;
		}
	}

	// Clamp scroll on wheel move (do this here so it applies to both wheel & drag)
	scroll = Clamp(scroll, 0.0f, maxHeight - Metrics::HEIGTH);

	// Draw scrollbar background
	DrawRectangle(Metrics::WIDTH - scrollbarWidth, 0, scrollbarWidth, Metrics::HEIGTH, LIGHTGRAY);

	// Draw thumb
	DrawRectangleRec(scrollbar, DARKGRAY);
}

