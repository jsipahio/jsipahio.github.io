#include <concepts>
#include <vector>

template <typename T>
concept HasSize = requires(T t) {
    {t.size()} -> std::same_as<size_t>;
};

template <HasSize T>
size_t getSize(T object) {
    return object.size();
}

template <typename T, typename U, typename R>
concept DivisionReturnsR = requires (T t, U u) {
    {t / u} -> std::same_as<R>;
};

template <typename T, typename U, typename R>
requires DivisionReturnsR<T, U, R>
R divide(T x, U y) {
    return x / y; 
}

template <typename T>
requires requires(T x, T y) {
    x + y;
}
T add(T x, T y) {
    return x + y;
}

int main() {
    // legal
    double x = divide<double, double, double>(1, 2);
    // legal
    int y = divide<int, int, int>(1, 2);
    // legal
    double z = divide<int, double, double>(1, 2);
    // not legal
    double a = divide<int, int, double>(1, 2); 

    std::vector<int> v1, v2;

    // if you are using an editor with error detection,
    // it should be showing red squiggles under add
    // see what happens if the requires clause is removed from add
    std::vector v3 = add<std::vector<int>>(v1, v2);

    return 0;
}
