#ifndef CONTROL_AI_FROM_GUI_H
#define CONTROL_AI_FROM_GUI_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class ControlAiFromGui  : public QObject
{
    Q_OBJECT
public:
    explicit ControlAiFromGui(QObject *parent = 0);
public slots:
    void refreshState();
    void play();
    void stop();
signals:
    void refresh();
};

#endif // CONTROL_AI_FROM_GUI_H
