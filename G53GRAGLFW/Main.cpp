#include "Engine.h"
//Main method, create an engine, run it, delete it, return
int main(int argc, char ** argv) {
	Engine * mEngine = new Engine();
	mEngine->Run();
	delete mEngine;
	return 0;
}