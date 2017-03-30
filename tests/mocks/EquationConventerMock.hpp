#include "IEquationConventer.hpp"
#include <gmock/gmock.h>

class EquationConventerMock : public IEquationConventer
{
public:
    MOCK_METHOD1( convert, Equation(const std::string) );
};
