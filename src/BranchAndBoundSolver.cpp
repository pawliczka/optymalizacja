#include "BranchAndBoundSolver.hpp"
#include "SimplexStatus.hpp"
#include <cmath>
#include <iostream>

BranchAndBoundSolver::BranchAndBoundSolver(std::shared_ptr<LinearProblem> linearProblem)
{
    m_initialProblem = linearProblem;
    m_numberOfVariables = linearProblem->getn();
    m_newConstrain.resizeEquation(linearProblem->getn());
    m_newConstrain.clear();
    m_newConstrain.setComparisonOperator(ComparisonOperator::None);

    m_rootNode = std::make_shared<NodeOfSolution>(linearProblem, 1, m_newConstrain);

    m_nodesOfSolution.push_front(m_rootNode);
    if (linearProblem->gettype() == OptimizeType::MIN)
        m_valueOfBestObjectiveFunction = std::numeric_limits<float>::max();
    else
        m_valueOfBestObjectiveFunction = std::numeric_limits<float>::lowest();
    m_optimizeType = linearProblem->gettype();
}

std::vector<std::shared_ptr<LinearProblemSolution>> BranchAndBoundSolver::Solve()
{
    Simplex simplex;
    std::shared_ptr<LinearProblem> tempProblem = std::make_shared<LinearProblem>(*m_initialProblem);

    while (!m_nodesOfSolution.empty())
    {
        std::cout << "Nakurwiam while'a" << std::endl;
        std::cout << "Liczba problemow do rozwiazania:   " << m_nodesOfSolution.size() << std::endl;
        std::shared_ptr<NodeOfSolution> tempNode = m_nodesOfSolution.front();
        m_nodesOfSolution.pop_front();

        tempNode->m_solution = simplex.Solve(*(tempNode->m_linearProblem.get()));


        tempProblem = std::make_shared<LinearProblem>(*(tempNode->m_linearProblem));
        if (simplex.getStatus() != SimplexStatus::STATUS_SOLVED)
        {
            std::cout << "Zly status, nastepna petla" << std::endl;
            continue;
        }

        if (IsSolutionIsInteger(*(tempNode->m_solution.get())))
        {
            InsertSolutionIsBetter(tempNode);
            std::cout << "Rozwiazanie calkowitoliczbowe > branch Not Needed" << std::endl;
        }
        else
        {
            std::cout << "probuje brancha" << std::endl;
            Branch(tempProblem, tempNode);
        }

        std::cout << "Liczba problemow do rozwiazania po petli:   " << m_nodesOfSolution.size() << std::endl;
    }
    SetRecursiveOptimalId(m_rootNode);
    return m_optimalSolutions;
}

#define LOWER_BOUND_ID(ID) (ID * 2 + 1)
#define UPPER_BOUND_ID(ID) (ID * 2 + 2)

void BranchAndBoundSolver::SingleBranch(std::shared_ptr<NodeOfSolution> tempNode,
    std::shared_ptr<LinearProblem> tempProblem, ComparisonOperator typeOfBound)
{
    int indexOfFirstNonIntegerElement = getIndexOfFirstNonInteger(*(tempNode->m_solution.get()));

    std::shared_ptr<LinearProblem> newProblem = std::make_shared<LinearProblem>(*tempProblem);
    m_newConstrain.clear();
    m_newConstrain.setCoefficient(std::make_pair(1, indexOfFirstNonIntegerElement + 1));

    if (typeOfBound == ComparisonOperator::LessEqual)
    {
        float lower_bound = std::floor(tempNode->m_solution->VariableValues[indexOfFirstNonIntegerElement]);
        m_newConstrain.setCoefficient(std::make_pair(-lower_bound, 0));
        m_newConstrain.setComparisonOperator(ComparisonOperator::LessEqual);
    }
    if (typeOfBound == ComparisonOperator::GreaterEqual)
    {
        float upper_bound = 1 + (std::floor(tempNode->m_solution->VariableValues[indexOfFirstNonIntegerElement]));
        m_newConstrain.setCoefficient(std::make_pair(-upper_bound, 0));
        m_newConstrain.setComparisonOperator(ComparisonOperator::GreaterEqual);
    }
    newProblem->addConstrain(m_newConstrain);

    if (typeOfBound == ComparisonOperator::LessEqual)
    {
        std::shared_ptr<NodeOfSolution> lowerNode =
            std::make_shared<NodeOfSolution>(newProblem, LOWER_BOUND_ID(tempNode->m_Id), m_newConstrain);
        tempNode->m_lowerBoundNode = lowerNode;
        m_nodesOfSolution.push_front(lowerNode);
    }

    if (typeOfBound == ComparisonOperator::GreaterEqual)
    {
        std::shared_ptr<NodeOfSolution> upperNode =
            std::make_shared<NodeOfSolution>(newProblem, UPPER_BOUND_ID(tempNode->m_Id), m_newConstrain);
        tempNode->m_upperBoundNode = upperNode;
        m_nodesOfSolution.push_front(upperNode);
    }
}

