/*
************************************************************************************************************
-------------------------------------------------- cppLawyer -----------------------------------------------


- Messy code >--------> because it is highly optimized <----------<
+ Low stack memory usage
+ Almost No function overhead
+ Regulate Stack Memory
+ Aggressive but peaceful
+ Low Ram Usage
+ Low Power Usage
+ Beautiful Adhan
+ Shows Accurate Prayer Times based on IP/Location
+ Shows How Many Minutes for the next prayer
+ Almost no CPU Usage
------------------------------------------------------------------------------------------------------------
************************************************************************************************************
*/

#ifndef MAIN_H
#define MAIN_H
#include <QMediaPlayer>
#include <QWidget>
#include "ui_gui.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QEventLoop>
#include <QTime>
#include <QStringRef>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget
{
    Q_OBJECT
public:
    gui(QWidget *parent = nullptr): QWidget(parent),ui(new Ui::gui) {
      ui->setupUi(this);


    }
    /////////////////////////////
    std::thread operationThread;
    QMediaPlayer adhanPlayer;
    QTime prayerTime;
    /////////////////////////////
    ~gui()
    {
        operationThread.detach();
        delete ui;
    }
    inline void reTryMessage() noexcept{
        ui->CurrentPrayer->setText(std::move("Reconnect"));
        ui->nextPrayer->setText(std::move("To Server"));
        ui->timeTogo->setText(std::move("--:--:--"));
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }/*Setting Message to user that it is reconnecting to server*/

 void set_data() noexcept{
           QString mainInfo;

          {
               /*getting public id and see where you are*/
           QString ip_adres;
           QEventLoop eventLoop;
           QNetworkAccessManager mgr;
           QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
           QNetworkRequest req( std::move(QUrl( std::move(QString(("https://api.ipify.org?format=json") ))) ));
           QNetworkReply *reply = std::move(mgr.get(req));
           eventLoop.exec();
           if (reply->error() == QNetworkReply::NoError) {
               //success
              //Example ip {"ip":"00.00.000.00"}
                QString jsonData(reply->readAll());
                jsonData.erase((jsonData.begin() + jsonData.size() - 2),jsonData.end());
                jsonData.erase(jsonData.begin(),jsonData.begin() + 7);
                ip_adres = std::move(jsonData);
                delete reply;

           } else { ip_adres = reply->errorString();
               delete reply; }//failure

               {
               /*Using public ip to determine prayer times for that place*/
               QEventLoop eventLoop;
               QNetworkAccessManager mgr;
               QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
               QNetworkRequest req( std::move(QUrl( std::move(QString(("https://api.pray.zone/v2/times/today.json?ip=" + std::move(ip_adres))) ))));
               QNetworkReply *reply = mgr.get(req);
               eventLoop.exec();
               if(reply->error() == QNetworkReply::NoError) {
                   //success
                   mainInfo = std::move(reply->readAll());
                   delete reply;
               }
               else {
                   //failure
                   delete reply;
                   mainInfo = std::move("failed");
               }
               }


          }//trash removing from stack asap

          if (mainInfo == "failed"){
              prayerTime = QTime::fromString("00:00:00","hh:mm:ss");
              ui->CurrentPrayer->setText(std::move("Server"));
              ui->nextPrayer->setText(std::move("Error"));
              ui->timeTogo->setText(std::move("00:00:00"));
              std::this_thread::sleep_for(std::chrono::seconds(5));
              return;
          }/*Setting Message to user that there is an problem at the server side*/


             mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 101);
             const QString val(QTime(QTime::currentTime()).toString("hh:mm"));

                    QString FajrTime(QStringRef(&mainInfo, 0, 5).toString());
                 if(val <= FajrTime){
                    ui->CurrentPrayer->setText(std::move("Fajr"));
                    prayerTime = QTime::fromString(FajrTime,"hh:mm");
                    ui->nextPrayer->setText(std::move(FajrTime));
                    return;
                 }else{
                     mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 16);
                        QString DhuhrTime(QStringRef(&mainInfo, 0, 5).toString());
                     if(val <= DhuhrTime){
                         ui->CurrentPrayer->setText(std::move("Dhuhr"));
                         prayerTime = QTime::fromString(DhuhrTime,"hh:mm");
                         ui->nextPrayer->setText(std::move(DhuhrTime));
                         return;
                      }else{
                          mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 14);
                            QString AsrTime(QStringRef(&mainInfo, 0, 5).toString());
                          if(val <= AsrTime){
                              ui->CurrentPrayer->setText(std::move("Asr"));
                              prayerTime = QTime::fromString(AsrTime,"hh:mm");
                              ui->nextPrayer->setText(std::move(AsrTime));
                              return;
                          }else{
                                 mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 35);
                                   QString MagribTime(QStringRef(&mainInfo, 0, 5).toString());
                                  if(val <= MagribTime){
                                       ui->CurrentPrayer->setText(std::move("Magrib"));
                                       prayerTime = QTime::fromString(MagribTime,"hh:mm");
                                       ui->nextPrayer->setText(std::move(MagribTime));
                                      return;
                                  }else{
                                     mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 15);
                                       QString IshaTime(QStringRef(&mainInfo, 0, 5).toString());
                                      if(val <= IshaTime){
                                          ui->CurrentPrayer->setText(std::move("Isha"));
                                          prayerTime = QTime::fromString(IshaTime,"hh:mm");
                                          ui->nextPrayer->setText(std::move(IshaTime));
                                          return;
                                      }
                                  }
                              }
                          }
            }
      }/*Requests Data from server and assigning data to UI*/

      inline const void set_timeToGo() noexcept{
         ui->timeTogo->setText(std::move((QTime((prayerTime.hour() - QTime().currentTime().hour()),
         (prayerTime.minute() - QTime().currentTime().minute()),
        (60 - QTime().currentTime().second())) ).toString("hh:mm:ss")));
      }/*displays the Time until next prayer*/



private:
       Ui::gui *ui;
};


#endif // MAIN_H
