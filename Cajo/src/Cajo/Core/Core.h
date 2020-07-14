#pragma once

#include <memory>

#ifdef CAJO_PLATFORM_WINDOWS
	#if CAJO_DYNAMIC_LINK
		#ifdef CAJO_BUILD_DLL 
			#define CAJO_API __declspec(dllexport)
		#else
			#define CAJO_API __declspec(dllimport)
		#endif
	#else
		#define CAJO_API
	#endif
#else
	#error Cajo only supports Windows.
#endif

#ifdef CAJO_DEBUG
	#define CAJO_ENABLE_ASSERTS
#endif

#ifdef CAJO_ENABLE_ASSERTS
	#define CAJO_ASSERT(x, ...) { if(!(x)) { CAJO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CAJO_CORE_ASSERT(x, ...) { if(!(x)) { CAJO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CAJO_ASSERT(x, ...)
	#define CAJO_CORE_ASSERT(x, ...)
#endif // CAJO_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define CAJO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) 

namespace Cajo {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}