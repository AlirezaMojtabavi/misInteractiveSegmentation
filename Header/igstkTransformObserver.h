/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    $RCSfile: igstkTransformObserver.h,v $
  Language:  C++
  Date:      $Date: 2008-02-11 01:41:51 $
  Version:   $Revision: 1.1 $

  Copyright (c) ISC  Insight Software Consortium.  All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __igstkTransformObserver_h
#define __igstkTransformObserver_h

#if defined(_MSC_VER)
// Warning about: identifier was truncated to '255' characters
// in the debug information (MVC6.0 Debug)
#pragma warning( disable : 4786 )
#endif

#include "igstkTransform.h"
#include "igstkCoordinateSystemTransformToResult.h"
#include "igstkCoordinateSystemTransformToErrorResult.h"

namespace igstk
{

class TransformObserver : public ::itk::Command 
{
public:
  igstkStandardClassBasicTraitsMacro( TransformObserver, ::itk::Command );
  igstkNewMacro( Self );  

protected:
  TransformObserver() 
    {
    m_GotTransform = false;
    m_GotTransformNotAvailableMessage = false;
    }
  ~TransformObserver() {}
public:
    
  typedef CoordinateSystemTransformToEvent     PositiveEventType;
  typedef TransformNotAvailableEvent           NegativeEventType;
        
  /** Payload contained in an event that returns a valid transform. This
   * payload includes the following items: Transform, Source coordinate system,
   * Destination coordinate system. */
  typedef CoordinateSystemTransformToResult PayloadType;

  void ObserveTransformEventsFrom( Object * objectToObserve )
    {
    if( objectToObserve )
      {
      objectToObserve->AddObserver( PositiveEventType(), this );
      objectToObserve->AddObserver( NegativeEventType(), this );
      }
    }

  void Execute(itk::Object *caller, const itk::EventObject & event)
    {
    const itk::Object * constCaller = caller;
    this->Execute( constCaller, event );
    }

  void Execute(const itk::Object *caller, const itk::EventObject & event)
    {

    m_GotTransform = false;
    m_GotTransformNotAvailableMessage = false;

    if( PositiveEventType().CheckEvent( &event ) )
      {
      const PositiveEventType * transformEvent = 
                 dynamic_cast< const PositiveEventType *>( &event );
      if( transformEvent )
        {
        m_TransformBetweenCoordinateSystems = transformEvent->Get();
        this->m_Transform = m_TransformBetweenCoordinateSystems.GetTransform();
        m_GotTransform = true;
        m_GotTransformNotAvailableMessage = false;
        }
      }

    if( NegativeEventType().CheckEvent( &event ) )
      {
      const NegativeEventType * negativeEvent = 
                 dynamic_cast< const NegativeEventType *>( &event );
      if( negativeEvent )
        {
        m_GotTransform = false;
        m_GotTransformNotAvailableMessage = true;
        }
      }
    }

  bool GotTransform() const
    {
    return m_GotTransform;
    }

  bool GotTransformNotAvailableMessage() const
    {
    return m_GotTransformNotAvailableMessage;
    }

  const Transform & GetTransform() const
    {
    return this->m_Transform;
    }

  const PayloadType & GetTransformBetweenCoordinateSystems() const
    {
    return m_TransformBetweenCoordinateSystems;
    }
 
  void Clear()
    {
    this->m_GotTransform = false;
    this->m_GotTransformNotAvailableMessage = false;
    }

private:

  PayloadType         m_TransformBetweenCoordinateSystems;
  Transform           m_Transform;
  
  bool                m_GotTransform;
  bool                m_GotTransformNotAvailableMessage;
};

} // end namespace igstk

#endif
