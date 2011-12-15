#include "Thread.hpp"

cge::thread::CMutexClass::CMutexClass(void)
:m_bCreated(TRUE)
{
#ifdef WIN32
   m_mutex = CreateMutex(NULL,FALSE,NULL);
   if( !m_mutex ) m_bCreated = FALSE;
#else
   pthread_mutexattr_t mattr;

   pthread_mutexattr_init( &mattr );
   pthread_mutex_init(&m_mutex,&mattr);

#endif

}

cge::thread::CMutexClass::~CMutexClass(void)
{
#ifdef WIN32
	WaitForSingleObject(m_mutex,INFINITE);
	CloseHandle(m_mutex);
#else
	pthread_mutex_lock(&m_mutex);
	pthread_mutex_unlock(&m_mutex);
	pthread_mutex_destroy(&m_mutex);
#endif
}

void
cge::thread::CMutexClass::Lock()
{
	ThreadId_t id = CThread::ThreadId();
	if(CThread::ThreadIdsEqual(&m_owner,&id) )
		return; // the mutex is already locked by this thread
#ifdef WIN32
	WaitForSingleObject(m_mutex,INFINITE);
#else
	pthread_mutex_lock(&m_mutex);
#endif
	m_owner = CThread::ThreadId();
}

void 
cge::thread::CMutexClass::Unlock()
{
	ThreadId_t id = CThread::ThreadId();
	if( ! CThread::ThreadIdsEqual(&id,&m_owner) )
		return; // on the thread that has locked the mutex can release 
	            // the mutex

	memset(&m_owner,0,sizeof(ThreadId_t));
#ifdef WIN32
	ReleaseMutex(m_mutex);
#else
	pthread_mutex_unlock(&m_mutex);
#endif
}

