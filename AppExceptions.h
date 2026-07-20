#pragma once

#include "exception"

class file_not_open : public std::exception {
public:
	const char* what() const noexcept override;
};