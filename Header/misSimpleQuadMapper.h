#pragma once

class misSimpleQuadMapper:public vtkMapper
{
protected:
	GLuint m_OcQuery    ;
	void vertex(float x, float y, float z);
	tgt::Texture   testTExture;
public:
	tgt::Texture GetTestTExture() const;
	void SetTestTExture(tgt::Texture val);

	virtual void Render(vtkRenderer *ren, vtkActor *a)  ;

	misSimpleQuadMapper(void);
	~misSimpleQuadMapper(void);
	void renderQuad2();
	void renderQuad();
	void drawQuads(float x, float y, float z);

	static   misSimpleQuadMapper* New();


#pragma region SuringeBox

	//Range -300 to +300
	void UpdateBox(int val);

#pragma endregion

	
};

