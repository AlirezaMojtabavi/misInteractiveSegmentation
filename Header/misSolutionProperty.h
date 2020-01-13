#pragma once

#include "ITreatmentSolution.h"
#include "misAppFoldersAddress.h"
#include "misDateTime.h"
#include "misEnums.h"
#include "misStrctPatientData.h"
#include "misTypes.h"

namespace parcast
{
	class IPackageRepo;
}

//The misSolutionProperty class read and save solution properties include  folder , id , patient name , registered image and 
// reference
// 
class misSolutionProperty: public Serializable, public parcast::ITreatmentSolution
{
public:

	misSolutionProperty(std::weak_ptr<parcast::IPackageRepo> pkgRepo);
	~misSolutionProperty(void);
	virtual void serialize(XmlSerializer& s) const;
    virtual void deserialize(XmlDeserializer& s);
	void SetSolutionUID( misUID val );
	void Reset(void);
	bool GetSolutionSavingCompelet(void);
	virtual void SetSolutionSavingCompelet(bool _arg);
	void SetPatientProperties(misPatientProperties patientProperties);
	misPatientProperties GetPatientProperties() const;
	bool IsThereAnyPatient(void) const;
	misUID GetSolutionUID(void) const;
	void UpdateSolutionAdressInAplicationSetting(void);
	misUID GetUserUID() const { return m_UserUID; }
	void SetUserUID(misUID val) { m_UserUID = val; }
	misDateTime GetDateTimeOfCreation() const;
	void SetDateTimeOfCreation(misDateTime val);
	misDateTime GetDateTimeOfLastModification() const;
	void SetDateTimeOfLastModification(misDateTime val);
	std::string GetLastSelectedTabName() const;
	void SetLastSelectedTabName(std::string val);
	bool GetIsViewable() const;
	void SetIsViewable(bool val);
	std::string GetLastSelectedSubTabName() const;
	void SetLastSelectedSubTabName(std::string val);
	std::string GetSolutionFolderName() const;
	void SetSolutionFolderName(std::string val );
	misUID GetRegisteredImageUID() const;
	void SetRegisteredImageUID(misUID val);
	misUID GetRegisteredReferenceUID() const;
	void SetRegisteredReferenceUID(misUID val);
	std::vector<std::shared_ptr<ISimpleDataPackage>> GetPackages() const override;

protected:

	bool                 m_IsThereAnyPatient;
	bool                 m_SolutionSavingCompelet;

private:
	misUID m_UserUID;
	misDateTime m_DateTimeOfCreation;
	misDateTime m_DateTimeOfLastModification;
	std::string m_SolutionFolderName;
	std::string m_LastSelectedTabName;
	std::string m_LastSelectedSubTabName;
	bool m_IsViewable;    
	misPatientProperties m_patientProperty;
	misUID m_SolutionUID;
	misUID m_RegisteredImageUID;
	misUID m_RegisteredReferenceUID;
	std::weak_ptr<parcast::IPackageRepo> m_PkgRepo;
};

