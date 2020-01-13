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

#ifndef VRN_BRICKEDVOLUMEREADER_H
#define VRN_BRICKEDVOLUMEREADER_H

#include "voreen/core/io/volumereader.h"
namespace voreen {

    class BrickedVolumeReader : public VolumeReader {
    public:
        BrickedVolumeReader(ProgressBar* progress = 0);

        virtual VolumeReader* create(ProgressBar* progress = 0) const;

        /**
        * Opens the Information file (bvi = bricked volume information) and
        * reads the neccessary information from it, like dimensions, format etc.
        */
        bool openFile(std::string filename);

        /**
        * Closes all open files and deletes the handles.
        */
        void closeFile();

 

        virtual VolumeHandle* read(const VolumeOrigin& origin)
            throw (tgt::FileException, std::bad_alloc);

        virtual VolumeCollection* read(const std::string& fileName)
            throw(tgt::CorruptedFileException, tgt::IOException, std::bad_alloc);

        virtual VolumeCollection* readSlices(const std::string& fileName, size_t firstSlice=0, size_t lastSlice=0)
            throw(tgt::CorruptedFileException, tgt::IOException, std::bad_alloc);

        /**
         * When a bricked volume was loaded successfully, the reader should stay in memory so
         * that it can do incremental loading based on view position. The reader will be freed
         * through the BrickingManager.
         */
        bool isPersistent() const { return persistent_; }

    protected:
       
 

        /**
        * The filestream used for reading brick positions from the bpi file.
        * The .bpi file stores the information where bricks can be found in the
        * .bv file.
        */
        std::fstream* bpiStream_;

        /**
        * The FILE used to access the .bv file. This is a FILE* and not a stream
        * because streams can't seek in files larger than 2gb. With FILE we can use
        * fseeki64.
        */
        FILE* bvFile_;

        uint64_t* positionArray_;
        char* allVoxelsEqualArray_;
        float* errorArray_;
        uint64_t currentBrick_;
        uint64_t errorArrayPosition_;

        bool persistent_;

        static ProgressBar* progressBar_;

    private:
        static const std::string loggerCat_;
    };

} // namespace voreen

#endif
