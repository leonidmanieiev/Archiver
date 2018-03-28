#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include "alias.h"

#include <queue>

struct Node;
struct cmp;

using min_heap = std::priority_queue<Node*, QVector<Node*>, cmp>;

struct Node
{
    QChar data;
    quint32 freq;
    Node* left;
    Node* right;

    Node(QChar data, quint32 freq)
    {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

struct cmp
{
    bool operator()(Node* left, Node* right)
    {
        return left->freq > right->freq;
    }
};

Node* create_huffman_tree(const map_qchar_quint& prob_of_chars);

hash_qchar_qstr get_codes(Node* root, QString str);

#endif // HUFFMAN_TREE_H
