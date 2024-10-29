#include "tree-sum-2.h"

template<typename T>
void TreeSum<T>::Build(const size_t i, const size_t l, const size_t r) {
    if (l == r) {
        tree[i] = data[l];
        return;
    }
    const size_t mid = (l + r) / 2;
    Build(2 * i, l, mid);
    Build(2 * i + 1, mid + 1, r);
    tree[i] = tree[2 * i] + tree[2 * i + 1];
}

template<typename T>
void TreeSum<T>::Push(const size_t i, const size_t l, const size_t r) {
    if (add[i] == valueZeroType) {
        return;
    }
    tree[i] += add[i] * (r - l + 1);
    if (l != r) {
        add[2 * i] += add[i];
        add[2 * i + 1] += add[i];
    }
    add[i] = valueZeroType;
}

template<typename T>
void TreeSum<T>::Update(const size_t i, const size_t l, const size_t r, const size_t left, const size_t right, const T value) {
    Push(i, l, r);
    if (l > right || r < left) {
        return;
    }
    if (l == left && r == right) {
        add[i] += value;
        Push(i, l, r);
        return;
    }
    const size_t mid = (l + r) / 2;
    Update(2 * i, l, mid, left, std::min(right, mid), value);
    Update(2 * i + 1, mid + 1, r, std::max(left, mid + 1), right, value);
    tree[i] = tree[2 * i] + tree[2 * i + 1];
}


template<typename T>
void TreeSum<T>::Update(const size_t i, const size_t l, const size_t r, const size_t idx, const T value) {
    Push(i, l, r);
    if (l == r) {
        tree[i] = value;
        return;
    }
    const size_t mid = (l + r) / 2;
    if (idx <= mid) {
        Update(2 * i, l, mid, idx, value);
    } else {
        Update(2 * i + 1, mid + 1, r, idx, value);
    }
    tree[i] = tree[2 * i] + tree[2 * i + 1];
}

template<typename T>
T TreeSum<T>::GetValue(const size_t i, const size_t l, const size_t r, const size_t left, const size_t right) {
    Push(i, l, r);
    if (l > right || r < left) {
        return valueZeroType;
    }
    if (l == left && r == right) {
        return tree[i];
    }
    const size_t mid = (l + r) / 2;
    return GetValue(2 * i, l, mid, left, std::min(right, mid))
           + GetValue(2 * i + 1, mid + 1, r, std::max(left, mid + 1), right);
}