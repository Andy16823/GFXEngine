#pragma once
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <thread>
#include <atomic>
#include <vector>

namespace GFXEngine
{
	/// <summary>
	/// Task completion callback type, called when a background task is completed. 
	/// The callback receives a reference to the completed task.
	/// </summary>
	using TaskCompletionCallback = std::function<void(class BackgroundTask&)>;

	/// <summary>
	/// BackgroundTask represents a unit of work that can be processed in a separate thread.
	/// The Process method should be overridden to define the specific work to be done.
	/// The Task needs to be added to the BackgroundTaskManager to be executed, and the completion callback will be called once the task is completed.
	/// The Task Process method will be called in a separate thread, so it should not interact with the main thread directly. 
	/// The completion callback will be called in the main thread when the task is completed, allowing for safe interaction with the main thread if needed.
	/// </summary>
	class BackgroundTask
	{
	private:
		std::thread m_thread;
		std::atomic<bool> m_completed{ false };
		TaskCompletionCallback m_completionCallback;

	public:
		virtual ~BackgroundTask()
		{
			if (m_thread.joinable())
			{
				m_thread.join();
			}
		}
		void start(TaskCompletionCallback completionCallback);
		bool isCompleted() const { return m_completed; }
		void complete() { if (m_completionCallback) m_completionCallback(*this); }

		virtual void process() = 0;

	};

	/// <summary>
	/// InlineTask is a simple implementation of BackgroundTask that allows you to define the task work using a std::function.
	/// </summary>
	class InlineTask : public BackgroundTask
	{
	private:
		std::function<void()> m_taskFunction;
	public:
		InlineTask(std::function<void()> taskFunction) : m_taskFunction(taskFunction) {}
		virtual void process() override { if (m_taskFunction) m_taskFunction(); }
	};

	/// <summary>
	/// CreationTask is a template class that extends BackgroundTask, allowing you to define a task that creates an object of type T using a std::function.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class CreationTask : public BackgroundTask
	{
	private:
		std::function<T()> m_creationFunction;
		std::optional<T> m_result;
	public:
		CreationTask(std::function<T()> creationFunction) : m_creationFunction(creationFunction) {}
		virtual void process() override { if (m_creationFunction) m_result = m_creationFunction(); }
		std::optional<T> getResult() const { return m_result; }
		std::optional<T> moveResult() { 
			auto result = std::move(m_result);
			m_result.reset();
			return result;
		}
	};

	/// <summary>
	/// FetcherTask is a template class that extends BackgroundTask, allowing you to define a 
	/// task that fetches an object of type T using a std::function.
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class FetcherTask : public BackgroundTask
	{
		std::function<T*()> m_fetchFunction;
		T* m_result = nullptr;
	public:
		FetcherTask(std::function<T*()> fetchFunction) : m_fetchFunction(fetchFunction) {}
		virtual void process() override { if (m_fetchFunction) m_result = m_fetchFunction(); }
		T* getResult() const { return m_result; }
	};

	/// <summary>
	/// BackgroundTaskManager manages a collection of BackgroundTask instances, allowing you to add new tasks, update their status, and clear completed tasks.
	/// </summary>
	class BackgroundTaskManager
	{
	private:
		std::vector<std::unique_ptr<BackgroundTask>> m_tasks;
		std::mutex m_mutex;
	public:
		BackgroundTask* addTask(std::unique_ptr<BackgroundTask> task);
		void update();
		void clear();
	};
}