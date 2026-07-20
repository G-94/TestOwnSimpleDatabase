#pragma once

#include <iostream>
#include <fstream>
#include <exception>
#include <boost/program_options.hpp>

#include "Log_t.h"
#include "AppExceptions.h"

#define USERS_DATA_DIR "users.txt"
#define ADMIN_PASSWORD "8888"

namespace opt = boost::program_options;

class access_locker {
private:
	std::fstream users_data;

	bool get_access(const std::string& username, const std::string& password);
	void add_user(const std::string& username, const std::string& password);

public:
	access_locker();
	~access_locker();

	bool request_access_to_DB(const opt::variables_map& vm);
};

