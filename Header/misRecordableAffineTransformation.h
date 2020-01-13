#pragma once

#include "IRecordableData.h"
#include "misLibraryMacroes.h"

// This class records affine transformations (transformations containing rotation, translation and scale) to a ostream
// Output format: 
//        r11, r12, r13, Tx
//        r21, r22, r23, Ty
//        r31, r32, r33, Tz
//        0,   0,   0,   1
// Where r## represents components of rotation and scale and Ti represent cartesian components of translation.
class MISLIBRARYEXPORT misRecordableAffineTransformation : public IRecordableData
{
public:
	misRecordableAffineTransformation( vtkMatrix4x4* matrix);

private:
	virtual std::ostream& WriteToStream(std::ostream& os) const;
	vtkSmartPointer<vtkMatrix4x4> m_Transformation;
};

