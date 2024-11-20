#include "cglobal.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_iDelayCut = 0;
    CGlobal::instance()->m_widget = this;

    CGlobal::instance()->setLoginInformation(new dlgLoginInformation());
    CGlobal::instance()->loginInformation()->setWindowTitle(tr("The registered device information"));
    CGlobal::instance()->loginInformation()->hide();
    CGlobal::instance()->setStatusTabs(new CStatusTabs());
    CGlobal::instance()->setClientBusiness(new CClientBusiness);
//    CGlobal::instance()->setProcessServer(new CprocessServer);
    CGlobal::instance()->setProcessSocket(new CprocessSocket);
    CGlobal::instance()->setInformationWindow(new dlgInformationWindow);
    CGlobal::instance()->setDlgDevices(new dlgDevices);
    CGlobal::instance()->setDeviceForbidFault(new dlgdeviceForbidFault);
    CGlobal::instance()->setCenterFrameContainer(new QStackedWidget);
    CGlobal::instance()->setCenterFrame(new CCenterFrame);
    CGlobal::instance()->setSystemRecord(new dlgSystemRecord);
    CGlobal::instance()->setProgramCanDeviceView(new CProgramCanDeviceView);
    CGlobal::instance()->setTimeInterval(new dlgTimeInterval);
    CGlobal::instance()->setAdminParamPage(new dlgadminParamPage);
    CGlobal::instance()->setUseTime(new dlgUseTime);
    CGlobal::instance()->centerFrameContainer()->insertWidget(0, CGlobal::instance()->CenterFrame());
//    CGlobal::instance()->centerFrameContainer()->insertWidget(1,CGlobal::instance()->dlgDeviceInfomation());
//    CGlobal::instance()->centerFrameContainer()->insertWidget(2,CGlobal::instance()->SystemRecord());
//    CGlobal::instance()->centerFrameContainer()->insertWidget(3,CGlobal::instance()->programCanDeviceView());
//    CGlobal::instance()->centerFrameContainer()->insertWidget(4,CGlobal::instance()->loginInformation());
//    CGlobal::instance()->centerFrameContainer()->insertWidget(5,CGlobal::instance()->TimeInterval());
//    CGlobal::instance()->centerFrameContainer()->insertWidget(6,CGlobal::instance()->AdminParamPage());
//    CGlobal::instance()->centerFrameContainer()->insertWidget(6,CGlobal::instance()->useTime());
    CGlobal::instance()->centerFrameContainer()->setCurrentIndex(0);
    CGlobal::instance()->setBottomToolBar(new CBottomToolBar);
    CGlobal::instance()->setTopToolBar(new CTopToolBar);
    CGlobal::instance()->setDataProcessing(new CDataProcessing());
    CGlobal::instance()->ClientBusiness()->InitController();
    CGlobal::instance()->ClientBusiness()->startCommunication();
    CGlobal::instance()->ClientBusiness()->setNewPwd(CGlobal::instance()->m_strPassWord);

    topBox = new GroupBox;
    topBox->setMaximumHeight(75);
    topBox->setMinimumHeight(75);
    topLayout = new QGridLayout;
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->addWidget(CGlobal::instance()->TopToolBar());
    topBox->setLayout(topLayout);

    bottomBox = new GroupBox;
    bottomBox->setMaximumHeight(32);
    bottomBox->setMinimumHeight(32);
    bottomLayout = new QGridLayout;
    bottomLayout->setContentsMargins(0, 0, 0, 0);
    bottomLayout->addWidget(CGlobal::instance()->BottomToolBar());
    bottomBox->setLayout(bottomLayout);

    QVBoxLayout *mainLayout = CGlobal::instance()->CreateVBoxLayout(this);
    mainLayout->setContentsMargins(1, 1, 1, 1);
    mainLayout->setSpacing(1);
    mainLayout->addWidget(topBox);
    mainLayout->addWidget(CGlobal::instance()->centerFrameContainer(),1);
    mainLayout->addWidget(CGlobal::instance()->statusTabs()->m_tabWidget);
    mainLayout->addWidget(bottomBox);
    createTimer();
    setGeometry(0,0,QApplication::desktop()->screen()->width(), QApplication::desktop()->screen()->height());
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    this->hide();
    startProcessTcpServer();
}

Widget::~Widget()
{
    delete CGlobal::instance()->InformationWindow();
    CGlobal::instance()->setClientBusiness(NULL);
    CGlobal::instance()->setProcessSocket(NULL);
    CGlobal::instance()->setProcessServer(NULL);
    CGlobal::instance()->m_widget = NULL;
    CGlobal::destroy();
}

