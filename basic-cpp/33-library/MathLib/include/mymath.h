#ifndef MYMATH_H
#define MYMATH_H

// #ifdef MYMATH_EXPORTS
// #define MYMATH_API __declspec(dllexport)
// #else
// #define MYMATH_API __declspec(dllimport)
// #endif

#if defined(_WIN32) || defined(__CYGWIN__)
    #ifdef MYMATH_EXPORTS
        #define MYMATH_API __declspec(dllexport)
    #else
        #define MYMATH_API __declspec(dllimport)
    #endif
#else
    // 在 Linux/macOS 等类 Unix 系统下，__declspec 无效
    // 如果你想处理符号可见性，可以使用 __attribute__((visibility("default")))
    // 但通常留空即可正常工作
    #define MYMATH_API __attribute__((visibility("default")))
#endif

extern "C" {
    MYMATH_API int add_int(int a, int b);
    MYMATH_API float add_float(float a, float b);
}

#endif // MYMATH_H