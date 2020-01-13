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
#pragma   once

/**
 * The @c XmlSerializationConstants class defines serialization constants, which are shared
 * by @c XmlSerializer and @c XmlDeserializer.
 *
 * @see XmlSerializer
 * @see XmlDeserializer
 */

class   XmlSerializationConstants {
public:

	 XmlSerializationConstants* getPtr();
	XmlSerializationConstants();
    /**
     * XML version attribute in XML declaration.
     */
      std::string XMLVERSION;

    /**
     * XML encoding attribute in XML declaration.
     */
      std::string XMLENCODING;

    /**
     * XML standalone attribute in XML declaration.
     */
      std::string XMLSTANDALONE;

    /**
     * XML root node name of serialized XML document.
     */
      std::string ROOTNODE;

    /**
     * Version attribute name.
     *
     * @note To obtain finer version control, you can set a version attribute for every XML node.
     */
      std::string VERSIONATTRIBUTE;

    /**
     * Version of @c XmlSerializer and @c XmlDeserializer.
     */
      std::string VERSION;

    /**
     * Id attribute name for reference resolving purposes.
     */
      std::string IDATTRIBUTE;

    /**
     * Reference attribute name for reference resolving purposes.
     */
      std::string REFERENCEATTRIBUTE;

    /**
     * Type attribute name for polymorphism purposes.
     */
      std::string TYPEATTRIBUTE;

    /**
     * Name of the value attribute which contains the content of simple types.
     */
      std::string VALUEATTRIBUTE;

    /**
     * Id prefix for reference resolving purposes.
     */
      std::string IDPREFIX;

    /**
     * Name of item nodes for collection serialization.
     */
      std::string ITEMNODE;

    /**
     * Name of key nodes for @c key/value pair serialization of maps.
     */
      std::string KEYNODE;

    /**
     * Name of value nodes for @c key/value pair serialization of maps.
     */
      std::string VALUENODE;

    /**
     * Name of temporary XML nodes.
     */
      std::string TEMPNODE;

    /**
     * Attribute name of vector's x element.
     */
      std::string VECTORXATTRIBUTE;

    /**
     * Attribute name of vector's y element.
     */
      std::string VECTORYATTRIBUTE;

    /**
     * Attribute name of vector's z element.
     */
      std::string VECTORZATTRIBUTE;

    /**
     * Attribute name of vector's w element.
     */
      std::string VECTORWATTRIBUTE;

    /**
     * Attribute name of color's r element.
     */
      std::string COLORRATTRIBUTE;

    /**
     * Attribute name of color's g element.
     */
      std::string COLORGATTRIBUTE;

    /**
     * Attribute name of color's b element.
     */
      std::string COLORBATTRIBUTE;

    /**
     * Attribute name of color's a element.
     */
      std::string COLORAATTRIBUTE;
};

  XmlSerializationConstants* XmlSerializationConstantsGetInstance();
