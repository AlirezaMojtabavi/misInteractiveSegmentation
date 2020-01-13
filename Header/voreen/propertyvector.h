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

#ifndef VRN_PROPERTYVECTOR_H
#define VRN_PROPERTYVECTOR_H

#include "tgt/vector.h"
#include "logmanager.h"
#include "propertyowner.h"
#include "templateproperty.h"
#include "condition.h"

#include <vector>
#include <string>

namespace voreen {

class PropertyVector : public Property, PropertyOwner{
public:

    PropertyVector(const std::string& id, const std::string& guiText, std::vector<Property*> properties);

    virtual ~PropertyVector();

    virtual std::string getTypeString() const;

    virtual std::string getName() const;

    void addProperty(Property* prop);

    const std::vector<Property*>& getProperties() const;

    template<typename T>
    T getProperty(int id) const {
        T prop = 0;
        if (id >= 0 && id < size()) {
            prop = dynamic_cast<T>(properties_[id]);
            if (!prop) {
                LWARNING("Property is of invalid type");
            }
        }
        else {
            //tgtAssert(false, "Invalid property id.");
            LERROR("Invalid property id: " << id);
        }
        return prop;
    }

    int size() const;

    /**
     * @see Property::serialize
     */


    /**
     * @see Property::deserialize
     */
   

     

    virtual void setOwner(PropertyOwner* owner);

protected:

    /**
     * Initializes the component properties.
     *
     * @see Property::initialize
     */
    void initialize() throw (VoreenException);

    /**
     * Deinitializes the component properties.
     *
     * @see Property::deinitialize
     */
    void deinitialize() throw (VoreenException);

    std::vector<Property*> properties_;

    static const std::string loggerCat_;

};

}   // namespace

#endif
