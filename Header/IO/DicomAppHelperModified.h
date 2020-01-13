#pragma once
/**
 * \class DICOMAppHelperModified
 * \brief Class to interface an application to a DICOMParser
 *
 * DICOMAppHelperModified assists an application in communicating with a
 * DICOMParser. DICOMAppHelperModified registers a series of callbacks to the
 * DICOMParser which allows it to cache the information from a DICOM
 * file in a format that is appropriate for an application to
 * use. Once a DICOM file is read, an application can query the
 * DICOMAppHelperModified for the resolution, pixel size, and pixel data.
 *
 * If a DICOMParser scans more than one file, the DICOMAppHelperModified will
 * group filesnames by SeriesUID.  This allows an application to pass
 * a series of DICOM files to the DICOMParser (which via the callback
 * mechanism allows the DICOMAppHelperModified to cache information) and then
 * query the DICOMAppHelperModified for the files that are from the same
 * series.  The application can request the filenames for a particular
 * series to be sorted based on image number, slice location, or
 * patient position. This allows the DICOMAppHelperModified to assist an
 * application is collecting all the images from one series into a
 * volume.
 */
#include <AppHelperSharedStruct.h>
class   DICOMAppHelperModified
{
public:
  /** Standard constructor */
  DICOMAppHelperModified();

  /** Standard destructor */
  virtual ~DICOMAppHelperModified();

  /** Callbacks that are registered with the DICOMParser.  The
   * DICOMParser will call one of these callbacks whenever it
   * encounters a (group, element) that has an associated callback */

  virtual void ImageWindowCenterCallback(DICOMParser *parser,
	  doublebyte group,
	  doublebyte element,
	  DICOMParser::VRTypes type,
	  unsigned char* val,
	  quadbyte len) ;

  virtual void ImageWindowWidthCallback(DICOMParser *parser,
	  doublebyte group,
	  doublebyte element,
	  DICOMParser::VRTypes type,
	  unsigned char* val,
	  quadbyte len) ;

  virtual void RescaleSlopeCallback(DICOMParser *parser,
                                     doublebyte group,
                                    doublebyte element,
                                    DICOMParser::VRTypes type,
                                    unsigned char* val,
                                    quadbyte len);

  virtual void ArrayCallback(DICOMParser *parser,
                             doublebyte group,
                             doublebyte element,
                             DICOMParser::VRTypes type,
                             unsigned char* val,
                             quadbyte len);

  virtual void SliceNumberCallback(DICOMParser *parser,
                                   doublebyte group,
                                   doublebyte element,
                                   DICOMParser::VRTypes type,
                                   unsigned char* val,
                                   quadbyte len) ;

  virtual void SliceLocationCallback(DICOMParser *parser,
                                     doublebyte group,
                                     doublebyte element,
                                     DICOMParser::VRTypes type,
                                     unsigned char* val,
                                     quadbyte len) ;

  virtual void ImagePositionPatientCallback(DICOMParser *parser,
                                            doublebyte group,
                                            doublebyte element,
                                            DICOMParser::VRTypes type,
                                            unsigned char* val,
                                            quadbyte len) ;

  virtual void ImageOrientationPatientCallback(DICOMParser *parser,
                                               doublebyte group,
                                               doublebyte element,
                                               DICOMParser::VRTypes type,
                                               unsigned char* val,
                                               quadbyte len) ;

  virtual void SeriesUIDCallback(DICOMParser *parser,
                                 doublebyte group,
                                 doublebyte element,
                                 DICOMParser::VRTypes type,
                                 unsigned char* val,
                                 quadbyte len) ;

  virtual void TransferSyntaxCallback(DICOMParser *parser,
                                      doublebyte group,
                                      doublebyte element,
                                      DICOMParser::VRTypes type,
                                      unsigned char* val,
                                      quadbyte len) ;

  virtual void BitsAllocatedCallback(DICOMParser *parser,
                                     doublebyte group,
                                     doublebyte element,
                                     DICOMParser::VRTypes type,
                                     unsigned char* val,
                                     quadbyte len) ;

  virtual void ToggleSwapBytesCallback(DICOMParser *parser,
                                       doublebyte,
                                       doublebyte,
                                       DICOMParser::VRTypes,
                                       unsigned char*,
                                       quadbyte);

