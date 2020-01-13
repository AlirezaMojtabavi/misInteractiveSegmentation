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

#ifndef VRN_XMLDESERIALIZER_H
#define VRN_XMLDESERIALIZER_H

#include "abstractserializable.h"
#include "logmanager.h"
#include "serializable.h"
#include "serializablefactory.h"
#include "serializationexceptions.h"
#include "xmlprocessor.h"
#include "xmlserializationconstants.h"
#include "xmlserializerbase.h"

#pragma warning( push )
#pragma warning( disable : 4290 )

// forward declaration
struct PlotSelectionEntry;

/**
 * @c XmlDeserializer is responsible for deserializing XML documents to memory data.
 *
 * @par
 * The implementation is capable of deserializing simple C++ data types, user defined classes
 * which are derived from @c Serializable, and most STL containers containing just the previously
 * mentioned data.
 *
 * @par
 * Furthermore, cycles, joints and polymorphic @c Serializable derivatives are supported which
 * makes the @c XmlDeserializer quite flexible. The deserialization process is independent
 * of deserialization order due to the use of @c key/value data, provided that different
 * keys are used at each hierarchy level.
 *
 * @par
 * Initially, the XML document can be read from an arbitrary @c std::istream. For instance, this
 * allows you to read a in memory created XML document from a @c std::stringstream.
 *
 * @par
 * You have to use @c XmlSerializer, which is the counterpart to @c XmlDeserializer, for
 * serializing memory data to XML documents.
 *
 * @par
 * Here is a short example of using the @c XmlDeserializer:
 * @code
 * int i;
 *
 * std::fstream f;
 * f.open("file.xml", std::ios::in);
 *
 * XmlDeserializer d;
 * d.read(f);
 * d.deserialize("i", i);
 *
 * f.close();
 * @endcode
 * For more complex examples and interaction with other classes of the serialization framework
 * see the &quot;serializertest&quot; application in &quot;apps/&quot; directory.
 *
 * @attention The whole XML document must be deserialized before you can use deserialized data.
 *            Otherwise, it cannot be ensured that all pointer references are correctly resolved.
 *
 * @note For further information on handling cycles, joints and polymorphism, see:
 *       http://www.parashift.com/c++-faq-lite/serialization.html
 *
 * @see XmlSerializer
 * @see XmlSerializerBase
 * @see Serializable
 */
class   XmlDeserializer : public XmlSerializerBase
{
public:
    /**
     * Constructor.
     *
     * @param documentPath Absolute path to the XML file the document has been read from. This information
     *     is not used by the deserializer itself and is therefore not required, but is intended
     *     to be accessible by deserializing objects for relative-to-absolute path conversions.
     */
    XmlDeserializer(std::string documentPath = "");

    /**
     * Default destructor.
     */
    ~XmlDeserializer();

    /**
     * Returns the absolute path to the XML file the document was read from.
     */
    std::string getDocumentPath() const;

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, bool& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, char& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, signed char& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, unsigned char& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, signed short& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, unsigned short& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, signed int& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, unsigned int& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, signed long& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
	 *
	 * @note: This overload was added by m.i.soboute
     */
	void deserialize(const std::string& key, long long& data)
		throw (SerializationException);

	/**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, unsigned long& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, float& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, double& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, long double& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, std::string& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::vec2& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::vec3& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::vec4& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::dvec2& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::dvec3& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::dvec4& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::ivec2& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::ivec3& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::ivec4& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */

	void deserialize(const std::string& key, tgt::Vector3ui& data)
		throw (SerializationException);

	void deserialize(const std::string& key, tgt::bvec3& data)
		throw (SerializationException);

    void deserialize(const std::string& key, tgt::col3& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::col4& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::mat2& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::mat3& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::mat4& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::Matrix2d& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::Matrix3d& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c key/data pair.
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, tgt::Matrix4d& data)
        throw (SerializationException);

    /**
     * Deserializes the given @c Serializable interface realization.
     *
     * @note All user defined classes must realize the @c Serializable
     *       interface to be deserializable.
     *
     * @param key the XML node key
     * @param data variable to store deserialized @c Serializable realization
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    void deserialize(const std::string& key, Serializable& data)
        throw (SerializationException);

    /**
     * Deserializes the given pointer reference.
     *
     * @tparam type of referenced data
     *
     * @param key the XML node key
     * @param data variable to store deserialized pointer reference
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     */
    template<class T>
    void deserialize(const std::string& key, T*& data)
        throw (SerializationException);

