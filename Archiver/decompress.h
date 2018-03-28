#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include "huffman_tree.h"
#include "parse_string_to_hash.h"

#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <fstream>

void adapt_char(std::ifstream& in_file, int& byte);

void decompress(QWidget *parent);

#endif // DECOMPRESS_H
