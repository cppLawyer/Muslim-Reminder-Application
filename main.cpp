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
/////////DEPEND//////////
#include "main.h"
#include <QApplication>
#include <QTime>
#include "ui_gui.h"
#include <QMediaPlayer>
#include <thread>
//////////////////////



void rootTask(gui& w) noexcept{
     w.adhanPlayer.setSource(std::move(QUrl(std::move("qrc:adhan/Adhan.mp3"))));
  do{
        w.set_data();
        while((w.prayerTime == QTime(00,00,00))){
            w.ui->CurrentPrayer->setText(std::move("Reconnect"));
            w.ui->nextPrayer->setText(std::move("To Server"));
            w.ui->timeTogo->setText(std::move("--:--:--"));
            std::this_thread::sleep_for(std::chrono::seconds(5));
            w.set_data();
        }//try to fix issue by retrying to connect autoSolve//

       do{
            /* to prevent function overhead*/
            w.ui->timeTogo->setText(std::move((QTime((w.prayerTime.hour() - QTime().currentTime().hour()),
            (w.prayerTime.minute() - QTime().currentTime().minute()),
            (60 - QTime().currentTime().second()))).toString("hh:mm:ss")));
           ///////////////////////////////////////////////////////////////////
            std::this_thread::sleep_for(std::chrono::seconds(1));
       }while(QTime::currentTime() < w.prayerTime);//waiting until it is time to pray//
    w.adhanPlayer.play(); /*waits until adhan is done and so prayerTime has time to update*/
   }while(w.program);
}//MAIN THREAD FOR THE APPLICATION


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui w;
    w.operationThread = std::thread(rootTask, std::ref(w));
    w.show();
    return a.exec();
}
