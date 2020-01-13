

#pragma once

#include <string>
#include "tgt/config.h"
#include "tgt/tgt_gl.h"
#include "tgt/vector.h"
#include "textureunit.h"
#include "tgtMacroHeader.h"

namespace tgt {

/**
 * OpenGL Texture
 */

/** SR-
 * IMPORTANT NOTE : this class should not have "setID" function!!
 */
class TGTLIBMISDLLEXPORT Texture {
public:
    friend class TextureManager;
    friend class TextureReader;

    enum Filter {
        NEAREST,
        LINEAR,
        MIPMAP,
        ANISOTROPIC
    };

    enum Wrapping {
        REPEAT = GL_REPEAT,
        CLAMP = GL_CLAMP,
        CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
        CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
        MIRRORED_REPEAT = GL_MIRRORED_REPEAT
    };
    
    Texture()
        : priority_(-1.f), pixels_(0), id_(0)
    {}

    //FIXME: these ctors are ambiguous due to the default params, you need to specify all
    //       arguments or the compile won't know which one you mean. joerg

    /**
     * Without data and internalformat argument, type_ is calculated by
     * dimensions and a new chunk of data will be allocated on the heap.
     */
    Texture(const tgt::ivec3& dimensions, GLint format = GL_RGBA,
            GLenum dataType = GL_UNSIGNED_BYTE, Filter filter = LINEAR,
            bool textureRectangle = false);

    /**
     * Without data and with internalformat argument, type_ is calculated by
     * dimensions and a new chunk of data will be allocated on the heap.
     */
    Texture(const tgt::ivec3& dimensions, GLint format, GLint internalformat,
            GLenum dataType  = GL_UNSIGNED_BYTE, Filter filter = LINEAR,
            bool textureRectangle = false);

    /**
     * With data and without internalformat argument, type_ is calculated by
     * dimensions and no new chunk of data will be allocated on the heap.
     */
    Texture(GLubyte* data, const tgt::ivec3& dimensions, GLint format = GL_RGBA,
            GLenum dataType = GL_UNSIGNED_BYTE, Filter filter = LINEAR,
            bool textureRectangle = false);

    /**
     * With data and internalformat argument, type_ is calculated by
     * dimensions and no new chunk of data will be allocated on the heap.
     */
    Texture(GLubyte* data, const tgt::ivec3& dimensions, GLint format, GLint internalformat,
            GLenum dataType  = GL_UNSIGNED_BYTE, Filter filter = LINEAR,
            bool textureRectangle = false);

    /**
    * The destructor deletes the Texture in OpenGL.
    * Handled by the texturemanager!
    */
    virtual ~Texture();

    /// allocates an appropriate buffer for the texture
    void alloc() {
        arraySize_ = hmul(dimensions_) * bpp_;
        pixels_ = new GLubyte[arraySize_];
    }

    /// destroys the buffer for the texture and sets arraySize_ to zero
    void destroy();

    /// calculates the bytes per pixel from format dataType and dataType
    static int calcBpp(GLint format, GLenum dataType);

    /// calculates the bytes per pixel from the internal format
    static int calcBpp(GLint internalformat);

	///calculates size on the GPU (using internalformat)
	int getSizeOnGPU() const;

    /**
     * calculates the type_ (GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D or GL_TEXTURE_RECTANGLE_ARB) from
     * dimensions_
     *
     * @param textureRectangle Determines, wether texture should be a texture rectangle
     *      GL_TEXTURE_RECTANGLE_ARB
    */
    GLenum calcType(bool textureRectangle = false);

    /**
     * Bind the texture to the active texture unit and target.
     *
     * Note: This does not enable texturing (use enable()).
     */
    void bind() const;

    /**
     * Enable texturing on the active texture unit.
     */
    void enable() const
    {
        glEnable(type_);
    }

    /**
     * Disable texturing on the active texture unit
     */
    void Disable() const
    {
        glDisable(type_);
    }

    /**
    *   Return OpenGL texture ID
    */
    GLuint getId() const;

    /**
    *   Set OpenGL texture ID.
    */
 
    /**
    *   Generate OpenGL texture ID
    *   @return The generated ID
    */
    GLuint generateId();
  
    std::string getName() const { return name_; }
    void setName(const std::string& name) { name_ = name; }

    /**
    *   Returns type of the texture (GL_TEXTURE_1D...3D, GL_TEXTURE_RECTANGLE_ARB)
    */
    GLenum getType() const { return type_; }

