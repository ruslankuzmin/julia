#include <QApplication>
#include <QWebEngineView>
#include <thread>
#include <sys/sysinfo.h>

#include "artificial_intelligence.h"

void ArtificialIntelligenceThread(){
    ArtificialIntelligence ai;
}

int main(int argc, char *argv[])
{
    std::thread artificialIntelligence(ArtificialIntelligenceThread);
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QWebEngineView view;
    view.setUrl(QUrl("qrc:///gui-html-files/index.html"));
    view.resize(1024, 600);
    view.show();
    int res = app.exec();
    return res;
    artificialIntelligence.join();
    return res;
}
