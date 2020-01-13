#pragma once

#include "ITransform.h"
#include "misLibraryMacroes.h"

// The misTransform class is the default implementation for ITransform interface. Internally it uses a TGT Matrix4.
// Transform concatenations are automatically stored in an internal stack to make subsequent decatenation possible. 
// Creating a misTransform object requires the matrix elements which might come from another vtkTransform or vtkMatrix. 
// This matrix is used to initialize internally maintained matrix. The only means of applying the transform to points and
// geometric constructs is to get the matrix elements and use them to initialize a vtkTransform object for example.
class MISLIBRARYEXPORT misTransform : public ITransform
{
public:
    // Creates a misTransform object with a vtkTransform object inside and initializes the vtkTransform object using the
    // specified matrix elements.
    misTransform(const double matrixElements[16]);
    ~misTransform(void);

    // This will be 1 when the misTransform object is first created.
    int GetNumberOfConcatTransforms() const override;

    std::shared_ptr<ITransform> GetInverse() const override;
    std::shared_ptr<ITransform> Clone() const override;
    void GetMarixElements(double matrixElements[16]) const override;
    void Decatenate() override;
    void Concatenate(std::shared_ptr<const ITransform> otherTrans) override;
    std::shared_ptr<ITransform> GetTranslation() const override;
    std::shared_ptr<ITransform> GetRotation() const override;
    parcast::Vector<double, 3> GetTVec() const override;
    parcast::Vector<double, 3> GetRVec() const override;

private:
    typedef tgt::Matrix4d MatrixType;

    // Creates a misTransform object and initializes the internal matrix as a copy of the specified matrix.
    // It is made private as the only use for this method is in Clone().
    misTransform(const MatrixType& matrix);

    // A stack of matrices the whose top (back) element represents current transform (with all concatenations ...) each 
    // concatenation pushes a new matrix on top and each decatenation pops the stack reverting the transform to its state before
    // last concatenation.
    std::list<MatrixType> m_MatrixStack;
};

MISLIBRARYEXPORT std::ostream& operator<< (std::ostream& outStr, const ITransform& transform);