#include "Log_t.h"

log_t::log_t(const std::string& dir)
{
	log_file.open(dir, std::ios::app);

	if (!log_file.is_open()) {
		std::cerr << "ERROR WHILE OPENING: " << LOG_DIR << std::endl;
		throw file_not_open();
	}
}

log_t::~log_t()
{
	log_file.close();
}

void log_t::write(const std::string& info)
{
	log_file << info << std::endl;
}
