#ifndef JNP1_7_PROJECT_FUNCTIONAL_H
#define JNP1_7_PROJECT_FUNCTIONAL_H

#include <functional>
#include <tuple>
#include <utility>
/*
template <typename F1, typename ... F>
class Composer {

    F1 f1;
    Composer<F ...> tail;

public:
    explicit Composer(F1 f1, F ... f) : f1(f1), tail(f ...) {}

    template <typename T>
    auto operator() (const T& x) const {
        return tail(f1(x));
    }
};

template <typename F>
class Composer<F> {
    F f;

public:
    explicit Composer(F f) : f(f) {}

    template <typename T>
    auto operator() (const T& x) const {
        return f(x);
    }
};

template <typename ... F>
auto compose(F ... f) {
    return Composer<F ...>(f ...);
}
*/
template <typename Arg, typename F>
auto invoke(Arg arg, F f) {
    return f(arg);
}

template <typename Arg, typename F1, typename ... F>
auto invoke(Arg arg, F1 f1, F ... f) {
    return invoke(f1(arg), f ...);
}

template <typename F1, typename ... F>
auto compose(F1 f1, F ... f) {
    return [f1, f ...](auto arg){return invoke(f1(arg), f ...);};
}

template <typename F>
auto compose(F f) {
    return [f](auto arg){return invoke(f(arg));};
}

/*
template <>
auto compose() {
    return [](auto arg) {return arg;};
}
*/


template <typename Arg, typename F>
std::tuple<typename F::result_type> createArgs(Arg arg, F f1) {
    return std::make_tuple(f1(arg));
}

template <typename Arg, typename F1, typename ... Fs>
std::tuple<typename F1::result_type, typename Fs::result_type ...>
        createArgs(Arg arg, F1 f1, Fs ... fs) {
    std::tuple<typename Fs::result_type ...> prev = createArgs(arg, fs ...);
    auto prev_ext = std::tuple_cat(prev, std::make_tuple(f1(arg)));
    return prev_ext;
}

template <typename H, typename ... F>
auto lift(H &h, F& ... f) {
    auto fun = [&](auto arg) {
        std::tuple<typename F::result_type ...> args = createArgs(arg, f ...);
        return std::apply(h, args);
    };
    return fun;
}



#endif //JNP1_7_PROJECT_FUNCTIONAL_H
