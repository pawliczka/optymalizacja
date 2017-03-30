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
    //EXPECT_CALL(*termConverter, convert("2x1")).WillOnce(Return(std::make_pair(2, 1)));

}

