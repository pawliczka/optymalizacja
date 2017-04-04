#pragma once
#include <string>

using Coefficient = int;
using Index = int;
using Term = std::pair<Coefficient, Index>;

class ITermConverter
{
public:
    virtual ~ITermConverter() = default;
    virtual Term convert(std::string expresion) = 0;
};
