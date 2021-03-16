#include "oscilloscopemodel.h"

#include <QTimerEvent>
#include <math.h>

#include "myfuncs.h"

/*!
 * \brief Возвращает число последовательности.
 *
 * Последовательность 1/2, 1/4, 3/4, 1/8, 3/8, 5/8, 7/8, 1/16, 3/16 и тд
 * \param numPoint - номер последовательности.
 * \return результат деления дроби.
 */
static double getXposition(int numPoint) {
    auto my2pow = [] (int n) {
        int r = 1;
        for (int i = 0; i < n; ++i) { r *= 2; }
        return r;
    };
    auto step = [] (int n) {
        return n == 0 ? 0 : int(log2((n - 1) / 2 + 1)) + 1;
    };
    auto znam = [my2pow, step] (int n) {
        return my2pow(step(n) + 1);
    };
    // общее количество дробей до этой ступеньки
    auto Sn = [my2pow] (int n) {
        return my2pow(n + 1) - 1;
    };
    auto chisl = [Sn, step] (int n) {
        return (n - Sn(step(n) - 1)) * 2 + 1;
    };
    if (numPoint < 2) {
        return numPoint;
    }
    return double(chisl(numPoint - 2)) / znam(numPoint - 2);
}

const QString OscilloscopeModel::ITEM_NAME = "OscilloscopeModel";
const bool OscilloscopeModel::IS_QML_REG = My::qmlRegisterType<OscilloscopeModel>(OscilloscopeModel::ITEM_NAME);

OscilloscopeModel::OscilloscopeModel(QObject *parent) : QAbstractTableModel(parent) { }

void OscilloscopeModel::addPoint() {
    auto x = getXposition(_points.size()) * 100;
    auto y = sin(x / 2) * cos(x) + 1;
    auto insertPos = std::distance(_points.begin(), _points.lowerBound(x)) - 1;
    beginInsertRows(QModelIndex(), insertPos, insertPos);
    _points.insert(x, y);
    endInsertRows();
}

void OscilloscopeModel::startGenerated() {
    beginResetModel();
    _points.clear();
    endResetModel();
    addPoint();
    if (_timerId) { killTimer(_timerId); }
    _timerId = startTimer(TIMER_ADD_POINT);
}

void OscilloscopeModel::continueGenerated() {
    Q_ASSERT(_timerId == 0);
    addPoint();
    _timerId = startTimer(TIMER_ADD_POINT);
}

void OscilloscopeModel::stopGenerated() {
    killTimer(_timerId);
    _timerId = 0;
}

int OscilloscopeModel::rowCount(const QModelIndex &parent) const {
    return _points.size();
}

int OscilloscopeModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant OscilloscopeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()
            || index.row() >= rowCount()
            || index.column() >= columnCount()) {
        return QVariant();
    }
    auto r = index.row();
    auto c = index.column();
    switch (role) {
    case Qt::DisplayRole:
        return c == 0 ? (_points.cbegin() + r).key()
                      : (_points.cbegin() + r).value();
    default:
        return QVariant();
    }
}

void OscilloscopeModel::timerEvent(QTimerEvent *event) {
    if (event->timerId() == _timerId) {
        addPoint();
        return;
    }
    Q_ASSERT(false);
}
