#pragma once
#include "ISimpleDataPackage.h"
#include "IConfirmedImageCounter.h"

class misConfirmedImageCounter : public IConfirmedImageCounter
{
public:
	bool IsThereAnyUnconfirmedImage(std::shared_ptr<ISimpleDataPackage> packge) override;
private:
 };


 
