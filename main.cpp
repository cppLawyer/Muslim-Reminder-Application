/*
************************************************************************************************************
-------------------------------------------------- cppLawyer -----------------------------------------------


- Messy code >--------> because it is highly optimized <----------<
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
------------------------------------------------------------------------------------------------------------
************************************************************************************************************
*/
/////////DEPEND//////////
#include "main.h"
#include <QApplication>
#include <QTime>
#include <QMediaPlayer>
#include <thread>
//////////////////////



void rootTask(gui& w) noexcept{
 w.adhanPlayer.setSource(std::move(QUrl(std::move("qrc:/new/sound/Adhan.mp3"))));
  do{
        w.set_data();

        while((w.prayerTime == QTime(00,00,00))){
            w.reTryMessage(); w.set_data();
        }//try to fix issue by retrying to connect//

        while(QTime::currentTime().toString("hh:mm") < w.prayerTime.toString("hh:mm")){
           w.set_timeToGo(); std::this_thread::yield();
        }//waiting until it is time to pray//

         w.adhanPlayer.play();
        while(w.adhanPlayer.playbackState() == 1){std::this_thread::yield();};
        /*waits until adhan is done and so prayerTime has time to update*/

   }while(true);
}//MAIN THREAD FOR THE APPLICATION


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui w;
    w.operationThread = std::thread(rootTask, std::ref(w));
    w.show();
    return a.exec();
}
