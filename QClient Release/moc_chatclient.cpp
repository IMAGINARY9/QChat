/****************************************************************************
** Meta object code from reading C++ file 'chatclient.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QChatClient/chatclient.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSChatClientENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSChatClientENDCLASS = QtMocHelpers::stringData(
    "ChatClient",
    "connected",
    "",
    "loggedIn",
    "loginError",
    "reason",
    "disconnected",
    "messageReceived",
    "sender",
    "text",
    "error",
    "QAbstractSocket::SocketError",
    "socekError",
    "updateUsersList",
    "QList<std::pair<QString,int>>",
    "userNames",
    "connectToServer",
    "QHostAddress",
    "address",
    "qintptr",
    "port",
    "login",
    "userName",
    "chatSelected",
    "chatName",
    "sendMessage",
    "disconnectFromHost",
    "unreadMessages",
    "isClear",
    "onReadyRead"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSChatClientENDCLASS_t {
    uint offsetsAndSizes[60];
    char stringdata0[11];
    char stringdata1[10];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[11];
    char stringdata5[7];
    char stringdata6[13];
    char stringdata7[16];
    char stringdata8[7];
    char stringdata9[5];
    char stringdata10[6];
    char stringdata11[29];
    char stringdata12[11];
    char stringdata13[16];
    char stringdata14[30];
    char stringdata15[10];
    char stringdata16[16];
    char stringdata17[13];
    char stringdata18[8];
    char stringdata19[8];
    char stringdata20[5];
    char stringdata21[6];
    char stringdata22[9];
    char stringdata23[13];
    char stringdata24[9];
    char stringdata25[12];
    char stringdata26[19];
    char stringdata27[15];
    char stringdata28[8];
    char stringdata29[12];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSChatClientENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSChatClientENDCLASS_t qt_meta_stringdata_CLASSChatClientENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "ChatClient"
        QT_MOC_LITERAL(11, 9),  // "connected"
        QT_MOC_LITERAL(21, 0),  // ""
        QT_MOC_LITERAL(22, 8),  // "loggedIn"
        QT_MOC_LITERAL(31, 10),  // "loginError"
        QT_MOC_LITERAL(42, 6),  // "reason"
        QT_MOC_LITERAL(49, 12),  // "disconnected"
        QT_MOC_LITERAL(62, 15),  // "messageReceived"
        QT_MOC_LITERAL(78, 6),  // "sender"
        QT_MOC_LITERAL(85, 4),  // "text"
        QT_MOC_LITERAL(90, 5),  // "error"
        QT_MOC_LITERAL(96, 28),  // "QAbstractSocket::SocketError"
        QT_MOC_LITERAL(125, 10),  // "socekError"
        QT_MOC_LITERAL(136, 15),  // "updateUsersList"
        QT_MOC_LITERAL(152, 29),  // "QList<std::pair<QString,int>>"
        QT_MOC_LITERAL(182, 9),  // "userNames"
        QT_MOC_LITERAL(192, 15),  // "connectToServer"
        QT_MOC_LITERAL(208, 12),  // "QHostAddress"
        QT_MOC_LITERAL(221, 7),  // "address"
        QT_MOC_LITERAL(229, 7),  // "qintptr"
        QT_MOC_LITERAL(237, 4),  // "port"
        QT_MOC_LITERAL(242, 5),  // "login"
        QT_MOC_LITERAL(248, 8),  // "userName"
        QT_MOC_LITERAL(257, 12),  // "chatSelected"
        QT_MOC_LITERAL(270, 8),  // "chatName"
        QT_MOC_LITERAL(279, 11),  // "sendMessage"
        QT_MOC_LITERAL(291, 18),  // "disconnectFromHost"
        QT_MOC_LITERAL(310, 14),  // "unreadMessages"
        QT_MOC_LITERAL(325, 7),  // "isClear"
        QT_MOC_LITERAL(333, 11)   // "onReadyRead"
    },
    "ChatClient",
    "connected",
    "",
    "loggedIn",
    "loginError",
    "reason",
    "disconnected",
    "messageReceived",
    "sender",
    "text",
    "error",
    "QAbstractSocket::SocketError",
    "socekError",
    "updateUsersList",
    "QList<std::pair<QString,int>>",
    "userNames",
    "connectToServer",
    "QHostAddress",
    "address",
    "qintptr",
    "port",
    "login",
    "userName",
    "chatSelected",
    "chatName",
    "sendMessage",
    "disconnectFromHost",
    "unreadMessages",
    "isClear",
    "onReadyRead"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSChatClientENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x06,    1 /* Public */,
       3,    0,   99,    2, 0x06,    2 /* Public */,
       4,    1,  100,    2, 0x06,    3 /* Public */,
       6,    0,  103,    2, 0x06,    5 /* Public */,
       7,    2,  104,    2, 0x06,    6 /* Public */,
      10,    1,  109,    2, 0x06,    9 /* Public */,
      13,    1,  112,    2, 0x06,   11 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      16,    2,  115,    2, 0x0a,   13 /* Public */,
      21,    1,  120,    2, 0x0a,   16 /* Public */,
      23,    1,  123,    2, 0x0a,   18 /* Public */,
      25,    1,  126,    2, 0x0a,   20 /* Public */,
      26,    0,  129,    2, 0x0a,   22 /* Public */,
      27,    2,  130,    2, 0x0a,   23 /* Public */,
      29,    0,  135,    2, 0x08,   26 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 17, 0x80000000 | 19,   18,   20,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::QString, QMetaType::QString,   24,
    QMetaType::Bool, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    8,   28,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ChatClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSChatClientENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSChatClientENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSChatClientENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ChatClient, std::true_type>,
        // method 'connected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loggedIn'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loginError'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'disconnected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'messageReceived'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'error'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QAbstractSocket::SocketError, std::false_type>,
        // method 'updateUsersList'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<std::pair<QString,int>> &, std::false_type>,
        // method 'connectToServer'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QHostAddress &, std::false_type>,
        QtPrivate::TypeAndForceComplete<qintptr, std::false_type>,
        // method 'login'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'chatSelected'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'sendMessage'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'disconnectFromHost'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'unreadMessages'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'onReadyRead'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ChatClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->loggedIn(); break;
        case 2: _t->loginError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->disconnected(); break;
        case 4: _t->messageReceived((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->error((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 6: _t->updateUsersList((*reinterpret_cast< std::add_pointer_t<QList<std::pair<QString,int>>>>(_a[1]))); break;
        case 7: _t->connectToServer((*reinterpret_cast< std::add_pointer_t<QHostAddress>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qintptr>>(_a[2]))); break;
        case 8: _t->login((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: { QString _r = _t->chatSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 10: { bool _r = _t->sendMessage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 11: _t->disconnectFromHost(); break;
        case 12: _t->unreadMessages((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2]))); break;
        case 13: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatClient::*)();
            if (_t _q_method = &ChatClient::connected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)();
            if (_t _q_method = &ChatClient::loggedIn; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QString & );
            if (_t _q_method = &ChatClient::loginError; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)();
            if (_t _q_method = &ChatClient::disconnected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QString & , const QString & );
            if (_t _q_method = &ChatClient::messageReceived; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(QAbstractSocket::SocketError );
            if (_t _q_method = &ChatClient::error; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChatClient::*)(const QList<std::pair<QString,int>> & );
            if (_t _q_method = &ChatClient::updateUsersList; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject *ChatClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSChatClientENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ChatClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void ChatClient::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ChatClient::loggedIn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ChatClient::loginError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ChatClient::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ChatClient::messageReceived(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ChatClient::error(QAbstractSocket::SocketError _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ChatClient::updateUsersList(const QList<std::pair<QString,int>> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
