#pragma once

#include <fstream>
#include <iostream>

#include "AppExceptions.h"

#define LOG_DIR "log.txt"

class log_t {
private:
	std::fstream log_file;

public:

	log_t(const std::string& dir);
	~log_t();

	void write(const std::string& info);
};