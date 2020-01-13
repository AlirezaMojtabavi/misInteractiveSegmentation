#pragma once

#include "misException.h"

// The misThreadSafeValue class template provides a thread-safe wrapper around a variable of arbitrary type. Essentially basic data
// types were considered in the design of this template. Therefore, the data type must provide a copy constructor, default 
// constructor, and copy assignment to be usable by this wrapper. Cast and assignment operators are overloaded to provide access to
// the wrapped data. Before entering a critical section on the wrapped data, call the Lock method to ensure exclusive access and
// call Unlock when leaving the critical section.
// Note: This class uses Win32 API for synchronizing access to the protected object.
template <typename ValueType>
class misThreadSafeValue
{
public:
	// Creates the object with the default value of ValueType and initializes the protection mechanism.
	misThreadSafeValue()
	{
		InitializeMutex();
	}

	// Creates and initialized the object using the specified value and also initializes the protection mechanism.
	misThreadSafeValue(const ValueType & initValue)
		: m_Value(initValue)
	{
		InitializeMutex();
	}

	// Creates the object with the default value of ValueType and initializes the protection mechanism.
	~misThreadSafeValue(void)
	{
		BOOL result = CloseHandle(m_MutexHandle);
	}

	const ValueType& Value() const
	{
		return m_Value;
	}

	ValueType& Value()
	{
		return m_Value;
	}

	operator const ValueType &() const
	{
		return m_Value;
	}

	operator ValueType &()
	{
		return m_Value;
	}

	ValueType & operator= (const ValueType &newValue)
	{
		m_Value = newValue;
		return *this;
	}

	// If the wrapped data is currently locked by another threads, waits until the holding thread unlocks the data and then 
	// acquires the lock for exclusive access of current thread. If no other thread currently has the data locked, this function
	// returns instantly with the lock acquired for the access of current thread.
	void Lock()
	{
		DWORD result = WaitForSingleObject(m_MutexHandle, INFINITE);
		if (result != WAIT_OBJECT_0)
		{
			std::stringstream message;
			message << 
				"misThreadSafeValue: Error while acquiring ownership of the mutex used for value access synchronization: ";
			switch (result)
			{
			case WAIT_FAILED:
				message << "GetLastError(): " << GetLastError() << ".";
				break;
			case WAIT_ABANDONED:
				message << "Mutex abandoned!";
				break;
			}
			throw misException(message.str());
		}
	}

	// Releases the lock held on the wrapped data (previously acquired through a call to Lock()).
	// Note: Put the Unlock() method in the finally block of a try ... finally ... structure to ensure proper disposal of the lock.
	// Failure to do so might result in other threads ending in a deadlock.
	void Unlock()
	{
		BOOL result = ReleaseMutex(m_MutexHandle);
		if (!result)
		{
			std::stringstream message;
			message << "Failed to release mutex used for value access synchronization. GetLastError(): " << GetLastError() << ".";
			throw misException(message.str());
		}
	}

private:
	// According to the Rule of Three the copy constructor and assignment are specially disabled.
	misThreadSafeValue(const misThreadSafeValue& initValue);
	ValueType & operator= (const misThreadSafeValue<ValueType> &newValue);

	// Creates the mutex. Used in all constructors.
	void InitializeMutex()
	{
		m_MutexHandle = CreateMutexEx(NULL, NULL, 0, DELETE | READ_CONTROL | SYNCHRONIZE);
		if (!m_MutexHandle)
			throw misException("misThreadSafeValue: Unable to create mutex for value access synchronization.");
	}

	ValueType m_Value;	// Holds the value being protected.
	HANDLE m_MutexHandle;	// Handle to the mutex used for synchronizing access to the protected value container.
};

