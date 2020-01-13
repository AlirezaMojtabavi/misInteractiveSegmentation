#pragma once
 
#include "video/VideoMacroHeader.h"
#include "video/misVideoWindow.h"
#include "SampleCGB.h"
#include "SampleGrabber.h"

// window messages
#define WM_FGNOTIFY WM_USER+1

#define KSPROPERTY_VIDEOPROCAMP_FLAGS_AUTO        0X0001L
#define KSPROPERTY_VIDEOPROCAMP_FLAGS_MANUAL      0X0002L

// Macros
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }
#endif

typedef enum  { 
	KS_AnalogVideo_None         = 0x00000000,
	KS_AnalogVideo_NTSC_M       = 0x00000001,
	KS_AnalogVideo_NTSC_M_J     = 0x00000002,
	KS_AnalogVideo_NTSC_433     = 0x00000004,
	KS_AnalogVideo_PAL_B        = 0x00000010,
	KS_AnalogVideo_PAL_D        = 0x00000020,
	KS_AnalogVideo_PAL_G        = 0x00000040,
	KS_AnalogVideo_PAL_H        = 0x00000080,
	KS_AnalogVideo_PAL_I        = 0x00000100,
	KS_AnalogVideo_PAL_M        = 0x00000200,
	KS_AnalogVideo_PAL_N        = 0x00000400,
	KS_AnalogVideo_PAL_60       = 0x00000800,
	KS_AnalogVideo_SECAM_B      = 0x00001000,
	KS_AnalogVideo_SECAM_D      = 0x00002000,
	KS_AnalogVideo_SECAM_G      = 0x00004000,
	KS_AnalogVideo_SECAM_H      = 0x00008000,
	KS_AnalogVideo_SECAM_K      = 0x00010000,
	KS_AnalogVideo_SECAM_K1     = 0x00020000,
	KS_AnalogVideo_SECAM_L      = 0x00040000,
	KS_AnalogVideo_SECAM_L1     = 0x00080000,
	KS_AnalogVideo_PAL_N_COMBO  = 0x00100000
} KS_AnalogVideoStandard;

struct StreamProperties 
{
	std::string	majorType;
	std::string	subType;
	std::string	formatType;
	LONG	lWidth;
	LONG	lHeight;
	ULONG	ulSampleSize;

	StreamProperties()
	{
		Reset();
	}

private:
	void Reset()
	{
		majorType  = "Unknown";
		subType    = "Unknown";
		formatType = "Unknown";
		lWidth = 0;
		lHeight = 0;
		ulSampleSize = 0;
	}

};
typedef std::vector<std::pair<IBaseFilter*, std::wstring>> CaptureDevices;

class    misVideoStarter
{
private:
	
	ICaptureGraphBuilder2	*pBuilder;
	IGraphBuilder   *m_GraphBuilder;
	IBaseFilter     *pVCap;
	IAMCrossbar		*pXBar;
	ISampleGrabber	*pGrabber;
	IVideoWindow	*m_VideoWindow;
	
	HWND	m_MainVideoWindow;
	int		gnRecurse;

	void LogMessage(const std::string& value);

	CaptureDevices	EnumerateDevices();
	
	void AddDeviceToPreviewGraph(std::wstring deviceName);

	void FilterNotify();

	void AddDeviceToGrabGraph(std::wstring deviceName);

	void	EnumerateCrossbars(); 
	void	Render();

	void	RunTheGraph();
	void	TearDownGraph();
	void	RemoveDownstream(IBaseFilter* pBaseFltr);

	HRESULT GetUnconnectedPin(IBaseFilter* pFilter, PIN_DIRECTION PinDir, IPin** ppPin);
	HRESULT GetPin(IBaseFilter* pFilter, LPCWSTR pName, IPin** ppPin);
	HRESULT GetPin(IBaseFilter* pFilter, const GUID* pFormat, PIN_DIRECTION PinDir, IPin** ppPin);
	HRESULT ConnectFilters(IGraphBuilder* pGraph, IBaseFilter* pUpstream, LPCWSTR pUpstreamPinName, IBaseFilter* pDownstream, LPCWSTR pDownstreamPinName);
	HRESULT ConnectFilters( IGraphBuilder *pGraph, /* Filter Graph Manager. */ IPin *pOut, /* Output pin on the upstream filter. */ IBaseFilter *pDest) /* Downstream filter. */;
	HRESULT ConnectFilters(IGraphBuilder *pGraph, IBaseFilter *pSrc, IPin *pIn);
	HRESULT ConnectFilters(IGraphBuilder *pGraph, IBaseFilter *pSrc, IBaseFilter *pDest);
	
public:
	std::vector<std::wstring> GetCaptureDevicesName();
	
	bool	GetReadyToPreview(std::wstring deviceName);
	bool	GetReadyToGrabVideo(std::wstring deviceName);
	void	Start();
	void	Stop();
	void	OnClose();

	IMediaEventEx*		GetMediaEvent();

	void	SetStreamType(PhysicalConnectorType streamType);
	std::string	GetStreamType();

	void SetBrightness(long val);
	void SetContrast(long val);
	void SetSaturation(long val);

	long GetBrightness();
	long GetContrast();
	long GetSaturation();

	bool IsEqualToFoundedDevice(IBaseFilter *pf);
		
	void CreateCaptureGraph(std::wstring fileName);
	void DestroyCaptureGraph();

	BYTE*	GetGrabbedBuffer(VIDEOINFOHEADER& headerInfo);
	HRESULT WriteBitmap(PCWSTR, BITMAPINFOHEADER*, size_t, BYTE*, size_t);

	void	PrepareVideoWin();

	misVideoStarter(HWND parent);
	misVideoStarter();
	~misVideoStarter();


};
