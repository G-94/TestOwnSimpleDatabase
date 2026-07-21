#include "DatabaseManager.h"

DB_manager::DB_manager(const std::string& database_dir_)
{
	database_dir = database_dir_;
	storage = database();
}

DB_manager::~DB_manager()
{}

bool DB_manager::load() noexcept
{
	try {
		database_file.open(database_dir, std::ios::in);

		if (!database_file.is_open()) {
			std::cerr << "ERROR WHILE OPENING: " << database_dir << std::endl;
			throw file_not_open();
		}

		std::string temp;

		//read tables name in cycle condition
		while (database_file >> temp) {
			storage.add_table(temp);
			if(!storage.open_table(temp)) return false;

			//ignore empty str
			std::getline(database_file, temp);

			//read table's cols
			std::getline(database_file, temp);
			boost::trim_left(temp);
			std::vector<std::string> columns_data;
			boost::split(columns_data, temp, boost::is_any_of(" \t:"), boost::token_compress_on);

			for (size_t i = 0; i + 1 < columns_data.size(); i += 2) {
				if(!storage.add_col(columns_data[i], set_type_by_string(columns_data[i + 1]))) return false;
			}

			size_t number_of_columns = columns_data.size();
			std::string row_name;

			//read data from rows
			while (database_file >> row_name && row_name != "---") {
				std::vector<std::any> added_data;
				size_t type_iter = 1;
				for (size_t i = 0; i < number_of_columns / 2; ++i) {
					if (type_iter >= number_of_columns) break;

					database_file >> temp;
					added_data.push_back(get_value_by_data(temp, columns_data[type_iter]));
					type_iter += 2;
				}

				if (!storage.insert_row<std::vector<std::any>>(row_name, added_data)) return false;
			}
		}

		database_file.close();
		return true;
	}
	catch (...) {
		database_file.close();
		return false;
	}
}

bool DB_manager::save() noexcept
{
	try {
		database_file.open(database_dir, std::ios::out | std::ios::trunc);

		if (!database_file.is_open()) {
			std::cerr << "ERROR WHILE OPENING: " << database_dir << std::endl;
			throw file_not_open();
		}

		for (const auto& [table_name, table] : storage) {
			storage.open_table(table_name);

			//write tables name in txt
			database_file << table_name << '\n';

			//write cols in txt
			auto columns = storage.get_column_order();
			if (columns == std::nullopt) return false;

			for (const auto& col : *columns) {
				auto type = storage.get_col_type(col.second);
				database_file << '\t' << col.second << " : ";
				if (type != std::nullopt) {
					database_file << *type;
				}
				else {
					database_file << "<unknown>";
				}
			}

			database_file << '\n';

			// write rows with data
			for (const auto& [row_name, data] : table) {
				database_file << row_name << "\t";
				for (const auto& [index, col_name] : *columns) {
					auto it = data.find(col_name);
					if (it != data.end()) {
						database_file << it->second << "\t\t";
					}
					else {
						database_file << "<NULL>\t";
					}
				}
				database_file << '\n';
			}

			database_file << "---\n";
		}

		database_file.close();
		return true;
	}
	catch (...) {
		database_file.close();
		return false;
	}
}

bool DB_manager::print_database()noexcept
{
	try {
		for (const auto& [table_name, table] : storage) {
			if (!storage.open_table(table_name)) return false;

			//write tables name in out
			std::cout << table_name << '\n';

			//write cols in out
			auto columns = storage.get_column_order();
			if (columns == std::nullopt) return false;

			for (const auto& col : *columns) {
				auto type = storage.get_col_type(col.second);
				std::cout << '\t' << col.second << " : ";
				if (type != std::nullopt) {
					std::cout << *type;
				}
				else {
					std::cout << "<unknown>";
				}
			}

			std::cout << '\n';

			// write rows with data in out
			for (const auto& [row_name, data] : table) {
				std::cout << row_name << "\t";
				for (const auto& [index, col_name] : *columns) {
					auto it = data.find(col_name);
					if (it != data.end()) {
						std::cout << it->second << "\t\t";
					}
					else {
						std::cout << "<NULL>\t";
					}
				}
				std::cout << '\n';
			}

			std::cout << "---\n";
		}

		return true;
	}
	catch (...) {
		return false;
	}
}

bool DB_manager::print_columns_data() noexcept
{
	try {
		auto columns = storage.get_column_order();
		if (columns == std::nullopt) return false;

		for (const auto& col : *columns) {
			auto type = storage.get_col_type(col.second);
			std::cout << '\t' << col.second << " : ";
			if (type != std::nullopt) {
				std::cout << *type;
			}
			else {
				std::cout << "<unknown>";
			}
		}

		std::cout << '\n';

		return true;
	}
	catch (...) {
		return false;
	}
}

std::any set_type_by_string(const std::string& type_name) noexcept
{
	if (type_name == "int") {
		return int();
	}
	else if (type_name == "double") {
		return double();
	}
	else if (type_name == "float") {
		return float();
	}
	else if (type_name == "string") {
		return std::string();
	}
	else if (type_name == "bool") {
		return bool();
	}
	else {
		return std::string();
	}
}

std::any get_value_by_data(const std::string& data, const std::string& type_name)
{
	if (type_name == "int") {
		return stoi(data);
	}
	else if (type_name == "double") {
		return stod(data);
	}
	else if (type_name == "float") {
		return stof(data);
	}
	else if (type_name == "string") {
		return data;
	}
	else if (type_name == "bool") {
		return (data == "true") ? true : false;
	}
	else {
		return "NULL";
	}
}
