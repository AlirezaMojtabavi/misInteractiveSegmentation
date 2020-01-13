#pragma once
#include "misitkTypdef.h"

typedef   itk::Vector<double,3>          misItkVectorType;
typedef   std::vector<misItkVectorType>   misItkListVectorType;
typedef   itk::Point<double,3>           misItkPointType ;
typedef   std::vector<misItkPointType>   misItkListPointType;
typedef   itk::Point<int,4>  misIntPointStrct;
typedef   itk::Point<float,2>               misFloatPointStrct;
typedef   std::vector<misFloatPointStrct>   misFloatPointsListTypdef;
typedef   itk::Matrix<double,4,4>           misItkMatrix4X4;
typedef	  itk::Versor<double>		        misItkVersorType;
