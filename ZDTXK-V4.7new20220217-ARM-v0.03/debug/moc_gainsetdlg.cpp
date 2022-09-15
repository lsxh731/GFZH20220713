/****************************************************************************
** Meta object code from reading C++ file 'gainsetdlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../gainsetdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gainsetdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CGainSetdlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   13,   12,   12, 0x0a,
      48,   12,   12,   12, 0x0a,
      64,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CGainSetdlg[] = {
    "CGainSetdlg\0\0nValue\0updateProgressBarValue(int)\0"
    "okBtn_clicked()\0cancelBtn_clicked()\0"
};

void CGainSetdlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CGainSetdlg *_t = static_cast<CGainSetdlg *>(_o);
        switch (_id) {
        case 0: _t->updateProgressBarValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->okBtn_clicked(); break;
        case 2: _t->cancelBtn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CGainSetdlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CGainSetdlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CGainSetdlg,
      qt_meta_data_CGainSetdlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CGainSetdlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CGainSetdlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CGainSetdlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CGainSetdlg))
        return static_cast<void*>(const_cast< CGainSetdlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CGainSetdlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
