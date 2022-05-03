#include "gui.h"
#include <QApplication>
#include <thread>
#include <QTime>
#include <QMediaPlayer>

inline int applicationManager(int argc, char *argv[]){
    QApplication a(argc, argv);
    gui w;

    w.show();
    w.setInfo();
    return a.exec();
}

inline void pushNoti(){
    while(prayerTime != QTime(QTime::currentTime()).toString("hh:mm")) {
        QThread::yieldCurrentThread();
    }
    QMediaPlayer adhanPlayer;
    adhanPlayer.setSource(QUrl("qrc:/new/sound/Adhan.mp3"));
    adhanPlayer.play();
    return;
}

int main(int argc, char *argv[])
{
    do{
       std::thread message(pushNoti);
       applicationManager(argc,argv);

     }while(true);
}