  virtual void PixelSpacingCallback(DICOMParser *parser,
                                    doublebyte group,
                                    doublebyte element,
                                    DICOMParser::VRTypes type,
                                    unsigned char* val,
                                    quadbyte len) ;

  virtual void HeightCallback(DICOMParser *parser,
                              doublebyte group,
                              doublebyte element,
                              DICOMParser::VRTypes type,
                              unsigned char* val,
                              quadbyte len);

  virtual void WidthCallback( DICOMParser *parser,
                              doublebyte group,
                              doublebyte element,
                              DICOMParser::VRTypes type,
                              unsigned char* val,
                              quadbyte len);

  virtual void PixelRepresentationCallback(DICOMParser *parser,
                                           doublebyte group,
                                           doublebyte element,
                                           DICOMParser::VRTypes type,
                                           unsigned char* val,
                                           quadbyte len);

  virtual void PhotometricInterpretationCallback(DICOMParser *parser,
                                                 doublebyte,
                                                 doublebyte,
                                                 DICOMParser::VRTypes,
                                                 unsigned char* val,
                                                 quadbyte len);

  virtual void PixelDataCallback(DICOMParser *parser,
                                 doublebyte,
                                 doublebyte,
                                 DICOMParser::VRTypes,
                                 unsigned char* val,
                                 quadbyte len);

  virtual void RescaleOffsetCallback( DICOMParser *parser,
                                      doublebyte,
                                      doublebyte,
                                      DICOMParser::VRTypes,
                                      unsigned char* val,
                                      quadbyte);

  /** Register all the standard callbacks with the DICOM Parser.  This
   * associates a callback with each (group, element) tag pair in the
   * header of the file whose data needs to be cached. */
  virtual void RegisterCallbacks(DICOMParser* parser);
  void RegisterReaderCallbacks(DICOMParser* parser);

  /** Register a callback for retrieving the pixel data from a DICOM
   *  file */
  virtual void RegisterPixelDataCallback(DICOMParser* parser);

  /** Output information associated with a DICOM series */
  void OutputSeries();

  /** The next set of methods are for accessing information which is
   * cached when a DICOM file is processed.  This allows access to
   * information from the header as well as the pixel data. */

  /** Get the pixel spacing of the last image processed by the
   *  DICOMParser */
  float* GetPixelSpacing()
  {
	  return PixelSpacing;
    }

  /** Get the image width of the last image processed by the
   *  DICOMParser */
  int GetWidth()
    {
    return Width;
    }

  /** Get the image height of the last image processed by the
   *  DICOMParser */
  int GetHeight()
    {
    return Height;
    }

  /** Get the dimensions (width, height) of the last image processed
   *  by the DICOMParser */
  int* GetDimensions()
    {
		if(Dimensions)
		   return Dimensions;
		else
		  return NULL;
    }

  /** Get the (DICOM) x,y,z coordinates of the first pixel in the
   * image (upper left hand corner) of the last image processed by the
   * DICOMParser */
  float *GetImagePositionPatient()
    {
	  if(ImagePositionPatient)
		  return ImagePositionPatient;
	  else
		return NULL;
    }

  /** Get the (DICOM) directions cosines. It consist of the components
   * of the first two vectors. The third vector needs to be computed
   * to form an orthonormal basis. */
 float *GetImageOrientationPatient()
    {
      if(ImageOrientationPatient)
		return ImageOrientationPatient;
	  else
	    return NULL;
    }

  /** Get the number of bits allocated per pixel of the last image
   *  processed by the DICOMParser */
  int GetBitsAllocated()
    {
    return BitsAllocated;
    }

  /** Get the pixel representation of the last image processed by the
   * DICOMParser. A zero is a unsigned quantity.  A one indicates a
   * signed quantity. */
  int GetPixelRepresentation()
    {
    return PixelRepresentation;
    }

