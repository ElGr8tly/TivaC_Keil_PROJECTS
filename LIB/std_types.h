#ifndef _STD_TYPES_H_
#define _STD_TYPES_H_


/************************************************************************/
/*                        MACROS DECLARATION                            */
/************************************************************************/
#ifndef TRUE
#define TRUE                        (1U)
#endif
#ifndef FALSE
#define FALSE                       (0U)
#endif
/************************************************************************/
#ifndef HIGH
#define HIGH                        (1U)
#endif
#ifndef LOW
#define LOW                         (0U)
#endif
/************************************************************************/
#ifndef NULL
#define NULL						((void*) 0U)
#endif
/************************************************************************/
#ifndef WEAK
#define WEAK                    __attribute__((weak))
#endif
/************************************************************************/
#ifndef STATIC_INLINE
#define STATIC_INLINE               static inline
#endif
/************************************************************************/
/*                    Data Type Declarations                            */
/************************************************************************/
typedef unsigned char                 uint8_t;          /*           0 .. 255             */
typedef signed char                   sint8_t;          /*        -128 .. +127            */
typedef unsigned short                uint16_t;         /*           0 .. 65535           */
typedef signed short                  sint16_t;         /*      -32768 .. +32767          */
typedef unsigned int                  uint32_t;         /*           0 .. 4294967295      */
typedef signed long                   sint32_t;         /* -2147483648 .. +2147483647     */
typedef unsigned long long            uint64_t;         /*       0..18446744073709551615  */
typedef signed long long              sint64_t;         /*                                */
typedef float                         float32_t;        /*                                */
typedef double                        float64_t;        /*                                */
typedef uint8_t                       bool_t;           /*      TRUE     or  FALSE        */ 
/************************************************************************/
#endif