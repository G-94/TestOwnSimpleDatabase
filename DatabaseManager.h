#pragma once

#include <iostream>
#include <fstream>
#include <optional>
#include <any>

#include <boost/type_index.hpp>

#include "Log_t.h"
#include "AppExceptions.h"
#include "OwnDB.h"

class DB_manager {
private:

	std::fstream database_file;

public:

	database storage;

	DB_manager(const std::string& database_dir);
	~DB_manager();

	bool load() noexcept;
	bool save() noexcept;

};