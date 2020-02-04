#ifndef JNP1_7_PROJECT_FUNCTIONAL_H
#define JNP1_7_PROJECT_FUNCTIONAL_H

#include <functional>
#include <tuple>
#include <utility>

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

template <typename F = void>
auto compose() {
    return [](auto arg) {return arg;};
}

template <typename H, typename ... F>
auto lift(H &h, F& ... f) {
    auto fun = [=](auto arg) {
        return h(f(arg) ...);
    };
    return fun;
}



#endif //JNP1_7_PROJECT_FUNCTIONAL_H
