// -*- mode: c++; coding: utf-8 -*-
// Mobile-services Switching Centre (mobsrvswcntr)

/*! \file mssc_config.h
 *
 * Декларации, настраивающие код библиотек и приложений таким образом, что их
 * можно собирать и разрабатывать кроссплатформенно.
 *
 * Исходный файл pwconfig.h из pw5e
 */
#ifndef mssc_config_h__
#define mssc_config_h__

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#ifdef __cplusplus
#  include <cassert>
#  include <cstdlib>
#  include <cstddef>
#else
#  include <assert.h>
#  include <stdlib.h>
#  include <stddef.h>
#endif

// memcpy у Borland находяться в неожиданом месте )
#if defined(__BORLANDC__) || defined(__BCPLUSPLUS__)
# include <mem.h>
#endif

#if defined(__osf__)
//     Tru64 lacks stdint.h, but has inttypes.h which defines a superset of
//     what stdint.h would define.
#  include <inttypes.h>
#else
#  include <stdint.h>
#endif

#ifdef max
#  undef max
#endif

#ifdef min
#  undef min
#endif


/****************************************************************************************************************
      Определяем платформу
 ****************************************************************************************************************/

/*! \page page1 Конфигурация платформы
 *
 * Файл <mssc_config.h>
 *
 * Определяются следующие платформы:
 *  \li \c  Linux   - макрос \b MSSC_LINUX
 *  \li \c  MCBC    - макрос \b MSSC_MCBC (MSSC_LINUX так же определен)
 *  \li \c  BSD     - макрос \b MSSC_BSD
 *  \li \c  Solaris - макрос \b MSSC_SOLARIS
 *  \li \c  QNX     - макрос \b MSSC_QNX
 *  \li \c  MacOS   - макрос \b MSSC_APPLE
 *  \li \c  Unix (неизветная версия Unix системы) - макрос \b MSSC_UNINX
 *  \li \c  Windows - макрос \b MSSC_WINODWS
 *  \li \c  Cygwin  - макрос \b MSSC_CYGWIN
 *
 * Правила конфигурации платоформы:
 *  \li \c макрос \b MSSC_PLATFORM содержит название (строковое представление) платформы
 *  \li \c макрос \b MSSC_POSIX    опредляет является ли данная ОС истиной(правильной) и подерживает POSIX (все платформы кроме Windows)
 *
 *  \note Если платформа определна как Cygwin - то макрос \b MSSC_WINDOWS НЕ доступен, за то опрределен макрос \b MSSC_POSIX
 */

// linux, also other platforms (Hurd etc) that use GLIBC, should these really have their own config headers though?
#if defined(linux) || defined(__linux) || defined(__linux__) || defined(__GNU__) || defined(__GLIBC__)
#  define MSSC_LINUX
#  define MSSC_POSIX
#  if defined(__mcbc__)
#     define MSSC_MCBC
#     define MSSC_PLATFORM "MCBC"
#  elif defined( __astra_linux__ )
#     define MSSC_ASTRA_LINUX
#     define MSSC_PLATFORM "Astra Linux"
#  else
#     define MSSC_PLATFORM "Linux"
#  endif
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) // BSD:
#  define MSSC_BSD
#  define MSSC_POSIX
#  define MSSC_PLATFORM "BSD"
#elif defined(sun) || defined(__sun) // solaris:
#  define MSSC_SOLARIS
#  define MSSC_POSIX
#  define MSSC_PLATFORM "Solaris"
#elif defined(__CYGWIN__) // cygwin is not win32:
#  define MSSC_CYGWIN
#  define MSSC_POSIX
#  define MSSC_PLATFORM "Cygwin"
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WINDOWS) // win32:
#  define MSSC_WINDOWS
#  define MSSC_PLATFORM "Windows"
#  if defined(__MINGW32__)  //  Get the information about the MinGW runtime, i.e. __MINGW32_*VERSION.
#     include <_mingw.h>
#  endif
#elif defined(macintosh) || defined(__APPLE__) || defined(__APPLE_CC__) // MacOS
#  define MSSC_APPLE
#  define MSSC_POSIX
#  define MSSC_PLATFORM "MacOS"
#elif defined(__QNXNTO__)  // QNX:
#  define MSSC_QNIX
#  define MSSC_POSIX
#  define MSSC_PLATFORM "QNX"
#elif defined(unix) || defined(__unix) || defined(_XOPEN_SOURCE) || defined(_POSIX_SOURCE)
#  define MSSC_UNINX
#  define MSSC_POSIX
#  define MSSC_PLATFORM "Unix"
#else
#   error "Unknown platform - please reconfigure"
#endif

