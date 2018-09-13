#include "NotSoSupaCirclagonApp.h"

int main() {
	
	// allocation
	auto app = new NotSoSupaCirclagonApp();

	// initialise and loop
	app->run("AIE", 720, 720, false);

	// deallocation
	delete app;

	return 0;
}