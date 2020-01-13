/**********************************************************************
 *                                                                    *
 * Voreen - The Volume Rendering Engine                               *
 *                                                                    *
 * Copyright (C) 2005-2010 The Voreen Team. <http://www.voreen.org>   *
 *                                                                    *
 * This file is part of the Voreen software package. Voreen is free   *
 * software: you can redistribute it and/or modify it under the terms *
 * of the GNU General Public License version 2 as published by the    *
 * Free Software Foundation.                                          *
 *                                                                    *
 * Voreen is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of     *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the       *
 * GNU General Public License for more details.                       *
 *                                                                    *
 * You should have received a copy of the GNU General Public License  *
 * in the file "LICENSE.txt" along with this program.                 *
 * If not, see <http://www.gnu.org/licenses/>.                        *
 *                                                                    *
 * The authors reserve all rights not expressly granted herein. For   *
 * non-commercial academic use see the license exception specified in *
 * the file "LICENSE-academic.txt". To get information about          *
 * commercial licensing please contact the authors.                   *
 *                                                                    *
 **********************************************************************/


#ifndef VRN_XMLSERIALIZER_H
#define VRN_XMLSERIALIZER_H

#include "serializable.h"
#include "serializablefactory.h"
#include "serializationexceptions.h"
#include "xmlserializationconstants.h"
#include "xmlserializerbase.h"

#pragma warning( push )
#pragma warning( disable : 4290 )

// forward declaration
struct PlotSelectionEntry;

/**
 * @c XmlSerializer is responsible for serializing memory data to XML documents.
 *
 * @par
 * The implementation is capable of serializing simple C++ data types, user defined classes
 * which are derived from @c Serializable, and most STL containers containing just the previously
 * mentioned data.
 *
 * @par
 * Furthermore, cycles, joints and polymorphic @c Serializable derivatives are supported which
 * makes the @c XmlSerializer quite flexible. The serialization process is independent
 * of serialization order due to the use of @c key/data pairs, provided that different
 * keys are used at each hierarchy level.
 *
 * @par
 * Finally, the XML document can be written to an arbitrary @c std::ostream. For instance, this
 * allows you to write the XML document into a @c std::stringstream for further processing.
 *
 * @par
 * You have to use @c XmlDeserializer, which is the counterpart to @c XmlSerializer, for
 * deserializing XML documents to memory data.
 *
 * @par
 * Here is a short example of using the @c XmlSerializer:
 * @code
 * int i = 1;
 *
 * std::fstream f;
 * f.open("file.xml", std::ios::out);
 *
 * XmlSerializer s;
 * s.serialize("i", i);
 * s.write(f);
 *
 * f.close();
 * @endcode
 * For more complex examples and interaction with other classes of the serialization framework
 * see the &quot;serializertest&quot; application in &quot;apps/&quot; directory.
 *
 * @attention All memory data must be serialized before the XML document can be written.
 *            Otherwise, it cannot be ensured that all pointer references are correctly resolved.
 *
 * @note For further information on handling cycles, joints and polymorphism, see:
 *       http://www.parashift.com/c++-faq-lite/serialization.html
 *
 * @see XmlDeserializer
 * @see XmlSerializerBase
 * @see Serializable
 */
class   XmlSerializer : public XmlSerializerBase
{
public:
	/**
	 * Constructor which initializes the XML document.
	 *
	 * @par
	 * Initialization of the XML document means creating XML declaration and root node
	 * as well as adding them to the XML document.
	 *
	 * @param documentPath Absolute path to the XML file the document will be written to. This information
	 *     is not used by the serializer itself and is therefore not required, but is intended
	 *     to be accessible by serializing objects for absolute-to-relative path conversions.
	 */
	XmlSerializer(std::string documentPath = "");

	/**
	 * Default destructor.
	 */
	~XmlSerializer();

