/*
*  
*  $Id: incomingdicomassociationcommand.h $
*  Ginkgo CADx Project
*
*  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
*  http://ginkgo-cadx.com
*
*  This file is licensed under LGPL v3 license.
*  See License.txt for details
*
*/
#pragma once
#include <api/globals.h>
#include <api/icommand.h>

struct T_ASC_Association;
struct T_DIMSE_Message;
class OFCondition;

namespace GADAPI {

	namespace PACS {
		class MISDLLEXPORT IncomingDicomAssociationCommandParams : public GNC::GCS::IComandoParams {
		public:
			IncomingDicomAssociationCommandParams(T_ASC_Association* assoc, unsigned long rcvTimeout = 0);
			virtual ~IncomingDicomAssociationCommandParams();

			T_ASC_Association* m_pAssoc;
			long               m_rcvTimeout;
		};

		//-----------------------------------------------------------------------------------------------
		//-----------------------------------------------------------------------------------------------

		class MISDLLEXPORT IncomingDicomAssociationCommand : public GNC::GCS::IComando {
		public:
			IncomingDicomAssociationCommand(IncomingDicomAssociationCommandParams* pParams, const std::string& name="SCP-Service");
			virtual ~IncomingDicomAssociationCommand();
			static int get_all_dcmfiles_count_within_folder(std::string folder);
			static std::string SetLastDirectory();
			static std::string GetSingleImageTempDirectory();
			static std::string GetTempImageFullPath();

		protected:

			virtual void Execute();
			virtual void Update();

			void echoSCP( T_ASC_Association * assoc, T_DIMSE_Message * msg, unsigned char presID, OFCondition* cond);
			void storeSCP( T_ASC_Association * assoc, T_DIMSE_Message * msg, unsigned char presID, OFCondition* cond);

			IncomingDicomAssociationCommandParams* m_pIncommingassociationParams;

			std::string ambitolog;
			std::list<std::string> m_DicomFileList;
			std::string m_Error;
			bool isLastDirSet;
		};

	}
}