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
#ifndef __MARKER_H__
#define __MARKER_H__

#include "Collection.h"
#include "Facet.h"
#include "MCamera.h"
#include "Persistence.h"
#include "Xform3D.h"

using namespace MTCollection;

namespace MTMarker
{
class Marker
{
public:
  Marker(mtHandle h=0);
  ~Marker();
  inline mtHandle getHandle()
  { 
	  return m_handle; 
  };

  mtHandle getTemplateFacets();
  int restoreTemplate(mtHandle persistenceHandle, const char* name);
  
  char* getName();
  void setName(char* name);
  bool wasIdentified(MCamera *cam);
  //Obtains the pose of the marker in the given camera's coordinate space.
  Xform3D* marker2CameraXf(mtHandle camHandle);
  Xform3D* GetMarker2ReferenceXf(mtHandle camHandle);
  bool WasIdentifiedInReferenceSpace(mtHandle camHandle);
  Xform3D* tooltip2MarkerXf();
   Xform3D* Gettooltip2Refrence(mtHandle camHandle);
  mtHandle identifiedFacets (MCamera *cam);
  // void setJitterFilteringFraction(double newVal); // Claudio
   // double getJitterFilteringFraction();
  int addTemplateFacet(Facet* newFacet, Xform3D* facet1ToNewFacetXf);
  bool validateTemplate(double positionToleranceMM, std::string complString);
  int storeTemplate(Persistence* p, const char* name);
  void SetReferenceCamera(mtHandle camHandle );

private:
  mtHandle m_handle;
  bool ownedByMe;
  char m_MarkerName[400];

};
};

#endif
