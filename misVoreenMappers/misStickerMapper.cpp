#include "StdAfx.h"
#include "misStickerMapper.h"

#include "misSimplePointType.h"

using namespace tgt;
misStickerMapper::misStickerMapper(void)
{
	this->m_EntryPoint = new double[3];
	this->m_TargetPoint = new double[3];
	this->m_ToolTip = new double[3];

	for(int i=0; i<3; i++)
	{
		this->m_EntryPoint[i] = 0;
		this->m_TargetPoint[i] = 0;
		this->m_ToolTip[i] = 0;
	}

	char *ext = (char*)glGetString( GL_EXTENSIONS );

	if( strstr( ext, "GL_NV_occlusion_query" ) == NULL )
	{

		return;
	}
	else
	{
		glGenOcclusionQueriesNV    = (PFNGLGENOCCLUSIONQUERIESNVPROC)wglGetProcAddress("glGenOcclusionQueriesNV");
		glDeleteOcclusionQueriesNV = (PFNGLDELETEOCCLUSIONQUERIESNVPROC)wglGetProcAddress("glDeleteOcclusionQueriesNV");
		glGetOcclusionQueryuivNV   = (PFNGLGETOCCLUSIONQUERYUIVNVPROC)wglGetProcAddress("glGetOcclusionQueryuivNV");
		glBeginOcclusionQueryNV    = (PFNGLBEGINOCCLUSIONQUERYNVPROC)wglGetProcAddress("glBeginOcclusionQueryNV");
		glEndOcclusionQueryNV      = (PFNGLENDOCCLUSIONQUERYNVPROC)wglGetProcAddress("glEndOcclusionQueryNV");

		if( !glGenOcclusionQueriesNV  || !glDeleteOcclusionQueriesNV || 
			!glGetOcclusionQueryuivNV || !glBeginOcclusionQueryNV    || 
			!glEndOcclusionQueryNV )
		{

			return;
		}
	}

	//
	// Create query objects for our sphere and plane
	//

	glGenOcclusionQueriesNV( 1, &m_OcQuery );
	 
	
	
}


misStickerMapper::~misStickerMapper(void)
{
	delete this->m_ToolTip;
	delete this->m_EntryPoint;
	delete this->m_TargetPoint;
}

