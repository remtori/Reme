#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Reme
{
	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_Logger; }
	private:
		static std::shared_ptr<spdlog::logger> s_Logger;
	};
}

// Log macros
#define LOG_TRACE(...)    ::Reme::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)     ::Reme::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::Reme::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::Reme::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Reme::Log::GetLogger()->critical(__VA_ARGS__)
