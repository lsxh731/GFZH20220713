/****************************************************************************
** Meta object code from reading C++ file 'hiscurveWidget.h'
**
** Created: Thu Jul 7 23:41:53 2022
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "hiscurveWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hiscurveWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CHiscurveWidget[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      24,   17,   16,   16, 0x0a,
      46,   16,   16,   16, 0x0a,
      65,   16,   16,   16, 0x0a,
      83,   16,   16,   16, 0x0a,
     103,   16,   16,   16, 0x0a,
     123,   16,   16,   16, 0x0a,
     143,   16,   16,   16, 0x0a,
     163,   16,   16,   16, 0x0a,
     184,   16,   16,   16, 0x0a,
     205,   16,   16,   16, 0x0a,
     226,   16,   16,   16, 0x0a,
     246,   16,   16,   16, 0x0a,
     265,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_CHiscurveWidget[] = {
    "CHiscurveWidget\0\0nIndex\0comboBox_clicked(int)\0"
    "queryBtn_clicked()\0loadBtn_clicked()\0"
    "totalvolt_clicked()\0totalcurr_clicked()\0"
    "excitvolt_clicked()\0excitcurr_clicked()\0"
    "PhaseAVolt_clicked()\0PhaseBVolt_clicked()\0"
    "PhaseCVolt_clicked()\0AllChoose_clicked()\0"
    "closeBtn_clicked()\0recoverBtn_clicked()\0"
};

const QMetaObject CHiscurveWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CHiscurveWidget,
      qt_meta_data_CHiscurveWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CHiscurveWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CHiscurveWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CHiscurveWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CHiscurveWidget))
        return static_cast<void*>(const_cast< CHiscurveWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int CHiscurveWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: comboBox_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: queryBtn_clicked(); break;
        case 2: loadBtn_clicked(); break;
        case 3: totalvolt_clicked(); break;
        case 4: totalcurr_clicked(); break;
        case 5: excitvolt_clicked(); break;
        case 6: excitcurr_clicked(); break;
        case 7: PhaseAVolt_clicked(); break;
        case 8: PhaseBVolt_clicked(); break;
        case 9: PhaseCVolt_clicked(); break;
        case 10: AllChoose_clicked(); break;
        case 11: closeBtn_clicked(); break;
        case 12: recoverBtn_clicked(); break;
        default: ;
        }
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
