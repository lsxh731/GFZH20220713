/****************************************************************************
** Meta object code from reading C++ file 'faultcondWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ZDTXK-V4.7new20220217-ARM-v0.03-0722/faultcondWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'faultcondWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CFaultConditionWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   22,   22,   22, 0x0a,
      49,   22,   22,   22, 0x0a,
      75,   22,   22,   22, 0x0a,
     101,   22,   22,   22, 0x0a,
     127,   22,   22,   22, 0x0a,
     153,   22,   22,   22, 0x0a,
     179,   22,   22,   22, 0x0a,
     205,   22,   22,   22, 0x0a,
     231,   22,   22,   22, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CFaultConditionWidget[] = {
    "CFaultConditionWidget\0\0radioButton0102_clicked()\0"
    "radioButton0304_clicked()\0"
    "radioButton0506_clicked()\0"
    "radioButton0708_clicked()\0"
    "radioButton0910_clicked()\0"
    "radioButton1112_clicked()\0"
    "radioButton1314_clicked()\0"
    "radioButton1516_clicked()\0closeBtn_clicked()\0"
};

void CFaultConditionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CFaultConditionWidget *_t = static_cast<CFaultConditionWidget *>(_o);
        switch (_id) {
        case 0: _t->radioButton0102_clicked(); break;
        case 1: _t->radioButton0304_clicked(); break;
        case 2: _t->radioButton0506_clicked(); break;
        case 3: _t->radioButton0708_clicked(); break;
        case 4: _t->radioButton0910_clicked(); break;
        case 5: _t->radioButton1112_clicked(); break;
        case 6: _t->radioButton1314_clicked(); break;
        case 7: _t->radioButton1516_clicked(); break;
        case 8: _t->closeBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData CFaultConditionWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CFaultConditionWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CFaultConditionWidget,
      qt_meta_data_CFaultConditionWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CFaultConditionWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CFaultConditionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CFaultConditionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CFaultConditionWidget))
        return static_cast<void*>(const_cast< CFaultConditionWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int CFaultConditionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
