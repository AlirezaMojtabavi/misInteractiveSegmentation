#include "StdAfx.h"
#include "misWindowModel.h"

using std::string;

misWindowModel::misWindowModel(void)
{
	m_Name="none";
}
void* misWindowModel::GetHandle() const
{
	return m_Handle;
}
void misWindowModel::SetHandle(void* left)
{
	m_Handle = left;
}
string misWindowModel::GetName() const
{
	return m_Name;
}
void misWindowModel::SetName(string left)
{
	m_Name = left;
}

int misWindowModel::GetWindowIndex() const
{
	return m_WindowIndex;
}

void misWindowModel::SetWindowIndex( int val )
{
	m_WindowIndex = val;
}

std::string misWindowModel::GetParentSubSequenceName() const
{
	return m_ParentSubSequenceName;
}

void misWindowModel::SetParentSubSequenceName( std::string val )
{
	m_ParentSubSequenceName = val;
}

std::string misWindowModel::GetParentSequenceName() const
{
	return m_ParentSequenceName;
}

void misWindowModel::SetParentSequenceName( std::string val )
{
	m_ParentSequenceName = val;
}

bool misWindowModel::GetActive() const
{
	return active;
}

void misWindowModel::SetActive( bool val )
{
	active = val;
}

int misWindowModel::GetToolbarHeight() const
{
	return toolbarHeight;
}

void misWindowModel::SetToolbarHeight( int val )
{
	toolbarHeight = val;
}

