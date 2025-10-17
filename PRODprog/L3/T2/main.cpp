#include <catch2/catch_test_macros.hpp>
#include <cstdint>

#include <iostream>

struct ListNode
{
public:
    ListNode(int value, ListNode* prev = nullptr, ListNode* next = nullptr)
        : value(value), prev(prev), next(next)
    {
        if (prev != nullptr) prev->next = this;
        if (next != nullptr) next->prev = this;
    }

public:
    int value;
    ListNode* prev;
    ListNode* next;
};


class List
{
public:
    List()
        : m_head(new ListNode(static_cast<int>(0))), m_size(0),
        m_tail(new ListNode(0, m_head))
    {       
    }

    virtual ~List()
    {
        Clear();
        delete m_head;
        delete m_tail;
    }

    bool Empty() { return m_size == 0; }

    unsigned long Size() { return m_size; }

    void PushFront(int value)
    {
        new ListNode(value, m_head, m_head->next);
        ++m_size;
    }

    void PushBack(int value)
    {
        new ListNode(value, m_tail->prev, m_tail);
        ++m_size;
    }

    int PopFront()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_head->next->next);
        int ret = node->value;
        delete node;
        return ret;
    }

    int PopBack()
    {
        if (Empty()) throw std::runtime_error("list is empty");
        auto node = extractPrev(m_tail);
        int ret = node->value;
        delete node;
        return ret;
    }

    void Clear()
    {
        auto current = m_head->next;
        while (current != m_tail)
        {
            current = current->next;
            delete extractPrev(current);
        }
    }

private:
    ListNode* extractPrev(ListNode* node)
    {
        auto target = node->prev;
        target->prev->next = target->next;
        target->next->prev = target->prev;
        --m_size;
        return target;
    }

private:
    ListNode* m_head;
    ListNode* m_tail;
    unsigned long m_size;
};

TEST_CASE("PushBack functionality tests") {
    List list;
    
    SECTION("PushBack adds elements to the back") {
        list.PushBack(1);
        list.PushBack(2);
        list.PushBack(3);
        
        REQUIRE(list.Size() == 3);
        REQUIRE(list.PopBack() == 3);
        REQUIRE(list.PopBack() == 2);
        REQUIRE(list.PopBack() == 1);
    }
    
    SECTION("PushBack increases size correctly") {
        REQUIRE(list.Size() == 0);
        list.PushBack(10);
        REQUIRE(list.Size() == 1);
        list.PushBack(20);
        REQUIRE(list.Size() == 2);
    }
}

TEST_CASE("PushFront functionality tests") {
    List list;
    
    SECTION("PushFront adds elements to the front") {
        list.PushFront(1);
        list.PushFront(2);
        list.PushFront(3);
        
        REQUIRE(list.Size() == 3);
        REQUIRE(list.PopFront() == 3);
        REQUIRE(list.PopFront() == 2);
        REQUIRE(list.PopFront() == 1);
    }
    
    SECTION("PushFront increases size correctly") {
        REQUIRE(list.Size() == 0);
        list.PushFront(10);
        REQUIRE(list.Size() == 1);
        list.PushFront(20);
        REQUIRE(list.Size() == 2);
    }
}

TEST_CASE("PopBack functionality tests") {
    List list;
    
    SECTION("PopBack throws exception on empty list") {
        REQUIRE(list.Empty() == true);
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
    }
}

TEST_CASE("PopFront functionality tests") {
    List list;
    
    SECTION("PopFront throws exception on empty list") {
        REQUIRE(list.Empty() == true);
        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
    }
}

TEST_CASE("Complex scenario: mixed operations") {
    List list;
    
    SECTION("Complex sequence of operations") {
        // Начальное состояние
        REQUIRE(list.Empty() == true);
        REQUIRE(list.Size() == 0);
        
        // Добавляем элементы в разные концы
        list.PushBack(100);   // [100]
        list.PushFront(50);   // [50, 100]
        list.PushBack(200);   // [50, 100, 200]
        list.PushFront(25);   // [25, 50, 100, 200]
        
        REQUIRE(list.Size() == 4);
        REQUIRE(list.Empty() == false);
        
        // Удаляем с обоих концов
        REQUIRE(list.PopFront() == 25);  // [50, 100, 200]
        REQUIRE(list.PopBack() == 200);  // [50, 100]
        
        REQUIRE(list.Size() == 2);

        REQUIRE(list.PopFront() == 50); // [100]
        REQUIRE(list.PopBack() == 100); // []

        REQUIRE(list.Size() == 0);
        REQUIRE(list.Empty() == true);
        
        // Проверяем, что исключения работают на пустом списке
        REQUIRE_THROWS_AS(list.PopBack(), std::runtime_error);
        REQUIRE_THROWS_AS(list.PopFront(), std::runtime_error);
        
        // Проверяем, что можно снова добавлять
        list.PushBack(999);
        REQUIRE(list.Size() == 1);
        REQUIRE(list.PopBack() == 999);
    }
}