/**************************************************************
*
*     Micron Tracker: Example C++ wrapper and Multi-platform demo
*   
*     Written by: 
*      Shahram Izadyar, Robarts Research Institute - London- Ontario , www.robarts.ca
*      Claudio Gatti, Claron Technology - Toronto -Ontario, www.clarontech.com
*
*     Copyright Claron Technology 2000-2003
*
***************************************************************/
#ifndef __VECTOR_H__
#define __VECTOR_H__

class MTCVector
{
public:
  MTCVector(mtHandle h =0);
  ~MTCVector();
  mtHandle Handle();

  void getEndPos2x3(double* result);
  void setEndPos2x3(double* newPos2x3);
  void getEndXPoints(double* result);



private:
  mtHandle m_handle;
  bool ownedByMe;
};

#endif
