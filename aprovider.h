#ifndef APROVIDER_H
#define APROVIDER_H

#include <QString>

namespace Tool {
class AProvider
{
public:
    AProvider();
    virtual ~AProvider();

    virtual std::string     &getFlow(const QString &url) = 0;
};

class   YoutubeProvider : public AProvider {
public:
    YoutubeProvider();
    ~YoutubeProvider();

    std::string     &getFlow(const QString &url);
};

}


#endif // APROVIDER_H