void Widget::startProcessTcpServer()
{
    // 创建tcpServer服务器
    m_tcpServer = new QTcpServer;

    // 创建tcpServer服务器线程
    m_tcpServerThread = new QThread;
    m_processServer = new CprocessServer(m_tcpServer);
    m_processServer->moveToThread(m_tcpServerThread);
    // 启动tcpServer服务器线程
    m_tcpServerThread->start();
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverDistributionSoftwareInfo(CDistribution*)),
            m_processServer, SLOT(slot_serverDistributionSoftwareInfo(CDistribution*)));
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverDistributionRealtimeData(CDistribution*)),
            m_processServer, SLOT(slot_serverDistributionRealtimeData(CDistribution*)));
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverLampSoftwareInfo(int,int,int)),
            m_processServer, SLOT(slot_serverLampSoftwareInfo(int,int,int)));
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverHostStateUpload(CController*)),
            m_processServer, SLOT(slot_serverHostStateUpload(CController*)));
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverCentralizedPowerStateUpload(CDistribution*)),
            m_processServer, SLOT(slot_serverCentralizedPowerStateUpload(CDistribution*)));
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverLampStateUpload(CDevice*)),
            m_processServer, SLOT(slot_serverLampStateUpload(CDevice*)));
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverLampDirectionUpload(int,QString)),
            m_processServer, SLOT(slot_serverLampDirectionUpload(int,QString)));

    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverResetDeclareUpload()),
            m_processServer, SLOT(slot_serverResetDeclareUpload()));
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverEmergencyInputUpload()),
            m_processServer, SLOT(slot_serverEmergencyInputUpload()));
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverManualLaunchUpload()),
            m_processServer, SLOT(slot_serverManualLaunchUpload()));
    connect(CGlobal::instance()->ClientBusiness(), SIGNAL(serverFirePointWarningUpload(int,int,int)),
            m_processServer, SLOT(slot_serverFirePointWarningUpload(int,int,int)));

    connect(m_processServer, SIGNAL(exeCommand(int,CMsgStructBase*)) ,
            CGlobal::instance()->ClientBusiness(), SLOT(slot_exeCommand(int,CMsgStructBase*)));
    connect(m_processServer, SIGNAL(performLaunch(int)) ,
            CGlobal::instance()->ClientBusiness(), SLOT(slot_PerformLaunch(int)));
    connect(m_processServer, SIGNAL(performReset()) ,
            CGlobal::instance()->ClientBusiness(), SLOT(slot_PerformReset()));

}

void Widget::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void Widget::createTimer()
{
    m_timerLED = new QTimer(this);
    connect(m_timerLED, SIGNAL(timeout()), this, SLOT(slotLEDTimer()));
    m_timerLED->start(500);
}


void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_F)
    {
        CGlobal::instance()->TopToolBar()->slotSearchDevice();
    }
    if(event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_L)
    {
        if(CGlobal::instance()->SystemRecord() == NULL)
        {
            CGlobal::instance()->setSystemRecord(new dlgSystemRecord(this));
            CGlobal::instance()->SystemRecord()->exec();
        }
    }
}


void Widget::slotLEDTimer()
{
    CGlobal::instance()->BottomToolBar()->setCurrentDateTime();
    if(CGlobal::instance()->m_HaveDialog)
    {
        CGlobal::instance()->m_bMove_Mouse = true;
    }
    if(CGlobal::instance()->m_bCutLayer != CGlobal::instance()->isAutoSwitchLayer())
    {
        CGlobal::instance()->m_bCutLayer = CGlobal::instance()->isAutoSwitchLayer();
    }
    if(!CGlobal::instance()->m_bMove_Mouse) {
        ++m_iDelayCut;
//        exitAdmin();
//        switchLayer();
    } else {
        m_iDelayCut = 0;
    }
    CGlobal::instance()->m_bMove_Mouse = false;
}


void Widget::switchLayer()
{
    if(m_iDelayCut > 2*CGlobal::instance()->m_nTimeCutLayer)
    {
        m_iDelayCut = 0;
        if(CGlobal::instance()->m_bCutLayer)
        {
            static int m_nLayerNum = -1;
            QList<CLayer*> tempLayer = CGlobal::instance()->getLayers(CGlobal::instance()->dm()->controllers());

            if(tempLayer.count()>0)
            {
                ++m_nLayerNum;
                if(m_nLayerNum >= tempLayer.count())
                {
                    m_nLayerNum = 0;
                }
                for(int i=0; i<tempLayer.count(); ++i)
                {
                    if(tempLayer.at(m_nLayerNum)->getStatus(OBJS_Fire))
                    {
                        if(CGlobal::instance()->designTreeView()->currentLayer() != tempLayer.at(m_nLayerNum))
                        {
                            CGlobal::instance()->setLayer(tempLayer.at(m_nLayerNum));
                        }
                        return;
                    }

                    ++m_nLayerNum;
                    if(m_nLayerNum >= tempLayer.count())
                    {
                        m_nLayerNum = 0;
                    }
                }
                m_nLayerNum = normalSwitch(tempLayer, m_nLayerNum);
            }
        }
    }
}
void Widget::slotEventChange()
{
    CGlobal::instance()->m_bMove_Mouse = true;

}

int Widget::normalSwitch(QList<CLayer*> &listLayer, int num)
{
    CLayer* m_Lay = CGlobal::instance()->designTreeView()->currentLayer();//?????????
    if(m_Lay)
    {
        int layNum = listLayer.indexOf(m_Lay);
        if(layNum >= 0)
        {
            num = layNum + 1;
            if(num >= listLayer.count())
            {
                num = 0;
            }
        }
    }
    CGlobal::instance()->setLayer(listLayer.at(num));
    return num;
}


