#include "bridge.h"

Bridge::Bridge(QObject *parent)
    : QObject{parent}
    , m_speed { 0.0 }
    , m_rpm   { 0.0 }
    , m_temp1 { 0.0 }
    , m_temp2 { 0.0 }
    , m_temp3 { 0.0 }
    , m_temp4 { 0.0 }
{}

// ── Setters ───────────────────────────────────────────────────────────────────
//  qFuzzyCompare guards against floating-point noise so the signal — and any
//  QML binding that depends on it — only fires when the value truly changes.

void Bridge::setSpeed(qreal value)
{
    if (qFuzzyCompare(m_speed, value)) return;
    m_speed = value;
    emit speedChanged(m_speed);
}

void Bridge::setRpm(qreal value)
{
    if (qFuzzyCompare(m_rpm, value)) return;
    m_rpm = value;
    emit rpmChanged(m_rpm);
}

void Bridge::setTemp1(qreal value)
{
    if (qFuzzyCompare(m_temp1, value)) return;
    m_temp1 = value;
    emit temp1Changed(m_temp1);
}

void Bridge::setTemp2(qreal value)
{
    if (qFuzzyCompare(m_temp2, value)) return;
    m_temp2 = value;
    emit temp2Changed(m_temp2);
}

void Bridge::setTemp3(qreal value)
{
    if (qFuzzyCompare(m_temp3, value)) return;
    m_temp3 = value;
    emit temp3Changed(m_temp3);
}

void Bridge::setTemp4(qreal value)
{
    if (qFuzzyCompare(m_temp4, value)) return;
    m_temp4 = value;
    emit temp4Changed(m_temp4);
}