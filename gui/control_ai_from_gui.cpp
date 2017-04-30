#include "control_ai_from_gui.h"


ControlAiFromGui::ControlAiFromGui(QObject *parent)
    : QObject(parent)
{
    QTimer::singleShot(7000,this,SLOT(refreshState()));
}

void ControlAiFromGui::refreshState()
{
    qDebug()<<"Slot worked";
    emit refresh();
}

void ControlAiFromGui::play()
{
    qDebug()<<"Play on";
}

void ControlAiFromGui::stop()
{

}
