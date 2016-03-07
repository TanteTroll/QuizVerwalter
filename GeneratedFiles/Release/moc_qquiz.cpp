/****************************************************************************
** Meta object code from reading C++ file 'qquiz.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qquiz.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qquiz.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QQuiz_t {
    QByteArrayData data[7];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QQuiz_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QQuiz_t qt_meta_stringdata_QQuiz = {
    {
QT_MOC_LITERAL(0, 0, 5), // "QQuiz"
QT_MOC_LITERAL(1, 6, 10), // "nameChange"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 3), // "str"
QT_MOC_LITERAL(4, 22, 7), // "setName"
QT_MOC_LITERAL(5, 30, 6), // "setKat"
QT_MOC_LITERAL(6, 37, 7) // "setQues"

    },
    "QQuiz\0nameChange\0\0str\0setName\0setKat\0"
    "setQues"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QQuiz[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x0a /* Public */,
       5,    1,   40,    2, 0x0a /* Public */,
       6,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void QQuiz::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QQuiz *_t = static_cast<QQuiz *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nameChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->setName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->setKat((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->setQues((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QQuiz::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QQuiz::nameChange)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject QQuiz::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QQuiz.data,
      qt_meta_data_QQuiz,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QQuiz::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QQuiz::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QQuiz.stringdata0))
        return static_cast<void*>(const_cast< QQuiz*>(this));
    return QObject::qt_metacast(_clname);
}

int QQuiz::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void QQuiz::nameChange(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_QQuizs_t {
    QByteArrayData data[4];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QQuizs_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QQuizs_t qt_meta_stringdata_QQuizs = {
    {
QT_MOC_LITERAL(0, 0, 6), // "QQuizs"
QT_MOC_LITERAL(1, 7, 8), // "editQuiz"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 9) // "saveToXml"

    },
    "QQuizs\0editQuiz\0\0saveToXml"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QQuizs[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QQuizs::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QQuizs *_t = static_cast<QQuizs *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->editQuiz(); break;
        case 1: _t->saveToXml(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject QQuizs::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QQuizs.data,
      qt_meta_data_QQuizs,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QQuizs::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QQuizs::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QQuizs.stringdata0))
        return static_cast<void*>(const_cast< QQuizs*>(this));
    return QObject::qt_metacast(_clname);
}

int QQuizs::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
