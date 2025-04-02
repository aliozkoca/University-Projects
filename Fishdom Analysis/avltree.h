
struct data
{
    char name[80];
    float lenght;
    char date[80];
    char city[80];
    struct data*next;
};
struct Avltree
{
    float weight;
    int height;
    struct data*data;
    struct Avltree*left;
    struct Avltree*right;
};
typedef struct Avltree*tree;
int Max(int,int);
int AvlTreeHeight(tree);
tree SingleRotateWithLeft(tree);
tree SingleRotateWithRight(tree );
tree DoubleRotateWithLeft(tree );
tree DoubleRotateWithRight(tree );
int Max(int x, int y)
{
    if (x >= y)
        return x;
    else
        return y;
}

int AVLTreeHeight(tree t)
{
    if (t == NULL)
        return -1;
    else
        return t->height;
}
tree SingleRotateWithLeft(tree k2)
{
    tree k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;
    k1->height= Max(AVLTreeHeight(k1->right), AVLTreeHeight(k1->left));
    k2->height=Max(AVLTreeHeight(k2->right), AVLTreeHeight(k2->left));
    return k1;
}
tree SingleRotateWithRight(tree k1)
{
    tree k2=k1->right;
    k1->right=k2->left;
    k2->left=k1;
    k1->height= Max(AVLTreeHeight(k1->right), AVLTreeHeight(k1->left));
    k2->height=Max(AVLTreeHeight(k2->right), AVLTreeHeight(k2->left));
    return k2;

}
tree DoubleRotateWithLeft(tree k3)
{
    k3->left= SingleRotateWithRight(k3->left);
    return SingleRotateWithLeft(k3);
}
tree DoubleRotateWithRight(tree k3)
{
    k3->right= SingleRotateWithLeft(k3->right);
    return SingleRotateWithRight(k3);
}

#ifndef ASSIGMENT_3_AVLTREE_H
#define ASSIGMENT_3_AVLTREE_H

#endif //ASSIGMENT_3_AVLTREE_H