    tgt::ivec3 getDimensions() const { return dimensions_;}
    int getWidth() const { return dimensions_.x; };
    int getHeight() const { return dimensions_.y; }
    int getDepth() const { return dimensions_.z; }
    GLint getFormat() const { return format_; }
    GLint getInternalFormat() const { return internalformat_; }
    Filter getFilter() const { return filter_; }
    GLenum getDataType() const { return dataType_; }
    size_t getArraySize() const { return arraySize_; }

    void setDimensions(tgt::ivec3 dimensions) { dimensions_ = dimensions; }
    void setBpp(GLubyte bpp) { bpp_ = bpp; }
    void setFormat(GLint format) { format_ = format; }
    void setInternalFormat(GLint internalformat) { internalformat_ = internalformat; }
    void setType(GLenum type) { type_ = type; }
    void setDataType(GLenum dataType) { dataType_ = dataType; }

    GLubyte* getPixelData() { return pixels_; }
    const GLubyte* getPixelData() const { return pixels_; }
    void setPixelData(GLubyte* pixels)
    {
        pixels_ = pixels;
        arraySize_ = pixels ? hmul(dimensions_) * bpp_ : 0;
    }

    /**
    *   Returns the Bytes Per Pixel used,
    *   usually 3 or 4 for 24/32 bits per pixel.
    */
    GLubyte getBpp() const { return bpp_; }

    /**
    *   Set Priority of this texture in GL
    *   @param p Priority, [0...1]
    */
    void setPriority(GLclampf p)
    {
        glPrioritizeTextures(1, &id_, &p);
    }

    /**
    *   Returns current Priority, -1 if not yet set
    */
    GLclampf getPriority() const { return priority_; }

    /**
    *   Check if texture is in resident GL memory
    */
    bool isResident() const
    {
        GLboolean resident;
        return glAreTexturesResident(1, &id_, &resident) == GL_TRUE;
    }

    /**
     *   Sets Filtering for Texture. Binds the texture.
     */
    void setFilter(Filter filter);

    /**
     * Applies the stored filter once again. Binds the texture.
     */
   virtual void applyFilter();

    /// Set texture wrapping mode. Binds the texture.
    void setWrapping(Wrapping w);

    /// Applies the textur wrapping mode once againg. Binds the texture.
    void applyWrapping();
    
    Wrapping getWrapping() const { return wrapping_; }

    /**
     * Upload Texture to graphics-card. Binds the texture.
     * 
     * type_, format_, internalformat_, dimensions, dataType_ and the pixels_ pointer have to
     * be set before calling this method.
     */
    void uploadTexture();
	virtual void uploadTexture(double shift, double scale);
    /**
     * Download Texture from graphics-card. Binds the texture.
     *
     * type_, format_, dimensions, dataType_ and the pixels_ pointer have to be set before
     * calling this method! Pixels will be allocated if pixels_ is a nullpointer.
     */
    void downloadTexture();

    /**
     * Download texture from the GPU to a newly allocated buffer, to which a
     * pointer is returned.  Binds the texture.
     *
     * type_, format_, dimensions, and dataType_ have to be set before
     * calling this method!
     */
    GLubyte* downloadTextureToBuffer() const;

    /**
     * Download texture from the GPU to a newly allocated buffer with
     * the passed format/data type and the texture's dimensions.
     */
    GLubyte* downloadTextureToBuffer(GLint format, GLenum dataType) const;

