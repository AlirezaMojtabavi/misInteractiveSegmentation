#pragma once
class IOblqueView
{
public:
	virtual ~IOblqueView() = default;
	virtual void SetObliqueFlag(bool isOblique) = 0;
};