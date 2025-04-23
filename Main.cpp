#include "Renderer.h"
#include "Parser.h"
#include "FileSytem.h"
#include "metrics.h"

int main() {
	// Initialize the window
	InitWindow(Metrics::WIDTH, Metrics::HEIGTH, "Ouais");
	SetTargetFPS(30);
	// Create a Renderer object
	Renderer renderer;
	

	Reader reader;
	auto data = reader.readCSV("Release/Data/1.21.5.csv");
	Loader loader;
	for (const auto& row : data) {
		if (row.size() >= 4) {
			std::string imagePath = row[0];
			std::string name = row[1];
			std::string quantity = row[2];
			std::string price = row[3];
			// Load the image using the Loader class
			MyImage image = loader.loadImage("Release/ressource/1.21.5/"+imagePath, {Metrics::IMAGE_SIZE, Metrics::IMAGE_SIZE }, Offset::DownLeft);
			renderer.images.push_back(image);
		}
	}
	renderer.Setup();


	// Main game loop
	while (!WindowShouldClose()) {
		renderer.Draw();
	}
	// Clean up
	renderer.TearDown();
	CloseWindow();
	return 0;
}