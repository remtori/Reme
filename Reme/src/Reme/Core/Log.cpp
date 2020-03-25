#include "pch.h"
#include "Reme/Core/Log.h"

#include <spdlog/spdlog-inl.h>

#ifdef _DEBUG
#include "spdlog/sinks/stdout_color_sinks.h"
#else
#include "spdlog/sinks/basic_file_sink.h"
#endif

namespace Reme
{
	std::shared_ptr<spdlog::logger> Log::s_Logger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n [%L]: %v%$");
#ifdef _DEBUG
		s_Logger = spdlog::stdout_color_mt("Reme Engine");
#else
		s_Logger = spdlog::basic_logger_mt("Reme Engine", "log.txt");
#endif
		s_Logger->set_level(spdlog::level::trace);
	}
}
