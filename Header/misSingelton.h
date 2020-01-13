#pragma once
template<typename T>
 class misSingleton
	 
{
	 
public:
	 static T* GetInstance()
		 
	{
		static T* me=new T;
		return me;
		 
	}
 
};
