/*
 *  $Id: startupform.h $
 *  Proyecto Ginkgo
 *
 *  Copyright 2008 MetaEmotion S.L. All rights reserved.
 *
 */
#pragma once
#include "startupformbase.h"
#include "startupview.h"

namespace GNC {
	namespace GUI {
		class StartUpForm: public StartUpFormBase {
		public:
			StartUpForm(GNC::GCS::IVista* pView);
			~StartUpForm();
		protected:
			virtual void OnEraseBackground(wxEraseEvent& event);
			//virtual void OnPaint(wxPaintEvent &event);
			GNC::GCS::IVista* IView;
		};
	}
}