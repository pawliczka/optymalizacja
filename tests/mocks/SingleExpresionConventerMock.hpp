#include "ISingleExpresionConventer.hpp"
#include <gmock/gmock.h>

class SingleExpresionConventerMock : public IEquationConventer
{
public:
    MOCK_METHOD1( convert, std::pair< int, int >( std::string ) );
};
