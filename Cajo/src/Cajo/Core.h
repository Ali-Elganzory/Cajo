#pragma once

#ifdef CAJO_PLATFORM_WINDOWS
	#ifdef CAJO_BUILD_DLL 
		#define CAJO_API __declspec(dllexport)
	#else
		#define CAJO_API __declspec(dllimport)
	#endif
#else
	#error Cajo only supports Windows.
#endif

#ifdef CAJO_ENABLE_ASSERTS
	#define CAJO_ASSERT(x, ...) { if(!(x)) { CAJO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CAJO_CORE_ASSERT(x, ...) { if(!(x)) { CAJO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CAJO_ASSERT(x, ...)
	#define CAJO_CORE_ASSERT(x, ...)
#endif // CAJO_ENABLE_ASSERTS


#define BIT(x) (1 << x)