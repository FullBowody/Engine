#pragma once

class Nullable
{
private:
    bool null;

protected:
    Nullable(): null(false) {}
    Nullable(bool null): null(null) {}
    Nullable(const Nullable& nullable): null(nullable.null) {}
    ~Nullable() {}

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
    Null(): T() { this->setNull(true); }
    Null(const T& value): T(value) { this->setNull(true); }
    Null(const Null<T>& null): T(null) { this->setNull(true); }
    ~Null() {}
};
