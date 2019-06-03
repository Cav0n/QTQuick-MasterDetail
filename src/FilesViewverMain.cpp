#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <QQuickView>
#include <QtQml>

#include "filemodel.h"
#include "filelist.h"
#include "file.h"

int main(int argc, char *argv[])
{
    // SailfishApp::main() will display "qml/Files.qml", if you need more
    // control over initialization, you can use:
    //
    //   - SailfishApp::application(int, char *[]) to get the QGuiApplication *
    //   - SailfishApp::createView() to get a new QQuickView * instance
    //   - SailfishApp::pathTo(QString) to get a QUrl to a resource file
    //   - SailfishApp::pathToMainQml() to get a QUrl to the main QML file
    //
    // To display the view, call "show()" (will show fullscreen on device).


    QGuiApplication* app = SailfishApp::application(argc, argv);
    QQuickView *view  = SailfishApp::createView();

    // Check if overwriting bindings with static javascript assignement
    QLoggingCategory::setFilterRules(QStringLiteral("qt.qml.binding.removal.info=true"));

    qmlRegisterType<FileModel>("FileModel", 1, 0, "FileModel" );
    qmlRegisterUncreatableType<FileList>("FileModel", 1, 0, "FileList", QStringLiteral("Don't define FileList in QML!!") );
    qmlRegisterUncreatableType<File>("FileModel", 1, 0, "File", QStringLiteral("Don't define File in QML!!") );


    FileList filesFromHd("/usr/bin/");

    view->rootContext()->setContextProperty("filesFromTmp", &filesFromHd);

    view->setSource(SailfishApp::pathTo("qml/Files.qml"));
    view->show();

    return app->exec();
}
