#pragma once
class IConfirmedImageCounter
{
public:
	virtual ~IConfirmedImageCounter() = default;
	virtual bool IsThereAnyUnconfirmedImage(std::shared_ptr<ISimpleDataPackage> packge)  = 0;

};
