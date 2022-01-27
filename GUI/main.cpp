#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "../TicTacToeHeader.h"
#include "../Players.h"

int main(int argc, char *argv[])
{
    Game tictactoe;
    tictactoe.playRound(0, 0);

    qDebug() << &tictactoe;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    qmlRegisterSingletonInstance("Game", 1, 0, "Game", &tictactoe);

    qmlRegisterType<PlayerClass>("Player", 1, 0, "Player");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
