#ifndef _misAllMessage_
#define _misAllMessage_

#pragma once

#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#using <System.Xml.dll>
#using <System.dll>

using namespace System;
using namespace System::Xml;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Collections::ObjectModel;

#include "misMessageTypeControler.h"

ref class misAllMessages
{
	private :

		static void LoadMessages()
		{
			msgXmlDocument = gcnew XmlDocument();

			if( File::Exists(messagesFilePath) )
			{
				msgXmlDocument->Load(messagesFilePath);
				System::Xml::XmlElement^ elmMessages = msgXmlDocument->DocumentElement;
				System::Xml::XmlNodeList^ lstMessages = elmMessages->ChildNodes;

				for each (System::Xml::XmlNode^ node in lstMessages)
				{
					misMessageTypeControler^ message = gcnew misMessageTypeControler();

					message->messageName  = node->FirstChild->InnerText ;

					message->messageValue = node->FirstChild->NextSibling->InnerText ;

					#pragma region Set messageBoxType

					if ( node->FirstChild->NextSibling->NextSibling->InnerText == "Question")
						message->messageBoxType =WrapperGUIBase::misMessageBoxType::Question;

					else if ( node->FirstChild->NextSibling->NextSibling->InnerText == "Warning")
						message->messageBoxType = WrapperGUIBase::misMessageBoxType::Warning;

					else if ( node->FirstChild->NextSibling->NextSibling->InnerText == "None")
						message->messageBoxType = WrapperGUIBase::misMessageBoxType::NONE;

					else if ( node->FirstChild->NextSibling->NextSibling->InnerText == "Information")
						message->messageBoxType = WrapperGUIBase::misMessageBoxType::Information;

					else if ( node->FirstChild->NextSibling->NextSibling->InnerText == "Error")
						message->messageBoxType = WrapperGUIBase::misMessageBoxType::Error;

					#pragma endregion

					#pragma region Set messageBoxButtons

					if ( node->FirstChild->NextSibling->NextSibling->NextSibling->InnerText == "Ok")
						message->messageBoxButtons = WrapperGUIBase::misMessageBoxButtonsOrder::ok;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->InnerText == "OkCancel")
						message->messageBoxButtons = WrapperGUIBase::misMessageBoxButtonsOrder::OkCancel;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->InnerText == "YesNo")
						message->messageBoxButtons = WrapperGUIBase::misMessageBoxButtonsOrder::YesNo;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->InnerText == "YesNoCancel")
						message->messageBoxButtons = WrapperGUIBase::misMessageBoxButtonsOrder::YesNoCancel;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->InnerText == "AbortRetryIgnore")
						message->messageBoxButtons = WrapperGUIBase::misMessageBoxButtonsOrder::AbortRetryIgnore;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->InnerText == "RetryCancel")
						message->messageBoxButtons = WrapperGUIBase::misMessageBoxButtonsOrder::RetryCancel;

					#pragma endregion

					#pragma region Set messageBoxDefaultButton

					if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "Ok")
						message->messageBoxDefaultButton = WrapperGUIBase::misMessageBoxButtons::Ok;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "Cancel")
						message->messageBoxDefaultButton = WrapperGUIBase::misMessageBoxButtons::Cancel;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "Yes")
						message->messageBoxDefaultButton = WrapperGUIBase::misMessageBoxButtons::Yes;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "No")
						message->messageBoxDefaultButton = WrapperGUIBase::misMessageBoxButtons::No;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "Abort")
						message->messageBoxDefaultButton = WrapperGUIBase::misMessageBoxButtons::Abort;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "Retry")
						message->messageBoxDefaultButton =WrapperGUIBase::misMessageBoxButtons::Retry;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "INGORE")
						message->messageBoxDefaultButton =WrapperGUIBase::misMessageBoxButtons::Ignore;

					#pragma endregion

					//#pragma region Set messageBoxSize

					//if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "Small" )
					//	message->messageBoxSize = misEnumMessageType::misMessageBoxSize::Small;

					//else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "Medium" )
					//	message->messageBoxSize = misEnumMessageType::misMessageBoxSize::Medium;

					//else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "Large" )
					//	message->messageBoxSize = misEnumMessageType::misMessageBoxSize::Large;

					//#pragma endregion

					//#pragma region Set needCheckBox Property

					//if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "True" )
					//	message->needCheckBox = true;

					//else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "False" )
					//	message->needCheckBox = false;

					//#pragma endregion

					/*#pragma region Set mustShow Property

					if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "True" )
						message->mustShow = true;

					else if ( node->FirstChild->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->NextSibling->InnerText == "False" )
						message->mustShow = false;

					#pragma endregion*/

					messageCollection->Add(message);
				}
			}
			else
			{
				System::Windows::Forms::MessageBox::Show("The file " + messagesFilePath + " was not found");
			}
		}

		static String^ messagesFilePath;

		static System::Collections::ObjectModel::Collection<misMessageTypeControler^>^ messageCollection;

		static XmlDocument^ msgXmlDocument ;

	public:

		static misMessageTypeControler^ FindMessage(String^ msgName)
		{
			messageCollection = gcnew Collection<misMessageTypeControler^>();

 			messagesFilePath = "./data/messages.xml";

			//messagesFilePath = "D:\\misProject1\\misSoloution\\ConcoleApplicationWithItk\\messages.xml";

			LoadMessages();

			misMessageTypeControler^ returnValue  = gcnew misMessageTypeControler();
			returnValue->mustShow = true;
			returnValue->needCheckBox = false;

			for each ( misMessageTypeControler^ message in messageCollection)
				if ( message->messageName == msgName )
				{
					returnValue = message;
					returnValue->IsExist = true;
					return returnValue;
				}

			return returnValue;
		}
};

#endif