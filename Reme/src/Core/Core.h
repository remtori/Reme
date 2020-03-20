#pragma once

#include "Core/Log.h"

#ifndef _REME_DISABLE_ASSERT
	#ifdef _MSC_VER
	#define DEBUG_BREAK __debugbreak()
	#else
	#include <signal.h>
	#define DEBUG_BREAK raise(SIGTRAP)
	#endif

	#define ASSERT(x, ...) if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK; }
#endif
