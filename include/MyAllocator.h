
//#include <memory>

template <typename T>
class MyAllocator:public std::allocator<T> {
public:
    using value_type = T;

    // Конструктор с параметром, если нужен
    explicit MyAllocator(size_t count = 10) : max_elements(count) {}

    template <typename U>
    MyAllocator(const MyAllocator<U>& other) noexcept : max_elements(other.max_elements) {}

    T* allocate(std::size_t n) {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) noexcept {
        ::operator delete(p);
    }

    // Необходимо для совместимости с контейнером
    template <typename U>
    struct rebind {
        using other = MyAllocator<U>;
    };

    bool operator==(const MyAllocator&) const { return true; }
    bool operator!=(const MyAllocator&) const { return false; }

    size_t max_elements; // количество элементов
};
