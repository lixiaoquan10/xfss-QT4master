/****************************************************************************
** Meta object code from reading C++ file 'cprocessModbusTcp.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/business/cprocessModbusTcp.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprocessModbusTcp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CprocessModbusTcp[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      41,   18,   18,   18, 0x0a,
      68,   18,   18,   18, 0x0a,
      88,   18,   18,   18, 0x0a,
     120,  114,   18,   18, 0x0a,
     164,   18,   18,   18, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CprocessModbusTcp[] = {
    "CprocessModbusTcp\0\0slot_readClientData()\0"
    "slot_handleNewConnection()\0"
    "slot_serverlisten()\0slot_handleDisconnected()\0"
    "error\0onSocketError(QAbstractSocket::SocketError)\0"
    "slot_controlTxtFileSize()\0"
};

void CprocessModbusTcp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CprocessModbusTcp *_t = static_cast<CprocessModbusTcp *>(_o);
        switch (_id) {
        case 0: _t->slot_readClientData(); break;
        case 1: _t->slot_handleNewConnection(); break;
        case 2: _t->slot_serverlisten(); break;
        case 3: _t->slot_handleDisconnected(); break;
        case 4: _t->onSocketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->slot_controlTxtFileSize(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CprocessModbusTcp::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CprocessModbusTcp::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CprocessModbusTcp,
      qt_meta_data_CprocessModbusTcp, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CprocessModbusTcp::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CprocessModbusTcp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CprocessModbusTcp::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CprocessModbusTcp))
        return static_cast<void*>(const_cast< CprocessModbusTcp*>(this));
    return QObject::qt_metacast(_clname);
}

int CprocessModbusTcp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
