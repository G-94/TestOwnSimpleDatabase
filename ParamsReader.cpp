#include "ParamsReader.h"

bool access_locker::get_access(const std::string& username, const std::string& password)
{
	users_data.clear();
	users_data.seekg(0, std::ios::beg);

	std::string existed_username;
	while (users_data >> existed_username) {
		std::string existed_password;
		users_data >> existed_password;

		try {
			if (username == existed_username && password == existed_password) {
				return true;
			}
		}
		catch (const std::exception& ex) {
			std::cerr << "ERORR WHILE SCANNING USER DATA: " << ex.what() << std::endl;
		}
	}

	return false;
}

void access_locker::add_user(const std::string& username, const std::string& password)
{
	std::string new_data = username + " " + password;
	users_data << new_data << std::endl;
}

access_locker::access_locker()
{
	users_data.open(USERS_DATA_DIR, std::ios::app | std::ios::in);

	if (!users_data.is_open()) {
		std::cerr << "ERROR WHILE OPENING: " << USERS_DATA_DIR << std::endl;
		throw file_not_open();
	}
}

access_locker::~access_locker()
{
	users_data.close();
}

bool access_locker::request_access_to_DB(const opt::variables_map& vm)
{
	std::string username, password;

	log_t log_file(LOG_DIR);

	try {
		username = vm["user"].as<std::string>();
		password = vm["password"].as<std::string>();
	}
	catch (const std::exception& ex) {
		std::cerr << "ERROR WHILE GETTING DATA FROM PROGRAMM PARAMS" << std::endl;
		return false;
	}

	if (vm.count("create_user")) {
		if (!vm.count("admin") || vm["admin"].as<std::string>() != ADMIN_PASSWORD) {
			std::cerr << "TRYING CREATE USER WITHOUT ADMIN RIGHTS" << std::endl;
			return false;
		}

		try {
			if (get_access(username, password)) {
				log_file.write("SUCCESSFUL LOGIN BY " + username);
			}
			else {
				add_user(username, password);
				log_file.write("SUCCESSFUL OF CREATING NEW USER: " + username);
			}

			return true;
		}
		catch (const std::exception& ex) {
			std::cerr << "ERORR WHILE CREATING USER: " << ex.what() << std::endl;
			return false;
		}
	}

	if (get_access(username, password)) {
		log_file.write("SUCCESSFUL LOGIN BY " + username);
		return true;
	}
	
	log_file.write("UNSUCCESSFUL LOGIN BY " + username);
	return false;
}
