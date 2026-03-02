#pragma once

#include <initializer_list>
#include <ostream>

template <typename T>
struct TListNode
{
    T val;
    TListNode* next;

    TListNode() : val(), next(nullptr) {}
    TListNode(const T& x) : val(x), next(nullptr) {}
    TListNode(const T& x, TListNode* next) : val(x), next(next) {}
};

template <typename T>
class LinkedList
{
public:
    LinkedList() : m_head(nullptr) {}

    LinkedList(std::initializer_list<T> list) : m_head(nullptr)
    {
        TListNode<T>* tail = nullptr;

        for (const auto& value : list)
        {
            auto* node = new TListNode<T>(value);

            if (!m_head)
            {
                m_head = node;
                tail = node;
            }
            else
            {
                tail->next = node;
                tail = node;
            }
        }
    }

    LinkedList(TListNode<T>* head) : m_head(head) {}

    LinkedList(const LinkedList& other) : m_head(nullptr)
    {
        TListNode<T>* current = other.m_head;
        TListNode<T>* tail = nullptr;

        while (current)
        {
            auto* node = new TListNode<T>(current->val);

            if (!m_head)
            {
                m_head = node;
                tail = node;
            }
            else
            {
                tail->next = node;
                tail = node;
            }

            current = current->next;
        }
    }

    LinkedList& operator=(const LinkedList& other)
    {
        if (this == &other)
            return *this;

        clear();

        m_head = nullptr;

        TListNode<T>* current = other.m_head;
        TListNode<T>* tail = nullptr;

        while (current)
        {
            auto* node = new TListNode<T>(current->val);

            if (!m_head)
            {
                m_head = node;
                tail = node;
            }
            else
            {
                tail->next = node;
                tail = node;
            }

            current = current->next;
        }

        return *this;
    }

    LinkedList(LinkedList&& other) noexcept : m_head(other.m_head) { other.m_head = nullptr; }

    LinkedList& operator=(LinkedList&& other) noexcept
    {
        if (this == &other)
            return *this;

        clear();

        m_head = other.m_head;

        other.m_head = nullptr;

        return *this;
    }

    ~LinkedList() { clear(); }

    TListNode<T>* data() const { return m_head; }

    TListNode<T>* release()
    {
        TListNode<T>* tmp = m_head;
        m_head = nullptr;
        return tmp;
    }

    bool operator==(const LinkedList& other) const
    {
        TListNode<T>* lhs = m_head;
        TListNode<T>* rhs = other.m_head;

        while (lhs && rhs)
        {
            if (lhs->val != rhs->val)
                return false;

            lhs = lhs->next;
            rhs = rhs->next;
        }

        return lhs == nullptr && rhs == nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList& list)
    {
        os << "[";
        TListNode<T>* current = list.m_head;

        while (current)
        {
            os << current->val;
            current = current->next;
            if (current)
                os << " -> ";
        }

        os << "]";
        return os;
    }

private:
    void clear()
    {
        while (m_head)
        {
            TListNode<T>* temp = m_head;
            m_head = m_head->next;
            delete temp;
        }
    }

private:
    TListNode<T>* m_head;
};
