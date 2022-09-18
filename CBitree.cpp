#include "CBitree.h"

CBitree::~CBitree()
{
	deleteTree(this);
}

/// <summary>
/// delete Tree
/// </summary>
/// <param name="pTree"></param>
void CBitree::deleteTree(CBitree* pTree)
{
	if (pTree)
	{
		if (!pTree->m_LeftChild && !pTree->m_RightChild)
		{
			delete pTree->m_data;
			return;
		}
		delete pTree->m_LeftChild;
		delete pTree->m_RightChild;
		delete pTree->m_data;	
	}
	deleteTree(m_LeftChild);
	deleteTree(m_RightChild);
}