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

#ifndef VRN_VOLUMEOPERATORINTENSITYMASK_H
#define VRN_VOLUMEOPERATORINTENSITYMASK_H

#include "tgt/vector.h"
#include "voreen/core/datastructures/volume/volumeoperator.h"

namespace voreen {

/**
 * A VolumeOperator which returns all voxel positions having values within the
 * thresholds being passed to the ctor.
 * Note that this currently works only for volumes containing intensities, i.e.
 * the template parameter T for the underlying VolumeAtomic<T> may not be of any type
 * which cannot be compared to or casted to float.
 */
class VolumeOperatorIntensityMask : public VolumeOperatorUnary<VolumeOperatorIntensityMask> {
friend class VolumeOperatorUnary<VolumeOperatorIntensityMask>;

public:
    VolumeOperatorIntensityMask(const tgt::vec2& thresholds);

private:
    template<typename T>
    VolumeAtomic<bool>* apply_internal(const VolumeAtomic<T>* const volume) const;

    template<typename S>
    VolumeAtomic<bool>* apply_internal(const VolumeAtomic<tgt::Vector2<S> >* const) const {
        // method currently not really implemented because it is not required...
        return 0;
    }

    template<typename S>
    VolumeAtomic<bool>* apply_internal(const VolumeAtomic<tgt::Vector3<S> >* const) const {
        // method currently not really implemented because it is not required...
        return 0;
    }

    template<typename S>
    VolumeAtomic<bool>* apply_internal(const VolumeAtomic<tgt::Vector4<S> >* const) const {
        // method currently not really implemented because it is not required...
        return 0;
    }

    tgt::vec2 thresholds_;
};

template<typename T>
VolumeAtomic<bool>* VolumeOperatorIntensityMask::apply_internal(const voreen::VolumeAtomic<T>* const volume) const
{
    if (volume == 0)
        return 0;

    const tgt::ivec3 dim = volume->getDimensions();
    const T* const data = volume->voxel();

    VolumeAtomic<bool>* subVolume = new VolumeAtomic<bool>(dim);
    bool* const binVoxels = subVolume->voxel();

    for (size_t i = 0; i < volume->getNumVoxels(); ++i) {
        float value = static_cast<float>(data[i]);
        if ((value >= thresholds_.x) && (value <= thresholds_.y))
            binVoxels[i] = true;
        else
            binVoxels[i] = false;
    }   // for (i
    return subVolume;
}

}   // namespace

#endif
