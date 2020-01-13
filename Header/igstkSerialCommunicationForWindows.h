/*=========================================================================

  Program:   Image Guided Surgery Software Toolkit
  Module:    $RCSfile: igstkSerialCommunicationForWindows.h,v $
  Language:  C++
  Date:      $Date: 2008-02-11 01:41:51 $
  Version:   $Revision: 1.12 $

  Copyright (c) ISC  Insight Software Consortium.  All rights reserved.
  See IGSTKCopyright.txt or http://www.igstk.org/copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igstkSerialCommunicationForWindows_h
#define __igstkSerialCommunicationForWindows_h

#include <windows.h>
#include <vector>
#include "igstkSerialCommunication.h"
 
/*
 * Serial data formats
 */
#define COMM_8N1    0x00 
#define COMM_8N2	0x01
#define COMM_8O1	0x02
#define COMM_8O2	0x03
#define COMM_8E1	0x04
#define COMM_8E2	0x05

#define COMM_7N1 	0x06   
#define COMM_7N2	0x07
#define COMM_7O1	0x08 
#define COMM_7O2	0x09
#define COMM_7E1	0x0A 
#define COMM_7E2	0x0B

#define COMM_OK                 1
#define COMM_IRQ_IN_USE         -1
#define COMM_OUT_OF_MEMORY      -2
#define COMM_NOT_INITIALIZED    -3
#define COMM_OUT_BUFFER_FULL    -4
#define COMM_NOT_PRESENT        -5
#define COMM_NO_DATA			-6

#define COMM_ERROR_SETTIMEOUT		-10
#define COMM_ERROR_SETBREAK			-11
#define COMM_ERROR_CLEARBREAK		-12
#define COMM_ERROR_CLEARBUFFER		-13
#define COMM_ERROR_CREATEEVENT		-14
#define COMM_ERROR_WRITE			-15
#define COMM_ERROR_WRITETIMEOUT		-16
#define COMM_ERROR_READ				-17
#define COMM_ERROR_READTIMEOUT		-18
#define COMM_ERROR_WAIT				-19
#define COMM_ERROR_WAITTIMEOUT		-20
#define COMM_ERROR_GETOVERLAPPED	-21

#define COMM_ERR_OVERRUN        0x02
#define COMM_ERR_PARITY         0x04
#define COMM_ERR_FRAME          0x08
#define COMM_ERR_BREAK          0x10

/*
 * Buffer size 
 */
#define READ_BUFFER_SIZE		3000
#define WRITE_BUFFER_SIZE		1024
namespace igstk
{

/** \class SerialCommunicationForWindows
 * 
 * \brief This class implements Windows specific methods for 32-bit 
 *        communication over a Serial Port(RS-232 connection).
 *
 *
 *  \image html  igstkSerialCommunicationForWindows.png 
 *              "SerialCommunicationForWindows State Machine Diagram"
 *  \image latex igstkSerialCommunicationForWindows.eps  
 *               "SerialCommunicationForWindows State Machine Diagram" 
 *
 *
 * \ingroup Communication
 * \ingroup SerialCommunication
 */

class SerialCommunicationForWindows : public SerialCommunication
{
public:

  /** Macro with standard traits declarations. */
  igstkStandardClassTraitsMacro( SerialCommunicationForWindows, 
                                 SerialCommunication )

public:

  /** Return value type for interface functions */ 
  typedef SerialCommunication::ResultType ResultType;

protected:

  /** Windows file handle type */
  typedef HANDLE HandleType;

  /** Constructor */
  SerialCommunicationForWindows();

  /** Destructor */
  ~SerialCommunicationForWindows();

  /** Opens serial port for communication; */
  virtual ResultType InternalOpenPort( void );

  /** Sets up communication on the open port as per the communication
      parameters. */
  virtual ResultType InternalUpdateParameters( void );

  /** Closes serial port  */
  virtual ResultType InternalClosePort( void );

  /** Send a serial break */
  virtual ResultType InternalSendBreak( void );

  /** Sleep for the number of milliseconds specified */
  virtual void InternalSleep( int milliseconds );

  /** Purge the input and output buffers */
  virtual ResultType InternalPurgeBuffers( void );

  /** Write data */
  virtual ResultType InternalWrite( const char *message,
                                    unsigned int numberOfBytes );

  /** Read data */
  virtual ResultType InternalRead( char *data, unsigned int numberOfBytes,
                                   unsigned int &bytesRead );

  /** Set the RTS value 
   *  0 : Clear the RTS (request-to-send) signal 
   *  1 : Sends the RTS signal */
  virtual ResultType InternalSetRTS(unsigned int signal);

  /** Set the timeout */
  virtual ResultType InternalSetTimeout( unsigned int timeoutPeriod );

  /** Print object information. */
  virtual void PrintSelf( std::ostream& os, itk::Indent indent ) const; 

private:
	

  unsigned int    m_OldTimeoutPeriod;

  HandleType      m_PortHandle;     // com port handle
  DCB			   m_CommSettings;

  COMMTIMEOUTS	
	  CommTimeouts;	/* com port timeouts */
};

} // end namespace igstk

#endif // __igstkSerialCommunicationForWindows_h
