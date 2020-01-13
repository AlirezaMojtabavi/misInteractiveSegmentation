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

#ifndef VRN_VOLUMESLICER_H
#define VRN_VOLUMESLICER_H

#include "volumerenderer.h"

#include "floatproperty.h"
#include "transfuncproperty.h"
#include "cameraproperty.h"

namespace voreen {

/**
 * A VolumeRenderer that uses slicing to produce pictures.
 */
class VolumeSlicer : public VolumeRenderer {
public:
    /**
     * Constructor.
     */
    VolumeSlicer();

    virtual ~VolumeSlicer();

    virtual void initialize() throw (VoreenException);

protected:

    FloatProperty samplingRate_;
    TransFuncProperty transferFunc_;  ///< the property that controls the transfer-function
    CameraProperty camera_;           ///< the camera used for lighting calculations

    // variables needed for clipping
    tgt::vec3* cubeVertices_;
    int* nSeq_; // permutation indice�s
    int* v1_; // edge start indices
    int* v2_; // edge end indices

    static const std::string loggerCat_; ///< category used in logging
};

} // namespace voreen

#endif // VRN_VOLUMESLICER_H