void BranchAndBoundSolver::Branch(std::shared_ptr<LinearProblem> tempProblem, std::shared_ptr<NodeOfSolution> tempNode)
{
    std::cout << "Obecnie BestObjFunValue:  " << m_valueOfBestObjectiveFunction << std::endl;
    tempNode->print();
    if (((m_optimizeType == OptimizeType::MAX) &&
            (m_valueOfBestObjectiveFunction <= tempNode->m_solution->ObjFuncValue)) ||
        ((m_optimizeType == OptimizeType::MIN) &&
            (m_valueOfBestObjectiveFunction >= tempNode->m_solution->ObjFuncValue)))
    {
        SingleBranch(tempNode, tempProblem, ComparisonOperator::LessEqual);
        SingleBranch(tempNode, tempProblem, ComparisonOperator::GreaterEqual);
    }
}

bool BranchAndBoundSolver::IsSolutionIsInteger(const LinearProblemSolution& solution) const
{
    double FractionalPart;
    double IntegerPart;

    for (auto const& elem : solution.VariableValues)
    {
        FractionalPart = std::modf(elem, &IntegerPart);
        if (FractionalPart > m_precision && FractionalPart < (1 - m_precision))
            return false;
    }

    return true;
}

void BranchAndBoundSolver::InsertSolutionIsBetter(std::shared_ptr<NodeOfSolution> node)
{
    if (((m_optimizeType == OptimizeType::MAX) && (m_valueOfBestObjectiveFunction < node->m_solution->ObjFuncValue)) ||
        ((m_optimizeType == OptimizeType::MIN) && (m_valueOfBestObjectiveFunction > node->m_solution->ObjFuncValue)))
    {
        m_optimalSolutions.clear();
        m_idOptimalNodes.clear();
        m_valueOfBestObjectiveFunction = node->m_solution->ObjFuncValue;
        m_optimalSolutions.push_back(node->m_solution);
        m_idOptimalNodes.push_back(node->m_Id);
    }

    else if (m_valueOfBestObjectiveFunction == node->m_solution->ObjFuncValue)
    {
        m_optimalSolutions.push_back(node->m_solution);
        m_idOptimalNodes.push_back(node->m_Id);
    }
}

int BranchAndBoundSolver::getIndexOfFirstNonInteger(const LinearProblemSolution& solution) const
{
    int index = 0;
    double FractionalPart;
    double IntegerPart;

    for (int i = 0; i < static_cast<int>(solution.VariableValues.size()); i++)
    {
        FractionalPart = std::modf(solution.VariableValues[i], &IntegerPart);
        if (FractionalPart > m_precision && FractionalPart < (1 - m_precision))
        {
            index = i;
            break;
        }
    }
    return index;
}

void BranchAndBoundSolver::SetRecursiveOptimalId(std::shared_ptr<NodeOfSolution> node)
{
    for (auto const &id : m_idOptimalNodes)
    {
        if(node->m_Id == id)
            node->isOptimal = true;
    }

    if((node->m_lowerBoundNode != nullptr) || (node->m_upperBoundNode != nullptr))
    {
        SetRecursiveOptimalId(node->m_lowerBoundNode);
        SetRecursiveOptimalId(node->m_upperBoundNode);
    }
}

std::shared_ptr<NodeOfSolution> BranchAndBoundSolver::GetRoot()
{
    return m_rootNode;
}

void BranchAndBoundSolver::setPrecision(float precision)
{
    m_precision = precision;
}
