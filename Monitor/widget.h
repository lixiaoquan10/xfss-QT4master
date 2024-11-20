#ifndef WIDGET_H
#define WIDGET_H

#include "cglobal.h"
#include <QWidget>
#include <QGridLayout>
#include <QHash>
#include <QTcpServer>
class CLayer;
class CDevice;
class GroupBox;
class QTabWidget;
class QTableView;
class CprocessServer;
class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void startProcessTcpServer();

private:
    void switchLayer();
    void createTimer();// Create timer
    void keyPressEvent(QKeyEvent  *event);
    int  normalSwitch(QList<CLayer*> &listLayer, int num);

protected:
    void closeEvent(QCloseEvent *e);

public slots:
    void slotLEDTimer();
    void slotEventChange();

private:
    int m_iDelayCut;

    QTimer  *m_timerLED;
    GroupBox *topBox;
    QGridLayout *topLayout;
    GroupBox *bottomBox;
    QGridLayout *bottomLayout;

    QTcpServer* m_tcpServer;               //tcp服务器
    QThread *m_tcpServerThread;            //tcp服务器线程
    CprocessServer* m_processServer;       //tcp服务器处理类
};

#endif // WIDGET_H
