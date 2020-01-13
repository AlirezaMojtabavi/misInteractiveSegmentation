#pragma once

#include "ITransform.h"
#include "misLibraryMacroes.h"

// The FakeTransform class is a fake implementation of ITransform used for unit testing of classes that use ITransform. It has
// functionalities that cannot be achieved with plain mock objects. Each fake transform has a name and a version which identify it.
// Use GetConcatenatedTransformsList to convert the transform and all its concatenations (and their concatenations ...) to a list
// of transforms that when chain concatenated reduce to the same transform.
class MISLIBRARYEXPORT FakeTransform : public ITransform
{
public:
	// ITransform interface: 
	virtual void Concatenate( std::shared_ptr<const ITransform> otherTrans ) override;
	virtual void Decatenate() override;
	virtual int GetNumberOfConcatTransforms() const override;
	virtual std::shared_ptr<ITransform> GetInverse() const override;
	virtual std::shared_ptr<ITransform> Clone() const;
	virtual void GetMarixElements( double matrixElements[16] ) const;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// The following are not from the ITransform interface and are used by test procedures.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Determines whether this transform is the original created within the test, one of its created clones, or one of its created
	// inverses.
	enum TransformVersion { ORIGINAL, INVERSE, CLONE };

	FakeTransform(const std::string &transformName);

	// Creates the inverse of this transform by flipping its transform version and if it has concatenations also inversing those
	// transforms and reversing the order of concatenation. (T1 . T2 . T3) ^ -1 = (T3 ^ -1) . (T2 ^ -1) . (T1 ^ -1)
	// If the test procedure requires the inverse of the transform, it should call this method instead of GetInverse since the other
	// one adds the created inverse to the list  returned by GetCreatedInversesList.
	std::shared_ptr<FakeTransform> GetInverseFake() const;

	// Creates a clone of the transform along with its concatenated transforms (and theirs ...)
	// If the test procedure requires a clone of the transform, it should call this method instead of Clone since the other
	// one adds the created clone to the list returned by GetCreatedClonesList.
	std::shared_ptr<FakeTransform> CloneFake() const;

	// Gets whether this transform is the inverse of the one identified by the same name.
	TransformVersion GetTransformVersion() const;

	// This list is maintained to monitor the clones of the original transform that are requested by the system under test as
	// cloning might imply performance overhead.
	std::list< std::shared_ptr<FakeTransform> > GetCreatedClonesList() const;

	// This list is maintained to monitor the inverses of the original transform that are requested by the system under test as
	// creating an inverse transform might imply performance overhead.
	std::list< std::shared_ptr<FakeTransform> > GetCreatedInversesList() const;

	// Converts this transform, its concatenated transforms (and theirs and so on) to a flat list of transforms (that do not 
	// contain any concatenated transforms) which will be equivalent to this transform (after all concatenations) when chain
	// concatenated.
	std::list< std::shared_ptr<const FakeTransform> > GetConcatenatedTransformsList() const;

	// Gets the name of the transform used for identifying each created transform.
	const std::string &GetTransformName() const;
	parcast::Vector<double, 3> GetTVec() const override;
	parcast::Vector<double, 3> GetRVec() const override;


private:
	FakeTransform(const std::string& transformName, const FakeTransform *originalFake, TransformVersion version);

	const FakeTransform *GetOriginalFakeTransform() const;

	virtual std::shared_ptr<ITransform> GetTranslation() const;

	virtual std::shared_ptr<ITransform> GetRotation() const;


 
private:
	mutable std::list< std::shared_ptr<FakeTransform> > m_CreatedClones;	// See GetCreatedClonesList()
	mutable std::list< std::shared_ptr<FakeTransform> > m_CreatedInverses;	// See GetCreatedInversesList()

	std::list< std::shared_ptr<const FakeTransform> > m_ConcatenatedTransforms;	// See GetConcatenatedTransformsList()
	std::string m_TransformName;	// See GetTransformName()
	TransformVersion m_TransformVersion;	// See GetTransformVersion()
	const FakeTransform *m_OriginalFakeTransform;	// Holder of the list of created clones and inverses.
};