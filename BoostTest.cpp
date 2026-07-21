#include "App.h"
#include "DatabaseManager.h"
#include <tuple>

int main(int argc, char* argv[]) {

	App app;
	if (app.start(argc, argv)) return 1;
	app.exec();

	return 0;
}