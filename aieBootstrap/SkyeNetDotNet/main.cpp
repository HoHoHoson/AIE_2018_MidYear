#include "SkyeNetDotNetApp.h"

int main() {
	
	// allocation
	auto app = new SkyeNetDotNetApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}