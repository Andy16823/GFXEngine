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
		//************************************
		// Method:    OptionalRef
		// FullName:  GFXEngine::OptionalRef<T>::OptionalRef
		// Access:    public 
		// Returns:   constexpr
		// Qualifier: noexcept : m_ptr(nullptr)
		//************************************
		constexpr OptionalRef() noexcept : m_ptr(nullptr) {}
		
		//************************************
		// Method:    OptionalRef
		// FullName:  GFXEngine::OptionalRef<T>::OptionalRef
		// Access:    public 
		// Returns:   constexpr
		// Qualifier: noexcept : m_ptr(nullptr)
		// Parameter: std::nullptr_t
		//************************************
		constexpr OptionalRef(std::nullptr_t) noexcept : m_ptr(nullptr) {}
		
		//************************************
		// Method:    OptionalRef
		// FullName:  GFXEngine::OptionalRef<T>::OptionalRef
		// Access:    public 
		// Returns:   constexpr
		// Qualifier: noexcept : m_ptr(ptr)
		// Parameter: T * ptr
		//************************************
		constexpr OptionalRef(T* ptr) noexcept : m_ptr(ptr) {}
		
		//************************************
		// Method:    OptionalRef
		// FullName:  GFXEngine::OptionalRef<T>::OptionalRef
		// Access:    public 
		// Returns:   constexpr
		// Qualifier: noexcept : m_ptr(&ref)
		// Parameter: T & ref
		//************************************
		constexpr OptionalRef(T& ref) noexcept : m_ptr(&ref) {}

		//************************************
		// Method:    hasValue
		// FullName:  GFXEngine::OptionalRef<T>::hasValue
		// Access:    public 
		// Returns:   constexpr bool
		// Qualifier: const noexcept
		//************************************
		constexpr bool hasValue() const noexcept { return m_ptr != nullptr; }
		
		//************************************
		// Method:    operator bool
		// FullName:  GFXEngine::OptionalRef<T>::operator bool
		// Access:    public 
		// Returns:   constexpr
		// Qualifier: const noexcept
		//************************************
		constexpr explicit operator bool() const noexcept { return hasValue(); }

		//************************************
		// Method:    operator->
		// FullName:  GFXEngine::OptionalRef<T>::operator->
		// Access:    public 
		// Returns:   constexpr T*
		// Qualifier: const noexcept
		//************************************
		constexpr T* operator->() const noexcept {
			assert(m_ptr && "dereferencing from an empty OptionalRef");
			return m_ptr;
		}

		//************************************
		// Method:    operator*
		// FullName:  GFXEngine::OptionalRef<T>::operator*
		// Access:    public 
		// Returns:   constexpr T&
		// Qualifier: const noexcept
		//************************************
		constexpr T& operator*() const noexcept {
			assert(m_ptr && "dereferencing from an empty OptionalRef");
			return *m_ptr;
		}
	
		//************************************
		// Method:    get
		// FullName:  GFXEngine::OptionalRef<T>::get
		// Access:    public 
		// Returns:   constexpr T*
		// Qualifier: const noexcept
		//************************************
		constexpr T* get() const noexcept { return m_ptr; }
	};
}