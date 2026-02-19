/****************************************************************************
** Meta object code from reading C++ file 'CellViewer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.13)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../src/CellViewer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CellViewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.13. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Netlist__CellViewer_t {
    QByteArrayData data[8];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Netlist__CellViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Netlist__CellViewer_t qt_meta_stringdata_Netlist__CellViewer = {
    {
QT_MOC_LITERAL(0, 0, 19), // "Netlist::CellViewer"
QT_MOC_LITERAL(1, 20, 7), // "setCell"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "Cell*"
QT_MOC_LITERAL(4, 35, 8), // "saveCell"
QT_MOC_LITERAL(5, 44, 8), // "openCell"
QT_MOC_LITERAL(6, 53, 12), // "showCellsLib"
QT_MOC_LITERAL(7, 66, 19) // "showInstancesWidget"

    },
    "Netlist::CellViewer\0setCell\0\0Cell*\0"
    "saveCell\0openCell\0showCellsLib\0"
    "showInstancesWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Netlist__CellViewer[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       4,    0,   42,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,
       6,    0,   44,    2, 0x0a /* Public */,
       7,    0,   45,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Netlist::CellViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CellViewer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setCell((*reinterpret_cast< Cell*(*)>(_a[1]))); break;
        case 1: _t->saveCell(); break;
        case 2: _t->openCell(); break;
        case 3: _t->showCellsLib(); break;
        case 4: _t->showInstancesWidget(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Netlist::CellViewer::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_Netlist__CellViewer.data,
    qt_meta_data_Netlist__CellViewer,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Netlist::CellViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Netlist::CellViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Netlist__CellViewer.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Netlist::CellViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
