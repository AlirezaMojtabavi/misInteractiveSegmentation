#pragma once
class ISideAnnotation
{
public:
	virtual ~ISideAnnotation() = default;
	virtual void SetSideAnnotation(std::map<parcast::AnnotationPositionOnWindow, parcast::AnnotationInfo> annotationData) = 0;
	virtual void SetRenWinSize(int horizantalSize, int verticalSize) = 0;
};

