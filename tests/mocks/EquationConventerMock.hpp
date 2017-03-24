#include "IEquationConventer.hpp"
#include <gmock/gmock.h>

class EquationConventerMock : public IEquationConventer
{
public:
    MOCK_METHOD0( convert, int() );
};
