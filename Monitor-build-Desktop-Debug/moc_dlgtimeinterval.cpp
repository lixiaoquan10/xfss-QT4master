/****************************************************************************
** Meta object code from reading C++ file 'dlgtimeinterval.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/dialog/dlgtimeinterval.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dlgtimeinterval.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_dlgTimeInterval[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   17,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      48,   16,   16,   16, 0x08,
      80,   16,   16,   16, 0x08,
     109,   16,   16,   16, 0x08,
     133,   16,   16,   16, 0x08,
     165,  153,   16,   16, 0x08,
     191,   16,   16,   16, 0x08,
     212,   16,   16,   16, 0x08,
     241,   16,   16,   16, 0x08,
     269,   16,   16,   16, 0x08,
     305,   16,   16,   16, 0x08,
     338,   16,   16,   16, 0x08,
     371,   16,   16,   16, 0x08,
     401,   16,   16,   16, 0x08,
     436,   16,   16,   16, 0x08,
     472,   16,   16,   16, 0x08,
     498,   16,   16,   16, 0x08,
     524,   16,   16,   16, 0x08,
     552,   16,   16,   16, 0x08,
     585,   16,   16,   16, 0x08,
     618,   16,   16,   16, 0x08,
     642,   16,   16,   16, 0x08,
     666,   16,   16,   16, 0x08,
     699,   16,   16,   16, 0x08,
     729,   16,   16,   16, 0x08,
     763,   16,   16,   16, 0x08,
     784,   16,   16,   16, 0x08,
     823,   16,   16,   16, 0x08,
     870,   16,   16,   16, 0x08,
     906,   16,   16,   16, 0x08,
     945,   16,   16,   16, 0x08,
     985,   16,   16,   16, 0x08,
    1026,   16,   16,   16, 0x08,
    1070,   16,   16,   16, 0x08,
    1105,   16,   16,   16, 0x08,
    1147,   16,   16,   16, 0x08,
    1179,   16,   16,   16, 0x08,
    1209,   16,   16,   16, 0x08,
    1240,   16,   16,   16, 0x08,
    1269,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_dlgTimeInterval[] = {
    "dlgTimeInterval\0\0checked\0"
    "m_Checked_signal(bool)\0"
    "on_pushButton_UseTime_clicked()\0"
    "on_m_ButtonTimeSet_clicked()\0"
    "on_pingButton_clicked()\0slot_timeFinished()\0"
    "successRate\0slot_pingFinished(double)\0"
    "slot_ipsetFinished()\0on_TwinkleCheckBox_clicked()\0"
    "on_EnergyCheckBox_clicked()\0"
    "on_pushButton_saveCloudIP_clicked()\0"
    "on_pushButton_can1can2_clicked()\0"
    "on_pushButton_can3can4_clicked()\0"
    "on_allStartCheckBox_clicked()\0"
    "on_onlyStartPageCheckBox_clicked()\0"
    "on_onlyStartGroupCheckBox_clicked()\0"
    "on_Can4CheckBox_clicked()\0"
    "on_Can8CheckBox_clicked()\0"
    "on_triangleButton_clicked()\0"
    "on_pushButton_can5can6_clicked()\0"
    "on_pushButton_can7can8_clicked()\0"
    "on_singleWLAN_clicked()\0on_doubleWLAN_clicked()\0"
    "on_pushButton_saveWlan_clicked()\0"
    "on_autoPageCheckBox_clicked()\0"
    "on_testLinkageComButton_clicked()\0"
    "slot_testComResult()\0"
    "on_pushButton_testLinkageCom_clicked()\0"
    "on_emergencyOnlyDistributionCheckBox_clicked()\0"
    "on_pushButton_phoneNumber_clicked()\0"
    "on_pushButton_lampForbidList_clicked()\0"
    "on_pushButton_firepointNumber_clicked()\0"
    "on_DirectionTwinkleOneCheckBox_clicked()\0"
    "on_DirectionTwinkleDoubleCheckBox_clicked()\0"
    "on_TwinkleConfigCheckBox_clicked()\0"
    "on_pushButton_lamptwinkleconfig_clicked()\0"
    "on_forbidARTUCheckBox_clicked()\0"
    "on_ARTU079KCheckBox_clicked()\0"
    "on_ARTU079KJCheckBox_clicked()\0"
    "on_ARTU426CheckBox_clicked()\0"
    "on_pushButton_ModbusTcp_clicked()\0"
};

void dlgTimeInterval::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        dlgTimeInterval *_t = static_cast<dlgTimeInterval *>(_o);
        switch (_id) {
        case 0: _t->m_Checked_signal((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_UseTime_clicked(); break;
        case 2: _t->on_m_ButtonTimeSet_clicked(); break;
        case 3: _t->on_pingButton_clicked(); break;
        case 4: _t->slot_timeFinished(); break;
        case 5: _t->slot_pingFinished((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 6: _t->slot_ipsetFinished(); break;
        case 7: _t->on_TwinkleCheckBox_clicked(); break;
        case 8: _t->on_EnergyCheckBox_clicked(); break;
        case 9: _t->on_pushButton_saveCloudIP_clicked(); break;
        case 10: _t->on_pushButton_can1can2_clicked(); break;
        case 11: _t->on_pushButton_can3can4_clicked(); break;
        case 12: _t->on_allStartCheckBox_clicked(); break;
        case 13: _t->on_onlyStartPageCheckBox_clicked(); break;
        case 14: _t->on_onlyStartGroupCheckBox_clicked(); break;
        case 15: _t->on_Can4CheckBox_clicked(); break;
        case 16: _t->on_Can8CheckBox_clicked(); break;
        case 17: _t->on_triangleButton_clicked(); break;
        case 18: _t->on_pushButton_can5can6_clicked(); break;
        case 19: _t->on_pushButton_can7can8_clicked(); break;
        case 20: _t->on_singleWLAN_clicked(); break;
        case 21: _t->on_doubleWLAN_clicked(); break;
        case 22: _t->on_pushButton_saveWlan_clicked(); break;
        case 23: _t->on_autoPageCheckBox_clicked(); break;
        case 24: _t->on_testLinkageComButton_clicked(); break;
        case 25: _t->slot_testComResult(); break;
        case 26: _t->on_pushButton_testLinkageCom_clicked(); break;
        case 27: _t->on_emergencyOnlyDistributionCheckBox_clicked(); break;
        case 28: _t->on_pushButton_phoneNumber_clicked(); break;
        case 29: _t->on_pushButton_lampForbidList_clicked(); break;
        case 30: _t->on_pushButton_firepointNumber_clicked(); break;
        case 31: _t->on_DirectionTwinkleOneCheckBox_clicked(); break;
        case 32: _t->on_DirectionTwinkleDoubleCheckBox_clicked(); break;
        case 33: _t->on_TwinkleConfigCheckBox_clicked(); break;
        case 34: _t->on_pushButton_lamptwinkleconfig_clicked(); break;
        case 35: _t->on_forbidARTUCheckBox_clicked(); break;
        case 36: _t->on_ARTU079KCheckBox_clicked(); break;
        case 37: _t->on_ARTU079KJCheckBox_clicked(); break;
        case 38: _t->on_ARTU426CheckBox_clicked(); break;
        case 39: _t->on_pushButton_ModbusTcp_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData dlgTimeInterval::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject dlgTimeInterval::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_dlgTimeInterval,
      qt_meta_data_dlgTimeInterval, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &dlgTimeInterval::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *dlgTimeInterval::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *dlgTimeInterval::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_dlgTimeInterval))
        return static_cast<void*>(const_cast< dlgTimeInterval*>(this));
    return QDialog::qt_metacast(_clname);
}

int dlgTimeInterval::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    }
    return _id;
}

// SIGNAL 0
void dlgTimeInterval::m_Checked_signal(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_timeThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_timeThread[] = {
    "timeThread\0\0timeFinished()\0"
};

void timeThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        timeThread *_t = static_cast<timeThread *>(_o);
        switch (_id) {
        case 0: _t->timeFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData timeThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject timeThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_timeThread,
      qt_meta_data_timeThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &timeThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *timeThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *timeThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_timeThread))
        return static_cast<void*>(const_cast< timeThread*>(this));
    return QThread::qt_metacast(_clname);
}

int timeThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void timeThread::timeFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_ipsetThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ipsetThread[] = {
    "ipsetThread\0\0ipsetFinished()\0"
};

void ipsetThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ipsetThread *_t = static_cast<ipsetThread *>(_o);
        switch (_id) {
        case 0: _t->ipsetFinished(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ipsetThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ipsetThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ipsetThread,
      qt_meta_data_ipsetThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ipsetThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ipsetThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ipsetThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ipsetThread))
        return static_cast<void*>(const_cast< ipsetThread*>(this));
    return QThread::qt_metacast(_clname);
}

int ipsetThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ipsetThread::ipsetFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
static const uint qt_meta_data_pingThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      24,   12,   11,   11, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_pingThread[] = {
    "pingThread\0\0successRate\0pingFinished(double)\0"
};

void pingThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        pingThread *_t = static_cast<pingThread *>(_o);
        switch (_id) {
        case 0: _t->pingFinished((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData pingThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject pingThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_pingThread,
      qt_meta_data_pingThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &pingThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *pingThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *pingThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_pingThread))
        return static_cast<void*>(const_cast< pingThread*>(this));
    return QThread::qt_metacast(_clname);
}

int pingThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void pingThread::pingFinished(double _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
