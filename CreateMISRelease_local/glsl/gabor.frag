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

#include "modules/mod_sampler2d.frag"

uniform SAMPLER2D_TYPE colorTex_;
uniform SAMPLER2D_TYPE depthTex_;
uniform TEXTURE_PARAMETERS texParams_;

uniform float orientation_;
uniform float wavelength_;
uniform float offset_;
uniform float sigma_;
uniform float aRatio_;

float gabor(float x, float y, float lambda, float theta, float psi, float phi, float gamma) {
    float x_ = x*cos(theta)+y*sin(theta);
    float y_ = -x*sin(theta)+y*cos(theta);

    return (exp(-(((x_*x_)+(gamma*gamma*y_*y_))/(2*phi*phi)))*cos((2*3.141*x_/lambda)+psi));
}

void main() {
    vec2 p = (gl_FragCoord.xy) * screenDimRCP_;
    p -= 0.5;
    p *= 2.0;
    float g = gabor(p.x, p.y, wavelength_, orientation_, offset_, sigma_, aRatio_);
    g += 1.0;
    g /= 2.0;
    FragData0 = vec4(vec3(g), 1.0);
    gl_FragDepth = textureLookup2Dnormalized(depthTex_, texParams_, p).z;
}
