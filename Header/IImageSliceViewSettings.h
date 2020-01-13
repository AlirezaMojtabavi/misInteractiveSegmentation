#pragma  once

#include "misPlaneAndBoxConfiguration.h"
#include "misQuadGeometry.h"
#include "misEnums.h"
// The IImageSliceViewSettings classes provides the abstract interface to classes that support extraction of image slice view 
// settings (the set of four points defining quad with the slice of image and a suitable view-up vector) given the dimensions of 
// a 3D image, a slicing plane specification, whether oblique view is desired, and the view-up calculation mode.
class IImageSliceViewSettings
{
public:
	virtual ~IImageSliceViewSettings() = default;
	typedef itk::Vector<double, 3> VectorType;	// Used for the view-up and plane normal vector
	typedef itk::Point<double, 3> PointType;	// Used for the view-up and plane normal vector

	// The ViewPlaceholderType enum contains values indicating which of the three possible views (for both oblique and standard 
	// views) is of interest. These values are placeholders that based on value IsOblique() is translated to corresponding 
	// values of the related slice plane extractor.
	enum ViewPlaceholderType
	{
		// In oblique mode translates to "inline axial" and in standard mode translates to "axial" view.
		VIEW_PLACEHOLDER_AXIAL,

		// In oblique mode translates to "probe eye" and in standard mode translates to "coronal" view.
		VIEW_PLACEHOLDER_CORONAL,

		// In oblique mode translates to "inline sagittal" and in standard mode translates to "sagittal" view.
		VIEW_PLACEHOLDER_SAGITTAL
	};

	// Modifies the zoom factor of the generated slice quad. The default slice quad side length is
	// equal to the diagonal of the image box. The final length of the image slice quad is the default length divided by this
	// zoom factor.
	virtual void SetZoomFactor(double zoomFactor) = 0;

	// Gets/sets the definition of the box and partial definition of the intersecting plane (lacking a normal vector/orientation).
	// Along with the plane normal vector, this defines the plane and box combination.
	virtual const misPlaneAndBoxConfiguration &GetPlaneAndBoxConfig() const = 0;
	virtual void SetPlaneAndBoxConfig(const misPlaneAndBoxConfiguration &config) = 0;

	// Gets/sets the plane normal vector which along with the PlaneAndBoxConfig provides a complete definition of the plane and 
	// image box. However, this property is only necessary in cases of IsOblique() = true. In other cases, the plane normal is
	// inferred from the ViewPlaceholder.
	virtual const VectorType &GetPlaneNormalVector() const = 0;
	virtual void SetProbeDirection(const VectorType &config) = 0;

	// Sets/gets the image view placeholder which is interpretted differently depending on the value of IsOblique().
	virtual ViewPlaceholderType GetViewPlaceholder() const = 0;
	virtual void SetViewPlaceholder( ViewPlaceholderType val ) = 0;

	// Sets/gets whether the slice plane is one of the standard anatomical planes (axial, coronal, sagittal) or it is oblique with
	// respect to them. This property affects the interpretation of ViewPlaceholder. Also, when IsOblique() is true, the plane 
	// normal must be set (it can be inferred from the ViewPlaceholder in standard mode).
	virtual void SetIsOblique(bool isOblique) = 0;
	virtual bool IsOblique() const = 0;

	// Gets the mode to use for calculation of the view-up vector. See GetViewUpVector().
	virtual misApplicationType GetSurgeryType() const = 0;

	// Calculates (based on GetSurgeryType()) the view-up vector to be used in displaying the image slice.
	virtual VectorType GetViewUpVector() = 0;

	// Gets the coordinates of the four corner points of the image slice resulting from intersection of 
	// the plane with the set of four edges of the box as a misQuadGeometry object.
	virtual misQuadGeometry GetImageSliceQuad() = 0;
	virtual void SetSurgeryType(misApplicationType appType) = 0;
	virtual  double GetZoomFactor() = 0;

};