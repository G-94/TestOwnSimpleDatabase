#include "AppExceptions.h"

const char* file_not_open::what() const noexcept
{
	return "DATA FILE WASNT OPENED";
}