/****************************************************************************************************************
      Определяем компилятор
****************************************************************************************************************/

#if defined(_MSC_VER) && defined(__clang__)
#  error Unsupported compilers configuration :(
#endif

/*! \page page2 Конфигурация компилятора
 *
 * Файл <mssc_config.h>
 *
 * Определяются следующие компиляторы:
 *  \li \c  GCC (включая MinGW) - макросы \b MSSC_CXX_GCC, \b MSSC_CXX_GCC_VER
 *  \li \c  LLVM clang          - макросы \b MSSC_CXX_CLANG, \b MSSC_CXX_CLANG_VER
 *  \li \c  Bolrand             - макросы \b MSSC_CXX_BORLAND, \b MSSC_CXX_BORLAND_VER
 *  \li \c  MS Visual C         - макросы \b MSSC_CXX_MSCm \b MSSC_CXX_MSC_VER
 *
 *  Макрос \b MSSC_CXX  содержит название (строковое представление) компилятора
*/
#if defined(__GNUC__)
#  define MSSC_CXX_GCC
#  define MSSC_CXX "gcc"
#  define MSSC_CXX_GCC_VER (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#  if MSSC_CXX_GCC_VER < 40000
#    error "Unsuported gcc version"
#  endif
#elif defined(__BORLANDC__) || defined(__BCPLUSPLUS__)
#  define MSSC_CXX_BORLAND
#  define MSSC_CXX "bcb"
#  error "Version of MSSC_CXX_BORLAND_VER not specified!" // доделать
#elif defined(_MSC_VER)
#  define MSSC_CXX_MSC
#  define MSSC_CXX "MS VisualC"
#  define MSSC_CXX_MSC_VER (_MSC_VER)
#else
#  error "Unknown compiler - please reconfigure"
#endif

#if defined(__clang__)
#  define MSSC_CXX_CLANG
#  if defined(MSSC_CXX_GCC)
#    undef MSSC_CXX // случай, когда CMAKE_C_COMPILER=gcc CMAKE_CXX_COMPILER=clang++ (сборка по умолчанию в QtCreator)
#  endif
#  define MSSC_CXX "clang"
#  if defined(__apple_build_version__) // Apple and LLVM's Clang. Apple Clang version 7.0 roughly equals LLVM Clang version 3.7
#    define MSSC_CXX_APPLE_CLANG_VER (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#  else
#    define MSSC_CXX_LLVM_CLANG_VER (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#  endif // __apple_build_version__
#endif

// Compatibility with non-clang compilers.
#ifndef __has_feature
#  define __has_feature(x) 0
#endif

// nullptr_t: MS at VS2010 (16.00); GCC at 4.6; Clang at 3.3; Intel 10.0; SunCC 5.13.
#if (MSSC_CXX_MSC_VER >= 1600) || __has_feature(cxx_nullptr) || \
    (__INTEL_COMPILER >= 1000) || (MSSC_CXX_GCC_VER >= 40600) || (__SUNPRO_CC >= 0x5130)
#  define MSSC_CXX11_NULLPTR 1
#endif // nullptr_t compilers

// Hack... C++11 nullptr_t type safety and analysis
#if defined(MSSC_CXX11_NULLPTR) && !defined(MSSC_NULLPTR)
#  define MSSC_NULLPTR nullptr
#elif !defined(NULLPTR)
#  define MSSC_NULLPTR NULL
#  error "possible problems with old compilers" // если сработает эта ошибка, то придётся перейти с nullptr на MSSC_NULLPTR
#endif // MSSC_CXX11_NULLPTR

