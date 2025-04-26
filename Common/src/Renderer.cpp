#include "Renderer.h"


void Renderer::Setup() {
	parser.Setup();
	Loader loader;
	for (auto& item : parser.AllItems)
	{
		MyImage image = loader.loadImage("Release/ressource/1.21.5/" + item.ImagePath, { IMAGE_SIZE, IMAGE_SIZE }, Offset::TopLeft);
		images.emplace(item.Id, image);
	}
}

void Renderer::TearDown() {
	CloseWindow();
}

void Renderer::Draw(void) {
	BeginDrawing();
	{
		ClearBackground(GRAY);
		mousePos = GetMousePosition();

		int i = 0;
		float y = 0;

		maxHeight = HEADER_HEIGHT + MENU_HEIGHT;

		for (auto& item : parser.AllItems) {
			if (!item.IsValid())
			{
				continue;
			}
			if (item.Name.find(parser.SearchText) == std::string::npos)
			{
				continue;
			}
			maxHeight += IMAGE_SIZE;

			float imageY = MENU_HEIGHT + HEADER_HEIGHT + y - scroll;

			Color rectColor = (i % 2 == 0) ? Color{ 245, 245, 220, 255 } : Color{ 210, 180, 140, 255 };

			// Draw background behind text
			DrawRectangle(0, imageY, WIDTH, IMAGE_SIZE, rectColor);
			// Draw black border around the rectangle
			DrawRectangleLinesEx({ 0, imageY, WIDTH, IMAGE_SIZE }, 2.0f, BLACK);
			//DrawRectangleLines(0, imageY, WIDTH, IMAGE_SIZE, BLACK);

			// Draw background behind each image
			DrawRectangle(0, imageY, IMAGE_SIZE + MARGIN * 2, IMAGE_SIZE, DARKGRAY);
			// Draw black border around the rectangle
			DrawRectangleLinesEx({ 0, imageY, IMAGE_SIZE + MARGIN * 2, IMAGE_SIZE }, 2.0f, BLACK);

			// Draw the image itself
			images.find(item.Id)->second.Draw({ MARGIN, imageY });
			//draw text
			DrawText(item.Name.c_str(), MARGIN + NAME_OFFSET, imageY + MARGIN * 1.8f, FONT_SIZE, BLACK);
			DrawText(std::to_string(item.Quantity).c_str(), MARGIN + NAME_OFFSET + NAME_WIDTH, imageY + MARGIN * 1.8f, FONT_SIZE, BLACK);
			DrawText(std::to_string(item.Price).c_str(), MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH, imageY + MARGIN * 1.8f, FONT_SIZE, BLACK);


			// Checkbox position
			float checkboxSize = 20;
			float checkboxX = MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH * 2;
			float checkboxY = imageY + MARGIN * 1.8f;

			// Mouse check
			Rectangle checkboxRect = { checkboxX, checkboxY, checkboxSize, checkboxSize };
			bool hovered = CheckCollisionPointRec(GetMousePosition(), checkboxRect);

			// Draw checkbox background
			DrawRectangleRec(checkboxRect, hovered ? LIGHTGRAY : GRAY);

			// If checked, draw checkmark
			if (item.IsStackable)
			{
				DrawLineEx({ checkboxX + 4, checkboxY + 4 }, { checkboxX + checkboxSize - 4, checkboxY + checkboxSize - 4 }, 3.f, BLACK);
				DrawLineEx({ checkboxX + 4, checkboxY + checkboxSize - 4 }, { checkboxX + checkboxSize - 4, checkboxY + 4 }, 3.f, BLACK);
			}

			// Handle click
			if (hovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				item.IsStackable = !item.IsStackable;
				item.Parse();
			}
			std::string stackText;
			if (std::floor(item.StackPrice) == item.StackPrice)
			{
				stackText = fmt::format("{}", static_cast<int>(item.StackPrice)); // no decimals
			}
			else
			{
				stackText = fmt::format("{:.1f}", item.StackPrice); // 2 decimals
			}
			std::string shulkerText;
			if (std::floor(item.ShulkerPrice) == item.ShulkerPrice)
			{
				shulkerText = fmt::format("{}", static_cast<int>(item.ShulkerPrice)); // no decimals
			}
			else
			{
				shulkerText = fmt::format("{:.1f}", item.ShulkerPrice); // 2 decimals
			}
			std::string dcText;
			if (std::floor(item.DCPrice) == item.DCPrice)
			{
				dcText = fmt::format("{}", static_cast<int>(item.DCPrice)); // no decimals
			}
			else
			{
				dcText = fmt::format("{:.1f}", item.DCPrice); // 2 decimals
			}
			DrawText(stackText.c_str(), MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH * 3, imageY + MARGIN * 1.8f, FONT_SIZE, BLACK);
			DrawText(shulkerText.c_str(), MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH * 4, imageY + MARGIN * 1.8f, FONT_SIZE, BLACK);
			DrawText(dcText.c_str(), MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH * 5, imageY + MARGIN * 1.8f, FONT_SIZE, BLACK);

			y += IMAGE_SIZE;
			i++;
		}

		float wheelMove = GetMouseWheelMove();
		if (wheelMove != 0.0f) {
			scroll -= wheelMove * IMAGE_SIZE;
		}
		// Clamp scroll value
		scroll = Clamp(scroll, 0.0f, maxHeight - HEIGTH);

		DrawMenu();
		DrawScrollBar();
		DrawHeader();
		//Draw
	}
	EndDrawing();
}


