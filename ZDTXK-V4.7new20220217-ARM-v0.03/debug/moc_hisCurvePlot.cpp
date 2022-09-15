/****************************************************************************
** Meta object code from reading C++ file 'hisCurvePlot.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hisCurvePlot.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hisCurvePlot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WamsPlot[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   10,    9,    9, 0x05,
      71,   62,    9,    9, 0x05,
     127,  106,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     161,  155,    9,    9, 0x0a,
     182,   10,    9,    9, 0x0a,
     221,  216,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_WamsPlot[] = {
    "WamsPlot\0\0Xp,Yp,w,x\0"
    "sendZoomInfo(double,double,double,double)\0"
    "iChartNo\0SendMouseDoubleClickedMessage(int)\0"
    "curveInfo,curveCount\0SendCurveInfo(SMaxMin*,int)\0"
    "iXPos\0setVerticalMark(int)\0"
    "zoom(double,double,double,double)\0"
    "rect\0sendZoomInfo(QwtDoubleRange)\0"
};

void WamsPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        WamsPlot *_t = static_cast<WamsPlot *>(_o);
        switch (_id) {
        case 0: _t->sendZoomInfo((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 1: _t->SendMouseDoubleClickedMessage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SendCurveInfo((*reinterpret_cast< SMaxMin*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setVerticalMark((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->zoom((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< double(*)>(_a[4]))); break;
        case 5: _t->sendZoomInfo((*reinterpret_cast< const QwtDoubleRange(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData WamsPlot::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject WamsPlot::staticMetaObject = {
    { &QwtPlot::staticMetaObject, qt_meta_stringdata_WamsPlot,
      qt_meta_data_WamsPlot, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WamsPlot::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WamsPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WamsPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WamsPlot))
        return static_cast<void*>(const_cast< WamsPlot*>(this));
    return QwtPlot::qt_metacast(_clname);
}

int WamsPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QwtPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WamsPlot::sendZoomInfo(double _t1, double _t2, double _t3, double _t4)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WamsPlot::SendMouseDoubleClickedMessage(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WamsPlot::SendCurveInfo(SMaxMin * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
