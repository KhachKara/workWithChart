#pragma once

#include <QAbstractTableModel>
#include <QPointF>

class OscilloscopeModel: public QAbstractTableModel {
    Q_OBJECT
    static const int TIMER_ADD_POINT = 5;
    static const QString ITEM_NAME;     // OscilloscopeModel
    static const bool IS_QML_REG;
public:
    OscilloscopeModel(QObject *parent = nullptr);

    Q_INVOKABLE void startGenerated();
    Q_INVOKABLE void continueGenerated();
    Q_INVOKABLE void stopGenerated();

    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
protected:
    void timerEvent(QTimerEvent *event) override;
    void addPoint();
private:
    int _timerId;
    QMap<double, double> _points;

};

