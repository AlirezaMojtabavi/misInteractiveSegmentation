#pragma once
class IVolumeDataDependency;

class misVolumeData3DViewer
{
public:
	misVolumeData3DViewer(std::shared_ptr<IVolumeDataDependency> volumeDep);
	~misVolumeData3DViewer();
	void ShowVolume();
private:
	std::shared_ptr<IVolumeDataDependency> m_VolumeDep;
};

