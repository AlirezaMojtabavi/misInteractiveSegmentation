#pragma once

#include "IImageSliceViewSettings.h"
#include "ISquareQuadCreator.h"
#include "mis3dVector.h"

// The misImageSliceViewSettings implementation of the IImageSliceViewSettings interface. Extracts the image slice quad by deriving
// three mutually orthogonal vectors. In the non-oblique mode, these vectors coincide with the three principal axes although each of
// the vectors might have a negative direction in dimension in which it lies. In the oblique mode, the three unit vectors are the
// probe direction, a vector perpendicular to the probe direction lying in the Sagittal plane, and the last vector is, of course,
// perpendicular to the first two. 3 slice quads are then created for each of the three placeholders. Each slice quad is created
// with one of the three unit vectors as their normal vector. For each of the views, the other two of the unit vectors are
// used as vertical and horizontal unit vectors. Quad points are calculated by placing the quad centre on the plane point (moving 
// the point along the direction of the plane normal by the specified offset, if any). The four points that constitute the quad
// are found by adding the quad centre point to either positive or negative of both horizontal and vertical unit vectors scaled 
// equally with respect to image dimensions (proportional to size of the image box diagonal). Then, the four points are ordered
// such that the resultant quad normal has the same direction as the unit vector designated as the plane normal.
// The following figure demonstrates how the four quad points (Q1, Q2, Q3, Q4) are found having the quad centre point (QC), and a 
// vertical (V) and a horizontal (H) vector.
//
//  Q1-----------------------Q2
//  |            ^            |
//  |            |            |
//  |            H            |
//  |            |            |
//  |<--- -V -- QC --- V ---->|
//  |            |            |
//  |           -H            |
//  |            |            |
//  |           \/            |
//  Q3-----------------------Q4
//
class misImageSliceViewSettings : public IImageSliceViewSettings
{
public:

	misImageSliceViewSettings();
	~misImageSliceViewSettings(void);

	virtual void SetZoomFactor(double zoomFactor) override;

	virtual const misPlaneAndBoxConfiguration &GetPlaneAndBoxConfig() const override;
	virtual void SetPlaneAndBoxConfig(const misPlaneAndBoxConfiguration &config) override;

	virtual void SetIsOblique(bool isOblique) override;
	virtual bool IsOblique() const override;

	virtual const VectorType & GetPlaneNormalVector() const override;
	virtual void SetProbeDirection( const VectorType &vec ) override;

	virtual ViewPlaceholderType GetViewPlaceholder() const override;
	virtual void SetViewPlaceholder( ViewPlaceholderType val ) override;

	virtual misApplicationType GetSurgeryType() const override;

	// Calculates, using the suitable method based on the value of IsOblique(), the four points forming a valid quad (order of the
	// points set so the normal vector points to the appropriate direction (which determines camera position).
	virtual misQuadGeometry GetImageSliceQuad() override;

	// Gets the view-up vector to be used in displaying the image slice as a itk vector. It calculates the view-up vector based on 
	// the value GetSurgeryType(). In ENT surgeries, the view-up vector is posterior-to-anterior in axial placeholder 
	// view and inferior-to-superior in the other two. In spine surgeries, the view-up vector is anterior-to-posterior in axial 
	// placeholder view and again inferior-to-superior in the other two.
	virtual VectorType GetViewUpVector() override;

	void SetSurgeryType(misApplicationType appType) override;
	double GetZoomFactor() override;
private:
	// Unit vectors normal to the three perpendicular planes of the image. Used in calculations.
	const mis3DVector<double> SuperiorToInferiorUnitVector, PosteriorToAnteriorUnitVector, DexterToSinisterUnitVector;

	// Performs calculations if necessary to update the internally kept image slice quad and view-up vector. Called by 
	// GetViewUpVector() and GetImageSliceQuad() before returning the internally kept value.
	void PerformCalculations();

	// Computes three mutually orthogonal unit vectors which in the non-oblique mode fall back to the three standard unit 
	// vectors (i, j, k) and in the oblique mode correspond to the probe direction, a vector perpendicular to both probe direction
	// and DexterToSinisterUnitVector, and the third vector is perpendicular to the first two. Which vector is assigned to the
	// probe direction (coronal or axial) depends on current surgery type. The result is stored in the output parameters.
	void ComputeOrthogonalVectors(VectorType& axial, VectorType& coronal, VectorType& sagittal);

	// Tells GetViewUpVector() and GetImageSliceQuad() whether they need to perform a calculation (if the input data is altered).
	bool m_IsCalculationNecessary;

	bool m_IsOblique;	// SetIsOblique()

	ViewPlaceholderType m_ViewPlaceholder;	// SetViewPlaceholder()
	misApplicationType m_AppType;	// See SetSurgeryType()
	misPlaneAndBoxConfiguration m_PlaneAndBoxConfig;	// See SetPlaneAndBoxConfig()
	VectorType m_ProbeDirection;	// See SetProbeDirection()

	VectorType m_ViewUpVector;	// Computed view-up vector, updated by PerformCalculations(), returned by GetViewUpVector().
	VectorType m_ViewSide;	// Computed view-side vector, updated by PerformCalculations().
	misQuadGeometry m_ImageSliceQuad;	// Computed quad, updated by PerformCalculations(), return by GetImageSliceQuad().
	double m_QuadSideHalfLength;	// Half length of the final slice view square, calculated based on image bounds.
	double m_ZoomFactor;	//
};