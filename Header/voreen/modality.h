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
#pragma  once
#include <string>
#include <iostream>
#include <vector>
#pragma warning  (disable: 4835)
#include "VoreenMacroes.h"

namespace voreen {

class VOREENEXPORTS   Modality {
public:
    Modality(const std::string& name = "MODALITY_UNKNOWN");
	 

    std::string getName() const { return name_; }
    bool isUnknown() const { return name_ == "MODALITY_UNKNOWN"; }

    static const std::vector<Modality*> getModalities() { return modalities(); }
    static const std::vector<std::string>& getModalityNames() { return modalityNames_(); }

    // all known modalities
    
    
protected:
    std::string name_;

    // This indirection is done to prevent the "static initialization order fiasco"
    // see http://www.parashift.com/c++-faq-lite/ctors.html (10.13)
    static std::vector<std::string>& modalityNames_();

    static std::vector<Modality*>& modalities();
};

 
} // namespace voreen
 