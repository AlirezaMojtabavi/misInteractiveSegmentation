/*
 *  
 *  $Id: ventanacontrollogs.h $
 *  Ginkgo CADx Project
 *
 *  Copyright 2008-14 MetaEmotion S.L. All rights reserved.
 *  http://ginkgo-cadx.com
 *
 *  This file is licensed under LGPL v3 license.
 *  See License.txt for details
 *
 *
 */
#pragma once
#include <list>
#include <api/controllers/icontroladorlog.h>
#include <main/controllers/log4cplus/logdefines.h>
#include <wx/event.h>
#include "ventanacontrollogsbase.h"

//DEFINE_EVENT_TYPE(wxEVT_LOG_ASYNC)
/*
BEGIN_DECLARE_EVENT_TYPES()
DECLARE_EVENT_TYPE( wxEVT_LOG_ASYNC, wxNewEventType() )
END_DECLARE_EVENT_TYPES()*/

const wxEventType wxEVT_LOG_ASYNC = wxNewEventType();

extern const wxEventType wxEVT_LOG_ASYNC;

class LogAsyncEvent : public wxEvent
{
public:
	LogAsyncEvent() { SetEventType(wxEVT_LOG_ASYNC); }

	LogAsyncEvent(const GNC::GCS::Logging::LogEvent& logEvent) : LogEvent(logEvent) { SetEventType(wxEVT_LOG_ASYNC); }

	LogAsyncEvent(const LogAsyncEvent& event) : wxEvent(event), LogEvent(event.LogEvent) {}

	virtual wxEvent *Clone() const { return new LogAsyncEvent(*this); }

    const GNC::GCS::Logging::LogEvent LogEvent;

private:
    DECLARE_DYNAMIC_CLASS_NO_ASSIGN(LogAsyncEvent)
};

typedef void (wxEvtHandler::*LogAsyncEventFunction)(LogAsyncEvent&);

#define LogAsyncEventHandler(func) \
(wxObjectEventFunction)(wxEventFunction)wxStaticCastEvent(LogAsyncEventFunction, &func)

#define EVT_LOG_ASYNC(func) \
wx__DECLARE_EVT0(wxEVT_LOG_ASYNC, LogAsyncEventHandler(func))

namespace GNC {
	namespace GUI {

		class VentanaControlLogs : public VentanaControlLogsBase, public GNC::GCS::Logging::ILogger
		{
		public:
			//singleton
			static VentanaControlLogs* Instance();
			static void CerrarSiAbierta();
			void Refrescar();

			//region Interfaz ILogger

			virtual void Append(const GNC::GCS::Logging::LogEvent& le);

			//endregion

		protected:
			static VentanaControlLogs*  m_pInstance;
			GNC::GCS::IControladorLog::MapaLogLevels m_MapaLogLevels;
			bool m_needRefresh;

			VentanaControlLogs();
			~VentanaControlLogs();

			virtual void OnClose(wxCloseEvent& event);
			virtual void OnLogAsync(LogAsyncEvent& event);

			virtual void OnInternalIdle();

			virtual void OnLimpiarClick( wxCommandEvent& /*event*/ ) { LimpiarRegistros(); }
			virtual void OnLimpiarRegistros( wxCommandEvent& /*event*/ ) { LimpiarRegistros(); }

			virtual void OnGuardarRegistros( wxCommandEvent& event );
			virtual void OnNivelChoice( wxCommandEvent& event );

			virtual void OnSalirClick( wxCommandEvent& event );
			virtual void OnKeyDown( wxKeyEvent& event );
			void LimpiarRegistros();

		};
	}
}
