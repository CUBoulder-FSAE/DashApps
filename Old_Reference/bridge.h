#pragma once

#include <QObject>

// ─────────────────────────────────────────────────────────────────────────────
//  Bridge
//
//  C++ backing model for Dashboard.qml.
//
//  Register in main.cpp before loading the QML engine:
//
//      Bridge dashboard;
//      engine.rootContext()->setContextProperty("dashboard", &dashboard);
//
//  Push data from your backend (CAN, serial, timer, etc.):
//
//      dashboard.setSpeed(120.5);
//      dashboard.setRpm(4200.0);
//      dashboard.setTemp1(87.3);
//
// ─────────────────────────────────────────────────────────────────────────────
class Bridge : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal speed  READ speed  WRITE setSpeed  NOTIFY speedChanged  FINAL)
    Q_PROPERTY(qreal rpm    READ rpm    WRITE setRpm    NOTIFY rpmChanged    FINAL)
    Q_PROPERTY(qreal temp1  READ temp1  WRITE setTemp1  NOTIFY temp1Changed  FINAL)
    Q_PROPERTY(qreal temp2  READ temp2  WRITE setTemp2  NOTIFY temp2Changed  FINAL)
    Q_PROPERTY(qreal temp3  READ temp3  WRITE setTemp3  NOTIFY temp3Changed  FINAL)
    Q_PROPERTY(qreal temp4  READ temp4  WRITE setTemp4  NOTIFY temp4Changed  FINAL)

public:
    explicit Bridge(QObject *parent = nullptr);
    ~Bridge() override = default;

    // Getters
    [[nodiscard]] qreal speed() const noexcept { return m_speed; }
    [[nodiscard]] qreal rpm()   const noexcept { return m_rpm;   }
    [[nodiscard]] qreal temp1() const noexcept { return m_temp1; }
    [[nodiscard]] qreal temp2() const noexcept { return m_temp2; }
    [[nodiscard]] qreal temp3() const noexcept { return m_temp3; }
    [[nodiscard]] qreal temp4() const noexcept { return m_temp4; }

public slots:
    // Setters — safe to connect() directly to other signals
    void setSpeed(qreal value);
    void setRpm  (qreal value);
    void setTemp1(qreal value);
    void setTemp2(qreal value);
    void setTemp3(qreal value);
    void setTemp4(qreal value);

signals:
    // One signal per property — emitted only when value actually changes
    void speedChanged(qreal newSpeed);
    void rpmChanged  (qreal newRpm);
    void temp1Changed(qreal newTemp);
    void temp2Changed(qreal newTemp);
    void temp3Changed(qreal newTemp);
    void temp4Changed(qreal newTemp);

private:
    qreal m_speed { 0.0 };
    qreal m_rpm   { 0.0 };
    qreal m_temp1 { 0.0 };
    qreal m_temp2 { 0.0 };
    qreal m_temp3 { 0.0 };
    qreal m_temp4 { 0.0 };
};