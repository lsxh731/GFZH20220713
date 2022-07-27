/****************************************************************************
** Meta object code from reading C++ file 'faultcondWidget.h'
**
** Created: Tue Jul 26 18:36:51 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "faultcondWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'faultcondWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CFaultConditionWidget[] = {

 // content:
       5,       // revision
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

const QMetaObject CFaultConditionWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CFaultConditionWidget,
      qt_meta_data_CFaultConditionWidget, 0 }
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
        switch (_id) {
        case 0: radioButton0102_clicked(); break;
        case 1: radioButton0304_clicked(); break;
        case 2: radioButton0506_clicked(); break;
        case 3: radioButton0708_clicked(); break;
        case 4: radioButton0910_clicked(); break;
        case 5: radioButton1112_clicked(); break;
        case 6: radioButton1314_clicked(); break;
        case 7: radioButton1516_clicked(); break;
        case 8: closeBtn_clicked(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
