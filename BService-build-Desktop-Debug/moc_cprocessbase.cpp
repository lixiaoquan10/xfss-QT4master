/****************************************************************************
** Meta object code from reading C++ file 'cprocessbase.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BService/process/cprocessbase.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cprocessbase.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CProcessBase[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      48,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     106,   14,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CProcessBase[] = {
    "CProcessBase\0\0processname,infoType,control,data\0"
    "sendEvent(QString,int,QHash<QString,QVariant>,QByteArray)\0"
    "recvEvent(QString,int,QHash<QString,QVariant>,QByteArray)\0"
};

void CProcessBase::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CProcessBase *_t = static_cast<CProcessBase *>(_o);
        switch (_id) {
        case 0: _t->sendEvent((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4]))); break;
        case 1: _t->recvEvent((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CProcessBase::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CProcessBase::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CProcessBase,
      qt_meta_data_CProcessBase, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CProcessBase::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CProcessBase::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CProcessBase::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CProcessBase))
        return static_cast<void*>(const_cast< CProcessBase*>(this));
    return QObject::qt_metacast(_clname);
}

int CProcessBase::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void CProcessBase::sendEvent(const QString & _t1, const int & _t2, const QHash<QString,QVariant> & _t3, const QByteArray & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE