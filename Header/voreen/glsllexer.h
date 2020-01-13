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

#ifndef VRN_GLSLLEXER_H
#define VRN_GLSLLEXER_H

#include "voreen/core/utils/GLSLparser/lexer.h"
#include "voreen/core/utils/GLSLparser/glsl/glsltoken.h"

namespace voreen {

namespace glslparser {

class GLSLLexer : public Lexer {
public:
    GLSLLexer(std::istream* const is, const std::map<std::string, Word>& keywords)
        throw (std::bad_alloc);

    GLSLLexer(const std::string& fileName, const std::map<std::string, Word>& keywords)
        throw (std::bad_alloc);

    virtual ~GLSLLexer();

    virtual Token* scan();

private:
    enum ScanState {
        STATE_NORMAL,
        STATE_INSIDE_ANNOTATION_BLOCK,
        STATE_INSIDE_ANNOTATION_LINE,
        STATE_INSIDE_BLOCK_COMMENT,
        STATE_INSIDE_LINE_COMMENT
    };

private:
    void initPredefinedStructs();

    Token* nextToken() throw (std::runtime_error);

    AnnotationToken* scanAnnotation(const std::string& annotation, const bool isLeading);

    ConstantToken* scanNumber() throw (std::runtime_error);

private:
    typedef std::map<std::string, Word> TypeNameMap;
    TypeNameMap typeNames_;

    ScanState state_;
    int previousTokenID_;
};

}   // namespace glslparser

}   // namespace voreen

#endif
