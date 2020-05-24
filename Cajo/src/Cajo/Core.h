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

#define BIT(x) (1 << x)