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

#ifndef VRN_RENDERTARGET_H
#define VRN_RENDERTARGET_H

#include "tgt/framebufferobject.h"

namespace tgt {
class __declspec( dllexport ) RenderTarget {
public:
    RenderTarget();
    virtual ~RenderTarget();

    //void initialize(GLint internalColorFormat = GL_RGBA16, GLint internalDepthFormat = GL_DEPTH_COMPONENT24);
	void initialize(GLint internalColorFormat , GLint internalDepthFormat ,	tgt::ivec3 size);
    void deinitialize();

    void activateTarget(const std::string& debugLabel = "");
    void deactivateTarget();
    bool isActive() const;

    void bindColorTexture();
    void bindDepthTexture();

    const tgt::Texture* getColorTexture() const { return colorTex_; }
    const tgt::Texture* getDepthTexture() const { return depthTex_; }

    tgt::Texture* getColorTexture() { return colorTex_; }
    tgt::Texture* getDepthTexture() { return depthTex_; }

    //Get the color at position pos. This method activates the RenderTarget!
    tgt::vec4 getColorAtPos(tgt::ivec2 pos);

    tgt::ivec2 getSize() const;
    void resize(tgt::ivec2 newsize);

    //these are just for Debugging purposes:
    std::string getDebugLabel() { return debugLabel_; }
    void setDebugLabel(const std::string& debugLabel) { debugLabel_ = debugLabel; }

    void increaseNumUpdates() { numUpdates_++; }
    int getNumUpdates() { return numUpdates_; }

protected:
    tgt::FramebufferObject* fbo_;

    tgt::Texture* colorTex_;
    tgt::Texture* depthTex_;

    std::string debugLabel_;
    int numUpdates_;

    static const std::string loggerCat_;
	tgt::GpuCapabilities*   gpuCapInstance;
};
}   // namespace

#endif  // VRN_RENDERTARGET_H
