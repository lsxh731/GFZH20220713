/****************************************************************************
** Meta object code from reading C++ file 'logindlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../logindlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logindlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CLogindlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      27,   10,   10,   10, 0x0a,
      46,   10,   10,   10, 0x0a,
      66,   10,   10,   10, 0x0a,
      88,   10,   10,   10, 0x0a,
     110,   10,   10,   10, 0x0a,
     132,   10,   10,   10, 0x0a,
     154,   10,   10,   10, 0x0a,
     176,   10,   10,   10, 0x0a,
     198,   10,   10,   10, 0x0a,
     220,   10,   10,   10, 0x0a,
     242,   10,   10,   10, 0x0a,
     264,   10,   10,   10, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CLogindlg[] = {
    "CLogindlg\0\0okBtn_clicked()\0"
    "clearBtn_clicked()\0cancelBtn_clicked()\0"
    "pushButton0_clicked()\0pushButton1_clicked()\0"
    "pushButton2_clicked()\0pushButton3_clicked()\0"
    "pushButton4_clicked()\0pushButton5_clicked()\0"
    "pushButton6_clicked()\0pushButton7_clicked()\0"
    "pushButton8_clicked()\0pushButton9_clicked()\0"
};

void CLogindlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CLogindlg *_t = static_cast<CLogindlg *>(_o);
        switch (_id) {
        case 0: _t->okBtn_clicked(); break;
        case 1: _t->clearBtn_clicked(); break;
        case 2: _t->cancelBtn_clicked(); break;
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
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CLogindlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CLogindlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CLogindlg,
      qt_meta_data_CLogindlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CLogindlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CLogindlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CLogindlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLogindlg))
        return static_cast<void*>(const_cast< CLogindlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CLogindlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
