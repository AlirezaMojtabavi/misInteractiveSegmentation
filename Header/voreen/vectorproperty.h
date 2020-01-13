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

#ifndef VRN_VECTORPROPERTY_H
#define VRN_VECTORPROPERTY_H

#include "condition.h"
#include "numericproperty.h"

#include <sstream>
#include "VoreenMacroes.h"

namespace voreen {



class VOREENEXPORTS FloatVec2Property : public NumericProperty<tgt::vec2> {
public:
    FloatVec2Property(const std::string& id, const std::string& guiText, const tgt::vec2& value,
                  const tgt::vec2& minimum = tgt::vec2(0.0f), const tgt::vec2& maximum = tgt::vec2(1.0f),
                  Processor::InvalidationLevel invalidationLevel=Processor::INVALID_RESULT);

    virtual ~FloatVec2Property() {}

    virtual std::string getTypeString() const;

      
};

//---------------------------------------------------------------------------



class VOREENEXPORTS FloatVec3Property : public NumericProperty<tgt::vec3> {
public:
    FloatVec3Property(const std::string& id, const std::string& guiText, const tgt::vec3& value,
                  const tgt::vec3& minimum = tgt::vec3(0.0f), const tgt::vec3& maximum = tgt::vec3(1.0f),
                  Processor::InvalidationLevel invalidationLevel=Processor::INVALID_RESULT);

    virtual ~FloatVec3Property() {}

    virtual std::string getTypeString() const;

      
};

//---------------------------------------------------------------------------



class VOREENEXPORTS FloatVec4Property : public NumericProperty<tgt::vec4> {
public:
    FloatVec4Property(const std::string& id, const std::string& guiText, const tgt::vec4& value,
                  const tgt::vec4& minimum = tgt::vec4(0.0f), const tgt::vec4& maximum = tgt::vec4(1.0f),
                  Processor::InvalidationLevel invalidationLevel=Processor::INVALID_RESULT);

    virtual ~FloatVec4Property() {}

    virtual std::string getTypeString() const;

      
};

//---------------------------------------------------------------------------



class VOREENEXPORTS IntVec2Property : public NumericProperty<tgt::ivec2> {
public:
    IntVec2Property(const std::string& id, const std::string& guiText, const tgt::ivec2& value,
                const tgt::ivec2& minimum = tgt::ivec2(0), const tgt::ivec2& maximum = tgt::ivec2(100),
                Processor::InvalidationLevel invalidationLevel=Processor::INVALID_RESULT);

    virtual ~IntVec2Property() {}

    virtual std::string getTypeString() const;

      
};

//---------------------------------------------------------------------------



class VOREENEXPORTS IntVec3Property : public NumericProperty<tgt::ivec3> {
public:
    IntVec3Property(const std::string& id, const std::string& guiText, const tgt::ivec3& value,
                const tgt::ivec3& minimum = tgt::ivec3(0), const tgt::ivec3& maximum = tgt::ivec3(100),
                Processor::InvalidationLevel invalidationLevel=Processor::INVALID_RESULT);

    virtual ~IntVec3Property() {}

    virtual std::string getTypeString() const;

      
};

//---------------------------------------------------------------------------



class VOREENEXPORTS IntVec4Property : public NumericProperty<tgt::ivec4> {
public:
    IntVec4Property(const std::string& id, const std::string& guiText, const tgt::ivec4& value,
                const tgt::ivec4& minimum = tgt::ivec4(0), const tgt::ivec4& maximum = tgt::ivec4(100),
                Processor::InvalidationLevel invalidationLevel=Processor::INVALID_RESULT);

    virtual ~IntVec4Property() {}

    virtual std::string getTypeString() const;

      
};

} // namespace voreen

#endif // VRN_VECTORPROPERTY_H
