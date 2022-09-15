/****************************************************************************
** Meta object code from reading C++ file 'hiscurveWidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../ZDTXK-V4.7new20220217-ARM-v0.03-0722/hiscurveWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hiscurveWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CHiscurveWidget[] = {

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

void CHiscurveWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CHiscurveWidget *_t = static_cast<CHiscurveWidget *>(_o);
        switch (_id) {
        case 0: _t->comboBox_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->queryBtn_clicked(); break;
        case 2: _t->loadBtn_clicked(); break;
        case 3: _t->totalvolt_clicked(); break;
        case 4: _t->totalcurr_clicked(); break;
        case 5: _t->excitvolt_clicked(); break;
        case 6: _t->excitcurr_clicked(); break;
        case 7: _t->PhaseAVolt_clicked(); break;
        case 8: _t->PhaseBVolt_clicked(); break;
        case 9: _t->PhaseCVolt_clicked(); break;
        case 10: _t->AllChoose_clicked(); break;
        case 11: _t->closeBtn_clicked(); break;
        case 12: _t->recoverBtn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CHiscurveWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CHiscurveWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CHiscurveWidget,
      qt_meta_data_CHiscurveWidget, &staticMetaObjectExtraData }
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
