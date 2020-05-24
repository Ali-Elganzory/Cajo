#pragma once

#include <memory>

#include "Core.h"
#include "spdlog\spdlog.h"
#include "spdlog\fmt\ostr.h"

namespace Cajo {

	class CAJO_API Log
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

// Core log macros
#define CAJO_CORE_TRACE(...)   ::Cajo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CAJO_CORE_INFO(...)    ::Cajo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CAJO_CORE_WARN(...)    ::Cajo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CAJO_CORE_ERROR(...)   ::Cajo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CAJO_CORE_FATAL(...)   ::Cajo::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define CAJO_TRACE(...)        ::Cajo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CAJO_INFO(...)         ::Cajo::Log::GetClientLogger()->info(__VA_ARGS__)
#define CAJO_WARN(...)         ::Cajo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CAJO_ERROR(...)        ::Cajo::Log::GetClientLogger()->error(__VA_ARGS__)
#define CAJO_FATAL(...)        ::Cajo::Log::GetClientLogger()->fatal(__VA_ARGS__)