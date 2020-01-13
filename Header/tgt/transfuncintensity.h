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

#ifndef VRN_TRANSFUNCINTENSITY_H
#define VRN_TRANSFUNCINTENSITY_H

#include "transfunc.h"

#include "tgt/vector.h"
#include "tgtMacroHeader.h"
 

class TransFuncMappingKey;

/**
 * One dimensional, piece-wise linear transfer function based on key values.
 *
 * Internally, it is represented by a one-dimensional RGBA texture of type GL_UNSIGNED_BYTE.
 */


class  TGTLIBMISDLLEXPORT TransFuncIntensity : public TransFunc {
public:
    /**
     * Constructor
     *
     * @param width desired width of the transfer function
     */
    TransFuncIntensity(int width= 256*2);

    /**
     * Copy constructor.
     *
     * @param tf reference to the TransFuncIntensity instance, which is copied
     */
    TransFuncIntensity(const TransFuncIntensity& tf);

    /**
     * Destructor - deletes the keys of the transfer function
     */
    virtual ~TransFuncIntensity();

    /**
     * Operator to compare two TransFuncIntensity objects. True is returned when the width of the
     * texture is the same and all keys are equal. Otherwise false is returned.
     *
     * @param tf transfer function that is compared with this transfer function
     * @return true when the keys of both transfer functions are equal
     */
    bool operator==(const TransFuncIntensity& tf);

    /**
     * Operator to compare two TransFuncIntensity objects. False is returned when the width of the
     * texture is the same and all keys are equal. Otherwise true is returned.
     *
     * @param tf transfer function that is compared with this transfer function
     * @return true when the keys of both transfer functions differ or the width of the texture
     *         is not the same, false otherwise
     */
    bool operator!=(const TransFuncIntensity& tf);

    /**
     * Re-generates the texture from the already existing keys.
     * If the texture was empty before the call, a new texture is created automatically.
     */
    void updateTexture();

    /**
     * Creates a default function.
     * Generates two keys:
     * One at intensity 0 with the color (0,0,0,0) ;
     * another one at intensity 1 with the color (255,255,255,255)
     */
    void createStdFunc();

    /**
     * Calculates the average for the segment [segStart,segEnd).
     *
     * @param segStart the start of the segment
     * @param segEnd the end of the segment; the value itself is not part of the calculation
     * @return a vector containing the average value for the segment
     */
    tgt::vec4 getMeanValue(float segStart, float segEnd) const;

    /**
     * Returns the value to which the input value is being mapped.
     * The procedures handles missing keys and out-of-range values gracefully.
     *
     * @param value the intensity value for which the mapping is requested
     * @return the value the input value is mapped to.
     */
    tgt::col4 getMappingForValue(float value) const;

    /**
     * Returns the number of keys in this transfer function.
     *
     * @return the number of keys
     */
    int getNumKeys() const;

    /**
     * Returns the key at i-th position. Keys are sorted by their intensities in ascending order.
     * If a value outside of [0, getNumKeys()] is passed, it will be clamped to the appropriate values.
     *
     * @param i the i-th key will be returned
     * @return the pointer to the appropriate key
     */
    TransFuncMappingKey* getKey(int i) const;

    /**
     * Returns all keys. Keys are sorted by their intensities in ascending order.
     *
     * @return a vector containing all the keys
     */
    const std::vector<TransFuncMappingKey*> getKeys() const;

    /**
    * Replaces the current keys by the passed ones.
    *
    * @param keys the new keys
    */
    void setKeys(std::vector<TransFuncMappingKey*> keys);

    /**
     * Adds a key to the property mapping function.
     * It will be automatically inserted into the correct position.
     *
     * @param key the key to be added
     */
    void addKeysInOrder(TransFuncMappingKey* key); // NOTE : this function doesn't sort the keys. uses push_back

	void TransFuncIntensity::addKey(TransFuncMappingKey* key);// sorts the keys and inserts them in keys vector.
    /**
     * Updates a key within the property mapping function.
     * Call this method when intensity of a key is changed.
     *
     * @param key the key to be updated
     */
    void updateKey(TransFuncMappingKey* key);

    /**
     * Removes the given key from the transfer function.
     * Also deletes the passed key.
     *
     * @param key the key that will be removed.
     */
    void removeKey(TransFuncMappingKey* key);

    /**
     * Removes all keys from the transfer function.
     */
    void clearKeys();

