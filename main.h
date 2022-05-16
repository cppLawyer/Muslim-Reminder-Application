/*
************************************************************************************************************
-------------------------------------------------- cppLawyer -----------------------------------------------
+ Low stack memory usage
+ Almost No function overhead
+ Regulate Stack Memory
+ Agressive but peacefull
+ Low Ram Usage
+ Low Power Usage
+ Beautiful Adhan
+ Shows Accurate Prayer Times based on IP/Location
+ Shows How Many Minutes for the next prayer
+ Almost no CPU Usage

-- Version 3.0 --
- Bug fixes
- Performance improvements
- Server Changed
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
    bool program = true;
    /////////////////////////////
    ~gui()
    {
        program = false;//to solve undefined behavior after detaching thread//
        operationThread.detach();
        delete ui;
    }
 inline void set_data() noexcept{
           QString mainInfo;

         {
               QString cityName;
               {
                   QEventLoop eventLoop;
                   QNetworkAccessManager mgr;
                   QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
                   QNetworkRequest req( std::move(QUrl( std::move(QString(std::move("http://ip-api.com/json/?fields=city")) ))));
                   QNetworkReply *reply = std::move(mgr.get(req));
                   eventLoop.exec();
                   //process data
                      QString jsonCity(std::move(reply->readAll()));
                      jsonCity.erase(jsonCity.begin(),jsonCity.begin() + 9);
                      jsonCity.erase(jsonCity.end(), jsonCity.end() - 2);
                      cityName = std::move(jsonCity);
                      delete reply;
               }//scope

               QEventLoop eventLoop;
               QNetworkAccessManager mgr;
               QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
               QNetworkRequest req( std::move(QUrl( std::move(QString("https://dailyprayer.abdulrcs.repl.co/api/" + std::move(cityName)) ))));
               QNetworkReply *reply = std::move(mgr.get(req));
               eventLoop.exec();
               if(reply->error() == QNetworkReply::NoError) {
                   //success
                      mainInfo = QString(std::move(reply->readAll()));
                      mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 9);
                      delete reply;
                      {
                         uint_fast8_t index = 0;
                         while(mainInfo[index] != '"'){
                           ++index;
                         }
                         //cityName.length not possible because return name of json depends on server chosen name//
                         mainInfo.erase(mainInfo.begin(),mainInfo.begin() + (44 + index));
                      }
               }
               else {
                   //failure
                   delete reply;
                   mainInfo = std::move("failed");
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

             const QString val(QTime(QTime::currentTime()).toString("hh:mm"));
                    QString FajrTime(QStringRef(&mainInfo, 0, 5).toString());
                 if(val <= FajrTime){
                    ui->CurrentPrayer->setText(std::move("Fajr"));
                    prayerTime = QTime::fromString(FajrTime,"hh:mm");
                    ui->nextPrayer->setText(std::move(FajrTime));
                    return;
                 }else{
                     mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 34);
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
                                 mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 18);
                                   QString MagribTime(QStringRef(&mainInfo, 0, 5).toString());
                                  if(val <= MagribTime){
                                       ui->CurrentPrayer->setText(std::move("Magrib"));
                                       prayerTime = QTime::fromString(MagribTime,"hh:mm");
                                       ui->nextPrayer->setText(std::move(MagribTime));
                                      return;
                                  }else{
                                     mainInfo.erase(mainInfo.begin(), mainInfo.begin() + 17);
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

       Ui::gui *ui;
};


#endif // MAIN_H
