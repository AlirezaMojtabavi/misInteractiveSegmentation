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

#ifndef VRN_RENDERPORT_H
#define VRN_RENDERPORT_H

#include "port.h"
#include "textureunit.h"
#include "tgt_gl.h"
#include "gpucapabilities.h"
#include "texture.h"
#include "VoreenMacroes.h"
 
 
namespace tgt {
    class FramebufferObject;
    class Shader;
	class RenderTarget;
}

namespace voreen {





class VOREENEXPORTS RenderPort : public Port {

    friend class RenderProcessor;
	friend class MeshEntryExitPoints;
    friend class NetworkEvaluator;

public:
    RenderPort(PortDirection direction, const std::string& name, bool allowMultipleConnections = false,
               Processor::InvalidationLevel invalidationLevel = Processor::INVALID_RESULT,
               GLint internalColorFormat=GL_RGBA16, GLint internalDepthFormat=GL_DEPTH_COMPONENT24);
    virtual ~RenderPort();

    /**
     * @brief Activates the outport's RenderTarget, so that all subsequent rendering operations
     * are performed on this target. The target has to be deactivated after all rendering operations
     * have been finished or before any other RenderPort is activated.
     *
     * @note Must not be called on an inport.
     *
     * @see deactivateTarget
     *
     * @param DEBUGLOGGINGLabel Additional description to be presented in the GUI.
     */
    void activateTarget(const std::string& DEBUGLOGGINGLabel = "");

    /**
     * Deactivates the outport's RenderTarget after rendering
     * has been finished.
     *
     * @note Must not be called on an inport.
     */
    void deactivateTarget();

    /**
     * Clears the contents of an activated outport's RenderTarget,
     * by calling glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT).
     *
     * @note May only be called on an activated outport.
     */
    void clearTarget();

    /**
     * Returns true, if the port is connected and (if it is an inport) has a valid rendering.
     */
    virtual bool isReady() const;

    /**
     * Returns true, if the port is an outport and stores a valid rendering,
     * or if is an inport, and its (first) connected outport stores a valid rendering.
     */
    bool hasValidResult() const;

    /**
     * Returns the dimensions of the associated RenderTarget.
     *
     * If no RenderTarget is associated, ivec2(0) is returned.
     */
    tgt::ivec2 getSize() const;

    /**
     * Returns true, if the associated RenderTarget is currently active.
     *
     * @see activateTarget, deactivateTarget
     */
    bool isActive() const;

    /**
     * Returns the port's RenderTarget, may be null.
     *
     * If this function is called on an outport, its own RenderTarget is returned.
     * If it is called on an inport, the RenderTarget of the (first) connected outport is returned.
     *
     * @see hasRenderTarget
     */
    tgt::RenderTarget* getRenderTarget();

    /// @overload
    const tgt::RenderTarget* getRenderTarget() const;

    /**
     * Returns the associated color texture.
     *
     * @return The color texture or null, if none is present.
     */
    const tgt::Texture* getColorTexture() const;

    /// @overload
    tgt::Texture* getColorTexture();

    /**
     * Returns the associated depth texture.
     *
     * @return The depth texture or null, if none is present.
     */
    const tgt::Texture* getDepthTexture() const;

    /// @overload
    tgt::Texture* getDepthTexture();

    /**
     * Returns true, if a RenderTarget is assigned to the RenderPort.
     *
     * If this function is called on an inport, it checks whether
     * its (first) connected outport has a RenderTarget.
     */
    bool hasRenderTarget() const;

    /**
     * Resizes the associated RenderTarget to the passed dimensions.
     *
     * If this function is called on an inport, the call is propagated to
     * all connected outports.
     */
    void resize(const tgt::ivec2& newsize);

    /**
     * Re-create and initialize the outport's RenderTarget with the given format.
     * The RenderTarget's resolution is preserved.
     *
     * @note This function must not be called on an inport.
     */
    void changeFormat(GLint internalColorFormat, GLint internalDepthFormat=GL_DEPTH_COMPONENT24);

