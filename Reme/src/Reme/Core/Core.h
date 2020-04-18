#pragma once

#include "Reme/Core/Log.h"

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define _REME_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define _REME_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define _REME_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define _REME_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define _REME_PLATFORM_LINUX
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection

// On Window and Linux for now use GLFW and OpenGL
#if defined(_REME_PLATFORM_WINDOWS) || defined(_REME_PLATFORM_LINUX)
#define _REME_USE_GLFW
#define _REME_USE_OPENGL
#endif

#ifndef _DEBUG
	#define _REME_DISABLE_ASSERT
#endif

#ifndef _REME_DISABLE_ASSERT
	#ifdef _MSC_VER
		#define DEBUG_BREAK __debugbreak()
	#else
		#include <signal.h>
		#define DEBUG_BREAK raise(SIGTRAP)
	#endif

	#define CORE_ASSERT(x, ...) if(!(x)) { CORE_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK; }
	#define ASSERT(x, ...) if(!(x)) { LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); DEBUG_BREAK; }
#else
	#define DEBUG_BREAK
	#define CORE_ASSERT(x, ...) x
	#define ASSERT(x, ...) x
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Reme
{
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

	template<typename T>
	using WeakRef = std::weak_ptr<T>;
}
