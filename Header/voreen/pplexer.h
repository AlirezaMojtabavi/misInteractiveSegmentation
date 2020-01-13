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

#ifndef VRN_PPLEXER
#define VRN_PPLEXER

#include "voreen/core/utils/GLSLparser/lexer.h"

#include "voreen/core/utils/GLSLparser/glsl/glsltoken.h"
#include <deque>

namespace voreen {

namespace glslparser {

class PreprocessorLexer : public Lexer {
public:
    PreprocessorLexer(std::istream* const is, const std::map<std::string, Word>& keywords)
        throw (std::bad_alloc);

    PreprocessorLexer(const std::string& fileName, const std::map<std::string, Word>& keywords)
        throw (std::bad_alloc);

    virtual ~PreprocessorLexer();

    virtual Token* scan();

private:
    enum ScannerState {
        STATE_START,
        STATE_INSIDE_BLOCK_COMMENT,
        STATE_INSIDE_LINE_COMMENT,
        STATE_READING_DIRECTIVE,
        STATE_SKIPPING_WHITESPACE,
        STATE_END
    };

private:
    std::deque<Token*> scanDirective(const std::string& directive) const;
    ConstantToken* scanNumber(const std::string& input, size_t& end) const;
    Token* createTextToken(const std::streampos& start, const std::streampos& end);

private:
    ScannerState scanState_;
    std::deque<Token*> currentDirective_;
};

}   // namespace glslparser

}   // namespace voreen

#endif
