#pragma once

//===========================================================================
#define  misSetArrayToVector(vector, arr)	\
	vector[0] = arr[0];	\
	vector[1] = arr[1];	\
	vector[2] = arr[2];

#define misVector(a, b, c) \
	(a)[0] = (b)[0] - (c)[0];	\
	(a)[1] = (b)[1] - (c)[1];	\
	(a)[2] = (b)[2] - (c)[2];

// This macro is placed inside class declaration to define internal class types Self, Superclass, Pointer, and ConstPointer and
// the GetNameOfClass method.
#define misObjectTypesMacro( className, superClassName ) \
public:	\
	/*	Declare utility internal types */	\
	typedef className                         Self;\
	typedef superClassName                    Superclass; \
	typedef ::itk::SmartPointer< Self >       Pointer; \
	typedef ::itk::SmartPointer< const Self > ConstPointer;	\
	\
	virtual const char *GetNameOfClass() const \
	{	\
		return #className;	\
	}	\


// This macro is placed inside class declaration to prevent objects of the class from being copy constructed or copy assigned.
#define misObjectCopyPreventMacro(className) \
private:	\
	className(const className &);	/*	Type is not copy constructible. */	\
	className& operator = (const className &);	/*	Type is not copy assignable. */	\


// Macro placed in the class declaration to bring in general misOldObject plumbing, which includes internal type definitions, object 
// copy regulation enforcements (non-copy-constructible and non-copy-assignable), and concrete type information methods. Almost all
// misOldObject subclasses require this macro.
#define misObjectMacro(className, superClassName)	\
	misObjectTypesMacro(className, superClassName)	\
	misObjectCopyPreventMacro(className)

// Macro placed within the class declaration to add the public factory method New() that creates a reference counted instance of 
// the class. Abstract subclasses of misOldObject should not include this macro.
#define misObjectNewMacro(className)	\
public:	\
	/* Creates a reference counted instance of the  */	\
	static Pointer New(void)	\
	{	\
		itk::SmartPointer<className> smartPtr;	\
		className *rawPtr = new className;	\
		smartPtr = rawPtr;	\
		itk::Object* itkObject = dynamic_cast<itk::Object*>(smartPtr.GetPointer());	\
		itkObject->UnRegister();	\
		return smartPtr;	\
	} 

// When placed inside definition of a class, inserts private definition for a boolean variable with a public getter method and 
// and three different setters.
#define misPrivateVariableWithPublicAccessorsMacro(variableType, variableName, accessorName) \
private:	\
	variableType variableName;	\
public:	\
	virtual void Set##accessorName(const variableType &newValue) { variableName = newValue; }	\
	virtual const variableType &Get##accessorName() const { return variableName; }


// When placed inside definition of a class, inserts private definition for a boolean variable with a public getter method and 
// three different setters.
#define misPrivateBooleanVariableWithPublicAccessorsMacro(variableName, accessorName) \
private:	\
	bool variableName;	\
public:	\
	virtual void accessorName##On () { variableName = true; }	\
	virtual void accessorName##Off () { variableName = false; }	\
	virtual void Set##accessorName(bool status) { variableName = status; }	\
	virtual bool accessorName() const { return variableName; }

// When placed inside definition of a class, inserts private definition for an array of size three of the specified data type with
// suitable public accessors for conveniently setting and getting elements of the private variable. It can be used for 3-vectors,
// and colour values, ...
#define misPrivate3VectorVariableWithPublicAccessorsMacro(variableType, variableName, accessorName) \
private:	\
	variableType variableName[3];	\
public:	\
	virtual void Set##accessorName(const variableType newValue[3])	\
	{	\
		for (int i = 0; i < 3; i++)	\
			variableName[i] = newValue[i];	\
	}	\
	virtual void Set##accessorName(variableType component1, variableType component2, variableType component3)	\
	{	\
		variableName[0] = component1;	\
		variableName[1] = component2;	\
		variableName[2] = component3;	\
	}	\
	virtual const variableType *Get##accessorName() const { return variableName; }	\
	virtual void Get##accessorName(variableType *comps)	\
	{	\
		comps[0] = variableName[0];	\
		comps[1] = variableName[1];	\
		comps[2] = variableName[2];	\
	}

