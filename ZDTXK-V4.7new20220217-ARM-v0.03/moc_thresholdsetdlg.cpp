/****************************************************************************
** Meta object code from reading C++ file 'thresholdsetdlg.h'
**
** Created: Thu Jul 7 23:41:50 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "thresholdsetdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'thresholdsetdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CThresholdsetdlg[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      39,   17,   17,   17, 0x08,
      60,   17,   17,   17, 0x08,
      81,   17,   17,   17, 0x08,
     104,   17,   17,   17, 0x08,
     125,   17,   17,   17, 0x08,
     149,   17,   17,   17, 0x08,
     170,   17,   17,   17, 0x08,
     194,   17,   17,   17, 0x08,
     215,   17,   17,   17, 0x08,
     238,   17,   17,   17, 0x08,
     264,   17,   17,   17, 0x08,
     286,   17,   17,   17, 0x08,
     308,   17,   17,   17, 0x08,
     328,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_CThresholdsetdlg[] = {
    "CThresholdsetdlg\0\0scbhSetBtn_clicked()\0"
    "gybhSetBtn_clicked()\0scdlSetBtn_clicked()\0"
    "IGBTgwSetBtn_clicked()\0dggwSetBtn_clicked()\0"
    "scbhLowerEdit_clicked()\0scbhUpEdit_clicked()\0"
    "gybhLowerEdit_clicked()\0gybhUpEdit_clicked()\0"
    "scdlProcEdit_clicked()\0scdlWarningEdit_clicked()\0"
    "IGBTgw1Edit_clicked()\0IGBTgw2Edit_clicked()\0"
    "dggw1Edit_clicked()\0dggw2Edit_clicked()\0"
};

const QMetaObject CThresholdsetdlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CThresholdsetdlg,
      qt_meta_data_CThresholdsetdlg, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CThresholdsetdlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CThresholdsetdlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CThresholdsetdlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CThresholdsetdlg))
        return static_cast<void*>(const_cast< CThresholdsetdlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CThresholdsetdlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: scbhSetBtn_clicked(); break;
        case 1: gybhSetBtn_clicked(); break;
        case 2: scdlSetBtn_clicked(); break;
        case 3: IGBTgwSetBtn_clicked(); break;
        case 4: dggwSetBtn_clicked(); break;
        case 5: scbhLowerEdit_clicked(); break;
        case 6: scbhUpEdit_clicked(); break;
        case 7: gybhLowerEdit_clicked(); break;
        case 8: gybhUpEdit_clicked(); break;
        case 9: scdlProcEdit_clicked(); break;
        case 10: scdlWarningEdit_clicked(); break;
        case 11: IGBTgw1Edit_clicked(); break;
        case 12: IGBTgw2Edit_clicked(); break;
        case 13: dggw1Edit_clicked(); break;
        case 14: dggw2Edit_clicked(); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
