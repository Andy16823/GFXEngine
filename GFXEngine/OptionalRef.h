#pragma once
#include <iostream>
#include <cassert>

namespace GFXEngine {
	template<typename T>
	class OptionalRef
	{
	private:
		T* m_ptr = nullptr;

	public:
		constexpr OptionalRef() noexcept : m_ptr(nullptr) {}
		constexpr OptionalRef(std::nullptr_t) noexcept : m_ptr(nullptr) {}
		constexpr OptionalRef(T* ptr) noexcept : m_ptr(ptr) {}
		constexpr OptionalRef(T& ref) noexcept : m_ptr(&ref) {}

		constexpr bool hasValue() const noexcept { return m_ptr != nullptr; }
		constexpr explicit operator bool() const noexcept { return hasValue(); }

		constexpr T* operator->() const noexcept {
			assert(m_ptr && "dereferencing from an empty OptionalRef");
			return m_ptr;
		}

		constexpr T& operator*() const noexcept {
			assert(m_ptr && "dereferencing from an empty OptionalRef");
			return *m_ptr;
		}
	
		constexpr T* get() const noexcept { return m_ptr; }
	};
}