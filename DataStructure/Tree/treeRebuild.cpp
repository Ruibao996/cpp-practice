# include <iostream>
# include <stdexcept>
# include "../../Utilities/BinaryTree.h"
using namespace std;

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);

BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
{
    if (preorder == nullptr || inorder == nullptr)
        return nullptr;

    return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length -1);
}

BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
{
    BinaryTreeNode* root  = new BinaryTreeNode();
    int root_value = startPreorder[0];
    root->m_nValue = root_value;
    root->m_pLeft = root->m_pRight = nullptr;

    if (startPreorder == endPreorder)
    {
        if (startInorder == endInorder && startInorder == startPreorder)
            return root;

        else
            throw std::invalid_argument("Invalid input");
    }

    int* rootInorder = startInorder;
    while (rootInorder <= endInorder && *rootInorder != root_value)
    {
        ++rootInorder;
    }

    if (rootInorder == endInorder && *rootInorder != root_value)
        throw std::invalid_argument("Invalid input");

    int leftLength = rootInorder - startInorder;
    int* leftEndPreorder = startPreorder + leftLength;

    if (leftLength > 0)
    {
        root->m_pLeft = ConstructCore(startPreorder + 1, leftEndPreorder, startInorder, rootInorder - 1);
    }

    if (leftLength < endPreorder - startPreorder)
    {
        root->m_pRight = ConstructCore(leftEndPreorder + 1, endPreorder, rootInorder + 1, endInorder);
    }

    return root;
}


// ====================测试代码====================
void Test(const char* testName, int* preorder, int* inorder, int length)
{
    if(testName != nullptr)
        printf("%s begins:\n", testName);

    printf("The preorder sequence is: ");
    for(int i = 0; i < length; ++ i)
        printf("%d ", preorder[i]);
    printf("\n");

    printf("The inorder sequence is: ");
    for(int i = 0; i < length; ++ i)
        printf("%d ", inorder[i]);
    printf("\n");

    try
    {
        BinaryTreeNode* root = Construct(preorder, inorder, length);
        PrintTree(root);

        DestroyTree(root);
    }
    catch(std::exception& exception)
    {
        printf("Invalid Input.\n");
    }
}

// 普通二叉树
//              1
//           /     \
//          2       3  
//         /       / \
//        4       5   6
//         \         /
//          7       8
void Test1()
{
    const int length = 8;
    int preorder[length] = {1, 2, 4, 7, 3, 5, 6, 8};
    int inorder[length] = {4, 7, 2, 1, 5, 3, 8, 6};

    Test("Test1", preorder, inorder, length);
}

// 所有结点都没有右子结点
//            1
//           / 
//          2   
//         / 
//        3 
//       /
//      4
//     /
//    5
void Test2()
{
    const int length = 5;
    int preorder[length] = {1, 2, 3, 4, 5};
    int inorder[length] = {5, 4, 3, 2, 1};

    Test("Test2", preorder, inorder, length);
}

// 所有结点都没有左子结点
//            1
//             \ 
//              2   
//               \ 
//                3 
//                 \
//                  4
//                   \
//                    5
void Test3()
{
    const int length = 5;
    int preorder[length] = {1, 2, 3, 4, 5};
    int inorder[length] = {1, 2, 3, 4, 5};

    Test("Test3", preorder, inorder, length);
}

// 树中只有一个结点
void Test4()
{
    const int length = 1;
    int preorder[length] = {1};
    int inorder[length] = {1};

    Test("Test4", preorder, inorder, length);
}

// 完全二叉树
//              1
//           /     \
//          2       3  
//         / \     / \
//        4   5   6   7
void Test5()
{
    const int length = 7;
    int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
    int inorder[length] = {4, 2, 5, 1, 6, 3, 7};

    Test("Test5", preorder, inorder, length);
}

// 输入空指针
void Test6()
{
    Test("Test6", nullptr, nullptr, 0);
}

// 输入的两个序列不匹配
void Test7()
{
    const int length = 7;
    int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
    int inorder[length] = {4, 2, 8, 1, 6, 3, 7};

    Test("Test7: for unmatched input", preorder, inorder, length);
}

int main(int argc, char* argv[])
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();

    return 0;
}