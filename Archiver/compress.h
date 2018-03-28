#ifndef COMPRESS_H
#define COMPRESS_H

#include "alias.h"

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

void compress(QWidget *parent, const hash_qchar_qstr& hash_qchar_code,
              const QString& archive_name, const QString& text_to_compress);

#endif // COMPRESS_H
