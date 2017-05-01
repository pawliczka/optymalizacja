#pragma once
#include <string>

using Coefficient = float;
using Index = int;
using Term = std::pair<Coefficient, Index>;

class ITermConverter
{
public:
    virtual ~ITermConverter() = default;
    virtual Term convert(std::string expresion) = 0;
};
