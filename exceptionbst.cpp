#include "exceptionbst.h"

duplicated_value::duplicated_value(const std::string &message) : std::logic_error(message) {}