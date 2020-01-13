/**************************************************************
*
*     Micron Tracker: Example C++ wrapper and Multi-platform demo
*   
*     Written by: 
*      Shahram Izadyar, Robarts Research Institute - London- Ontario , www.robarts.ca
*      Claudio Gatti, Ahmad Kolahi, Claron Technology - Toronto -Ontario, www.clarontech.com
*
*     Copyright Claron Technology 2000-2003
*
***************************************************************/
#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include "MisMicronUtilities.h"

namespace MTCollection
{
class Collection
{
public:
  Collection(mtHandle h=0);
  ~Collection();
  inline mtHandle getHandle()
  { 
	  //bool StatusOfHandle = MisMicronUtilities::CheckHandleValidity(m_handle);
	  return m_handle;
	  
  };
  inline void setHandle(mtHandle h)
  {
	  bool StatusOfHandle = MisMicronUtilities::CheckHandleValidity(m_handle);
	  if(StatusOfHandle)
	  {
		   m_handle = h;
	  }
	  
  };
  
  void add(mtHandle val);
  void remove(int idx);
  int count();
  mtHandle itemI(int idx);
  double itemD(int idx);

private:
  mtHandle m_handle;
  bool ownedByMe;
};
};

#endif
