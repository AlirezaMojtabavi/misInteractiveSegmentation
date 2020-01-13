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

#ifndef VRN_PROPERTY_H
#define VRN_PROPERTY_H

#include "tgt/vector.h"
 
 
#include "processor.h"

#include <string>
#include <vector>
#include <set>
#include <sstream>
#include "exception.h"
#include "VoreenMacroes.h"

namespace voreen {

class PropetyOwner;

class ProcessorNetwork;

/**
 * Abstract base class for properties that can be assigned to processors
 * and other PropertyOwners.
 *
 * @see TemplateProperty
 */


class VOREENEXPORTS Property {

     
    friend class PropertyVector;
    friend class Processor;
    friend class ProcessorNetwork;

public:
    /**
     * The property view specifies how a property should be represented
     * in the user interface. Multiple views can be combined.
     */
    enum View {
        DEFAULT =        1,
        LIGHT_POSITION = 1 << 1,
        COLOR =          1 << 2,
        SLIDER =         1 << 3,
        SPINBOX =        1 << 4
    };

    /**
     * Every property has a level of detail setting which determines, whether the property
     * should be visible in a network editing mode (=DEVELOPER) or in a user environment.
     */
    enum LODSetting {
        USER = 0,
        DEVELOPER = 1
    };

    /**
     * Constructor - sets standard-values
     *
     * @param property's identifier: Must be not empty
     *        and must be unique among all properties of a PropertyOwner
     * @param guiName textual representation of the property in the GUI
     * @param invalidationLevel the level the owner is invalidated with upon change
     */
    Property(const std::string& id, const std::string& guiName,
             Processor::InvalidationLevel invalidationLevel = Processor::INVALID_RESULT);

    virtual ~Property();

    /**
     * Returns a textual description of the property type,
     * usually corresponding to the type of the stored value.
     */
    virtual std::string getTypeString() const;

    /**
     * Returns the identifier of the property.
     */
    std::string getID() const;

    /**
     * Returns the InvalidationLevel of this property.
     *
     * @return The owner is invalidated with this InvalidationLevel upon change.
     */
    Processor::InvalidationLevel getInvalidationLevel();

    /**
     * Returns the identifier of the property preceeded by
     * its owner's name, e.g. "Background.color1".
     *
     * If the property is not assigned to an owner,
     * only its id is returned.
     *
     * @see PropertyOwner::getName
     */
    std::string getFullyQualifiedID() const;

    /**
     * Assigns the string that is to be shown
     * in the user interface.
     */
    void setGuiName(const std::string& guiName);

    /**
     * Returns the property's gui name.
     */
    std::string getGuiName() const;

    /**
     * Specifies how the property should be represented
     * in user interface.
     */
    void setViews(View views);

    /**
     * Returns the property's view flags.
     */
    View getViews() const;

    /**
     * Specifies in which environments (developer, user) the property should be shown.
     */
    void setLevelOfDetail(LODSetting lod);

    /**
     * Returns the property's level of detail.
     */
    LODSetting getLevelOfDetail() const;

    /**
     * Returns the GUI name of the property preceeded by
     * its owner's name, e.g. "Background.First Color".
     *
     * If the property is not assigned to an owner,
     * only its GUI name is returned.
     *
     * @see PropertyOwner::getName
     * @see getGuiName
     */
    std::string getFullyQualifiedGuiName() const;

    /**
     * Specifies the visibility of the property in the user interface.
     * Internally passes the visibility state to the assigned widgets.
     */
    void setVisible(bool state);

    /**
     * Returns whether the property (i.e., its widgets) is visible in the GUI.
     */
    bool isVisible() const;

    /**
     * Enables or disables all widgets of this property.
     */
    void setWidgetsEnabled(bool enabled);

    /**
     * Indicates whether the widgets of this property are enabled or disabled.
     */
    bool getWidgetsEnabled() const;

    /**
     * Sets the processor this property is assigned to.
     */
    virtual void setOwner(PropertyOwner* owner);

    /**
     * Returns the processor this property is assigned to.
     */
    PropertyOwner* getOwner() const;

    /**
     * Notifies the property that its stored value has changed.
     */
    virtual void invalidate();

    /**
     * Switch interactionmode on or off.
     *
     * @param interactionMode
     * @param source The source (usually a GUI element) that has issued the interaction mode.
     */
    void toggleInteractionMode(bool interactionmode, void* source);

 

    /**
     * Assigns the property to a property group.
     *
     * The group membership of a property has no effect on the property itself,
     * but may be considered in a GUI representation. The default group ID
     * is the empty string, indicating that the property does not belong to a group.
     */
    void setGroupID(const std::string& id);

    /**
     * Returns the id of the property group to which the property is assigned to.
     * If the property does not belong to a group, an empty string is returned.
     */
    std::string getGroupID() const;
 


 
 protected:

    /**
     * Override this method for performing initializations
     * of the property. It is usually called by the owning Processor's
     * initialize() function.
     *
     * @note All OpenGL initializations must be done here,
     *       instead of the constructor! Time-consuming operations
     *       should also happen here.
     *
     * @throw VoreenException if the initialization failed
     */
    virtual void initialize() throw (VoreenException){}

    /**
     * Override this method for performing deinitializations
     * of the property.
     *
     * @note All OpenGL deinitializations must be done here,
     *       instead of the destructor!
     *
     * @throw VoreenException if the deinitialization failed
     */
	virtual void deinitialize() throw (VoreenException){}

    /**
     * Invalidates the owner with the InvalidationLevel set in the constructor
     */
    void invalidateOwner();

    /**
     * Invalidates the owner with a given InvalidationLevel.
     *
     * @param invalidationLevel Use this InvalidationLevel to invalidate
     */
    void invalidateOwner(Processor::InvalidationLevel invalidationLevel);

    std::string id_;
    std::string guiName_;

    PropertyOwner* owner_;
    Processor::InvalidationLevel invalidationLevel_;
    bool widgetsEnabled_;
    bool visible_;
    LODSetting lod_;
    int views_;
    std::string groupId_;

 
    

private:
    

    /// Used for cycle prevention during interaction mode propagation
    bool interactionModeVisited_;

    /// Used for (de-)serializeValue methods
    bool serializeValue_;

    /// Used for cycle prevention during check whether two props are linked
    mutable bool linkCheckVisited_;

     

    /**
     * Stores the gui name that has been passed to the constructor.
     * The gui name is only serialized, if it differs from the initial one.
     */
    std::string initialGuiName_;
};

} // namespace voreen

#endif // VRN_PROPERTY_H
