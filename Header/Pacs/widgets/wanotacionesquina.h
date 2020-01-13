/*
 *  
 *  $Id: wanotacionesquina.h $
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
#include <api/iwidgets.h>
#include <api/api.h>
#include <api/ianotador.h>
#include <api/observers/ieventsobserver.h>
#include <vector>
#include <list>
#include "openglhelper.h"

#define TAMFUENTE 12.0f
#define TAMFUENTE_MIN 10.0f
#define PROPVIEWPORT 0.40f // Proporcion maxima del viewport, tanto de ancho como de alto. (25%)

namespace GNC {
	namespace GCS {

		namespace Widgets {

			class EstadoInterno;
			class Anotaciones;
			class OrientationMarks;

			//----------------------------------------------------------------------------------------------------
			//region Widget anotador
			class EXTAPI WAnotador : public GNC::GCS::Widgets::IWidget, public GNC::GCS::IEventsObserver {
			public:

				WAnotador(GNC::GCS::IAnotador* annotator, IWidgetsManager* pManager, long vid, const char* nombre, long gid);

				~WAnotador();

				virtual void LiberarRecursos(GNC::GCS::IWidgetsRenderer* renderer);
			//endregion

			//----------------------------------------------------------------------------------------------------
			//region "Interfaz generica"
			public:
				virtual void OnMouseEvents(GNC::GCS::Events::EventoRaton&);

				virtual void OnKeyEvents(GNC::GCS::Events::EventoTeclado&);

				virtual bool HitTest(float x, float y, const GNC::GCS::Vector& umbral);

				virtual bool HitTest(GNC::GCS::Vector* vertices, int numVertices);

				virtual void Render(GNC::GCS::Contexto3D* c);

				virtual void OffscreenRender(Contexto3D* c);

				virtual void Modificar(bool modificar);

				virtual void Seleccionar(bool seleccionado);

				virtual void Iluminar(bool iluminado);

				virtual void Ocultar(bool oculto);

				virtual void RecalcularEstaticas(Anotaciones* pAnotaciones, GNC::GCS::Contexto3D* c);

				virtual void RecalcularPosicion(OrientationMarks* pAnotaciones, GNC::GCS::Contexto3D* c);

			//endregion

				//----------------------------------------------------------------------------------------------------
				//region "Interfaz especifica"
			public:
				virtual void SetAnotador(GNC::GCS::IAnotador* anotador);
				virtual void SetTextColor(const GNC::GCS::GLHelper::TColor& color);
				GNC::GCS::IAnotador* m_pAnnotator;
				
				//endregion

			public:

				typedef enum TPosicionAnotacion {
					TP_TopLeft = 0,
					TP_TopRight,
					TP_BottomLeft,
					TP_BottomRight,
					TP_Top,
					TP_Right,
					TP_Bottom,
					TP_Left,
					TP_NumPosiciones
				} TPosicionAnotacion;

				//endregion

				void setVolatileProperty(TPosicionAnotacion pos, bool enabled);

				void InvalidarTodas();

			//----------------------------------------------------------------------------------------------------
			//region "Interfaz de eventos ginkgo"
			public:

				virtual void ProcesarEvento(GNC::GCS::Events::IEvent *evt);

			//endregion

			//----------------------------------------------------------------------------------------------------
			//region "Estado interno"
			protected:

				EstadoInterno* m_Estado;				
				GNC::GCS::GLHelper::TColor m_color;
				std::string m_CachedPatientPosition;

				bool m_volatileProperty[TP_NumPosiciones];

			//endregion

			};
			//endregion
		}
	}
}
