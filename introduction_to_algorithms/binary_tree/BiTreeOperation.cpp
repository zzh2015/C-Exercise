/*******************************************************************************
Copyright: 2015, Innovem Tech. Co., Ltd.
FileName: BiTreeOperation.cpp
*******************************************************************************/
#include "BiTreeOperation.h"

#include <assert.h>
#include <deque>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

void CreateBITree(BITree &root)
{
    auto ch = '#';
    ch = getchar();
    if (ch == '#') {
        root = NULL;
    } else {
        root = new BITNode;
        root->m_Val = ch;
        CreateBITree(root->m_Lchild);
        CreateBITree(root->m_Rchild);
    }
}

bool BITreeEmpty(BITree root)
{
    if (root != NULL) {
        return true;
    } else {
        return false;
    }
}

int BITreeDepth(BITree root)
{
    auto i = 0;
    auto j = 0;

    if (root == NULL) {
        return 0;
    }
    if (root->m_Lchild != NULL) {
        i = BITreeDepth(root->m_Lchild);
    } else {
        i = 0;
    }

    if (root->m_Rchild != NULL) {
        j = BITreeDepth(root->m_Rchild);
    } else {
        j = 0;
    }

    return (i>j ? i+1 : j+1);
}

void Assign(BITree p, char e)
{
    p->m_Val = e;
}

char ParentValue(BITree root, char e)
{
    std::deque<BITree> q;
    auto p = root;
    if (root != NULL) {
        q.push_back(root);
        while(!q.empty()) {
            p = q.front();
            q.pop_front();
            if (p->m_Lchild != NULL && p->m_Lchild->m_Val == e
                    || p->m_Rchild != NULL && p->m_Rchild->m_Val == e) {
                return p->m_Val;
            } else {
                if (p->m_Lchild != NULL) {
                    q.push_back(p->m_Lchild);
                }
                if (p->m_Rchild != NULL) {
                    q.push_back(p->m_Rchild);
                }
            }
        }
    }

    return '#';
}

BITree Point(BITree root, char e)
{
    std::deque<BITree> q;
    auto p = root;
    q.push_back(root);
    while(!q.empty()) {
        p = q.front();
        q.pop_front();
        if (p->m_Val == e) {
            return p;
        }

        if (p->m_Lchild != NULL) {
            q.push_back(p->m_Lchild);
        }

        if (p->m_Rchild != NULL) {
            q.push_back(p->m_Rchild);
        }
    }
    return NULL;
}

void PostOrder(BITree root)
{
    if (root == NULL) {
        return;
    }
    std::stack<BITree> s;
    std::vector<char> v;
    auto pCur = root;
    auto pLast = root;
    pLast = NULL;
    //pCur移动到左子树最下边
    while (pCur) {
        s.push(pCur);
        pCur = pCur->m_Lchild;
    }
    while (!s.empty()) {
        pCur = s.top();
        s.pop();
        if (pCur->m_Rchild == NULL
                || pCur->m_Rchild == pLast) {
            v.push_back(pCur->m_Val);
            pLast = pCur;
        } else {
            s.push(pCur);
            pCur = pCur->m_Rchild;
            while (pCur != NULL) {
                s.push(pCur);
                pCur = pCur->m_Lchild;
            }
        }
    }
    
    printf("post order:\n");
    for (auto c : v) {
        printf("%c", c);
    }
    printf("\n");
}

int main()
{
    BITNode *root = NULL;
    //ab#d##c#e##
    CreateBITree(root);
    auto ret = BITreeDepth(root);
    printf("ret: %d\n", ret);
    printf("ch: %c\n", ParentValue(root, 'e'));
    auto p = Point(root, 'b');
    if (p!=NULL) {
        printf("ch:%c\n", p->m_Val);
    }
    PostOrder(root);

    return 0;
}
