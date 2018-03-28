#include "get_text_from_file.h"

QString get_text_from_file(QWidget *parent, const QString& path)
{
    QFile in_file(path);

    if(!in_file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(parent, "Error", "File cannot be open");
        throw std::invalid_argument("get_text_from_file()::invalid file");
    }

    QTextStream ts_in(&in_file);
    QString text = ts_in.readAll();

    in_file.close();
    return text;
}
