/****************************************************************************
** Meta object code from reading C++ file 'tempermonitorWidget.h'
**
** Created: Thu Jul 7 23:41:51 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "tempermonitorWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tempermonitorWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CTempMonitorWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   19,   19,   19, 0x0a,
      39,   19,   19,   19, 0x0a,
      57,   19,   19,   19, 0x0a,
      75,   19,   19,   19, 0x0a,
      93,   19,   19,   19, 0x0a,
     111,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CTempMonitorWidget[] = {
    "CTempMonitorWidget\0\0temperLangChange()\0"
    "sub1Btn_clicked()\0sub2Btn_clicked()\0"
    "sub3Btn_clicked()\0sub4Btn_clicked()\0"
    "closeBtn_clicked()\0"
};

const QMetaObject CTempMonitorWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CTempMonitorWidget,
      qt_meta_data_CTempMonitorWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CTempMonitorWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CTempMonitorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CTempMonitorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CTempMonitorWidget))
        return static_cast<void*>(const_cast< CTempMonitorWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int CTempMonitorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: temperLangChange(); break;
        case 1: sub1Btn_clicked(); break;
        case 2: sub2Btn_clicked(); break;
        case 3: sub3Btn_clicked(); break;
        case 4: sub4Btn_clicked(); break;
        case 5: closeBtn_clicked(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
