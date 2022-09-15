/****************************************************************************
** Meta object code from reading C++ file 'keyboarddlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ZDTXK-V4.7new20220217-ARM-v0.03-0722/keyboarddlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyboarddlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CKeyBoardDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      30,   13,   13,   13, 0x0a,
      50,   13,   13,   13, 0x0a,
      69,   13,   13,   13, 0x0a,
      91,   13,   13,   13, 0x0a,
     113,   13,   13,   13, 0x0a,
     135,   13,   13,   13, 0x0a,
     157,   13,   13,   13, 0x0a,
     179,   13,   13,   13, 0x0a,
     201,   13,   13,   13, 0x0a,
     223,   13,   13,   13, 0x0a,
     245,   13,   13,   13, 0x0a,
     267,   13,   13,   13, 0x0a,
     289,   13,   13,   13, 0x0a,
     308,   13,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CKeyBoardDlg[] = {
    "CKeyBoardDlg\0\0okBtn_clicked()\0"
    "cancelBtn_clicked()\0clearBtn_clicked()\0"
    "pushButton0_clicked()\0pushButton1_clicked()\0"
    "pushButton2_clicked()\0pushButton3_clicked()\0"
    "pushButton4_clicked()\0pushButton5_clicked()\0"
    "pushButton6_clicked()\0pushButton7_clicked()\0"
    "pushButton8_clicked()\0pushButton9_clicked()\0"
    "pointBtn_clicked()\0nagBtn_clicked()\0"
};

void CKeyBoardDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CKeyBoardDlg *_t = static_cast<CKeyBoardDlg *>(_o);
        switch (_id) {
        case 0: _t->okBtn_clicked(); break;
        case 1: _t->cancelBtn_clicked(); break;
        case 2: _t->clearBtn_clicked(); break;
        case 3: _t->pushButton0_clicked(); break;
        case 4: _t->pushButton1_clicked(); break;
        case 5: _t->pushButton2_clicked(); break;
        case 6: _t->pushButton3_clicked(); break;
        case 7: _t->pushButton4_clicked(); break;
        case 8: _t->pushButton5_clicked(); break;
        case 9: _t->pushButton6_clicked(); break;
        case 10: _t->pushButton7_clicked(); break;
        case 11: _t->pushButton8_clicked(); break;
        case 12: _t->pushButton9_clicked(); break;
        case 13: _t->pointBtn_clicked(); break;
        case 14: _t->nagBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CKeyBoardDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CKeyBoardDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CKeyBoardDlg,
      qt_meta_data_CKeyBoardDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CKeyBoardDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CKeyBoardDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CKeyBoardDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CKeyBoardDlg))
        return static_cast<void*>(const_cast< CKeyBoardDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CKeyBoardDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
