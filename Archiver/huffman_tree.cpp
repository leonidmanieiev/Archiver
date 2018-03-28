#include "huffman_tree.h"

hash_qchar_qstr get_codes(Node* root, QString str)
{
    static hash_qchar_qstr hash_char_code;

    if(!root) return hash_char_code;

    if(root->data != '$') hash_char_code[root->data] = str;

    hash_char_code = get_codes(root->left, str + "0");
    hash_char_code = get_codes(root->right, str + "1");

    return hash_char_code;
}

Node* create_huffman_tree(const map_qchar_quint& prob_of_chars)
{
    Node *root, *left, *right;
    min_heap m_heap;

    foreach(const auto& key, prob_of_chars.keys())
        m_heap.push(new Node(key, prob_of_chars[key]));

    while(m_heap.size() != 1)
    {
        left = m_heap.top();
        m_heap.pop();

        right = m_heap.top();
        m_heap.pop();

        root = new Node('$', left->freq + right->freq);
        root->left = left;
        root->right = right;

        m_heap.push(root);
    }

    return m_heap.top();
}
