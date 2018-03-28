#include "compress.h"

void compress(QWidget *parent, const hash_qchar_qstr& hash_qchar_code,
              const QString& archive_name, const QString& text_to_compress)
{
    QFile out_file(archive_name);

    if(!out_file.open(QFile::WriteOnly | QFile::Text | QFile::Append))
    {
        QMessageBox::warning(parent, "Error", "File cannot be open");
        throw std::invalid_argument("compress()::invalid file");
    }

    int shifts_cnt = 0;
    unsigned char buf = 0;
    bool buf_set = false;

    foreach(const QChar& ch, text_to_compress)
    {
        QString code = hash_qchar_code[ch];

        foreach(const QChar& bit, code)
        {
            bool bbit = bit == '1' ? true : false;
            buf |= bbit << (7 - shifts_cnt);
            buf_set = true;

            shifts_cnt++;

            if(shifts_cnt == 8)
            {
                out_file.write(reinterpret_cast<char *>(&buf),
                               sizeof(buf));
                shifts_cnt = 0; buf = 0;
                buf_set = false;
            }
        }
    }

    if(buf_set)
    {
        out_file.write(reinterpret_cast<char *>(&buf), sizeof(buf));
    }

    out_file.flush();
    out_file.close();
}
