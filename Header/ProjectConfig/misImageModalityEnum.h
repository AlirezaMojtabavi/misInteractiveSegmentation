#pragma  once
enum misImageDataModality
{
	//; the graphical user interface knows the following imaging modality codes 
	//; Computer Tomography          =  1, 
	//; Magnetic Resonance Imaging   =  2,
	//; X-Ray image                  =  3,
	//; Digital X-Ray                =  4
	//; Positron Emmision Tomography =  5,
	//; SPECT                        =  6,
	//; Angioscopy                   =  7,
	//; Digital Angioscopy           =  8,
	//; Ultrasound imaging           =  9,
	//; Nuclear Medicine             = 10;
	//; No Data to read				 = 11;
	CT = 1,
	MRI,
	fMRI,
	XRay,
	DXRay,
	PET,
	SPECT,
	Angio,
	DAngio,
	US,
	NM,
	NoData
};