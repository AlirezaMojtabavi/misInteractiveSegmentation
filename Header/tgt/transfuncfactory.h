#include <string>
#include "tgtMacroHeader.h"
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

#ifndef VRN_TRANSFUNCFACTORY_H
#define VRN_TRANSFUNCFACTORY_H

 
 

/**
 * The @c TransFuncFactory class is responsible for transfer function creation
 * during serialization process.
 *
 * @see SerializableFactory
 */
class TGTLIBMISDLLEXPORT TransFuncFactory   {
public:
    /**
     * Returns the singleton instance of the tranfer function factory.
     *
     * @returns the instance.
     */
    static TransFuncFactory* getInstance();

    /**
     * @see SerializableFactory::getTypeString
     */
    virtual const std::string getTypeString(const std::type_info& type) const;



private:
    /**
     * Default constructor.
     */
    TransFuncFactory();

    /**
     * Singleton instance of the transfer function factory.
     */
    static TransFuncFactory* instance_;
};

 

#endif // VRN_TRANSFUNCFACTORY_H