// см. также https://github.com/weidai11/cryptopp/blob/master/config.h

/****************************************************************************************************************
      Задаём макросы, зависящие от используемого компилятора для управления им
****************************************************************************************************************/

/*! \page page2 Конфигурация компилятора для GCC 4.6/Clang 1.7/Apple Clang 2.0 или выше для "GCC diagnostic {push|pop}"
 *
 * Файл <mssc_config.h>
 *
 * Определяются следующие компиляторы:
 *  \li \c  GCC (включая MinGW)   - макрос \b MSSC_GCC_DIAGNOSTIC_AVAILABLE
 *
 * Предлагается использование макросов в следующих случаях:
\code
void foo()
{
    #if MSSC_GCC_DIAGNOSTIC_AWARE
    #  pragma GCC diagnostic push
    #  pragma GCC diagnostic ignored "-Wunused-variable"
    #endif
    for (const auto & ref : m_params.streams)
    {
        assert((ref.first_cic % 32) == 0); // warning: unused variable ‘ref’ [-Wunused-variable]
    }
    #if MSSC_GCC_DIAGNOSTIC_AWARE
    #  pragma GCC diagnostic pop
    #endif
}
\endcode
*/
#if (MSSC_CXX_GCC_VER >= 40600) || (MSSC_CXX_LLVM_CLANG_VER >= 10700) || (MSSC_CXX_APPLE_CLANG_VER >= 20000)
#  define MSSC_GCC_DIAGNOSTIC_AWARE 1
#endif

// [GCC Bug 53431] "C++ preprocessor ignores #pragma GCC diagnostic". Clang honors it.
#if MSSC_GCC_DIAGNOSTIC_AWARE
#  pragma GCC diagnostic ignored "-Wunknown-pragmas"
#  pragma GCC diagnostic ignored "-Wunused-function"
#endif

/****************************************************************************************************************
      Макросы экспорта/иморта функци
****************************************************************************************************************/

/*! \page page3 Макросы экспорта/импорта функци
 *
 * Файл <mssc_config.h>
 *
 * Определены следующие макросы облегчающие жизнь при переносе кода между платофрмами:
 *   \li \c \b MSSC_SYMBOL_EXPORT - макрос определяет экспортируемые ф-ции для Windows библиотек
 *   \li \c \b MSSC_SYMBOL_IMPORT - макрос определяет импортируемые ф-ции для Winodws библиотек
 *   \li \c \b MSSC_STDCALL       - соглашение о вызове __stdcall
 *   \li \c \b MSSC_CDECL         - соглашение о вызове __cdecl
*/
#if defined(__GNUC__) && (__GNUC__ >= 4) && (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
   // All Win32 development environments, including 64-bit Windows and MinGW, define
   // _WIN32 or one of its variant spellings. Note that Cygwin is a POSIX environment,
   // so does not define _WIN32 or its variants.
#  define MSSC_SYMBOL_EXPORT __attribute__((dllexport))
#  define MSSC_SYMBOL_IMPORT __attribute__((dllimport))
#endif
#if defined(MSSC_WINDOWS)
#  ifndef MSSC_SYMBOL_EXPORT
#    define MSSC_SYMBOL_EXPORT __declspec(dllexport)
#  endif
#  ifndef MSSC_SYMBOL_IMPORT
#    define MSSC_SYMBOL_IMPORT __declspec(dllimport)
#  endif
#  define MSSC_STDCALL __stdcall
#  define MSSC_CDECL   __cdecl
#else
#  define MSSC_SYMBOL_EXPORT
#  define MSSC_SYMBOL_IMPORT
#  define MSSC_STDCALL
#  define MSSC_CDECL
#endif


/****************************************************************************************************************
      Если Windows, используем MINIMAL INCLUDEs
****************************************************************************************************************/

