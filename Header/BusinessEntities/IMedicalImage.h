#pragma once

namespace parcast
{

	// The IMedicalImage class provides the abstract interface to objects representing any type of medical image that can be used in
	// CAST scenarios, including CT, MR, fMRI, DTI, etc.
	class IMedicalImage
	{
	public:

		virtual ~IMedicalImage() { }
	};

}
