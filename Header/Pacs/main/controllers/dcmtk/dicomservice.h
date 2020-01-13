/*
 *
 *  $Id: dicomservice.h $
 *  Ginkgo CADx Project
 *
 *  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
 *  http://ginkgo-cadx.com
 *
 *  This file is licensed under LGPL v3 license.
 *  See License.txt for details
 *
 *  Code adapted from Aeskulap
 *
 */
#pragma once

#include <api/threads/thread.h>
#include <api/dicom/idicomconformance.h>
#include <api/iproxynotificadorprogreso.h>

#include "helpers.h"

#ifdef verify
#define MACRO_QUE_ESTORBA verify
#undef verify
#endif

#include <dcmtk/dcmnet/cond.h>

#ifdef MACRO_QUE_ESTORBA
#define verify MACRO_QUE_ESTORBA
#endif

struct T_ASC_Network;

class GTLSTransportLayer;
class wxSemaphore;

namespace GIL {
	namespace DICOM {

		class Service : public GNC::GCS::Thread {
		public:

			typedef enum RoleType {
				RT_Acceptor,
				RT_Requestor,
				RT_AcceptorRequestor
			} RoleType;

			std::string ambitolog;

			GNC::IProxyNotificadorProgreso* m_pNotificadorProgreso;
			/**
			Constructors
			*/

			Service(const std::string& ambitolog);
			virtual ~Service();

			void Destroy();

			CONDITION Start();

			void Stop();

			virtual void* Task();

			CONDITION acceptAssociation();

			/*Set notificador de progreso*/
			void SetNotificadorProgreso(GNC::IProxyNotificadorProgreso* pNotificadorProgreso) {

				m_pNotificadorProgreso = pNotificadorProgreso;
			}

			
			bool NotificarProgreso(float progresoNormalizado, std::string& texto) {
			//	if(m_pNotificadorProgreso!=NULL) {
			//		return m_pNotificadorProgreso->NotificarProgreso(progresoNormalizado,texto);
			//	}
				return true;
			}
			

			/**
			Drop the association
			*/
			CONDITION Drop(CONDITION cond = DIMSE_NORMAL);

			RoleType GetRole() const
			{
				return m_Role;
			}

			void SetRole(RoleType role)
			{
				m_Role = role;
			}

			void SetLocalAET(const std::string& localAET)
			{
				this->m_localAET = localAET;
			}

			const std::string& GetLocalAET() const
			{
				return m_localAET;
			}

			void SetAcceptorPort(unsigned short port)
			{
				m_acceptorPort = port;
			}

			unsigned short GetAcceptorPort() const
			{
				return m_acceptorPort;
			}
			
			void SetTimeout(int timeout) {
				m_timeout = timeout;
			}

			int GetTimeout() const {
				return m_timeout;
			}

			unsigned long GetTid() const {
				return m_ServiceThreadId;
			}

			void SetTLS(const std::string& CliCert, const std::string& CliKey, bool validate) { m_TLS = true; m_CliCert = CliCert; m_CliKey = CliKey; m_Validate = validate; }
			
			bool IsSecure() const { return m_TLS; }

			//http://support.dcmtk.org/wiki/dcmtk/howto/useridentitynegotiation
			void SetUserPass(const std::string& PacsUser, const std::string& PacsPass) { m_UseUserPass = true; m_pacsUser = PacsUser, m_pacsPass = PacsPass; }
			bool UseUserPass() { return m_UseUserPass; }
			const std::string& GetUser() {return m_pacsUser;}
			const std::string& GetPass() {return m_pacsPass;}

			const std::string& GetCliCert() const { return m_CliCert; }
			const std::string& GetCliKey() const { return m_CliKey; }
			const bool GetValidate() const { return m_Validate; }

		protected:

			/**
			Protected data
			*/

			std::string m_localAET;

			int  m_acceptorPort;
			int  m_timeout;

			T_ASC_Network*      m_pNet;
			GTLSTransportLayer* m_pTLSLayer;

			RoleType        m_Role;
			GNC::GCS::ILockable lockerRunning;


			int m_rcvTimeout;
			int m_pollTimeout;
			int m_rcvPDUSize;
			int m_sendPDUSize;

			bool m_TLS;
			bool m_UseUserPass;
			std::string m_pacsUser;
			std::string m_pacsPass;
			std::string m_CliCert;
			std::string m_CliKey;
			bool m_Validate;

			unsigned long m_ServiceThreadId;
			
			bool m_WantToStop;
		};
	}
}
