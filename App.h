#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <boost/program_options.hpp>

#include "ParamsReader.h"
#include "Log_t.h"
#include "AppExceptions.h"

#define USERS_DATA_DIR "users.txt"
#define LOG_DIR "log.txt"
#define ADMIN_PASSWORD "8888"

namespace opt = boost::program_options;

class App {
private:

public:

	App();

	int start(int argc, char* argv[]);

	int exec();


};