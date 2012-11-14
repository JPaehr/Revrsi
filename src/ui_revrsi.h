/********************************************************************************
** Form generated from reading UI file 'revrsi.ui'
**
** Created: Mon Nov 12 10:06:39 2012
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REVRSI_H
#define UI_REVRSI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Revrsi
{
public:
    QAction *actionNeu;
    QAction *actionBeenden;
    QAction *actionOptionen;
    QAction *actionServer;
    QAction *actionClient;
    QAction *action_ber;
    QAction *actionHilfe;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuSpiel;
    QMenu *menuEinstellungen;
    QMenu *menuNetzwerk;
    QMenu *menuHilfe;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *Revrsi)
    {
        if (Revrsi->objectName().isEmpty())
            Revrsi->setObjectName(QString::fromUtf8("Revrsi"));
        Revrsi->resize(808, 655);
        actionNeu = new QAction(Revrsi);
        actionNeu->setObjectName(QString::fromUtf8("actionNeu"));
        actionBeenden = new QAction(Revrsi);
        actionBeenden->setObjectName(QString::fromUtf8("actionBeenden"));
        actionOptionen = new QAction(Revrsi);
        actionOptionen->setObjectName(QString::fromUtf8("actionOptionen"));
        actionServer = new QAction(Revrsi);
        actionServer->setObjectName(QString::fromUtf8("actionServer"));
        actionClient = new QAction(Revrsi);
        actionClient->setObjectName(QString::fromUtf8("actionClient"));
        action_ber = new QAction(Revrsi);
        action_ber->setObjectName(QString::fromUtf8("action_ber"));
        actionHilfe = new QAction(Revrsi);
        actionHilfe->setObjectName(QString::fromUtf8("actionHilfe"));
        centralWidget = new QWidget(Revrsi);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        Revrsi->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Revrsi);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 808, 23));
        menuSpiel = new QMenu(menuBar);
        menuSpiel->setObjectName(QString::fromUtf8("menuSpiel"));
        menuEinstellungen = new QMenu(menuBar);
        menuEinstellungen->setObjectName(QString::fromUtf8("menuEinstellungen"));
        menuNetzwerk = new QMenu(menuBar);
        menuNetzwerk->setObjectName(QString::fromUtf8("menuNetzwerk"));
        menuHilfe = new QMenu(menuBar);
        menuHilfe->setObjectName(QString::fromUtf8("menuHilfe"));
        Revrsi->setMenuBar(menuBar);
        statusBar = new QStatusBar(Revrsi);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Revrsi->setStatusBar(statusBar);
        mainToolBar = new QToolBar(Revrsi);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Revrsi->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menuSpiel->menuAction());
        menuBar->addAction(menuEinstellungen->menuAction());
        menuBar->addAction(menuNetzwerk->menuAction());
        menuBar->addAction(menuHilfe->menuAction());
        menuSpiel->addAction(actionNeu);
        menuSpiel->addAction(actionBeenden);
        menuEinstellungen->addAction(actionOptionen);
        menuNetzwerk->addAction(actionServer);
        menuNetzwerk->addAction(actionClient);
        menuHilfe->addAction(actionHilfe);
        menuHilfe->addAction(action_ber);

        retranslateUi(Revrsi);
        QObject::connect(actionBeenden, SIGNAL(triggered()), Revrsi, SLOT(close()));

        QMetaObject::connectSlotsByName(Revrsi);
    } // setupUi

    void retranslateUi(QMainWindow *Revrsi)
    {
        Revrsi->setWindowTitle(QApplication::translate("Revrsi", "Revrsi", 0, QApplication::UnicodeUTF8));
        actionNeu->setText(QApplication::translate("Revrsi", "Neu", 0, QApplication::UnicodeUTF8));
        actionBeenden->setText(QApplication::translate("Revrsi", "Beenden", 0, QApplication::UnicodeUTF8));
        actionOptionen->setText(QApplication::translate("Revrsi", "Optionen", 0, QApplication::UnicodeUTF8));
        actionServer->setText(QApplication::translate("Revrsi", "Server", 0, QApplication::UnicodeUTF8));
        actionClient->setText(QApplication::translate("Revrsi", "Client", 0, QApplication::UnicodeUTF8));
        action_ber->setText(QApplication::translate("Revrsi", "\303\234ber", 0, QApplication::UnicodeUTF8));
        actionHilfe->setText(QApplication::translate("Revrsi", "Hilfe", 0, QApplication::UnicodeUTF8));
        menuSpiel->setTitle(QApplication::translate("Revrsi", "Spiel", 0, QApplication::UnicodeUTF8));
        menuEinstellungen->setTitle(QApplication::translate("Revrsi", "Einstellungen", 0, QApplication::UnicodeUTF8));
        menuNetzwerk->setTitle(QApplication::translate("Revrsi", "Netzwerk", 0, QApplication::UnicodeUTF8));
        menuHilfe->setTitle(QApplication::translate("Revrsi", "Hilfe", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Revrsi: public Ui_Revrsi {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REVRSI_H
