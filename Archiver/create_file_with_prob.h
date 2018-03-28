#ifndef CREATE_FILE_WITH_PROB_H
#define CREATE_FILE_WITH_PROB_H

#include "probability_of_chars.h"
#include "parse_hash_to_string.h"
#include "huffman_tree.h"
#include "alias.h"

#include <QFileDialog>

void save_as(QWidget* parent, const QString& filename,
             const QString& hash_rep, const quint64 &text_length);

QString create_file_with_prob(QWidget* parent, QString& text_to_compress,
                              map_qchar_quint& prob_of_chars);

#endif // CREATE_FILE_WITH_PROB_H