void Renderer::DrawMenu() {

	static bool textBoxActive = false;

	// Draw background bar
	DrawRectangle(0, 0, WIDTH, 60, LIGHTGRAY);
	DrawRectangleLinesEx({ 0, 0, WIDTH, 60 }, 2.0f, BLACK);

	// Draw text box
	Rectangle textBox = { MARGIN * 3 + IMAGE_SIZE, MARGIN, TEXTBOX_WIDTH, MENU_HEIGHT - MARGIN * 2 };
	DrawRectangleRec(textBox, textBoxActive ? DARKGRAY : GRAY);
	DrawText(parser.SearchText, textBox.x + 5, textBox.y + 5, FONT_SIZE, BLACK);
	DrawRectangleLinesEx(textBox, 1.0f, BLACK);

	// Click detection for text box
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		textBoxActive = CheckCollisionPointRec(mousePos, textBox);
	}

	// Handle input
	if (textBoxActive) {
		int key = GetCharPressed();
		while (key > 0) {
			if (key >= 32 && key <= 125 && strlen(parser.SearchText) < sizeof(parser.SearchText) - 1) {
				size_t len = strlen(parser.SearchText);
				parser.SearchText[len] = (char)key;
				parser.SearchText[len + 1] = '\0';
			}
			key = GetCharPressed();
		}

		if (IsKeyPressed(KEY_BACKSPACE)) {
			size_t len = strlen(parser.SearchText);
			if (len > 0) parser.SearchText[len - 1] = '\0';
		}
	}

	// Exit button
	float exitX = WIDTH - BUTTON_WIDTH - SCROLLBAR_WIDTH - MARGIN;
	Rectangle exitBtn = { exitX, MARGIN, BUTTON_WIDTH, BUTTON_HEIGHT };
	Color exitColor = CheckCollisionPointRec(mousePos, exitBtn) ? DARKGRAY : GRAY;
	DrawRectangleRec(exitBtn, exitColor);
	DrawText("Exit", exitBtn.x + 20, exitBtn.y + 10, 20, WHITE);

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, exitBtn)) {
		CloseWindow();
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
	DrawRectangleLinesEx({ WIDTH - SCROLLBAR_WIDTH, 0, SCROLLBAR_WIDTH, HEIGTH }, 2.0f, BLACK); // Draw border

	// Draw thumb
	DrawRectangleRec(scrollbar, DARKGRAY);
	DrawRectangleLinesEx(scrollbar, 2.0f, BLACK); // Draw border
}

void Renderer::DrawHeader()
{
	// Draw background bar
	DrawRectangle(0, 60, WIDTH - SCROLLBAR_WIDTH, HEADER_HEIGHT, BLACK); // or any color you like

	DrawText("Items", MARGIN * 0.5, MENU_HEIGHT + MARGIN * 0.6, FONT_SIZE * 0.6, WHITE);
	DrawText("Name", MARGIN + NAME_OFFSET, MENU_HEIGHT + MARGIN * 0.6, FONT_SIZE * 0.6, WHITE);
	DrawText("Quantity", MARGIN + NAME_OFFSET + NAME_WIDTH, MENU_HEIGHT + MARGIN * 0.6, FONT_SIZE * 0.6, WHITE);
	DrawText("Price", MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH, MENU_HEIGHT + MARGIN * 0.6, FONT_SIZE * 0.6, WHITE);
	DrawText("Stackable", MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH * 2, MENU_HEIGHT + MARGIN * 0.6, FONT_SIZE * 0.6, WHITE);
	DrawText("Stack", MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH * 3, MENU_HEIGHT + MARGIN * 0.6, FONT_SIZE * 0.6, WHITE);
	DrawText("Shulker", MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH * 4, MENU_HEIGHT + MARGIN * 0.6, FONT_SIZE * 0.6, WHITE);
	DrawText("DC", MARGIN + NAME_OFFSET + NAME_WIDTH + ECONOMY_WIDTH * 5, MENU_HEIGHT + MARGIN * 0.6, FONT_SIZE * 0.6, WHITE);
}