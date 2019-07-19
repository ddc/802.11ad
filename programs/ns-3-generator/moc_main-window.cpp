/****************************************************************************
** Meta object code from reading C++ file 'main-window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "gui/main-window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'main-window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      23,   11,   11,   11, 0x08,
      39,   11,   11,   11, 0x08,
      51,   11,   11,   11, 0x08,
      63,   11,   11,   11, 0x08,
      74,   11,   11,   11, 0x08,
      90,   11,   11,   11, 0x08,
     102,   11,   11,   11, 0x08,
     117,   11,   11,   11, 0x08,
     132,   11,   11,   11, 0x08,
     150,   11,   11,   11, 0x08,
     167,   11,   11,   11, 0x08,
     183,   11,   11,   11, 0x08,
     203,   11,   11,   11, 0x08,
     217,   11,   11,   11, 0x08,
     234,   11,   11,   11, 0x08,
     249,   11,   11,   11, 0x08,
     257,   11,   11,   11, 0x08,
     271,   11,   11,   11, 0x08,
     281,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0CreatePc()\0CreatePcGroup()\0"
    "CreateEmu()\0CreateTap()\0CreateAp()\0"
    "CreateStation()\0CreateHub()\0CreateSwitch()\0"
    "CreateRouter()\0CreateWiredLink()\0"
    "CreateWifiLink()\0CreateP2pLink()\0"
    "CreateApplication()\0GenerateCpp()\0"
    "GeneratePython()\0DeleteObject()\0About()\0"
    "SavePicture()\0SaveXml()\0LoadXml()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->CreatePc(); break;
        case 1: _t->CreatePcGroup(); break;
        case 2: _t->CreateEmu(); break;
        case 3: _t->CreateTap(); break;
        case 4: _t->CreateAp(); break;
        case 5: _t->CreateStation(); break;
        case 6: _t->CreateHub(); break;
        case 7: _t->CreateSwitch(); break;
        case 8: _t->CreateRouter(); break;
        case 9: _t->CreateWiredLink(); break;
        case 10: _t->CreateWifiLink(); break;
        case 11: _t->CreateP2pLink(); break;
        case 12: _t->CreateApplication(); break;
        case 13: _t->GenerateCpp(); break;
        case 14: _t->GeneratePython(); break;
        case 15: _t->DeleteObject(); break;
        case 16: _t->About(); break;
        case 17: _t->SavePicture(); break;
        case 18: _t->SaveXml(); break;
        case 19: _t->LoadXml(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
