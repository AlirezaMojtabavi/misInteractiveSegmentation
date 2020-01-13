#pragma once

#include "IUserDescription.h"
#include "IUserRegistryEditor.h"

class misUserRegistryEditor : public IUserRegistryEditor
{
public:
	class Injector
	{
	public:
		virtual std::shared_ptr<IUserDescription> CreateUserDescription(
			const std::string& userId, const std::string& profileDirPath) const;
	};

	misUserRegistryEditor(std::shared_ptr<Injector> injector = std::shared_ptr<Injector>());

	virtual void LoadFromFile(const std::string& registryFilePath) override;
	virtual UserCollectionType GetUsers() const override;

private:
	// Gets the first child element of the specified element with the specified tag name. An exception is thrown if the 
	// child element does not exist.
	tinyxml2::XMLElement* GetChildElement(tinyxml2::XMLNode* parent, const std::string &childName);

	std::shared_ptr<Injector> m_Injector;

	UserCollectionType m_Users;

	// The XMLDocument object is the owner of all XMLElement pointers. Therefore, validity of m_UsersNode relies on it.
	tinyxml2::XMLDocument m_XmlDoc;

	// The XMLElement representing the <ParsissData> / <Users> element in the loaded XML file.
	tinyxml2::XMLElement* m_UsersNode;
};

