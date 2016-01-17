#ifndef LOCALDATA_H
#define LOCALDATA_H

#include <QVariantMap>

namespace Model
{
    class LocalData
    {
    public:
        static LocalData    *instance();
        static void         deleteInstance();

        QVariantMap         Values;

    private:
        LocalData();
        LocalData(const LocalData &);
        ~LocalData();
        LocalData   &operator=(const LocalData &);

        static LocalData    *_instance;
    };
}

#endif // LOCALDATA_H
