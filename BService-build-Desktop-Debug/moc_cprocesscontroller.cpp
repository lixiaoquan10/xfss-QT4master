/****************************************************************************
** Meta object code from reading C++ file 'cprocesscontroller.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BService/process/cprocesscontroller.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprocesscontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CProcessController[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      32,   19,   19,   19, 0x0a,
      48,   19,   19,   19, 0x0a,
      65,   19,   19,   19, 0x0a,
      83,   19,   19,   19, 0x0a,
     101,   19,   19,   19, 0x0a,
     119,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CProcessController[] = {
    "CProcessController\0\0selfCheck()\0"
    "stopSelfCheck()\0yearMonthCheck()\0"
    "updateLedStatus()\0KeyFlagTimeStop()\0"
    "slot_searchFire()\0slot_resetARTUdoStatus()\0"
};

void CProcessController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CProcessController *_t = static_cast<CProcessController *>(_o);
        switch (_id) {
        case 0: _t->selfCheck(); break;
        case 1: _t->stopSelfCheck(); break;
        case 2: _t->yearMonthCheck(); break;
        case 3: _t->updateLedStatus(); break;
        case 4: _t->KeyFlagTimeStop(); break;
        case 5: _t->slot_searchFire(); break;
        case 6: _t->slot_resetARTUdoStatus(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CProcessController::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CProcessController::staticMetaObject = {
    { &CProcessBase::staticMetaObject, qt_meta_stringdata_CProcessController,
      qt_meta_data_CProcessController, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CProcessController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CProcessController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CProcessController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CProcessController))
        return static_cast<void*>(const_cast< CProcessController*>(this));
    return CProcessBase::qt_metacast(_clname);
}

int CProcessController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CProcessBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE