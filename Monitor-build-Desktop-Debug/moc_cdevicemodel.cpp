/****************************************************************************
** Meta object code from reading C++ file 'cdevicemodel.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Monitor/model/cdevicemodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cdevicemodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CDeviceModel[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      26,   14,   13,   13, 0x09,
      77,   70,   13,   13, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CDeviceModel[] = {
    "CDeviceModel\0\0type,object\0"
    "objectChanged(CObject::ObjectType,CObject*)\0"
    "object\0objectDestroy(CObject*)\0"
};

void CDeviceModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CDeviceModel *_t = static_cast<CDeviceModel *>(_o);
        switch (_id) {
        case 0: _t->objectChanged((*reinterpret_cast< CObject::ObjectType(*)>(_a[1])),(*reinterpret_cast< CObject*(*)>(_a[2]))); break;
        case 1: _t->objectDestroy((*reinterpret_cast< CObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CDeviceModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CDeviceModel::staticMetaObject = {
    { &CModel::staticMetaObject, qt_meta_stringdata_CDeviceModel,
      qt_meta_data_CDeviceModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CDeviceModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CDeviceModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CDeviceModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CDeviceModel))
        return static_cast<void*>(const_cast< CDeviceModel*>(this));
    return CModel::qt_metacast(_clname);
}

int CDeviceModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
