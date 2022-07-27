/****************************************************************************
** Meta object code from reading C++ file 'gainsetdlg.h'
**
** Created: Tue Jul 26 18:36:58 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gainsetdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gainsetdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CGainSetdlg[] = {

 // content:
       5,       // revision
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

const QMetaObject CGainSetdlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CGainSetdlg,
      qt_meta_data_CGainSetdlg, 0 }
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
        switch (_id) {
        case 0: updateProgressBarValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: okBtn_clicked(); break;
        case 2: cancelBtn_clicked(); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
