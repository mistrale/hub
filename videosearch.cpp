#include "videosearch.h"

Model::VideoSearch::VideoSearch()
{

}

QVariant        Model::VideoSearch::getValue(const QString &key) {
    return _values[key];
}

void            Model::VideoSearch::setValue(const QString &key, const QVariant &value) {
    _values[key] = value;
}
