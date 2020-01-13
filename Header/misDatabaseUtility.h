#pragma once

#include "misDateTime.h"
#include "misLogger.h"

#ifndef MISDATABASEUTILITY
#define MISDATABASEUTILITY

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Data::SqlTypes;
using namespace System::IO;

class misDatabaseUtility
{
public :

	misDatabaseUtility(void);
	static misDatabaseUtility* GetInstance();
	bool            IsDataFieldNULL(SqlDataReader^ reader, String^ fieldName);

	int             DoCommand(String^ storedProcedureName,System::Collections::Generic::List<SqlParameter^>^ parameters);
	int             DoCommand(String^ storedProcedureName);
	SqlDataReader^  DoReader(String^ storedProcedureName,System::Collections::Generic::List<SqlParameter^>^ parameters);
	SqlDataReader^  DoReader(String^ storedProcedureName);
	void			EndReader(void);


	static std::string	ToString( String^ sourceString);

	std::string		GetStringFieldByName( SqlDataReader^ reader, String^ fieldName );
	misDateTime		GetDateTimeFieldByName( SqlDataReader^ reader, String^ fieldName );
	bool			GetBooleanFieldByName( SqlDataReader^ reader, String^ fieldName );
	int				GetIntFieldByName( SqlDataReader^ reader, String^ fieldName );
	double			GetDoubleFieldByName( SqlDataReader^ reader, String^ fieldName );	
	float*     		GetFloatArrayFieldByName( SqlDataReader^ reader, String^ fieldName, int length );
	int*     		GetIntArrayFieldByName( SqlDataReader^ reader, String^ fieldName, int length );
	double*         GetDoubleArrayFieldByName( SqlDataReader^ reader, String^ fieldName, int length );
	SqlBinary		GetBinaryFieldByName( SqlDataReader^ reader, String^ fieldName );

	vtkMatrix4x4*	GetMatrix4x4(SqlBinary bytes);
	MemoryStream^	GetMemoryStreamFromTransform(vtkTransform* transform);
	MemoryStream^	GetMemoryStreamFromTransform(vtkMatrix4x4* matrix);

	void			SwitchToPortableDatabase();
	void			SwitchToMainDatabase();

private:

	gcroot<String^>		    m_DatabasePath;
	misLogger*				m_Logger;
	gcroot<SqlConnection^>  m_sqlConnection;

private:

	System::Object^ GetDataFieldByName(SqlDataReader^ reader, String^ fieldName);
	float*	ConvertSqlBinaryToFloatArray(SqlBinary binaryData, int length);
	int*	ConvertSqlBinaryToIntArray(SqlBinary binaryData, int length);
	double* ConvertSqlBinaryToDoubleArray(SqlBinary binaryData, int length);	

};

#endif

