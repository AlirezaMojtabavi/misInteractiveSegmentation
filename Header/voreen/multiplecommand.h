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

#ifndef VRN_MULTIPLECOMMAND_H
#define VRN_MULTIPLECOMMAND_H

#include <vector>
#include "command.h"

namespace voreen {

/**
 * This class represents a command which can be called multiple times in a given commandline and
 * can have 1-4 arguments of types T, U, V and U.
 * This class simply tries to convert the parameters to the appropriate values and stores them in it
 * The template must be usable within a stringstream (necessary for conversion)
 * \sa MultipleCommandZeroArguments
 */
template<class T, class U = T, class V = U, class W = V>
class MultipleCommand : public Command {
public:
    MultipleCommand(std::vector<T>* ptr1,
        const std::string& name, const std::string& shortName = "", const std::string& infoText = "",
        const std::string parameterList = "")
        : Command(name, shortName, infoText, parameterList, 1, true)
        , ptr1_(ptr1)
        , ptr2_(0)
        , ptr3_(0)
        , ptr4_(0)
    {}

    MultipleCommand(std::vector<T>* ptr1, std::vector<U>* ptr2,
        const std::string& name, const std::string& shortName = "", const std::string& infoText = "",
        const std::string parameterList = "")
        : Command(name, shortName, infoText, parameterList, 2, true)
        , ptr1_(ptr1)
        , ptr2_(ptr2)
        , ptr3_(0)
        , ptr4_(0)
    {}

    MultipleCommand(std::vector<T>* ptr1, std::vector<U>* ptr2, std::vector<V>* ptr3,
        const std::string& name, const std::string& shortName = "", const std::string& infoText = "",
        const std::string parameterList = "")
        : Command(name, shortName, infoText, parameterList, 3, true)
        , ptr1_(ptr1)
        , ptr2_(ptr2)
        , ptr3_(ptr3)
        , ptr4_(0)
    {}

    MultipleCommand(std::vector<T>* ptr1, std::vector<U>* ptr2, std::vector<V>* ptr3, std::vector<W>* ptr4,
        const std::string& name, const std::string& shortName = "", const std::string& infoText = "",
        const std::string parameterList = "")
        : Command(name, shortName, infoText, parameterList, 4, true)
        , ptr1_(ptr1)
        , ptr2_(ptr2)
        , ptr3_(ptr3)
        , ptr4_(ptr4)
    {}

    bool execute(const std::vector<std::string>& parameters) {
        ptr1_->push_back(cast<T>(parameters[0]));
        if (ptr2_ != 0)
            ptr2_->push_back(cast<U>(parameters[1]));
        if (ptr3_ != 0)
            ptr3_->push_back(cast<V>(parameters[2]));
        if (ptr4_ != 0)
            ptr4_->push_back(cast<W>(parameters[3]));

        return true;
    }

    bool checkParameters(const std::vector<std::string>& parameters) {
        bool result = parameters.size() == static_cast<size_t>(argumentNum_);

        result &= is<T>(parameters[0]);
        if (ptr2_ != 0)
            result &= is<U>(parameters[1]);
        if (ptr3_ != 0)
            result &= is<V>(parameters[2]);
        if (ptr4_ != 0)
            result &= is<W>(parameters[3]);

        return result;
    }

protected:
    std::vector<T>* ptr1_;
    std::vector<U>* ptr2_;
    std::vector<V>* ptr3_;
    std::vector<W>* ptr4_;
};

/**
 * This class represents a command with zero arguments which can be called multiple times in a given commandline.
 * The pointer will be set to "true", if the command is executed
 * The template must be usable within a stringstream (necessary for conversion)
 * \sa MultipleCommand
 */
class MultipleCommandZeroArguments : public Command {
public:
    MultipleCommandZeroArguments(std::vector<bool>* ptr, const std::string& name, const std::string& shortName = "",
        const std::string& infoText = "")
        : Command(name, shortName, infoText, "", 0, true)
        , ptr_(ptr)
    {}

    bool execute(const std::vector<std::string>& /*parameters*/) {
        ptr_->push_back(true);
        return true;
    }

protected:
    std::vector<bool>* ptr_;
};

} // namespace

#endif // VRN_MULTIPLECOMMAND_H
