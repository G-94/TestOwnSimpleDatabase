#include "App.h"

App::App()
{}

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
			return 0;
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
	return 0;
}
