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

#ifndef VRN_VOLUMEWRITER_H
#define VRN_VOLUMEWRITER_H

#include <string>
#include <vector>

#include "exception.h"

namespace voreen {
// forward declarations
class ProgressBar;
class VolumeHandle;

/**
 * Reads a volume dataset.
 * Implement this class in order to support a new format.
 */
class VolumeWriter {
public:
    VolumeWriter(ProgressBar* progress = 0);
    virtual ~VolumeWriter() {}

    /**

     */
    virtual VolumeWriter* create(ProgressBar* progress = 0) const = 0;

    /**
     * Saves a Volume to the given file.
     *
     * @param fileName The file name where the data should go.
     * @param Volume The volume which should be saved.
     */
    virtual void write(const std::string& fileName, VolumeHandle* volumeHandle)
        throw (IOException) = 0;

    /**
     * Returns the filename extensions that are supported by the writer.
     */
    const std::vector<std::string>& getExtensions() const;

    /**
     * Use this method as a helper to get a file name without its extension
     *
     * @param fileName File name to be examined.
     * @return File name without extension.
     */
    static std::string getFileNameWithoutExtension(const std::string& filename);

    /**
     * Use this method as a helper to get the extension of a given file name.
     *
     * @param fileName File name to be examined.
     * @return The extension of the file name.
     */
    static std::string getExtension(const std::string& filename);

protected:
    ProgressBar* progress_;

    /// List of filename extensions supported by the reader.
    std::vector<std::string> extensions_;

    static const std::string loggerCat_;
};
} // namespace voreen

#endif // VRN_VOLUMEWRITER_H
