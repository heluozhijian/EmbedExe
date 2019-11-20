#include "EmbedExe.h"

#include <Windows.h>
#include <QDebug>
#include <QProcess>

#pragma comment(lib, "user32.lib")

EmbedExe::EmbedExe(QWidget *parent): QMainWindow(parent)
{
    // pushButton
    pushButton = new QPushButton;
    pushButton->setText(QStringLiteral("计算器"));

    // widget
    widget = new QWidget;
    widget->setVisible(true);

    // gridLayout
    gridLayout = new QGridLayout;
    gridLayout->setSpacing(5);
    gridLayout->setContentsMargins(0, 0, 0, 0); //left top right bottom
    gridLayout->addWidget(pushButton, 0, 0);
    gridLayout->addWidget(widget, 1, 0);
    gridLayout->setRowStretch(0, 1);
    gridLayout->setRowStretch(1, 20);
    gridLayout->setColumnStretch(0, 1);

    // centralWidget
    centralWidget = new QWidget;
    centralWidget->setLayout(gridLayout);

    // this
    this->setCentralWidget(centralWidget);

    QObject::connect(pushButton, SIGNAL(clicked()), this, SLOT(onPushButtonClicked()));
    Sleep(1000);
}

EmbedExe::~EmbedExe()
{

}

void EmbedExe::onPushButtonClicked(void)
{
    qDebug() << "EmbedExe::onPushButtonClicked";

    QProcess pro;
    pro.startDetached("C:/Windows/system32/calc.exe", QStringList() << "");
    pro.close();

    Sleep(1000);

    HWND hWnd = reinterpret_cast<HWND>(widget->winId());
    EmbedCalc(hWnd);
}

void EmbedExe::EmbedCalc(HWND hWnd)
{
    qDebug() << "Parent window:" << hWnd;

    HWND calcHwnd = FindWindow(L"ApplicationFrameWindow", L"计算器");
    if(calcHwnd != nullptr)
    {
        qDebug() << "Child window:" << calcHwnd;
        // Change the parent so the calc window belongs to our apps main window
        HWND ret = SetParent(calcHwnd, hWnd);
        qDebug() << "SetParent - ret" << ret;

        // Update the style so the calc window is embedded in our main window
        SetWindowLong(calcHwnd, GWL_STYLE, GetWindowLong(calcHwnd, GWL_STYLE) | WS_CHILD);

        // We need to update the position as well since changing the parent does not
        // adjust it automatically.
        SetWindowPos(calcHwnd, nullptr, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

    }
}
