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
#ifndef __FACET_H__
#define __FACET_H__

#include "Collection.h"
#include "MCamera.h"
#include "MTCVector.h"
#include "Xform3D.h"

class Facet
{
public:
  Facet(mtHandle h =0);
  ~Facet();
  inline mtHandle getHandle(){ return m_handle; };
  void getXpoints( MCamera *cam, double *result2x3x2x2); //[LV/SV][L/R/M][base/head][X/Y]
  std::vector<MTCVector *> IdentifiedVectors();
  std::vector<MTCVector *> TemplateVectors();
  bool setVectorsFromSample(std::vector<MTCollection::Collection*> &sampledVectorSets, 
	  std::string &outCompletionExplanation , double maxSampleErrorAllowedMM = 2.0);
  bool validateTemplate(double positionToleranceMM, std::string outCompletionString = NULL);
  bool identify(MCamera* cam, std::vector<MTCVector*> vectorSet, double positionToleranceMM);
  Xform3D* getFacet2CameraXf(MCamera* cam);


private:
  mtHandle m_handle;
  bool ownedByMe;
};

#endif
