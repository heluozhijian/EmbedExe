#ifndef EMBEDEXE_H
#define EMBEDEXE_H

#include <QMainWindow>
#include <QLayout>
#include <QWidget>
#include <QPushButton>

class EmbedExe : public QMainWindow
{
    Q_OBJECT

public:
    EmbedExe(QWidget *parent = nullptr);
    ~EmbedExe();

    QGridLayout *gridLayout;
    QWidget *centralWidget;
    QPushButton *pushButton;
    QWidget *widget;

    void EmbedCalc(HWND hWnd);

private slots:
    void onPushButtonClicked(void);
};

#endif // EMBEDEXE_H
