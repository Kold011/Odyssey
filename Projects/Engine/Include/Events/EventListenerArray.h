#pragma once

namespace Odyssey
{
	struct IEventListener
	{
	public:
		operator bool() { return IsValid(); }
		bool IsValid() { return ID != (uint64_t)(-1); }

	public:
		uint64_t ID = (uint64_t)(-1);
	};

	template<typename EventType>
	struct EventListener : IEventListener
	{
	public:
		EventListener(uint64_t id, std::function<void(EventType*)> callback)
		{
			ID = id;
			Callback = callback;
		}

	public:
		std::function<void(EventType*)> Callback;
	};

	// Empty abstract base class so we can store the templated version in containers
	class IEventListenerArray
	{
	};

	template<typename EventType>
	class EventListenerArray : public IEventListenerArray
	{
	public:
		std::shared_ptr<EventListener<EventType>> AddListener(std::function<void(EventType*)> callback)
		{
			std::shared_ptr<EventListener<EventType>> listener = std::make_shared<EventListener<EventType>>(m_NextID++, callback);
			m_Listeners.push_back(listener);
			return listener;
		}

		void RemoveListener(std::shared_ptr<EventListener<EventType>> listener)
		{
			auto iter = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
			if (iter != m_Listeners.end())
				m_Listeners.erase(iter);
		}

		void ExecuteCallbacks(EventType* e)
		{
			for (auto& listener : m_Listeners)
			{
				if (listener)
					listener->Callback(e);
			}
		}

	private:
		std::vector<std::shared_ptr<EventListener<EventType>>> m_Listeners;
		uint64_t m_NextID = 0;
	};
}