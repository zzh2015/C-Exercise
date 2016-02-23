/*******************************************************************************
Copyright: 2015, Innovem Tech. Co., Ltd.
FileName: BiTreeOperation.h
*******************************************************************************/
#ifndef _BiTreeOperation_H_
#define _BiTreeOperation_H_
typedef struct BITNode {
    char m_Val;
    struct BITNode *m_Lchild, *m_Rchild;
}BITNode, *BITree;

extern void CreateBITree(BITree &);
extern bool BITreeEmpty(BITree);
extern int BITreeDepth(BITree);
extern bool Root(BITree);
extern char Value(BITree);

extern void Assign(BITree p, char e);
/*返回值为value节点的双亲节点的值*/
extern char ParentValue(BITree root, char e);
/*返回值为e的节点*/
extern BITree Point(BITree root, char e);

extern void PostOrder(BITree root);

#endif
