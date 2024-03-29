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

    Vector<T> *Add(Vector<T> vector)
    {
        X(vector.X() + X());
        Y(vector.Y() + Y());

        return this;
    }

    Vector<T> *Subtract(Vector<T> vector)
    {
        X(vector.X() - X());
        Y(vector.Y() - Y());

        return this;
    }

    Vector<T> *Scale(T x)
    {
        X(X() * x);
        Y(Y() * x);

        return this;
    }

    T Distance()
    {
        return std::sqrt(X() * X() + Y() * Y());
    }

    Vector<T> *Distance(T x)
    {
        T distance = Distance();
        if (distance == 0)
            distance = 1;
        X(X() / distance);
        Y(Y() / distance);

        return this;
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
