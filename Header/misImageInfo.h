#ifndef misImageInfo_H
#define misImageInfo_H

class misImageInfo
{
private:
	std::vector <std::string> m_FileName;
	std::vector <std::string> m_SliceNo;
	std::vector <std::string> m_SliceLocation;
public:
	void setm_FileName(std::vector <std::string> value){m_FileName=value;}
	std::vector <std::string> getm_FileName(){ return m_FileName;}
	void setm_SliceNo(std::vector <std::string> value){m_SliceNo=value;}
	std::vector <std::string> getm_SliceNo(){ return m_SliceNo;}
	void setm_SliceLocation(std::vector <std::string> value){m_SliceLocation=value;}
	std::vector <std::string> getm_SliceLocation(){ return m_SliceLocation;}
};

#endif