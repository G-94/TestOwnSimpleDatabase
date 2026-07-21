#include "App.h"

bool App::execute_command(std::string command_line) noexcept
{
	try {
		//split line to keywords and data
		boost::trim_left(command_line);
		std::vector<std::string> splitted_line;
		boost::split(splitted_line, command_line, boost::is_any_of(" \t"), boost::token_compress_on);

		std::string main_command = splitted_line.at(0);

		if (main_command == "ADD_TABLE") {
			bool is_operation_done = manager.storage.add_table(splitted_line.at(1));
			if (!is_operation_done) return false;
		}
		else if (main_command == "OPEN_TABLE") {
			bool is_operation_done = manager.storage.open_table(splitted_line.at(1));
			if (!is_operation_done) return false;
		}
		else if (main_command == "LOAD_DB") {
			bool is_operation_done = manager.load();
			if (!is_operation_done) return false;
		}
		else if (main_command == "SAVE_DB") {
			bool is_operation_done = manager.save();
			if (!is_operation_done) return false;
		}
		else if (main_command == "PRINT_DB") {
			bool is_operation_done = manager.print_database();
			if (!is_operation_done) return false;
		}
		else if (main_command == "ADD_COL") {
			bool is_operation_done = manager.storage.add_col(splitted_line.at(1), set_type_by_string(splitted_line.at(2)));
			if (!is_operation_done) return false;
		}
		else if (main_command == "ADD_ROW") {
			bool is_operation_done = manager.storage.add_row(splitted_line.at(1));
			if (!is_operation_done) return false;
		}
		else if (main_command == "DELETE_TABLE") {
			bool is_operation_done = manager.storage.delete_table(splitted_line.at(1));
			if (!is_operation_done) return false;
		}
		else if (main_command == "REMOVE_ROW") {
			bool is_operation_done = manager.storage.remove_row(splitted_line.at(1));
			if (!is_operation_done) return false;
		}
		else if (main_command == "REMOVE_COL") {
			bool is_operation_done = manager.storage.remove_col(splitted_line.at(1));
			if (!is_operation_done) return false;
		}
		else if (main_command == "CURRENT_TABLE") {
			std::cout << manager.storage.get_current_table_name() << std::endl;
		}
		else if (main_command == "GET_ROW") {
			const std::string& key = splitted_line.at(1);
			auto row = manager.storage.get_row(key);
			if (row == std::nullopt) return false;

			bool is_operation_done = manager.print_columns_data();
			if (!is_operation_done) return false;

			std::cout << key;
			for (const auto& value : *row) {
				std::cout << "\t\t" << value;
			}
			std::cout << std::endl;
		}
		else if (main_command == "GET_ROW_IF") {
			std::string col_name = splitted_line.at(1);
			std::string sign = splitted_line.at(2);
			std::string operand = splitted_line.at(3);

			auto col_type = manager.storage.get_col_type(col_name);
			if (col_type == std::nullopt) return false;

			std::function<bool(const std::any& value)> pred = get_operator_func(sign, get_value_by_data(operand, *col_type));
			auto rows = manager.storage.get_rows_if(col_name, pred);
			if (rows == std::nullopt) return false;

			bool is_operation_done = manager.print_columns_data();
			if (!is_operation_done) return false;

			for (const auto& [row_name, row_data] : *rows) {
				std::cout << row_name;
				for (const auto& value : row_data) {
					std::cout << "\t\t" << value;
				}
				std::cout << '\n';
			}
		}
		else if (main_command == "GET_VAL") {
			std::string key = splitted_line.at(1);
			std::string col = splitted_line.at(2);

			auto value = manager.storage.get(key, col);
			if (value == std::nullopt) return false;
			std::cout << *value << std::endl;
		}
		else if (main_command == "GET_COL_TYPE") {
			std::string col = splitted_line.at(1);

			auto result = manager.storage.get_col_type(col);
			if (result == std::nullopt) return false;
			std::cout << *result << std::endl;
		}
		else if (main_command == "INSERT_VALUE") {
			std::string key = splitted_line.at(1);
			std::string col = splitted_line.at(2);
			std::string value = splitted_line.at(3);

			auto col_type = manager.storage.get_col_type(col);
			if (col_type == std::nullopt) return false;

			bool is_operation_done = manager.storage.insert_value(key, col, get_value_by_data(value, *col_type));
			if (!is_operation_done) return false;
		}
		else if (main_command == "INSERT_ROW") {
			std::string key = splitted_line.at(1);
			std::vector<std::any> added_data;

			auto cols_data = manager.storage.get_column_order();
			if (cols_data == std::nullopt) return false;

			auto data_it = splitted_line.begin() + 2;
			auto cols_data_it = (*cols_data).begin();

			while (data_it != splitted_line.end()) {
				auto col_type = manager.storage.get_col_type((*cols_data_it).second);
				if (col_type == std::nullopt) return false;
				added_data.push_back(get_value_by_data(*data_it, *col_type));

				++cols_data_it;
				++data_it;
			}

			bool is_operation_done = manager.storage.insert_row(key, added_data);
			if (!is_operation_done) return false;
		}
		else {
			return false;
		}

		return true;
	}
	catch (...) {
		return false;
	}
}

int App::start(int argc, char* argv[])
{
	opt::options_description desc("Students Exam DB programm params");

	desc.add_options()
		("user", opt::value<std::string>()->required(), "Username of DB editor")
		("password", opt::value<std::string>()->required(), "Password of user")
		("admin", opt::value<std::string>(), "Open the DB like admin. Unlock some functions")
		("create_user", "create new user of DB")
		("help", "Show all programm options")
		;

	opt::variables_map vm;
	opt::store(opt::parse_command_line(argc, argv, desc), vm);

	if (vm.count("help")) {
		std::cout << desc << std::endl;
		return 0;
	}

	opt::notify(vm);

	access_locker ac_loc;

	try {
		bool is_logged_in = ac_loc.request_access_to_DB(vm);
		if (!is_logged_in) {
			std::cout << "Failed to log in DB. Wrong username or password!" << std::endl;
			return 1;
		}
		else {
			std::cout << "Welcome " << vm["user"].as<std::string>() << "!" << std::endl;
		}
	}
	catch (const std::exception& ex) {
		std::cout << "Failed to log in DB. Crash error" << std::endl;
		std::cerr << ex.what() << std::endl;
		return 1;
	}

	return 0;
}

int App::exec()
{
	while (true) {
		std::string command;
		std::getline(std::cin, command);

		if (command == "CLOSE") {
			break;
		}

		if (!execute_command(command)) {
			logger.write("SOMETHING WENT WRONG WHILE DOING: " + command);
			std::cout << "Something went wrong. Check the command and try again." << std::endl;
		}
		else {
			logger.write("SUCCESSFULY DONE: " + command);
		}
	}

	return 0;
}
