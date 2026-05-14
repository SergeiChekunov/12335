// -*- mode: c++; coding: utf-8 -*-
// PostWin 5 Embedded libraryиии

/*! \file pwdisable_copy
 *
 * Автор: I.Kashurnikov и другие
 * Last modified: $Id: pwdisable_copy.h 476 2012-08-30 09:37:54Z kashurnikov $
 *
 */

#ifndef disable_copy_h__
#define disable_copy_h__

#include <mssc_config.h>


/****************************************************************************************************************
    MSSC_DISABLE_COPY
 ****************************************************************************************************************/

/*! \def MSSC_DISABLE_COPY
 *  \brief Макрос отключает конструктор копирования и присваивания
 *
 *  Используейте данные метод в секции \b private класса
 *
 *  Пример использования:
 *   \code
 *      class MyClass{
 *         int* p;
 *      public:
 *          MyClass();
 *          virtual ~MyClass();
 *          //... некоторые методы
 *      private:
 *         MSSC_DISABLE_COPY( MyClass ); // Эквивалентно следующему коду: MyClass( const MyClass& );
 *                                       //                               void operator=( const MyClass& );
 *      };
 *   \endcode
 */
#if defined(MSSC_CXX_BORLAND)
#  define MSSC_DISABLE_COPY( ClassName ) \
      ClassName( const ClassName& ); \
      void operator=( const ClassName& )
#else
#  define MSSC_DISABLE_COPY( ClassName ) \
      ClassName( const ClassName& ) = delete; \
      void operator=( const ClassName& ) = delete
#endif


#endif
