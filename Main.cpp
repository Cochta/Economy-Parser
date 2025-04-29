#include "Renderer.h"

#ifdef PLATFORM_WEB
#include "emscripten/emscripten.h"
#endif // PLATFORM_WEB

// Update and Draw one frame
void UpdateDrawFrame(void* renderer) {
	static_cast<Renderer*>(renderer)->Draw();
}

int main() {
	// Create a Renderer object
	Renderer renderer;
	renderer.Setup();

#ifdef PLATFORM_WEB
	emscripten_set_main_loop_arg(UpdateDrawFrame, &renderer, 0, 1);

#else
	// Main game loop
	while (!WindowShouldClose()) {
		renderer.Draw();
	}
#endif
	// Clean up
	renderer.TearDown();
	return 0;
}