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

#ifndef VRN_TRANSFUNCINTENSITYGRADIENT_H
#define VRN_TRANSFUNCINTENSITYGRADIENT_H

#include "transfunc.h"
#include "tgtMacroHeader.h"

namespace tgt {
    class FramebufferObject;
}

 

class TransFuncPrimitive;

/**
 * This class represents a two-dimensional intensity-gradient based transfer function.
 *
 * - x-axis: intensity
 * - y-axis: gradient magnitude
 *
 * The transfer function is defined by primitives that can be added and edited with TransFuncEditorIntensityGradient.
 * Internally, the transfer function is represented by a two-dimensional RGBA texture of type GL_FLOAT,
 * which is updated through a framebuffer object.
 */
class  TGTLIBMISDLLEXPORT TransFuncIntensityGradient : public TransFunc {
 
public:
    /**
     * Constructor
     *
     * @param width width of the texture of the transfer function
     * @param height height of the texture of the transfer function
     */
    TransFuncIntensityGradient(int width = 256, int height = 256);

    /**
     * Destructor
     *
     * - deletes all primitives the transfer function consists of
     * - deletes the framebuffer object
     */
    virtual ~TransFuncIntensityGradient();

    /**
     * Operator to compare two TransFuncIntensityGradient's. True is returned when
     * height and width are the same in both transfer functions and all texel in this
     * transfer function have the same value as the corresponding texel in the other
     * transfer function.
     *
     * @param tf transfer function that is compared with this transfer function
     * @return true when width and height and all texel are the same in both transfer functions, false otherwise
     */
    bool operator==(const TransFuncIntensityGradient& tf);

    /**
     * Operator to compare two TransFuncIntensityGradient's. False is returned when
     * height and width are the same in both transfer functions and all texel in this
     * transfer function have the same value as the corresponding texel in the other transfer function.
     *
     * @param tf transfer function that is compared with this transfer function
     * @return false when width and height and texel are the same in both transfer functions, true otherwise
     */
    bool operator!=(const TransFuncIntensityGradient& tf);

    /**
     * Sets the scaling factor in y direction for the primitive coordinates to the given value.
     * That is necessary because the histogram is scaled to the maximum gradient length that occurs
     * in the current rendered dataset. Usually this length is smaller than the highest possible
     * gradient length. The factor is passed to the primitives.
     *
     * @param factor scaling factor for primitive coordinates in y direction
     */
    void setScaleFactor(float factor);

    /**
     * The central entry point for loading a gradient transfer function.
     * The file extension is extracted and based on that the apropriate
     * load function is called. If there is no extension, loading will be unsuccessful.
 
    /**
     * Adds the given primitive to the transfer function.
     *
     * @param p the primitive that is added to the transfer function
     */
    void addPrimitive(TransFuncPrimitive* p);

    /**
     * Removes the given primitive from the transfer function. The primitive is deleted as well.
     *
     * @param p the primitve that will be removed from transfer function
     */
    void removePrimitive(TransFuncPrimitive* p);

    /**
     * Returns the primitive that is under the mouse cursor or 0 if there is none.
     *
     * @param pos position of the mouse cursor
     * @return primitive that is under the mouse cursor or 0 if there is none
     */
    TransFuncPrimitive* getPrimitiveForClickedControlPoint(const tgt::vec2& pos) const;

    /**
     * Calls paint for all primitives
     */
    void paint();

    /**
     * Paints all primitives for selection purposes.
     */
    void paintForSelection();

    /**
     * Paints all primitives for display in an editor. Control points are added for every primitive.
     * An outline is added to the selected primitive.
     */
    void paintInEditor();

    /**
     * Clears the transfer function, i.e. all primitives of the transfer function are
     * deleted.
     */
    void clear();

    /**
     * Renders the transfer function to texture using a framebuffer object.
     * The viewport is set to the dimensions of the texture and paint() is called
     * for every primitive.
     */
    void updateTexture();

    /**
     * Returns the i.th primitive of the transfer function or 0
     * if no such primitive exists.
     */
    TransFuncPrimitive* getPrimitive(int i) const;

    /**
     * @see Serializable::serialize
     */


    /**
     * @see Serializable::deserialize
     */
   

    /**
     * Returns a copy of this object.
     */
    virtual TransFunc* clone() const;

protected:
    /**
     * Attaches the texture that has been created by the base class to a framebuffer object.
     */
    virtual void createTex();

     

    std::vector<TransFuncPrimitive*> primitives_; ///< primitives the transfer function consists of

private:
    tgt::FramebufferObject* fbo_;        ///< used for rendering the primitives to the texture

     static const std::string loggerCat_; ///< the logger category
};
 

#endif // VRN_TRANSFUNCINTENSITYGRADIENT_H
