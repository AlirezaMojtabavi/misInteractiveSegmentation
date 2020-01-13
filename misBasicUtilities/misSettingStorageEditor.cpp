#include "StdAfx.h"
#include "misSettingStorageEditor.h"

misSettingStorageEditor::misSettingStorageEditor(std::shared_ptr<ISettingsContainer> preferences)
	: m_SettingsContainer(preferences), m_RootNodePath("ParsissData/UserPreferences")
{
}

void misSettingStorageEditor::LoadFromFile( const std::string& preferencesFilePath )
{
	if (m_XmlDoc.LoadFile(preferencesFilePath.c_str()) != tinyxml2::XML_SUCCESS)
		throw std::exception(
		("Failed to load user preferences XML file. File corrupt or not found: " + preferencesFilePath).c_str());

	auto rootNode = GetOrCreateChildElements(&m_XmlDoc, m_RootNodePath);
	LoadPreferenceItemsUnderNode(rootNode, "");
}


void misSettingStorageEditor::SaveToFile( const std::string& preferencesFilePath )
{
	if (!m_XmlDoc.FirstChild() || !m_XmlDoc.FirstChild()->ToDeclaration())
		m_XmlDoc.InsertFirstChild(m_XmlDoc.NewDeclaration());

	auto rootNode = GetOrCreateChildElements(&m_XmlDoc, m_RootNodePath);

	auto setPrefs = m_SettingsContainer->GetAllSettings();
	for (auto paramNameItr = setPrefs.cbegin(); paramNameItr != setPrefs.cend(); ++paramNameItr)
	{
		auto paramName = *paramNameItr;
		auto paramNode = GetOrCreateChildElements(rootNode, paramName);

		if (m_SettingsContainer->IsParamSet(paramName))
		{
			switch (m_SettingsContainer->GetParamType(paramName))
			{
			case ISettingsContainer::PT_BOOLEAN:
				paramNode->SetAttribute("value", (m_SettingsContainer->GetBoolean(paramName)) ? "true" : "false");
				paramNode->SetAttribute("type", "Boolean");
				break;
			case ISettingsContainer::PT_INTEGER:
				paramNode->SetAttribute("value", m_SettingsContainer->GetInteger(paramName));
				paramNode->SetAttribute("type", "Integer");
				break;
			case ISettingsContainer::PT_DOUBLE:
				paramNode->SetAttribute("value", m_SettingsContainer->GetDouble(paramName));
				paramNode->SetAttribute("type", "Double");
				break;
			case ISettingsContainer::PT_STRING:
				paramNode->SetAttribute("value", m_SettingsContainer->GetString(paramName).c_str());
				paramNode->SetAttribute("type", "String");
				break;
			case ISettingsContainer::PT_STRING_LIST:
				{
					paramNode->DeleteChildren();
					auto stringList = m_SettingsContainer->GetStringList(paramName);
					for (auto stringItem = stringList.cbegin(); stringItem != stringList.cend(); ++stringItem)
					{
						auto stringItemNode = m_XmlDoc.NewElement("item");
						paramNode->InsertEndChild(stringItemNode);
						stringItemNode->SetAttribute("value", stringItem->c_str());
					}
					paramNode->SetAttribute("type", "StringList");
				}
				break;
			}
		}

		auto description = m_SettingsContainer->GetParamDescription(paramName);
		if (!description.empty())
			paramNode->SetAttribute("description", description.c_str());

		auto hrname = m_SettingsContainer->GetParamHumanReadableName(paramName);
		if (!hrname.empty())
			paramNode->SetAttribute("hrname", hrname.c_str());

		auto popularity = m_SettingsContainer->GetParamPopularity(paramName);
		if (!popularity == ISettingsContainer::PL_NOT_SET)
			paramNode->SetAttribute("popularity", popularity);

		auto valueRange = m_SettingsContainer->GetValueRange(paramName);
		if (!valueRange.empty())
		{
			auto valueRangeNode = GetOrCreateChildElements(paramNode, "ValueRange");
			valueRangeNode->DeleteChildren();
			for (auto valueRangeItem = valueRange.cbegin(); valueRangeItem != valueRange.cend(); ++valueRangeItem)
			{
				auto valueRangeItemNode = m_XmlDoc.NewElement("item");
				valueRangeNode->InsertEndChild(valueRangeItemNode);
				valueRangeItemNode->SetAttribute("value", valueRangeItem->c_str());
			}
		}

	}

	if (m_XmlDoc.SaveFile(preferencesFilePath.c_str()) != tinyxml2::XML_SUCCESS)
		throw std::exception(
		("Failed to save user preferences XML file. Disk full or write protected. -> " + preferencesFilePath).c_str());
}

