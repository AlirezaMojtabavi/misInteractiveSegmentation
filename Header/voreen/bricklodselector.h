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

#ifndef VRN_BRICKLODSELECTOR_H
#define VRN_BRICKLODSELECTOR_H

#include "voreen/core/datastructures/volume/bricking/brickinginformation.h"

namespace voreen {

/**
 * This class is the superclass to all classes that implement
 * the selection of lods (level of details) for the VolumeBricks.
 * This selection can depend on the camera position, or some kind
 * of error calculation for example. The available resolutions the bricks
 * can be assigned must be set in brickingInformation_
 */
class BrickLodSelector {
public:

    BrickLodSelector(BrickingInformation& brickingInformation);

    virtual ~BrickLodSelector() {}

    /**
     * Assigns a level of detail to every VolumeBrick in the brickingInformation.volumeBricks
     * vector.
     */
    virtual void selectLods() = 0;

protected:
    BrickingInformation& brickingInformation_;

private:

}; //end of class

} //namespace


#endif // VRN_BRICKLODSELECTOR_H
