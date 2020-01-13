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

#ifndef VRN_OPTIONPROPERTY_H
#define VRN_OPTIONPROPERTY_H

#include "templateproperty.h"
#include "condition.h"

#include "tgt/tgt_gl.h"

#include <map>

namespace voreen {

/**
 * Non-generic base type for option properties.
 *
 * @see OptionProperty
 */
class OptionPropertyBase : public TemplateProperty<std::string> {
public:
    OptionPropertyBase(const std::string& id, const std::string& guiText,
                       Processor::InvalidationLevel invalidationLevel=Processor::INVALID_RESULT)
        : TemplateProperty<std::string>(id, guiText, "", invalidationLevel)
    {}

    virtual void select(const std::string& key) = 0;
    virtual const std::string& getKey() const = 0;
    virtual bool isSelected(const std::string& key) const = 0;
    virtual bool hasKey(const std::string& key) const = 0;

    virtual std::vector<std::string> getKeys() const = 0;
    virtual std::vector<std::string> getDescriptions() const = 0;

    /**
     * @see Property::deserialize
     */
   
};

// ----------------------------------------------------------------------------

template<class T>
struct Option {
    Option(const std::string& key, const std::string& description, const T& value)
        : key_(key)
        , description_(description)
        , value_(value)
    {}

    std::string key_;
    std::string description_;
    T value_;
};

// ----------------------------------------------------------------------------

/**
 * Generic option property allowing the user to select
 * one out of multiple options.
 */
template<class T>
class OptionProperty : public OptionPropertyBase {
public:
    OptionProperty(const std::string& id, const std::string& guiText,
        Processor::InvalidationLevel invalidationLevel=Processor::INVALID_RESULT);
    virtual ~OptionProperty() {}

    virtual std::string getTypeString() const;

    virtual void addOption(const std::string& key, const std::string& description, const T& value);

    virtual void select(const std::string& key);
    virtual void selectByKey(const std::string& key);
    virtual void selectByValue(const T& value);
    virtual bool isSelected(const std::string& key) const;

    virtual const std::string& getKey() const { return get(); }
    std::string getDescription() const;
    T getValue() const;

    const std::vector<Option<T> >& getOptions() const { return options_; }
    void setOptions(const std::vector<Option<T> >& options) { options_ = options; }
    virtual std::vector<std::string> getKeys() const;
    virtual bool hasKey(const std::string& key) const;
    virtual std::vector<T> getValues() const;
    virtual std::vector<std::string> getDescriptions() const;



protected:
    virtual  
    const Option<T>* getOption(const std::string& key) const;

    std::vector<Option<T> > options_;
};

// ----------------------------------------------------------------------------
// template implementations

template<class T>
OptionProperty<T>::OptionProperty(const std::string& id, const std::string& guiText,
                                  Processor::InvalidationLevel invalidationLevel)
    : OptionPropertyBase(id, guiText, invalidationLevel)
{
    addValidation(OptionPropertyValidation(this)); // is at position 0 in the validations_ vector
}
template<class T>
std::string voreen::OptionProperty<T>::getTypeString() const {
    return "OptionProperty";
}

template<class T>
void OptionProperty<T>::addOption(const std::string& key, const std::string& description, const T& value) {
    std::vector<std::string> keys = getKeys();
    if (std::find(keys.begin(), keys.end(), key) == keys.end()) {
        options_.push_back(Option<T>(key, description, value));
        if (options_.size() == 1)
            set(key);
    }
    else {
        LERRORC("OptionProperty", "Key '" << key << "' already inserted.");
    }
}

template<class T>
void OptionProperty<T>::select(const std::string& key) {
    set(key);
}

template<class T>
void OptionProperty<T>::selectByKey(const std::string& key) {
    select(key);
}

template<class T>
void OptionProperty<T>::selectByValue(const T& value) {
    // find the option that fits the value
    for (size_t i = 0; i < options_.size(); ++i) {
        if (options_[i].value_ == value) {
            set(options_[i].key_);
            return;
        }
    }
    // if nothing was set the value was not valid
    throw Condition::ValidationFailed();
}

template<class T>
bool OptionProperty<T>::isSelected(const std::string& key) const {
    std::vector<std::string> keys = getKeys();
    if (std::find(keys.begin(), keys.end(), key) == keys.end()) {
        LWARNINGC("OptionProperty", "Unknown key: " << key);
    }
    return (get() == key);
}

template<class T>
T OptionProperty<T>::getValue() const {
    if (options_.empty()) {
        LWARNINGC("OptionProperty", "OptionProperty is empty (no options)");
        throw (VoreenException("OptionProperty is empty (no options)"));
    }
    const Option<T>* curOption = getOption(get());
    if (curOption)
        return curOption->value_;
    else
        return options_.front().value_;  // Just to silence the compiler
}

template<class T>
std::string OptionProperty<T>::getDescription() const {
    if (options_.empty()) {
        LWARNINGC("OptionProperty", "OptionProperty is empty (no options)");
        throw (VoreenException("OptionProperty is empty (no options)"));
    }
    const Option<T>* curOption = getOption(get());
    if (curOption)
        return curOption->description_;
    else
        return options_.front().description_;  // Just to silence the compiler
}

template<class T>
std::vector<std::string> OptionProperty<T>::getKeys() const {
    std::vector<std::string> keys;
    for (size_t i = 0; i < options_.size(); ++i)
        keys.push_back(options_[i].key_);

    return keys;
}

template<class T>
bool OptionProperty<T>::hasKey(const std::string& key) const {
    std::vector<std::string> keys = getKeys();
    return (std::find(keys.begin(), keys.end(), key) != keys.end());
}

template<class T>
std::vector<T> OptionProperty<T>::getValues() const {
    std::vector<T> values;
    for (size_t i = 0; i < options_.size(); ++i)
        values.push_back(options_[i].value_);

    return values;
}

template<class T>
std::vector<std::string> OptionProperty<T>::getDescriptions() const {
    std::vector<std::string> descriptions;
    for (size_t i = 0; i < options_.size(); ++i)
        descriptions.push_back(options_[i].description_);

    return descriptions;
}


template<class T>
const Option<T>* voreen::OptionProperty<T>::getOption(const std::string& key) const {
    for (size_t i=0; i<options_.size(); ++i)
        if (options_[i].key_ == key)
            return &options_[i];
    return 0;
}

 

typedef OptionProperty<int> IntOptionProperty;
typedef OptionProperty<float> FloatOptionProperty;
typedef OptionProperty<GLenum> GLEnumOptionProperty;

// since option ids are already strings, an additional value is not necessarily required for string option properties
class StringOptionProperty : public OptionProperty<std::string> {

public:

    StringOptionProperty(const std::string& id, const std::string& guiText,
                         Processor::InvalidationLevel invalidationLevel = Processor::INVALID_RESULT) :
        OptionProperty<std::string>(id, guiText, invalidationLevel)
    {}

    virtual std::string getTypeString() const {
        return "StringOptionProperty";
    }

    virtual void addOption(const std::string& key, const std::string& description) {
        addOption(key, description, key);
    }

    virtual void addOption(const std::string& key, const std::string& description, const std::string& value) {
        OptionProperty<std::string>::addOption(key, description, value);
    }

};

} // namespace voreen

#endif // VRN_OPTIONPROPERTY_H
