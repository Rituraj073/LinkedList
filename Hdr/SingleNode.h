#pragma once

template <class T>
struct SingleNode
{
    T val;
    SingleNode* next;

    SingleNode(const T& value = T{}, SingleNode* next = nullptr)
        : val(value), next(next) {
    }

    // Nodes should not be copied
    SingleNode(const SingleNode&) = delete;
    SingleNode& operator=(const SingleNode&) = delete;

    // Allow default move operations (optional)
    SingleNode(SingleNode&&) = default;
    SingleNode& operator=(SingleNode&&) = default;
};