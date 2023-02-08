/*********************************************************************
*
* The idea is taken from https://github.com/TheCherno/Hazel.git (temporarily)
*
*********************************************************************/

#pragma once

#include "Engine/Core/Macro.h"
#include "Engine/System/Debug/Log.h"

#include <filesystem>

#define HK_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { HK##type##ERROR(msg, __VA_ARGS__); } }
#define HK_INTERNAL_ASSERT_WITH_MSG(type, check, ...) HK_INTERNAL_ASSERT_IMPL(type, check, "Assertion error: ({0}) at {1}:{2}", __VA_ARGS__, std::filesystem::path(__FILE__).string(), __LINE__)
#define HK_INTERNAL_ASSERT_NO_MSG(type, check) HK_INTERNAL_ASSERT_IMPL(type, check, "Assertion error: ({0}) at {1}:{2}", RETURN_MACRO_STR(check), std::filesystem::path(__FILE__).string(), __LINE__)

#define HK_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define HK_INTERNAL_ASSERT_GET_MACRO(...) RETURN_MACRO( HK_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, HK_INTERNAL_ASSERT_WITH_MSG, HK_INTERNAL_ASSERT_NO_MSG) )

// assert
#define HK_ASSERT(...) RETURN_MACRO( HK_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )