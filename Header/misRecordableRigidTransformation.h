#pragma once

#include "IRecordableData.h"
#include "misLibraryMacroes.h"

// This class records rigid transformation (transformation that only contains rotation and translation) to a ostream
// Output format: W(angle), rotationAxisX, rotationAxisY, rotationAxisZ, translationX, translationY, translationZ;\n
class  MISLIBRARYEXPORT misRecordableRigidTransformation : public IRecordableData
{
public:
	misRecordableRigidTransformation(const itk::Versor<double>& rotation, const itk::Vector<double, 3>& translation);

private:
	virtual std::ostream& WriteToStream(std::ostream& os) const;

	// Quaternion representation of rotation
	itk::Versor<double> m_Rotation;

	// x, y, z translation
	itk::Vector<double> m_Translation;
};

