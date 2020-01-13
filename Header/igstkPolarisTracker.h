/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    $RCSfile: igstkPolarisTracker.h,v $
  Language:  C++
  Date:      $Date: 2008-11-17 20:12:25 $
  Version:   $Revision: 1.13 $

  Copyright (c) ISC  Insight Software Consortium.  All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igstkPolarisTracker_h
#define __igstkPolarisTracker_h

#include "igstkPolarisTrackerTool.h"
#include "igstkNDITracker.h"
#include "misStrctConnectOption.h"

namespace igstk
{
/** \class PolarisTracker
  * \brief Provides support for the Polaris optical tracker.
  *
  * This class provides an interface to the Polaris line of
  * optical tracking systems, including the Vicra and the
  * Spectra.  These devices are manufactured by
  * Northern Digital Inc. of Waterloo, Ontario, Canada.
  *
  * Tracking of the silvered markers individually is not possible,
  * the markers must be configured as a tool before they can
  * be tracked.
  *
  * \ingroup Tracker
  * \ingroup NDITracker
  *
  */

class PolarisTracker : public NDITracker
{
public:
  /** Macro with standard traits declarations. */
  igstkStandardClassTraitsMacro( PolarisTracker, NDITracker )

		//----------------------------------------Added By MIS (A.M)
		/** IR Illumination rate */
		enum IRATEFrequency {	ILLUMINATIONRATE_20HZ     = 0,
			ILLUMINATIONRATE_30HZ     = 1,
			ILLUMINATIONRATE_60HZ     = 2	};
		enum Volume
		{
			VolumePyramid	= 1,
			VolumeExtended  = 2
		};
		//Set the Illumination Frequency to use.			//Added by MIS Team (A.M)
		//igstkSetMacro( IRFrequency, IRATEFrequency );
		//Get the Illumination Freqency.
		igstkGetMacro( IRFrequency, IRATEFrequency );
		ResultType PolarisTracker::RequestSetIRFrequency( int IRfrequencyInHz );
		ResultType PolarisTracker::RequestSetVolume( int Volume );
		virtual bool Connect(misStrctComConnectionOptions connecting);
		//-----------------------------------------
protected:

		IRATEFrequency m_IRFrequency;				//A.M
		Volume m_Volume;							//A.M
  PolarisTracker(void);

  virtual ~PolarisTracker(void);

  /** Verify tracker tool information */
  virtual ResultType VerifyTrackerToolInformation( const TrackerToolType * );

  /** The "ValidateSpecifiedFrequency" method checks if the specified  
   *  frequency is valid for the tracking device that is being used. */
  virtual ResultType ValidateSpecifiedFrequency( double frequencyInHz );

  /** Print object information */
  virtual void PrintSelf( std::ostream& os, ::itk::Indent indent ) const; 

private:

  PolarisTracker(const Self&);   //purposely not implemented
  void operator=(const Self&);   //purposely not implemented

};

}

#endif //__igstk_PolarisTracker_h_
