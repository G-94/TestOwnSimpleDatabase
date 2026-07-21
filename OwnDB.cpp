#include "OwnDB.h"

bool database::is_table_open() const noexcept
{
	return (!current_table.empty() && storage.find(current_table) != storage.end());
}

bool database::is_row_exists(const std::string& row) const noexcept
{
	if (!is_table_open()) return false;
	return (storage.at(current_table).find(row) != storage.at(current_table).end());
}

bool database::is_col_exists(const std::string& col) const noexcept
{
	if (!is_table_open()) return false;
	auto it = schema.find(current_table);
	if (it == schema.end()) return false;
	const auto& cols = it->second;
	return boost::range::find_if(cols, [&](const auto& pair) {
		return pair.first == col;
		}) != cols.end();
}

bool database::add_table(const std::string& table_name) noexcept
{
	try {
		storage.emplace(table_name, Table_t());
		schema.emplace(table_name, Table_schema_t());
		return true;
	}
	catch (...) {
		return false;
	}
}

bool database::add_row(const std::string& row_name) noexcept
{
	if (!is_table_open()) return false;

	try {
		if (is_row_exists(row_name)) return false;
		
		Row_t new_row;

		for (const auto& [col_name, value] : schema[current_table]) {
			new_row.emplace(col_name, value);
		}

		storage[current_table].emplace(row_name, std::move(new_row));
		return true;
	}
	catch (...) {
		return false;
	}
}

bool database::open_table(const std::string& table_name) noexcept
{
	if (storage.find(table_name) == storage.end()) return false;

	try {
		current_table = table_name;
		return true;
	}
	catch (...) {
		return false;
	}
	
}

bool database::delete_table(const std::string& table_name) noexcept
{
	if (storage.find(table_name) == storage.end()) return false;
	storage.erase(table_name);
	return true;
}

bool database::remove_col(const std::string& col_name) noexcept
{
	if (!is_table_open()) return false;
	
	auto col_it = boost::range::find_if(schema[current_table], [&](const auto& pair) { return pair.first == col_name; });
	if (col_it == schema[current_table].end()) return false;

	for (auto& row : storage[current_table]) {
		row.second.erase(col_name);
	}

	schema[current_table].erase(col_it);
	return true;

}

bool database::remove_row(const std::string& row_name) noexcept
{
	if (!is_table_open()) return false;
	if (storage[current_table].find(row_name) == storage[current_table].end()) return false;
	storage[current_table].erase(row_name);
	return true;
}

std::optional<Ordered_Row_Data_t> database::get_row(const std::string& key) noexcept
{
	if (!is_table_open()) return std::nullopt;
	if (!is_row_exists(key)) return std::nullopt;

	try {
		Ordered_Row_Data_t result;

		for (const auto& col : storage[current_table][key]) {
			result.push_back(col.second);
		}

		return result;
	}
	catch (...) {
		return std::nullopt;
	}
}

std::optional<std::map<std::string, Ordered_Row_Data_t>> database::get_rows_if(const std::string& col_name,
	std::function<bool(const std::any& val)> predicate) noexcept
{
	if (!is_table_open()) return std::nullopt;
	if (!is_col_exists(col_name)) return std::nullopt;

	try {
		std::map<std::string, Ordered_Row_Data_t> result;

		for (const auto& [row_name, row_data] : storage.at(current_table)) {
			if (predicate(row_data.at(col_name))) {
				auto added_row = get_row(row_name);
				if (added_row == std::nullopt) return std::nullopt;

				result.emplace(row_name, *added_row);
			}
		}
		return result;
	}
	catch (...) {
		return std::nullopt;
	}
}

std::optional<std::any> database::get(const std::string& key, const std::string& col) const noexcept
{
	if (!is_table_open()) return std::nullopt;
	if (!is_row_exists(key) || !is_col_exists(col)) return std::nullopt;
	return storage.at(current_table).at(key).at(col);
}

const std::string& database::get_current_table_name() const noexcept
{
	return current_table;
}

std::optional<std::map<size_t, std::string>> database::get_column_order() const noexcept
{
	if (!is_table_open()) return std::nullopt;
	std::map<size_t, std::string> order;

	size_t counter = 0;
	for (const auto& col : schema.at(current_table)) {
		order.emplace(counter, col.first);
		counter++;
	}

	return order;
}

std::optional<std::string> database::get_col_type(const std::string& col_name) const noexcept
{
	if (!is_table_open()) return std::nullopt;

	auto it = boost::range::find_if(schema.at(current_table), [&](const auto& pair) {return pair.first == col_name; });
	if (it == schema.at(current_table).end()) return std::nullopt;
	return get_type_of(it->second);
}

DB_t::const_iterator database::begin() const noexcept
{
	return storage.begin();
}

DB_t::const_iterator database::end() const noexcept
{
	return storage.end();
}

DB_t::iterator database::begin() noexcept
{
	return storage.begin();
}

DB_t::iterator database::end() noexcept
{
	return storage.end();
}

std::ostream& operator<<(std::ostream& os, const std::any& value)
{
	if (value.type() == typeid(int)) {
		os << std::any_cast<int>(value);
	}
	else if (value.type() == typeid(double)) {
		os << std::any_cast<double>(value);
	}
	else if (value.type() == typeid(float)) {
		os << std::any_cast<float>(value);
	}
	else if (value.type() == typeid(std::string)) {
		os << std::any_cast<std::string>(value);
	}
	else if (value.type() == typeid(const char*)) {
		os << std::any_cast<const char*>(value);
	}
	else if (value.type() == typeid(bool)) {
		os << (std::any_cast<bool>(value) ? "true" : "false");
	}
	else {
		os << "<unknown type: " << value.type().name() << ">";
	}
	return os;
}

const std::string get_type_of(const std::any& value) noexcept
{
	if (value.type() == typeid(int)) {
		return "int";
	}
	else if (value.type() == typeid(double)) {
		return "double";
	}
	else if (value.type() == typeid(float)) {
		return "float";
	}
	else if (value.type() == typeid(std::string)) {
		return "string";
	}
	else if (value.type() == typeid(const char*)) {
		return "string";
	}
	else if (value.type() == typeid(bool)) {
		return "bool";
	}
	else {
		return "<unknown>";
	}
}
