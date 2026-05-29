#pragma once
#include <cassert>
#include <cstddef>
#include <stdexcept>

namespace GFXEngine {

	/// <summary>
	/// Iterator that allows iterating over a buffer with a specified stride, useful for accessing vertex components in interleaved vertex buffers.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class StrideIterator {
	private:
		const std::byte* m_ptr;
		size_t m_stride;

	public:
		StrideIterator(const std::byte* ptr, size_t stride) : m_ptr(ptr), m_stride(stride) {}

		const T& operator*() const {
			return *reinterpret_cast<const T*>(m_ptr);
		}

		StrideIterator& operator++() {
			m_ptr += m_stride;
			return *this;
		}

		bool operator!=(const StrideIterator& other) const 
		{
			return m_ptr != other.m_ptr;
		}

		bool operator==(const StrideIterator& other) const 
		{
			return m_ptr == other.m_ptr;
		}

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
	public:
		using iterator = StrideIterator<T>;

		StrideSpan(const void* data, size_t count, size_t stride) : m_data(static_cast<const std::byte*>(data)), m_count(count), m_stride(stride) 
		{
			if (stride < sizeof(T))
			{
				throw std::runtime_error("Stride smaller than element size");
			}
		}

		const T& operator[](size_t index) const 
		{
			assert(index < m_count);
			return *reinterpret_cast<const T*>(m_data + index * m_stride);
		}

		size_t size() const 
		{
			return m_count;
		}

		iterator begin() const 
		{
			return iterator(m_data, m_stride);
		}

		iterator end() const 
		{
			return iterator(m_data + m_count * m_stride, m_stride);
		}

		const void* bufferData() const
		{
			return m_data;
		}

	private:
		const std::byte* m_data;
		size_t m_count;
		size_t m_stride;
	};
}