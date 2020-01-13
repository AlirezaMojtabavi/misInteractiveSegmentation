/*
 *  
 *  $Id: toolslider.h $
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
#include "enabled_tools.h"
#if defined(ENABLE_SLIDERTOOL)
#ifndef SLIDERTOOL_H
#define SLIDERTOOL_H
#include <export/tools/itoolslider.h>
#include <widgets/wslider.h>
#include <api/api.h>

namespace GNC {

	class EXTAPI ToolSlider : public GNC::GCS::IToolSlider {
	public:
		typedef GNC::GCS::Events::EventoRaton       TEventoRaton;
		typedef GNC::GCS::Events::EventoTeclado     TEventoTeclado;
		typedef GNC::GCS::Widgets::WSliderBuilder      TBuilder;
		ToolSlider();
		~ToolSlider();

		virtual GNC::GCS::ITool* NewTool();
		virtual void Connect();
		virtual void Disconnect();
	protected:

		TBuilder*            m_pBuilder;
	};
}
#endif
#endif