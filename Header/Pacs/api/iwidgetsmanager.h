/*
 *  
 *  $Id: iwidgetsmanager.h $
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
#include <api/api.h>
#include <api/math/geometry.h>
#include <api/ievento.h>
#include <api/iwidgetsproperties.h>

// Forward declarations

namespace GNC {
	namespace GCS {
		class IEventsController;
		class IWidgetsRenderer;
		class IContexto;
		class IAnotador;
		class IImpresorOverlay;

		namespace Widgets {
			class IWidget;
			class IPublicadorEventos;
			class IObservadorWidget;
			class IWidgetBuilder;
		}
	}
}

// Forward declarations

namespace GNC {
	namespace GCS {

		class EXTAPI ListaWidgets : public std::list< GNC::GCS::Widgets::IWidget*, std::allocator<GNC::GCS::Widgets::IWidget*> >{};
		class EXTAPI ListaBuilders : public std::list< GNC::GCS::Widgets::IWidgetBuilder*, std::allocator<GNC::GCS::Widgets::IWidgetBuilder*> >{};
		class EXTAPI ListaObservadores : public std::list<GNC::GCS::Widgets::IObservadorWidget* , std::allocator<GNC::GCS::Widgets::IObservadorWidget*> > {};
		class EXTAPI ListaRenderers : public std::list<GNC::GCS::IWidgetsRenderer*, std::allocator<GNC::GCS::IWidgetsRenderer*> > {};

		class EXTAPI IWidgetsManager : public GNC::GCS::Events::ISubscriptorEventos {

		public:

			IWidgetsManager(GNC::GCS::IVista* pVista);

			virtual ~IWidgetsManager();
			
			inline GNC::GCS::IVista* GetVista(){
				return m_pView;
			}

			inline void MarcarModificado(bool modificado) {
				m_Modified = modificado;
			}

			inline bool EstaModificado() {
				return m_Modified;
			}

		//----------------------------------------------------------------------------------------------------
		//region "Interfaz de registro de IWidgetBuilder's"

		protected:
			ListaBuilders m_pBuilders;

		public:
			inline void RegisterBuilder(GNC::GCS::Widgets::IWidgetBuilder* pBuilder)
			{
				m_pBuilders.push_back(pBuilder);
			}

			inline void UnRegisterBuilder(GNC::GCS::Widgets::IWidgetBuilder* pBuilder)
			{
				for (ListaBuilders::iterator it = m_pBuilders.begin(); it != m_pBuilders.end(); ++it) {
					if ( (*it) == pBuilder) {
						m_pBuilders.erase(it);
						break;
					}
				}
			}

		//endregion

		//----------------------------------------------------------------------------------------------------
		//region "Interfaz de registro de IWidget's"

		public:			
			typedef ListaWidgets::iterator IteradorListaWidgets;

		protected:
			ListaWidgets m_Widgets;

		public:

			virtual void Enable(bool enabled);
			virtual bool IsEnabled();

			virtual void InsertarWidget(GNC::GCS::Widgets::IWidget* pWidget, bool propagarEvento=true) = 0;

			/** Removes a widget. Note: Frees the pWidget pointing! **/
			virtual void EliminarWidget(const GNC::GCS::Widgets::IWidget* pWidget, bool propagarEvento=true) = 0;

			/** Removes a widget. Note: Frees the pWidget pointing! **/
			virtual void EliminarWidget(GNC::GCS::IWidgetsManager::IteradorListaWidgets& it, bool propagarEvento=true) = 0;

			/** Removes all widgets. Note: Frees the pWidget pointers! **/
			virtual void EliminarTodosLosWidgets(bool propagarEventos=true) = 0;

			/** Remove all widgets except anyone with this tid **/
			virtual void RemoveAllWidgetsExceptTID(long tid, bool propagateEvents=true) = 0;		
			
			virtual void RemoveUserAnnotationWidgets(bool propagateEvents=true) = 0;

			virtual void OcultarTodosLosWidgets(bool ocultar, long GID) = 0;

			/** Set visible on all widgets matching TID **/
			virtual void SetVisibleByTID(bool visible, long tid) = 0;

			/** Removes all widgets. Note: Frees the pWidget pointers! **/
			virtual void EliminarTodosLosWidgets(long GID) = 0;

			virtual void OcultarWidgetsDeSubVista(bool ocultar, long vid) = 0;

			virtual GNC::GCS::ListaWidgets& GetListaWidgets() = 0;

			virtual void GetListaWidgetsSubVista(long vid, GNC::GCS::ListaWidgets& lista) = 0;

		//endregion

		//----------------------------------------------------------------------------------------------------
		//region "Interfaz de registro del IWidgetsRenderer"

		public:

			virtual void SetRendererActivo(GNC::GCS::IWidgetsRenderer* pRenderer) = 0;
			
			inline GNC::GCS::IWidgetsRenderer* GetRendererActivo()
			{
				return m_pRendererActivo;
			}

			virtual void InsertarRenderer(GNC::GCS::IWidgetsRenderer* pRenderer) = 0;

			virtual void EliminarRenderer(GNC::GCS::IWidgetsRenderer* pRenderer) = 0;

			virtual void LiberarRecursos(GNC::GCS::IWidgetsRenderer* pRenderer) = 0;

		protected:
			GNC::GCS::IWidgetsRenderer* m_pRendererActivo;			

			ListaRenderers m_Renderers;

		//endregion

		//----------------------------------------------------------------------------------------------------
		//region "Interfaz de Observadores"

		public:			
			typedef ListaObservadores::iterator IteradorListaObservadores;

		protected:
			ListaObservadores m_Observadores;

		public:
			
			void InsertarObservador(GNC::GCS::Widgets::IObservadorWidget* observador);

			void EliminarObservador(GNC::GCS::Widgets::IObservadorWidget* observador);
			
			virtual void NotificarCreacion(GNC::GCS::Widgets::IWidget* pWidget) = 0;

			virtual void NotificarDestruccion(GNC::GCS::Widgets::IWidget* pWidget) = 0;

			virtual void NotificarModificacion(GNC::GCS::Widgets::IWidget* pWidget) = 0;

		//endregion

		//----------------------------------------------------------------------------------------------------
		//region "Interfaz general"
			virtual void CrearWidgetAnotador(GNC::GCS::IAnotador* pAnotador) = 0;
			virtual void EnableAnotacionDinamica(bool enable) = 0;
			virtual void MostrarOcultarAnotador() = 0;
			virtual bool IsVisibleAnotador() = 0;
		//endregion

		//----------------------------------------------------------------------------------------------------
		//region "Interfaz general"

		public:

			virtual void Render() = 0;
			
			virtual void TickAnimation(double freq) = 0;

			virtual void EnableAnimation() = 0;

			virtual void DisableAnimation() = 0;

			/* Este metodo solo debe ser invocado por IWidgetsRenderer */
			virtual void RenderPrivate(Contexto3D* c) = 0;

			/*imprime los widgets sobre la imagen que recibe, definida por anchura y altura*/
			virtual void OffScreenRender(GNC::GCS::Contexto3D* c) = 0;

			/* Metodo que indica al manager que es preciso hacer un render() */
			virtual void Modificado() = 0;

			virtual void ModificadoPorWidget(GNC::GCS::Widgets::IWidget* w) = 0;

			virtual void OnMouseEvents(GNC::GCS::Events::EventoRaton&) = 0;

			virtual void OnKeyEvents(GNC::GCS::Events::EventoTeclado&) = 0;

			virtual void DefaultMouseEventProcess(GNC::GCS::Events::EventoRaton& evento) = 0;

			virtual void DefaultKeyEventProcess(GNC::GCS::Events::EventoTeclado& event) = 0;

			// Propaga a todos los widgets no ocultos un hit test de seleccion. Los widgets se seleccionan si validan un hittest con el bounding box especificado.
			virtual void PropagarHitTestSeleccion(GNC::GCS::Vector* vertices, int numVertices) = 0;

		protected:
			bool          m_Modified;
			GNC::GCS::IVista*		  m_pView;

		//endregion

		//----------------------------------------------------------------------------------------------------
		//region "Interfaz de selecciones"

		protected:
			float m_BoundingBoxSeleccion[4];
			ListaWidgets m_WidgetsSeleccionados;
			bool m_Enabled;

		//endregion

		//----------------------------------------------------------------------------------------------------
		//region "Interfaz de acceso al sistema de eventos ginkgo"

		public:

			virtual void LanzarEventoCreacion(GNC::GCS::Widgets::IWidget* w) = 0;
			virtual void LanzarEventoModificacion(GNC::GCS::Widgets::IWidget* w) = 0;
			virtual void LanzarEventoDestruccion(GNC::GCS::Widgets::IWidget* w) = 0;

		//endregion

		//----------------------------------------------------------------------------------------------------
			virtual void SetCursor(GNC::GCS::Widgets::TipoCursor cursor) = 0;
			GNC::GCS::Widgets::TipoCursor m_cursor;
		//endregion

		};
	}
}
