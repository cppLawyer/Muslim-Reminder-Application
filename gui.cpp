#include "gui.h"
#include "ui_gui.h"
#include <api_manager.h>
#include <QPair>
gui::gui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gui)
{
    ui->setupUi(this);
}

void gui::setInfo(){
QPair<QString,QString> pair = use_api::get_data();
ui->CurrentPrayer->setText(pair.first);
ui->nextPrayer->setText(pair.second);

}

gui::~gui()
{
    delete ui;
}

