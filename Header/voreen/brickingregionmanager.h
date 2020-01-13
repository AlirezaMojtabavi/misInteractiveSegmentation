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

#ifndef VRN_BRICKINGREGIONMANAGER_H
#define VRN_BRICKINGREGIONMANAGER_H

#include "voreen/core/datastructures/volume/bricking/brickingregion.h"

namespace voreen {

    /**
    * This class manages the BrickingRegions.
    */
    class BrickingRegionManager {
    public:

        /**
        * @param brickingInformation    Struct containing all the necessary
        *                               information about bricking.
        */
        BrickingRegionManager(BrickingInformation& brickingInformation);

        ~BrickingRegionManager();

        /**
        * Adds a BrickingRegion to the BrickingRegionManagers control.
        */
        void addRegion(BrickingRegion* region);

        /**
        * Removes a region from the BrickingRegionManager.
        */
        void deleteRegion(BrickingRegion* region);

        /**
        * Remives all regions with the given priority from the BrickingRegionManager.
        */
        void deleteRegions(int priority);

        /**
        * Returns all BrickingRegions.
        */
        std::vector<BrickingRegion*> getBrickingRegions();

        /**
        * Returns all bricks that are not inside any region.
        */
        std::vector<Brick*> getBricksWithoutRegion();

    protected:

        /**
        * Removes all bricks in the region from the vector that stores the bricks
        * that don't have a region.
        */
        void removeBricksFromVector(BrickingRegion* region);

        /**
        * Vector holding all regions together with their priorities.
        */
        std::vector<BrickingRegion*> brickingRegions_;

        /**
        * Struct holding all the information necessary for bricking.
        */
        BrickingInformation& brickingInformation_;

        /**
        * Vector holding all bricks that are not inside any region.
        */
        std::vector<Brick*> bricksWithoutRegion_;

    private:

    };
}


#endif
