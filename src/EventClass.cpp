
#include "thread.hpp"

cge::thread::CEventClass::CEventClass(void)
:m_bCreated(TRUE)
{
#ifdef WIN32
	m_event = CreateEvent(NULL,FALSE,FALSE,NULL);
	if( !m_event )
	{
		m_bCreated = FALSE;
	}
#else
	pthread_mutexattr_t mattr;
	
	pthread_mutexattr_init(&mattr);
	pthread_mutex_init(&m_lock,&mattr);
	pthread_cond_init(&m_ready,NULL);

#endif	
}

cge::thread::CEventClass::~CEventClass(void)
{
#ifdef WIN32
	CloseHandle(m_event);
#else
	pthread_cond_destroy(&m_ready);
	pthread_mutex_destroy(&m_lock);
#endif
}


/**
 *
 * Set
 * set an event to signaled
 *
 **/
void
cge::thread::CEventClass::Set()
{
#ifdef WIN32
	SetEvent(m_event);
#else
	pthread_mutex_lock(&m_lock);
	pthread_mutex_unlock(&m_lock);
	pthread_cond_signal(&m_ready);
#endif
}

/**
 *
 * Wait
 * wait for an event -- wait for an event object
 * to be set to signaled
 *
 **/
BOOL
cge::thread::CEventClass::Wait()
{
#ifdef WIN32
	if( WaitForSingleObject(m_event,INFINITE) != WAIT_OBJECT_0 )
	{
		return FALSE;
	}
	return TRUE;
#else
	pthread_mutex_lock(&m_lock);
	pthread_cond_wait(&m_ready,&m_lock);
	return TRUE;
#endif
}

/**
 *
 * Reset
 * reset an event flag to unsignaled
 *
 **/
void
cge::thread::CEventClass::Reset()
{
#ifndef WIN32
	pthread_mutex_unlock(&m_lock);
#endif
}