#if defined(MSSC_WINDOWS)
#  if !defined(WIN32_LEAN_AND_MEAN)
#    define WIN32_LEAN_AND_MEAN
#  endif
#endif

/****************************************************************************************************************
      Макросы для представления 64-битных констат (литералов)
****************************************************************************************************************/

/*! \page page4 Макросы для представления 64-битных констант
 *
 *   Определены следущие макросы:
 *   \li \c MSSC_INT64_C
 *   \li \c MSSC_UINT64_C
 *
 *  Пример:
 *   \сode
 *      int64_t  i64value = MSSC_INT64_C(932838457459459);
 *      uint64_t u64value = MSSC_UINT64_C(932838457459459);
 *   \endcode
*/

#if defined(MSSC_WINDOWS) && !defined(MSSC_CXX_GCC)
#  define MSSC_INT64_C(c) c ## i64    /* signed 64 bit constant */
#  define MSSC_UINT64_C(c) c ## ui64   /* unsigned 64 bit constant */
#else
#  define MSSC_INT64_C(c) static_cast<long long>(c ## LL)     /* signed 64 bit constant */
#  define MSSC_UINT64_C(c) static_cast<unsigned long long>(c ## ULL) /* unsigned 64 bit constant */
#endif

/****************************************************************************************************************
      Макросы для определения предельных значений целочисленных типов
****************************************************************************************************************/

/*! \page page5 Макросы для определения предельных значений целочисленных типов
 *
 *   Определены следущие макросы:
 *   \li \c MSSC_INT8_MIN
 *   \li \c MSSC_INT16_MIN
 *   \li \c MSSC_INT32_MIN
 *   \li \c MSSC_INT64_MIN
 *   \li \c MSSC_INT8_MAX
 *   \li \c MSSC_INT16_MAX
 *   \li \c MSSC_INT32_MAX
 *   \li \c MSSC_INT64_MAX
 *   \li \c MSSC_UINT8_MAX
 *   \li \c MSSC_UINT16_MAX
 *   \li \c MSSC_UINT32_MAX
 *   \li \c MSSC_UINT64_MAX
 *
 *  Пример:
 *   \сode
 *      uint32_t ui32value = MSSC_UINT32_MAX;
 *      if ( i32value == MSSC_INT32_MIN ) ...;
 *   \endcode
*/

#ifdef INT8_MIN
#  define MSSC_INT8_MIN INT8_MIN
#else
#  define MSSC_INT8_MIN ( -0x7f - 1 )
#endif

#ifdef INT16_MIN
#  define MSSC_INT16_MIN INT16_MIN
#else
#  define MSSC_INT16_MIN ( -0x7fff - 1 )
#endif

#ifdef INT32_MIN
#  define MSSC_INT32_MIN INT32_MIN
#else
#  define MSSC_INT32_MIN ( -0x7fffffff - 1 )
#endif

#ifdef INT64_MIN
#  define MSSC_INT64_MIN INT64_MIN
#else
#  define MSSC_INT64_MIN ( MSSC_INT64_C( -0x7fffffffffffffff ) - 1 )
#endif

#ifdef INT8_MAX
#  define MSSC_INT8_MAX INT8_MAX
#else
#  define MSSC_INT8_MAX ( 0x7f )
#endif

#ifdef INT16_MAX
#  define MSSC_INT16_MAX INT16_MAX
#else
#  define MSSC_INT16_MAX ( 0x7fff )
#endif

#ifdef INT32_MAX
#  define MSSC_INT32_MAX INT32_MAX
#else
#  define MSSC_INT32_MAX ( 0x7fffffff )
#endif

#ifdef INT64_MAX
#  define MSSC_INT64_MAX INT64_MAX
#else
#  define MSSC_INT64_MAX ( MSSC_INT64_C( 0x7fffffffffffffff ) )
#endif

#ifdef UINT8_MAX
#  define MSSC_UINT8_MAX UINT8_MAX
#else
#  define MSSC_UINT8_MAX ( 0xff )
#endif

#ifdef UINT16_MAX
#  define MSSC_UINT16_MAX UINT16_MAX
#else
#  define MSSC_UINT16_MAX ( 0xffff )
#endif

