#pragma once

#include "pch.h"

namespace Etas {

	template <typename T>
	using Uniq = std::unique_ptr<T>;

	template<typename T, typename ... Args>
	constexpr Uniq<T> createUniq(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Shared = std::shared_ptr<T>;

	template <typename T, typename ... Args>
	constexpr Shared<T> createShared(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}