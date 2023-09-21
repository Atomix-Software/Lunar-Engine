#pragma once

#include "luna/core/Core.h"

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace luna
{
	class LNA_API Log
	{
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core Logger
#define LNA_CORE_TRACE(...)   ::luna::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LNA_CORE_INFO(...)    ::luna::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LNA_CORE_WARN(...)    ::luna::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LNA_CORE_ERROR(...)   ::luna::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LNA_CORE_FATAL(...)   ::luna::Log::GetCoreLogger()->critical(__VA_ARGS__)

// App Logger
#define LNA_TRACE(...) ::luna::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LNA_INFO(...)  ::luna::Log::GetClientLogger()->info(__VA_ARGS__)
#define LNA_WARN(...)  ::luna::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LNA_ERROR(...) ::luna::Log::GetClientLogger()->error(__VA_ARGS__)
#define LNA_FATAL(...) ::luna::Log::GetClientLogger()->critical(__VA_ARGS__)