#ifdef UINT32_MAX
#  define MSSC_UINT32_MAX UINT32_MAX
#else
#  define MSSC_UINT32_MAX ( 0xffffffff )
#endif

#ifdef UINT64_MAX
#  define MSSC_UINT64_MAX UINT64_MAX
#else
#  define MSSC_UINT64_MAX ( MSSC_UINT64_C( 0xffffffffffffffff ) )
#endif

#ifdef MAX_PATH
#  define MSSC_MAX_PATH MAX_PATH
#else
#  define MSSC_MAX_PATH 260
#endif


/****************************************************************************************************************
      Макросы определяющие разрядность платформы под которую осуществляется сборка x86 или x64
****************************************************************************************************************/

/*! \page page5 Макросы определяющие разрядность платформы под которую осуществляется сборка x86 или x64
 *
 *  Определены следущие мскросы:
 *    \li \c  MSSC_ENV64BIT
 *    \li \c  MSSC_ENV32BIT
*/

#if defined(MSSC_WINDOWS)
    // Check windows
    #if _WIN64
        #define MSSC_ENV64BIT
    #else
        #define MSSC_ENV32BIT
    #endif
#else
    // Check GCC
    #if __GNUC__
        #if __x86_64__ || __ppc64__
            #define MSSC_ENV64BIT
        #else
            #define MSSC_ENV32BIT
        #endif
    #elif defined(UINTPTR_MAX)
        #if UINTPTR_MAX == 0xffffffff
            #define MSSC_ENV32BIT
        #elif UINTPTR_MAX == 0xffffffffffffffff
            #define MSSC_ENV64BIT
        #endif
    #endif
#endif

#if defined(MSSC_CXX_GCC)  // GCC -  считаем что с 11 стандартом
#   define MSSC_NOEXCEPT_FALSE noexcept(false)
#elif defined(MSSC_CXX_MSC)
#  if  _MSC_VER >= 1900  // Только наичная с MSVC 2015
#     define MSSC_NOEXCEPT_FALSE noexcept(false)
#  else
#     define MSSC_NOEXCEPT_FALSE
#  endif
#elif defined(MSSC_CXX_BORLAND)
#   define MSSC_NOEXCEPT_FALSE
#else
#  error "Compiler not supported"
#endif

/****************************************************************************************************************
      Макросы для кроссплатформенных спецификаторов формата вывода
****************************************************************************************************************/

/*! \page page6 Макросы для кроссплатформенных спецификаторов формата вывода
 *
 *   Определены следущие макросы:
 *   \li \c MSSC_PRINTF_I64
 *
 *  Пример:
 *   \сode
 *      int64_t val = MSSC_INT64_MAX;
 *      printf("Max x64 value is %"MSSC_PRINTF_I64"d\n", val);
 *      uint64_t uval = MSSC_UINT64_MAX;
 *      printf("Max unsigned x64 value is %"MSSC_PRINTF_I64"u, as hex is 0x%"MSSC_PRINTF_I64"x\n", uval, uval);
 *   \endcode
*/
#if defined(MSSC_ENV64BIT)
#  define MSSC_PRINTF_I64 "l"
#elif defined(MSSC_WINDOWS) && !defined(MSSC_CXX_GCC)
#  define MSSC_PRINTF_I64 "I64"
#else
#  define MSSC_PRINTF_I64 "ll"
#endif



/****************************************************************************************************************
      Макросы для разделителей пути в файловой системы
****************************************************************************************************************/

/*! \page page7 Макросы для разделителей пути в файловой системы
 *
 *   Определены следущие макросы:
 *   \li \c MSSC_FS_PATH_NATIVE_SEPARATOR - для Windows - '\', для отсальных - '/'
 */
#if defined(MSSC_WINDOWS)
#  define MSSC_FS_PATH_NATIVE_SEPARATOR '\\'
#else
#  define MSSC_FS_PATH_NATIVE_SEPARATOR '/'
#endif



