
#pragma once


#include <dcmtk/config/osconfig.h>
#include <dcmtk/dcmdata/dctk.h>
class D2DCommon
{
public:

	D2DCommon() : m_logStream(NULL), m_debug(OFFalse), m_inventMissingType2Attribs(OFTrue),
		m_inventMissingType1Attribs(OFFalse)
	{
	}
	/** Prints a message to the given stream.
	 ** @param  stream - [out] output stream to which the message is printed
	 *  @param  message1 - [in] first part of message to be printed
	 *  @param  message2 - [in] second part of message to be printed
	 *  @return none
	 */
	void printMessage(OFConsole *stream,
							 const OFString& message1,
							 const OFString& message2 = "") const
	{
		if (stream != NULL)
		{
			stream->lockCerr() << message1 << message2 << std::endl;
			stream->unlockCerr();
		}
	}
	
  /** Sets the log stream
   *  The log stream is used to report any warnings and error messages.
   *  @param stream - [out] pointer to the log stream (might be NULL = no messages)
   *  @return none
   */
  void setLogStream(OFConsole *stream)
  {
    m_logStream= stream;
  }

  /** Sets the debug mode
   *  @param debugMode - [in] New status for debug mode
   *  @return none
   */
  void setDebugMode(const OFBool& debugMode) { m_debug = debugMode; };

/** Check whether given type 1 attribute is present and has a length > 0.
	 *  @param  key - [in] The attribute tag check
	 *  @param  targetDset - [out] targetDset
	 *  @param  defaultValue - [in] value to be inserted if attribute is missing
	 *                         (needs invent option for type 1 attributes enabled)
	 *  @return A string with an error message if attribute is not present
	 *          or has length of 0
	 */
	OFString checkAndInventType1Attrib(const DcmTagKey& key,
									   DcmDataset* targetDset,
									   const OFString& defaultValue = "") const;
	
	
	/** Inserts an empty element with the given tag into a dataset
	 *  @param  key - [in] The attribute tag to check
	 *  @param  targetDset - [out] targetDset
	 *  @return A string with an error message if attribute is not present
	 *          nor gets inserted automatically (see m_inventMissingType2Attribs)
	 */
	OFString checkAndInventType2Attrib(const DcmTagKey& key,
									   DcmDataset* targetDset) const;

protected:
	

  /// stream where warning/error message are sent to.
  /// can be NULL (default, no output).
  OFConsole *m_logStream;

  /// debug mode status
  OFBool m_debug;
	
	/// If true, missing type 2 elements are inserted automatically (empty value).
	/// Enabled per default.
	OFBool m_inventMissingType2Attribs;
	
	/// If true, missing type 1 elements are inserted automatically with a
	/// predefined value, if possible. Disabled per default.
	OFBool m_inventMissingType1Attribs;

};
	