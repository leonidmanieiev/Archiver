#ifndef GET_TEXT_FROM_FILE_H
#define GET_TEXT_FROM_FILE_H

#include <QTextStream>
#include <QFile>
#include <QMessageBox>
#include <stdexcept>

QString get_text_from_file(QWidget *parent, const QString& path);

#endif // GET_TEXT_FROM_FILE_H
