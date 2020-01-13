#pragma once

DEFINE_GUID(CLSID_SampleGrabber,0xc1f400a0,0x3f08,0x11d3,0x9f,0x0b,0x00,0x60,0x08,0x03,0x9e,0x37);
DEFINE_GUID(IID_ISampleGrabber,0x6b652fff,0x11fe,0x4fce,0x92,0xad,0x02,0x66,0xb5,0xd7,0xc7,0x8f);
DEFINE_GUID(CLSID_NullRenderer,0xc1f400a4,0x3f08,0x11d3,0x9f,0x0b,0x00,0x60,0x08,0x03,0x9e,0x37);

interface ISampleGrabberCB : public IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE SampleCB(
		double SampleTime,
		IMediaSample *pSample) = 0;

	virtual HRESULT STDMETHODCALLTYPE BufferCB(
		double SampleTime,
		BYTE *pBuffer,
		LONG BufferLen) = 0;

	virtual ~ISampleGrabberCB() {}
};

interface ISampleGrabber : public IUnknown
{
	virtual HRESULT STDMETHODCALLTYPE SetOneShot(
		BOOL OneShot) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetMediaType(
		const AM_MEDIA_TYPE *pType) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetConnectedMediaType(
		AM_MEDIA_TYPE *pType) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetBufferSamples(
		BOOL BufferThem) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentBuffer(
		LONG *pBufferSize,
		LONG *pBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentSample(
		IMediaSample **ppSample) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetCallback(
		ISampleGrabberCB *pCallback,
		LONG WhichMethodToCallback) = 0;

	virtual ~ISampleGrabber() {}
};

//Callback class
class SampleGrabberCallback : public ISampleGrabberCB{
public:

	//------------------------------------------------
	SampleGrabberCallback(){
		InitializeCriticalSection(&critSection);
		freezeCheck = 0;


		bufferSetup         = false;
		newFrame            = false;
		latestBufferLength  = 0;

		hEvent = CreateEvent(NULL, true, false, NULL);
	}


	//------------------------------------------------
	virtual ~SampleGrabberCallback(){
		ptrBuffer = NULL;
		DeleteCriticalSection(&critSection);
		CloseHandle(hEvent);
		if(bufferSetup){
			delete[] pixels;
		}
	}


	//------------------------------------------------
	bool setupBuffer(int numBytesIn){
		if(bufferSetup){
			return false;
		}else{
			numBytes            = numBytesIn;
			pixels              = new unsigned char[numBytes];
			bufferSetup         = true;
			newFrame            = false;
			latestBufferLength  = 0;
		}
		return true;
	}


	//------------------------------------------------
	STDMETHODIMP_(ULONG) AddRef() { return 1; }
	STDMETHODIMP_(ULONG) Release() { return 2; }


	//------------------------------------------------
	STDMETHODIMP QueryInterface(REFIID, void **ppvObject){
		*ppvObject = static_cast<ISampleGrabberCB*>(this);
		return S_OK;
	}


	//This method is meant to have less overhead
	//------------------------------------------------
	STDMETHODIMP SampleCB(double , IMediaSample *pSample){
		if(WaitForSingleObject(hEvent, 0) == WAIT_OBJECT_0) return S_OK;

		HRESULT hr = pSample->GetPointer(&ptrBuffer);

		if(hr == S_OK){
			latestBufferLength = pSample->GetActualDataLength();
			if(latestBufferLength == numBytes){
				EnterCriticalSection(&critSection);
				memcpy(pixels, ptrBuffer, latestBufferLength);
				newFrame    = true;
				freezeCheck = 1;
				LeaveCriticalSection(&critSection);
				SetEvent(hEvent);
			}else{
				printf("ERROR: SampleCB() - buffer sizes do not match\n");
			}
		}

		return S_OK;
	}


	//This method is meant to have more overhead
	STDMETHODIMP BufferCB(double, BYTE *, long){
		return E_NOTIMPL;
	}

	int freezeCheck;

	int latestBufferLength;
	int numBytes;
	bool newFrame;
	bool bufferSetup;
	unsigned char * pixels;
	unsigned char * ptrBuffer;
	CRITICAL_SECTION critSection;
	HANDLE hEvent;
};