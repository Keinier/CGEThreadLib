#ifndef __MUTEX_CLASS_HPP__
#define __MUTEX_CLASS_HPP__

#ifndef WIN32
#include <pthread.h>
#endif

#include "Thread.hpp"

namespace cge
{
	namespace thread
	{
		class CMutexClass
		{
			private:
#ifdef WIN32
					HANDLE m_mutex;
#else
					pthread_mutex_t m_mutex;
#endif
					ThreadId_t m_owner;
			public:
					BOOL m_bCreated;
					void Lock();
					void Unlock();
					CMutexClass(void);
					~CMutexClass(void);
		};
	};
};
#endif//__MUTEX_CLASS_HPP__

