/*
 *  
 *  $Id: wrectangulo.h $
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
#include <vector>

namespace GNC {
	namespace GCS {
		namespace Widgets {
			//---------------------------------------------------------------------

			class EXTAPI WRectanguloBuilder : public GNC::GCS::Widgets::IWidgetBuilder {
			public:

				typedef GNC::GCS::Vector                 TVector;
				typedef GNC::GCS::Events::EventoRaton   TEventoRaton;
				typedef GNC::GCS::Events::EventoTeclado TEventoTeclado;
				typedef GNC::GCS::IWidgetsManager        TWidgetsManager;
				typedef GNC::GCS::Widgets::IWidget       TWidget;

				WRectanguloBuilder(TWidgetsManager* pManager, const GNC::GCS::TriggerButton& buttonMask, long gid);

				~WRectanguloBuilder();

				virtual void OnMouseEvents(TEventoRaton& event);
				virtual void OnKeyEvents(TEventoTeclado& event);

				virtual void Render(GNC::GCS::Contexto3D* c);

				virtual GNC::GCS::Widgets::TipoCursor GetCursor();

				//region "Helpers"

				bool         m_Dentro;
				//endregion


			protected:
				TVector                  m_NodoMoviendose;  // Cursor
				TVector                  m_Start;           // Origen del boundingBox
				TVector                  m_Stop;            // Destino del boundingBox

				TVector                  m_Vertices[4];     // Vertices del bounding box.

				bool                     m_MouseDown;
				Estado                   m_Estado;
			};

			//---------------------------------------------------------------------

			class EXTAPI WRectangulo : public GNC::GCS::Widgets::IWidget {

			//region "Constructor y destructor"

			public:
				typedef GNC::GCS::Nodo                   TNodo;
				typedef GNC::GCS::Vector                 TVector;
				typedef GNC::GCS::Matriz                 TMatriz;
				typedef GNC::GCS::Contexto3D             TContexto;
				typedef GNC::GCS::Events::EventoRaton   TEventoRaton;
				typedef GNC::GCS::Events::EventoTeclado TEventoTeclado;

				WRectangulo(TVector bb[4], IWidgetsManager* pManager, long vid, const char* nombre, long gid);

				~WRectangulo();

				//endregion

				//region "Interfaz especifica"

				virtual void OnMouseEvents(TEventoRaton&);

				virtual void OnKeyEvents(TEventoTeclado&);

				virtual bool HitTest(float x, float y, const GNC::GCS::Vector& umbral);

				virtual bool HitTest(TVector* vertices, int numVertices);

				virtual void Render(TContexto* c);

				virtual void OffscreenRender(Contexto3D* c);

				virtual bool SoportaAutoBorrado() const {
					return true;
				}

				//endregion

				//region "Estado interno"
			private:
				bool            m_MouseDown;
				TVector         m_PosCursor;
				//endregion

				//region "Propiedades geometricas"
			public:
				TNodo m_Vertices[4];

				friend std::ostream& operator<<(std::ostream& out, const WRectangulo& w) {
					out << "[ Rect = [ " << w.m_Vertices[0] << ", " << w.m_Vertices[1] << ", " << w.m_Vertices[2] << ", " << w.m_Vertices[3] <<  " ],  GID=" << w.m_GID << ", TID=" << w.m_TID << " UID=" << w.m_UID << " ]";
					return out;
				};

				friend std::ostream& operator<<(std::ostream& out, const WRectangulo* w) {
					if (w == NULL) {
						out << "[ NULL ]";
					}
					else {
						out << *w;
					}
					return out;
				};

			public:
				//endregion

				//region "Propiedades radiometricas"

				//endregion
			};
		};
	};
};