    /**
     * This method returns whether the mapping function is empty.
     * i.e., it contains no mapping keys.
     *
     * @return Is the mapping function empty?
     */
    bool isEmpty() const;


    /**
     * Sets the lower and upper intensity thresholds to given values. The thresholds have to be normalized
     * to the range [0,1]. The texture is not updated at this time.
     *
     * @param lower lower threshold
     * @param upper upper threshold
     */
    void setThresholds(float lower, float upper);

    /**
     * @overload
     */
    void setThresholds(const tgt::vec2& thresholds);

    /**
     * Returns the lower and upper intensity thresholds of the tranfer function.
     * The thresholds are normalized within the range [0,1].
     */
    tgt::vec2 getThresholds() const;

    /**
     * Updates the transfer function's state from the passed
     * transfer function.
     */
    void updateFrom(const TransFuncIntensity& tf);

    /**
     * @see Serializable::serialize
     */


    /**
     * @see Serializable::deserialize
     */
   

    /**
     * Retuns a copy of this object.
     */
    virtual TransFunc* clone() const;

protected:
    /**
     * Loads a transfer function from an file with ending tfi.
     *
     * @param filename the name of the file, which should be opened
     * @return true if loading succeeds, false otherwise
     */
    bool loadTfi(const std::string& filename);

    /**
     * Loads a transfer function out of an ordinary image file. For this method, DevIL is required.
     *
     * @param filename the name of the file, which should be opened
     * @return true if loading succeeds, false otherwise
     */
    bool loadImage(const std::string& filename);

    /**
     * Loads a transfer function from a text file.
     * This format is used by Klaus Engel in his preintegration volume renderer.
     * Its just 256 rows of 4 entries each. -> RGBA
     *
     * @param filename the name of the file, which should be opened
     * @return true if loading succeeds, false otherwise
     */
    bool loadTextTable(const std::string& filename);

    /**
     * Loads a transfer function from an Osirix CLUT file.
     * Osirix CLUT doesn't support an alpha channel. So all values will be set opaque.
     *
     * @param filename the name of the CLUT file
     * @return true if loading succeeds, false otherwise
     */
    bool loadOsirixCLUT(const std::string& filename);

    /**
     * Loads a transfer function from a LUT used by ImageJ (http://rsbweb.nih.gov/ij/)
     * Those Lookup-Tables might come in three different kinds:
     * i)   binary LUT's coming from the National Institutes of Health (NIH)
     *      those files include a header containing additional information about the table
     * ii)  binary LUT's saved in a raw format, lacking additional data.
     * iii) a LUT in a simple text format, also with a 'missing' header
     *
     * @param filename the name of the file, which should be opened
     * @return true if loading succeeds, false otherwise
     */
    bool loadImageJ(const std::string& filename);

    /**
     * Opens a binary LUT-File. There a two possibilities for a binary file; raw and NIH
     * the NIH type includes additional data about version information and the number of colors.
     * No alpha-channel information is included in a LUT file. All values will be opaque.
     *
     * @param fileStream the already opened file stream used to extract the data
     * @param raw should the file be treated as raw data?
     * @return 256 if the load was successful, 0 otherwise
     */
    int openImageJBinary(std::ifstream& fileStream, bool raw);

    /**
     * Opens a LUT file containing textual information. Currently, two types are supported;
     * i)  256 rows , 3 columns  ; one column for each color
     * ii) 256 rows , 4 columns  ; the first column is an index from 0 to 255. The others like i)
     * Each entry should be seperated by a tabstop.
     * In both cases rows beginning with a non-integer character will be ignored.
     * No alpha-channel information is included in a the file. All values will be opaque.
     *
     * @param fileStream the already opened file stream used to extract the data
     * @return 256 if the load was successful, 0 otherwise
     */
    int openImageJText(std::ifstream& fileStream);

    /**
     * This method generates keys out of the given data.
     * The given data has to have the shape RGBA, otherwise the creation will be unsuccessful.
     * The method extrapolates the extrema of the colorchannels and puts a key in those places,
     * where the difference between neighboring entries is not linear.
     *
     * @param data an array of width*4 entries of bytes
     */
    void generateKeys(unsigned char* data);

	
	
    std::vector<TransFuncMappingKey*> keys_; ///< internal representation of the transfer function as a set of keys

    float lowerThreshold_; ///< lower threshold
    float upperThreshold_; ///< upper threshold

    static const std::string loggerCat_; ///< logger category
};

 

#endif // VRN_TRANSFUNCINTENSITY_H
