#pragma once

#include "IImage.h"
#include "misObject.h"
#include "misOpenglTexture.h"

class vtkTexture;
class vtkImageMapToWindowLevelColors;

enum LayerStatus
{
	UnActived = 0,
	Actived
};

// alyer a path from source  to Texture
class  misStrctLayer
{
public:
	misStrctLayer();

	std::string GetName() const { return m_Name; }
	void SetName(std::string val) { m_Name = val; }

	bool GetGrayScaleMapping() const { return m_GrayScaleMapping; }
	void SetGrayScaleMapping(bool val) { m_GrayScaleMapping = val; }
	void GrayScaleMappingOff();
	void GrayScaleMappingOn();

	LayerStatus GetLayerStatus() const { return m_LayerStatus; };
	void SetLayerStatus(LayerStatus status) { m_LayerStatus = status; };

	bool GetLoadStatus() const { return m_IsLoaded; };
	void SetLoadStatus(bool loadStatus) { m_IsLoaded = loadStatus; };

	std::shared_ptr<IImage> GetSource() const;
	void SetSource(std::shared_ptr<IImage> val);

	misWindowLevelStr GetWinlevel() const;
	void SetWinlevel(misWindowLevelStr val);
private:

	misWindowLevelStr m_Winlevel;
	bool m_GrayScaleMapping;
	bool m_IsLoaded;
	LayerStatus m_LayerStatus;

	bool  m_Enable;
	std::string   m_Name;
	void Enable() ;
	void Disable();
	bool  IsEnabled() const;
	std::shared_ptr<IImage> m_pSource;


};

 