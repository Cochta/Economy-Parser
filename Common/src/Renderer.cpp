#include "Renderer.h"


void Renderer::Setup() {
	parser.Setup();
	Loader loader;
	for (auto row : parser.Data)
	{
		MyImage image = loader.loadImage("Release/ressource/1.21.5/" + row[1], { IMAGE_SIZE, IMAGE_SIZE }, Offset::TopLeft);
		images.emplace(row[0], image);
	}

	maxHeight = images.size() * IMAGE_SIZE + HEADER_HEIGHT + MENU_HEIGHT;
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
			scroll -= wheelMove * IMAGE_SIZE;
		}
		// Clamp scroll value
		scroll = Clamp(scroll, 0.0f, maxHeight - HEIGTH);

		int i = 0;
		float y = 0;

		for (auto data : parser.Data) {
			float imageY = MENU_HEIGHT + HEADER_HEIGHT + y - scroll;

			Color rectColor = (i % 2 == 0) ? Color{ 245, 245, 220, 255 } : Color{ 84, 70, 58, 255 };

			// Draw background behind text
			DrawRectangle(0, imageY, WIDTH, IMAGE_SIZE, rectColor);

			// Draw background behind each image
			DrawRectangle(0, imageY, IMAGE_SIZE + MARGIN * 2, IMAGE_SIZE, DARKGRAY);

			// Draw the image itself
			images.find(data[0])->second.Draw({ MARGIN, imageY });

			//draw text
			Color textColor = (i % 2 == 0) ? BLACK : WHITE;
			DrawText(data[2].c_str(), MARGIN + NAME_OFFSET, imageY + MARGIN * 1.8f, kFontSize, textColor);
			DrawText(data[3].c_str(), MARGIN + NAME_OFFSET + NAME_WIDTH, imageY + MARGIN * 1.8f, kFontSize, textColor);
			DrawText(data[4].c_str(), MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH, imageY + MARGIN * 1.8f, kFontSize, textColor);


			y += IMAGE_SIZE;
			i++;
		}

		DrawMenu();
		DrawScrollBar();
		DrawHeader();
		//Draw
	}
	EndDrawing();
}


void Renderer::DrawMenu() {

	const float margin = 10.0f;

	const char* labels[] = { "Feur", "Poubelle", "Exit" };
	const int buttonCount = sizeof(labels) / sizeof(labels[0]);

	// Draw background bar
	DrawRectangle(0, 0, WIDTH, 60, LIGHTGRAY); // or any color you like

	for (int i = 0; i < buttonCount; ++i) {
		float x = margin + i * (BUTTON_WIDTH + margin);
		float y = 10.0f;

		Rectangle button = { x, y, BUTTON_WIDTH, BUTTON_HEIGHT };

		// Hover color
		Color color = CheckCollisionPointRec(mousePos, button) ? DARKGRAY : GRAY;
		DrawRectangleRec(button, color);

		// Centered text
		int textWidth = MeasureText(labels[i], 20);
		DrawText(labels[i], x + BUTTON_WIDTH / 2 - textWidth / 2, y + 10, 20, WHITE);

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

	if (maxHeight <= HEIGTH) return; // No need to scroll

	float scrollbarHeight = HEIGTH * (HEIGTH / maxHeight);
	float scrollbarY = (scroll / (maxHeight - HEIGTH)) * (HEIGTH - scrollbarHeight);
	Rectangle scrollbar = { WIDTH - SCROLLBAR_WIDTH, scrollbarY, SCROLLBAR_WIDTH, scrollbarHeight };

	// Start drag
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, scrollbar)) {
		isDragging = true;
		dragOffsetY = mousePos.y - scrollbarY;
	}

	// Continue drag
	if (isDragging) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			float newY = mousePos.y - dragOffsetY;
			newY = Clamp(newY, 0.0f, HEIGTH - scrollbarHeight);
			scroll = (newY / (HEIGTH - scrollbarHeight)) * (maxHeight - HEIGTH);
		}
		else {
			isDragging = false;
		}
	}

	// Clamp scroll on wheel move (do this here so it applies to both wheel & drag)
	scroll = Clamp(scroll, 0.0f, maxHeight - HEIGTH);

	// Draw scrollbar background
	DrawRectangle(WIDTH - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, HEIGTH, LIGHTGRAY);

	// Draw thumb
	DrawRectangleRec(scrollbar, DARKGRAY);
}

void Renderer::DrawHeader()
{
	// Draw background bar
	DrawRectangle(0, 60, WIDTH - SCROLLBAR_WIDTH, HEADER_HEIGHT, BLACK); // or any color you like

	DrawText("Items", MARGIN * 0.5, MENU_HEIGHT + MARGIN * 0.6, kFontSize * 0.6, WHITE);
	DrawText("Name", MARGIN + NAME_OFFSET, MENU_HEIGHT + MARGIN * 0.6, kFontSize * 0.6, WHITE);
	DrawText("Quantity", MARGIN + NAME_OFFSET + NAME_WIDTH, MENU_HEIGHT + MARGIN * 0.6, kFontSize * 0.6, WHITE);
	DrawText("Price", MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH, MENU_HEIGHT + MARGIN * 0.6, kFontSize * 0.6, WHITE);
}

