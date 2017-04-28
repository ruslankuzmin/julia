#include <QApplication>
#include <QWebEngineView>
#include <thread>
#include <sys/sysinfo.h>
#include <sys/stat.h>

#include "gui/control_ai_from_gui.h"
#include "artificial_intelligence.h"

void ArtificialIntelligenceThread(int & enabled){
    ArtificialIntelligence ai;
    ai.MainLoop(enabled);
}

int main(int argc, char *argv[])
{
    int isRun = true;
    //Start AI
    std::thread artificialIntelligence(ArtificialIntelligenceThread,
                                       std::ref(isRun));
    //Start GUI
    QApplication app(argc, argv);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QWebEngineView view;

    struct stat sb;
    if (!(stat("output/screenshots/", &sb) == 0 && S_ISDIR(sb.st_mode)))
    {
        system("rm output/screenshots/*");
    }

    view.setUrl(QUrl("qrc:///gui-html-files/index.html"));
    view.resize(1024, 600);

    ControlAiFromGui control;
    QWebChannel * channel = new QWebChannel(&control);
    view.page()->setWebChannel(channel);
    channel->registerObject(QString("TheNameOfTheObjectUsed"), this);

    view.show();
    int res = app.exec();
    //End AI
    isRun = false;
    artificialIntelligence.join();
    return res;
}