	/**
	 * Returns the absolute path to the XML file the document will be written to.
	 */
	std::string getDocumentPath() const;

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const bool& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const char& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const signed char& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const unsigned char& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const signed short& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const unsigned short& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const signed int& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const unsigned int& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const signed long& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const unsigned long& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 *
	 * @note: This overload was added by m.i.soboute
	 */
	void serialize(const std::string& key, const long long& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const float& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const double& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const long double& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void serialize(const std::string& key, const std::string& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::vec2& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::vec3& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::vec4& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::dvec2& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::dvec3& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::dvec4& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::ivec2& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::ivec3& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::ivec4& data)
		throw (SerializationException);

	void serialize(const std::string& key, const tgt::Vector3ui& data) 
			throw (SerializationException);
	
	void serialize(const std::string& key, const tgt::bvec3& data) 
			throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::col3& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::col4& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::mat2& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::mat3& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::mat4& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::Matrix2d& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::Matrix3d& data)
		throw (SerializationException);

	/**
	 * Serializes the given @c key/data pair.
	 *
	 * @param key the XML node key
	 * @param data the data
	 */
	void serialize(const std::string& key, const tgt::Matrix4d& data)
		throw (SerializationException);
	 
	
	/**
	 * Serializes the given @c Serializable interface realization.
	 *
	 * @note All user defined classes must realize the @c Serializable
	 *       interface to be serializable.
	 *
	 * @param key the XML node key
	 * @param data the @c Serializable realization
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if @c serialize method of given @c Serializable raises this exception
	 */
	void serialize(const std::string& key, const Serializable& data)
		throw (SerializationException);

	
	/**
	 * Serializes the given @c Serializable interface realization.
	 *
	 * @note All user defined classes must realize the @c Serializable
	 *       interface to be serializable.
	 *
	 * @param key the XML node key
	 * @param data the @c Serializable realization
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if @c serialize method of given @c Serializable raises this exception
	 */
	template<class T>
	void serialize(const std::string& key, const T* const& data)
		throw (SerializationException);

	/**
	 * Serializes the given std::pair.
	 *
	 * @tparam S data type of first pair item
	 * @tparam T data type of second pair item
	 *
	 * @param key the XML node key
	 * @param data the pair to serialize
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if serialization of pair items raises this exception
	 */
	template<class S, class T>
	void serialize(const std::string& key, const std::pair<S, T>& data)
		throw (SerializationException);

