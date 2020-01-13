#pragma once

class  misMatrix : public Serializable
{
	vnl_matrix<double> m_Matrix;

	void serialize(XmlSerializer& s) const;
	void deserialize(XmlDeserializer& s);

public:
	misMatrix(void);
	~misMatrix(void);

	void Set(vtkMatrix4x4* matrix);
	vtkMatrix4x4*  GetVTKMatrix();
	void Set(vnl_matrix<double> CurrentData);
	vnl_matrix<double> Get_vnl_matrix();



	//makes a file called HTn2r.xml.xml and writes data in it
	void WriteMisMatrixStrctInFile();

	//reads data from xml file which is located on the root of RoboticProject folder
	void ReadMisMatrixStrctFromXmlFile();
};
