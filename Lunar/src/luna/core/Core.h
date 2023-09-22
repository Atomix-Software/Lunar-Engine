#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define LNA_PLATFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>

	#if TARGET_IPHONE_SIMULATOR == 1
		#error "iOS simulator not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define LNA_PLATFORM_IOS
		#error "iOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define LNA_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple Platform!"
	#endif
#elif defined(__ANDROID__)
	#define LNA_PLATFORM_ANDROID
	#error "Android not supported!"
#elif defined(__linux__)
	#define LNA_PLATFORM_LINUX
	#error "Linux not supported!"
#else
	#error "Unsupported OS!"
#endif

#ifdef LNA_PLATFORM_WINDOWS
	#ifdef LNA_DYNAMIC_LINK
		#ifdef LNA_BUILD_DLL
			#define LNA_API __declspec(dllexport)
		#else
			#define LNA_API __declspec(dllimport)
		#endif
	#else
		#define LNA_API
	#endif
#endif

#ifndef LNA_PROFILE
	#define LNA_PROFILE 0
#endif

#ifdef LNA_DEBUG
	#if defined(LNA_PLATFORM_WINDOWS)
		#define LNA_DEBUGBREAK() __debugbreak()
	#elif defined(LNA_PLATFORM_LINUX)
		#include <signal.h>
		#define LNA_DEBUGBREAK() raise(SIGTRAP)
	#endif
	#define LNA_ENABLE_ASSERT
#endif

#ifdef LNA_ENABLE_ASSERT
	#define LNA_ASSERT(x, ...) { if(!(x)) { LNA_ERROR("Assertion Failed: {0}", __VA_ARGS__); LNA_DEBUGBREAK(); } }
	#define LNA_CORE_ASSERT(x, ...) { if(!(x)) { LNA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); LNA_DEBUGBREAK(); } }
#else
	#define LNA_ASSERT(x, ...) 
	#define LNA_CORE_ASSERT(x, ...) 
#endif

// Shifts a value over by a desired amount of bits
#define BIT(x) (1 << x)
#define LNA_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace luna
{
	template<typename T>
	using Unique = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Unique<T> CreateUnique(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Shared = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Shared<T> CreateShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}