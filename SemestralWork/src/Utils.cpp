#include "Utils.h"

StringHolder::StringHolder() = default;

std::string StringHolder::getString() const {
    return rules;
}