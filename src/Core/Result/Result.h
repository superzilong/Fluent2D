#pragma once

#include <QString>

class Result
{
public:
    Result() = default;
    Result(const QString& err) { m_msg = err; }

    ~Result() = default;

    Result(const Result& other)                = default;
    Result(Result&& other) noexcept            = default;
    Result& operator=(const Result& other)     = default;
    Result& operator=(Result&& other) noexcept = default;

    operator bool() const { return m_msg.isEmpty(); }
    bool     succeed() const { return m_msg.isEmpty(); }
    QString  error() { return m_msg; }

private:
    QString m_msg;
};