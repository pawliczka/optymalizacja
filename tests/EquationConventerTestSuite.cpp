#include "EquationConventer.hpp"
#include "TermConverterMock.hpp"
#include "Equation.hpp"
#include <gmock/gmock.h>
#include <memory>

using namespace testing;

class EquationConventerTestSuite : public Test
{
public:
    EquationConventerTestSuite() : sut(termConverter)
    {
    }
    std::shared_ptr<TermConverterMock> termConverter =
        std::make_shared<testing::StrictMock<TermConverterMock>>();
    EquationConventer sut;
};

TEST_F(EquationConventerTestSuite, xxx)
{
    sut.convert("2x3-2x2+x1+1>=0");
}

