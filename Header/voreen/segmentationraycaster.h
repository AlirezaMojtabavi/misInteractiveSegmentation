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

#ifndef VRN_SEGMENTATIONRAYCASTER_H
#define VRN_SEGMENTATIONRAYCASTER_H

#include "voreen/core/processors/volumeraycaster.h"

#include "voreen/core/properties/cameraproperty.h"
#include "voreen/core/properties/transfuncproperty.h"

#include "voreen/core/ports/volumeport.h"

#include <map>

namespace voreen {

/**
 * Raycasting of a segmented data set.
 */
class SegmentationRaycaster : public VolumeRaycaster {
public:
    SegmentationRaycaster();
    virtual ~SegmentationRaycaster();
    virtual Processor* create() const;

    virtual std::string getClassName() const  { return "SegmentationRaycaster"; }
    virtual std::string getCategory() const   { return "Raycasting"; }
    virtual CodeState getCodeState() const    { return CODE_STATE_STABLE; }
    virtual std::string getProcessorInfo() const;

    virtual bool isReady() const;

    TransFuncProperty& getTransFunc();

    const PropertyVector& getSegmentationTransFuncs();

    BoolProperty& getApplySegmentationProp();

protected:
    virtual void process();
    virtual void initialize() throw (VoreenException);
    virtual void deinitialize() throw (VoreenException);

    virtual void loadShader();
    virtual std::string generateHeader(VolumeHandle* volumeHandle = 0);
    virtual void compile(VolumeHandle* volumeHandle);

private:
    tgt::Shader* raycastPrg_;          ///< The shader program used by this raycaster.

    // callbacks for gui changes
    void applySegmentationChanged();
    void segmentationTransFuncChanged(int segment);
    void transFuncResolutionChanged();

    // writes the contents of the transferFunc_ prop into the 2D transfer function at the position
    // corresponding to the passed segment id
    void updateSegmentationTransFuncTex(int segment);

    // create the segmentation transfer function
    void createSegmentationTransFunc();
    // initializes the segmentation transfunc texture from the segmentation transfer functions
    void initializeSegmentationTransFuncTex();

    CameraProperty camera_;

    // The transfer function property used in non-segmentation mode
    TransFuncProperty transferFunc_;

    // Segmentation transfuncs used in segmentation mode
    PropertyVector* segmentTransFuncs_;

    // 2D texture that contains the segments' 1D transfer functions in row-order
    tgt::Texture* segmentationTransFuncTex_;
    // determines whether the segmentation transfunc has to be uploaded before next use
    bool segmentationTransFuncTexValid_;

    VolumeHandle* segmentationHandle_;

    BoolProperty applySegmentation_;
    IntOptionProperty transFuncResolutionProp_;
    std::vector<std::string> transFuncResolutions_;
    int lastSegment_;

    StringOptionProperty compositingMode1_;    ///< What compositing mode should be applied for second outport
    StringOptionProperty compositingMode2_;    ///< What compositing mode should be applied for third outport

    bool destActive_[2];

    VolumePort volumeInport_;
    VolumePort segmentationInport_;
    RenderPort entryPort_;
    RenderPort exitPort_;

    RenderPort outport1_;
    RenderPort outport2_;
    RenderPort outport3_;
    PortGroup portGroup_;
};

} // namespace

#endif // VRN_SEGMENTATIONRAYCASTER_H
