template <class T>
class misMemberCommandCallback : public vtkCommand
{
public:
	/** pointer to a member function that takes a Object* and the event */
	typedef  void (T::*TMemberFunctionPointer)(vtkObject*, unsigned long , 	void *);
	typedef  void (T::*TConstMemberFunctionPointer)(const vtkObject*, unsigned long , 	void *);

	static  misMemberCommandCallback* New()
	{
		return  new misMemberCommandCallback;
	}

	void SetCallbackFunction(T* object,
		TMemberFunctionPointer memberFunction)
	{
		m_This = object;
		m_MemberFunction = memberFunction;
	}
	void SetCallbackFunction(T* object,
		TConstMemberFunctionPointer memberFunction)
	{
		m_This = object;
		m_ConstMemberFunction = memberFunction;
	}

	/**  Invoke the member function. */
	virtual void Execute(vtkObject *caller, unsigned long eventId,
		void *callData)
	{
		if( m_MemberFunction )
		{
			((*m_This).*(m_MemberFunction))(caller, eventId,callData);
		}
	}

	/**  Invoke the member function with a const object. */
	virtual void Execute(const vtkObject *caller, unsigned long eventId,
		void *callData)
	{
		if( m_MemberFunction )
		{
			((*m_This).*(m_ConstMemberFunction))(caller, eventId,callData);
		}
	}
	misMemberCommandCallback():m_MemberFunction(0),m_ConstMemberFunction(0) {}

protected:

	T* m_This;
	TMemberFunctionPointer m_MemberFunction;
	TConstMemberFunctionPointer m_ConstMemberFunction;
	virtual ~misMemberCommandCallback(){}
};
