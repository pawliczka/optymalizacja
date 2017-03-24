#include "ITermConverter.hpp"
#include <gmock/gmock.h>

class TermConverterMock : public IEquationConventer
{
public:
    MOCK_METHOD1( convert, Term( std::string ) );
};
