#include "videosearch.h"

Model::VideoSearch::VideoSearch()
{

}

QVariant        Model::VideoSearch::getValue(const QString &key) const {
    return _values[key];
}

QVariantMap     Model::VideoSearch::getValues() const {
    return _values;
}

void            Model::VideoSearch::setValue(const QString &key, const QVariant &value) {
    _values[key] = value;
}
