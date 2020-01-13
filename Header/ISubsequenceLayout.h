#pragma once
#include "misWindowModel.h"
class ISubsequenceLayout
{
public:
	typedef std::list<misWindowModel>  ListType;
	virtual bool Active() const = 0;
	virtual void Active(bool val) = 0;
	virtual int GetActiveWindow() const = 0;
	virtual void SetActiveWindow(int left) = 0;
	virtual int GetFullScreenWindowID() const = 0;
	virtual void SetullScreenWindowID(int left) = 0;
	virtual int GetID() const = 0;
	virtual void SetID(int left) = 0;
	virtual std::string GetName() const = 0;
	virtual void SetName(std::string left) = 0;
	virtual void	SetParentTabName(std::string parentTabName) = 0;
	virtual std::string	get_m_ParentTabName() = 0;
	virtual void* get_m_MainHandle() const = 0;
	virtual void set_m_MainHandle(void* left) = 0;
	virtual void AddWindow(misWindowModel window) = 0;
	virtual bool GetWindow(std::string name, misWindowModel& window) = 0;
	virtual bool GetWindow(int id, misWindowModel& window) = 0;
	virtual int GetNumOfWindows() = 0;
	virtual ListType GetchildWindows() = 0;
};