#ifndef GUI_H
#define GUI_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class gui; }
QT_END_NAMESPACE

class gui : public QWidget
{
    Q_OBJECT

public:
    gui(QWidget *parent = nullptr);
    ~gui();
    void setInfo();
private:
    Ui::gui *ui;
};

#endif // GUI_H
