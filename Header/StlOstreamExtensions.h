#pragma once

template <typename T>
std::ostream& operator<< (std::ostream& str, const std::vector<T>& vec)
{
	str << "std::vector<" << typeid(T).name() << "> { ";
	for (int i = 0; i < vec.size() - 1; ++i)
		str << vec[i] << ", ";
	str << vec.back() << " }";
	return str;
}