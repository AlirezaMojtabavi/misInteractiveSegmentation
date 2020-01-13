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

#ifndef VRN_MULTISCALE_H
#define VRN_MULTISCALE_H

#include "voreen/modules/base/processors/utility/scale.h"

namespace voreen {

/**
 * Performs a scaling.
 */
class MultiScale : public ScalingProcessor {
public:
    MultiScale();
    ~MultiScale();

    virtual std::string getCategory() const { return "Utility"; }
    virtual std::string getClassName() const { return "MultiScale"; }
    virtual Processor::CodeState getCodeState() const { return CODE_STATE_STABLE; } ///2.0
    virtual std::string getProcessorInfo() const;
    virtual Processor* create() const {return new MultiScale();}
    virtual void initialize() throw (VoreenException);

    virtual bool isReady() const;
    void process();

    virtual void textureContainerChanged(RenderPort* p);
    virtual void portResized(RenderPort* p, tgt::ivec2 newsize);

    tgt::ivec2 selectBest();
protected:
    IntOptionProperty scalingMode1_;
    IntOptionProperty scalingMode2_;
    IntOptionProperty scalingMode3_;
    IntOptionProperty scalingMode4_;

    StringOptionProperty selectionMode_;

    RenderPort outport1_;
    RenderPort outport2_;
    RenderPort outport3_;
    RenderPort outport4_;
};


} // namespace voreen

#endif //VRN_MULTISCALE_H
