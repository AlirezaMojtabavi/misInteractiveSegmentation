#pragma once

template <typename TInputImage, typename TOutputImage>
class misImageNormalizer : public ProcessObject
{
public:

	/** Standard class typedefs. */
	typedef misImageNormalizer Self;
	typedef itk::ProcessObject Superclass;
	typedef itk::SmartPointer<Self> Pointer;
	typedef itk::SmartPointer<const Self>  ConstPointer;

	/** Run-time type information (and related methods). */
	//itkTypeMacro(misImageNormalizer, Object);

	/** Method for creation through the object factory. */
	itkNewMacro(Self);

	/** Input Image Type. */
	typedef TInputImage InputImageType;

	/** Output Image Type. */
	typedef TOutputImage OutputImageType;

	/** Image dimension enumeration. */
	itkStaticConstMacro(ImageDimension, unsigned int, TInputImage::ImageDimension );

	/** Set the input fixed image. */
	itkSetObjectMacro( InputImage, InputImageType );

	/** Get the output fixed image. */
	itkGetObjectMacro( OutputImage, OutputImageType );

	/** Method to execute the preprocessing. */
	virtual void Execute();

protected:
	misImageNormalizer();
	~misImageNormalizer(){};

private:
	typename InputImageType::Pointer       m_InputImage;
	typename OutputImageType::Pointer      m_OutputImage;
};

template <typename TInputImage, typename TOutputImage>
misImageNormalizer<TInputImage, TOutputImage>::misImageNormalizer()
{
	m_InputImage   = NULL;
	m_OutputImage  = NULL;
}

template <typename TInputImage, typename TOutputImage>
void misImageNormalizer<TInputImage, TOutputImage>::Execute()
{
	typedef ChangeInformationImageFilter<TInputImage>
		CentererType;
	typedef NormalizeImageFilter<TInputImage,TOutputImage>
		NormalizerType;

	CentererType::Pointer   centerer;
	NormalizerType::Pointer normalizer;

	centerer =  CentererType::New();
	normalizer = NormalizerType::New();
	centerer->CenterImageOff();
	if (m_InputImage)
	{
		centerer->SetInput( m_InputImage );
		if (centerer->GetOutput())
		{
			normalizer->SetInput( centerer->GetOutput() );
			normalizer->Update();

			m_OutputImage = normalizer->GetOutput();
		}
	}
}