  /** Get the number of components of the last image processed by the
   *  DICOMParser. */
  int GetNumberOfComponents()
    {
     if (!PhotometricInterpretation)
        {
           return 1;
        }

    //
    // DICOM standard says that spaces (0x20) are to
    // be ignored for CS types.  We don't handle this
    // well yet.
    //
    dicom_stl::string str1(*PhotometricInterpretation);
    dicom_stl::string rgb("RGB ");

    if (str1 == rgb)
      {
         return 3;
      }
    else
      {
         return 1;
      }
    }

  /** Get the transfer syntax UID for the last image processed by the
   *  DICOMParser. */
  dicom_stl::string GetTransferSyntaxUID()
    {
    return *(TransferSyntaxUID);
    }

  /** Get a textual description of the transfer syntax of the last
   *  image processed by the DICOMParser. */
  const char* TransferSyntaxUIDDescription(const char* uid);

  /** Get the image data from the last image processed by the
   * DICOMParser.  The data is only valid if the PixelDataCallback was
   * registered.
   * \sa RegisterPixelDataCallback()
  */
  void GetImageData(void* & data, DICOMParser::VRTypes& dataType, unsigned long& len);

  /** Determine whether the image data was rescaled (by the
   *  RescaleSlope tag) to be floating point. */
  bool RescaledImageDataIsFloat();

  /** Determine whether the image data was rescaled (by the
   * RescaleSlope tag) to be a signed data type. */
  bool RescaledImageDataIsSigned();

  /** Get the slice number of the last image processed by the
      DICOMParser. */
  int GetSliceNumber()
    {
    return SliceNumber;
    }
  float GetSliceLocation()
  {
	  return SliceLocation;
  }

  /** Clear the internal databases. This will reset the internal
   * databases that are grouping filenames based on SeriesUID's and
   * ordering filenames based on image locations. */
  void Clear();

  /** Get the series UIDs for the files processed since the last
   * clearing of the cache. */
  void GetSeriesUIDs(dicom_stl::vector<dicom_stl::string> &v);

  /** Get the filenames for a series ordered by slice number. */
  void GetSliceNumberFilenamePairs(const dicom_stl::string &seriesUID,
                              dicom_stl::vector<dicom_stl::pair<int, dicom_stl::string> > &v, bool ascending = true);

  /** Get the filenames for a series order by slice number.  Use the
      first series by default. */
  void GetSliceNumberFilenamePairs(dicom_stl::vector<dicom_stl::pair<int, dicom_stl::string> > &v, bool ascending = true);

  /* Get the filenames for a series ordered by slice location. */
  void GetSliceLocationFilenamePairs(const dicom_stl::string &seriesUID,
                              dicom_stl::vector<dicom_stl::pair<float, dicom_stl::string> > &v, bool ascending = true);

  /* Get the filenames for a series ordered by slice location. Use the
   * first series by default. */
  void GetSliceLocationFilenamePairs(dicom_stl::vector<dicom_stl::pair<float, dicom_stl::string> > &v, bool ascending = true);

  /* Get the filenames for a series ordered by image position
     patient. This is the most reliable way to order the images in a
     series. */
  void GetImagePositionPatientFilenamePairs(const dicom_stl::string &seriesUID,
                            dicom_stl::vector<dicom_stl::pair<float, dicom_stl::string> > &v, bool ascending = true);

  /* Get the filenames for a series ordered by image position
     patient. This is the most reliable way to order the images in a
     series. Use the first series by default. */
  void GetImagePositionPatientFilenamePairs(dicom_stl::vector<dicom_stl::pair<float, dicom_stl::string> > &v, bool ascending = true);

  float GetRescaleSlope()
    {
    return RescaleSlope;
    }

  float GetRescaleOffset()
    {
 	return RescaleOffset;
    }

  dicom_stl::string GetPatientName()
    {
if(PatientName)
		return *(PatientName);
	else
	return NULL;
    }

  dicom_stl::string GetStudyUID()
    {
    if(StudyUID)
		return *(StudyUID);
	else
	return NULL;
    }
  dicom_stl::string GetSerieUID()
    {
    if(SerieUID)
		return *(SerieUID);
	else
    	return NULL;
    }

