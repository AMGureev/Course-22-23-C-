#pragma once

class Any {
private:
public:
    Any();

    template <class T>
    explicit Any(const T& value);

    template <class T>
    Any& operator=(const T& value);

    Any(const Any& rhs);
    Any& operator=(Any rhs);
    ~Any();

    bool Empty() const;

    void Clear();
    void Swap(Any& rhs);

    template <class T>
    const T& GetValue() const;
};