    /**
     * Flags the outport's rendering as valid.
     *
     * @note It is normally not necessary to call this function,
     *  since it is called implicitly by activateTarget/deactivateTarget.
     *
     * @note Must not be called on an inport.
     */
    void validateResult();

    /**
     * Flags the outport's rendering as invalid.
     *
     * @note It is normally not necessary to call this function,
     *  since it is called implicitly.
     *
     * @note Must not be called on an inport.
     */
    void invalidateResult();

    /**
     * @brief Passes the assigned textures' TEXTURE_PARAMETERS struct to the passed shader.
     *  Needs to be called for each inport whose textures are to be accessed by the shader.
     *
     * @param uniform The name of the struct used in the shader.
     */
    void setTextureParameters(tgt::Shader* shader, const std::string& uniform);

    /**
     * Bind the color texture of this port's RenderTarget to the currently active texture unit.
     */
    void bindColorTexture();

    /**
     * Bind the color texture of this port's RenderTarget to a specific texture unit.
     *
     * @param texUnit The texture unit to activate before binding.
     */
    



    /**
     * Bind the depth texture of this port's RenderTarget to the currently active texture unit.
     */
    void bindDepthTexture();

    /**
     * Bind the depth texture of this port's RenderTarget to a specific texture unit.
     *
     * @param texUnit The texture unit to activate before binding.
     */
    

  

    /**
     * Convenience function, calling bindColorTexture(colorUnit) and bindDepthTexture(depthUnit).
     */
    void bindTextures(GLint colorUnit, GLint depthUnit);

    /// @overload
    void bindTextures(tgt::TextureUnit& colorUnit, tgt::TextureUnit& depthUnit);

    /**
     * Writes the currently stored rendering to an image file.
     *
     * @note This function requires Voreen to be built with DevIL support.
     *
     * @param filename the filename of the output file. Must have an
     *      extension known by the DevIL library. *.jpg and *.png
     *      should work fine.
     *
     * @throw VoreenException if the image saving failed
     */
    void saveToImage(const std::string &filename) throw (VoreenException);

    /**
     * \brief Returns the current content of the color buffer, converted
     * to RGBA format. The data type is specified as template parameter.
     *
     * @tparam T Specifies the data type of the returned image data.
     *         Supported types: uint8_t, uint16_t, float
     *
     * @note Releasing the allocated memory is up to the caller!
     *
     * @throw VoreenException if the color buffer content could not be read
     *        or converted
     */
    template<typename T>
    tgt::Vector4<T>* readColorBuffer() throw (VoreenException);

    // administrative stuff regarding RenderPort size origins.
    void sizeOriginChanged(void* so);
    void* getSizeOrigin() const;
    virtual bool testConnectivity(const Port* inport) const;
    bool doesSizeOriginConnectFailWithPort(Port* inport) const;
    virtual void initialize() throw (VoreenException);

protected:
    /**
     * Assigns the passed RenderTarget to this RenderPort.
     *
     * Is called by the NetworkEvaluator.
     */
    virtual void setRenderTarget(tgt::RenderTarget* renderTarget);

    /**
     * Initializes the RenderTarget, if the port is an outport.
     *
     * @see Port::initialize
     */

    /**
     * Deinitializes the RenderTarget, if the port is an outport.
     *
     * @see Port::deinitialize
     */
    virtual void deinitialize() throw (VoreenException);

    /**
     * Additionally propagates the connected port's size origin.
     *
     * @see Port::connect
     */
    virtual bool connect(Port* inport);

    /**
     * Additionally propagates itself as size origin.
     *
     * @see Port::disconnect
     */
    virtual void disconnect(Port* other);

    /**
     * Additionally checks, if the passed processor is of type RenderProcessor.
     *
     * @see Port::setProcessor
     */
    virtual void setProcessor(Processor* p);

    void setRenderTargetSharing(bool sharing);

