#pragma once

#include "Reme/Core/Log.h"

#ifndef _REME_DISABLE_ASSERT
	#ifdef _MSC_VER
	#define DEBUG_BREAK __debugbreak()
	#else
	#include <signal.h>
	#define DEBUG_BREAK raise(SIGTRAP)
	#endif

	#define REME_ASSERT(x, ...) if(!(x)) { CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK; }
#endif

#define BIT(x) (1 << x)

#define REME_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
