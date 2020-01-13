/*
 *  
 *  $Id: wtrapezoide.h $
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
#include <api/widgetserializable.h>
#include <vector>

class vtkImageData;

namespace GNC {
	namespace GCS {
		namespace Widgets {
			//---------------------------------------------------------------------

			class WTrapezoideBuilder : public GNC::GCS::Widgets::IWidgetBuilder {
			public:

				typedef GNC::GCS::Vector TVector;
				typedef GNC::GCS::Events::EventoRaton   TEventoRaton;
				typedef GNC::GCS::Events::EventoTeclado TEventoTeclado;
				typedef GNC::GCS::IWidgetsManager        TWidgetsManager;
				typedef GNC::GCS::Widgets::IWidget       TWidget;

				WTrapezoideBuilder(TWidgetsManager* pManager, const GNC::GCS::TriggerButton& buttonMask, long gid, int numMaxTrapezoides = 0);

				~WTrapezoideBuilder();

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
				int                      m_NumMaxTrapezoides;

				TVector                  m_Vertices[4]; // Vertices del bounding box.

				bool                     m_MouseDown;
				Estado                   m_Estado;
			};

			//---------------------------------------------------------------------

			class WTrapezoide : public GNC::GCS::Widgets::IWidget, public GNC::GCS::Widgets::IWidgetSerializable {

			//region "Constructor y destructor"

			public:
				typedef GNC::GCS::Nodo   TNodo;
				typedef GNC::GCS::Vector TVector;
				typedef GNC::GCS::Matriz TMatriz;
				typedef GNC::GCS::Contexto3D TContexto;
				typedef GNC::GCS::Events::EventoRaton TEventoRaton;
				typedef GNC::GCS::Events::EventoTeclado TEventoTeclado;

				WTrapezoide(IWidgetsManager* pManager, const TVector bb[4], long vid, const char* nombre, long gid);

				~WTrapezoide();

				//endregion

				//region "Serializado y desserializado"
				WTrapezoide(IWidgetsManager* pManager, long vid, long gid, wxXmlNode* nodo);

				wxXmlNode* Serializar(const std::string& nombreMedico);
				//endregion


				//region "Interfaz especifica"

				virtual void OnMouseEvents(TEventoRaton&);

				virtual void OnKeyEvents(TEventoTeclado&);

				virtual bool HitTest(float x, float y, const GNC::GCS::Vector& umbral);

				virtual bool HitTest(TVector* vertices, int numVertices);

				virtual void Render(TContexto* c);

				virtual void OffscreenRender(Contexto3D* c);

				virtual bool EsMarcador() const
				{
					return true;
				}

				virtual bool DelimitaArea() const
				{
					return true;
				}

				virtual bool ContieneFast(const GNC::GCS::Vector& punto) const
				{
					return punto.DentroDePoligono2(m_Vertices, 4);
				}

				virtual void GetBoundingBox(GNC::GCS::Vector& bb0, GNC::GCS::Vector& bb1) const
				{
					m_Vertices[0].IniciarBoundingBox(bb0, bb1);
					for (int i = 1; i < 4; ++i) {
						m_Vertices[i].ExtenderBoundingBox(bb0, bb1);
					}
				}

				virtual void GetPosicion(GNC::GCS::Vector& posicion) const
				{
					posicion = m_Centro;
				}

				virtual void GetPuntoAnclaje(GNC::GCS::Vector& punto, const GNC::GCS::Vector& escala) const
				{
					punto = m_PosCursor + (GNC::GCS::Vector(10.0f, -10.0f) * escala);
				}

				virtual void GetCentro(GNC::GCS::Vector& centro) const
				{
					centro = m_Centro;
				}

				virtual float GetAreaMetrica() const
				{
					if (GNC::GCS::Vector::EsPoligonoSimple(m_Vertices, 4)) {
						return GNC::GCS::Vector::AreaDePoligono(m_Vertices, 4);
					}
					else {
						return std::numeric_limits<float>::quiet_NaN();
					}
				}

				virtual float GetPerimetro() const
				{
					return m_Perimetro;
				}

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
				TNodo     m_Vertices[4];
				TVector   m_Centro;
				double    m_Perimetro;
				double    m_AreaMetrica;

				friend std::ostream& operator<<(std::ostream& out, const WTrapezoide& w) {
					out << "[ Puntos = [ " << w.m_Vertices[0] << ", " << w.m_Vertices[1] << ", " << w.m_Vertices[2] << ", " << w.m_Vertices[3] <<  " ],  GID=" << w.m_GID << ", TID=" << w.m_TID << " UID=" << w.m_UID << " ]";
					return out;
				}

				friend std::ostream& operator<<(std::ostream& out, const WTrapezoide* w) {
					if (w == NULL) {
						out << "[ NULL ]";
					}
					else {
						out << *w;
					}
					return out;
				}

			public:
				//endregion

				//region "Propiedades radiometricas"

				//endregion


			public:

				virtual void InsertarPropiedades(TListaMapasPropiedades &listaMapaPropiedades);

			private:

				virtual void Recalcular();
			};
		}
	}
}
