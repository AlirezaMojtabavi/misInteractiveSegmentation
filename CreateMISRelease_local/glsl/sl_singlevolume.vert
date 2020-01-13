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

// uniforms needed for clipping code
uniform int frontIdx_;
uniform vec3 vecView_;
uniform float camDistance_;
uniform float dPlaneStart_;
uniform float dPlaneIncr_;
uniform int[64] nSequence_;
uniform vec3[8] vecVertices_;
uniform int[24] v1_;
uniform int[24] v2_;

void main() {
    vec3 position = vec3(0.0);
    float dPlane = dPlaneStart_ + gl_Vertex.y * dPlaneIncr_;

    for (int e=0; e<4; e++) {
        int vidx1 = nSequence_[int(frontIdx_*8 + v1_[int(gl_Vertex.x*4 + e)])];
        int vidx2 = nSequence_[int(frontIdx_*8 + v2_[int(gl_Vertex.x*4 + e)])];
        vec3 vecV1 = vecVertices_[vidx1];
        vec3 vecV2 = vecVertices_[vidx2];
        vec3 vecDir = vecV2-vecV1;
        float denom = dot(vecDir,vecView_);

        if (denom == 0.0)
            continue;

        float lambda =  (dPlane-dot(vecV1,vecView_))/denom;
        if (lambda >= 0.0 && lambda <= 1.0) {
            position = vecV1 + lambda * vecDir;
            break;
        }
    }
    gl_TexCoord[0] = vec4(0.5*position + 0.5, 1.0);
    gl_Position =  gl_ModelViewProjectionMatrix * vec4(position, 1.0);
}
