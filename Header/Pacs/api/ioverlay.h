/*
 *  
 *  $Id: ioverlay.h $
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

#include <api/math/geometry.h>

namespace GNC {
	namespace GCS {
		class Contexto3D;
		
		namespace Widgets {
			class IWidget;
			class IWidgetBuilder;
		}
	}
}

namespace GNC {
	namespace GCS {
		
		/* Interfaz que se ocupa de imprimir (OpenGL + Cairo) datos referidos a un widget o a un widgetsRenderer */
		class IImpresorOverlay {
		public:
			virtual ~IImpresorOverlay() {}

			virtual void ImprimirOverlay(GNC::GCS::Widgets::IWidget* w, GNC::GCS::Contexto3D* c , GNC::GCS::Vector& boundingBox) = 0;
			virtual void ImprimirOverlay(GNC::GCS::Widgets::IWidgetBuilder* wb, GNC::GCS::Contexto3D* c, GNC::GCS::Vector& boundingBox) = 0;
		};
		
	}
}
