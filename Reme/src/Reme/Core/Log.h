#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Reme
{
	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Log macros
#ifndef _REME_DISABLE_LOGGING

#define LOG_TRACE(...)    ::Reme::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)     ::Reme::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)     ::Reme::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)    ::Reme::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...) ::Reme::Log::GetLogger()->critical(__VA_ARGS__)

#define CORE_LOG_TRACE(...)    ::Reme::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CORE_LOG_INFO(...)     ::Reme::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CORE_LOG_WARN(...)     ::Reme::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CORE_LOG_ERROR(...)    ::Reme::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CORE_LOG_CRITICAL(...) ::Reme::Log::GetCoreLogger()->critical(__VA_ARGS__)

#else

#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_CRITICAL(...)

#define CORE_LOG_TRACE(...)
#define CORE_LOG_INFO(...)
#define CORE_LOG_WARN(...)
#define CORE_LOG_ERROR(...)
#define CORE_LOG_CRITICAL(...)

#endif
