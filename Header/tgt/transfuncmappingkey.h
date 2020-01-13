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

#ifndef VRN_TRANSFUNCMAPPINGKEY_H
#define VRN_TRANSFUNCMAPPINGKEY_H
 

#include "tgt/vector.h"
#include "tgt/texture.h"

 

/**
 * One of multiple keys that define a TransfuncIntensity.
 * Each key has an intensity at which it is located and a color.
 * Furthermore it can be split in two parts with two different colors.
 */
 

class TGTLIBMISDLLEXPORT TransFuncMappingKey  {
public:
    /**
     * Constructor
     *
     * @param i intensity at which this key is located
     * @param color the color of this key
     */
    TransFuncMappingKey(float i, const tgt::col4& color);

    /**
     * Standard Destructor
     */
    ~TransFuncMappingKey();

    /**
     * Operator to compare two TransFuncMappingKeys. True is returned when both keys
     * have the same intensity, color and split status. Otherwise false is returned.
     *
     * @param key key that is compared with this key
     * @return true if both keys have same split status, same color and same intensity, false otherwise
     */
    bool operator==(const TransFuncMappingKey& key);

    /**
     * Operator to compare two TransFuncMappingKeys. True is returned when both keys
     * differ in color, intensity or split status. Otherwise false is returned.
     *
     * @param key key that is compared with this key
     * @return true if both keys differ in split status, color or intensity, false otherwise
     */
    bool operator!=(const TransFuncMappingKey& key);

    /**
     * Sets the color of the left part of the key to the given value.
     *
     * @param color color the left part of the key will be set to
     */
    void setColorL(const tgt::col4& color);

    /**
     * Sets the color of the left part of the key to the given value.
     *
     * @param color color the left part of the key will be set to
     */
    void setColorL(const tgt::ivec4& color);

    /**
     * Returns the color of the left part of the key.
     *
     * @return color of the left part of the key
     */
    tgt::col4& getColorL();

    /**
     * Sets the color of the right part of the key to the given value.
     *
     * @param color color the right part of the key will be set to
     */
    void setColorR(const tgt::col4& color);

    /**
     * Sets the color of the right part of the key to the given value.
     *
     * @param color color the right part of the key will be set to
     */
    void setColorR(const tgt::ivec4& color);

    /**
     * Returns the color of the right part of the key.
     *
     * @return color of the right part of the key
     */
    tgt::col4& getColorR();

    /**
     * Sets the alpha value of the right part of the key to the given value.
     * The value has to be in the range 0.f-1.f.
     *
     * @param a alpha value the right part of the key will be set to
     */
    void setAlphaR(float a);

    /**
     * Sets the alpha value of the left part of the key to the given value.
     * The value has to be in the range 0.f-1.f.
     *
     * @param a alpha value the left part of the key will be set to
     */
    void setAlphaL(float a);

    /**
     * Returns the alpha value of the right part of the key as float (0.f-1.f).
     *
     * @return alpha value of the right part of the key
     */
    float getAlphaR();

    /**
     * Returns the alpha value of the left part of the key as float (0.f-1.f).
     *
     * @return alpha value of the left part of the key
     */
    float getAlphaL();

    /**
     * Returns whether the key is split or not.
     *
     * @return true if the key is split, false otherwise.
     */
    bool isSplit();

    /**
     * Splits or unsplits this key.
     *
     * @param split true to split, false to merge
     * @param useLeft in case of joining: use the left color (else use right)
     */
    void setSplit(bool split, bool useLeft=true);

    /**
     * Returns the intensity at which the key is located.
     *
     * @return intensity at which the key is located
     */
    float getIntensity();

    /**
     * Sets the intensity of the key to the given value. The keys of the transfer function
     * have to be sorted after this.
     *
     * @param i new intensity of the key
     */
    void setIntensity(float i);

    tgt::Texture* getTextureL() const;

    tgt::Texture* getTextureR() const;

    void setTextureL(tgt::Texture* tex);

    void setTextureR(tgt::Texture* tex);

    const std::string& getTexNameLeft() const;

    const std::string& getTexNameRight() const;

    void setTexNameLeft(std::string& name);

    void setTexNameRight(std::string& name);

    /**
     * @see Serializable::serialize
     */


    /**
     * @see Serializable::deserialize
     */
   

    /**
     * Returns a copy of this object.
     */
    TransFuncMappingKey* clone() const;

private:
    friend class XmlDeserializer;
    friend class TransFuncFactory;
    /**
     * Default constructor needed for serialization purposes.
     */
    TransFuncMappingKey();

    float intensity_;  ///< intensity at which the key is located
    tgt::col4 colorL_; ///< color of the left part of the key
    tgt::col4 colorR_; ///< color of the right part of the key
    tgt::Texture* texL_;
    tgt::Texture* texR_;
    std::string texNameLeft_;
    std::string texNameRight_;
    bool split_;       ///< is the key split?
};


#endif // VRN_TRANSFUNCMAPPINGKEY_H
