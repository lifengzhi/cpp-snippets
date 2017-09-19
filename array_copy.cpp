// See: CppCon 2016: Dan Saks “extern c: Talking to C Programmers about C++”
// https://youtu.be/D7Sd8A6_fYU

// See: https://stackoverflow.com/q/5724171/496459

#include <iostream>
#include <cstring>
#include <type_traits>

#include <gsl/gsl>

template <typename T, size_t N>
inline void array_copy(T (&dst)[N], T (&src)[N])
{
    static_assert(std::is_trivially_copy_assignable<T>::value,
                  "element type has non-trivial copy assignment");
#if 1
    memcpy(dst, src, N * sizeof(T));
#else
    for (size_t i = 0; i < N; ++i)
    {
        dst[i] = src[i];
    }
#endif
}

template <typename T>
void print_collection(gsl::span<const T> s)
{
    std::copy(std::begin(s), std::end(s),
              std::ostream_iterator<T>(std::cout, "\n"));
}

int main()
{
    int arr1[] {1,2,3};
    int arr2[sizeof(arr1)/sizeof(arr1[0])];

    array_copy(arr2, arr1);

    gsl::span<const int> s1 {arr1};
    gsl::span<const int> s2 {arr2};
    print_collection(s1);
    print_collection(s2);
}