std::shared_ptr<ISettingsContainer> misSettingStorageEditor::GetPreferences() const 
{
	return m_SettingsContainer;
}

tinyxml2::XMLElement* misSettingStorageEditor::GetOrCreateChildElements(tinyxml2::XMLNode* parentNode, const std::string& nodeName)
{
	std::stringstream strStream(nodeName);
	std::string category;
	while (std::getline(strStream, category, '/'))
	{
		auto node = parentNode->FirstChildElement(category.c_str());
		if (!node)
		{
			node = m_XmlDoc.NewElement(category.c_str());
			parentNode->InsertEndChild(node);
		}
		parentNode = node;
	}
	return parentNode->ToElement();
}

void misSettingStorageEditor::LoadPreferenceItemsUnderNode( tinyxml2::XMLNode* parentNode, const std::string& categoryPrefix )
{
	std::string catPref(categoryPrefix);
	if (!catPref.empty() && catPref.back() != '/')
		catPref.append("/");

	auto paramNode = parentNode->FirstChildElement();
	while (paramNode)
	{
		std::string paramName = catPref + paramNode->Name();

		auto valueTypeCstr = paramNode->Attribute("type");
		std::string valueType = valueTypeCstr ? valueTypeCstr : "Category";

		if (valueType == "Boolean")
		{
			 auto valueStr = std::string(paramNode->Attribute("value"));
				m_SettingsContainer->SetBoolean(paramName, (valueStr == "true")?true : false);
		}
		else if (valueType == "Integer")
		{
			int value;
			if (paramNode->QueryIntAttribute("value", &value) == tinyxml2::XML_SUCCESS)
				m_SettingsContainer->SetInteger(paramName, value);
		}
		else if (valueType == "Double")
		{
			double value;
			if (paramNode->QueryDoubleAttribute("value", &value) == tinyxml2::XML_SUCCESS)
				m_SettingsContainer->SetDouble(paramName, value);
		}
		else if (valueType == "String")
		{
			auto value = paramNode->Attribute("value");
			if (value)
				m_SettingsContainer->SetString(paramName, value);
		}
		else if (valueType == "StringList")
		{
			ISettingsContainer::StringList stringList;
			auto stringItemNode = paramNode->FirstChildElement("item");
			while (stringItemNode)
			{
				auto stringItem = stringItemNode->Attribute("value");
				if (stringItem)
					stringList.push_back(stringItem);
				stringItemNode = stringItemNode->NextSiblingElement("item");
			}
			m_SettingsContainer->SetStringList(paramName, stringList);
		}
		else // if (valueType == "Category")
		{
			LoadPreferenceItemsUnderNode(paramNode, paramName);
		}

		auto description = paramNode->Attribute("description");
		if (description)
			m_SettingsContainer->SetParamDescription(paramName, description);

		auto hrname = paramNode->Attribute("hrname");
		if (hrname)
			m_SettingsContainer->SetParamHumanReadableName(paramName, hrname);

		int popularity;
		if (paramNode->QueryIntAttribute("popularity", &popularity) == tinyxml2::XML_SUCCESS)
			m_SettingsContainer->SetParamPopularity(paramName, static_cast<ISettingsContainer::PopularityLevel>(popularity));

		auto valueRangeNode = paramNode->FirstChildElement("ValueRange");
		if (valueRangeNode)
		{
			ISettingsContainer::StringList valueRange;
			auto valueRangeItemNode = valueRangeNode->FirstChildElement("item");
			while (valueRangeItemNode)
			{
				auto stringItem = valueRangeItemNode->Attribute("value");
				if (stringItem)
					valueRange.push_back(stringItem);
				valueRangeItemNode = valueRangeItemNode->NextSiblingElement("item");
			}
			m_SettingsContainer->SetValueRange(paramName, valueRange);
		}

		paramNode = paramNode->NextSiblingElement();
	}
}

void misSettingStorageEditor::SetRootNodePath( const std::string& path )
{
	m_RootNodePath = path;
}