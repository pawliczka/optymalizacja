#include "EquationConventer.hpp"
#include "TermConverterMock.hpp"
#include "Equation.hpp"
#include <gmock/gmock.h>
#include <list>
#include <memory>

using namespace testing;

class EquationConventerTestSuite : public Test
{
    using ExpectCallsList = std::list<std::pair<std::string, Term>>;

public:
    EquationConventerTestSuite()
        : sut(termConverter)
    {
    }
    std::shared_ptr<TermConverterMock> termConverter = std::make_shared<testing::StrictMock<TermConverterMock>>();
    EquationConventer sut;

    void expectTermConverterCalls(ExpectCallsList expectCallsList)
    {
        for (const auto& expectCall : expectCallsList)
        {
            EXPECT_CALL(*termConverter, convert(expectCall.first)).WillOnce(Return(expectCall.second));
        }
    }
};

TEST_F(EquationConventerTestSuite, xxx)
{
    expectTermConverterCalls({{"2x3", Term(2, 3)}, {"-2x2", Term(-2, 2)}, {"x1", Term(1, 1)}, {"1", Term(1, 0)}});
    sut.convert("2x3-2x2+x1+1>=0");
}
