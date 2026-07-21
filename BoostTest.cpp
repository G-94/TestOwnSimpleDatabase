#include "App.h"
#include "DatabaseManager.h"
#include <tuple>

int main(int argc, char* argv[]) {
	
#if false
	App app;
	if (app.start(argc, argv)) return 0;
#endif

	DB_manager db("test_db.txt");

#if true
	std::cout << db.load() << std::endl;
	std::cout << db.storage.open_table("users") << std::endl;
	db.storage.insert_row<std::vector<std::any>>("3", { "Vasilyi", 13, 560.0f });
#endif

#if false
	db.storage.add_table("users");
	db.storage.open_table("users");

	db.storage.add_col<std::string>("name");
	db.storage.add_col<int>("age");
	db.storage.add_col<float>("amount");

	db.storage.add_row("1");
	db.storage.insert_value<std::string>("1", "name", "Matvey");
	db.storage.insert_value<int>("1", "age", 16);
	db.storage.insert_value<float>("1", "amount", 350.50f);

	db.storage.insert_row<std::vector<std::any>>("2", {"Nikita", 22, 480.4f});
	db.storage.insert_value<int>("2", "age", 24);

	db.storage.add_table("second");
	db.storage.open_table("second");

	db.storage.add_col<std::string>("name");
	db.storage.add_col<int>("age");
	db.storage.add_col<float>("amount");

	db.storage.add_row("1");
	db.storage.insert_value<std::string>("1", "name", "Matvey");
	db.storage.insert_value<int>("1", "age", 16);
	db.storage.insert_value<float>("1", "amount", 350.50f);

	db.storage.insert_row<std::vector<std::any>>("2", { "Nikita", 22, 480.3f });
	db.storage.insert_value<int>("2", "age", 24);

#endif

	std::cout << db.save() << std::endl;

	return 0;
}