// When placed inside definition of a class, inserts private definition for an array of size two of the specified data type with
// suitable public accessors for conveniently setting and getting elements of the private variable. It can be used for 2-vectors,
// positions, sizes, ...
#define misPrivate2VectorVariableWithPublicAccessorsMacro(variableType, variableName, accessorName) \
private:	\
	variableType variableName[2];	\
public:	\
	virtual void Set##accessorName(const variableType newValue[2])	\
	{	\
		for (int i = 0; i < 2; i++)	\
		variableName[i] = newValue[i];	\
	}	\
	virtual void Set##accessorName(variableType component1, variableType component2)	\
	{	\
		variableName[0] = component1;	\
		variableName[1] = component2;	\
	}	\
	virtual const variableType *Get##accessorName() const { return variableName; }

#define misCreateVariableWithBooleanMacro(propertyName) \
	misPrivateBooleanVariableWithPublicAccessorsMacro(m_##propertyName, propertyName);

#define misCreateVariableWithProtectedSetGetMacro(name, type)	\
protected:	\
	type m_##name;	\
	misProtectedSetMacro(name,type);\
	misGetMacro(name,type);

#define misCreateVariableWithGetMacro(name,type)\
	 protected:\
	 type m_##name;\
	 misGetMacro(name,type);


#define misCreateVariableWithAbstractGetMacro(name,type)\
	 protected:\
	 type m_##name;\
	 misSetMacro(name,type);\
	 misAbstractGetMacro(name,type);

#define misCreateVariableWithSetGetMacro(name,type)\
	 protected:\
	 type m_##name;\
	 misSetMacro(name,type);\
	 misGetMacro(name,type);

#define misCreateVariableWithProtectedSetGetMacroWithModificationFlag(name,type)\
	 protected:\
	 type m_##name;\
	 misProtectedSetMacroWithModificationFlag(name,type);\
	 misGetMacro(name,type);

#define misCreateVariableWithSetGetMacroWithModificationFlag(name,type)\
	 protected:\
	 type m_##name;\
	 misSetMacroWithModificationFlag(name,type);\
	 misGetMacro(name,type);


#define misSetMacro(name,type) \
	public:\
	virtual void Set##name (type _arg) \
  { \
  if (this->m_##name != _arg) \
	{ \
	this->m_##name = _arg; \
	} \
  } 

#define misSetMacroWithModificationFlag(name,type) \
	public:\
	virtual void Set##name (type _arg) \
  { \
  if (this->m_##name != _arg) \
	{ \
	this->m_##name = _arg; \
	this->m_ModificationFlag = true;\
	} \
  } 


#define misProtectedSetMacro(name,type) \
	protected:\
	virtual void Set##name (type _arg) \
  { \
  if (this->m_##name != _arg) \
	{ \
	this->m_##name = _arg; \
	} \
  }

#define misProtectedSetMacroWithModificationFlag(name,type) \
	protected:\
	virtual void Set##name (type _arg) \
  { \
  if (this->m_##name != _arg) \
	{ \
	this->m_##name = _arg; \
	this->m_ModificationFlag = true;\
	} \
  }



//#define	 misCreateVariableWithSetGetWithMidifiedFlageMacro(name,type)\
//		 protected:\
//		 type m_##name;\
//		 bool m_##name##ModifiedFlage;
//		 misSetWithModifiedFlageMacro(name,type);\
//		 misGetMacro(name,type);


//#define misSetWithModifiedFlageMacro(name,type) \
//	Private:\
//	virtual void Set##name (type _arg) \
//		 { \
//		 if (this->m_##name != _arg) \
//		 { \
//		 this->m_##name = _arg; \
//		 this->m_##name##ModifiedFlage = true;\
//		 this->m_DatasHaveBeenModified = true;\
//		 } \
//		 }
//===========================================================================
#define misGetMacro(name,type) \
	public:\
virtual type Get##name () { \
	return this->m_##name; \
  } 


#define misAbstractGetMacro(name,type) \
	public:\
	virtual type Get##name () =0; 
	
//===========================================================================

// Set character string.  Creates member Set"name"() 
// (e.g., SetFilename(char *));
//
#define misSetStringMacro(name) \
virtual void Set##name (const char* _arg) \
  { \
   if ( this->name == NULL && _arg == NULL) { return;} \
  if ( this->name && _arg && (!strcmp(this->name,_arg))) { return;} \
  if (this->name) { delete [] this->name; } \
  if (_arg) \
	{ \
	size_t n = strlen(_arg) + 1; \
	char *cp1 =  new char[n]; \
	const char *cp2 = (_arg); \
	this->name = cp1; \
	do { *cp1++ = *cp2++; } while ( --n ); \
	} \
   else \
	{ \
	this->name = NULL; \
	} \
  this->Modified(); \
  } 

//
// Get character string.  Creates member Get"name"() 
// (e.g., char *GetFilename());
//
#define misGetStringMacro(name) \
virtual char* Get##name () { \
   return this->name; \
  } 

#define misCasacdeUp(eventType,objectName)\
if (typeid(event)==typeid(##eventType))\
		{\
			this->##objectName->InvokeEvent(event);\
		}


#define misPreDefinitionMacro(selfClassName, superClassName)\
	public:\
	typedef selfClassName                    Self;\
	typedef superClassName                   Superclass;\
	typedef ::itk::SmartPointer<Self>        Pointer;\
	typedef ::itk::SmartPointer<const Self>  ConstPointer;

	//#define  FindAndReturnInListByName(argument,listName,type) bool FindIn##listname(argument,type&  res) \
//{\	
//    ListType::const_iterator   iter=##this->listName.begin();\
//	ListType::const_iterator   iterEnd=##this->listName.end();\
//	while (iter!=iterEnd)\
//	{\
//	if (iter==##argument)\
//	{\
//			rs= *iter;\
//				return true;\
//	}\
//		iter++;\
//	}\
//	return false;\
//}\


//	 


#define misExtrcatElementFromListMacro(listType, listElemetType)\
protected:\
	listElemetType* ExtrcatFromList##listType (listType _arglistName, int _argid)\
	{\
	 listType::const_iterator   ierator;\
	 ierator = _arglistName.begin();\
	 if ( (_argid <0) || (_argid >=  _arglistName.size()) )\
			return 0;\
for (int i=0; i<_argid; i++)\
	 {\
	   ierator++;\
	 }\
	 listElemetType*  pElemet;\
	 pElemet = ierator;\
	 return pElemet;\
}
#define  misErrorMessageBox(inputMsg)\
	string message;\
	message.append("Source File:");\
	message.append(__FILE__);\
	message.append("\n");\
	char str[5];\
	_itoa(__LINE__,str,10);\
	message.append("Line Number: ");\
	message.append(str);\
	message.append("\n");\
	message.append(inputMsg);\
	MessageBoxA(0,(char*)message.c_str(),"Error ",0)  ;\
	//DebugBreak();

 

	
#define  misLOgViwerMacro(inputMsg)\
misLogToEventViewer* pLogViwer=misLogToEventViewer::GetInstance();\
pLogViwer->WriteEntry(inputMsg);\
delete pLogViwer;



#define RreturnPathClassMacro(TextMessge,mLogger)\
	string FileName(__FILE__);\
	string ClassName;\
	ClassName= FileName.substr(2);\
	string stringmessage;\
	stringmessage=ClassName.append ("::");\
	stringmessage=stringmessage.append(TextMessge);\
	mLogger->Debug(stringmessage);

#define RreturnClassName()\
string FileName(__FILE__);\
string ClassName;\
ClassName= FileName.substr(2);

#define CreateMisLinearTexture(image,pTexture)\
misImageToTexturePropertyConvertor convertor;\
misTexturePropertyStruct texProp = convertor(image);\
pTexture= new misOpenglTexture(texProp,tgt::Texture::Filter::LINEAR);


