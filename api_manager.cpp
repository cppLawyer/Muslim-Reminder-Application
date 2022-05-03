#include "api_manager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
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
    mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 101);
    QString val = QTime(QTime::currentTime()).toString("hh:mm");

          QPair<QString,QString> Fajr("Fajr", std::move(QStringRef(&mainInfo, 0, 5).toString()));
           if(val <= Fajr.second){
              return Fajr;
           }else{
               mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 16);
                QPair<QString,QString> Dhuhr("Dhuhr", std::move(QStringRef(&mainInfo, 0, 5).toString()));
               if(val <= Dhuhr.second){
                    return Dhuhr;
                }else{
                    mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 14);
                    QPair<QString,QString> Asr("Asr", std::move(QStringRef(&mainInfo, 0, 5).toString()));
                    if(val <= Asr.second){
                        return Asr;
                    }else{
                           mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 35);
                            QPair<QString,QString> Magrib("Magrib", std::move(QStringRef(&mainInfo, 0, 5).toString()));
                            if(val <= Magrib.second){
                                return Magrib;
                            }else{
                               mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 15);
                                QPair<QString,QString> Isha("Isha", std::move(QStringRef(&mainInfo, 0, 5).toString()));
                                if(val <= Isha.second){
                                    return Isha;
                                }
                            }
                        }
                    }
                }





return QPair<QString,QString>("Error:","No Network Connection");
}












