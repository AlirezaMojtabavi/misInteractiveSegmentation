/*
 *  
 *  $Id: iobservadorpoligono.h $
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
namespace GNC {
	namespace GCS {
		namespace Widgets {
			class WPoligono;

			namespace Observadores {

				/* Observador especifico de la herramienta lazo */
				class IObservadorPoligono {
				public:

					virtual ~IObservadorPoligono(){}

					virtual void OnPoligonoCreado(GNC::GCS::Widgets::WPoligono* pPoligono) = 0;
					virtual void OnPoligonoModificado(GNC::GCS::Widgets::WPoligono* pPoligono) = 0;
					virtual void OnPoligonoDestruido(GNC::GCS::Widgets::WPoligono* pPoligono) = 0;
				};
			}

			namespace Notificadores {
				class INotificadorPoligono {

				protected:
					GNC::GCS::Widgets::Observadores::IObservadorPoligono* m_pObservadorPoligono;

				public:
					INotificadorPoligono() {
						m_pObservadorPoligono = NULL;
					}

					INotificadorPoligono(GNC::GCS::Widgets::Observadores::IObservadorPoligono* pObservador) {
						m_pObservadorPoligono = pObservador;
					}

					virtual ~INotificadorPoligono(){}

				public:
					void SetObservador(GNC::GCS::Widgets::Observadores::IObservadorPoligono* pObservador)
					{
						m_pObservadorPoligono = pObservador;
					}

					virtual void NotificarCreacion(WPoligono* pWidget) {
						if (m_pObservadorPoligono != NULL) {
							m_pObservadorPoligono->OnPoligonoCreado(pWidget);
						}
					}

					virtual void NotificarModificacion(WPoligono* pWidget) {
						if (m_pObservadorPoligono != NULL) {
							m_pObservadorPoligono->OnPoligonoModificado(pWidget);
						}
					}

					virtual void NotificarDestruccion(WPoligono* pWidget) {
						if (m_pObservadorPoligono != NULL) {
							m_pObservadorPoligono->OnPoligonoDestruido(pWidget);
						}
					}
				};
			}
		}
	}
}
