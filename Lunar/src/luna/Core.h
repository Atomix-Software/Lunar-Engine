#pragma once

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