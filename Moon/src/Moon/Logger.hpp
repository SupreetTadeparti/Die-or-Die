#pragma once

#include "Core.h"
#include <memory>
#include <spdlog\spdlog.h>

namespace Moon
{
	class Logger
	{
	public:
		static MOON_API void Init();
		static MOON_API inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		static MOON_API inline std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define MoonLogTrace(...)		Moon::Logger::GetCoreLogger()->trace(__VA_ARGS__);
#define MoonLogInfo(...)		Moon::Logger::GetCoreLogger()->info(__VA_ARGS__);
#define MoonLogWarn(...)		Moon::Logger::GetCoreLogger()->warn(__VA_ARGS__);
#define MoonLogError(...)		Moon::Logger::GetCoreLogger()->error(__VA_ARGS__);
#define MoonLogCritical(...)	Moon::Logger::GetCoreLogger()->critical(__VA_ARGS__);

#define LogTrace(...)			Moon::Logger::GetClientLogger()->trace(__VA_ARGS__);
#define LogInfo(...)			Moon::Logger::GetClientLogger()->info(__VA_ARGS__);
#define LogWarn(...)			Moon::Logger::GetClientLogger()->warn(__VA_ARGS__);
#define LogError(...)			Moon::Logger::GetClientLogger()->error(__VA_ARGS__);
#define LogCritical(...)		Moon::Logger::GetClientLogger()->critical(__VA_ARGS__);