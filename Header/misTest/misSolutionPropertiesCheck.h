#pragma once

#include "DateTimeMatcher.h"
#include "misSolutionProperty.h"

class misSolutionPropertiesCheck
{
public:
	static bool CheckSolution(const misSolutionProperty& a, const misSolutionProperty& b, bool checkDateTimeOfLastModification = true)
	{
		using namespace parcast;
		auto result = true;
		result = result && (a.GetUserUID() == b.GetUserUID());
		result = result && (DateTimeMatcher::IsEqual(
			DateTime(a.GetDateTimeOfCreation()), DateTime(b.GetDateTimeOfCreation())));
		if(checkDateTimeOfLastModification)
			result = result && (DateTimeMatcher::IsEqual(
				DateTime(a.GetDateTimeOfLastModification()), DateTime(b.GetDateTimeOfLastModification())));
		result = result && (a.GetSolutionFolderName() == b.GetSolutionFolderName());
		result = result && (a.GetLastSelectedTabName() == b.GetLastSelectedTabName());
		result = result && (a.GetLastSelectedSubTabName() == b.GetLastSelectedSubTabName());
		result = result && (a.GetIsViewable() == b.GetIsViewable());
		result = result && (a.GetSolutionUID() == b.GetSolutionUID());
		result = result && (a.GetRegisteredImageUID() == b.GetRegisteredImageUID());
		result = result && (a.GetRegisteredReferenceUID() == b.GetRegisteredReferenceUID());
		result = result && CheckPatient(a.GetPatientProperties(), b.GetPatientProperties());
		return result;
	}

	static bool CheckPatient(const misPatientProperties& patA, const misPatientProperties& patB)
	{
		auto result = true;
		result = result && (patA.PatientUID == patB.PatientUID);
		result = result && (patA.GetBirthDate() == patB.GetBirthDate());
		result = result && (patA.FamilyName == patB.FamilyName);
		result = result && (patA.Gender == patB.Gender);
		result = result && (patA.FirstName == patB.FirstName);
		result = result && (patA.Position == patB.Position);
		result = result && (patA.Weight == patB.Weight);
		result = result && (patA.ReadyForSurgery == patB.ReadyForSurgery);
		result = result && (patA.GetAge() == patB.GetAge());
		return result;
	}

	static bool CheckDirectoryContent(const boost::filesystem::path &targetDirectory, const boost::filesystem::path &compareDirectory)
	{
		try
		{
			boost::filesystem::recursive_directory_iterator targetDirItr(targetDirectory);
			for (const auto &dirElementA : targetDirItr)
			{
				auto rel = relative(dirElementA.path(), targetDirectory);
				auto compareDirPath = compareDirectory / rel;
				if (!exists(compareDirPath))
					return false;

				if (is_directory(dirElementA))
					continue;

				auto dirAPath = dirElementA.path().string();
				auto dirBPath = compareDirPath.string();
				std::ifstream f1(dirAPath, std::ifstream::binary | std::ifstream::ate);
				std::ifstream f2(dirBPath, std::ifstream::binary | std::ifstream::ate);

				if (f1.fail() || f2.fail())
					return false;

				if (f1.tellg() != f2.tellg())
					return false;

				f1.seekg(0, std::ifstream::beg);
				f2.seekg(0, std::ifstream::beg);

				if (!std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
					std::istreambuf_iterator<char>(),
					std::istreambuf_iterator<char>(f2.rdbuf())))
					return false;

			}

		}
		catch (const boost::filesystem::filesystem_error& e) 
		{
			std::cout << e.what() << '\n';
			return false;
		}
		return true;
	}
};
