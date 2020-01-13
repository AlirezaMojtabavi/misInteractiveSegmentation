#pragma once
class IValidLandmarksEnumerator
{
public:
	virtual ~IValidLandmarksEnumerator() = default;
	virtual size_t GetNumberofCurrentValidLandmarks() = 0;
};
