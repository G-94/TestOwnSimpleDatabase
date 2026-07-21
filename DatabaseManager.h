#pragma once

#include <iostream>
#include <fstream>
#include <optional>
#include <any>

#include <boost/type_index.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

#include "Log_t.h"
#include "AppExceptions.h"
#include "OwnDB.h"

std::any set_type_by_string(const std::string& type_name) noexcept;
std::any get_value_by_data(const std::string& data, const std::string& type_name);

class DB_manager {
private:

	std::fstream database_file;
	std::string database_dir;

public:

	database storage;

	DB_manager(const std::string& database_dir_);
	~DB_manager();

	bool load() noexcept;
	bool save() noexcept;

	bool print_database() noexcept;
	bool print_columns_data() noexcept;

};


