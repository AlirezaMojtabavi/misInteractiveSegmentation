#pragma once

class misStickerMapper : public vtkMapper
{
private:
	misStickerMapper(void);
	~misStickerMapper(void);

	double * m_ToolTip;
	double * m_EntryPoint;
	double * m_TargetPoint;

public:

protected:
	GLuint m_OcQuery    ;
	void vertex(float x, float y, float z);
	tgt::Texture   testTExture;
public:
	tgt::Texture GetTestTExture() const;
	void SetTestTExture(tgt::Texture val);

	virtual void Render(vtkRenderer *ren, vtkActor *a)  ;
	void renderQuad2(vtkRenderer *ren);
	void renderQuad();
	void drawQuads(float x, float y, float z);

	static   misStickerMapper* New();


#pragma region SyringeBox

	void SetToolTip(double * CurrentToolTip);
	void SetEntryPoint(double * CurrentEntryPoint);
	void SetTargetPoint(double * CurrentTargetPoint);

	//Range -300 to +300
	void UpdateBox(vtkRenderer *ren, int val);

	//This function generates the appropriate value which is set to UpdateBox function
	int GenerateRangeToUpdateBox();

	//Determines if Drilling is in progress and we must update the colored boxes or not
	bool DrillingIsInProgress();

	//Main function which accumulates all codes of updating the box all together
	void RenderBox(vtkRenderer *ren);

#pragma endregion

};

