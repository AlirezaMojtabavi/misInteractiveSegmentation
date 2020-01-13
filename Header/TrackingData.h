#pragma once
using namespace System;
using namespace System::Windows;
using namespace System::Reflection;
using namespace System::Windows::Controls;
using namespace System::Windows::Markup;
using namespace System::IO;
using namespace System::Xml;
using namespace System::Windows;
using namespace System::Windows::Controls;
using namespace System::Windows::Data;
using namespace System::Windows::Input;
using namespace System::Windows::Interop;
using namespace System::Collections::ObjectModel;
ref class TrackingDataItem
{

private:
 
            String^ m_Name;
			int m_index;
			float m_tx;
			float m_ty;
			float m_tz;
			String^ m_Status;
public:
			


             property  String^ Name
            {
               String^ get() { return m_Name; }
               void set(String^ value) { m_Name = value; }
            }

           property   int Index  
            {
               int  get() { return m_index; }
               void  set(int value) { m_index = value; }
            }
            property  int TX  
            {
                int get() { return m_tx; }
                void set(int value) { m_tx = value; }
            }
            property  int TY  
            {
                int get() { return m_ty; }
                void set(int value) { m_ty = value; }
            }

            property  int TZ  
            {
                int get() { return m_tz; }
               void  set(int value) { m_tz = value; }
            }
			           
			property  String^ Status
            {
                String^ get() { return m_Status; }
                void set(String^ value) { m_Status = value; }
            }



			TrackingDataItem(String^  name ,int index,int x,int y,int z,String^ status)
            {
				this->Name=name;
				this->Index=index;
				this->TX=x;this->TY=y;this->TZ=z;
				this->Status=status;

            }
};
