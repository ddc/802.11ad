/****************************************************************************
** Meta object code from reading C++ file 'application-pages.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/application-pages.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'application-pages.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PingPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,
      19,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PingPage[] = {
    "PingPage\0\0Choose()\0Add()\0"
};

void PingPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PingPage *_t = static_cast<PingPage *>(_o);
        switch (_id) {
        case 0: _t->Choose(); break;
        case 1: _t->Add(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData PingPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PingPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PingPage,
      qt_meta_data_PingPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PingPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PingPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PingPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PingPage))
        return static_cast<void*>(const_cast< PingPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int PingPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_UdpEchoPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      22,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_UdpEchoPage[] = {
    "UdpEchoPage\0\0Choose()\0Add()\0"
};

void UdpEchoPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        UdpEchoPage *_t = static_cast<UdpEchoPage *>(_o);
        switch (_id) {
        case 0: _t->Choose(); break;
        case 1: _t->Add(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData UdpEchoPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject UdpEchoPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_UdpEchoPage,
      qt_meta_data_UdpEchoPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &UdpEchoPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *UdpEchoPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *UdpEchoPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_UdpEchoPage))
        return static_cast<void*>(const_cast< UdpEchoPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int UdpEchoPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_TcpPage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      18,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TcpPage[] = {
    "TcpPage\0\0Choose()\0Add()\0"
};

void TcpPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TcpPage *_t = static_cast<TcpPage *>(_o);
        switch (_id) {
        case 0: _t->Choose(); break;
        case 1: _t->Add(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TcpPage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TcpPage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TcpPage,
      qt_meta_data_TcpPage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TcpPage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TcpPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TcpPage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpPage))
        return static_cast<void*>(const_cast< TcpPage*>(this));
    return QWidget::qt_metacast(_clname);
}

int TcpPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
