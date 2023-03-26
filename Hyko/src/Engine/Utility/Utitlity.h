#pragma once

#include <type_traits>

namespace HKUtility {
	template<typename T, typename ...Ts>
	struct has_type {
		static constexpr bool value = std::disjunction_v<std::is_same<T, Ts>...>;
	};

	template<typename T, typename... Ts>
	inline constexpr bool has_type_v = has_type<T, Ts...>::value;
}