#include "api_manager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <fstream>
#include <QString>
#include <QEventLoop>
#include <QPair>
#include <QTime>
#include <QStringRef>


QString use_api::get_publicIP(){
    QString ip_adres;
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString(("https://api.ipify.org?format=json") )) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        //success
        ip_adres = reply->readAll();


        delete reply;
    }
    else {
        //failure
        ip_adres = reply->errorString();
        delete reply;
    }
    return ip_adres;
}


QString use_api::get_prayerInfo(){
    QString prayerInfo;
    QEventLoop eventLoop;
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QNetworkRequest req( QUrl( QString(("https://api.pray.zone/v2/times/today.json?ip="+get_publicIP()) )) );
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        //success
        prayerInfo = reply->readAll();
        delete reply;
    }
    else {
        //failure
        prayerInfo = reply->errorString();
        delete reply;
    }
    return prayerInfo;
}


QPair<QString,QString> use_api::get_data(){
    QString mainInfo = get_prayerInfo();

    //{"code":200,"status":"OK","results":{"datetime":[{"times":{"Imsak":"03:26","Sunrise":"06:11","Fajr":"03:36","Dhuhr":"13:40","Asr":"17:44","Sunset":"21:09","Maghrib":"21:33","Isha":"23:33","Midnight":"00:23"}
    mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 68);
    QTime time(QTime::currentTime());
    QString val = time.toString("hh:mm");
    QPair<QString,QString> Imsak("Imsak", QStringRef(&mainInfo, 0, 5).toString());
    if(val <= Imsak.second){
        return Imsak;
    }else{
        mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 18);
        QPair<QString,QString> Sunrise("Sunrise", QStringRef(&mainInfo, 0, 5).toString());
        if(val <= Sunrise.second){
            return Sunrise;
        }else{
            mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 18);
            QPair<QString,QString> Fajr("Fajr", QStringRef(&mainInfo, 0, 5).toString());
            if(val <= Fajr.second){
                return Fajr;
            }else{
                mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 18);
                QPair<QString,QString> Dhuhr("Dhuhr", QStringRef(&mainInfo, 0, 5).toString());
                if(val <= Dhuhr.second){
                    return Dhuhr;
                }else{
                    mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 18);
                    QPair<QString,QString> Asr("Asr", QStringRef(&mainInfo, 0, 5).toString());
                    if(val <= Asr.second){
                        return Asr;
                    }else{
                        mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 18);
                        QPair<QString,QString> Sunset("Sunset", QStringRef(&mainInfo, 0, 5).toString());
                        if(val <= Sunset.second){
                            return Sunset;
                        }else{
                            mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 18);
                            QPair<QString,QString> Magrib("Magrib", QStringRef(&mainInfo, 0, 5).toString());
                            if(val <= Magrib.second){
                                return Magrib;
                            }else{
                                mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 18);
                                QPair<QString,QString> Isha("Isha", QStringRef(&mainInfo, 0, 5).toString());
                                if(val <= Isha.second){
                                    return Isha;
                                }
                            }
                        }
                    }
                }
            }
        }
    }


return QPair<QString,QString>("Error",mainInfo);
}












