#pragma once

#include "DateTimeMatcher.h"
#include "misSolutionProperty.h"

class misSolutionPropertiesBoostChecks
{
public:
	static void CheckSolution(const misSolutionProperty& a, const misSolutionProperty& b, bool checkDateTimeOfLastModification = true)
	{
		using namespace parcast;
		BOOST_CHECK_EQUAL(a.GetUserUID(), b.GetUserUID());

		BOOST_CHECK(DateTimeMatcher::IsEqual(
			DateTime(a.GetDateTimeOfCreation()), DateTime(b.GetDateTimeOfCreation())));

		if(checkDateTimeOfLastModification)
		{
			BOOST_CHECK(DateTimeMatcher::IsEqual(
				DateTime(a.GetDateTimeOfLastModification()), DateTime(b.GetDateTimeOfLastModification())));
		}

		BOOST_CHECK_EQUAL(a.GetSolutionFolderName(), b.GetSolutionFolderName());
		BOOST_CHECK_EQUAL(a.GetLastSelectedTabName(), b.GetLastSelectedTabName());
		BOOST_CHECK_EQUAL(a.GetLastSelectedSubTabName(), b.GetLastSelectedSubTabName());
		BOOST_CHECK_EQUAL(a.GetIsViewable(), b.GetIsViewable());
		BOOST_CHECK_EQUAL(a.GetSolutionUID(), b.GetSolutionUID());
		BOOST_CHECK_EQUAL(a.GetRegisteredImageUID(), b.GetRegisteredImageUID());
		BOOST_CHECK_EQUAL(a.GetRegisteredReferenceUID(), b.GetRegisteredReferenceUID());
		CheckPatient(a.GetPatientProperties(), b.GetPatientProperties());
	}

	static void CheckPatient(const misPatientProperties& patA, const misPatientProperties& patB)
	{
		BOOST_CHECK_EQUAL(patA.PatientUID, patB.PatientUID);
		BOOST_CHECK_EQUAL(patA.GetBirthDate(), patB.GetBirthDate());
		BOOST_CHECK_EQUAL(patA.FamilyName, patB.FamilyName);
		BOOST_CHECK_EQUAL(patA.Gender, patB.Gender);
		BOOST_CHECK_EQUAL(patA.FirstName, patB.FirstName);
		BOOST_CHECK_EQUAL(patA.Position, patB.Position);
		BOOST_CHECK_EQUAL(patA.Weight, patB.Weight);
		BOOST_CHECK_EQUAL(patA.ReadyForSurgery, patB.ReadyForSurgery);
		BOOST_CHECK_EQUAL(patA.GetAge(), patB.GetAge());
	}
};