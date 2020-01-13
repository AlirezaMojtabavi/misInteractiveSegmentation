#include "StdAfx.h"
#include "misVoreenActor.h"

misVoreenActor::misVoreenActor(void)
{
}

misVoreenActor::~misVoreenActor(void)
{
}

misVoreenActor* misVoreenActor::New()
{
	return new misVoreenActor();
}

int misVoreenActor::RenderOpaqueGeometry(vtkViewport *  viewport)
{

	return 0;
}

int misVoreenActor::RenderVolumetricGeometry(vtkViewport *viewport)
{
	int          renderedSomething = 0;
	vtkRenderer* ren = static_cast<vtkRenderer*>(viewport);

	if (!this->Mapper)
	{
		return 0;
	}

	// make sure we have a property
	if (!this->Property)
	{
		// force creation of a property
		this->GetProperty();
	}

	// is this actor opaque ?
	if (this->GetIsOpaque())
	{
		this->Property->Render(this, ren);

		// render the backface property
		if (this->BackfaceProperty)
		{
			this->BackfaceProperty->BackfaceRender(this, ren);
		}

		// render the texture 
		if (this->Texture)
		{
			this->Texture->Render(ren);
		}
		this->Render(ren, this->Mapper);
		this->Property->PostRender(this, ren);
		if (this->Texture)
		{
			this->Texture->PostRender(ren);
		}
		this->EstimatedRenderTime += this->Mapper->GetTimeToDraw();
		renderedSomething = 1;
	}

	return renderedSomething;


}
