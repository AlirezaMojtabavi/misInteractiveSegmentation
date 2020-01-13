#pragma once
#include "windows.h"
#include "cuda_gl_interop.h"
#include "cuda_runtime_api.h"
#include <driver_functions.h>
#include "shrqatest.h"
#include "string_helper.h"
#include "sdkHelper.h"
 
#include "driver_types.h"
class misCudaInitlizer
{
private:
	int gpuGLDeviceInit();

	int findCudaGLDevice();
 	void __checkCudaErrors( cudaError err, const char *file, const int line );
	int gpuDeviceInit(int devID);
	int findCudaDevice();
	int gpuGetMaxGflopsDeviceId();
public:
	

	misCudaInitlizer(void);
	~misCudaInitlizer(void);
	int chooseCudaDevice(bool bUseOpenGL);
 
};

