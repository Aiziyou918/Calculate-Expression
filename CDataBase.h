#pragma once

#include <cstdlib>
#include <string>

using namespace std;

/// <summary>
/// enum operator
/// </summary>
enum class eOperator : char
{
	ADD, SUB, MULTI, DIVISON, POWER, FUNC, DOT, NONE,
};


/// <summary>
/// base class of Data
/// </summary>
class CDataTypeBase
{
public:
	CDataTypeBase() {};
	virtual ~CDataTypeBase() {};
	virtual double getValueData() { return 0.0; };
	virtual eOperator getValueOperator() { return eOperator::NONE; };
	virtual string getValueBracket() { return ""; };

};


/// <summary>
/// class of data
/// </summary>
class CData : public CDataTypeBase
{
public:
	CData(string pDataExpress) { m_Data = stod(pDataExpress, NULL); };
	~CData() {};
	double getValueData() { return m_Data; };

private:
	double m_Data;
};


/// <summary>
/// class of operator
/// </summary>
class COperator : public CDataTypeBase
{
public:
	COperator(eOperator pOperator) { m_Operator = pOperator; };
	~COperator() {};
	
	eOperator getValueOperator() { return m_Operator; };
private:
	eOperator m_Operator;
};


/// <summary>
/// class of bracket
/// </summary>
class CBracket : public CDataTypeBase
{
public:
	CBracket(string pExpression) { m_Expression = pExpression; };
	~CBracket() {};
	string getValueBracket() { return m_Expression; };

private:
	string m_Expression;
};

