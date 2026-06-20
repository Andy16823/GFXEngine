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
	using TaskCompletionCallback = std::function<void(class BackgroundTask&)>;

	class BackgroundTask
	{
	private:
		std::thread m_thread;
		std::atomic<bool> m_completed{ false };
		TaskCompletionCallback m_completionCallback;

	public:
		
		//************************************
		// Method:    ~BackgroundTask
		// FullName:  GFXEngine::BackgroundTask::~BackgroundTask
		// Access:    virtual public 
		// Returns:   
		// Qualifier:
		//************************************
		virtual ~BackgroundTask()
		{
			if (m_thread.joinable())
			{
				m_thread.join();
			}
		}
		
		//************************************
		// Method:    start
		// FullName:  GFXEngine::BackgroundTask::start
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: TaskCompletionCallback completionCallback
		//************************************
		void start(TaskCompletionCallback completionCallback);
		
		//************************************
		// Method:    isCompleted
		// FullName:  GFXEngine::BackgroundTask::isCompleted
		// Access:    public 
		// Returns:   bool
		// Qualifier: const
		//************************************
		bool isCompleted() const { return m_completed; }
		
		//************************************
		// Method:    complete
		// FullName:  GFXEngine::BackgroundTask::complete
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void complete() { if (m_completionCallback) m_completionCallback(*this); }

		//************************************
		// Method:    process
		// FullName:  GFXEngine::BackgroundTask::process
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void process() = 0;
	};

	class InlineTask : public BackgroundTask
	{
	private:
		std::function<void()> m_taskFunction;
	public:

		//************************************
		// Method:    InlineTask
		// FullName:  GFXEngine::InlineTask::InlineTask
		// Access:    public 
		// Returns:   
		// Qualifier: : m_taskFunction(taskFunction)
		// Parameter: std::function<void
		// Parameter: > taskFunction
		//************************************
		InlineTask(std::function<void()> taskFunction) : m_taskFunction(taskFunction) {}
		
		//************************************
		// Method:    process
		// FullName:  GFXEngine::InlineTask::process
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void process() override { if (m_taskFunction) m_taskFunction(); }
	};

	template<typename T>
	class CreationTask : public BackgroundTask
	{
	private:
		std::function<T()> m_creationFunction;
		std::optional<T> m_result;
	public:

		//************************************
		// Method:    CreationTask
		// FullName:  GFXEngine::CreationTask<T>::CreationTask
		// Access:    public 
		// Returns:   
		// Qualifier: : m_creationFunction(creationFunction)
		// Parameter: std::function<T
		// Parameter: > creationFunction
		//************************************
		CreationTask(std::function<T()> creationFunction) : m_creationFunction(creationFunction) {}

		//************************************
		// Method:    process
		// FullName:  GFXEngine::CreationTask<T>::process
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void process() override { if (m_creationFunction) m_result = m_creationFunction(); }
		
		//************************************
		// Method:    getResult
		// FullName:  GFXEngine::CreationTask<T>::getResult
		// Access:    public 
		// Returns:   std::optional<T>
		// Qualifier: const
		//************************************
		std::optional<T> getResult() const { return m_result; }
		
		//************************************
		// Method:    moveResult
		// FullName:  GFXEngine::CreationTask<T>::moveResult
		// Access:    public 
		// Returns:   std::optional<T>
		// Qualifier:
		//************************************
		std::optional<T> moveResult() { 
			auto result = std::move(m_result);
			m_result.reset();
			return result;
		}
	};

	template<typename T>
	class FetcherTask : public BackgroundTask
	{
		std::function<T*()> m_fetchFunction;
		T* m_result = nullptr;
	public:

		//************************************
		// Method:    FetcherTask
		// FullName:  GFXEngine::FetcherTask<T>::FetcherTask
		// Access:    public 
		// Returns:   
		// Qualifier: : m_fetchFunction(fetchFunction)
		// Parameter: std::function<T * 
		// Parameter: > fetchFunction
		//************************************
		FetcherTask(std::function<T*()> fetchFunction) : m_fetchFunction(fetchFunction) {}
		
		//************************************
		// Method:    process
		// FullName:  GFXEngine::FetcherTask<T>::process
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		//************************************
		virtual void process() override { if (m_fetchFunction) m_result = m_fetchFunction(); }
		
		//************************************
		// Method:    getResult
		// FullName:  GFXEngine::FetcherTask<T>::getResult
		// Access:    public 
		// Returns:   T*
		// Qualifier: const
		//************************************
		T* getResult() const { return m_result; }
	};

	class BackgroundTaskManager
	{
	private:
		std::vector<std::unique_ptr<BackgroundTask>> m_tasks;
		std::mutex m_mutex;
	public:

		//************************************
		// Method:    addTask
		// FullName:  GFXEngine::BackgroundTaskManager::addTask
		// Access:    public 
		// Returns:   GFXEngine::BackgroundTask*
		// Qualifier:
		// Parameter: std::unique_ptr<BackgroundTask> task
		//************************************
		BackgroundTask* addTask(std::unique_ptr<BackgroundTask> task);
		
		//************************************
		// Method:    update
		// FullName:  GFXEngine::BackgroundTaskManager::update
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void update();
		
		//************************************
		// Method:    clear
		// FullName:  GFXEngine::BackgroundTaskManager::clear
		// Access:    public 
		// Returns:   void
		// Qualifier:
		//************************************
		void clear();
	};
}