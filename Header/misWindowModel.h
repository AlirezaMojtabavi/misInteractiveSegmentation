#pragma once

class misWindowModel
{
public:

	misWindowModel();
	void SetHandle(void* left);
	void* GetHandle() const;
	std::string GetName() const;
	void SetName(std::string left);
	int GetWindowIndex() const;
	void SetWindowIndex(int val);
	std::string GetStyle() const { return style; }
	void SetStyle(std::string val) { style = val; }
	std::string GetParentSubSequenceName() const;
	void SetParentSubSequenceName(std::string val);
	std::string GetParentSequenceName() const;
	void SetParentSequenceName(std::string val);
	bool GetActive() const;
	void SetActive(bool val);
	int GetToolbarHeight() const;
	void SetToolbarHeight(int val);

private:
	void* m_Handle;
	int m_WindowIndex;
	std::string m_Name;
	std::string style;
	std::string m_ParentSubSequenceName;
	std::string m_ParentSequenceName;
	bool active;
	int toolbarHeight;
};