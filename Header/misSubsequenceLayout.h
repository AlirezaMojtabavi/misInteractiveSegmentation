#pragma once

#include "..\misGUIModel\misGuiMdelMacroes.h"
#include "ISubsequenceLayout.h"
#include "misWindowModel.h"

class misSubsequenceLayout :public ISubsequenceLayout
{
public:
	misSubsequenceLayout();

	bool Active() const override;
	void Active(bool val) override;
	int GetActiveWindow() const override;
	void SetActiveWindow(int left) override;
	int GetFullScreenWindowID() const override;
	void SetullScreenWindowID(int left) override;
	int GetID() const override;
	void SetID(int left )override;
	std::string GetName() const override;
	void SetName(std::string left) override;
	void SetParentTabName(std::string parentTabName) override;
	std::string	get_m_ParentTabName() override;
	void* get_m_MainHandle() const  override;
	void set_m_MainHandle(void* left) override;
	void AddWindow(misWindowModel window) override;
	bool GetWindow(std::string name,misWindowModel& window) override;
	bool GetWindow(int id,  misWindowModel& window) override;
	int GetNumOfWindows()override;
	ListType GetchildWindows() override;
	misWindowModel m_pActiveWindow;

private:

	int m_ID;
	std::string m_Name;
	int  m_ActiveWindow;
	int  m_FullScreenWindowID;
	void* m_MainHandle;
	ListType  childWindows;
	std::string    m_ParentTabName;
	bool m_Active;
};