    bool getRenderTargetSharing() const;

private:
    tgt::RenderTarget* renderTarget_;

    bool validResult_;
    tgt::ivec2 size_; //neccessary for inports
    void* sizeOrigin_;

    GLint internalColorFormat_;
    GLint internalDepthFormat_;

    bool renderTargetSharing_;

    static const std::string loggerCat_; ///< category used in logging
 };

template<typename T>
tgt::Vector4<T>* voreen::RenderPort::readColorBuffer() throw (VoreenException) {
    if (!getColorTexture()) {
        throw VoreenException("RenderPort::readColorBuffer() called on an empty render port");
    }

    // determine OpenGL data type from template parameter
    GLenum dataType;
    if (typeid(T) == typeid(uint8_t))
        dataType = GL_UNSIGNED_BYTE;
    else if (typeid(T) == typeid(uint16_t))
        dataType = GL_UNSIGNED_SHORT;
    else if (typeid(T) == typeid(float))
        dataType = GL_FLOAT;
    else
        throw VoreenException("RenderPort::readColorBuffer(): unsupported data type. "
            "Expected: uint8_t, uint16_t, float");

    GLubyte* pixels = 0;
    try {
        pixels = getColorTexture()->downloadTextureToBuffer(GL_RGBA, dataType);
    }
    catch (std::bad_alloc&) {
        throw VoreenException("RenderPort::readColorBuffer(): bad allocation");
    }
    LGL_ERROR;

    if (pixels)
        return reinterpret_cast<tgt::Vector4<T>*>(pixels);
    else
        throw VoreenException("RenderPort::readColorBuffer(): failed to download texture");
}


//------------------------


/**
 * @brief This class groups RenderPorts to allow easy rendering to multiple targets.
 */


class VOREENEXPORTS PortGroup {
public:
    /**
     * @param ignoreConnectivity If this is true all ports are attached to the FBO, otherwise only the connected ones.
     */
    PortGroup(bool ignoreConnectivity = true);
    ~PortGroup();

    /// Initializes the FBO
    void initialize();

    /// Deinitializes the FBO
    void deinitialize();

    ///Add or remove a port to/from the group.
    void addPort(RenderPort* rp);
    void addPort(RenderPort& rp);
    void removePort(RenderPort* rp);
    void removePort(RenderPort& rp);
    // Check if the group contains the specified port.
    bool containsPort(RenderPort* rp);
    bool containsPort(RenderPort& rp);

    /**
     * @brief Start rendering to all attached ports.
     *
     * @param DEBUGLOGGINGLabel @see RenderPort::activateTarget
     */
    void activateTargets(const std::string& DEBUGLOGGINGLabel = "");

    void deactivateTargets();

    /**
     * Clears the contents of the associated RenderPorts,
     * by calling glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT).
     *
     * @note May only be called on an activated port group.
     */
    void clearTargets();

    ///Resize all attached ports.
    void resize(const tgt::ivec2& newsize);

    /**
     * @brief Defines OP0, OP1, ... OPn to address targets in shader.
     *
     * Example:
     * CPP:
     * addPort(p1); addPort(p2); addPort(p3);
     *
     * glsl:
     * FragData0 = vec4(1.0); //write to p1
     * FragData1 = vec4(1.0); //write to p2
     * FragData2 = vec4(1.0); //write to p3
     *
     * The defines can also be used to test if a port is connected:
     * #ifdef OP0
     *    FragData0 = result;
     * #endif
     *
     * @return A string containing the defines.
     */
    std::string generateHeader(tgt::Shader* shader);

    /**
     * Re-attach all rendertargets to the FBO.
     * If ignoreConnectivity is true only connected ports are attached.
     */
    void reattachTargets();
protected:

    std::vector<RenderPort*> ports_;
    tgt::FramebufferObject* fbo_;
    bool ignoreConnectivity_;
};


} // namespace

#endif // VRN_RENDERPORT_H
