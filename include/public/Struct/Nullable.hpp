#pragma once

class Nullable
{
private:
    bool null;

protected:
    Nullable(): null(false) {}
    Nullable(bool null): null(null) {}

    void setNull(bool null)
    {
        this->null = null;
    }

public:
    bool isNull() const
    {
        return null;
    }
};

template <typename T>
class Null: public T
{
public:
    Null() { setNull(true); }
    Null(const T& value): T(value) { setNull(true); }
    Null(const Null<T>& null): T(null) { setNull(null.isNull()); }
    ~Null() {}
};
