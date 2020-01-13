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

#ifndef VRN_VOLUMEHANDLEPROPERTY_H
#define VRN_VOLUMEHANDLEPROPERTY_H

#include "templateproperty.h"
#include "condition.h"
#include "VoreenMacroes.h"

namespace voreen {

class VolumeHandle;

/**
 * Property encapsulating a VolumeHandle object.
 */


class VOREENEXPORTS VolumeHandleProperty : public TemplateProperty<VolumeHandle*> {

public:
    /**
     * Constructor.
     *
     * @param ident identifier that is used in serialization
     * @param guiText text that is shown in the gui
     * @param value the initial volume handle to assign
     *
     */
    VolumeHandleProperty(const std::string& id, const std::string& guiText, VolumeHandle* const value = 0,
       Processor::InvalidationLevel invalidationLevel = Processor::INVALID_PARAMETERS);

     virtual std::string getTypeString() const;

    /**
     * Sets the stored volume handle to the given one.
     *
     * @note The property does not take ownership of the
     *       assigned volume handle and does therefore NOT
     *       delete it on destruction or when a new handle is assigned.
     */
    void set(VolumeHandle* handle);

    

    /// @see Property::createWidget
      

    /// @see Property::serialize


    /// @see Property::deserialize
   

protected:
    /// Deletes the assigned volume, if it is owned by the property.
  
	void VolumeHandleProperty::deinitialize() throw (VoreenException);
    bool handleOwner_;

};

} // namespace voreen

#endif // VRN_VOLUMEHANDLEPROPERTY_H
