#include "Renderer.h"

int main() {
	// Initialize the window
	InitWindow(Metrics::WIDTH, Metrics::HEIGTH, "Ouais");
	SetTargetFPS(30);

	// Create a Renderer object
	Renderer renderer;
	renderer.Setup();

	// Main game loop
	while (!WindowShouldClose()) {
		renderer.Draw();
	}
	// Clean up
	renderer.TearDown();
	return 0;
}