    /**
     * Returns, wether texture is a texture rectangle (GL_TEXTURE_RECTANGLE_ARB)
     */
    bool isTextureRectangle() const;

/*
    1D access, always possible
*/
    template <class T>
    inline T& texel(size_t i) {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( i < size_t(hmul(dimensions_)), "index out of range" );
        return ((T*) pixels_)[i];
    }
    template <class T>
    inline const T& texel(size_t i) const {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( i < size_t(hmul(dimensions_)), "index out of range" );
        return ((T*) pixels_)[i];
    }

/*
    2D access, only possible when type_ == GL_TEXTURE_2D
*/
    template <class T>
    inline T& texel(size_t x, size_t y) {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( dimensions_.x * y + x < size_t(hmul(dimensions_)), "index out of range" );
        //tgtAssert( type_ == GL_TEXTURE_2D, "using 2d access, but it's not a GL_TEXTURE_2D");
        return ((T*) pixels_)[dimensions_.x * y + x];
    }
    template <class T>
    inline const T& texel(size_t x, size_t y) const {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( dimensions_.x * y + x < size_t(hmul(dimensions_)), "index out of range" );
        //tgtAssert( type_ == GL_TEXTURE_2D, "using 2d access, but it's not a GL_TEXTURE_2D");
        return ((T*) pixels_)[dimensions_.x * y + x];
    }
    template <class T>
    inline T& texel(const ivec2& pos) {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( dimensions_.x * pos.y + pos.x < hmul(dimensions_), "index out of range" );
        //tgtAssert( type_ == GL_TEXTURE_2D, "using 2d access, but it's not a GL_TEXTURE_2D");
        return ((T*) pixels_)[dimensions_.x * pos.y + pos.x];
    }
    template <class T>
    inline const T& texel(const ivec2& pos) const {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( dimensions_.x * pos.y + pos.x < hmul(dimensions_), "index out of range" );
        //tgtAssert( type_ == GL_TEXTURE_2D, "using 2d access, but it's not a GL_TEXTURE_2D");
        return ((T*) pixels_)[dimensions_.x * pos.y + pos.x];
    }

/*
    3D access, only possible when type_ == GL_TEXTURE_3D
*/
    template <class T>
    inline T& texel(size_t x, size_t y, size_t z) {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( z*dimensions_.x*dimensions_.y + y*dimensions_.x + x < size_t(hmul(dimensions_)), "index out of range" );
        //tgtAssert( type_ == GL_TEXTURE_3D, "using 3d access, but it's not a GL_TEXTURE_3D");
        return ((T*) pixels_)[z*dimensions_.x*dimensions_.y + y*dimensions_.x + x];
    }
    template <class T>
    inline const T& texel(size_t x, size_t y, size_t z) const {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( z*dimensions_.x*dimensions_.y + y*dimensions_.x + x < size_t(hmul(dimensions_)), "index out of range" );
        //tgtAssert( type_ == GL_TEXTURE_3D, "using 3d access, but it's not a GL_TEXTURE_3D");
        return ((T*) pixels_)[z*dimensions_.x*dimensions_.y + y*dimensions_.x + x];
    }
    template <class T>
    inline T& texel(const ivec3& pos) {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( pos.z*dimensions_.x*dimensions_.y + pos.y*dimensions_.x + pos.x < hmul(dimensions_), "index out of range" );
        //tgtAssert( type_ == GL_TEXTURE_3D, "using 3d access, but it's not a GL_TEXTURE_3D");
        return ((T*) pixels_)[pos.z*dimensions_.x*dimensions_.y + pos.y*dimensions_.x + pos.x];
    }
    template <class T>
    inline const T& texel(const ivec3& pos) const {
        //tgtAssert( sizeof(T) == bpp_, "sizeof(T) != bytes per pixel here" );
        //tgtAssert( pos.z*dimensions_.x*dimensions_.y + pos.y*dimensions_.x + pos.x < hmul(dimensions_), "index out of range" );
        //tgtAssert( type_ == GL_TEXTURE_3D, "using 3d access, but it's not a GL_TEXTURE_3D");
        return ((T*) pixels_)[pos.z*dimensions_.x*dimensions_.y + pos.y*dimensions_.x + pos.x];
    }

    ///Return texel as tgt::Color (slow!), downloadTexture() needs to be called first
	tgt::Color texelAsFloat(size_t x, size_t y) const;
	tgt::Color texelAsFloat(tgt::svec2 p) const { return texelAsFloat(p.x, p.y); }
protected:
    tgt::ivec3 dimensions_;
    GLint format_;          ///< GL_RGB...
    GLint internalformat_;  ///< GL_RGB...
    GLenum dataType_;       ///< GL_UNSIGNED_BYTE
    Filter filter_;
    Wrapping wrapping_;

    GLclampf priority_;     ///< GL texture priority [0...1]
    GLubyte* pixels_;       ///< (temporary) buffer for loading image
    size_t arraySize_;
    GLuint id_;             ///< OpenGL texture id

    GLenum type_;           ///< 1D, 2D, 3D
    GLubyte bpp_;           ///< bytes per pixel

    std::string name_;      ///< optional, e.g. for storing texture file name
    
    // used internally in the constructors
    void init(bool allocData, bool textureRectangle);
	tgt::GpuCapabilities*   gpuCapInstance;
};

} // namespace tgt

 
