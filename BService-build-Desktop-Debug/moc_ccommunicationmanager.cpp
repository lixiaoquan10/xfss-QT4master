/****************************************************************************
** Meta object code from reading C++ file 'ccommunicationmanager.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../BService/process/ccommunicationmanager.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ccommunicationmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CCommunicationManager[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      37,   23,   22,   22, 0x05,
      98,   61,   22,   22, 0x05,

 // slots: signature, parameters, type, tag, flags
     171,  161,   22,   22, 0x0a,
     204,   22,   22,   22, 0x0a,
     228,   22,   22,   22, 0x0a,
     246,   22,   22,   22, 0x08,
     268,   22,   22,   22, 0x08,
     294,   22,   22,   22, 0x08,
     317,   22,   22,   22, 0x08,
     340,   22,   22,   22, 0x08,
     382,  363,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CCommunicationManager[] = {
    "CCommunicationManager\0\0nSerialNumber\0"
    "sig_ReceivedPacket(int)\0"
    "lineName,infoType,controlDomain,data\0"
    "sig_ReciveData(QString,int,QHash<QString,QVariant>,QByteArray)\0"
    "name,data\0doReciveData(QString,QByteArray)\0"
    "slot_LinkageFlagReset()\0slot_ARTUDIsend()\0"
    "handleLedReciveData()\0handleLinkageReciveData()\0"
    "handleTestReciveData()\0handleCan1ReciveData()\0"
    "handleCan2ReciveData()\0name,nSerialNumber\0"
    "updataRecentSerialNumber(QString,int)\0"
};

void CCommunicationManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CCommunicationManager *_t = static_cast<CCommunicationManager *>(_o);
        switch (_id) {
        case 0: _t->sig_ReceivedPacket((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sig_ReciveData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< const QHash<QString,QVariant>(*)>(_a[3])),(*reinterpret_cast< const QByteArray(*)>(_a[4]))); break;
        case 2: _t->doReciveData((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 3: _t->slot_LinkageFlagReset(); break;
        case 4: _t->slot_ARTUDIsend(); break;
        case 5: _t->handleLedReciveData(); break;
        case 6: _t->handleLinkageReciveData(); break;
        case 7: _t->handleTestReciveData(); break;
        case 8: _t->handleCan1ReciveData(); break;
        case 9: _t->handleCan2ReciveData(); break;
        case 10: _t->updataRecentSerialNumber((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CCommunicationManager::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CCommunicationManager::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CCommunicationManager,
      qt_meta_data_CCommunicationManager, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CCommunicationManager::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CCommunicationManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CCommunicationManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CCommunicationManager))
        return static_cast<void*>(const_cast< CCommunicationManager*>(this));
    return QObject::qt_metacast(_clname);
}

int CCommunicationManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void CCommunicationManager::sig_ReceivedPacket(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CCommunicationManager::sig_ReciveData(const QString & _t1, const int & _t2, const QHash<QString,QVariant> & _t3, const QByteArray & _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
