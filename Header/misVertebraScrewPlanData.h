#pragma once

#include "misPlanData.h"
#include "misVertebraEnum.h"

// The misVertebraScrewPlanData  describes and implant or screw properties such as start, end positions, diameter, length,
// 
class  misVertebraScrewPlanData : public misPlanData
{
public:
	misVertebraScrewPlanData(
		const std::string& parentImageUid,
		std::weak_ptr<parcast::IPackagePlanRelRepo> pkgPlanRelRepo,
		std::weak_ptr<ICoordinateSystemCorrelationManager<std::string>> correlationManager,
		std::weak_ptr<parcast::IPlanTransformCalculator> planTranformCalculator,
		std::weak_ptr<parcast::ITransformFactory> tranformFactory,
		std::weak_ptr<parcast::IPlanRepo> planRepo, double targetRegionRadius, double screwDiameter);
	~misVertebraScrewPlanData(void);

	misVertebraScrewDirectionEnum	GetScrewVerbetraDirection();
	misVertebraNameEnum				GetScrewVerbetraPosition();
	misImplanteBrandnamesEnum		GetImplantBrand();
	double	GetScrewLength();
	void	SetScrewVerbetraDirection(misVertebraScrewDirectionEnum loc);
	void	SetScrewVerbetraPosition(misVertebraNameEnum pos);
	void	SetImplantBrand(misImplanteBrandnamesEnum brand);
	void	SetScrewLength(double len);
	void	DeepCopy(std::weak_ptr<misPlanData> screwPlanData);
	bool GetScrewPlacementFinalized() override;
	void SetScrewPlacementFinalized(bool isFinished) override;
	MisObjectType   GetObjectType(void);
private:
	misVertebraScrewDirectionEnum	m_ScrewVerbetraDirection;
	misVertebraNameEnum				m_ScrewVerbetraPosition;
	misImplanteBrandnamesEnum		m_ImplantBrand;

	double	m_ScrewLength;
	bool	m_ScrewPlacementFinalized;
};

