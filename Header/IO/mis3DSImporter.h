#pragma once

class vtkPolyData;

struct bachBlock
{
	vtkAlgorithmOutput*  algorithm;
	vtkProperty*  prop;
	bachBlock();
};
class mis3DSImporter : public vtkImporter
{
public:
  static mis3DSImporter *New()
  {
	  return new 		  mis3DSImporter;
  }


  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Specify the name of the file to read.
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  // Description:
  // Set/Get the computation of normals. If on, imported geometry will
  // be run through vtkPolyDataNormals.
  vtkSetMacro(ComputeNormals,int);
  vtkGetMacro(ComputeNormals,int);
  vtkBooleanMacro(ComputeNormals,int);

  // Description:
  // Return the file pointer to the open file.
  FILE *GetFileFD() {return this->FileFD;};
   void Read ();
  vtk3DSOmniLight *OmniList;
  vtk3DSSpotLight *SpotLightList;
  vtk3DSCamera    *CameraList;
  vtk3DSMesh      *MeshList;
  vtk3DSMaterial  *MaterialList;
  vtk3DSMatProp   *MatPropList;
  std::vector<vtkSmartPointer<vtkActor>> getActors();
  std::vector<bachBlock> getBatches();

protected:
  mis3DSImporter();
  ~mis3DSImporter();

  std::vector<vtkSmartPointer<vtkActor>> m_Actors;
  virtual int ImportBegin ();
  virtual void ImportEnd ();
  void ImportAllActor ();
  virtual void ReadData();
  vtkPolyData *GeneratePolyData (vtk3DSMesh *meshPtr);
  int Read3DS ();

  char *FileName;
  FILE *FileFD;
  int ComputeNormals;
private:
 std::vector<bachBlock>  m_Batches;
  mis3DSImporter(const mis3DSImporter&);  // Not implemented.
  void operator=(const mis3DSImporter&);  // Not implemented.
  void ImportProperties (vtkRenderer *vtkNotUsed(renderer));
};
