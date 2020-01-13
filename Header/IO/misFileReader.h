#ifndef MISFILEREADER_H_HEADER_INCLUDED_B80702A9
#define MISFILEREADER_H_HEADER_INCLUDED_B80702A9

//#include "misSeconderyNeededHeader.h"

class vtkPolyData;

class misFileReader
{
public:
	static vtkSmartPointer<vtkPolyData> ReadPolydataFromOBJFile(std::string fileName);
	static vtkSmartPointer<vtkPolyData> ReadPolydataFromSTLFile(std::string fileName);
};

#endif /* MISFILEREADER_H_HEADER_INCLUDED_B80702A9 */