  dicom_stl::string GetStudyID()
    {
    if(StudyID)
		return *(StudyID);
	else
	return NULL;
    }
  //-------------------------------------------------------
  dicom_stl::string GetPhaseEncoding()
  {
	if(PhaseEncoding)
	  return *(PhaseEncoding);
	else
	return NULL;
  }
  int GetFlipAngle()
  {
	if(FlipAngle)
	  return *(FlipAngle);
	else
	return NULL;
  }
  dicom_stl::string GetVariableFlipAngle()
  {
	  if(VariableFlipAngle)
	return *(VariableFlipAngle);
	else
	return NULL;
  }
  unsigned long GetPixelBandWidth()
  {
	  if(PixelBandWidth)
	return *(PixelBandWidth);
	else
	return NULL;
  }
  int GetEchoNumber()
  {
	if(EchoNumber)
	  return *(EchoNumber);
	else
	return NULL;
  }
  double GetImageFrequency()
  {
	if(ImageFrequency)
	  return *(ImageFrequency);
	else
	return NULL;
  }
  unsigned long GetPercentPhaseFieldofView()
  {
	if(PercentPhaseFieldofView)
	  return *(PercentPhaseFieldofView);
	else
	return NULL;
  }
  int GetRepetitionTime()
  {
	if(RepetitionTime)
	  return *(RepetitionTime);
	else
	return NULL;
  }
  double GetSpatialResolution()
  {
	if(SpatialResolution)
	  return *(SpatialResolution);
	else
	return NULL;
  }
  unsigned long GetDistanceSourcetoDetector()
  {
	if(DistanceSourcetoDetector)
	  return *(DistanceSourcetoDetector);
	else
	return NULL;
  }
  unsigned long GetDistanceSourcetoPatient()
  {
	if(DistanceSourcetoPatient)
	  return *(DistanceSourcetoPatient);
	else
	return NULL;
  }
  unsigned long GetExposureTime()
  {
if(ExposureTime)
	  return *(ExposureTime);
	else
	return -1;
  }
  int GetX_RayTubeCurrent()
  {
	if(X_RayTubeCurrent)
	  return *(X_RayTubeCurrent);
	else
	return NULL;
  }
  unsigned long GetExposure()
  {
	if(Exposure)
	  return *(Exposure);
	else
	return -1;
  }
  double GetKV()
  {
	if(KV)
	  return *(KV);
	else
	return NULL;
  }

  dicom_stl::string GetPatientID()
  {
	if(PatientID)
	  return *(PatientID);
	else
	return NULL;
  }
  dicom_stl::string GetGender()
  {
	  return Gender;
  }
  dicom_stl::string GetPatientBirthDate()
  {
	if(PatientBirthDate)
	  return *(PatientBirthDate);
	else
	return NULL;
  }
  int GetPatientAge()
  {
	if(PatientAge)
	  return *(PatientAge);
	else
	return NULL;
  }
  int GetPatientWeight()
  {
	if(PatientWeight)
	  return *(PatientWeight);
	else
	return -1;
  }
  dicom_stl::string GetStudyDescription()
  {
	if(StudyDescription)
	  return *(StudyDescription);
	else
	return NULL;
  }
  dicom_stl::string GetStudyDate()
  {
	if(StudyDate)
	  return *(StudyDate);
	else
	return NULL;
  }
  dicom_stl::string GetStudyTime()
  {
	if(StudyTime)
	  return *(StudyTime);
	else
	return NULL;
  }
  dicom_stl::string GetSeriesDescription()
  {
	if(SeriesDescription)
	  return *(SeriesDescription);
	else
	return NULL;
  }
  dicom_stl::string GetModality()
  {
	if(Modality)
	  return *(Modality);
	else
	return NULL;
  }
  dicom_stl::string GetAcquisitionDate()
  {
	if(AcquisitionDate)
	  return *(AcquisitionDate);
	else
	return NULL;
  }
  dicom_stl::string GetAcquisitionTime()
  {
	if(AcquisitionTime)
	  return *(AcquisitionTime);
	else
	return NULL;
  }
  dicom_stl::string GetProtocolName()
  {
	if(ProtocolName)
	  return *(ProtocolName);
	else
	return NULL;
  }
  dicom_stl::string GetManufacturer()
  {
	if(Manufacturer)
	  return *(Manufacturer);
	else
	return NULL;
  }
  dicom_stl::string GetManufacturerModelName()
  {
	if(ManufacturerModelName)
	  return *(ManufacturerModelName);
	else
	return NULL;
  }
  dicom_stl::string GetSoftwareVersion()
  {
	if(SoftwareVersion)
	  return *(SoftwareVersion);
	else
	return NULL;
  }
  dicom_stl::string GetInstitutionName()
  {
	if(InstitutionName)
	  return *(InstitutionName);
	else
	return NULL;
  }
  int GetSamplesperPixel()
  {
	if(SamplesperPixel)
	  return *(SamplesperPixel);
	else
	return NULL;
  }
  int GetSpacingBetweenSlices()
  {
	if(SpacingBetweenSlices)
	  return static_cast<int>(*(SpacingBetweenSlices));
	else
	return NULL;
  }
  int GetBitsStored()
  {
	if(BitsStored)
	  return *(BitsStored);
	else
	return NULL;
  }
  int GetHighBit()
  {
	if(HighBit)
	  return *(HighBit);
	else
	return NULL;
  }
  dicom_stl::string GetPatientPosition()
  {
	if(PatientPosition)
	  return *(PatientPosition);
	else
	return NULL;
  }

