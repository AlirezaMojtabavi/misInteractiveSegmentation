#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Use the following MIS macros in classes that need to send events to their clients.
// If declaring events in an abstract interface class, use the MIS_HAS_EVENTS_INTERFACE and MIS_DEFINE_EVENT_INTERFACE macros.
// If defining events in concrete classes that implement abstract interfaces declaring MIS events, use 
// MIS_HAS_EVENTS_IMPLEMENTATION and MIS_DEFINE_EVENT_IMPLEMENTATION.
// If defining events in concrete classes that do not implement events declared in a base abstract interface, use the macros
// MIS_HAS_EVENTS_IMPLEMENTATION_WITHOUT_BASE and MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE.
// Also, concrete classes defining events need to use the MIS_INITIALIZE_EVENTS macro in all the constructors (at least one must
// be defined).
// If a class inherits an abstract interface with MIS events and at the same time needs to define events that are not inherited
// from the interface, just place MIS_HAS_EVENTS_IMPLEMENTATION inside the public block and it will not be necessary to also use
// MIS_HAS_EVENTS_IMPLEMENTATION_WITHOUT_BASE.
// The MIS_HAS_EVENTS_* macros indicate that a class uses the MIS events infrastructure. They bring in the definitions/declarations
// shared among all events. Simply place the MIS_HAS_EVENTS_* macro in the public block of the class.
// The MIS_DEFINE_EVENT_* macros define a single event (declare in the case of abstract interface). They are placed 
// within the public block of the class using the following syntax:
// MIS_DEFINE_EVENT_*(EventName, EventArg1Type eventArg1, EventArg2Type eventArg2, EventArg3Type eventArg3, ...)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MIS_INITIALIZE_EVENTS m_LastEventHandlerId = 1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Used in abstract interface classes
#define MIS_HAS_EVENTS_INTERFACE	\
public:	\
	typedef long long int EventHandlerId;	\
	virtual void RemoveEventHandler(EventHandlerId handlerId) = 0;

#define MIS_DEFINE_EVENT_INTERFACE(EVENT_NAME, ...)	\
public:	\
	typedef void __stdcall EVENT_NAME##EventHandler(__VA_ARGS__);	\
	virtual EventHandlerId Add##EVENT_NAME##EventHandler(std::function<EVENT_NAME##EventHandler> handler) = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Used in concrete classes that implement abstract interfaces declaring MIS events
#define MIS_HAS_EVENTS_IMPLEMENTATION	\
public:	\
	virtual void RemoveEventHandler(EventHandlerId handlerId)	\
	{	\
		auto connItr = m_EventSignalConnections.find(handlerId);	\
		if (connItr == m_EventSignalConnections.cend())	\
			return;	\
		connItr->second.disconnect();	\
		m_EventSignalConnections.erase(handlerId);	\
	}	\
private:	\
	EventHandlerId m_LastEventHandlerId;	\
	std::map<EventHandlerId, boost::signals2::connection> m_EventSignalConnections;	\
public:

#define MIS_DEFINE_EVENT_IMPLEMENTATION(EVENT_NAME)	\
public:	\
	virtual EventHandlerId Add##EVENT_NAME##EventHandler(std::function<EVENT_NAME##EventHandler> handler) override	\
	{	\
		m_EventSignalConnections[m_LastEventHandlerId] = m_##EVENT_NAME##Signal.connect(handler);	\
		return m_LastEventHandlerId++;	\
	}	\
private:	\
	boost::signals2::signal<EVENT_NAME##EventHandler> m_##EVENT_NAME##Signal;	\
public:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Used in concrete classes that do not implement events declared in a base abstract interface
#define MIS_HAS_EVENTS_IMPLEMENTATION_WITHOUT_BASE	\
public:	\
	typedef long long int EventHandlerId;	\
	virtual void RemoveEventHandler(EventHandlerId handlerId)	\
	{	\
		auto connItr = m_EventSignalConnections.find(handlerId);	\
		if (connItr == m_EventSignalConnections.cend())	\
			return;	\
		connItr->second.disconnect();	\
		m_EventSignalConnections.erase(handlerId);	\
	}	\
private:	\
	EventHandlerId m_LastEventHandlerId;	\
	std::map<EventHandlerId, boost::signals2::connection> m_EventSignalConnections;	\
public:

#define MIS_DEFINE_EVENT_IMPLEMENTATION_WITHOUT_BASE(EVENT_NAME, ...)	\
public:	\
	typedef void __stdcall EVENT_NAME##EventHandler(__VA_ARGS__);	\
	EventHandlerId Add##EVENT_NAME##EventHandler(std::function<EVENT_NAME##EventHandler> handler)	\
	{	\
		m_EventSignalConnections[m_LastEventHandlerId] = m_##EVENT_NAME##Signal.connect(handler);	\
		return m_LastEventHandlerId++;	\
	}	\
