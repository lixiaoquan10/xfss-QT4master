/****************************************************************************
** Meta object code from reading C++ file 'ctoptoolbar.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/widget/ctoptoolbar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ctoptoolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CTopToolBar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      42,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      33,   12,   12,   12, 0x0a,
      52,   12,   12,   12, 0x0a,
      70,   12,   12,   12, 0x0a,
      91,   12,   12,   12, 0x0a,
     112,   12,   12,   12, 0x0a,
     136,   12,   12,   12, 0x0a,
     150,   12,   12,   12, 0x0a,
     171,   12,   12,   12, 0x0a,
     188,   12,   12,   12, 0x0a,
     206,   12,   12,   12, 0x0a,
     222,   12,   12,   12, 0x0a,
     237,   12,   12,   12, 0x0a,
     258,   12,   12,   12, 0x0a,
     280,   12,   12,   12, 0x0a,
     297,   12,   12,   12, 0x0a,
     311,   12,   12,   12, 0x0a,
     330,   12,   12,   12, 0x0a,
     344,   12,   12,   12, 0x0a,
     359,   12,   12,   12, 0x0a,
     371,   12,   12,   12, 0x0a,
     382,   12,   12,   12, 0x0a,
     397,   12,   12,   12, 0x0a,
     412,   12,   12,   12, 0x0a,
     429,   12,   12,   12, 0x0a,
     442,   12,   12,   12, 0x0a,
     453,   12,   12,   12, 0x0a,
     471,   12,   12,   12, 0x0a,
     495,   12,   12,   12, 0x0a,
     518,   12,   12,   12, 0x0a,
     539,   12,   12,   12, 0x0a,
     562,   12,   12,   12, 0x0a,
     575,   12,   12,   12, 0x0a,
     589,   12,   12,   12, 0x0a,
     601,   12,   12,   12, 0x0a,
     617,   12,   12,   12, 0x0a,
     634,   12,   12,   12, 0x0a,
     658,   12,   12,   12, 0x0a,
     670,   12,   12,   12, 0x0a,
     683,   12,   12,   12, 0x0a,
     704,   12,   12,   12, 0x0a,
     729,  726,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CTopToolBar[] = {
    "CTopToolBar\0\0slotShowCheckMenu()\0"
    "slotShowListMenu()\0slotShowRegMenu()\0"
    "slotShowBrowseMenu()\0slotShowManageMenu()\0"
    "slotShowEmergencyMenu()\0slottimeout()\0"
    "slotShowSystemMenu()\0slotMuteSystem()\0"
    "slotResetSystem()\0slotMonthTest()\0"
    "slotYearTest()\0slotDayInformation()\0"
    "slotWeekInformation()\0slotDeviceInfo()\0"
    "slotCanInfo()\0slotSearchDevice()\0"
    "slotLogging()\0slotSelfTest()\0slotStart()\0"
    "slotStop()\0slotHandFire()\0slotListView()\0"
    "slotLayoutView()\0slotManual()\0slotAuto()\0"
    "slotSystemSetup()\0slotStartSimulateTime()\0"
    "slotStopSimulateTime()\0slotSaveDeviceData()\0"
    "slotSaveDeviceStatus()\0slotOutUSB()\0"
    "slotReStart()\0slotAbout()\0slotUpdateLog()\0"
    "slotRefreshUSB()\0slotScreenCalibration()\0"
    "slotLogin()\0slotLogout()\0slotCheckLoginInfo()\0"
    "slot_threadFinished()\0,,\0"
    "slot_updateStatus(CObject*,short,unsigned char)\0"
};

void CTopToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CTopToolBar *_t = static_cast<CTopToolBar *>(_o);
        switch (_id) {
        case 0: _t->slotShowCheckMenu(); break;
        case 1: _t->slotShowListMenu(); break;
        case 2: _t->slotShowRegMenu(); break;
        case 3: _t->slotShowBrowseMenu(); break;
        case 4: _t->slotShowManageMenu(); break;
        case 5: _t->slotShowEmergencyMenu(); break;
        case 6: _t->slottimeout(); break;
        case 7: _t->slotShowSystemMenu(); break;
        case 8: _t->slotMuteSystem(); break;
        case 9: _t->slotResetSystem(); break;
        case 10: _t->slotMonthTest(); break;
        case 11: _t->slotYearTest(); break;
        case 12: _t->slotDayInformation(); break;
        case 13: _t->slotWeekInformation(); break;
        case 14: _t->slotDeviceInfo(); break;
        case 15: _t->slotCanInfo(); break;
        case 16: _t->slotSearchDevice(); break;
        case 17: _t->slotLogging(); break;
        case 18: _t->slotSelfTest(); break;
        case 19: _t->slotStart(); break;
        case 20: _t->slotStop(); break;
        case 21: _t->slotHandFire(); break;
        case 22: _t->slotListView(); break;
        case 23: _t->slotLayoutView(); break;
        case 24: _t->slotManual(); break;
        case 25: _t->slotAuto(); break;
        case 26: _t->slotSystemSetup(); break;
        case 27: _t->slotStartSimulateTime(); break;
        case 28: _t->slotStopSimulateTime(); break;
        case 29: _t->slotSaveDeviceData(); break;
        case 30: _t->slotSaveDeviceStatus(); break;
        case 31: _t->slotOutUSB(); break;
        case 32: _t->slotReStart(); break;
        case 33: _t->slotAbout(); break;
        case 34: _t->slotUpdateLog(); break;
        case 35: _t->slotRefreshUSB(); break;
        case 36: _t->slotScreenCalibration(); break;
        case 37: _t->slotLogin(); break;
        case 38: _t->slotLogout(); break;
        case 39: _t->slotCheckLoginInfo(); break;
        case 40: _t->slot_threadFinished(); break;
        case 41: _t->slot_updateStatus((*reinterpret_cast< CObject*(*)>(_a[1])),(*reinterpret_cast< short(*)>(_a[2])),(*reinterpret_cast< unsigned char(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CTopToolBar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CTopToolBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CTopToolBar,
      qt_meta_data_CTopToolBar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CTopToolBar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CTopToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CTopToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CTopToolBar))
        return static_cast<void*>(const_cast< CTopToolBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int CTopToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    }
    return _id;
}
static const uint qt_meta_data_resetThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,
      33,   30,   12,   12, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_resetThread[] = {
    "resetThread\0\0threadFinished()\0,,\0"
    "updateStatus(CObject*,short,unsigned char)\0"
};

void resetThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        resetThread *_t = static_cast<resetThread *>(_o);
        switch (_id) {
        case 0: _t->threadFinished(); break;
        case 1: _t->updateStatus((*reinterpret_cast< CObject*(*)>(_a[1])),(*reinterpret_cast< short(*)>(_a[2])),(*reinterpret_cast< unsigned char(*)>(_a[3]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData resetThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject resetThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_resetThread,
      qt_meta_data_resetThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &resetThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *resetThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *resetThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_resetThread))
        return static_cast<void*>(const_cast< resetThread*>(this));
    return QThread::qt_metacast(_clname);
}

int resetThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void resetThread::threadFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void resetThread::updateStatus(CObject * _t1, short _t2, unsigned char _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
