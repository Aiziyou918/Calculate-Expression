#pragma once

#include "CDataBase.h"

/// <summary>
/// express binary tree
/// </summary>
class CBitree
{
public:
	CBitree(CDataTypeBase* pData) { m_data = pData; };
	~CBitree();
	void setLChild(CBitree* pLeftChild) { m_LeftChild = pLeftChild; };
	void setRChild(CBitree* pRightChild) { m_RightChild = pRightChild; };
	CDataTypeBase* getValue() { return m_data; };

	CBitree* m_LeftChild;
	CBitree* m_RightChild;

private:
	CDataTypeBase* m_data;

	void deleteTree(CBitree* pTree);
};

