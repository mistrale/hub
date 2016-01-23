#ifndef VIDEOSEARCH_H
#define VIDEOSEARCH_H

#include <QVariant>

namespace Model {
    class VideoSearch
    {
    public:
        VideoSearch();

        void            setValue(const QString &key, const QVariant &value);
        QVariant        getValue(const QString &key);

    private:
        QVariantMap     _values;
    };
}


#endif // VIDEOSEARCH_H
