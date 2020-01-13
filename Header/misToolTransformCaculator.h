#pragma once

#include "misCalibrationEnums.h"
#include "misMatrixCorectionToPolarisBase.h"
#include "misObject.h"
#include "misPrimaeryNeededHeader.h"
#include "misSeconderyNeededHeader.h"
#include "misSmoothToolData.h"
#include "misToolProperties.h"
#include "misTrackingManagerTypes.h"
#include "misTransformType.h"

class vtkTransform;

class misToolTransformCaculator
{
	typedef ::itk::Vector<double, 3>	VectorType;
	typedef ::itk::Versor<double>		VersorType;
	friend class misTrackingToolObserver;
	misCreateVariableWithGetMacro(KernelSize,int);
	misCreateVariableWithSetGetMacro(MinDistanseofJitter,double);
	misCreateVariableWithSetGetMacro(MinRotationofJitter,double);
	misSetMacro(toolType, TrackerToolType);
public:

	void              GetToolTip(double tipPosition[3]);
	bool			  GetRelatedToolTip(double tipPosition[3]);
	bool              GetToolTipVirtual(double virtualTipPosition[3]);
	misToolStatus     GetToolStatus(void);
	misTransformType  GetTransformType() const;
	void              SetToolStatus(misToolStatus toolStatus);
	misToolStatus     GetTemporayToolStatus(void);
	void              SetTemporayToolStatus(misToolStatus toolStatus);
	// zero mens invisible and 1 declare completely visible
	float GetVisibilityRatio(void);	
	void SetVisibility(bool  visibility );
	void SetToolFreez(bool val);
	bool IsValidNow();
	igstk::Transform  GetFinalToolTransformIGSTK();
	// NOTE :The Get Value must not delete ! use with care
	vtkTransform*     GetFinalToolTransform(void);
	void			  GetFinalVirtualToolTransform(vtkTransform* resTransform);
	vtkMatrix4x4*     GetRawToolTransform(void);
	double          GetLastMovement(void){return this->m_LastMovement;};
	double          GetLastRotation(void){return this->m_LastRotation;};
	bool            GetVisibility() const;
	void UpdateToolTransform(igstk::Transform      rawTransfrom);
	void SetValidReference(bool validReferenceExist);
	void SetPatientRegistartionTransform( vtkMatrix4x4* invPatientRegistartionTransform);
	void SetCorrelatedImageTransform( vtkMatrix4x4* imageToImageRegistartionTransform);

	void          SetToolTransformComputationType( misTransformType toolTransformType);

	// the following transform is defined in order to provide a means for obtaining the required compensatory rotation 
	// in order to make the representation of the tool inline with the tooltipPointerRepresentationOrientation
	void          SetToolReresentationCompensatorTransform(itk::Versor<double> comasentationTransform);
	void          SetToolReresentationCompensatorTransform(vtkMatrix4x4* comasentationTransform);
	void          ResetToolReresentationCompensatorTransform(void);
	vtkSmartPointer<vtkMatrix4x4> GetToolReresentationCompensatorTransform( void ) const;

	void ResetSetting();
	void SetTipOffset(double tipOffset[3]);
	void   SetVirtualTipLength( double virtualTipLength );
	double GetVirtualTipLength(void);
	bool   GetFreezeState(void);

	misToolTransformCaculator(vtkMatrix4x4 * CorrectionMatrix);
	~misToolTransformCaculator(void);
	//returns camera2openGl corrector matrix
	vtkMatrix4x4 * GetOpenGlCorrectorMatrix();
	misSmoothToolData* GetSmoothing() const;
	void SetToolName(const std::string& name);
protected:
	misTransformType                        m_RealTransformTypeState;
	misTransformType                        m_DemandedTransformType;
	misToolRepresentationType               m_RepresentationType;
	misToolTrackingEnum                     m_ToolTrackingState;
	double                  m_LastMovement;
	double                  m_LastRotation;
	TrackerToolType			m_toolType;	
	TrackerType				m_TrackerType;
	float  m_VisibilityRatio;
	int    m_VisibilityPeriod; // compute visibilityRation with this interval
private: 
	igstk::Transform       m_RawTransfrom;
	vtkTransform*          m_InitialTransform;
	vtkMatrix4x4*          m_LastRawMatrix;

	vtkMatrix4x4*         m_InvPatientRegistartionMatrix;
	vtkMatrix4x4*         m_ImageCorrelationRegistartionMatrix;

	vtkMatrix4x4*         m_LastSmoothedDataMatrix;
	vtkMatrix4x4*         m_RelatedMatrix;
	vtkMatrix4x4*         m_CorrectedSmoothedDataMatrix; // TODO : must remove JHB

	igstk::Transform	  m_FinalRegistredRelativeTransformIGSTK;
	vtkMatrix4x4*         m_FinalRegistredRelativeMatrix;
	vtkTransform*         m_FinalRegistredRelativeTransform;
	vtkMatrix4x4*	      m_toolRepresentationCompensationTransform;

	vtkMatrix4x4*         m_TempTransform;
	vtkMatrix4x4*         m_TempTransform2;

	double		    m_TipPosition[3];
	double          m_VirtualTipLength;
	//double		    m_RawVirtualTipPosition[3];
	double          m_PreviousTipPosition[3];
	VersorType      m_PreviosTipQuternion;

	bool         m_Visibility;
	bool         m_FreezTool ;

	misToolStatus		m_ActivationStatus;	
	bool                m_ToolHasBeenFixed;
	double		        m_TipOffset[3];
	misSmoothToolData*    m_Smoothing;
	void Smoothing(misSmoothToolData* val) { m_Smoothing = val; }
 
	void          RemoveSurfaceNotification( const itk::Object *caller, const itk::EventObject & event);
	void          NewTrackingTool();
	void UpdateRegistrationEffectInToolTransform(void);
	void UpdateToolCompensationTransform(void);
	void UpdateFinalTransformIGSTK(void);
	void UpdatelastTransformInformations(vtkMatrix4x4*  finalRegistredRelativeMatrix);
	bool CheckDemandedToolTransformIsValid(void);
	void UpdateToolTransformInternal(void);
	bool                            m_ValidReferenceExist;
	misMatrixCorectionToPolarisBase   m_MatrixCorrector;
	std::string m_ToolName;


 
	

};

