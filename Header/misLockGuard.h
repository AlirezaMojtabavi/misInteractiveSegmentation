#pragma once

// The misLockGuard is used to wrap and guard a lockable object (a mutex, etc.) against exceptions. It achieves this purpose by 
// performing locking and unlocking of the guarded object respectively in its constructor and destructor. Using this class
// you can make sure that resources do not remain unlocked when leaving the scope in which the lock was acquired, e.g. due to
// an exception being thrown.
// Usage:
//		misLockGuard<Mutex> safeMutex;
//		// Perform critical section operations here
//		safeMutex.Unlock();	// This is optional as leaving the scope will automatically unlock the mutex.
template <class T>
class misLockGuard
{
public:
	misLockGuard(T& guardedLockableObject)
		: m_GuardedLockableObject(guardedLockableObject), m_LockAcquired(false)
	{
		Lock();
	}

	~misLockGuard(void)
	{
		Unlock();
	}

	void Lock()
	{
		if (!m_LockAcquired)
			m_GuardedLockableObject.Lock();
		m_LockAcquired = true;
	}

	void Unlock()
	{
		if (m_LockAcquired)
			m_GuardedLockableObject.Unlock();
		m_LockAcquired = false;
	}

private:
	misLockGuard(const T& guardedLockableObject);
	misLockGuard& operator=(const T& guardedLockableObject);

	T& m_GuardedLockableObject;
	bool m_LockAcquired;
};

