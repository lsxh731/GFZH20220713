/****************************************************************************
** Meta object code from reading C++ file 'syssetdlg.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ZDTXK-V4.7new20220217-ARM-v0.03-0722/syssetdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'syssetdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CSyssetdlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      32,   11,   11,   11, 0x0a,
      48,   11,   11,   11, 0x0a,
      72,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CSyssetdlg[] = {
    "CSyssetdlg\0\0updateSystimeEdit()\0"
    "okBtn_clicked()\0sysTimesetBtn_clicked()\0"
    "restorefactoryBtn_clicked()\0"
};

void CSyssetdlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CSyssetdlg *_t = static_cast<CSyssetdlg *>(_o);
        switch (_id) {
        case 0: _t->updateSystimeEdit(); break;
        case 1: _t->okBtn_clicked(); break;
        case 2: _t->sysTimesetBtn_clicked(); break;
        case 3: _t->restorefactoryBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CSyssetdlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CSyssetdlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CSyssetdlg,
      qt_meta_data_CSyssetdlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CSyssetdlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CSyssetdlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CSyssetdlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CSyssetdlg))
        return static_cast<void*>(const_cast< CSyssetdlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CSyssetdlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
