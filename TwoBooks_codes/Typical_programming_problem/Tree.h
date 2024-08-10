
#pragma once

struct BinaryTreeNode
{
    double                 m_dbValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

__declspec(dllexport) BinaryTreeNode* CreateBinaryTreeNode(double dbValue);
__declspec(dllexport) void ConnectTreeNodes(BinaryTreeNode* pParent, BinaryTreeNode* pLeft, BinaryTreeNode* pRight);
__declspec(dllexport) void DestroyTree(BinaryTreeNode* pRoot);

 
