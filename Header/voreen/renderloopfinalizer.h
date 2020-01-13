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

#ifndef VRN_RENDERLOOPFINALIZER_H
#define VRN_RENDERLOOPFINALIZER_H

#include "voreen/core/processors/renderprocessor.h"

namespace voreen {

/**
 * In combination with RenderLoopInitiator, this class is used to define render loops.
 */
class RenderLoopFinalizer : public RenderProcessor {
public:
    RenderLoopFinalizer();
    virtual Processor* create() const;

    virtual std::string getCategory() const { return "Utility"; }
    virtual std::string getClassName() const { return "RenderLoopFinalizer"; }
    virtual CodeState getCodeState() const { return CODE_STATE_STABLE; }
    virtual std::string getProcessorInfo() const;

    virtual bool isUtility() const { return true; }
    virtual bool isReady() const;

protected:
    virtual void process();
    virtual void initialize() throw (VoreenException);
    virtual void deinitialize() throw (VoreenException);

    tgt::Shader* shaderPrg_;
    RenderPort inport_;
    RenderPort outport_;
    RenderPort loopOutport_;
};

}

#endif //VRN_RENDERLOOPFINALIZER_H
