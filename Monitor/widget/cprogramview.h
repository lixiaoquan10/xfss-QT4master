﻿#ifndef CPROGRAMVIEW_H
#define CPROGRAMVIEW_H

#include <QWidget>
#include <QTimer>
#include <QVBoxLayout>
#include <QThread>

class CMiniSplitter;
class QToolButton;

class CProgramView : public QWidget
{
    Q_OBJECT
public:
    explicit CProgramView(QWidget *parent = 0);
    virtual ~CProgramView();
    void Sleep(int msec);
signals:
    void sigRegAllInfo();
    void sigRegLoopInfo();
public slots:
    void slot_regALL();
    void slot_regLoop();
    void slot_unLogin();
    void slot_unLoginLoop();
    void slot_recodeAllDevice();
    void slot_recodeLoopDevice();
    void slot_saveAllDevice();
    void slot_saveLoopDevice();
    void slot_removeLoginObject();
    void slot_resetControllerView();

    void slot_updateTreeFinished();
private:
    CMiniSplitter* m_pSplitter;
    QToolButton* m_regAll;
    QToolButton* m_clrAllReg;
    QToolButton* m_regOne;
    QToolButton* m_clrOneReg;
    QToolButton* m_readdressAll;
    QToolButton* m_readdress;
    QToolButton* m_storeAll;
    QToolButton* m_store;
    bool m_isRemoveLoop;

    QTimer* m_timerReset;
};

class updateTreeThread : public QThread
{
    Q_OBJECT
public:
    explicit updateTreeThread(QObject *parent = NULL)
        : QThread(parent)
    {
    }
signals:
    void updateTreeFinished();
protected:
    void run();
};


#endif // CPROGRAMVIEW_H
