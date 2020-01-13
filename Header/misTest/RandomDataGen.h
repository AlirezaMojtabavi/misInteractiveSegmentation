#pragma once

namespace parcast
{

	class RandomDataGen
	{
	public:
		static std::shared_ptr< std::vector<unsigned char> > GenByteArray(int size)
		{
			std::random_device randDev;
			std::uniform_int_distribution<int> dist(0, 0xFF);
			auto data = std::make_shared< std::vector<unsigned char> >(size);
			for (auto& byte : *data)
				byte = static_cast<unsigned char>(dist(randDev));
			return data;
		}

		template <typename T>
		static std::shared_ptr< std::vector<T> > GenDoubleArray(int size, T lowBound, T highBound)
		{
			auto data = std::make_shared< std::vector<T> >();
			data->reserve(size);

			for (int i = 0; i < size; ++i)
				data->push_back(GenReal(lowBound, highBound));

			return data;
		}

		template <typename T>
		static T GenInteger(T lowBound, T highBound)
		{
			std::random_device randDev;
			std::uniform_int_distribution<T> dist(lowBound, highBound);
			return dist(randDev);
		}

		template <typename T>
		static T GenReal(T lowBound, T highBound)
		{
			std::random_device randDev;
			std::uniform_real_distribution<T> dist(lowBound, highBound);
			return dist(randDev);
		}

		static bool GenBool()
		{
			return GenInteger(0, 1) ? true : false;
		}

		static std::string GenAlNum(int length, const std::string excludeChars = "")
		{
			std::random_device randDev;
			std::uniform_int_distribution<int> dist(static_cast<int>('0'), static_cast<int>('z'));
			std::stringstream genStr;
			int currentLength = 0;
			while (currentLength < length)
			{
				char ch = static_cast<char>(dist(randDev));
				if (excludeChars.find(ch) == excludeChars.npos && std::isalnum(ch))
				{
					currentLength++;
					genStr << ch;
				}
			}
			return genStr.str();
		}
	};

}