private:	\
	boost::signals2::signal<EVENT_NAME##EventHandler> m_##EVENT_NAME##Signal;	\
public:

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The following macros are used in mixed mode (CLR) wrapper classes that encapsulate classes with MIS events.
// Use MIS_HAS_EVENTS_CLR_WRAPPER once in the public block of the wrapper class.
#define MIS_HAS_EVENTS_CLR_WRAPPER	\
private:	\
	System::Collections::ArrayList m_NativeEventHandlerIds;	\
	System::Collections::Generic::List<System::Runtime::InteropServices::GCHandle> m_AllocatedFunctionPointerGCHandles;	\
public:

// Use MIS_DECLARE_EVENT_CLR_WRAPPER_PUBLIC once for every event in the public block of the wrapper class using the 
// following syntax:
// MIS_DECLARE_EVENT_CLR_WRAPPER_PUBLIC(EventName, EventCLRTypeArg1 eventClrArg1, EventCLRTypeArg2 eventClrArg2, ...)
#define MIS_DECLARE_EVENT_CLR_WRAPPER_PUBLIC(EVENT_NAME, ...)	\
public:	\
	delegate void EVENT_NAME##Delegate(__VA_ARGS__);	\
	event EVENT_NAME##Delegate^ EVENT_NAME##Event;	\
public:

// Use MIS_DEFINE_EVENT_HANDLER_CLR_WRAPPER once for every event in the "private" block of the wrapper class using the 
// following syntax:
// MIS_DEFINE_EVENT_HANDLER_CLR_WRAPPER(EventName, EventNativeTypeArg1 eventNativeClrArg1, ...) {
//		// Code to handle the native event, marshal parameters to CLR, and call the CLR event 
//		// defined by MIS_DECLARE_EVENT_CLR_WRAPPER_PUBLIC
// }
#define MIS_DEFINE_EVENT_HANDLER_CLR_WRAPPER(EVENT_NAME, ...)	\
private:	\
	delegate void EVENT_NAME##NativeDelegate(__VA_ARGS__);	\
	void On##EVENT_NAME(__VA_ARGS__)

// Use MIS_ATTACH_EVENT_CLR_WRAPPER once for every event to attach the native event handler (defined using 
// MIS_DEFINE_EVENT_HANDLER_CLR_WRAPPER) to the native object event.
// NATIVE_CLASS: Name of the native class being wrapped.
// NATIVE_OBJECT_PTR: Pointer to the encapsulated native object exposing the event.
// WRAPPER_CLASS: Name of the CLR wrapper class.
// EVENT_NAME: EVENT_NAME is of course event name.
#define MIS_ATTACH_EVENT_CLR_WRAPPER(NATIVE_CLASS, NATIVE_OBJECT_PTR, WRAPPER_CLASS, EVENT_NAME)	\
{	\
	using namespace System::Runtime::InteropServices;	\
	auto handlerNativeDelegate = gcnew EVENT_NAME##NativeDelegate(this, &WRAPPER_CLASS::On##EVENT_NAME);	\
	m_AllocatedFunctionPointerGCHandles.Add(GCHandle::Alloc(handlerNativeDelegate));	\
	auto handlerNativeFunctionPointer = reinterpret_cast<NATIVE_CLASS::EVENT_NAME##EventHandler*>(	\
	Marshal::GetFunctionPointerForDelegate(handlerNativeDelegate).ToPointer());	\
	m_NativeEventHandlerIds.Add((NATIVE_OBJECT_PTR)->Add##EVENT_NAME##EventHandler(handlerNativeFunctionPointer));	\
}

// Use MIS_FINALIZE_EVENTS_CLR_WRAPPER exactly once in the finalizer/destructor of the CLR wrapper class.
// NATIVE_CLASS: Name of the native class being wrapped.
#define MIS_FINALIZE_EVENTS_CLR_WRAPPER(NATIVE_CLASS, NATIVE_OBJECT_PTR)	\
{	\
	for each (NATIVE_CLASS::EventHandlerId handlerId in m_NativeEventHandlerIds)	\
		(NATIVE_OBJECT_PTR)->RemoveEventHandler(handlerId);	\
	for each (System::Runtime::InteropServices::GCHandle gcHandle in m_AllocatedFunctionPointerGCHandles)	\
		gcHandle.Free();	\
}