    /**
     * Deserializes a std::pair.
     *
     * @tparam S data type of first pair item
     * @tparam T data type of second pair item
     *
     * @param key the XML node key
     * @param data variable to store deserialized pair
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     */
    template<class S, class T>
    void deserialize(const std::string& key, std::pair<S, T>& data)
        throw (SerializationException);

    /**
     * Deserializes a data vector.
     *
     * @note Element order of collection items remains constant during
     *       serialization and deserialization.
     *
     * @tparam T data type of vector items
     *
     * @param key the XML node key
     * @param data variable to store deserialized data vector
     * @param itemKey XML node key for each XML child node
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     */
    template<class T>
    void deserialize(const std::string& key, std::vector<T>& data, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
        throw (SerializationException);

    /**
     * Deserializes a data deque.
     *
     * @note Element order of collection items remains constant during
     *       serialization and deserialization.
     *
     * @tparam T data type of vector items
     *
     * @param key the XML node key
     * @param data variable to store deserialized data vector
     * @param itemKey XML node key for each XML child node
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     */
    template<class T>
    void deserialize(const std::string& key, std::deque<T>& data, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
        throw (SerializationException);

    /**
     * Deserializes a data list.
     *
     * @note Element order of collection items remains constant during
     *       serialization and deserialization.
     *
     * @tparam T data type of vector items
     *
     * @param key the XML node key
     * @param data variable to store deserialized data vector
     * @param itemKey XML node key for each XML child node
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     */
    template<class T>
    void deserialize(const std::string& key, std::list<T>& data, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
        throw (SerializationException);

    /**
     * Deserializes a data set.
     *
     * @note Element order of set items are not guaranteed to remains constant
     *       during serialization and deserialization due to limits of
     *       some STL containers like @c std::set.
     *
     * @tparam T data type of set items
     * @tparam C comparison class @see std::set
     *
     * @param key the XML node key
     * @param data variable to store deserialized data set
     * @param itemKey XML node key for each XML child node
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     * @throws XmlSerializationInvalidOperationException
     *         if pointer content serialization is enabled,
     *         because of possible hash problems on deserialization
     */
    template<class T, class C>
    void deserialize(const std::string& key, std::set<T, C>& data, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
        throw (SerializationException);

    /**
     * Deserializes a data stack.
     *
     * @tparam T data type of set items
     *
     * @param key the XML node key
     * @param data variable to store deserialized data set
     * @param itemKey XML node key for each XML child node
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     * @throws XmlSerializationInvalidOperationException
     *         if pointer content serialization is enabled,
     *         because of possible hash problems on deserialization
     */
    template<class T>
    void deserialize(const std::string& key, std::stack<T>& data, const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
        throw (SerializationException);

    /**
     * Deserializes a data map.
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
     * @param data variable to store deserialized data map
     * @param valueKey XML node key for each value node
     * @param keyKey key for each XML key node or attribute
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     */
    template<class T, class U, class C>
    void deserialize(
        const std::string& key,
        std::map<T, U, C>& data,
        const std::string& valueKey = XmlSerializationConstantsGetInstance()->VALUENODE,
        const std::string& keyKey = XmlSerializationConstantsGetInstance()->KEYNODE)
        throw (SerializationException);
	/**
     * Mark a pointer as freed during deserialization process,
     * which leads to null pointer resolving of all coming references to this pointer.
     *
     * @param pointer the pointer to mark as freed
     */
    void freePointer(void* pointer);

    /**
     * Reads the XML document from the given input stream after an optional XML preprocessor is applied.
     *
     * @param stream the input stream
     * @param xmlProcessor XML preprocessor
     *
     * @throws XmlSerializationFormatException if the XML document is incorrect formatted.
     * @throws XmlSerializationVersionMismatchException if the XML document serialization version
     *     does not match with the serialization version of this class.
     * @throws XmlSerializationReferenceResolvingException if there are references in
     *     the XML document which cannot be resolved.
     */
    void read(std::istream& stream, XmlProcessor* xmlProcessor = 0)
        throw (SerializationException);

protected:
    /**
     * Category for logging.
     */
       std::string loggerCat_;

private:
    /**
     * Adds given @c id/address pair to the pointer address look up map.
     *
     * @param element XML element containing the id attribute
     * @param address the address
     *
     * @throws XmlSerializationDuplicateIdException if id already exists
     */
    inline void addReferenceAddress(TiXmlElement* element, void* address)
        throw (SerializationException);

    /**
     * Adds given @c id/reference pair to the unresolved reference map.
     *
     * @param element XML element containing the reference attribute
     * @param data the unresolved reference
     */
    template<class T>
    inline void addUnresolvedReference(TiXmlElement* element, T*& data);

    typedef std::set<std::string> ReferenceIdSetType;
    typedef std::vector<std::string> ReferenceIdListType;

    /**
     * Helper function for recursive search for unresolvable references.
     *
     * To determine all unresolvable references you have to look up for
     * all @c references which are not in the @c resolvableReferences set.
     *
     * @param node the node to search for unresolvable references
     * @param references a set containing all references
     * @param resolvableReferences a set containing all resolvable references
     */
    void findUnresolvableReferences(TiXmlElement* node, ReferenceIdSetType& references, ReferenceIdSetType& resolvableReferences) const;

    /**
     * Finds and returns unresolvable references.
     *
     * @return a vector containing the reference ids of each unresolvable reference.
     */
    ReferenceIdListType findUnresolvableReferences() const;

    /**
     * Helper function for deserializing @c key/data pairs with simple data types.
     *
     * @tparam T data type
     *
     * @param key the XML node key
     * @param data variable to store deserialized data
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     */
    template<class T>
    inline void deserializeSimpleTypes(const std::string& key, T& data)
        throw (SerializationException);

    /**
     * Helper function for deserializing tgt vectors.
     *
     * @tparam T data type of vector
     *
     * @param key the XML node key
     * @param vector variable to store deserialized vector
     * @param isColor flag determine if given vector is a color
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     */
    template<class T>
    inline void deserializeTgtVector(const std::string& key, T& vector, const bool& isColor = false)
        throw (SerializationException);

    /**
     * Helper function deserializes the given @c key/data pair from XML attribute named @c key
     * contained in the XML node @c nodeKey.
     *
     * @tparam T data type
     *
     * @param nodeKey the XML node key
     * @param key the XML attribute key
     * @param data variable to store deserialized data
     * @param markVisited if @c true the XML node with given @c nodeKey is marked as visited
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     */
    template<class T>
    inline void deserializeAttributeFromNode(const std::string& nodeKey, const std::string& key, T& data, const bool& markVisited = true)
        throw (SerializationException);

    /**
     * Helper function for deserializing data collections like STL container.
     *
     * Serialization using pointer content does not make sense for constant iterator items,
     * that is why this function ignores the setting concerning usage of pointer content
     * serialization.
     *
     * @note Element order of collection items remains constant during
     *       serialization and deserialization.
     *
     * @tparam T data type of collection
     *
     * @param key the XML node key
     * @param collection variable to store deserialized data collection
     * @param itemKey XML node key for each XML child node
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     */
    template<class T>
    inline void deserializeCollectionConstIteratorItems(
        const std::string& key,
        T& collection,
        const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
        throw (SerializationException);

    /**
     * Helper function for deserializing data collections like STL container.
     *
     * @note Element order of collection items remains constant during
     *       serialization and deserialization.
     *
     * @tparam T data type of collection
     *
     * @param key the XML node key
     * @param collection variable to store deserialized data collection
     * @param itemKey XML node key for each XML child node
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     */
    template<class T>
    inline void deserializeCollection(
        const std::string& key,
        T& collection,
        const std::string& itemKey = XmlSerializationConstantsGetInstance()->ITEMNODE)
        throw (SerializationException);

    /**
     * Helper function for deserializing data maps like STL maps.
     *
     * @note Element order of map items are not guaranteed to remains constant
     *       during serialization and deserialization due to limits of
     *       some STL containers like @c std::map.
     *
     * @tparam T data type of map
     *
     * @param key the XML node key
     * @param map varaible to store deserialized data map
     * @param valueKey XML node key for each value node
     * @param keyKey key for each XML key node or attribute
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     * @throws XmlSerializationFormatException if a XML node is incorrect formatted.
     * @throws XmlSerializationDuplicateIdException if multiple XML nodes share same id attribute
     * @throws XmlSerializationMemoryAllocationException
     *         in case of trying to allocate memory for an @c AbstractSerializable
     *         or if there are not enough allocate items if pointer content serialization is enabled
     */
    template<class T>
    inline void deserializeMap(
        const std::string& key,
        T& map,
        const std::string& valueKey = XmlSerializationConstantsGetInstance()->VALUENODE,
        const std::string& keyKey = XmlSerializationConstantsGetInstance()->KEYNODE)
        throw (SerializationException);

    /**
     * Resolves the reference corresponding with the reference attribute of the given @c element.
     *
     * @param element XML element containing reference attribute
     * @param data variable to store resolved reference
     */
    template<class T>
    void resolveReference(TiXmlElement* element, T*& data);

    /**
     * Returns the next XML element with given @c key as name, which is not deserialized yet.
     *
     * @param key XML node name
     *
     * @returns the next XML element with given @c key as name
     *
     * @throws XmlSerializationNoSuchDataException if no data with the given key can be found.
     */
	static  bool excpectedToFind;
	static  bool findedElement;
    TiXmlElement* getNextXmlElement(const std::string& key)
        throw (SerializationException);

    /**
     * Type definition for set of visited XML nodes.
     */
    typedef std::set<TiXmlNode*> VisitedNodesSetType;

    /**
     * Set of already visited XML nodes.
     */
    VisitedNodesSetType visitedNodes_;

    /**
     * Type definition for pointer address look up map.
     */
    typedef std::map<std::string, void*> IdAddressMapType;

    /**
     * Map for looking up pointer addresses by reference id.
     */
    IdAddressMapType idAddressMap_;

    /**
     * The @c IReferenceResolver interface allow to treat every @c ReferenceResolver
     * template specialization in the same way.
     *
     * @see ReferenceResolver
     */
    class IReferenceResolver {
    public:

        virtual ~IReferenceResolver() {}

        /**
         * Resolves an unresolved pointer reference.
         *
         * @param resolvedAddress the resolved address
         */
        virtual void resolve(void* resolvedAddress) = 0;
    };

    /**
     * @c ReferenceResolver is a concrete implementation for resolving
     * unresolved pointer references.
     *
     * @attention Resolving of unresolved references cannot be done in
     *            case of incomplete XML documents, which does not contain
     *            the referenced data, or in case of deserialization method-calls
     *            do not correspond to the serialization method-calls.
     *
     * @tparam type of referenced data
     *
     * @see IReferenceResolver
     */
    template<class T>
    class ReferenceResolver : public IReferenceResolver {
    public:
        /**
         * Constructs a @c ReferenceResolver in accordance to the given parameters.
         *
         * @param data variable to store resolved address
         */
        ReferenceResolver(T*& data);

        /**
         * @see IReferenceResolver::resolve
         */
        virtual void resolve(void* resolvedAddress);

    private:
        /**
         * Reference to pointer which needs address resolving.
         */
        T*& data_;
    };

    /**
     * Type definition for reference resolver list.
     */
    typedef std::vector<IReferenceResolver*> ReferenceResolverListType;

    /**
     * Type definition for unresolved reference map.
     */
    typedef std::map<std::string, ReferenceResolverListType> UnresolvedReferenceMapType;

    /**
     * Unresolved reference map which contains map/reference-resolver-list pairs.
     */
    UnresolvedReferenceMapType unresolvedReferenceMap_;

    /// Path to XML file the document was read from.
    std::string documentPath_;
};

template<class T>
XmlDeserializer::ReferenceResolver<T>::ReferenceResolver(T*& data) : data_(data) {
}

template<class T>
void XmlDeserializer::ReferenceResolver<T>::resolve(void* resolvedAddress) {
    data_ = static_cast<T*>(resolvedAddress);
}

inline void XmlDeserializer::addReferenceAddress(TiXmlElement* element, void* address)
    throw (SerializationException)
{
    const std::string* id = element->Attribute(XmlSerializationConstantsGetInstance()->IDATTRIBUTE);
    // Has element no id attribute?
    if (!id)
        return;

    // Does id already exists?
    if (idAddressMap_.find(*id) != idAddressMap_.end())
        raise(XmlSerializationDuplicateIdException("Multiple XML nodes share the id attribute '" + *id + "'"));

    // If there are unresolved references to this id, resolve them...
    UnresolvedReferenceMapType::iterator idIterator = unresolvedReferenceMap_.find(*id);
    if (idIterator != unresolvedReferenceMap_.end()) {
        for (ReferenceResolverListType::iterator it = idIterator->second.begin(); it != idIterator->second.end(); ++it) {
            (*it)->resolve(address);
            delete *it;
        }

        unresolvedReferenceMap_.erase(idIterator);
    }

    idAddressMap_[*id] = address;
}

template<class T>
inline void XmlDeserializer::addUnresolvedReference(TiXmlElement* element, T*& data) {
    const std::string* reference = element->Attribute(XmlSerializationConstantsGetInstance()->REFERENCEATTRIBUTE);

    // Has element no reference attribute?
    if (!reference)
        return;

    // Are there other unresolved references with same id?
    if (unresolvedReferenceMap_.find(*reference) != unresolvedReferenceMap_.end()) {
        // Insert reference resolver into existing list...
        unresolvedReferenceMap_.find(*reference)->second.push_back(new ReferenceResolver<T>(data));
    }
    else {
        // Create new reference resolver list and append a new reference resolver...
        ReferenceResolverListType referenceResolverList;
        referenceResolverList.push_back(new ReferenceResolver<T>(data));
        unresolvedReferenceMap_[*reference] = referenceResolverList;
    }
}

template<class T>
void XmlDeserializer::deserialize(const std::string& key, T*& data)
    throw (SerializationException)
{
    // Always deserialize pointer from content?
    if (usePointerContentSerialization_) {
        TemporaryUsePointerContentSerializationChanger usePointerContentSerializationChanger(*this, false);

        deserialize(key, *data);

        return;
    }

    TiXmlElement* element = getNextXmlElement(key);

    const std::string* reference = element->Attribute(XmlSerializationConstantsGetInstance()->REFERENCEATTRIBUTE);

    // Set pointer to null to be on the safe side(delete on 0 is allowed)...
    data = 0;

    // Has element reference attribute?
    if (reference) {
        resolveReference(element, data);
    }
    else { // No reference attribute...
        // Does element contain serialized content?
        if (useAttributes_ || element->Attribute(XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE) || !element->NoChildren()) {
            // Is AbstractSerializable 0 pointer?
            if (!element->FirstAttribute() && element->NoChildren())
                return;

            // Gather type information...
            const std::string* type = element->Attribute(XmlSerializationConstantsGetInstance()->TYPEATTRIBUTE);

            // Allocate memory for the object...
			_ASSERT(data!=NULL);
            //data = allocateMemory<T>(data, type);

            // ATTENTION: We have to set element unvisited in order to deserialize it.
            visitedNodes_.erase(visitedNodes_.find(element));

            deserialize(key, *data);
        }
    }
}

template<class S, class T>
void XmlDeserializer::deserialize(const std::string& key, std::pair<S, T>& data)
    throw (SerializationException)
{
    // Always deserialize pointer from content?
    if (usePointerContentSerialization_) {
        TemporaryUsePointerContentSerializationChanger usePointerContentSerializationChanger(*this, false);

        deserialize(key, data.first);
        deserialize(key, data.second);

        return;
    }

    TiXmlElement* element = getNextXmlElement(key);

    TemporaryNodeChanger nodeChanger(*this, element);

    // first item
    if (useAttributes_ && isPrimitiveType(typeid(S))) {
        // deserialize primitive type from XML attribute
        deserializeAttributeFromNode("First", XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, data.first);
    }
    else {
        deserialize("First", data.first);
    }

    // second item
    if (useAttributes_ && isPrimitiveType(typeid(T))) {
        // deserialize primitive type from XML attribute
        deserializeAttributeFromNode("Second", XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, data.second);
    }
    else {
        deserialize("Second", data.second);
    }

    addReferenceAddress(element, &data);
}

template<class T>
void XmlDeserializer::deserialize(const std::string& key, std::vector<T>& data, const std::string& itemKey)
    throw (SerializationException)
{
    deserializeCollection(key, data, itemKey);
}

template<class T>
void XmlDeserializer::deserialize(const std::string& key, std::deque<T>& data, const std::string& itemKey)
    throw (SerializationException)
{
    deserializeCollection(key, data, itemKey);
}

template<class T>
void XmlDeserializer::deserialize(const std::string& key, std::list<T>& data, const std::string& itemKey)
    throw (SerializationException)
{
    deserializeCollection(key, data, itemKey);
}

template<class T, class C>
void XmlDeserializer::deserialize(const std::string& key, std::set<T, C>& data, const std::string& itemKey)
    throw (SerializationException)
{
    if (usePointerContentSerialization_)
        raise(XmlSerializationInvalidOperationException("Set deserialization using pointer content is not permitted."));
    deserializeCollectionConstIteratorItems(key, data, itemKey);
}

template<class T, class U, class C>
void XmlDeserializer::deserialize(const std::string& key,
                                  std::map<T, U, C>& data,
                                  const std::string& valueKey,
                                  const std::string& keyKey)
    throw (SerializationException)
{
    deserializeMap(key, data, valueKey, keyKey);
}

template<class T>
void XmlDeserializer::deserialize(const std::string& key, std::stack<T>& data, const std::string& itemKey)
    throw (SerializationException)
{
}

template<class T>
inline void XmlDeserializer::deserializeSimpleTypes(const std::string& key, T& data)
	throw (SerializationException)
{
	TiXmlElement* element;
	if (useAttributes_)
		element = node_->ToElement();
	else
		element = getNextXmlElement(key);
	if (!element)
		return;
    const std::string* value;

    if (useAttributes_) {
        value = element->Attribute(key);
        if (!value)
            raise(XmlSerializationNoSuchDataException("No attribute with key '" + key + "' found."));
    }
    else {
        // Is there no value attribute in XML element?
        value = element->Attribute(XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE);
        if (!value)
            raise(XmlSerializationFormatException("XML node '" + key + "' does not contain value attribute."));
    }

    convertStringToData(*value, data);

    if (!useAttributes_)
        addReferenceAddress(element, &data);
}

template<>
inline void XmlDeserializer::deserializeSimpleTypes(const std::string& key, std::string& data)
    throw (SerializationException)
{
    TiXmlElement* element;
    // Deserialize from XML attributes?

		if (useAttributes_)
			element = node_->ToElement();
		else
			element = getNextXmlElement(key);

if (!element)
	return;

    const std::string* value;
    // Deserialize from XML attributes?
    if (useAttributes_)
        value = element->Attribute(key);
    else
        value = element->Attribute(XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE);

    // Is there no matching attribute in XML element?
    if (value) {
        // ATTENTION: No special handling of the given string is needed that is why this block
        //            has to correspond with the not specialized serializeSimpleTypes method.
        data = *value;
    }
    else {
        // Deserialize from XML attributes?
        if (useAttributes_)
            element = getNextXmlElement(key);

        // Is there no text in the XML element?
        if (!element->FirstChild() || element->FirstChild()->Type() != TiXmlElement::TEXT) {
            // Deserialize from XML attributes?
            if (useAttributes_)
                raise(XmlSerializationNoSuchDataException("Neither a '" + key + "' attribute nor text content data exists."));
            else
                raise(XmlSerializationFormatException("XML node '" + key + "' neither has a value attribute nor contains text data."));
        }

        data = element->FirstChild()->ToText()->ValueStr();
    }

    if (!useAttributes_)
        addReferenceAddress(element, &data);
}

template<>
inline void XmlDeserializer::deserializeSimpleTypes(const std::string& key, Serializable& data)
    throw (SerializationException)
{
    TiXmlElement* element = getNextXmlElement(key);

	if(!element)
		return;
    TemporaryNodeChanger nodeChanger(*this, element);

    data.deserialize(*this);

    addReferenceAddress(element, &data);
}

template<class T>
inline void XmlDeserializer::deserializeTgtVector(const std::string& key, T& vector, const bool& isColor)
    throw (SerializationException)
{
    TiXmlElement* element = getNextXmlElement(key);
	if(!element)
		 raise(XmlSerializationNoSuchDataException("Xml node '" + key ));
    const std::string* x;
    const std::string* y;
    const std::string* z;
    const std::string* w;
    if (isColor) {
        x = element->Attribute(XmlSerializationConstantsGetInstance()->COLORRATTRIBUTE);
        y = element->Attribute(XmlSerializationConstantsGetInstance()->COLORGATTRIBUTE);
        z = element->Attribute(XmlSerializationConstantsGetInstance()->COLORBATTRIBUTE);
        w = element->Attribute(XmlSerializationConstantsGetInstance()->COLORAATTRIBUTE);
    }
    else {
        x = element->Attribute(XmlSerializationConstantsGetInstance()->VECTORXATTRIBUTE);
        y = element->Attribute(XmlSerializationConstantsGetInstance()->VECTORYATTRIBUTE);
        z = element->Attribute(XmlSerializationConstantsGetInstance()->VECTORZATTRIBUTE);
        w = element->Attribute(XmlSerializationConstantsGetInstance()->VECTORWATTRIBUTE);
    }

    // Is there no x attribute?
    if (!x)
        raise(XmlSerializationFormatException("Xml node '" + key + "' has no x-attribute."));

    if (isColor) {
        // ATTENTION: The string to int to type conversion is mandatory,
        //            since tgt::col3, tgt::col4 are vector of UCHARs.
        //            Otherwise, strings like "153" are converted to '1' instead of 153.
        int value;
        convertStringToData(*x, value);
        vector[0] = static_cast<typename T::ElemType>(value);
    }
    else
        convertStringToData(*x, vector[0]);

    // Y attribute expected?
    if (vector.size >= 2) {
        // Is there no y attribute?
        if (!y)
            raise(XmlSerializationFormatException("Xml node '" + key + "' has no y-attribute."));

        if (isColor) {
            // ATTENTION: The string to int to type conversion is mandatory,
            //            since tgt::col3, tgt::col4 are vector of UCHARs.
            //            Otherwise, strings like "153" are converted to '1' instead of 153.
            int value;
            convertStringToData(*y, value);
            vector[1] = static_cast<typename T::ElemType>(value);
        }
        else
            convertStringToData(*y, vector[1]);
    }

    // Z attribute expected?
    if (vector.size >= 3) {
        // Is there no z attribute?
        if (!z)
            raise(XmlSerializationFormatException("Xml node '" + key + "' has no z-attribute."));

        if (isColor) {
            // ATTENTION: The string to int to type conversion is mandatory,
            //            since tgt::col3, tgt::col4 are vector of UCHARs.
            //            Otherwise, strings like "153" are converted to '1' instead of 153.
            int value;
            convertStringToData(*z, value);
            vector[2] = static_cast<typename T::ElemType>(value);
        }
        else
            convertStringToData(*z, vector[2]);
    }

    // W attribute expected?
    if (vector.size >= 4) {
        // Is there no w attribute?
        if (!w)
            raise(XmlSerializationFormatException("Xml node '" + key + "' has no w-attribute."));

        if (isColor) {
            // ATTENTION: The string to int to type conversion is mandatory,
            //            since tgt::col3, tgt::col4 are vector of UCHARs.
            //            Otherwise, strings like "153" are converted to '1' instead of 153.
            int value;
            convertStringToData(*w, value);
            vector[3] = static_cast<typename T::ElemType>(value);
        }
        else
            convertStringToData(*w, vector[3]);
    }

    addReferenceAddress(element, &vector);
}

template<class T>
inline void XmlDeserializer::deserializeAttributeFromNode(const std::string& nodeKey, const std::string& key, T& data, const bool& markVisited)
    throw (SerializationException)
{
    TemporaryNodeChanger nodeChanger(*this, getNextXmlElement(nodeKey));

    deserialize(key, data);

    if (!markVisited)
        visitedNodes_.erase(node_);
}

template<class T>
inline void XmlDeserializer::deserializeCollectionConstIteratorItems(const std::string& key, T& collection, const std::string& itemKey)
    throw (SerializationException)
{
    TiXmlElement* element = getNextXmlElement(key);

    TemporaryNodeChanger nodeChanger(*this, element);
	findedElement=true;
	excpectedToFind=false;

    try {
        collection.clear();

        while (findedElement) {
            typename T::value_type item;

            try {
                // Deserialize primitive type from XML attribute?
                if (useAttributes_ && isPrimitiveType(typeid(typename T::value_type))) {
                    deserializeAttributeFromNode(itemKey, XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, item);
                }
                else
                    deserialize(itemKey, item);

				if (findedElement)
				{
					collection.insert(collection.end(), item);
				}
            }
            catch (XmlSerializationMemoryAllocationException&) {
                // Just ignore items for which no memory was allocatable...
            }
        }
    }
    catch (XmlSerializationNoSuchDataException&) {
        // There are just no more collection items, just ignore the exception...
        removeLastError();
    }

    addReferenceAddress(element, &collection);
	excpectedToFind=true;
}

template<class T>
inline void XmlDeserializer::deserializeCollection(const std::string& key, T& collection, const std::string& itemKey)
    throw (SerializationException)
{
    // Never deserialize pointer from content?
    if (!usePointerContentSerialization_) {
        deserializeCollectionConstIteratorItems(key, collection, itemKey);
        return;
    }

    TiXmlElement* element = getNextXmlElement(key);

    TemporaryNodeChanger nodeChanger(*this, element);

    for (typename T::iterator it = collection.begin(); it != collection.end(); ++it) {
        // Deserialize primitive type from XML attribute?
        if (useAttributes_ && isPrimitiveType(typeid(typename T::value_type))) {
            deserializeAttributeFromNode(itemKey, XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, *it);
        }
        else
            deserialize(itemKey, *it);
    }

    try {
        getNextXmlElement(itemKey);
        // Collection is too small for storing all serialized values. Log it, but do not treat as error.
        //addError(XmlSerializationMemoryAllocationException("Not enough allocated items in collection."));
        LWARNING("Not enough allocated items in collection with key: " << key);
    }
    catch (XmlSerializationNoSuchDataException&) {
        removeLastError();
    }

    addReferenceAddress(element, &collection);
}

template<class T>
inline void XmlDeserializer::deserializeMap(const std::string& key,
                                            T& map,
                                            const std::string& valueKey,
                                            const std::string& keyKey)
    throw (SerializationException)
{
    TiXmlElement* element = getNextXmlElement(key);

    TemporaryNodeChanger nodeChanger(*this, element);

    try {
        if (!usePointerContentSerialization_)
            map.clear();

		findedElement=true;
		excpectedToFind=false;
        while (findedElement) {
            typename T::key_type key;
            typename T::mapped_type value;

            bool memoryAllocationExceptionCatched = false;

            try {
                // Deserialize primitive key type as XML attribute?
                if (useAttributes_ && isPrimitiveType(typeid(typename T::key_type))) {
                    // ATTENTION: We have to set element unvisited in order to deserialize its content later.
                    deserializeAttributeFromNode(valueKey, keyKey, key, false);
                }
                else
                    deserialize(keyKey, key);
            }
            catch (XmlSerializationMemoryAllocationException&) {
                memoryAllocationExceptionCatched = true;
            }

            // Always deserialize pointer from content?
            if (usePointerContentSerialization_) {
                if (map.find(key) == map.end()) {
                    // There is no map item with deserialized key. Log it, but do not treat it as error.
                    //addError(XmlSerializationMemoryAllocationException("No allocated map item with key '" + convertDataToString(key) + "'."));
                    LWARNING("No allocated map item with key '" << convertDataToString(key) << "'.");
                    getNextXmlElement(valueKey);
                    continue;
                }

                // Deserialize primitive mapped type from XML attribute?
                if (useAttributes_
                    && (isPrimitiveType(typeid(typename T::mapped_type)) || isPrimitivePointerType(typeid(typename T::mapped_type))))
                {
                    deserializeAttributeFromNode(valueKey, XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, map.find(key)->second);
                } // Deserialize primitive mapped type from XML node
                else
                    deserialize(valueKey, map.find(key)->second);;
            }
            else {
                try {
                    // Deserialize primitive mapped type as XML attribute?
                    if (useAttributes_ && isPrimitiveType(typeid(typename T::mapped_type)))
                        deserializeAttributeFromNode(valueKey, XmlSerializationConstantsGetInstance()->VALUEATTRIBUTE, value);
                    // Deserialize primitive mapped type from XML node
                    else
                        deserialize(valueKey, value);
                }
                catch (XmlSerializationMemoryAllocationException&) {
                    memoryAllocationExceptionCatched = true;
                }
            }

            if (!memoryAllocationExceptionCatched && !usePointerContentSerialization_)
                map[key] = value;
        }
    }
    catch (XmlSerializationNoSuchDataException&) {
        // There are just no more collection items, just ignore the exception...
        removeLastError();
    }

	excpectedToFind=true;
    addReferenceAddress(element, &map);
}

template<class T>
void XmlDeserializer::resolveReference(TiXmlElement* element, T*& data) {
    const std::string* reference = element->Attribute(XmlSerializationConstantsGetInstance()->REFERENCEATTRIBUTE);

    // Has XML element no reference attribute?
    if (!reference)
        return;

    // Is referenced data already deserialized?
    if (idAddressMap_.find(*reference) != idAddressMap_.end()) {
        data = static_cast<T*>(idAddressMap_.find(*reference)->second);
    }
    else { // Have to wait for deserialization of referenced data...
        const std::string* type = element->Attribute(XmlSerializationConstantsGetInstance()->TYPEATTRIBUTE);

        // Has XML element an type attribute?
        if (type) {
            // Check if later resolving is possible at all?
            //delete allocateMemory<T>(data, type);

            // As no exception was raise later resolving is possible, so add unresolved reference...
            addUnresolvedReference(element, data);
        }
        else
            addUnresolvedReference(element, data);
    }
}

#pragma warning( pop )

#endif // VRN_XMLDESERIALIZER_H
