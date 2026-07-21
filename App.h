#pragma once

#include <iostream>
#include <fstream>
#include <exception>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>

#include "ParamsReader.h"
#include "Log_t.h"
#include "AppExceptions.h"
#include "DatabaseManager.h"
#include "operator_func_cast.hpp"

#define USERS_DATA_DIR "users.txt"
#define DB_DIR "main_database.txt"
#define LOG_DIR "log.txt"
#define ADMIN_PASSWORD "8888"

namespace opt = boost::program_options;

class App {
private:

	DB_manager manager;
	log_t logger;

	bool execute_command(std::string command_line) noexcept;

public:

	App() : manager(DB_DIR), logger(LOG_DIR) {}

	int start(int argc, char* argv[]);

	int exec();


};