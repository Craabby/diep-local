#pragma once

#include <cmath>

template <typename T>
class Vector
{
    T m_X;
    T m_Y;

public:
    Vector(T x, T y)
        : m_X(x), m_Y(y)
    {
    }

    // no template argument = clone
    // template argument = clone + cast
    template <typename _T = T>
    Vector<_T> Clone()
    {
        return Vector<_T>((_T)X(), (_T)Y());
    }

    void Add(Vector<T> vector)
    {
        X(vector.X() + X());
        X(vector.Y() + Y());
    }

    void Subtract(Vector<T> vector)
    {
        X(vector.X() - X());
        X(vector.Y() - Y());
    }

    void Scale(T x)
    {
        X(X() * x);
        Y(Y() * x);
    }

    T Distance()
    {
        return std::sqrt<T>(X() * X() + Y() * Y());
    }

    T X() const
    {
        return m_X;
    }
    T Y() const
    {
        return m_Y;
    }

    void X(T x)
    {
        m_X = x;
    }

    void Y(T y)
    {
        m_Y = y;
    }
};