  float GetWindowCenter()
  {
	  if(m_WindowCenter)
		  return *(m_WindowCenter);
	  else
		  return NULL;
  }

  float GetWindowWidth()
  {
	  if(m_WindowWidth)
		  return *(m_WindowWidth);
	  else
		  return NULL;
  }

//-------------------------------------------------------
  void PatientNameCallback(DICOMParser *,
                           doublebyte,
                           doublebyte,
                           DICOMParser::VRTypes,
                           unsigned char* val,
                           quadbyte);

  void StudyUIDCallback(DICOMParser *,
                           doublebyte,
                           doublebyte,
                           DICOMParser::VRTypes,
                           unsigned char* val,
                           quadbyte);

  void StudyIDCallback(DICOMParser *,
                           doublebyte,
                           doublebyte,
                           DICOMParser::VRTypes,
                           unsigned char* val,
                           quadbyte);

  void GantryAngleCallback(DICOMParser *,
                           doublebyte,
                           doublebyte,
                           DICOMParser::VRTypes,
                           unsigned char* val,
                           quadbyte);
  //------------------------------------------------------------------
  void PhaseEncodingCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void FlipAngleCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void VariableFlipAngleCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void PixelBandWidthCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void EchoNumberCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void ImageFrequencyCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void PercentPhaseFieldofViewCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void RepetitionTimeCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void SpatialResolutionCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void DistanceSourcetoDetectorCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void DistanceSourcetoPatientCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void ExposureTimeCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void X_RayTubeCurrentCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void ExposureCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void KVCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

  void PatientIDCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
  void GenderCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void PatientBirthdateCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void PatientAgeCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void PatientWeightCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void StudyDescriptionCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void StudyDateCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void StudyTimeCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void SeriesDescriptionCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void ModalityCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void AcquisitionDateCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void AcquisitionTimeCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void ProtocolNameCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void ManufacturerCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void ManufacturerModelNameCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);
void SoftwareVersionCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

void InstitutionNameCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

void SamplesperPixelCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

void SpacingBetweenSlicesCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

void BitsStoredCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

void HighBitCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

