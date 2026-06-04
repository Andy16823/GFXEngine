#pragma once
#include <functional>
#include <memory>
#include <mutex>

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