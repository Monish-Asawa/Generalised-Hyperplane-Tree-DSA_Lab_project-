#ifndef TREE_H
#define TREE_H

#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

#define n 10

struct data {
    float values[n];
};

// using list = vector<struct data>;

struct node {
    struct data pivot1;
    struct data pivot2;
    struct node* lchild;
    struct node* rchild;
    struct node* parent;
};

float distance(struct data a, struct data b);

struct node* new_node( vector<struct data> pivots, node* y);

void insert_node(node** root,  vector<struct data> pivots);

#endif /* TREE_H */
