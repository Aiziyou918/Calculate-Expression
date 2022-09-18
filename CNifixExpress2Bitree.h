#pragma once

#include <stack>
#include <string>
#include <vector>
#include "CDataBase.h"
#include "CBiTree.h"

using namespace std;

///operator string list
const string ListOperator = "+-*/^";

/// <summary>
/// class of translate nifix expression into bitree and calculate.
/// </summary>
class CNifixExpress2Bitree
{
public:
	CNifixExpress2Bitree(string pExpression);
	~CNifixExpress2Bitree() {};	
	double Calculate(CBitree *pExpress);
	double getValue() { return m_Result; };

private:
	CBitree* m_ExpressTree;
	double m_Result;

	bool isPriority(eOperator first, eOperator second);
	int priority(eOperator pOperator);
	CBitree* AnalysisExp(string pExpression);
	CBitree* CreateTreeExp(vector<CDataTypeBase*>& pSuffixStack);
};
