#ifndef __EVENT_CLASS_HPP__
#define __EVENT_CLASS_HPP__

namespace cge
{
	namespace thread
	{
		class CEventClass
		{
			private:
#ifdef WIN32
					HANDLE m_event;
#else
					pthread_cond_t m_ready;
					pthread_mutex_t m_lock;
#endif
			public:
					BOOL m_bCreated;
					void Set();
					BOOL Wait();
					void Reset();
					CEventClass(void);
					~CEventClass(void);
		};
	};
};
#endif//__EVENT_CLASS_HPP__

