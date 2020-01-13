#pragma once

namespace parcast
{

	class ISolutionImportExport
	{
	public:
		virtual ~ISolutionImportExport() = default;
		virtual void Export(const std::string& path) const = 0;
		virtual void Import(const std::string& path) const = 0;
		virtual void SetAuxiliarySolutionFolder(std::string path) = 0;
	};

}