/****************************************************************************************************************
      Макросы указывающие что ф-ция устарела
****************************************************************************************************************/

/*! \page page8 Макросы указывающие что ф-ция устарела
 *
 *  Определены следующие макросы:
 *    \li \c  MSSC_FUNCTION_DEPRECATED( FUNC )
 *
 *  Если вы хотите объявить некоторую ф-цию как устаревшую, и чтобы при ее использовании компилятором
 *  выдавалось предупреждение, вы можете воспользоваться макросом \b MSSC_FUNCTION_DEPRECATED, следующим образом:
 *  \code
 *    // Пусть есть ф-ция void my_depereacted_func( int ), чтобы пометить ее как устаревшую,
 *    // ее объявление должно выглядеть как:
 *
 *    MSSC_FUNCTION_DEPRECATED( void my_depereacted_func( int ) );
 *
 *    int main() {
 *          my_depereacted_func(5); // Здесь будет предупрежедение компилятора
 *    }
 *  \encode
*/
#if defined(MSSC_CXX_MSC) // Для Borland нельзя указывать __declspec(deprecated), если указать он не будет экспортровать ф-ции из dll
#  define MSSC_FUNCTION_DEPRECATED( FUNC ) __declspec(deprecated) FUNC
#elif defined(MSSC_CXX_GCC)
#  define MSSC_FUNCTION_DEPRECATED(FUNC) FUNC __attribute__ ((deprecated))
#else
#  define MSSC_FUNCTION_DEPRECATED(FUNC ) FUNC
#endif

/****************************************************************************************************************
      Макросы указывающие что класс устарел
****************************************************************************************************************/

/*! \page page8 Макросы указывающие что  класс устарел
 *
 *  Определены следующие макросы:
 *    \li \c  MSSC_CLASS_DEPRECATED_BEGIN( CLASS )
 *    \li \c  MSSC_CLASS_DEPRECATED_END( )
 *
 *  Если вы хотите объявить некоторый класс как устаревший, и чтобы при его использовании компилятором
 *  выдавалось предупреждение, вы можете воспользоваться макросами \b MSSC_CLASS_DEPRECATED_BEGIN и \b MSSC_CLASS_DEPRECATED_END, следующим образом:
 *  \code
 *    // Пусть есть класс my_depereacted_class, чтобы пометить его как устаревший,
 *    // его объявление должно выглядеть как:
 *
 *    class MSSC_CLASS_DEPRECATED_BEGIN( my_depereacted_class )
 *    {
 *    } MSSC_CLASS_DEPRECATED_END();
 *
 *    int main() {
 *          my_depereacted_class c; // Здесь будет предупрежедение компилятора
 *    }
 *  \encode
*/
#if defined(MSSC_CXX_MSC) // Для Borland нельзя указывать __declspec(deprecated), если указать он не будет экспортровать ф-ции из dll
#  define MSSC_CLASS_DEPRECATED_BEGIN(CLASS) __declspec(deprecated) CLASS
#  define MSSC_CLASS_DEPRECATED_END()
#elif defined(MSSC_CXX_GCC)
#  define MSSC_CLASS_DEPRECATED_BEGIN(CLASS) CLASS
#  define MSSC_CLASS_DEPRECATED_END()  __attribute__ ((deprecated))
#else
#  define MSSC_CLASS_DEPRECATED_BEGIN(CLASS) CLASS
#  define MSSC_CLASS_DEPRECATED_END()
#endif

// Макрос для пометки неиспользуемой переменной
//  C++Builder Warning W8057 : Parameter 'param' is never used in function foo()
//  MSVC error C2055 : требуется список формальных параметров, а не список типов
//  gcc error : unused parameter
#define MSSC_UNUSED(x)       ((void)(x))

#if !defined(__BASE_FILE__)
#  if defined(MSSC_CXX_MSC) // в студии этот макрос не определён https://stackoverflow.com/a/24322665/8898651
#    define __BASE_FILE__ __FILE__
#  endif
#endif

#include <mssc_disablecopy.h>

#endif
