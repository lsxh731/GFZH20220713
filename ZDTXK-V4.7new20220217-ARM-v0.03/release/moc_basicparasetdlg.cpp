/****************************************************************************
** Meta object code from reading C++ file 'basicparasetdlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ZDTXK-V4.7new20220217-ARM-v0.03-0722/basicparasetdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basicparasetdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CBasicParaSetdlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      34,   17,   17,   17, 0x0a,
      54,   17,   17,   17, 0x0a,
      83,   17,   17,   17, 0x0a,
     112,   17,   17,   17, 0x0a,
     141,   17,   17,   17, 0x0a,
     170,   17,   17,   17, 0x0a,
     199,   17,   17,   17, 0x0a,
     231,   17,   17,   17, 0x0a,
     254,   17,   17,   17, 0x0a,
     277,   17,   17,   17, 0x0a,
     300,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CBasicParaSetdlg[] = {
    "CBasicParaSetdlg\0\0okBtn_clicked()\0"
    "cancelBtn_clicked()\0Sub1CurrentUplEdit_clicked()\0"
    "Sub2CurrentUplEdit_clicked()\0"
    "Sub3CurrentUplEdit_clicked()\0"
    "Sub4CurrentUplEdit_clicked()\0"
    "GfTotalVoltUplEdit_clicked()\0"
    "GfTotalCurrentUplEdit_clicked()\0"
    "checkBoxSub1_clicked()\0checkBoxSub2_clicked()\0"
    "checkBoxSub3_clicked()\0checkBoxSub4_clicked()\0"
};

void CBasicParaSetdlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CBasicParaSetdlg *_t = static_cast<CBasicParaSetdlg *>(_o);
        switch (_id) {
        case 0: _t->okBtn_clicked(); break;
        case 1: _t->cancelBtn_clicked(); break;
        case 2: _t->Sub1CurrentUplEdit_clicked(); break;
        case 3: _t->Sub2CurrentUplEdit_clicked(); break;
        case 4: _t->Sub3CurrentUplEdit_clicked(); break;
        case 5: _t->Sub4CurrentUplEdit_clicked(); break;
        case 6: _t->GfTotalVoltUplEdit_clicked(); break;
        case 7: _t->GfTotalCurrentUplEdit_clicked(); break;
        case 8: _t->checkBoxSub1_clicked(); break;
        case 9: _t->checkBoxSub2_clicked(); break;
        case 10: _t->checkBoxSub3_clicked(); break;
        case 11: _t->checkBoxSub4_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CBasicParaSetdlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CBasicParaSetdlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CBasicParaSetdlg,
      qt_meta_data_CBasicParaSetdlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CBasicParaSetdlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CBasicParaSetdlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CBasicParaSetdlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CBasicParaSetdlg))
        return static_cast<void*>(const_cast< CBasicParaSetdlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CBasicParaSetdlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
