#pragma once

#include <QQmlEngine>

namespace My {

template<class C>
bool qmlRegisterUncreatableType(QString itemName) {
    qmlRegisterUncreatableType<C>(QString("cpp.%1").arg(itemName).toUtf8(),
                                  12, 34, itemName.toUtf8(),
                                  "Not creatable as it is an enum type");
    return true;
}


template<class C>
bool qmlRegisterType(QString itemName) {
    qmlRegisterType<C>(QString("cpp.%1").arg(itemName).toUtf8(),
                       12, 34, itemName.toUtf8());
    return true;
}

template <class It>
QHash<QString, int> arrayToHash(It begin, It end) {
    QHash<QString, int> r;
    for (int i = 0; begin != end; ++i, ++begin) {
        r[*begin] = i;
    }
    return r;
}

}   // namespace My
