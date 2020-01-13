#include "StdAfx.h"
#include "misSimpleQuadMapper.h"

using namespace tgt;
misSimpleQuadMapper::misSimpleQuadMapper(void)
{
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


misSimpleQuadMapper::~misSimpleQuadMapper(void)
{
}

void misSimpleQuadMapper::renderQuad2()
{
	 static int i=-300;
	 i=i+5;
	if (i>300)
	{
		i=-300;
	}

		UpdateBox(i);
	 
	
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







void misSimpleQuadMapper::renderQuad() {

	//RAMA Commented
	//glDepthFunc(GL_ALWAYS);

	glBeginOcclusionQueryNV( m_OcQuery);
	//RAMA Commented

	//RAMA Commented
	//RAMA Commented 

	float matModelView[16];
	float matProjection[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,matModelView);
	glGetFloatv(GL_PROJECTION_MATRIX,matProjection);

	double p[4];
	p[0]=matProjection[3]-matProjection[2];
	p[1] =matProjection[7]-matProjection[6];
	p[2]=matProjection[11]-matProjection[10];
	p[3]=matProjection[15]-matProjection[14];

	double pFar[4];
	pFar[0]=matProjection[3]+matProjection[2];
	pFar[1] =matProjection[7]+matProjection[6];
	pFar[2]=matProjection[11]+matProjection[10];
	pFar[3]=matProjection[15]+matProjection[14];

	
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

void misSimpleQuadMapper::Render( vtkRenderer *ren, vtkActor *a )
{
	//TextureUnit  unit1;
	//unit1.activate();
	//testTExture.enable();
	//testTExture.bind();
	//
	renderQuad2();
	//testTExture.Disable();
}
void misSimpleQuadMapper::drawQuads(float x, float y, float z)
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
void misSimpleQuadMapper::vertex(float x, float y, float z)
{
	//glColor3f(x,y,z);
	glTexCoord3f( x, y, z);
	glVertex3f(x,y,z); 

}

tgt::Texture misSimpleQuadMapper::GetTestTExture() const
{
	return testTExture;
}

void misSimpleQuadMapper::SetTestTExture( tgt::Texture val )
{
	testTExture = val;
}

misSimpleQuadMapper* misSimpleQuadMapper::New()
{
	return new 		misSimpleQuadMapper;
}

void misSimpleQuadMapper::UpdateBox( int val )
{
	GLfloat myLeft = -150;
	GLfloat myMiddle = val;
	GLfloat myRight = 150;
	GLfloat myUp = 300;
	GLfloat myDown = -300;


	if(val < -300)
	{
		val = -300;
	}
	else if(val > 300)
	{
		val = 300;
	}



	glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
	glEnable ( GL_COLOR_MATERIAL );

	glBegin(GL_QUADS);

	glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(myLeft, myDown);


	glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(myRight, myDown);


	glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(myRight, myMiddle);


	glColor3f(1.f, 0.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(myLeft, myMiddle);


	glEnd();


	glBegin(GL_QUADS);

	glColor3f(0.f, 1.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(myLeft, myMiddle);
	


	glColor3f(0.f, 1.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(myRight, myMiddle);


	glColor3f(0.f, 1.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(myRight, myUp);


	glColor3f(0.f, 1.f,0.0f);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex2f(myLeft, myUp);


	glEnd();
}