	/**
	 * Serializes the given data vector.
	 *
	 * @par
	 * Iterates over the given data collection and serialize each collection item.
	 *
	 * @note Element order of collection items remains constant during
	 *       serialization and deserialization.
	 *
	 * @tparam T data type of vector items
	 *
	 * @param key the XML node key
	 * @param data the data vector
	 * @param itemKey XML node key for each XML child node
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if serialization of collection items raises this exception
	 */
	template<class T>
	void serialize(const std::string& key, const std::vector<T>& data, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
		throw (SerializationException);

	/**
	 * Serializes the given data deque.
	 *
	 * @par
	 * Iterates over the given data collection and serialize each collection item.
	 *
	 * @note Element order of collection items remains constant during
	 *       serialization and deserialization.
	 *
	 * @tparam T data type of vector items
	 *
	 * @param key the XML node key
	 * @param data the data vector
	 * @param itemKey XML node key for each XML child node
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if serialization of collection items raises this exception
	 */
	template<class T>
	void serialize(const std::string& key, const std::deque<T>& data, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
		throw (SerializationException);

	/**
	 * Serializes the given data list.
	 *
	 * @par
	 * Iterates over the given data collection and serialize each collection item.
	 *
	 * @note Element order of collection items remains constant during
	 *       serialization and deserialization.
	 *
	 * @tparam T data type of vector items
	 *
	 * @param key the XML node key
	 * @param data the data vector
	 * @param itemKey XML node key for each XML child node
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if serialization of collection items raises this exception
	 */
	template<class T>
	void serialize(const std::string& key, const std::list<T>& data, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
		throw (SerializationException);

	/**
	 * Serializes the given data set.
	 *
	 * @par
	 * Iterates over the given data collection and serialize each collection item.
	 *
	 * @note Element order of set items are not guaranteed to remains constant
	 *       during serialization and deserialization due to limits of
	 *       some STL containers like @c std::set.
	 *
	 * @tparam T data type of set items
	 * @tparam C comparison class @see std::set
	 *
	 * @param key the XML node key
	 * @param data the data set
	 * @param itemKey XML node key for each XML child node
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if serialization of collection items raises this exception
	 * @throws XmlSerializationInvalidOperationException
	 *     if pointer content serialization is enabled,
	 *     because of possible hash problems on deserialization
	 */
	template<class T, class C>
	void serialize(const std::string& key, const std::set<T, C>& data, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
		throw (SerializationException);

	/**
	 * Serializes the given data stack.
	 *
	 * @par
	 * Iterates over the given data collection and serialize each collection item.
	 *
	 * @tparam T data type of stack items
	 *
	 * @param key the XML node key
	 * @param data the data set
	 * @param itemKey XML node key for each XML child node
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if serialization of collection items raises this exception
	 * @throws XmlSerializationInvalidOperationException
	 *     if pointer content serialization is enabled,
	 *     because of possible hash problems on deserialization
	 */
	template<class T>
	void serialize(const std::string& key, const std::stack<T>& data)
		throw (SerializationException);

	/**
	 * Serializes the given data map.
	 *
	 * @par
	 * Iterates over the given map and serialize each @c key/value pair item of the map.
	 *
	 * @note Element order of map items are not guaranteed to remains constant
	 *       during serialization and deserialization due to limits of
	 *       some STL containers like @c std::map.
	 *
	 * @tparam T data type of map keys
	 * @tparam U data type of map values
	 * @tparam C comparison class @see std::map
	 *
	 * @param key the XML node key
	 * @param data the data map
	 * @param valueKey XML node key for each value node
	 * @param keyKey key for each XML key node or attribute
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if serialization of the @c key/value pair item raises this exception
	 */
	template<class T, class U, class C>
	void serialize(
		const std::string& key,
		const std::map<T, U, C>& data,
		const std::string& valueKey = XmlSerializationConstantsGetInstance()->VALUENODE,
		const std::string& keyKey = XmlSerializationConstantsGetInstance()->KEYNODE)
		throw (SerializationException);
	/**
	 * Writes the XML document that contains all already serialized data to the given stream.
	 *
	 * @attention Keep in mind that all memory data must be serialized before the XML document
	 *            can be written. Otherwise, it cannot be ensured that all pointer references
	 *            are resolved.
	 *
	 * @param stream the output stream
	 */
	void write(std::ostream& stream);

protected:
	/**
	 * Category for logging.
	 */
	static const std::string loggerCat_;

private:
	/**
	 * Adds given @c data/node pair to the XML node look up map.
	 *
	 * @param data data address
	 * @param node the XML node
	 */
	inline void addDataNode(const void* data, TiXmlElement* node);

	/**
	 * Adds given unresolved reference to the unresolved reference vector.
	 *
	 * @tparam T type of referenced data
	 *
	 * @param unresolvedReferenceNode XML node of the unresolved reference
	 * @param reference the unresolved reference
	 */
	template<class T>
	inline void addUnresolvedReference(TiXmlElement* unresolvedReferenceNode, const T* const& reference);

	/**
	 * Checks if the given XML attribute key is not a reserved key and unique.
	 *
	 * @param key the XML attrubte key
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	void checkAttributeKey(const std::string& key)
		throw (SerializationException);

	/**
	 * Makes the XML attribute key of the given @c element the first XML attribute.
	 *
	 * @param key key of XML attribute to move
	 * @param element the @c element
	 */
	void moveAttributeToFront(const std::string& key, TiXmlElement* element);

	/**
	 * Resolves unresolved references during @c write method.
	 */
	void resolveUnresolvedReferences();

	/**
	 * Helper function for serializing @c key/data pairs with simple data types.
	 *
	 * @tparam T data type
	 *
	 * @param key the XML node key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	template<class T>
	inline void serializeSimpleTypes(const std::string& key, const T& data)
		throw (SerializationException);

	/**
	 * Helper function for serializing @c key/data pairs with tgt vectors.
	 *
	 * @tparam T data type of vector
	 *
	 * @param key the XML node key
	 * @param vector the tgt vector
	 * @param isColor flag determine if given vector is a color
	 */
	template<class T>
	inline void serializeTgtVector(const std::string& key, const T& vector, const bool& isColor = false)
		throw (SerializationException);

	/**
	 * Helper function creates a XML node with the given @c nodeKey and
	 * serializes the given @c key/data pair as an attribute.
	 *
	 * @tparam T data type
	 *
	 * @param nodeKey the XML node key
	 * @param key the XML attribute key
	 * @param data the data
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if primitive data is serialized as XML attributes and key is reserved or not unique
	 */
	template<class T>
	inline void serializeAttributeInNode(const std::string& nodeKey, const std::string& key, const T& data)
		throw (SerializationException);

	/**
	 * Helper function for serializing data collections like STL container.
	 *
	 * @note Element order of collection items remains constant during
	 *       serialization and deserialization.
	 *
	 * @tparam T data type of collection
	 *
	 * @param key the XML node key
	 * @param collection the data collection
	 * @param itemKey XML node key for each XML child node
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if serialization of collection items raises this exception
	 */
	template<class T>
	inline void serializeCollection(const std::string& key, const T& collection, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
		throw (SerializationException);

	/**
	 * Helper function for serializing data maps like STL maps.
	 *
	 * @note Element order of map items are not guaranteed to remains constant
	 *       during serialization and deserialization due to limits of
	 *       some STL containers like @c std::map.
	 *
	 * @tparam T data type of map
	 *
	 * @param key the XML node key
	 * @param map the map
	 * @param valueKey XML node key for each value node
	 * @param keyKey key for each XML key node or attribute
	 *
	 * @throws XmlSerializationAttributeNamingException
	 *     if serialization of @c key/value pair items raises the exception
	 */
	template<class T>
	inline void serializeMap(
		const std::string& key,
		const T& map,
		const std::string& valueKey = XmlSerializationConstantsGetInstance()->VALUENODE,
		const std::string& keyKey = XmlSerializationConstantsGetInstance()->KEYNODE)
		throw (SerializationException);

	/**
	 * Type definition for XML node look up map.
	 */
	typedef std::map<void*, TiXmlElement*> DataNodeMapType;

	/**
	 * Map for looking up XML nodes by pointer address.
	 */
	DataNodeMapType dataNodeMap_;

	/**
	 * The @c IReferenceContentSerializer interface allows to treat every
	 * @c ReferenceContentSerializer template specialization in the same way.
	 *
	 * @see ReferenceContentSerializer
	 * @see UnresolvedReference
	 */
	class IReferenceContentSerializer {
	public:

		virtual ~IReferenceContentSerializer() {}

		/**
		 * Serializes the content of a reference.
		 *
		 * @param key the XML node key
		 *
		 * @returns serialized content
		 */
		virtual TiXmlElement* serialize(const std::string& key) const = 0;
	};

	template<class T> class ReferenceContentSerializer;
	template<class T> friend class ReferenceContentSerializer;
	/**
	 * @c ReferenceContentSerializer is a concrete implementation for serializing
	 * the content of pointer references.
	 *
	 * @note Serialization of pointer reference content is just necessary when
	 *       the pointer data is not serialized, i.e. it is created using @c new.
	 *
	 * @tparam type of referenced data
	 *
	 * @see IReferenceContentSerializer
	 * @see UnresolvedReference
	 */
	template<class T>
	class ReferenceContentSerializer : public IReferenceContentSerializer {
	public:
		/**
		 * Constructs a @c ReferenceContentSerializer in accordance to the given parameters.
		 *
		 * @param serializer Serializer to use for content serialization
		 * @param reference the unresolved reference
		 */
		ReferenceContentSerializer(XmlSerializer* serializer, const T* const& reference);

		/**
		 * @see IReferenceContentSerializer::serialize
		 */
		virtual TiXmlElement* serialize(const std::string& key) const;

	private:
		/**
		 * Serializer to use for content serialization.
		 */
		XmlSerializer* serializer_;

		/**
		 * The unresolved reference.
		 */
		const T* const reference_;
	};

	/**
	 * The @c UnresolvedReference class encapsulates data for resolving unresolved references.
	 */
	struct UnresolvedReference {
		/**
		 * The XML node of the unresolved pointer reference.
		 */
		TiXmlElement* unresolvedReferenceNode;

		/**
		 * Type string corresponding with the reference type.
		 *
		 * @note The string is empty if there is no corresponding type string.
		 */
		std::string typeString;

		/**
		 * The pointer address of the reference for XML node look up.
		 */
		void* reference;

		/**
		 * A @c IReferenceContentSerializer instance for serializing reference content
		 * when pointed data is not serialized during serialization process.
		 *
		 * @attention Remember to free assigned memory for @c referenceContentSerializer.
		 */
		IReferenceContentSerializer* referenceContentSerializer;
	};

	/**
	 * Type definition for unresolved references vector.
	 */
	typedef std::vector<UnresolvedReference> UnresolvedReferencesType;

	/**
	 * Vector of unresolved references which are resolved during the @c write method.
	 */
	UnresolvedReferencesType unresolvedReferences_;

	/**
	 * Current id for resolving unresolved references.
	 */
	long id_;

	/// Path to the target XML document
	std::string documentPath_;

};

template<class T>
XmlSerializer::ReferenceContentSerializer<T>::ReferenceContentSerializer(
	XmlSerializer* serializer, const T* const& reference)
	: serializer_(serializer)
	, reference_(reference)
{
}

template<class T>
TiXmlElement* XmlSerializer::ReferenceContentSerializer<T>::serialize(const std::string& key) const {
	TiXmlElement* result = 0;

	// Create temporary XML node...
	TemporaryNodeChanger nodeChange(*serializer_, new TiXmlElement(XmlSerializationConstantsGetInstance()->TEMPNODE));

	// Serialize reference content to temporary XML node...
	serializer_->serialize(key, *reference_);
	// ATTENTION: You must not clone or delete temporary node respectively its inner nodes,
	//            otherwise created pointers will point to incorrect address or become invalid.
	//            Remember to delete temporary XML node later.
	result = serializer_->node_->ToElement();

	return result;
}

inline void XmlSerializer::addDataNode(const void* data, TiXmlElement* node) {
	dataNodeMap_[const_cast<void*>(data)] = node;
}

template<class T>
inline void XmlSerializer::addUnresolvedReference(TiXmlElement* unresolvedReferenceNode,
												  const T* const& reference)
{
	// Is null pointer?
	if (!reference)
		// It is refering to nowhere, so we cannot do anything.
		return;

	// Assemble unresolved reference for resolving later on...
	XmlSerializer::UnresolvedReference unresolvedReference;
	unresolvedReference.unresolvedReferenceNode = unresolvedReferenceNode;
	unresolvedReference.typeString = getTypeString(typeid(*reference));
	unresolvedReference.reference = const_cast<T*>(reference);
	unresolvedReference.referenceContentSerializer = new ReferenceContentSerializer<T>(this, reference);

	// As we want ascending ids so far as possible,
	// we have to insert the unresolved references at the beginning.
	unresolvedReferences_.insert(unresolvedReferences_.begin(), unresolvedReference);
}

template<class T>
void XmlSerializer::serialize(const std::string& key, const T* const& data)
	throw (SerializationException)
{
	// Always serialize pointer content?
	if (usePointerContentSerialization_) {
		TemporaryUsePointerContentSerializationChanger usePointerContentSerializationChanger(*this, false);

		serialize(key, *data);

		return;
	}

	TiXmlElement* newNode = new TiXmlElement(key);

	// Is data not a null pointer?
	if (data) {
		// Set type attribute if a registered factory supports the data type T...
		std::string typeString = getTypeString(typeid(*data));
		if (!typeString.empty())
			newNode->SetAttribute(XmlSerializationConstantsGetInstance()->TYPEATTRIBUTE, typeString);
	}

	node_->LinkEndChild(newNode);

	addUnresolvedReference(newNode, data);
}

template<class S, class T>
void XmlSerializer::serialize(const std::string& key, const std::pair<S, T>& data)
	throw (SerializationException)
{
	TiXmlElement* newNode = new TiXmlElement(key);
	node_->LinkEndChild(newNode);

	TemporaryNodeChanger nodeChanger(*this, newNode);

	// first item
	if (useAttributes_ && isPrimitiveType(typeid(S))) {
		// serialize primitive type as XML attribute
		serializeAttributeInNode("First", XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, data.first);
	}
	else {
		// serialize as XML node
		serialize("First", data.first);
	}

	// second item
	if (useAttributes_ && isPrimitiveType(typeid(T))) {
		// serialize primitive type as XML attribute
		serializeAttributeInNode("Second", XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, data.second);
	}
	else {
		// serialize as XML node
		serialize("Second", data.second);
	}

	addDataNode(&data, newNode);
}

template<class T>
void XmlSerializer::serialize(const std::string& key, const std::vector<T>& data, const std::string& itemKey)
	throw (SerializationException)
{
	serializeCollection(key, data, itemKey);
}

template<class T>
void XmlSerializer::serialize(const std::string& key, const std::deque<T>& data, const std::string& itemKey)
	throw (SerializationException)
{
	serializeCollection(key, data, itemKey);
}

template<class T>
void XmlSerializer::serialize(const std::string& key, const std::list<T>& data, const std::string& itemKey)
	throw (SerializationException)
{
	serializeCollection(key, data, itemKey);
}

template<class T>
void XmlSerializer::serialize(const std::string& key, const std::stack<T>& data)
	throw (SerializationException)
{
	TiXmlElement* newNode = new TiXmlElement(key);
	node_->LinkEndChild(newNode);

	TemporaryNodeChanger nodeChanger(*this, newNode);

	// make a temporary copy of the stack
	std::stack<T> copy = data;

	// pop each element and serialize it until the stack is empty
	while (!copy.empty()) {
		const T& top = copy.top();
		serialize("Item", top);
		copy.pop();
	}

	addDataNode(&data, newNode);
}

template<class T, class C>
void XmlSerializer::serialize(const std::string& key, const std::set<T, C>& data, const std::string& itemKey)
	throw (SerializationException)
{
	if (usePointerContentSerialization_)
		raise(XmlSerializationInvalidOperationException("Set serialization using pointer content is not permitted."));
	serializeCollection(key, data, itemKey);
}

template<class T, class U, class C>
void XmlSerializer::serialize(const std::string& key,
							  const std::map<T, U, C>& data,
							  const std::string& valueKey,
							  const std::string& keyKey)
	throw (SerializationException)
{
	serializeMap(key, data, valueKey, keyKey);
}

template<class T>
inline void XmlSerializer::serializeSimpleTypes(const std::string& key, const T& data)
	throw (SerializationException)
{
	// Serialize as XML attribute?
	if (useAttributes_) {
		checkAttributeKey(key);
		node_->ToElement()->SetAttribute(key, convertDataToString(data));
	}
	// Serialize as XML node?
	else {
		TiXmlElement* newNode = new TiXmlElement(key);
		node_->LinkEndChild(newNode);
		newNode->SetAttribute(XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, convertDataToString(data));

		addDataNode(&data, newNode);
	}
}

template<>
inline void XmlSerializer::serializeSimpleTypes(const std::string& key, const std::string& data)
	throw (SerializationException)
{
	// Serialize as XML attribute wanted and possible?
	if (useAttributes_ && data.find("\n") == std::string::npos && data.find("\r") == std::string::npos) {
		checkAttributeKey(key);
		node_->ToElement()->SetAttribute(key, data);
		return;
	}

	// Serialize as XML node...
	TiXmlElement* newNode = new TiXmlElement(key);
	node_->LinkEndChild(newNode);
	if (data.find("\n") == std::string::npos && data.find("\r") == std::string::npos) {
		// ATTENTION: No special handling of the given string is needed that is why this block
		//            has to correspond with the not specialized serializeSimpleTypes method.
		newNode->SetAttribute(XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, data);
	}
	else {
		// Serialize string as CDATA to prevent possible conversion or other XML errors...
		TiXmlText* text = new TiXmlText(data);
		text->SetCDATA(true);
		newNode->LinkEndChild(text);
	}

	addDataNode(&data, newNode);
}

template<>
inline void XmlSerializer::serializeSimpleTypes(const std::string& key, const Serializable& data)
	throw (SerializationException)
{
	TiXmlElement* newNode = new TiXmlElement(key);
	node_->LinkEndChild(newNode);

	TemporaryNodeChanger nodeChanger(*this, newNode);

	data.serialize(*this);

	addDataNode(&data, newNode);
}

template<class T>
inline void XmlSerializer::serializeTgtVector(const std::string& key, const T& vector, const bool& isColor)
	throw (SerializationException)
{
	TiXmlElement* newNode = new TiXmlElement(key);
	node_->LinkEndChild(newNode);

	newNode->SetAttribute(
		isColor ? XmlSerializationConstantsGetInstance()->COLORRATTRIBUTE : XmlSerializationConstantsGetInstance()->VECTORXATTRIBUTE,
		convertDataToString(isColor ? static_cast<int>(vector[0]) : vector[0]));

	if (vector.size >= 2) {
		newNode->SetAttribute(
			isColor ? XmlSerializationConstantsGetInstance()->COLORGATTRIBUTE : XmlSerializationConstantsGetInstance()->VECTORYATTRIBUTE,
			convertDataToString(isColor ? static_cast<int>(vector[1]) : vector[1]));
	}

	if (vector.size >= 3) {
		newNode->SetAttribute(
			isColor ? XmlSerializationConstantsGetInstance()->COLORBATTRIBUTE : XmlSerializationConstantsGetInstance()->VECTORZATTRIBUTE,
			convertDataToString(isColor ? static_cast<int>(vector[2]) : vector[2]));
	}

	if (vector.size >= 4) {
		newNode->SetAttribute(
			isColor ? XmlSerializationConstantsGetInstance()->COLORAATTRIBUTE : XmlSerializationConstantsGetInstance()->VECTORWATTRIBUTE,
			convertDataToString(isColor ? static_cast<int>(vector[3]) : vector[3]));
	}

	addDataNode(&vector, newNode);
}

template<class T>
inline void XmlSerializer::serializeAttributeInNode(const std::string& nodeKey, const std::string& key, const T& data)
	throw (SerializationException)
{
	TiXmlNode* newNode = new TiXmlElement(nodeKey);
	node_->LinkEndChild(newNode);

	TemporaryNodeChanger nodeChanger(*this, newNode);

	serialize(key, data);
}

template<class T>
inline void XmlSerializer::serializeCollection(const std::string& key, const T& collection, const std::string& itemKey)
	throw (SerializationException)
{
	TiXmlElement* newNode = new TiXmlElement(key);
	node_->LinkEndChild(newNode);

	TemporaryNodeChanger nodeChanger(*this, newNode);

	for (typename T::const_iterator it = collection.begin(); it != collection.end(); ++it) {
		// Serialize primitive type as XML attribute?
		if (useAttributes_ && isPrimitiveType(typeid(typename T::value_type))) {
			serializeAttributeInNode(itemKey, XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, *it);
		}
		// Serialize as XML node...
		else
			serialize(itemKey, *it);
	}

	addDataNode(&collection, newNode);
}

template<class T>
inline void XmlSerializer::serializeMap(const std::string& key,
										const T& map,
										const std::string& valueKey,
										const std::string& keyKey)
	throw (SerializationException)
{
	TiXmlElement* newNode = new TiXmlElement(key);
	node_->LinkEndChild(newNode);

	TemporaryNodeChanger nodeChanger(*this, newNode);

	for (typename T::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		// Serialize primitive key type as XML node?
		if (!useAttributes_ || !isPrimitiveType(typeid(typename T::key_type)))
			serialize(keyKey, it->first);

		// Serialize primitive mapped type as XML attribute?
		if (useAttributes_ && isPrimitiveType(typeid(typename T::mapped_type))) {
			serializeAttributeInNode(valueKey, XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, it->second);
		}
		// Serialize as XML node...
		else {
			if (usePointerContentSerialization_ && useAttributes_ && isPrimitivePointerType(typeid(typename T::mapped_type))) {
				serializeAttributeInNode(valueKey, XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, it->second);
			}
			else
				serialize(valueKey, it->second);
		}

		// Serialize primitive key type as XML attribute?
		if (useAttributes_ && isPrimitiveType(typeid(typename T::key_type))) {
			TemporaryNodeChanger innerNodeChanger(*this, node_->LastChild());

			serialize(keyKey, it->first);

			moveAttributeToFront(keyKey, node_->ToElement());
		}
	}

	addDataNode(&map, newNode);
}

#pragma warning( pop )

#endif // VRN_XMLSERIALIZER_H
