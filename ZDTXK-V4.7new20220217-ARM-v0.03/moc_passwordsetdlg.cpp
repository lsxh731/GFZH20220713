/****************************************************************************
** Meta object code from reading C++ file 'passwordsetdlg.h'
**
** Created: Tue Jul 26 18:36:54 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "passwordsetdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'passwordsetdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CPasswordSetdlg[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      33,   16,   16,   16, 0x0a,
      53,   16,   16,   16, 0x0a,
      72,   16,   16,   16, 0x0a,
      94,   16,   16,   16, 0x0a,
     116,   16,   16,   16, 0x0a,
     138,   16,   16,   16, 0x0a,
     160,   16,   16,   16, 0x0a,
     182,   16,   16,   16, 0x0a,
     204,   16,   16,   16, 0x0a,
     226,   16,   16,   16, 0x0a,
     248,   16,   16,   16, 0x0a,
     270,   16,   16,   16, 0x0a,
     292,   16,   16,   16, 0x0a,
     314,   16,   16,   16, 0x0a,
     335,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CPasswordSetdlg[] = {
    "CPasswordSetdlg\0\0okBtn_clicked()\0"
    "cancelBtn_clicked()\0clearBtn_clicked()\0"
    "pushButton0_clicked()\0pushButton1_clicked()\0"
    "pushButton2_clicked()\0pushButton3_clicked()\0"
    "pushButton4_clicked()\0pushButton5_clicked()\0"
    "pushButton6_clicked()\0pushButton7_clicked()\0"
    "pushButton8_clicked()\0pushButton9_clicked()\0"
    "rBtncurrpwd_clicked()\0rBtnnewpwd_clicked()\0"
    "rBtncheckpwd_clicked()\0"
};

const QMetaObject CPasswordSetdlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CPasswordSetdlg,
      qt_meta_data_CPasswordSetdlg, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CPasswordSetdlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CPasswordSetdlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CPasswordSetdlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CPasswordSetdlg))
        return static_cast<void*>(const_cast< CPasswordSetdlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CPasswordSetdlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: okBtn_clicked(); break;
        case 1: cancelBtn_clicked(); break;
        case 2: clearBtn_clicked(); break;
        case 3: pushButton0_clicked(); break;
        case 4: pushButton1_clicked(); break;
        case 5: pushButton2_clicked(); break;
        case 6: pushButton3_clicked(); break;
        case 7: pushButton4_clicked(); break;
        case 8: pushButton5_clicked(); break;
        case 9: pushButton6_clicked(); break;
        case 10: pushButton7_clicked(); break;
        case 11: pushButton8_clicked(); break;
        case 12: pushButton9_clicked(); break;
        case 13: rBtncurrpwd_clicked(); break;
        case 14: rBtnnewpwd_clicked(); break;
        case 15: rBtncheckpwd_clicked(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
