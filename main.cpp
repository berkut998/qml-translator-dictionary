#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "clipboarddictionary.h"
#include <QApplication>
#include <QIcon>
#include <QQuickWidget>
#include <QSystemTrayIcon>
#include <QQmlContext>
#include <systemtray.h>
#include "http_Translator.h"
#include "sqldictionary.h"

// Объявляем пользовательский тип данных для работы с иконкой в QML
Q_DECLARE_METATYPE(QSystemTrayIcon::ActivationReason)
// Second, define the singleton type provider function (callback).
static QObject *example_qobject_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    ClipBoardDictionary *clipBoard = new ClipBoardDictionary();
    return clipBoard;
}

static QObject *example_qobject_singletontype_httpTranslator(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    http_Translator *httpTranslator = new http_Translator();
    return httpTranslator;
}

static QObject *example_qobject_singletontype_dictionary(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    SqlDictionary *dictionary = new SqlDictionary();
    return dictionary;
}


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication app(argc, argv);
    app.setOrganizationName("Some Company");
    app.setOrganizationDomain("somecompany.com");
    app.setApplicationName("Amazing Application");
    QQmlApplicationEngine engine;
    qmlRegisterSingletonType<ClipBoardDictionary>("ClipBoardDictionary",1,0,"ClipBoardDictionary",example_qobject_singletontype_provider);
    qmlRegisterSingletonType<http_Translator>("Http_Translator",1,0,"Http_Translator",example_qobject_singletontype_httpTranslator);
    qmlRegisterSingletonType<SqlDictionary>("SqlDictionary",1,0,"SqlDictionary",example_qobject_singletontype_dictionary);
    // Объявляем и инициализируем объекта класса для работы с системным треем
    SystemTray * systemTray = new SystemTray();
    QQmlContext * context = engine.rootContext();
    // Устанавливаем доступ к свойствам объекта класса в контексте QML
    context->setContextProperty("systemTray", systemTray);


    // Регистрируем QSystemTrayIcon в качестве типа объекта в Qml
    qmlRegisterType<QSystemTrayIcon>("QSystemTrayIcon", 1, 0, "QSystemTrayIcon");
    // Регистрируем в QML тип данных для работы с получаемыми данными при клике по иконке
    qRegisterMetaType<QSystemTrayIcon::ActivationReason>("ActivationReason");
    // Устанавливаем Иконку в контекст движка
    engine.rootContext()->setContextProperty("iconTray", QIcon("qrc:/Assets/swap_horiz_black_24dp.svg"));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
