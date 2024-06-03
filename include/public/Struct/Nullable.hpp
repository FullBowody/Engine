#pragma once

class Nullable
{
private:
    bool null;

protected:
    Nullable(): null(false) {}
    Nullable(bool null): null(null) {}

public:
    bool isNull() const
    {
        return null;
    }
};

template <typename T>
class Null: public Nullable, public T
{
public:
    Null(): Nullable(true) {}
    Null(const T& value): Nullable(false), T(value) {}
    Null(const Null<T>& null): Nullable(null.isNull()), T(null) {}
    ~Null() {}
};
