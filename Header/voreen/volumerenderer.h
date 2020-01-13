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

#ifndef VRN_VOLUMERENDERER_H
#define VRN_VOLUMERENDERER_H

#include "renderprocessor.h"

#include "boolproperty.h"
#include "vectorproperty.h"
#include "floatproperty.h"
#include "volumeport.h"

#include "textureunit.h"
class misOpenglTexture;
#include "volume.h"
#include "VoreenMacroes.h"

namespace voreen {

/**
 * All processors that access volume data in shaders
 * should be derived from this base class.
 *
 * It extends the generateHeader and setGlobalShaderParameters methods
 * inherited from RenderProcessor and provides a function for passing
 * volumes to a shader. Additionally, it declares light source properties:
 * add these in your derived class' constructor to actually use them.
 *
 * @see VolumeRaycaster
 */


class VOREENEXPORTS VolumeRenderer : public RenderProcessor {
public:
    VolumeRenderer();

protected:
    /**
     * This struct contains information about a volume. It is exclusively used
     * as parameter type for the bindVolumes() function.
     */
    struct VolumeStruct {
        VolumeStruct();
        VolumeStruct(const Volume* volume, tgt::TextureUnit* texUnit,
                     const std::string& samplerIdentifier, const std::string& volumeParametersIdentifier,
                     bool applyDatasetTrafoMatrix = true, GLenum wrapMode = GL_CLAMP_TO_EDGE,
                     tgt::vec4 borderColor = tgt::vec4(0.f), GLint filterMode = GL_LINEAR);

        const Volume* volume_;     ///< the texture to be bound
        tgt::TextureUnit* texUnit_;                     ///< the texture unit to bind to
        GLenum wrapMode_;                               ///< the texture wrapping mode to set
        tgt::vec4 borderColor_;                         ///< the texture's border color
        GLint filterMode_;                              ///< the filtering mode to use for this texture
        std::string samplerIdentifier_;                 ///< the sampler by which the
                                                        ///  volume is accessed in the shader
        std::string volumeParametersIdentifier_;        ///< the identifier of the volume parameter struct
                                                        ///  for this volume in the shader
        bool applyDatasetTrafoMatrix_;                  ///< apply the volume's trafo matrix in the shader?
    };

    /**
     * Defines the 3D texture type used for volumes.
     *
     * @see RenderProcessor::generateHeader
     */
    virtual std::string generateHeader();

    /**
     * Sets the parameters of the light source.
     * The camera parameter is passed to the super class function.
     *
     * @see RenderProcessor::setGlobalShaderParameters
     */
    virtual void setGlobalShaderParameters(tgt::Shader* shader, const tgt::Camera* camera = 0);

    /**
     * This function binds the volume textures used by the volume renderer and passes the
     * corresponding samplers (texture units) to the shader.
     * \note This function also sets additional meta data like the volume's dimensions and spacing.
     *       For this reason, every volume renderer that uses a volume texture must call this function
     *       for all volumes accessed during a rendering pass. Do not bypass this function by binding
     *       volume textures directly unless you know exactly what you are doing!
     * @param shader the shader that performs the volume rendering
     * @param volumes vector of the volumes to bind
     * @param camera the scene's camera position. Is transformed to volume object coordinates for lighting calculations.
     * @param lightPosition the scene's light position. Is transformed to volume object coordinates for lighting calculations.
     */
    virtual void bindVolumes(tgt::Shader* shader, const std::vector<VolumeStruct> &volumes,
                             const tgt::Camera* camera = 0, const tgt::vec4& lightPosition = tgt::vec4(0.f));

	 bool CheckTeturesId( const std::vector<VolumeStruct> &volumes );
 
    /// The position of the light source used for lighting calculations in world coordinates
    FloatVec4Property lightPosition_;

    /// The light source's ambient color according to the Phong lighting model
    FloatVec4Property lightAmbient_;
    /// The light source's diffuse color according to the Phong lighting model
    FloatVec4Property lightDiffuse_;
    /// The light source's specular color according to the Phong lighting model
    FloatVec4Property lightSpecular_;

    /// The light source's attenuation factors (x = constant, y = linear, z = quadratic)
    FloatVec3Property lightAttenuation_;
    /// Apply light attenuation?
    BoolProperty applyLightAttenuation_;
    /// The ambient material color according to the Phong lighting model

    FloatVec4Property materialAmbient_;
    /// The diffuse material color according to the Phong lighting model
    FloatVec4Property materialDiffuse_;
    /// The specular material color according to the Phong lighting model
    FloatVec4Property materialSpecular_;

    /// The material's specular exponent according to the Phong lighting model
    FloatProperty materialShininess_;

    static const std::string loggerCat_;
	static  tgt::GpuCapabilities*   gpuCapInstance;
};

} // namespace voreen

#endif // VRN_VOLUMERENDERER_H