void PatientPositionCallback(DICOMParser *parser,
                                         doublebyte,
                                         doublebyte,
                                         DICOMParser::VRTypes,
                                         unsigned char* val,
                                         quadbyte);

 //-------------------------------------------------------------------
  float GetGantryAngle()
    {
   		return GantryAngle;
	}

 protected:
  int   BitsAllocated;
  bool  ByteSwapData;
  float PixelSpacing[3];

  float ImageWindowCenter;
  float ImageWindowWidth;

  int   Width;
  int   Height;
  int   SliceNumber;
  int   Dimensions[2];
  float ImagePositionPatient[3];
  float ImageOrientationPatient[6];

  // map from series UID to vector of files in the series
  // dicom_stl::map<dicom_stl::string, dicom_stl::vector<dicom_stl::string>, ltstdstr> SeriesUIDMap;

  // map from filename to intraseries sortable tags
  // dicom_stl::map<dicom_stl::string, DICOMOrderingElements, ltstdstr> SliceOrderingMap;

  typedef dicom_stl::map<dicom_stl::pair<doublebyte, doublebyte>, DICOMTagInfo> TagMapType;
  // TagMapType TagMap;

  dicom_stream::ofstream HeaderFile;

  // 0 unsigned
  // 1 2s complement (signed)
  int PixelRepresentation;
  dicom_stl::string* PhotometricInterpretation;
  dicom_stl::string* TransferSyntaxUID;
  float RescaleOffset;
  float RescaleSlope;
  void* ImageData;
  DICOMParser::VRTypes ImageDataType;
  unsigned long ImageDataLengthInBytes;

  dicom_stl::string* PatientName;
  dicom_stl::string* StudyUID;
  dicom_stl::string* StudyID;

  float GantryAngle;
  //-------------------------------------------------------------------
  dicom_stl::string* SerieUID;
  dicom_stl::string* PhaseEncoding;
  int* FlipAngle;
  dicom_stl::string* VariableFlipAngle;
  unsigned long* PixelBandWidth;
  int* EchoNumber;
  double* ImageFrequency;
  unsigned long* PercentPhaseFieldofView;
  int* RepetitionTime;
  double* SpatialResolution;
  unsigned long* DistanceSourcetoDetector;
  unsigned long* DistanceSourcetoPatient;
  unsigned long* ExposureTime;
  int* X_RayTubeCurrent;
  unsigned long* Exposure;
  double *KV;
  dicom_stl::string* PatientID;
  dicom_stl::string Gender;
  dicom_stl::string* PatientBirthDate;
  char* PatientAge;
  char* PatientWeight;
  dicom_stl::string* StudyDescription;
  dicom_stl::string* StudyDate;
  dicom_stl::string* StudyTime;
  dicom_stl::string* SeriesDescription;
  dicom_stl::string* Modality;
  dicom_stl::string* AcquisitionDate;
  dicom_stl::string* AcquisitionTime;
  dicom_stl::string* ProtocolName;
  dicom_stl::string* Manufacturer;
  dicom_stl::string* ManufacturerModelName;
  dicom_stl::string* SoftwareVersion;
  dicom_stl::string* InstitutionName;
  dicom_stl::string* PatientPosition;
  int* SamplesperPixel;
  float* SpacingBetweenSlices;
  int* BitsStored;
  int* HighBit;
  float SliceLocation;

  float* m_WindowCenter;
  float* m_WindowWidth;
  //-------------------------------------------------------------------
  DICOMMemberCallback<DICOMAppHelperModified>* SeriesUIDCB;
  DICOMMemberCallback<DICOMAppHelperModified>* SliceNumberCB;
  DICOMMemberCallback<DICOMAppHelperModified>* SliceLocationCB;
  DICOMMemberCallback<DICOMAppHelperModified>* ImagePositionPatientCB;
  DICOMMemberCallback<DICOMAppHelperModified>* ImageOrientationPatientCB;
  DICOMMemberCallback<DICOMAppHelperModified>* TransferSyntaxCB;
  DICOMMemberCallback<DICOMAppHelperModified>* ToggleSwapBytesCB;
  DICOMMemberCallback<DICOMAppHelperModified>* BitsAllocatedCB;
  DICOMMemberCallback<DICOMAppHelperModified>* PixelSpacingCB;
  DICOMMemberCallback<DICOMAppHelperModified>* HeightCB;
  DICOMMemberCallback<DICOMAppHelperModified>* WidthCB;
  DICOMMemberCallback<DICOMAppHelperModified>* PixelRepresentationCB;
  DICOMMemberCallback<DICOMAppHelperModified>* PhotometricInterpretationCB;
  DICOMMemberCallback<DICOMAppHelperModified>* RescaleOffsetCB;
  DICOMMemberCallback<DICOMAppHelperModified>* RescaleSlopeCB;
  DICOMMemberCallback<DICOMAppHelperModified>* PixelDataCB;
  DICOMMemberCallback<DICOMAppHelperModified>* PatientNameCB;
  DICOMMemberCallback<DICOMAppHelperModified>* StudyUIDCB;
  DICOMMemberCallback<DICOMAppHelperModified>* StudyIDCB;

  DICOMMemberCallback<DICOMAppHelperModified>* GantryAngleCB;
