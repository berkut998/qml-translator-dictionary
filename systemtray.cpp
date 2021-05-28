#include "systemtray.h"
#include <QMenu>
#include <QSystemTrayIcon>

SystemTray::SystemTray(QObject *parent) : QObject(parent)
{

    // Создаём контекстное меню с двумя пунктами
    QMenu *trayIconMenu = new QMenu();

    QAction * viewWindow = new QAction(trUtf8("Развернуть окно"), this);
    QAction * quitAction = new QAction(trUtf8("Выход"), this);

    /* подключаем сигналы нажатий на пункты меню к соответсвующим сигналам для QML.
     * */
    connect(viewWindow, &QAction::triggered, this, &SystemTray::signalShow);
    connect(quitAction, &QAction::triggered, this, &SystemTray::signalQuit);

    trayIconMenu->addAction(viewWindow);
    trayIconMenu->addAction(quitAction);

    /* Инициализируем иконку трея, устанавливаем иконку,
     * а также задаем всплывающую подсказку
     * */
    trayIcon = new QSystemTrayIcon();
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/Assets/kisspng-translation-google-translate-computer-icons-micros-language-5abddd208a8e67.4592666915223923525675.png"));
    trayIcon->show();
    trayIcon->setToolTip("Tray Program" "\n"
                         "Работа со сворачиванием программы трей");

    /* Также подключаем сигнал нажатия на иконку к обработчику
     * данного нажатия
     * */
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

/* Метод, который обрабатывает нажатие на иконку приложения в трее
 * */
void SystemTray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason){
    case QSystemTrayIcon::Trigger:
        // В случае сигнала нажатия на иконку трея вызываем сигнал в QML слой
        emit signalIconActivated();
        break;
    default:
        break;
    }
}

void SystemTray::hideIconTray()
{
    trayIcon->hide();
}

void SystemTray::showMessage(QString message)
{
    trayIcon->showMessage("Translate",message,trayIcon->icon(),1000);
}
