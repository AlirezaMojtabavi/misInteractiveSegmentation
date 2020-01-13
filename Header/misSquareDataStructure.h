#pragma once

#include "VisualizationGeneralTypes.h"

struct SquareDS
{
	double leftDownPointX;
	double leftDownPointY;
	double leftDownPointZ;

	double leftUpPointX;
	double leftUpPointY;
	double leftUpPointZ;

	double rightDownPointX;
	double rightDownPointY;
	double rightDownPointZ;

	double rightUpPointX;
	double rightUpPointY;
	double rightUpPointZ;


};
class misSquareDataStructure  
{
  public:
	  
	  int result;
	  //-----------------------------------
	  ///////// Constructor
	  static misSquareDataStructure *New()
	  {
		  return new misSquareDataStructure;
	  }
     //-------------------------------------
	  int CheckSquare(SquareDS planSquare, SquareDS viewSquare,IMAGEORIENTATION orientation);
 protected:
 private:
};