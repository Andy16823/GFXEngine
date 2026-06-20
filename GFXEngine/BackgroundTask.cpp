#include "BackgroundTask.h"

void GFXEngine::BackgroundTask::start(TaskCompletionCallback completionCallback)
{
	m_completionCallback = completionCallback;
	m_thread = std::thread([this]() {
		process();
		m_completed = true;
		});
}

GFXEngine::BackgroundTask* GFXEngine::BackgroundTaskManager::addTask(std::unique_ptr<BackgroundTask> task)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_tasks.push_back(std::move(task));
	return m_tasks.back().get();
}

void GFXEngine::BackgroundTaskManager::update()
{
	// Iterate in reverse to safely remove completed tasks
	for (size_t i = m_tasks.size(); i-- > 0; )
	{
		auto& task = m_tasks[i];
		if (task->isCompleted()) 
		{
			task->complete();
			m_tasks.erase(m_tasks.begin() + i);
		}
	}
}

void GFXEngine::BackgroundTaskManager::clear()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_tasks.clear();
}
