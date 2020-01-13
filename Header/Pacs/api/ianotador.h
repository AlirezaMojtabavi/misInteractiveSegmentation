/*
 *  
 *  $Id: ianotador.h $
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
#include <api/math/geometry3d.h>

namespace GNC {
	namespace GCS {

		//region "Forward declarations"
		class Contexto3D;
		//endregion

		//-----------------------------------------------------------------------------------------------

		class IAnotador {
		public:

			virtual ~IAnotador() {}

			virtual std::string GetTopLeftAnnotation(GNC::GCS::Contexto3D* c) = 0;
			virtual std::string GetTopRightAnnotation(GNC::GCS::Contexto3D* c) = 0;
			virtual std::string GetBottomLeftAnnotation(GNC::GCS::Contexto3D* c) = 0;
			virtual std::string GetBottomRightAnnotation(GNC::GCS::Contexto3D* c) = 0;

			virtual std::string GetPatientPosition(GNC::GCS::Contexto3D* c) = 0;

			//el comportamiento por defecto de las anotaciones con posicion es el mismo que las de sin posicion
			//si se desean pueden sobreescribirse
			virtual std::string GetAnotacionPosicion(const GNC::GCS::Vector3D& wP, GNC::GCS::Contexto3D* c) = 0;
		};
	}
}
