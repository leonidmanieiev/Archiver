#include "parse_hash_to_string.h"

map_qchar_quint
parse_str_to_hash(const QString& hash_rep)
{
    map_qchar_quint prob_of_chars;
    QStringList segments = hash_rep.split('|', QString::SkipEmptyParts);

    for(QStringList::iterator it = segments.begin(); it != segments.end(); ++it)
    {
        QChar ch(it->section('=', 0, 0).toUShort());
        prob_of_chars[ch] = it->section('=', 1, 1).toUInt();
    }

    return prob_of_chars;
}
