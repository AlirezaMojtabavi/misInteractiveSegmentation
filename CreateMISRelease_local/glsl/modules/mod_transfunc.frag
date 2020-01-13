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

/**
 * This module contains all functions which can be used for performing
 * classifications of a voxel within a raycaster.
 * The functions below are referenced by RC_APPLY_CLASSIFICATION which
 * is used in the raycaster fragment shaders.
 */

#if defined(TF_SAMPLER_TYPE)
    uniform TF_SAMPLER_TYPE transferFunc_;
#endif

vec4 applyTF(sampler1D transfunc, float intensity) {
    #if defined(GLSL_VERSION_130)
        return texture(transfunc, intensity);
    #else
        return texture1D(transfunc, intensity);
    #endif
}

vec4 applyTF(sampler1D transfunc, vec4 intensity) {
    #if defined(GLSL_VERSION_130)
        return texture(transfunc, intensity.r);
    #else
        return texture1D(transfunc, intensity.r);
    #endif
}

vec4 applyTF(sampler2D transfunc, float intensity, float gradientMagnitude) {
    #if defined(GLSL_VERSION_130)
        return texture(transfunc, vec2(intensity, gradientMagnitude));
    #else
        return texture2D(transfunc, vec2(intensity, gradientMagnitude));
    #endif
}

vec4 applyTF(sampler2D transfunc, vec4 intensityGradient) {
    #if defined(GLSL_VERSION_130)
        return texture(transfunc, vec2(intensityGradient.r, length(intensityGradient.rgb)));
    #else
        return texture2D(transfunc, vec2(intensityGradient.r, length(intensityGradient.rgb)));
    #endif
}