void misStickerMapper::renderQuad2(vtkRenderer *ren)
{
	RenderBox(ren);

	/* static int i=-300;
	 i=i+5;
	if (i>300)
	{
		i=-300;
	}

		UpdateBox(i);*/
	 
	
	return;
	//int w =10;
	//int x = 20;
	//int y = 50;
	// int h =100;
	//unsigned int rgba = 0xff0000ff; // red, no alpha
	//glBegin(GL_QUADS);
	///*glColor4f(((rgba>>24)&0xff)/255.0f,
	//((rgba>>16)&0xff)/255.0f, 
	//((rgba>>8)&0xff)/255.0f,
	//(rgba&0xff)/255.0f);*/
	//glColor4f(250.0f,
	//	0.0f, 
	//	0.0f,
	//	1.0f);
	//glVertex3f(x,y,0);
	//glVertex3f(x+w,y,0);
	//glVertex3f(x+w,y+h,0);
	//glVertex3f(x,y+h,0);
	//glEnd();
	//glColor4f(1, 1, 1, 1);


	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
		glEnable ( GL_COLOR_MATERIAL );

	glBegin(GL_QUADS);
	
	glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(-300.f, -300.f);
	

	glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(300.f, -300.f);
	

	glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(300.f, 0.f);
	

	glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(-300.f, 0.f);


	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.f, 1.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(-300.f, 0.f);


	glColor3f(0.f, 1.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(300.f, 0.f);


	glColor3f(0.f, 1.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(300.f, 300.f);


	glColor3f(0.f, 1.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(-300.f, 300.f);


	glEnd();

	

}







void misStickerMapper::renderQuad() {



	glBeginOcclusionQueryNV( m_OcQuery);
	

	
	glBegin(GL_QUADS);
	glTexCoord2f(0.f, 0.f);
	glVertex2f(-1.f, -1.f);

	glTexCoord2f(1.f, 0.f);
	glVertex2f(1.f, -1.f);

	glTexCoord2f(1.f, 1.f);
	glVertex2f(1.f, 1.f);

	glTexCoord2f(0.f, 1.f);
	glVertex2f(-1.f, 1.f);
	glEnd();

	glDepthFunc(GL_LESS);
	glEndOcclusionQueryNV( );
	GLuint planeFragmentCount;

	glGetOcclusionQueryuivNV( m_OcQuery, GL_PIXEL_COUNT_NV, &planeFragmentCount );


}

void misStickerMapper::Render( vtkRenderer *ren, vtkActor *a )
{
	//TextureUnit  unit1;
	//unit1.activate();
	//testTExture.enable();
	//testTExture.bind();
	//
	renderQuad2(ren);
	//testTExture.Disable();
}
void misStickerMapper::drawQuads(float x, float y, float z)
{

	glBegin(GL_QUADS);
	/* Back side */
	glNormal3f(0.0, 0.0, -1.0);
	vertex(0.0, 0.0, 0.0);
	vertex(0.0, y, 0.0);
	vertex(x, y, 0.0);
	vertex(x, 0.0, 0.0);

	/* Front side */
	glNormal3f(0.0, 0.0, 1.0);
	vertex(0.0, 0.0, z);
	vertex(x, 0.0, z);
	vertex(x, y, z);
	vertex(0.0, y, z);

	/* Top side */
	glNormal3f(0.0, 1.0, 0.0);
	vertex(0.0, y, 0.0);
	vertex(0.0, y, z);
	vertex(x, y, z);
	vertex(x, y, 0.0);

	/* Bottom side */
	glNormal3f(0.0, -1.0, 0.0);
	vertex(0.0, 0.0, 0.0);
	vertex(x, 0.0, 0.0);
	vertex(x, 0.0, z);
	vertex(0.0, 0.0, z);

	/* Left side */
	glNormal3f(-1.0, 0.0, 0.0);
	vertex(0.0, 0.0, 0.0);
	vertex(0.0, 0.0, z);
	vertex(0.0, y, z);
	vertex(0.0, y, 0.0);

	/* Right side */
	glNormal3f(1.0, 0.0, 0.0);
	vertex(x, 0.0, 0.0);
	vertex(x, y, 0.0);
	vertex(x, y, z);
	vertex(x, 0.0, z);
	glEnd();

}
void misStickerMapper::vertex(float x, float y, float z)
{
	//glColor3f(x,y,z);
	glTexCoord3f( x, y, z);
	glVertex3f(x,y,z); 

}

tgt::Texture misStickerMapper::GetTestTExture() const
{
	return testTExture;
}

void misStickerMapper::SetTestTExture( tgt::Texture val )
{
	testTExture = val;
}

misStickerMapper* misStickerMapper::New()
{
	return new 		misStickerMapper;
}

void misStickerMapper::UpdateBox( vtkRenderer *ren,int val )
{
	//Struct for saving opengl colors 
	struct myColor
	{
		GLfloat Color_Red;
		GLfloat Color_Green;
		GLfloat Color_Blue;

		void SetColorToRed()
		{
			this->Color_Red = 1.0f;
			this->Color_Green = 0.0f;
			this->Color_Blue = 0.0f;
		}

		void SetColorToGreen()
		{
			this->Color_Red = 0.0f;
			this->Color_Green = 1.0f;
			this->Color_Blue = 0.0f;
		}

		void SetColorToBlue()
		{
			this->Color_Red = 0.0f;
			this->Color_Green = 0.0f;
			this->Color_Blue = 1.0f;
		}
	};

	//struct to save normal vectors used in opengl
	struct myNormalVector
	{
		GLfloat nx;
		GLfloat ny;
		GLfloat nz;
	};

	//A lambda function to change a point in view coordinate into a point in world coordinate
	//NOTICE: Do not forget to delete the outputs of this method while used. This can avoid memory leaks
	auto changeViewCoordIntoWorldCoord = [&](vtkRenderer *ren, GLfloat x, GLfloat y, GLfloat z)->double*
	{
		double * worldRDPt = new double[4]; 
		ren->SetViewPoint(x,y,z);
		ren->ViewToWorld();
		ren->GetWorldPoint(worldRDPt);

		return worldRDPt;
	};


	//bounds val which is in range [-300, +300] into range [minimum, maximum]
	//
	auto LimitValueInPredefinedBound = [&](int val, GLfloat minimum, GLfloat maximum )->GLfloat
	{
		if(val < -300)
		{
			val = -300;
		}
		else if(val > 300)
		{
			val = 300;
		}

		//bound the values between a minimum and a maximum

		GLfloat Range = (maximum - minimum);

		return ((GLfloat)val + 300.0)/600.0 * (Range) + minimum;

	};

////////////////////////////////////////////////////////////////////////////////////


	//A lambda function to draw a vertex in 3d mode
	auto DrawOneVertexInWorldCoordinate = [&](vtkRenderer * Renderer, myColor Col, myNormalVector NormalVector, GLfloat x, GLfloat y, GLfloat z)->void
	{
		double * CorrectedPoint = changeViewCoordIntoWorldCoord(Renderer, x, y, z);

		GLfloat Corrected_x = CorrectedPoint[0];
		GLfloat Corrected_y = CorrectedPoint[1];
		GLfloat Corrected_z = CorrectedPoint[2];

		glColor3f(Col.Color_Red, Col.Color_Green, Col.Color_Blue);
		glNormal3f(NormalVector.nx, NormalVector.ny, NormalVector.nz);
		glVertex3f(Corrected_x, Corrected_y, Corrected_z);

		delete CorrectedPoint;
	};
//////////////////////////////////////////////////////////////////////////////////
	GLfloat myLeft = 0.6;
	GLfloat myRight = 0.7;

	GLfloat myUp = 0.8;
	GLfloat myMiddle = val;	
	GLfloat myDown = 0.6;

	GLfloat myDepth = 0.1;

	if(val < -300)
	{
		val = -300;
	}
	else if(val > 300)
	{
		val = 300;
	}

	GLfloat CorrectedInputValue = LimitValueInPredefinedBound(val,myDown,myUp);
	
	myColor ColorOfVertex;
	myNormalVector NormalVector;
	
	NormalVector.nx = 0.0;
	NormalVector.ny = 0.0;
	NormalVector.nz = 1.0;

	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glEnable ( GL_COLOR_MATERIAL );

	glBegin(GL_QUADS);


	ColorOfVertex.SetColorToRed();
	DrawOneVertexInWorldCoordinate(ren, ColorOfVertex, NormalVector, myLeft,myDown,myDepth);
	/*glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(myLeft, myDown);*/

	DrawOneVertexInWorldCoordinate(ren, ColorOfVertex, NormalVector, myRight,myDown,myDepth);
	/*glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(myRight, myDown);*/

	DrawOneVertexInWorldCoordinate(ren, ColorOfVertex, NormalVector, myRight,CorrectedInputValue,myDepth);
	/*glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(myRight, myMiddle);*/

	DrawOneVertexInWorldCoordinate(ren, ColorOfVertex, NormalVector, myLeft,CorrectedInputValue,myDepth);
	//glColor3f(1.f, 0.f,0.0f);
	//glNormal3f(0.0, 0.0, 1.0);
	//glVertex3f(myLeft, myMiddle);
	glEnd();


	//Drawing another colored square


	ColorOfVertex.SetColorToGreen();
	/*NormalVector.nx = 0.0;
	NormalVector.ny = 0.0;
	NormalVector.nz = 1.0;*/

	glBegin(GL_QUADS);

	DrawOneVertexInWorldCoordinate(ren, ColorOfVertex, NormalVector, myLeft,CorrectedInputValue,myDepth);
	//glColor3f(0.f, 1.f,0.0f);
	//glNormal3f(0.0, 0.0, 1.0);
	//glVertex3f(myLeft, myMiddle);
	

	DrawOneVertexInWorldCoordinate(ren, ColorOfVertex, NormalVector, myRight,CorrectedInputValue,myDepth);
	/*glColor3f(0.f, 1.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(myRight, myMiddle);*/

	DrawOneVertexInWorldCoordinate(ren, ColorOfVertex, NormalVector, myRight,myUp,myDepth);
	//glColor3f(0.f, 1.f,0.0f);
	//glNormal3f(0.0, 0.0, 1.0);
	//glVertex3f(myRight, myUp);

	DrawOneVertexInWorldCoordinate(ren, ColorOfVertex, NormalVector, myLeft,myUp,myDepth);
	//glColor3f(0.f, 1.f,0.0f);
	//glNormal3f(0.0, 0.0, 1.0);
	//glVertex3f(myLeft, myUp);


	glEnd();

}

bool misStickerMapper::DrillingIsInProgress()
{
	//return true;
	//TODO: THIS algorithm may not work properly and needs consideration

	//Algorithm:
	//V1 = tip - entry
	//V2 = tip - target
	//if the angle of V1 and V2 are very small then we still did not started drilling
	//if the angle of V1 and V2 are very big near 180 degrees then we have drilling in progress

	double V1[3] = {0,0,0};
	double V2[3] = {0,0,0};

	for(int i=0; i<3; i++)
	{
		V1[i] = m_EntryPoint[i]  - m_ToolTip[i];
		V2[i] = m_TargetPoint[i] - m_ToolTip[i];
	}
	

	misSimplePointType V1Point, V2Point;
	V1Point.SetPoint(V1);
	V2Point.SetPoint(V2);

	double angle = misSimplePointType::GetAngle(V1Point, V2Point);

	if(angle > 180)
	{
		angle -= 180;
	}
	
	if((angle < 180) && (angle > 90))
	{
		return true;
	}
	return false;
}

void misStickerMapper::SetToolTip( double * CurrentToolTip )
{
	for(int i=0; i<3; i++)
	{
		this->m_ToolTip[i] = CurrentToolTip[i];
	}
}

void misStickerMapper::SetEntryPoint( double * CurrentEntryPoint )
{
	for(int i=0; i<3; i++)
	{
		this->m_EntryPoint[i] = CurrentEntryPoint[i];
	}
}

void misStickerMapper::SetTargetPoint( double * CurrentTargetPoint )
{
	for(int i=0; i<3; i++)
	{
		this->m_TargetPoint[i] = CurrentTargetPoint[i];
	}
}

void misStickerMapper::RenderBox(vtkRenderer *ren)
{
	if(this->DrillingIsInProgress())
	{
		int Val = this->GenerateRangeToUpdateBox();
		this->UpdateBox(ren,Val);
	}
	else
	{
		this->UpdateBox(ren,-300);
	}
}

int misStickerMapper::GenerateRangeToUpdateBox()
{
	double DevisionOfScrewLength = 1.0;
	double ScrewLength = 1.0;

	double TempVector[3] = {0,0,0};
	
	for(int i=0; i<3; i++)
	{
		TempVector[i] = this->m_TargetPoint[i] - this->m_EntryPoint[i];
	}

	ScrewLength = sqrt((TempVector[0]*TempVector[0]) + (TempVector[1]*TempVector[1]) + (TempVector[2]*TempVector[2]));


	for(int i=0; i<3; i++)
	{
		TempVector[i] = this->m_ToolTip[i] - this->m_EntryPoint[i];
	}

	DevisionOfScrewLength = sqrt((TempVector[0]*TempVector[0]) + (TempVector[1]*TempVector[1]) + (TempVector[2]*TempVector[2]));
	DevisionOfScrewLength = abs(ScrewLength - DevisionOfScrewLength);


	//Note:
	//this formula comes from:
	//    Y - y0     X - x0
	//   ------ = -----------
	//   y1 - y0	 x1 - x0
	//
	//We have assumed that the red-green box accepts the range of (-300  to  +300)
	//and we have 2 points to determine the formula of line:
	//(0, -300) and (Screw length, +300)
	return (((600 * DevisionOfScrewLength) - (300 * ScrewLength)) / ScrewLength);
}