//----------------------------------------------------------------
  DICOMMemberCallback<DICOMAppHelperModified>* PhaseEncodingCB;
  DICOMMemberCallback<DICOMAppHelperModified>* FlipAngleCB;
  DICOMMemberCallback<DICOMAppHelperModified>* VariableFlipAngleCB;
  DICOMMemberCallback<DICOMAppHelperModified>* PixelBandWidthCB;
  DICOMMemberCallback<DICOMAppHelperModified>* EchoNumberCB;
  DICOMMemberCallback<DICOMAppHelperModified>* ImageFrequencyCB;
  DICOMMemberCallback<DICOMAppHelperModified>* PercentPhaseFieldofViewCB;
  DICOMMemberCallback<DICOMAppHelperModified>* RepetitionTimeCB;
  DICOMMemberCallback<DICOMAppHelperModified>* SpatialResolutionCB;
  DICOMMemberCallback<DICOMAppHelperModified>* DistanceSourcetoDetectorCB;
  DICOMMemberCallback<DICOMAppHelperModified>* DistanceSourcetoPatientCB;
  DICOMMemberCallback<DICOMAppHelperModified>* ExposureTimeCB;
  DICOMMemberCallback<DICOMAppHelperModified>* X_RayTubeCurrentCB;
  DICOMMemberCallback<DICOMAppHelperModified>* ExposureCB;
  DICOMMemberCallback<DICOMAppHelperModified>* KVCB;

  DICOMMemberCallback<DICOMAppHelperModified>* PatientPositionCB;
 DICOMMemberCallback<DICOMAppHelperModified>* PatientIDCB;
 DICOMMemberCallback<DICOMAppHelperModified>* GenderCB;
 DICOMMemberCallback<DICOMAppHelperModified>* PatientBirthdateCB;
 DICOMMemberCallback<DICOMAppHelperModified>* PatientAgeCB;
 DICOMMemberCallback<DICOMAppHelperModified>* PatientWeightCB;
 DICOMMemberCallback<DICOMAppHelperModified>* StudyDescriptionCB;
 DICOMMemberCallback<DICOMAppHelperModified>* StudyDateCB;
 DICOMMemberCallback<DICOMAppHelperModified>* StudyTimeCB;
 DICOMMemberCallback<DICOMAppHelperModified>* SeriesDescriptionCB;
 DICOMMemberCallback<DICOMAppHelperModified>* ModalityCB;
 DICOMMemberCallback<DICOMAppHelperModified>* AcquisitionDateCB;
 DICOMMemberCallback<DICOMAppHelperModified>* AcquisitionTimeCB;
 DICOMMemberCallback<DICOMAppHelperModified>* ProtocolNameCB;
 DICOMMemberCallback<DICOMAppHelperModified>* ManufacturerCB;
 DICOMMemberCallback<DICOMAppHelperModified>* ManufacturerModelNameCB;
 DICOMMemberCallback<DICOMAppHelperModified>* SoftwareVersionCB;
 DICOMMemberCallback<DICOMAppHelperModified>* InstitutionNameCB;
 DICOMMemberCallback<DICOMAppHelperModified>* SamplesperPixelCB;
 DICOMMemberCallback<DICOMAppHelperModified>* SpacingBetweenSlicesCB;
 DICOMMemberCallback<DICOMAppHelperModified>* BitsStoredCB;
 DICOMMemberCallback<DICOMAppHelperModified>* HighBitCB;

  DICOMMemberCallback<DICOMAppHelperModified>* WindowCenterCB;
  DICOMMemberCallback<DICOMAppHelperModified>* WindowWidthCB;

//----------------------------------------------------------------

  //
  // Implementation contains stl templated classes that
  // can't be exported from a DLL in Windows. We hide
  // them in the implementation to get rid of annoying
  // compile warnings.
  //
  DICOMAppHelperImplementation* Implementation;


 private:
  DICOMAppHelperModified(const DICOMAppHelperModified&);
  void operator=(const DICOMAppHelperModified&);


};

#ifdef _MSC_VER
#pragma warning ( pop )
#endif

