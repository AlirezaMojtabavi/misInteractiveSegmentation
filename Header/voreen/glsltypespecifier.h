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

#ifndef VRN_GLSLTYPESPECIFIER_H
#define VRN_GLSLTYPESPECIFIER_H

#include "voreen/core/utils/GLSLparser/glsl/glslexpression.h"
#include "voreen/core/utils/GLSLparser/glsl/glslqualifier.h"

namespace voreen {

namespace glslparser {

class GLSLTypeSpecifier : public GLSLNode {
public:
    GLSLTypeSpecifier(const Token& token, GLSLPrecisionQualifier* const precision,
        const bool isArray, GLSLConditionalExpression* const numArrayElements)
        : GLSLNode(token.getTokenID()),
        token_(token.getCopy()),
        typeQualifier_(0),
        precision_(precision),
        isArray_(isArray),
        numArrayElements_(numArrayElements)
    {
    }

    virtual ~GLSLTypeSpecifier() {
        delete token_;
        delete typeQualifier_;
        delete precision_;
        delete numArrayElements_;
    }

    virtual int getNodeType() const { return GLSLNodeTypes::NODE_TYPE_SPECIFIER; }

    void setIsArray(const bool isArray) { isArray_ = isArray; }

    void setNumArrayElements(GLSLConditionalExpression* const numArrayElements) {
        numArrayElements_ = numArrayElements;
        if (numArrayElements_ > 0)
            isArray_ = true;
    }

    Token* getTypeToken() const { return token_; }
    GLSLTypeQualifier* getTypeQualifier() const { return typeQualifier_; }
    GLSLPrecisionQualifier* getPrecisionQualifier() const { return precision_; }
    GLSLConditionalExpression* getNumArrayElements() { return numArrayElements_; }
    bool isArray() const { return isArray_; }

    void setPrecision(GLSLPrecisionQualifier* const precision) { precision_ = precision; }
    void setTypeQualifier(GLSLTypeQualifier* const typeQualifier) { typeQualifier_ = typeQualifier; }

protected:
    Token* const token_;
    GLSLTypeQualifier* typeQualifier_;
    GLSLPrecisionQualifier* precision_;
    bool isArray_;
    GLSLConditionalExpression* numArrayElements_;
};

}   // namespace glslparser

}   // namespace voreen

#endif
