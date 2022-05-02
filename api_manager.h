#ifndef API_MANAGER_H
#define API_MANAGER_H
#include <QString>
#include <QPair>

namespace use_api{
QString get_publicIP();
QString get_prayerInfo();
QPair<QString,QString> get_data();
}



#endif // API_MANAGER_H
