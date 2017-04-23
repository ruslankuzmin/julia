#include <QApplication>
#include <QWebEngineView>
#include <thread>
#include <sys/sysinfo.h>

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
    system("rm output/screenshots/*");
    view.setUrl(QUrl("qrc:///gui-html-files/index.html"));
    view.resize(1024, 600);
    view.show();

    int res = app.exec();

    //End AI
    isRun = false;
    artificialIntelligence.join();
    return res;
}
