#include "CNifixExpress2Bitree.h"

CNifixExpress2Bitree::CNifixExpress2Bitree(string pExpression)
{
	m_ExpressTree = AnalysisExp(pExpression);
	m_Result = Calculate(m_ExpressTree);
}

/// <summary>
/// judge priority
/// </summary>
/// <param name="first"></param>
/// <param name="second"></param>
/// <returns></returns>
bool CNifixExpress2Bitree::isPriority(eOperator first, eOperator second)
{
	return priority(first) >= priority(second) ? true : false;
}

/// <summary>
/// get priority
/// </summary>
/// <param name="pOperator"></param>
/// <returns></returns>
int CNifixExpress2Bitree::priority(eOperator pOperator)
{
	switch (pOperator)
	{
	case eOperator::ADD: return 1;
		break;
	case eOperator::SUB: return 1;
		break;
	case eOperator::MULTI: return 2;
		break;
	case eOperator::DIVISON: return 2;
		break;
	case eOperator::POWER: return 3;
		break;
	default:
		break;
	}
}

/// <summary>
/// translate expression into tree
/// </summary>
/// <param name="pExpression"></param>
/// <returns></returns>
CBitree* CNifixExpress2Bitree::AnalysisExp(string pExpression)
{
	stack<CDataTypeBase*> sOperator;
	vector<CDataTypeBase*> vSuffixExpress;
	for (int i = 0; i < pExpression.size(); i++)
	{
		//find bracket pair
		if (pExpression[i] == '(')
		{
			int LSum = 1;
			int RSum = 0;
			int location;
			for (int j = i + 1; j < pExpression.size(); j++)
			{
				if (pExpression[j] == '(')
					LSum++;
				else if (pExpression[j] == ')')
					RSum++;
				if (RSum == LSum)
				{
					location = j;
					break;
				}

			}
			string expressBracket = pExpression.substr(i + 1, location - i - 1);
			CBracket *bracket = new CBracket(expressBracket);
			vSuffixExpress.push_back(bracket);
			i = location;
		}
		//operator into stack and judge priority, translate into suffix expression
		else if(pExpression[i] == '+')
		{
			if (sOperator.empty() || !isPriority(sOperator.top()->getValueOperator(), eOperator::ADD))
				sOperator.push(new COperator(eOperator::ADD));
			else
			{
				while (isPriority(sOperator.top()->getValueOperator(), eOperator::ADD) && !sOperator.empty())
				{
					vSuffixExpress.push_back(sOperator.top());
					sOperator.pop();
					if(sOperator.empty())
						break;
				}
				sOperator.push(new COperator(eOperator::ADD));
			}
		}
		else if (pExpression[i] == '-')
		{
			if (sOperator.empty() || !isPriority(sOperator.top()->getValueOperator(), eOperator::SUB))
				sOperator.push(new COperator(eOperator::SUB));
			else
			{
				while (isPriority(sOperator.top()->getValueOperator(), eOperator::SUB) && !sOperator.empty())
				{
					vSuffixExpress.push_back(sOperator.top());
					sOperator.pop();
					if (sOperator.empty())
						break;
				}
				sOperator.push(new COperator(eOperator::SUB));
			}
		}
		else if (pExpression[i] == '*')
		{
			if (sOperator.empty() || !isPriority(sOperator.top()->getValueOperator(), eOperator::MULTI))
				sOperator.push(new COperator(eOperator::MULTI));
			else
			{
				while (isPriority(sOperator.top()->getValueOperator(), eOperator::MULTI) && !sOperator.empty())
				{
					vSuffixExpress.push_back(sOperator.top());
					sOperator.pop();
					if (sOperator.empty())
						break;
				}
				sOperator.push(new COperator(eOperator::MULTI));
			}
		}
		else if (pExpression[i] == '/')
		{
			if (sOperator.empty() || !isPriority(sOperator.top()->getValueOperator(), eOperator::DIVISON))
				sOperator.push(new COperator(eOperator::DIVISON));
			else
			{
				while (isPriority(sOperator.top()->getValueOperator(), eOperator::DIVISON) && !sOperator.empty())
				{
					vSuffixExpress.push_back(sOperator.top());
					sOperator.pop();
					if (sOperator.empty())
						break;
				}
				sOperator.push(new COperator(eOperator::DIVISON));
			}
		}
		else if (pExpression[i] == '^')
		{
			if (sOperator.empty() || !isPriority(sOperator.top()->getValueOperator(), eOperator::POWER))
				sOperator.push(new COperator(eOperator::POWER));
			else
			{
				while (isPriority(sOperator.top()->getValueOperator(), eOperator::POWER) && !sOperator.empty())
				{
					vSuffixExpress.push_back(sOperator.top());
					sOperator.pop();
					if (sOperator.empty())
						break;
				}
				sOperator.push(new COperator(eOperator::POWER));
			}
		}
		//process space
		else if(pExpression[i] == ' ')
			continue;
		//process data
		else
		{
			string temp = pExpression.substr(i, pExpression.size() - i);
			int loc = temp.find_first_of(ListOperator);
			if (loc == string::npos)
				loc = 1;
			string express = temp.substr(0, loc);
			vSuffixExpress.push_back(new CData(express));
		}
	}
	while (!sOperator.empty())
	{
		vSuffixExpress.push_back(sOperator.top());
		sOperator.pop();
	}
	return CreateTreeExp(vSuffixExpress);
}

/// <summary>
/// create expression tree
/// </summary>
/// <param name="pSuffixStack"></param>
/// <returns></returns>
CBitree* CNifixExpress2Bitree::CreateTreeExp(vector<CDataTypeBase*>& pSuffixStack)
{
	stack<CBitree*> stackTree;
	for (int i = 0; i < pSuffixStack.size(); i++)
	{
		if (dynamic_cast<CData*>(pSuffixStack[i]) || dynamic_cast<CBracket*>(pSuffixStack[i]))
		{
			CBitree* node = new CBitree(pSuffixStack[i]);
			stackTree.push(node);
		}
		else if (dynamic_cast<COperator*>(pSuffixStack[i]))
		{
			CBitree* node = new CBitree(pSuffixStack[i]);
			node->setRChild(stackTree.top());
			stackTree.pop();
			node->setLChild(stackTree.top());
			stackTree.pop();
			stackTree.push(node);
		}
	}
	return stackTree.top();
}


/// <summary>
/// calculate result
/// </summary>
/// <param name="pExpress"></param>
/// <returns></returns>
double CNifixExpress2Bitree::Calculate(CBitree *pExpress)
{
	double lValue = 0, RValue = 0;
	if (dynamic_cast<CData*>(pExpress->getValue()) && pExpress)
		return pExpress->getValue()->getValueData();
	else if (dynamic_cast<COperator*>(pExpress->getValue()) && pExpress)
	{
		lValue = Calculate(pExpress->m_LeftChild);
		RValue = Calculate(pExpress->m_RightChild);
		switch (pExpress->getValue()->getValueOperator())
		{
		case eOperator::ADD: return lValue + RValue;
			break;
		case eOperator::SUB: return lValue - RValue;
			break;
		case eOperator::MULTI: return lValue * RValue;
			break;
		case eOperator::DIVISON: return lValue / RValue;
			break;
		case eOperator::POWER: return pow(lValue, RValue);
		default:
			break;
		}
	}
	else if (dynamic_cast<CBracket*>(pExpress->getValue()) && pExpress)
	{
		CBitree *Bitree= AnalysisExp(pExpress->getValue()->getValueBracket());
		return Calculate(Bitree);
	}
}