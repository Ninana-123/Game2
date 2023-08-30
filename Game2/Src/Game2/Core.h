#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
#else
		#define HAZEL_API __declspec(dllimport)
#endif

#else
	#error Game2 only supports Windows!
#endif

