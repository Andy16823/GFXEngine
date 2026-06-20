#pragma once
#include <cassert>
#include <cstddef>
#include <stdexcept>

namespace GFXEngine {

	template<typename T>
	class StrideIterator {
	private:
		const std::byte* m_ptr;
		size_t m_stride;

	public:
		//************************************
		// Method:    StrideIterator
		// FullName:  GFXEngine::StrideIterator<T>::StrideIterator
		// Access:    public 
		// Returns:   
		// Qualifier: : m_ptr(ptr), m_stride(stride)
		// Parameter: const std::byte * ptr
		// Parameter: size_t stride
		//************************************
		StrideIterator(const std::byte* ptr, size_t stride) : m_ptr(ptr), m_stride(stride) {}

		//************************************
		// Method:    operator*
		// FullName:  GFXEngine::StrideIterator<T>::operator*
		// Access:    public 
		// Returns:   const T&
		// Qualifier: const
		//************************************
		const T& operator*() const {
			return *reinterpret_cast<const T*>(m_ptr);
		}

		//************************************
		// Method:    operator++
		// FullName:  GFXEngine::StrideIterator<T>::operator++
		// Access:    public 
		// Returns:   GFXEngine::StrideIterator&
		// Qualifier:
		//************************************
		StrideIterator& operator++() {
			m_ptr += m_stride;
			return *this;
		}

		//************************************
		// Method:    operator!=
		// FullName:  GFXEngine::StrideIterator<T>::operator!=
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: const StrideIterator & other
		//************************************
		bool operator!=(const StrideIterator& other) const 
		{
			return m_ptr != other.m_ptr;
		}

		//************************************
		// Method:    operator==
		// FullName:  GFXEngine::StrideIterator<T>::operator==
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		// Parameter: const StrideIterator & other
		//************************************
		bool operator==(const StrideIterator& other) const 
		{
			return m_ptr == other.m_ptr;
		}

		//************************************
		// Method:    operator->
		// FullName:  GFXEngine::StrideIterator<T>::operator->
		// Access:    public 
		// Returns:   const T*
		// Qualifier: const
		//************************************
		const T* operator->() const 
		{
			return reinterpret_cast<const T*>(m_ptr);
		}
	};

	/// <summary>
	/// StrideSpan is a non-owning view over a contiguous block of memory with a specified stride, allowing access to elements of type T that are interleaved in the buffer.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class StrideSpan {
	private:
		const std::byte* m_data;
		size_t m_count;
		size_t m_stride;

	public:
		using iterator = StrideIterator<T>;

	public:
		//************************************
		// Method:    StrideSpan
		// FullName:  GFXEngine::StrideSpan<T>::StrideSpan
		// Access:    public 
		// Returns:   
		// Qualifier: : m_data(static_cast<const std::byte*>(data)), m_count(count), m_stride(stride)
		// Parameter: const void * data
		// Parameter: size_t count
		// Parameter: size_t stride
		//************************************
		StrideSpan(const void* data, size_t count, size_t stride) : m_data(static_cast<const std::byte*>(data)), m_count(count), m_stride(stride) 
		{
			if (stride < sizeof(T))
			{
				throw std::runtime_error("Stride smaller than element size");
			}
		}

		//************************************
		// Method:    operator[]
		// FullName:  GFXEngine::StrideSpan<T>::operator[]
		// Access:    public 
		// Returns:   const T&
		// Qualifier: const
		// Parameter: size_t index
		//************************************
		const T& operator[](size_t index) const 
		{
			assert(index < m_count);
			return *reinterpret_cast<const T*>(m_data + index * m_stride);
		}

		//************************************
		// Method:    size
		// FullName:  GFXEngine::StrideSpan<T>::size
		// Access:    public 
		// Returns:   std::size_t
		// Qualifier: const
		//************************************
		size_t size() const 
		{
			return m_count;
		}

		//************************************
		// Method:    begin
		// FullName:  GFXEngine::StrideSpan<T>::begin
		// Access:    public 
		// Returns:   std::iterator
		// Qualifier: const
		//************************************
		iterator begin() const 
		{
			return iterator(m_data, m_stride);
		}

		//************************************
		// Method:    end
		// FullName:  GFXEngine::StrideSpan<T>::end
		// Access:    public 
		// Returns:   std::iterator
		// Qualifier: const
		//************************************
		iterator end() const 
		{
			return iterator(m_data + m_count * m_stride, m_stride);
		}

		//************************************
		// Method:    bufferData
		// FullName:  GFXEngine::StrideSpan<T>::bufferData
		// Access:    public 
		// Returns:   const void*
		// Qualifier: const
		//************************************
		const void* bufferData() const
		{
			return m_data;
		}
	};
}