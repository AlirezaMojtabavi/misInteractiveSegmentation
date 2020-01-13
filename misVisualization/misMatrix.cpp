#include "StdAfx.h"
#include "misMatrix.h"

#include "misTryCatchDeserializationMACRO.h"

misMatrix::misMatrix(void)
{
	this->m_Matrix.set_size(4,4);
}


misMatrix::~misMatrix(void)
{
}

void misMatrix::Set( vnl_matrix<double> CurrentData )
{
	this->m_Matrix = CurrentData;
}

void misMatrix::Set( vtkMatrix4x4* matrix )
{
 
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
	{
		double val=matrix->GetElement(i,j);
		m_Matrix.put(i,j,val);
	}
 

}

vnl_matrix<double> misMatrix::Get_vnl_matrix()
{
	return this->m_Matrix;
}

void misMatrix::WriteMisMatrixStrctInFile()
{
	std::ofstream f;

	f.open("HTn2r.xml", std::ios::out);

	XmlSerializer s;
	s.serialize("misMatrixHTn2r",this);
	s.write(f);
	f.close();
}

void misMatrix::ReadMisMatrixStrctFromXmlFile()
{
	misMatrix HTn2r;

	XmlDeserializer s;
	std::ifstream f;

	f.open("HTn2r.xml",std::ios::in);
	s.read(f);
	s.deserialize("misMatrixHTn2r",(*this));
	f.close();
}

void misMatrix::serialize( XmlSerializer& s ) const
{
	s.serialize("R00",this->m_Matrix.get(0,0));
	s.serialize("R01",this->m_Matrix.get(0,1));
	s.serialize("R02",this->m_Matrix.get(0,2));
	s.serialize("R03",this->m_Matrix.get(0,3));

	s.serialize("R10",this->m_Matrix.get(1,0));
	s.serialize("R11",this->m_Matrix.get(1,1));
	s.serialize("R12",this->m_Matrix.get(1,2));
	s.serialize("R13",this->m_Matrix.get(1,3));

	s.serialize("R20",this->m_Matrix.get(2,0));
	s.serialize("R21",this->m_Matrix.get(2,1));
	s.serialize("R22",this->m_Matrix.get(2,2));
	s.serialize("R23",this->m_Matrix.get(2,3));	

	s.serialize("R30",this->m_Matrix.get(3,0));
	s.serialize("R31",this->m_Matrix.get(3,1));
	s.serialize("R32",this->m_Matrix.get(3,2));
	s.serialize("R33",this->m_Matrix.get(3,3));
}

void misMatrix::deserialize( XmlDeserializer& s )
{
	double Temp[4][4];
	TRYCATCHDESERILIZE("R00",Temp[0][0]);
	TRYCATCHDESERILIZE("R01",Temp[0][1]);
	TRYCATCHDESERILIZE("R02",Temp[0][2]);
	TRYCATCHDESERILIZE("R03",Temp[0][3]);

	TRYCATCHDESERILIZE("R10",Temp[1][0]);
	TRYCATCHDESERILIZE("R11",Temp[1][1]);
	TRYCATCHDESERILIZE("R12",Temp[1][2]);
	TRYCATCHDESERILIZE("R13",Temp[1][3]);

	TRYCATCHDESERILIZE("R20",Temp[2][0]);
	TRYCATCHDESERILIZE("R21",Temp[2][1]);
	TRYCATCHDESERILIZE("R22",Temp[2][2]);
	TRYCATCHDESERILIZE("R23",Temp[2][3]);

	TRYCATCHDESERILIZE("R30",Temp[3][0]);
	TRYCATCHDESERILIZE("R31",Temp[3][1]);
	TRYCATCHDESERILIZE("R32",Temp[3][2]);
	TRYCATCHDESERILIZE("R33",Temp[3][3]);

	for(int r=0;r<4;r++)
	{
		for(int c=0;c<4;c++)
		{
			this->m_Matrix.put(r,c,Temp[r][c]);
		}
	}
}

vtkMatrix4x4* misMatrix::GetVTKMatrix()
{

	vtkMatrix4x4*  mat=vtkMatrix4x4::New();
	for (int i=0;i<4;i++)
		for (int j=0;j<4;j++)
		{
			double val=m_Matrix.get(i,j);
			mat->SetElement(i,j,val);
		}
		return  mat;

}
