/********************************************************************************
** Form generated from reading UI file 'dlgtimeinterval.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGTIMEINTERVAL_H
#define UI_DLGTIMEINTERVAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDateTimeEdit>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dlgTimeInterval
{
public:
    QGroupBox *EnergyModeBox;
    QVBoxLayout *verticalLayout_6;
    QCheckBox *EnergyCheckBox;
    QGroupBox *EmergencyBox;
    QVBoxLayout *verticalLayout_12;
    QCheckBox *TwinkleCheckBox;
    QCheckBox *emergencyOnlyDistributionCheckBox;
    QGroupBox *VersionBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_10;
    QLineEdit *version_ledkey;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_CAN1_2;
    QLineEdit *version_can1can2;
    QPushButton *pushButton_can1can2;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_CAN3_4;
    QLineEdit *version_can3can4;
    QPushButton *pushButton_can3can4;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_CAN5_6;
    QLineEdit *version_can5can6;
    QPushButton *pushButton_can5can6;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_CAN7_8;
    QLineEdit *version_can7can8;
    QPushButton *pushButton_can7can8;
    QGroupBox *PowerBox;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *PowersendLayout;
    QLabel *label_12;
    QLabel *label_powersend;
    QHBoxLayout *PowerOLayout;
    QLabel *label_13;
    QLabel *label_powerotime;
    QHBoxLayout *PowerFaultLayout;
    QLabel *label_14;
    QLabel *label_powerfault;
    QGroupBox *SwitchLayerBox;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *SwitchLayerTime;
    QLabel *label_2;
    QGroupBox *wlanBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label_myip1;
    QLineEdit *m_myip1;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_gateway1;
    QLineEdit *m_gateway1;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_myip2;
    QLineEdit *m_myip2;
    QHBoxLayout *horizontalLayout_24;
    QLabel *label_gateway2;
    QLineEdit *m_gateway2;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_saveWlan;
    QGroupBox *UseTimeBox;
    QHBoxLayout *horizontalLayout_14;
    QLineEdit *UseTime;
    QLabel *label_3;
    QPushButton *pushButton_UseTime;
    QGroupBox *timeBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QDateTimeEdit *dateEdit;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_5;
    QDateTimeEdit *timeEdit;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *m_ButtonTimeSet;
    QGroupBox *pingBox;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QLineEdit *m_pingIP;
    QPushButton *pingButton;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_8;
    QLineEdit *m_pingResult;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *cloudIPSetBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_Hostip;
    QLineEdit *m_hostip;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_com;
    QLineEdit *m_com;
    QPushButton *pushButton_saveCloudIP;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_cloudComStatus;
    QLineEdit *m_cloudComStatus;
    QGroupBox *comStatusBox;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_cloudStatus;
    QLineEdit *m_cloudStatus;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_masterStatus;
    QLineEdit *m_masterStatus;
    QGroupBox *StartRuleBox;
    QVBoxLayout *verticalLayout_15;
    QCheckBox *allStartCheckBox;
    QCheckBox *onlyStartGroupCheckBox;
    QCheckBox *onlyStartPageCheckBox;
    QGroupBox *CanNumberBox;
    QVBoxLayout *verticalLayout_16;
    QCheckBox *Can4CheckBox;
    QCheckBox *Can8CheckBox;
    QGroupBox *controlType;
    QVBoxLayout *verticalLayout_17;
    QCheckBox *singleWLAN;
    QCheckBox *doubleWLAN;
    QGroupBox *AutoPageBox;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *autoPageCheckBox;
    QGroupBox *testLinkageComBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QComboBox *comboBox_testLinkageCom;
    QPushButton *pushButton_testLinkageCom;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_9;
    QLineEdit *m_testLinkageComResult;
    QPushButton *testLinkageComButton;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_15;
    QLineEdit *m_LinkageStatus;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox_phoneNumber;
    QHBoxLayout *horizontalLayout_26;
    QLineEdit *lineEdit_phoneNumber;
    QPushButton *pushButton_phoneNumber;
    QGroupBox *groupBox_firepointNumber;
    QHBoxLayout *horizontalLayout_27;
    QLineEdit *lineEdit_firepointNumber;
    QPushButton *pushButton_firepointNumber;
    QPushButton *pushButton_lampForbidList;
    QGroupBox *lampEmergencyType;
    QVBoxLayout *verticalLayout_7;
    QCheckBox *DirectionTwinkleOneCheckBox;
    QCheckBox *DirectionTwinkleDoubleCheckBox;
    QCheckBox *TwinkleConfigCheckBox;
    QPushButton *pushButton_lamptwinkleconfig;
    QGroupBox *ARTUBox;
    QVBoxLayout *verticalLayout_18;
    QCheckBox *forbidARTUCheckBox;
    QCheckBox *ARTU079KCheckBox;
    QCheckBox *ARTU079KJCheckBox;
    QCheckBox *ARTU426CheckBox;
    QGroupBox *groupBox_ModbusTcp;
    QPushButton *pushButton_ModbusTcp;

    void setupUi(QDialog *dlgTimeInterval)
    {
        if (dlgTimeInterval->objectName().isEmpty())
            dlgTimeInterval->setObjectName(QString::fromUtf8("dlgTimeInterval"));
        dlgTimeInterval->resize(1366, 768);
        dlgTimeInterval->setMinimumSize(QSize(1366, 768));
        dlgTimeInterval->setMaximumSize(QSize(1366, 768));
        QFont font;
        font.setPointSize(13);
        dlgTimeInterval->setFont(font);
        dlgTimeInterval->setInputMethodHints(Qt::ImhNone);
        EnergyModeBox = new QGroupBox(dlgTimeInterval);
        EnergyModeBox->setObjectName(QString::fromUtf8("EnergyModeBox"));
        EnergyModeBox->setGeometry(QRect(1200, 20, 110, 58));
        QFont font1;
        font1.setPointSize(12);
        EnergyModeBox->setFont(font1);
        EnergyModeBox->setCheckable(false);
        EnergyModeBox->setChecked(false);
        verticalLayout_6 = new QVBoxLayout(EnergyModeBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        EnergyCheckBox = new QCheckBox(EnergyModeBox);
        EnergyCheckBox->setObjectName(QString::fromUtf8("EnergyCheckBox"));
        EnergyCheckBox->setFont(font1);

        verticalLayout_6->addWidget(EnergyCheckBox);

        EmergencyBox = new QGroupBox(dlgTimeInterval);
        EmergencyBox->setObjectName(QString::fromUtf8("EmergencyBox"));
        EmergencyBox->setGeometry(QRect(490, 20, 260, 80));
        EmergencyBox->setFont(font1);
        EmergencyBox->setCheckable(false);
        EmergencyBox->setChecked(false);
        verticalLayout_12 = new QVBoxLayout(EmergencyBox);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        TwinkleCheckBox = new QCheckBox(EmergencyBox);
        TwinkleCheckBox->setObjectName(QString::fromUtf8("TwinkleCheckBox"));
        TwinkleCheckBox->setFont(font1);

        verticalLayout_12->addWidget(TwinkleCheckBox);

        emergencyOnlyDistributionCheckBox = new QCheckBox(EmergencyBox);
        emergencyOnlyDistributionCheckBox->setObjectName(QString::fromUtf8("emergencyOnlyDistributionCheckBox"));
        emergencyOnlyDistributionCheckBox->setFont(font1);

        verticalLayout_12->addWidget(emergencyOnlyDistributionCheckBox);

        VersionBox = new QGroupBox(dlgTimeInterval);
        VersionBox->setObjectName(QString::fromUtf8("VersionBox"));
        VersionBox->setGeometry(QRect(1040, 140, 270, 210));
        VersionBox->setFont(font1);
        VersionBox->setCheckable(false);
        VersionBox->setChecked(false);
        verticalLayout = new QVBoxLayout(VersionBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_10 = new QLabel(VersionBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(65, 28));
        label_10->setMaximumSize(QSize(65, 28));
        label_10->setFont(font1);

        horizontalLayout_22->addWidget(label_10);

        version_ledkey = new QLineEdit(VersionBox);
        version_ledkey->setObjectName(QString::fromUtf8("version_ledkey"));
        version_ledkey->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(version_ledkey->sizePolicy().hasHeightForWidth());
        version_ledkey->setSizePolicy(sizePolicy);
        version_ledkey->setMinimumSize(QSize(110, 28));
        version_ledkey->setMaximumSize(QSize(110, 28));
        version_ledkey->setFont(font1);
        version_ledkey->setReadOnly(true);

        horizontalLayout_22->addWidget(version_ledkey);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_22);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_CAN1_2 = new QLabel(VersionBox);
        label_CAN1_2->setObjectName(QString::fromUtf8("label_CAN1_2"));
        label_CAN1_2->setMinimumSize(QSize(65, 28));
        label_CAN1_2->setMaximumSize(QSize(65, 28));
        label_CAN1_2->setFont(font1);

        horizontalLayout_21->addWidget(label_CAN1_2);

        version_can1can2 = new QLineEdit(VersionBox);
        version_can1can2->setObjectName(QString::fromUtf8("version_can1can2"));
        version_can1can2->setEnabled(true);
        sizePolicy.setHeightForWidth(version_can1can2->sizePolicy().hasHeightForWidth());
        version_can1can2->setSizePolicy(sizePolicy);
        version_can1can2->setMinimumSize(QSize(110, 28));
        version_can1can2->setMaximumSize(QSize(110, 28));
        version_can1can2->setFont(font1);
        version_can1can2->setReadOnly(true);

        horizontalLayout_21->addWidget(version_can1can2);

        pushButton_can1can2 = new QPushButton(VersionBox);
        pushButton_can1can2->setObjectName(QString::fromUtf8("pushButton_can1can2"));
        pushButton_can1can2->setMinimumSize(QSize(0, 28));
        pushButton_can1can2->setMaximumSize(QSize(60, 28));
        pushButton_can1can2->setFont(font1);

        horizontalLayout_21->addWidget(pushButton_can1can2);


        verticalLayout->addLayout(horizontalLayout_21);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_CAN3_4 = new QLabel(VersionBox);
        label_CAN3_4->setObjectName(QString::fromUtf8("label_CAN3_4"));
        label_CAN3_4->setMinimumSize(QSize(65, 28));
        label_CAN3_4->setMaximumSize(QSize(65, 28));
        label_CAN3_4->setFont(font1);

        horizontalLayout_20->addWidget(label_CAN3_4);

        version_can3can4 = new QLineEdit(VersionBox);
        version_can3can4->setObjectName(QString::fromUtf8("version_can3can4"));
        version_can3can4->setEnabled(true);
        sizePolicy.setHeightForWidth(version_can3can4->sizePolicy().hasHeightForWidth());
        version_can3can4->setSizePolicy(sizePolicy);
        version_can3can4->setMinimumSize(QSize(110, 28));
        version_can3can4->setMaximumSize(QSize(110, 28));
        version_can3can4->setFont(font1);
        version_can3can4->setReadOnly(true);

        horizontalLayout_20->addWidget(version_can3can4);

        pushButton_can3can4 = new QPushButton(VersionBox);
        pushButton_can3can4->setObjectName(QString::fromUtf8("pushButton_can3can4"));
        pushButton_can3can4->setMinimumSize(QSize(0, 28));
        pushButton_can3can4->setMaximumSize(QSize(60, 28));
        pushButton_can3can4->setFont(font1);

        horizontalLayout_20->addWidget(pushButton_can3can4);


        verticalLayout->addLayout(horizontalLayout_20);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_CAN5_6 = new QLabel(VersionBox);
        label_CAN5_6->setObjectName(QString::fromUtf8("label_CAN5_6"));
        label_CAN5_6->setMinimumSize(QSize(65, 28));
        label_CAN5_6->setMaximumSize(QSize(65, 28));
        label_CAN5_6->setFont(font1);

        horizontalLayout_19->addWidget(label_CAN5_6);

        version_can5can6 = new QLineEdit(VersionBox);
        version_can5can6->setObjectName(QString::fromUtf8("version_can5can6"));
        version_can5can6->setEnabled(true);
        sizePolicy.setHeightForWidth(version_can5can6->sizePolicy().hasHeightForWidth());
        version_can5can6->setSizePolicy(sizePolicy);
        version_can5can6->setMinimumSize(QSize(110, 28));
        version_can5can6->setMaximumSize(QSize(110, 28));
        version_can5can6->setFont(font1);
        version_can5can6->setReadOnly(true);

        horizontalLayout_19->addWidget(version_can5can6);

        pushButton_can5can6 = new QPushButton(VersionBox);
        pushButton_can5can6->setObjectName(QString::fromUtf8("pushButton_can5can6"));
        pushButton_can5can6->setMinimumSize(QSize(0, 28));
        pushButton_can5can6->setMaximumSize(QSize(60, 28));
        pushButton_can5can6->setFont(font1);

        horizontalLayout_19->addWidget(pushButton_can5can6);


        verticalLayout->addLayout(horizontalLayout_19);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_CAN7_8 = new QLabel(VersionBox);
        label_CAN7_8->setObjectName(QString::fromUtf8("label_CAN7_8"));
        label_CAN7_8->setMinimumSize(QSize(65, 28));
        label_CAN7_8->setMaximumSize(QSize(65, 28));
        label_CAN7_8->setFont(font1);

        horizontalLayout_13->addWidget(label_CAN7_8);

        version_can7can8 = new QLineEdit(VersionBox);
        version_can7can8->setObjectName(QString::fromUtf8("version_can7can8"));
        version_can7can8->setEnabled(true);
        sizePolicy.setHeightForWidth(version_can7can8->sizePolicy().hasHeightForWidth());
        version_can7can8->setSizePolicy(sizePolicy);
        version_can7can8->setMinimumSize(QSize(110, 28));
        version_can7can8->setMaximumSize(QSize(110, 28));
        version_can7can8->setFont(font1);
        version_can7can8->setReadOnly(true);

        horizontalLayout_13->addWidget(version_can7can8);

        pushButton_can7can8 = new QPushButton(VersionBox);
        pushButton_can7can8->setObjectName(QString::fromUtf8("pushButton_can7can8"));
        pushButton_can7can8->setMinimumSize(QSize(0, 28));
        pushButton_can7can8->setMaximumSize(QSize(60, 28));
        pushButton_can7can8->setFont(font1);

        horizontalLayout_13->addWidget(pushButton_can7can8);


        verticalLayout->addLayout(horizontalLayout_13);

        PowerBox = new QGroupBox(dlgTimeInterval);
        PowerBox->setObjectName(QString::fromUtf8("PowerBox"));
        PowerBox->setGeometry(QRect(580, 690, 111, 31));
        PowerBox->setCheckable(false);
        PowerBox->setChecked(false);
        verticalLayout_11 = new QVBoxLayout(PowerBox);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        PowersendLayout = new QHBoxLayout();
        PowersendLayout->setObjectName(QString::fromUtf8("PowersendLayout"));
        label_12 = new QLabel(PowerBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setMaximumSize(QSize(84, 16777215));

        PowersendLayout->addWidget(label_12);

        label_powersend = new QLabel(PowerBox);
        label_powersend->setObjectName(QString::fromUtf8("label_powersend"));
        label_powersend->setAlignment(Qt::AlignCenter);

        PowersendLayout->addWidget(label_powersend);


        verticalLayout_11->addLayout(PowersendLayout);

        PowerOLayout = new QHBoxLayout();
        PowerOLayout->setObjectName(QString::fromUtf8("PowerOLayout"));
        label_13 = new QLabel(PowerBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMaximumSize(QSize(84, 16777215));

        PowerOLayout->addWidget(label_13);

        label_powerotime = new QLabel(PowerBox);
        label_powerotime->setObjectName(QString::fromUtf8("label_powerotime"));
        label_powerotime->setAlignment(Qt::AlignCenter);

        PowerOLayout->addWidget(label_powerotime);


        verticalLayout_11->addLayout(PowerOLayout);

        PowerFaultLayout = new QHBoxLayout();
        PowerFaultLayout->setObjectName(QString::fromUtf8("PowerFaultLayout"));
        label_14 = new QLabel(PowerBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(84, 16777215));

        PowerFaultLayout->addWidget(label_14);

        label_powerfault = new QLabel(PowerBox);
        label_powerfault->setObjectName(QString::fromUtf8("label_powerfault"));
        label_powerfault->setAlignment(Qt::AlignCenter);

        PowerFaultLayout->addWidget(label_powerfault);


        verticalLayout_11->addLayout(PowerFaultLayout);

        SwitchLayerBox = new QGroupBox(dlgTimeInterval);
        SwitchLayerBox->setObjectName(QString::fromUtf8("SwitchLayerBox"));
        SwitchLayerBox->setGeometry(QRect(360, 690, 121, 31));
        SwitchLayerBox->setCheckable(true);
        SwitchLayerBox->setChecked(false);
        horizontalLayout_3 = new QHBoxLayout(SwitchLayerBox);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(SwitchLayerBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        SwitchLayerTime = new QLineEdit(SwitchLayerBox);
        SwitchLayerTime->setObjectName(QString::fromUtf8("SwitchLayerTime"));
        SwitchLayerTime->setMaximumSize(QSize(95, 16777215));

        horizontalLayout_2->addWidget(SwitchLayerTime);

        label_2 = new QLabel(SwitchLayerBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        wlanBox = new QGroupBox(dlgTimeInterval);
        wlanBox->setObjectName(QString::fromUtf8("wlanBox"));
        wlanBox->setGeometry(QRect(40, 120, 270, 210));
        wlanBox->setFont(font1);
        verticalLayout_3 = new QVBoxLayout(wlanBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_myip1 = new QLabel(wlanBox);
        label_myip1->setObjectName(QString::fromUtf8("label_myip1"));
        label_myip1->setMinimumSize(QSize(83, 28));
        label_myip1->setMaximumSize(QSize(83, 28));
        label_myip1->setFont(font1);

        horizontalLayout->addWidget(label_myip1);

        m_myip1 = new QLineEdit(wlanBox);
        m_myip1->setObjectName(QString::fromUtf8("m_myip1"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(m_myip1->sizePolicy().hasHeightForWidth());
        m_myip1->setSizePolicy(sizePolicy1);
        m_myip1->setMinimumSize(QSize(150, 28));
        m_myip1->setMaximumSize(QSize(150, 28));
        m_myip1->setFont(font1);
        m_myip1->setEchoMode(QLineEdit::Normal);

        horizontalLayout->addWidget(m_myip1);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_gateway1 = new QLabel(wlanBox);
        label_gateway1->setObjectName(QString::fromUtf8("label_gateway1"));
        label_gateway1->setMinimumSize(QSize(83, 28));
        label_gateway1->setMaximumSize(QSize(83, 28));
        label_gateway1->setFont(font1);

        horizontalLayout_15->addWidget(label_gateway1);

        m_gateway1 = new QLineEdit(wlanBox);
        m_gateway1->setObjectName(QString::fromUtf8("m_gateway1"));
        m_gateway1->setEnabled(true);
        sizePolicy1.setHeightForWidth(m_gateway1->sizePolicy().hasHeightForWidth());
        m_gateway1->setSizePolicy(sizePolicy1);
        m_gateway1->setMinimumSize(QSize(150, 28));
        m_gateway1->setMaximumSize(QSize(150, 28));
        m_gateway1->setFont(font1);
        m_gateway1->setEchoMode(QLineEdit::Normal);

        horizontalLayout_15->addWidget(m_gateway1);


        verticalLayout_3->addLayout(horizontalLayout_15);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        label_myip2 = new QLabel(wlanBox);
        label_myip2->setObjectName(QString::fromUtf8("label_myip2"));
        label_myip2->setMinimumSize(QSize(83, 28));
        label_myip2->setMaximumSize(QSize(83, 28));
        label_myip2->setFont(font1);

        horizontalLayout_23->addWidget(label_myip2);

        m_myip2 = new QLineEdit(wlanBox);
        m_myip2->setObjectName(QString::fromUtf8("m_myip2"));
        sizePolicy1.setHeightForWidth(m_myip2->sizePolicy().hasHeightForWidth());
        m_myip2->setSizePolicy(sizePolicy1);
        m_myip2->setMinimumSize(QSize(150, 28));
        m_myip2->setMaximumSize(QSize(150, 28));
        m_myip2->setFont(font1);
        m_myip2->setEchoMode(QLineEdit::Normal);

        horizontalLayout_23->addWidget(m_myip2);


        verticalLayout_3->addLayout(horizontalLayout_23);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        label_gateway2 = new QLabel(wlanBox);
        label_gateway2->setObjectName(QString::fromUtf8("label_gateway2"));
        label_gateway2->setMinimumSize(QSize(83, 28));
        label_gateway2->setMaximumSize(QSize(83, 28));
        label_gateway2->setFont(font1);

        horizontalLayout_24->addWidget(label_gateway2);

        m_gateway2 = new QLineEdit(wlanBox);
        m_gateway2->setObjectName(QString::fromUtf8("m_gateway2"));
        m_gateway2->setEnabled(true);
        sizePolicy1.setHeightForWidth(m_gateway2->sizePolicy().hasHeightForWidth());
        m_gateway2->setSizePolicy(sizePolicy1);
        m_gateway2->setMinimumSize(QSize(150, 28));
        m_gateway2->setMaximumSize(QSize(150, 28));
        m_gateway2->setFont(font1);
        m_gateway2->setEchoMode(QLineEdit::Normal);

        horizontalLayout_24->addWidget(m_gateway2);


        verticalLayout_3->addLayout(horizontalLayout_24);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer);

        pushButton_saveWlan = new QPushButton(wlanBox);
        pushButton_saveWlan->setObjectName(QString::fromUtf8("pushButton_saveWlan"));
        pushButton_saveWlan->setMinimumSize(QSize(0, 28));
        pushButton_saveWlan->setMaximumSize(QSize(16777215, 28));
        pushButton_saveWlan->setFont(font1);

        horizontalLayout_16->addWidget(pushButton_saveWlan);


        verticalLayout_3->addLayout(horizontalLayout_16);

        UseTimeBox = new QGroupBox(dlgTimeInterval);
        UseTimeBox->setObjectName(QString::fromUtf8("UseTimeBox"));
        UseTimeBox->setGeometry(QRect(810, 230, 210, 70));
        UseTimeBox->setFont(font1);
        UseTimeBox->setCheckable(false);
        UseTimeBox->setChecked(false);
        horizontalLayout_14 = new QHBoxLayout(UseTimeBox);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        UseTime = new QLineEdit(UseTimeBox);
        UseTime->setObjectName(QString::fromUtf8("UseTime"));
        UseTime->setEnabled(true);
        UseTime->setMinimumSize(QSize(40, 28));
        UseTime->setMaximumSize(QSize(40, 28));
        UseTime->setFont(font1);
        UseTime->setReadOnly(true);

        horizontalLayout_14->addWidget(UseTime);

        label_3 = new QLabel(UseTimeBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setFont(font1);

        horizontalLayout_14->addWidget(label_3);

        pushButton_UseTime = new QPushButton(UseTimeBox);
        pushButton_UseTime->setObjectName(QString::fromUtf8("pushButton_UseTime"));
        pushButton_UseTime->setMinimumSize(QSize(0, 28));
        pushButton_UseTime->setMaximumSize(QSize(16777215, 28));
        pushButton_UseTime->setFont(font1);

        horizontalLayout_14->addWidget(pushButton_UseTime);

        timeBox = new QGroupBox(dlgTimeInterval);
        timeBox->setObjectName(QString::fromUtf8("timeBox"));
        timeBox->setGeometry(QRect(600, 140, 190, 140));
        timeBox->setFont(font1);
        verticalLayout_4 = new QVBoxLayout(timeBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_4 = new QLabel(timeBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(0, 28));
        label_4->setMaximumSize(QSize(16777215, 28));
        label_4->setFont(font1);

        horizontalLayout_7->addWidget(label_4);

        dateEdit = new QDateTimeEdit(timeBox);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setMinimumSize(QSize(115, 28));
        dateEdit->setMaximumSize(QSize(115, 28));
        dateEdit->setFont(font1);

        horizontalLayout_7->addWidget(dateEdit);


        verticalLayout_4->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_5 = new QLabel(timeBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(0, 28));
        label_5->setMaximumSize(QSize(16777215, 28));
        label_5->setFont(font1);

        horizontalLayout_8->addWidget(label_5);

        timeEdit = new QDateTimeEdit(timeBox);
        timeEdit->setObjectName(QString::fromUtf8("timeEdit"));
        timeEdit->setMinimumSize(QSize(115, 28));
        timeEdit->setMaximumSize(QSize(115, 28));
        timeEdit->setFont(font1);

        horizontalLayout_8->addWidget(timeEdit);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalSpacer_3 = new QSpacerItem(40, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_3);

        m_ButtonTimeSet = new QPushButton(timeBox);
        m_ButtonTimeSet->setObjectName(QString::fromUtf8("m_ButtonTimeSet"));
        m_ButtonTimeSet->setMinimumSize(QSize(0, 28));
        m_ButtonTimeSet->setMaximumSize(QSize(16777215, 28));
        m_ButtonTimeSet->setFont(font1);

        horizontalLayout_9->addWidget(m_ButtonTimeSet);


        verticalLayout_4->addLayout(horizontalLayout_9);

        pingBox = new QGroupBox(dlgTimeInterval);
        pingBox->setObjectName(QString::fromUtf8("pingBox"));
        pingBox->setGeometry(QRect(40, 350, 280, 100));
        pingBox->setFont(font1);
        verticalLayout_10 = new QVBoxLayout(pingBox);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_6 = new QLabel(pingBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(0, 28));
        label_6->setMaximumSize(QSize(16777215, 28));
        label_6->setFont(font1);

        horizontalLayout_10->addWidget(label_6);

        m_pingIP = new QLineEdit(pingBox);
        m_pingIP->setObjectName(QString::fromUtf8("m_pingIP"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(m_pingIP->sizePolicy().hasHeightForWidth());
        m_pingIP->setSizePolicy(sizePolicy2);
        m_pingIP->setMinimumSize(QSize(150, 28));
        m_pingIP->setMaximumSize(QSize(150, 28));
        m_pingIP->setFont(font1);
        m_pingIP->setEchoMode(QLineEdit::Normal);

        horizontalLayout_10->addWidget(m_pingIP);

        pingButton = new QPushButton(pingBox);
        pingButton->setObjectName(QString::fromUtf8("pingButton"));
        pingButton->setMinimumSize(QSize(0, 28));
        pingButton->setMaximumSize(QSize(45, 28));
        pingButton->setFont(font1);

        horizontalLayout_10->addWidget(pingButton);


        verticalLayout_10->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_8 = new QLabel(pingBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(0, 28));
        label_8->setMaximumSize(QSize(16777215, 28));
        label_8->setFont(font1);

        horizontalLayout_11->addWidget(label_8);

        m_pingResult = new QLineEdit(pingBox);
        m_pingResult->setObjectName(QString::fromUtf8("m_pingResult"));
        sizePolicy2.setHeightForWidth(m_pingResult->sizePolicy().hasHeightForWidth());
        m_pingResult->setSizePolicy(sizePolicy2);
        m_pingResult->setMinimumSize(QSize(60, 28));
        m_pingResult->setMaximumSize(QSize(60, 28));
        m_pingResult->setFont(font1);
        m_pingResult->setEchoMode(QLineEdit::Normal);
        m_pingResult->setReadOnly(true);

        horizontalLayout_11->addWidget(m_pingResult);

        horizontalSpacer_4 = new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_4);


        verticalLayout_10->addLayout(horizontalLayout_11);

        cloudIPSetBox = new QGroupBox(dlgTimeInterval);
        cloudIPSetBox->setObjectName(QString::fromUtf8("cloudIPSetBox"));
        cloudIPSetBox->setGeometry(QRect(340, 130, 240, 140));
        cloudIPSetBox->setFont(font1);
        verticalLayout_5 = new QVBoxLayout(cloudIPSetBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_Hostip = new QLabel(cloudIPSetBox);
        label_Hostip->setObjectName(QString::fromUtf8("label_Hostip"));
        label_Hostip->setMinimumSize(QSize(50, 28));
        label_Hostip->setMaximumSize(QSize(50, 28));
        label_Hostip->setFont(font1);

        horizontalLayout_17->addWidget(label_Hostip);

        m_hostip = new QLineEdit(cloudIPSetBox);
        m_hostip->setObjectName(QString::fromUtf8("m_hostip"));
        sizePolicy2.setHeightForWidth(m_hostip->sizePolicy().hasHeightForWidth());
        m_hostip->setSizePolicy(sizePolicy2);
        m_hostip->setMinimumSize(QSize(150, 28));
        m_hostip->setMaximumSize(QSize(150, 28));
        m_hostip->setFont(font1);
        m_hostip->setEchoMode(QLineEdit::Normal);

        horizontalLayout_17->addWidget(m_hostip);


        verticalLayout_5->addLayout(horizontalLayout_17);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_com = new QLabel(cloudIPSetBox);
        label_com->setObjectName(QString::fromUtf8("label_com"));
        label_com->setMinimumSize(QSize(50, 28));
        label_com->setMaximumSize(QSize(50, 28));
        label_com->setFont(font1);

        horizontalLayout_5->addWidget(label_com);

        m_com = new QLineEdit(cloudIPSetBox);
        m_com->setObjectName(QString::fromUtf8("m_com"));
        sizePolicy2.setHeightForWidth(m_com->sizePolicy().hasHeightForWidth());
        m_com->setSizePolicy(sizePolicy2);
        m_com->setMinimumSize(QSize(60, 28));
        m_com->setMaximumSize(QSize(60, 28));
        m_com->setFont(font1);
        m_com->setEchoMode(QLineEdit::Normal);

        horizontalLayout_5->addWidget(m_com);

        pushButton_saveCloudIP = new QPushButton(cloudIPSetBox);
        pushButton_saveCloudIP->setObjectName(QString::fromUtf8("pushButton_saveCloudIP"));
        sizePolicy2.setHeightForWidth(pushButton_saveCloudIP->sizePolicy().hasHeightForWidth());
        pushButton_saveCloudIP->setSizePolicy(sizePolicy2);
        pushButton_saveCloudIP->setMinimumSize(QSize(0, 28));
        pushButton_saveCloudIP->setMaximumSize(QSize(80, 28));
        pushButton_saveCloudIP->setFont(font1);

        horizontalLayout_5->addWidget(pushButton_saveCloudIP);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_cloudComStatus = new QLabel(cloudIPSetBox);
        label_cloudComStatus->setObjectName(QString::fromUtf8("label_cloudComStatus"));
        label_cloudComStatus->setMinimumSize(QSize(0, 28));
        label_cloudComStatus->setMaximumSize(QSize(16777215, 28));
        label_cloudComStatus->setFont(font1);

        horizontalLayout_25->addWidget(label_cloudComStatus);

        m_cloudComStatus = new QLineEdit(cloudIPSetBox);
        m_cloudComStatus->setObjectName(QString::fromUtf8("m_cloudComStatus"));
        sizePolicy2.setHeightForWidth(m_cloudComStatus->sizePolicy().hasHeightForWidth());
        m_cloudComStatus->setSizePolicy(sizePolicy2);
        m_cloudComStatus->setMinimumSize(QSize(0, 28));
        m_cloudComStatus->setMaximumSize(QSize(150, 28));
        m_cloudComStatus->setFont(font1);
        m_cloudComStatus->setEchoMode(QLineEdit::Normal);
        m_cloudComStatus->setReadOnly(true);

        horizontalLayout_25->addWidget(m_cloudComStatus);


        verticalLayout_5->addLayout(horizontalLayout_25);

        comStatusBox = new QGroupBox(dlgTimeInterval);
        comStatusBox->setObjectName(QString::fromUtf8("comStatusBox"));
        comStatusBox->setGeometry(QRect(980, 600, 190, 100));
        comStatusBox->setFont(font1);
        verticalLayout_14 = new QVBoxLayout(comStatusBox);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_cloudStatus = new QLabel(comStatusBox);
        label_cloudStatus->setObjectName(QString::fromUtf8("label_cloudStatus"));
        label_cloudStatus->setMinimumSize(QSize(0, 28));
        label_cloudStatus->setMaximumSize(QSize(16777215, 28));
        label_cloudStatus->setFont(font1);

        horizontalLayout_6->addWidget(label_cloudStatus);

        m_cloudStatus = new QLineEdit(comStatusBox);
        m_cloudStatus->setObjectName(QString::fromUtf8("m_cloudStatus"));
        sizePolicy2.setHeightForWidth(m_cloudStatus->sizePolicy().hasHeightForWidth());
        m_cloudStatus->setSizePolicy(sizePolicy2);
        m_cloudStatus->setMinimumSize(QSize(0, 28));
        m_cloudStatus->setMaximumSize(QSize(80, 28));
        m_cloudStatus->setFont(font1);
        m_cloudStatus->setEchoMode(QLineEdit::Normal);
        m_cloudStatus->setReadOnly(true);

        horizontalLayout_6->addWidget(m_cloudStatus);


        verticalLayout_14->addLayout(horizontalLayout_6);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_masterStatus = new QLabel(comStatusBox);
        label_masterStatus->setObjectName(QString::fromUtf8("label_masterStatus"));
        label_masterStatus->setMinimumSize(QSize(0, 28));
        label_masterStatus->setMaximumSize(QSize(16777215, 28));
        label_masterStatus->setFont(font1);

        horizontalLayout_18->addWidget(label_masterStatus);

        m_masterStatus = new QLineEdit(comStatusBox);
        m_masterStatus->setObjectName(QString::fromUtf8("m_masterStatus"));
        sizePolicy2.setHeightForWidth(m_masterStatus->sizePolicy().hasHeightForWidth());
        m_masterStatus->setSizePolicy(sizePolicy2);
        m_masterStatus->setMinimumSize(QSize(0, 28));
        m_masterStatus->setMaximumSize(QSize(80, 28));
        m_masterStatus->setFont(font1);
        m_masterStatus->setEchoMode(QLineEdit::Normal);
        m_masterStatus->setReadOnly(true);

        horizontalLayout_18->addWidget(m_masterStatus);


        verticalLayout_14->addLayout(horizontalLayout_18);

        StartRuleBox = new QGroupBox(dlgTimeInterval);
        StartRuleBox->setObjectName(QString::fromUtf8("StartRuleBox"));
        StartRuleBox->setGeometry(QRect(310, 20, 150, 100));
        StartRuleBox->setFont(font1);
        StartRuleBox->setCheckable(false);
        StartRuleBox->setChecked(false);
        verticalLayout_15 = new QVBoxLayout(StartRuleBox);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        allStartCheckBox = new QCheckBox(StartRuleBox);
        allStartCheckBox->setObjectName(QString::fromUtf8("allStartCheckBox"));
        allStartCheckBox->setFont(font1);

        verticalLayout_15->addWidget(allStartCheckBox);

        onlyStartGroupCheckBox = new QCheckBox(StartRuleBox);
        onlyStartGroupCheckBox->setObjectName(QString::fromUtf8("onlyStartGroupCheckBox"));
        onlyStartGroupCheckBox->setFont(font1);

        verticalLayout_15->addWidget(onlyStartGroupCheckBox);

        onlyStartPageCheckBox = new QCheckBox(StartRuleBox);
        onlyStartPageCheckBox->setObjectName(QString::fromUtf8("onlyStartPageCheckBox"));
        onlyStartPageCheckBox->setFont(font1);

        verticalLayout_15->addWidget(onlyStartPageCheckBox);

        CanNumberBox = new QGroupBox(dlgTimeInterval);
        CanNumberBox->setObjectName(QString::fromUtf8("CanNumberBox"));
        CanNumberBox->setGeometry(QRect(170, 20, 110, 80));
        CanNumberBox->setFont(font1);
        CanNumberBox->setCheckable(false);
        CanNumberBox->setChecked(false);
        verticalLayout_16 = new QVBoxLayout(CanNumberBox);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        Can4CheckBox = new QCheckBox(CanNumberBox);
        Can4CheckBox->setObjectName(QString::fromUtf8("Can4CheckBox"));
        Can4CheckBox->setFont(font1);

        verticalLayout_16->addWidget(Can4CheckBox);

        Can8CheckBox = new QCheckBox(CanNumberBox);
        Can8CheckBox->setObjectName(QString::fromUtf8("Can8CheckBox"));
        Can8CheckBox->setFont(font1);

        verticalLayout_16->addWidget(Can8CheckBox);

        controlType = new QGroupBox(dlgTimeInterval);
        controlType->setObjectName(QString::fromUtf8("controlType"));
        controlType->setGeometry(QRect(40, 20, 100, 80));
        controlType->setFont(font1);
        controlType->setCheckable(false);
        controlType->setChecked(false);
        verticalLayout_17 = new QVBoxLayout(controlType);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        singleWLAN = new QCheckBox(controlType);
        singleWLAN->setObjectName(QString::fromUtf8("singleWLAN"));
        singleWLAN->setFont(font1);

        verticalLayout_17->addWidget(singleWLAN);

        doubleWLAN = new QCheckBox(controlType);
        doubleWLAN->setObjectName(QString::fromUtf8("doubleWLAN"));
        doubleWLAN->setFont(font1);

        verticalLayout_17->addWidget(doubleWLAN);

        AutoPageBox = new QGroupBox(dlgTimeInterval);
        AutoPageBox->setObjectName(QString::fromUtf8("AutoPageBox"));
        AutoPageBox->setGeometry(QRect(1030, 20, 150, 58));
        AutoPageBox->setFont(font1);
        AutoPageBox->setCheckable(false);
        AutoPageBox->setChecked(false);
        verticalLayout_8 = new QVBoxLayout(AutoPageBox);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        autoPageCheckBox = new QCheckBox(AutoPageBox);
        autoPageCheckBox->setObjectName(QString::fromUtf8("autoPageCheckBox"));
        autoPageCheckBox->setFont(font1);

        verticalLayout_8->addWidget(autoPageCheckBox);

        testLinkageComBox = new QGroupBox(dlgTimeInterval);
        testLinkageComBox->setObjectName(QString::fromUtf8("testLinkageComBox"));
        testLinkageComBox->setGeometry(QRect(340, 290, 239, 140));
        testLinkageComBox->setFont(font1);
        verticalLayout_2 = new QVBoxLayout(testLinkageComBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_11 = new QLabel(testLinkageComBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(0, 28));
        label_11->setMaximumSize(QSize(16777215, 28));
        label_11->setFont(font1);

        horizontalLayout_4->addWidget(label_11);

        comboBox_testLinkageCom = new QComboBox(testLinkageComBox);
        comboBox_testLinkageCom->setObjectName(QString::fromUtf8("comboBox_testLinkageCom"));
        comboBox_testLinkageCom->setMinimumSize(QSize(0, 28));
        comboBox_testLinkageCom->setMaximumSize(QSize(16777215, 28));
        comboBox_testLinkageCom->setFont(font1);

        horizontalLayout_4->addWidget(comboBox_testLinkageCom);

        pushButton_testLinkageCom = new QPushButton(testLinkageComBox);
        pushButton_testLinkageCom->setObjectName(QString::fromUtf8("pushButton_testLinkageCom"));
        pushButton_testLinkageCom->setMinimumSize(QSize(0, 28));
        pushButton_testLinkageCom->setMaximumSize(QSize(50, 28));
        pushButton_testLinkageCom->setFont(font1);

        horizontalLayout_4->addWidget(pushButton_testLinkageCom);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_9 = new QLabel(testLinkageComBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(0, 28));
        label_9->setMaximumSize(QSize(16777215, 28));
        label_9->setFont(font1);

        horizontalLayout_12->addWidget(label_9);

        m_testLinkageComResult = new QLineEdit(testLinkageComBox);
        m_testLinkageComResult->setObjectName(QString::fromUtf8("m_testLinkageComResult"));
        sizePolicy2.setHeightForWidth(m_testLinkageComResult->sizePolicy().hasHeightForWidth());
        m_testLinkageComResult->setSizePolicy(sizePolicy2);
        m_testLinkageComResult->setMinimumSize(QSize(60, 28));
        m_testLinkageComResult->setMaximumSize(QSize(80, 28));
        m_testLinkageComResult->setFont(font1);
        m_testLinkageComResult->setEchoMode(QLineEdit::Normal);
        m_testLinkageComResult->setReadOnly(true);

        horizontalLayout_12->addWidget(m_testLinkageComResult);

        testLinkageComButton = new QPushButton(testLinkageComBox);
        testLinkageComButton->setObjectName(QString::fromUtf8("testLinkageComButton"));
        testLinkageComButton->setMinimumSize(QSize(0, 28));
        testLinkageComButton->setMaximumSize(QSize(50, 28));
        testLinkageComButton->setFont(font1);

        horizontalLayout_12->addWidget(testLinkageComButton);


        verticalLayout_2->addLayout(horizontalLayout_12);

        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        label_15 = new QLabel(testLinkageComBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setMinimumSize(QSize(0, 28));
        label_15->setMaximumSize(QSize(16777215, 28));
        label_15->setFont(font1);

        horizontalLayout_28->addWidget(label_15);

        m_LinkageStatus = new QLineEdit(testLinkageComBox);
        m_LinkageStatus->setObjectName(QString::fromUtf8("m_LinkageStatus"));
        sizePolicy2.setHeightForWidth(m_LinkageStatus->sizePolicy().hasHeightForWidth());
        m_LinkageStatus->setSizePolicy(sizePolicy2);
        m_LinkageStatus->setMinimumSize(QSize(80, 28));
        m_LinkageStatus->setMaximumSize(QSize(80, 28));
        m_LinkageStatus->setFont(font1);
        m_LinkageStatus->setEchoMode(QLineEdit::Normal);
        m_LinkageStatus->setReadOnly(true);

        horizontalLayout_28->addWidget(m_LinkageStatus);

        horizontalSpacer_5 = new QSpacerItem(38, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_28);

        groupBox_phoneNumber = new QGroupBox(dlgTimeInterval);
        groupBox_phoneNumber->setObjectName(QString::fromUtf8("groupBox_phoneNumber"));
        groupBox_phoneNumber->setGeometry(QRect(810, 140, 210, 70));
        groupBox_phoneNumber->setFont(font1);
        horizontalLayout_26 = new QHBoxLayout(groupBox_phoneNumber);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        lineEdit_phoneNumber = new QLineEdit(groupBox_phoneNumber);
        lineEdit_phoneNumber->setObjectName(QString::fromUtf8("lineEdit_phoneNumber"));
        lineEdit_phoneNumber->setMinimumSize(QSize(130, 28));
        lineEdit_phoneNumber->setMaximumSize(QSize(130, 28));
        lineEdit_phoneNumber->setFont(font1);

        horizontalLayout_26->addWidget(lineEdit_phoneNumber);

        pushButton_phoneNumber = new QPushButton(groupBox_phoneNumber);
        pushButton_phoneNumber->setObjectName(QString::fromUtf8("pushButton_phoneNumber"));
        pushButton_phoneNumber->setMinimumSize(QSize(50, 28));
        pushButton_phoneNumber->setMaximumSize(QSize(50, 28));
        pushButton_phoneNumber->setFont(font1);

        horizontalLayout_26->addWidget(pushButton_phoneNumber);

        groupBox_firepointNumber = new QGroupBox(dlgTimeInterval);
        groupBox_firepointNumber->setObjectName(QString::fromUtf8("groupBox_firepointNumber"));
        groupBox_firepointNumber->setGeometry(QRect(790, 320, 170, 70));
        groupBox_firepointNumber->setFont(font1);
        horizontalLayout_27 = new QHBoxLayout(groupBox_firepointNumber);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        lineEdit_firepointNumber = new QLineEdit(groupBox_firepointNumber);
        lineEdit_firepointNumber->setObjectName(QString::fromUtf8("lineEdit_firepointNumber"));
        lineEdit_firepointNumber->setMinimumSize(QSize(40, 28));
        lineEdit_firepointNumber->setMaximumSize(QSize(40, 28));
        lineEdit_firepointNumber->setFont(font1);

        horizontalLayout_27->addWidget(lineEdit_firepointNumber);

        pushButton_firepointNumber = new QPushButton(groupBox_firepointNumber);
        pushButton_firepointNumber->setObjectName(QString::fromUtf8("pushButton_firepointNumber"));
        pushButton_firepointNumber->setMinimumSize(QSize(50, 28));
        pushButton_firepointNumber->setMaximumSize(QSize(50, 28));
        pushButton_firepointNumber->setFont(font1);

        horizontalLayout_27->addWidget(pushButton_firepointNumber);

        pushButton_lampForbidList = new QPushButton(dlgTimeInterval);
        pushButton_lampForbidList->setObjectName(QString::fromUtf8("pushButton_lampForbidList"));
        pushButton_lampForbidList->setGeometry(QRect(1030, 90, 150, 28));
        pushButton_lampForbidList->setMinimumSize(QSize(150, 28));
        pushButton_lampForbidList->setMaximumSize(QSize(150, 28));
        pushButton_lampForbidList->setFont(font1);
        lampEmergencyType = new QGroupBox(dlgTimeInterval);
        lampEmergencyType->setObjectName(QString::fromUtf8("lampEmergencyType"));
        lampEmergencyType->setGeometry(QRect(780, 20, 230, 100));
        lampEmergencyType->setFont(font1);
        verticalLayout_7 = new QVBoxLayout(lampEmergencyType);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        DirectionTwinkleOneCheckBox = new QCheckBox(lampEmergencyType);
        DirectionTwinkleOneCheckBox->setObjectName(QString::fromUtf8("DirectionTwinkleOneCheckBox"));
        DirectionTwinkleOneCheckBox->setFont(font1);

        verticalLayout_7->addWidget(DirectionTwinkleOneCheckBox);

        DirectionTwinkleDoubleCheckBox = new QCheckBox(lampEmergencyType);
        DirectionTwinkleDoubleCheckBox->setObjectName(QString::fromUtf8("DirectionTwinkleDoubleCheckBox"));
        DirectionTwinkleDoubleCheckBox->setFont(font1);

        verticalLayout_7->addWidget(DirectionTwinkleDoubleCheckBox);

        TwinkleConfigCheckBox = new QCheckBox(lampEmergencyType);
        TwinkleConfigCheckBox->setObjectName(QString::fromUtf8("TwinkleConfigCheckBox"));
        TwinkleConfigCheckBox->setFont(font1);

        verticalLayout_7->addWidget(TwinkleConfigCheckBox);

        pushButton_lamptwinkleconfig = new QPushButton(dlgTimeInterval);
        pushButton_lamptwinkleconfig->setObjectName(QString::fromUtf8("pushButton_lamptwinkleconfig"));
        pushButton_lamptwinkleconfig->setGeometry(QRect(1200, 90, 110, 28));
        pushButton_lamptwinkleconfig->setMinimumSize(QSize(110, 28));
        pushButton_lamptwinkleconfig->setMaximumSize(QSize(110, 28));
        pushButton_lamptwinkleconfig->setFont(font1);
        ARTUBox = new QGroupBox(dlgTimeInterval);
        ARTUBox->setObjectName(QString::fromUtf8("ARTUBox"));
        ARTUBox->setGeometry(QRect(600, 300, 170, 135));
        ARTUBox->setFont(font1);
        ARTUBox->setCheckable(false);
        ARTUBox->setChecked(false);
        verticalLayout_18 = new QVBoxLayout(ARTUBox);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        forbidARTUCheckBox = new QCheckBox(ARTUBox);
        forbidARTUCheckBox->setObjectName(QString::fromUtf8("forbidARTUCheckBox"));
        forbidARTUCheckBox->setFont(font1);

        verticalLayout_18->addWidget(forbidARTUCheckBox);

        ARTU079KCheckBox = new QCheckBox(ARTUBox);
        ARTU079KCheckBox->setObjectName(QString::fromUtf8("ARTU079KCheckBox"));
        ARTU079KCheckBox->setFont(font1);

        verticalLayout_18->addWidget(ARTU079KCheckBox);

        ARTU079KJCheckBox = new QCheckBox(ARTUBox);
        ARTU079KJCheckBox->setObjectName(QString::fromUtf8("ARTU079KJCheckBox"));
        ARTU079KJCheckBox->setFont(font1);

        verticalLayout_18->addWidget(ARTU079KJCheckBox);

        ARTU426CheckBox = new QCheckBox(ARTUBox);
        ARTU426CheckBox->setObjectName(QString::fromUtf8("ARTU426CheckBox"));
        ARTU426CheckBox->setFont(font1);

        verticalLayout_18->addWidget(ARTU426CheckBox);

        groupBox_ModbusTcp = new QGroupBox(dlgTimeInterval);
        groupBox_ModbusTcp->setObjectName(QString::fromUtf8("groupBox_ModbusTcp"));
        groupBox_ModbusTcp->setGeometry(QRect(790, 400, 170, 80));
        groupBox_ModbusTcp->setFont(font1);
        pushButton_ModbusTcp = new QPushButton(groupBox_ModbusTcp);
        pushButton_ModbusTcp->setObjectName(QString::fromUtf8("pushButton_ModbusTcp"));
        pushButton_ModbusTcp->setGeometry(QRect(20, 40, 130, 28));
        pushButton_ModbusTcp->setFont(font1);
        SwitchLayerBox->raise();
        EnergyModeBox->raise();
        EmergencyBox->raise();
        VersionBox->raise();
        PowerBox->raise();
        wlanBox->raise();
        UseTimeBox->raise();
        timeBox->raise();
        pingBox->raise();
        cloudIPSetBox->raise();
        comStatusBox->raise();
        StartRuleBox->raise();
        CanNumberBox->raise();
        controlType->raise();
        AutoPageBox->raise();
        testLinkageComBox->raise();
        groupBox_phoneNumber->raise();
        groupBox_firepointNumber->raise();
        pushButton_lampForbidList->raise();
        lampEmergencyType->raise();
        pushButton_lamptwinkleconfig->raise();
        ARTUBox->raise();
        groupBox_ModbusTcp->raise();

        retranslateUi(dlgTimeInterval);

        QMetaObject::connectSlotsByName(dlgTimeInterval);
    } // setupUi

    void retranslateUi(QDialog *dlgTimeInterval)
    {
        dlgTimeInterval->setWindowTitle(QApplication::translate("dlgTimeInterval", "Dialog", 0, QApplication::UnicodeUTF8));
        EnergyModeBox->setTitle(QApplication::translate("dlgTimeInterval", "\350\212\202\350\203\275\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        EnergyCheckBox->setText(QApplication::translate("dlgTimeInterval", "\350\212\202\350\203\275\346\250\241\345\274\217", 0, QApplication::UnicodeUTF8));
        EmergencyBox->setTitle(QApplication::translate("dlgTimeInterval", "\345\272\224\346\200\245\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        TwinkleCheckBox->setText(QApplication::translate("dlgTimeInterval", "\346\240\207\345\277\227\347\201\257\345\272\224\346\200\245\351\227\252\347\203\201", 0, QApplication::UnicodeUTF8));
        emergencyOnlyDistributionCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\272\224\346\200\245\344\273\205\345\220\257\345\212\250\347\201\257\345\205\267\346\211\200\345\234\250\351\233\206\344\270\255\347\224\265\346\272\220", 0, QApplication::UnicodeUTF8));
        VersionBox->setTitle(QApplication::translate("dlgTimeInterval", "\344\270\255\351\227\264\345\261\202\347\211\210\346\234\254\345\217\267", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("dlgTimeInterval", "\347\201\257\351\224\256\346\235\277:", 0, QApplication::UnicodeUTF8));
        label_CAN1_2->setText(QApplication::translate("dlgTimeInterval", "CAN1/2:", 0, QApplication::UnicodeUTF8));
        pushButton_can1can2->setText(QApplication::translate("dlgTimeInterval", "\350\257\273\345\217\226", 0, QApplication::UnicodeUTF8));
        label_CAN3_4->setText(QApplication::translate("dlgTimeInterval", "CAN3/4:", 0, QApplication::UnicodeUTF8));
        pushButton_can3can4->setText(QApplication::translate("dlgTimeInterval", "\350\257\273\345\217\226", 0, QApplication::UnicodeUTF8));
        label_CAN5_6->setText(QApplication::translate("dlgTimeInterval", "CAN5/6:", 0, QApplication::UnicodeUTF8));
        pushButton_can5can6->setText(QApplication::translate("dlgTimeInterval", "\350\257\273\345\217\226", 0, QApplication::UnicodeUTF8));
        label_CAN7_8->setText(QApplication::translate("dlgTimeInterval", "CAN7/8:", 0, QApplication::UnicodeUTF8));
        pushButton_can7can8->setText(QApplication::translate("dlgTimeInterval", "\350\257\273\345\217\226", 0, QApplication::UnicodeUTF8));
        PowerBox->setTitle(QApplication::translate("dlgTimeInterval", "PowerBox", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("dlgTimeInterval", "PowerSend:", 0, QApplication::UnicodeUTF8));
        label_powersend->setText(QApplication::translate("dlgTimeInterval", "0", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("dlgTimeInterval", "PowerOvertime:", 0, QApplication::UnicodeUTF8));
        label_powerotime->setText(QApplication::translate("dlgTimeInterval", "0", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("dlgTimeInterval", "PowerFault:", 0, QApplication::UnicodeUTF8));
        label_powerfault->setText(QApplication::translate("dlgTimeInterval", "0", 0, QApplication::UnicodeUTF8));
        SwitchLayerBox->setTitle(QApplication::translate("dlgTimeInterval", "Available", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("dlgTimeInterval", "Automatic Switch Layer:", 0, QApplication::UnicodeUTF8));
        SwitchLayerTime->setText(QString());
        label_2->setText(QApplication::translate("dlgTimeInterval", "Second", 0, QApplication::UnicodeUTF8));
        wlanBox->setTitle(QApplication::translate("dlgTimeInterval", "\347\275\221\345\217\243", 0, QApplication::UnicodeUTF8));
        label_myip1->setText(QApplication::translate("dlgTimeInterval", "\347\275\221\345\217\2431\345\234\260\345\235\200:", 0, QApplication::UnicodeUTF8));
        label_gateway1->setText(QApplication::translate("dlgTimeInterval", " \351\273\230\350\256\244\347\275\221\345\205\263: ", 0, QApplication::UnicodeUTF8));
        label_myip2->setText(QApplication::translate("dlgTimeInterval", "\347\275\221\345\217\2432\345\234\260\345\235\200:", 0, QApplication::UnicodeUTF8));
        label_gateway2->setText(QApplication::translate("dlgTimeInterval", " \351\273\230\350\256\244\347\275\221\345\205\263: ", 0, QApplication::UnicodeUTF8));
        pushButton_saveWlan->setText(QApplication::translate("dlgTimeInterval", "\344\277\235\345\255\230\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        UseTimeBox->setTitle(QApplication::translate("dlgTimeInterval", "\344\275\277\347\224\250\346\234\237\351\231\220", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("dlgTimeInterval", "\345\244\251", 0, QApplication::UnicodeUTF8));
        pushButton_UseTime->setText(QApplication::translate("dlgTimeInterval", "\344\277\256\346\224\271\344\275\277\347\224\250\346\234\237\351\231\220", 0, QApplication::UnicodeUTF8));
        timeBox->setTitle(QApplication::translate("dlgTimeInterval", "\346\227\266\351\227\264\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("dlgTimeInterval", "\346\227\245\346\234\237:", 0, QApplication::UnicodeUTF8));
        dateEdit->setDisplayFormat(QApplication::translate("dlgTimeInterval", "yyyy-MM-dd", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("dlgTimeInterval", "\346\227\266\351\227\264:", 0, QApplication::UnicodeUTF8));
        timeEdit->setDisplayFormat(QApplication::translate("dlgTimeInterval", "HH:mm:ss", 0, QApplication::UnicodeUTF8));
        m_ButtonTimeSet->setText(QApplication::translate("dlgTimeInterval", "\344\277\256\346\224\271\346\227\266\351\227\264", 0, QApplication::UnicodeUTF8));
        pingBox->setTitle(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\346\265\213\350\257\225(Ping)", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("dlgTimeInterval", "IP\345\234\260\345\235\200:", 0, QApplication::UnicodeUTF8));
        pingButton->setText(QApplication::translate("dlgTimeInterval", "ping", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("dlgTimeInterval", "\346\265\213\350\257\225\346\210\220\345\212\237\347\216\207:", 0, QApplication::UnicodeUTF8));
        cloudIPSetBox->setTitle(QApplication::translate("dlgTimeInterval", "\344\272\221\345\271\263\345\217\260IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_Hostip->setText(QApplication::translate("dlgTimeInterval", "IP\345\234\260\345\235\200:", 0, QApplication::UnicodeUTF8));
        label_com->setText(QApplication::translate("dlgTimeInterval", "\347\253\257   \345\217\243:", 0, QApplication::UnicodeUTF8));
        pushButton_saveCloudIP->setText(QApplication::translate("dlgTimeInterval", "\344\277\235\345\255\230\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_cloudComStatus->setText(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\347\212\266\346\200\201:", 0, QApplication::UnicodeUTF8));
        comStatusBox->setTitle(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\347\212\266\346\200\201", 0, QApplication::UnicodeUTF8));
        label_cloudStatus->setText(QApplication::translate("dlgTimeInterval", "\344\272\221\345\271\263\345\217\260:", 0, QApplication::UnicodeUTF8));
        label_masterStatus->setText(QApplication::translate("dlgTimeInterval", "\345\256\242\346\210\267\347\253\257:", 0, QApplication::UnicodeUTF8));
        StartRuleBox->setTitle(QApplication::translate("dlgTimeInterval", "\345\220\257\345\212\250\350\247\204\345\210\231", 0, QApplication::UnicodeUTF8));
        allStartCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\205\250\351\203\250\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        onlyStartGroupCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\210\206\347\273\204\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        onlyStartPageCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\220\257\345\212\250\346\211\200\345\234\250\351\241\265\351\235\242", 0, QApplication::UnicodeUTF8));
        CanNumberBox->setTitle(QApplication::translate("dlgTimeInterval", "CAN\345\233\236\350\267\257\346\225\260", 0, QApplication::UnicodeUTF8));
        Can4CheckBox->setText(QApplication::translate("dlgTimeInterval", "4\350\267\257CAN", 0, QApplication::UnicodeUTF8));
        Can8CheckBox->setText(QApplication::translate("dlgTimeInterval", "8\350\267\257CAN", 0, QApplication::UnicodeUTF8));
        controlType->setTitle(QApplication::translate("dlgTimeInterval", "\344\270\273\346\234\272\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        singleWLAN->setText(QApplication::translate("dlgTimeInterval", "\345\215\225\347\275\221\345\217\243", 0, QApplication::UnicodeUTF8));
        doubleWLAN->setText(QApplication::translate("dlgTimeInterval", "\345\217\214\347\275\221\345\217\243", 0, QApplication::UnicodeUTF8));
        AutoPageBox->setTitle(QApplication::translate("dlgTimeInterval", "\350\207\252\345\212\250\350\275\256\350\257\242\351\241\265\351\235\242", 0, QApplication::UnicodeUTF8));
        autoPageCheckBox->setText(QApplication::translate("dlgTimeInterval", "\350\207\252\345\212\250\350\275\256\350\257\242\351\241\265\351\235\242", 0, QApplication::UnicodeUTF8));
        testLinkageComBox->setTitle(QApplication::translate("dlgTimeInterval", "RS232/RS485\351\200\232\350\256\257(\347\201\253\346\212\245)", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("dlgTimeInterval", "\346\263\242\347\211\271\347\216\207:", 0, QApplication::UnicodeUTF8));
        comboBox_testLinkageCom->clear();
        comboBox_testLinkageCom->insertItems(0, QStringList()
         << QApplication::translate("dlgTimeInterval", "4800", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgTimeInterval", "9600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgTimeInterval", "19200", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgTimeInterval", "38400", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgTimeInterval", "57600", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("dlgTimeInterval", "115200", 0, QApplication::UnicodeUTF8)
        );
        pushButton_testLinkageCom->setText(QApplication::translate("dlgTimeInterval", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\346\265\213\350\257\225:", 0, QApplication::UnicodeUTF8));
        testLinkageComButton->setText(QApplication::translate("dlgTimeInterval", "\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("dlgTimeInterval", "\351\200\232\350\256\257\347\212\266\346\200\201:", 0, QApplication::UnicodeUTF8));
        groupBox_phoneNumber->setTitle(QApplication::translate("dlgTimeInterval", "\350\201\224\347\263\273\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        pushButton_phoneNumber->setText(QApplication::translate("dlgTimeInterval", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox_firepointNumber->setTitle(QApplication::translate("dlgTimeInterval", "\345\220\257\345\212\250\347\201\253\350\255\246\347\202\271\344\270\252\346\225\260", 0, QApplication::UnicodeUTF8));
        pushButton_firepointNumber->setText(QApplication::translate("dlgTimeInterval", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        pushButton_lampForbidList->setText(QApplication::translate("dlgTimeInterval", "\346\230\276\347\244\272\347\201\257\345\205\267\347\246\201\347\224\250\345\210\227\350\241\250", 0, QApplication::UnicodeUTF8));
        lampEmergencyType->setTitle(QApplication::translate("dlgTimeInterval", "\347\201\257\345\205\267\345\272\224\346\200\245\347\261\273\345\236\213", 0, QApplication::UnicodeUTF8));
        DirectionTwinkleOneCheckBox->setText(QApplication::translate("dlgTimeInterval", "\347\201\257\345\205\267\346\226\271\345\220\221\345\222\214\351\227\252\347\203\201\350\277\236\345\217\221", 0, QApplication::UnicodeUTF8));
        DirectionTwinkleDoubleCheckBox->setText(QApplication::translate("dlgTimeInterval", "\347\201\257\345\205\267\346\226\271\345\220\221\343\200\201\351\227\252\347\203\201\345\215\225\347\213\254\346\216\247\345\210\266", 0, QApplication::UnicodeUTF8));
        TwinkleConfigCheckBox->setText(QApplication::translate("dlgTimeInterval", "\351\227\252\347\203\201\351\205\215\347\275\256\345\236\213\347\201\257\345\205\267", 0, QApplication::UnicodeUTF8));
        pushButton_lamptwinkleconfig->setText(QApplication::translate("dlgTimeInterval", "\347\201\257\345\205\267\351\227\252\347\203\201\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        ARTUBox->setTitle(QApplication::translate("dlgTimeInterval", "ARTU\350\201\224\345\212\250\346\250\241\345\235\227", 0, QApplication::UnicodeUTF8));
        forbidARTUCheckBox->setText(QApplication::translate("dlgTimeInterval", "\347\246\201\347\224\250ARTU", 0, QApplication::UnicodeUTF8));
        ARTU079KCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\220\257\347\224\250079ARTU-K", 0, QApplication::UnicodeUTF8));
        ARTU079KJCheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\220\257\347\224\250079ARTU-KJ", 0, QApplication::UnicodeUTF8));
        ARTU426CheckBox->setText(QApplication::translate("dlgTimeInterval", "\345\220\257\347\224\250ARTU-426", 0, QApplication::UnicodeUTF8));
        groupBox_ModbusTcp->setTitle(QApplication::translate("dlgTimeInterval", "ModbusTCP\346\234\215\345\212\241", 0, QApplication::UnicodeUTF8));
        pushButton_ModbusTcp->setText(QApplication::translate("dlgTimeInterval", "\345\257\274\345\207\272\345\257\204\345\255\230\345\231\250\347\202\271\350\241\250", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class dlgTimeInterval: public Ui_dlgTimeInterval {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGTIMEINTERVAL_H
