#pragma once

#include "RandomDataGen.h"
#include "boost/algorithm/string.hpp"

namespace parcast
{

	class RandomDirTreeGenerator
	{
	public:
		static void CreateFiles(int levels, const std::string& basePath, std::size_t maxFileSize,
			std::vector< std::pair<std::string, bool> >& outDirList)
		{
			using rand = parcast::RandomDataGen;

			if (levels == 0)
				return;

			auto numFiles = rand::GenInteger(0, 8), numDirs = rand::GenInteger(2, 8);

			auto base = basePath;
			if (!base.empty())
				base.append("/");

			for (int i = 0 ; i < numFiles; )
			{
				const auto fileName = rand::GenAlNum(rand::GenInteger(1, 20));
				if (NameIsReseved(fileName))
					continue;

				auto filePath = base + fileName  + "." + rand::GenAlNum(rand::GenInteger(3, 4));
				const auto length = rand::GenInteger(std::size_t(), maxFileSize);
				const auto data = rand::GenByteArray(length);
				std::ofstream file(filePath, std::ios::out | std::ios::binary);
				for (auto byte : *data)
					file << byte;
				outDirList.push_back(std::make_pair(filePath, false));

				i++;
			}

			for (auto i = 0; i < numDirs;)
			{
				const auto dirName = rand::GenAlNum(rand::GenInteger(1, 20));
				if (NameIsReseved(dirName))
					continue;

				auto dirNamePath = base + dirName;

				boost::filesystem::create_directory(dirNamePath);
				outDirList.push_back(std::make_pair(dirNamePath, true));
				CreateFiles(levels - 1, dirNamePath, maxFileSize, outDirList);
				++i;
			}
		}
	private:
		static bool NameIsReseved(const std::string& fileName)
		{
			const auto find = [&fileName](const std::string& str)
			{
				return boost::to_upper_copy(fileName) == str;
			};
			const std::array<std::string, 22> reservedNames =
			{ "CON", "PRN", "AUX", "NUL", "COM1", "COM2", "COM3", "COM4", "COM5", "COM6", "COM7", "COM8",
				"COM9", "LPT1", "LPT2", "LPT3", "LPT4", "LPT5", "LPT6", "LPT7", "LPT8", "LPT9" };
			return std::any_of(reservedNames.cbegin(), reservedNames.cend(), find);
		}
	};

}