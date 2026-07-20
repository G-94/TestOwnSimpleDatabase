#include "DatabaseManager.h"

DB_manager::DB_manager(const std::string& database_dir)
{
	database_file.open(database_dir, std::ios::out | std::ios::trunc | std::ios::in);

	if (!database_file.is_open()) {
		std::cerr << "ERROR WHILE OPENING: " << database_dir << std::endl;
		throw file_not_open();
	}

	storage = database();
}

DB_manager::~DB_manager()
{
	database_file.close();
}

bool DB_manager::load() noexcept
{



	return false;
}

bool DB_manager::save() noexcept
{
	try {
		for (const auto& [table_name, table] : storage) {
			storage.open_table(table_name);

			//запись названия таблицы в txt
			database_file << table_name << '\n';

			//запись колонок в txt
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

			// запись row с данными
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

			database_file << '\n';
		}

		return true;
	}
	catch (...) {
		return false;
	}
}
