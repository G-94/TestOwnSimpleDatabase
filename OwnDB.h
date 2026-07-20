#pragma once

#include <string>
#include <vector>
#include <map>
#include <any>
#include <optional>
#include <ostream>
#include <boost/range/algorithm/find.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/type_index.hpp>

typedef std::map<std::string, std::any> Row_t;
typedef std::map<std::string, Row_t> Table_t;
typedef std::map<std::string, Table_t> DB_t;

typedef std::vector<std::pair<std::string, std::any>> Table_schema_t;
typedef std::map<std::string, Table_schema_t> Schema_t;

template <typename T>
concept Iterable = requires (T val) {
	std::begin(val);
	std::end(val);
};

std::ostream& operator << (std::ostream& os, const std::any& value);

const std::string get_type_of(const std::any& value) noexcept;

class database {
private:
	DB_t storage;
	Schema_t schema;

	std::string current_table;

	bool is_table_open() const noexcept;
	bool is_row_exists(const std::string& row) const noexcept;
	bool is_col_exists(const std::string& col) const noexcept;

public:

	bool add_table(const std::string& table_name) noexcept;
	bool add_row(const std::string& row_name) noexcept;

	template<typename T>
	bool add_col(const std::string& col_name, const T& default_value = T()) noexcept;

	bool open_table(const std::string& table_name) noexcept;

	bool delete_table(const std::string& table_name) noexcept;
	bool remove_col(const std::string& col_name) noexcept;
	bool remove_row(const std::string& row_name) noexcept;

	template <Iterable T>
	bool insert_value(const std::string& key, const T& iterable_value, size_t offset = 0) noexcept;

	template <Iterable T>
	bool insert_row(const std::string& key, const T& iterable_value) noexcept;

	template<typename T>
	bool insert_value(const std::string& key, const std::string& col, const T& value) noexcept;

	template<typename T>
	std::optional<T> get(const std::string& key, const std::string& col) const noexcept;

	const std::string& get_current_table_name() const noexcept;
	std::optional<std::map<size_t, std::string>> get_column_order() const noexcept;

	std::optional<std::string> get_col_type(const std::string& col_name) const noexcept;

	DB_t::const_iterator begin() const noexcept;
	DB_t::const_iterator end() const noexcept;

	DB_t::iterator begin() noexcept;
	DB_t::iterator end() noexcept;
};

template<typename T>
inline bool database::add_col(const std::string& col_name, const T& default_value) noexcept
{
	if (!is_table_open()) return false;

	try {
		schema[current_table].emplace_back(col_name, default_value);

		for (auto& row : storage[current_table]) {
			if (row.second.find(col_name) == row.second.end()) {
				row.second[col_name] = default_value;
			}
		}
		return true;
	}
	catch (...) {
		return false;
	}
}

template<Iterable T>
inline bool database::insert_value(const std::string& key, const T& iterable_value, size_t offset) noexcept
{
	if (!is_table_open()) return false;
	if (!is_row_exists(key)) return false;

	try {
		auto schema_it = schema.at(current_table).begin() + offset;
		for (const auto& val : iterable_value) {
			storage[current_table][key][schema_it->first] = val;;
			schema_it++;
		}
		return true;
	}
	catch (...) {
		return false;
	}
}

template<Iterable T>
inline bool database::insert_row(const std::string& key, const T& iterable_value) noexcept
{
	if (!is_table_open()) return false;

	try {
		bool is_row_added = add_row(key);
		if (!is_row_added) return false;

		auto schema_it = schema.at(current_table).begin();
		for (const auto& val : iterable_value) {
			storage[current_table][key][schema_it->first] = val;;
			schema_it++;
		}
		return true;
	}
	catch (...) {
		return false;
	}
}

template<typename T>
inline bool database::insert_value(const std::string& key, const std::string& col, const T& value) noexcept
{
	if (!is_table_open()) return false;
	if (!is_row_exists(key) || !is_col_exists(col)) return false;

	try {
		storage[current_table][key][col] = value;
		return true;
	}
	catch (...) {
		return false;
	}
}

template<typename T>
inline std::optional<T> database::get(const std::string& key, const std::string& col) const noexcept
{
	if (!is_table_open()) return std::nullopt;
	if (!is_row_exists(key) || !is_col_exists(col)) return std::nullopt;
	return std::any_cast<T>(storage.at(current_table).at(key).at(col));
}

