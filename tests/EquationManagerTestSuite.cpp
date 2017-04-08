#include "EquationManager.hpp"
#include "EquationConventerMock.hpp"
#include <gmock/gmock.h>

using namespace testing;

class EquationManagerTestSuite : public testing::Test
{
public:
    EquationManagerTestSuite()
        : sut(m_equationConventerMock)
    {
    }

    std::shared_ptr<StrictMock<EquationConventerMock>> m_equationConventerMock =
        std::make_shared<StrictMock<EquationConventerMock>>();

    EquationManager sut;
};

TEST_F(EquationManagerTestSuite, init)
{
    sut.convertToEquations();
}
