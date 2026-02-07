#include <iostream>
#include <iterator>
#include <stdexcept>
using namespace std;

// контейнер
template <class T, class Allocator = allocator<T>> class MyContainer {
public:
    
    
    using value_type = T;

    // Тип аллокатора
    using allocator_type = Allocator;

    // ссылка на элементы контейнера
    using reference = value_type&;

    // константная ссылка на тип элементовконтейнера
    using const_reference = const value_type&;

    // размер контейнера
    using size_type = size_t;

    // разница между позициями итератора
    using difference_type = ptrdiff_t;

    // класс для контейнера пользователя
    class iterator {
    public:
        // Type definitions for the iterator

        // тег для итераторов с произвольным доступом
        using iterator_category = random_access_iterator_tag;

        // тип элементов принадляжащих итератору
        using value_type = T;

        // тип для определения разницы между итераторами
        using difference_type = ptrdiff_t;

        // тип указателя на элемент
        using pointer = T*;
        // ссылка на тип элемента
        using reference = T&;

        // в конструктор передается указатель на элемент
        iterator(pointer ptr) : ptr_(ptr) {
        }

        // возвращает ссылку для доступа к элементу
        reference operator*() const {
            return *ptr_;
        }

        //  доступ к элементу класса через указатель
        pointer operator->() const {
            return ptr_;
        }

        // увеличение префикса дляя доступа к следующему элементу
        iterator& operator++() {
            ++ptr_;
            return *this;
        }

        //перемещение к следующему элементу и возврат позиции
        iterator operator++(int) {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }

        // оператор для сравнения элементов
        bool operator==(const iterator& other) const {
            return ptr_ == other.ptr_;
        }

        // оператор для сравнения элементов
        bool operator!=(const iterator& other) const {
            return ptr_ != other.ptr_;
        }

    private:
        pointer ptr_; // указатель на текущий элемент
    };

    // пустой контейнер
    MyContainer() : data_(nullptr), size_(0), capacity_(0) {
    }
    // Добавляем конструктор с аллокатором
    explicit MyContainer(const Allocator& alloc) : capacity_(10), size_(0), data_(nullptr), allocator_(alloc) {
        data_ = allocator_.allocate(capacity_);
    }

    // конструктор для создания копии другого контейнера
    MyContainer(const MyContainer& other) : size_(other.size_), capacity_(other.capacity_) {

        // выделение памяти
        data_ = allocator_type().allocate(capacity_);
        // копирование в другой контейнер 
        copy(other.data_, other.data_ + size_, data_);
    }

    // уничтожение контейнера очистак памяти
    ~MyContainer() {
        
        allocator_type().deallocate(data_, capacity_);
    }

    // функция добавляет элемент в конец контейнера
    void push_back(const T& value) {
        if (size_ == capacity_) {

            // если памяти не хватает то выделим еще
            size_type new_capacity = capacity_ ? 2 * capacity_ : 1;
            T* new_data = allocator_type().allocate(new_capacity);
            copy(data_, data_ + size_, new_data);
            allocator_type().deallocate(data_, capacity_);
            data_ = new_data;
            capacity_ = new_capacity;
        }
        data_[size_++] = value;
    }

    // удаляет последний элемент в контейнере
    void pop_back() {
        // проверка пустой ли контейнер
        if (size_ > 0) {
            --size_;
        }
    }

    // проверка индекса и доступ к элементу
    reference at(size_type index) {
        if (index >= size_) {

            
            throw out_of_range("Index out of range");
        }
        return data_[index];
    }

    // читает элементы не меняя
    const_reference at(size_type index) const {
        if (index >= size_) {

            // проверка границ индекса
            throw out_of_range("Index out of range");
        }
        return data_[index];
    }

    // возврат количества элементов в контейнере
    size_type size() const {
        return size_;
    }

    // Проверка пустой контейнер
    bool empty() const {
        return size_ == 0;
    }

    // функция для получения первой позиции контейнера
    iterator begin() {
        return iterator(data_);
    }

    // функция для получения последней позиции контейнера
    iterator end() {
        return iterator(data_ + size_);
    }

private:
    // данные контейнера
    T* data_;

    // количество  элементов
    size_type size_;

    // определяет вместимость контейнера
    size_type capacity_;
    Allocator allocator_;
};