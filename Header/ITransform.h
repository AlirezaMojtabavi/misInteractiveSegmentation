#pragma once

#include "BusinessEntities/Vector.h"

// The ITransform is the abstract interface to classes that provide general properties and functionalities of geometric and
// space transforms. These include concatenating one transform to another (multiplication) and decatenation thereof, 
// inversing and cloning the transform. Functionality provided in this interfaces seeks to abstract transform operations used
// in correlation manager. Therefore, applying transform to points and vectors ..., which are not used there are excluded from 
// the interface. To make other uses of the transform, its matrix elements can be retrieved and passed either to a vtkMatrix
// or other compatible structures.
// The concatenations are expected to be performed by prepending the concatenated transform before the current transform matrix, 
// that is, if the current matrix is M and a transform with matrix A is concatenated to this matrix, the new matrix should be
// A * M. This is called post-multiplication in VTK terminology.
class ITransform
{
public:
    // Concatenates the specified transform to the chain of concatenated transforms that this transform object wraps.
    virtual void Concatenate(std::shared_ptr<const ITransform> otherTrans) = 0;

    // Decatenates the last concatenated transform from the chain of concatenated transforms wrapped within this object.
    virtual void Decatenate() = 0;

    // Gets the number of transforms daisy chained in concatenation. 
    virtual int GetNumberOfConcatTransforms() const = 0;

    // Gets the inverse of this transform as a new transform. The returned transform is not connected in any way to this transform
    // afterwards, i.e. its future behaviour will be independent of this transform object.
    virtual std::shared_ptr<ITransform> GetInverse() const = 0;

    // Creates a copy of this transform object whose future behaviour will be independent of that of this transform object.
    virtual std::shared_ptr<ITransform> Clone() const = 0;
		
    // Gets the elements of the matrix defining the internally held transform as an array of 16 doubles. Each consecutive four 
    // elements in the array represent one row in the 4x4 matrix. This matrix can be used to initialize a vtkMatrix, 
    // vtkTransform ... This is how ITransform objects can be applied to points, vectors, ...
    virtual void GetMarixElements(double matrixElements[16]) const = 0;

    // Creates and returns a new transform object that contains only the translation part of this transform.
    virtual std::shared_ptr<ITransform> GetTranslation() const = 0;

    // Creates and returns a new transform object that contains only the rotation part of this transform.
    virtual std::shared_ptr<ITransform> GetRotation() const = 0;

    // Creates and returns the translation vector corresponding to this transform object.
    virtual parcast::Vector<double, 3> GetTVec() const = 0;

    // Creates and returns the rotation vector corresponding to this transform object. The rotation vector is such that its 
    // direction determines the rotation axis and its magnitude determines the angle of rotation (in degrees).
    virtual parcast::Vector<double, 3> GetRVec() const = 0;

    virtual ~ITransform(void) { }
};