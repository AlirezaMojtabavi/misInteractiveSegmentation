#ifndef mis4RenderPack_H
#define mis4RenderPack_H

#include "misWindow.h"
#include "VisualizationGeneralTypes.h"
 

class mis4RenderPack
{
	public:

		misWindow* GetWindow(IMAGEORIENTATION ornt) const
		{ 
			misWindow* win = 0;;
			switch (ornt)
			{
				case AXIAL:
					win = this->GetAxialWindow();
					break;
				case CORONAL:
					win = this->GetCoronalWindow();
					break;
				case SAGITTAL:
					win = this->GetSagittalWindow();
					break;
				case UNKnownDirection:
					win = this->GetVolumeWindow();
					break;
			}
			return win;
		}

		void SetWindow(misWindow* val , IMAGEORIENTATION ornt)
		{
			if (val)
			{
				switch (ornt)
				{
				case AXIAL:
					this->SetAxialWindow(val);
					break;
				case CORONAL:
					this->SetCoronalWindow(val);
					break;
				case SAGITTAL:
					this->SetSagittalWindow(val);
					break;
				case UNKnownDirection:
					this->SetVolumeWindow(val);
					break;
				}
			}
			else
				_ASSERT( 0 == 1);
		}
		misWindow* GetAxialWindow() const { return m_AxialWindow; }
		void SetAxialWindow(misWindow* val) { m_AxialWindow = val; }
		misWindow* GetCoronalWindow() const { return m_CoronalWindow; }
		void SetCoronalWindow(misWindow* val) { m_CoronalWindow = val; }
		misWindow* GetSagittalWindow() const { return m_SagittalWindow; }
		void SetSagittalWindow(misWindow* val) { m_SagittalWindow = val; }
		misWindow* GetVolumeWindow() const { return m_VolumeWindow; }
		void SetVolumeWindow(misWindow* val) { m_VolumeWindow = val; }

	protected:

		misWindow*  m_AxialWindow;
		misWindow*  m_CoronalWindow;
		misWindow*  m_SagittalWindow;
		misWindow*  m_VolumeWindow;

 };

#endif
//===========================================================================