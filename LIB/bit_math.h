#ifndef _BIT_MATH_H_
#define _BITMATH_H_
/**************************************************************************/
/*                    Macros funcitons for Bit operations                 */
/**************************************************************************/
#define SET_BIT(_REG_ , _BIT_NUM_)        ((_REG_) |=  (1U<<(_BIT_NUM_)))
#define CLR_BIT(_REG_ , _BIT_NUM_)        ((_REG_) &= ~(1U<<(_BIT_NUM_)))
#define TOG_BIT(_REG_ , _BIT_NUM_)        ((_REG_) ^=  (1U<<(_BIT_NUM_)))
#define GET_BIT(_REG_ , _BIT_NUM_)        (((_REG_)>>  (_BIT_NUM_)) &1U ) 
#define SET_BITS(_REG_ , _MSK_)           ((_REG_) |=  (_MSK_))
#define CLR_BITS(_REG_ , _MSK_)           ((_REG_) &= ~(_MSK_))
#define TOG_BITS(_REG_ , _MSK_)           ((_REG_) ^=  (_MSK_))
#define GET_BITS(_REG_ , _MSK_)           ((_REG_)  &  (_MSK_))
#define CLR_ALL_BITS(_REG_)               ((_REG_)  = (0U))
#define SET_ALL_BITS(_REG_)               ((_REG_)  = ~((_REG_) & 0U))
#define TOG_ALL_BITS(_REG_)               ((_REG_)  = ~(_REG_))
/*************************************************************************
* @Example  :  We can use it if we need group of pins  ( from  5  to 12  ) 
*                                  or  
* need all pins except ( from 5 to 12 ) like  ( 0bx1110 0000 0001 1111 )
**************************************************************************/
#define PUT_ONES_IN_8BIT(_FROM_,_TO_)     ((unsigned char)(  ( ( 2 << ((_TO_) - (_FROM_))) - 1 ) << (_FROM_)))
#define PUT_ZEROS_IN_8BIT(_FROM_,_TO_)    ( ~PUT_ONES_IN_8BIT( _FROM_ , _TO_ ))
#define PUT_ONES_IN_16BIT(_FROM_,_TO_)    ((unsigned short)( ( ( 2 << ((_TO_) - (_FROM_))) - 1 ) << (_FROM_)))
#define PUT_ZEROS_IN_16BIT(_FROM_,_TO_)   ( ~PUT_ONES_IN_16BIT( _FROM_ , _TO_ ))
#define PUT_ONES_IN_32BIT(_FROM_,_TO_)    ((unsigned long)(  ( ( 2 << ((_TO_) - (_FROM_))) - 1 ) << (_FROM_)))
#define PUT_ZEROS_IN_32BIT(_FROM_,_TO_)   ( ~PUT_ONES_IN_32BIT( _FROM_ , _TO_ ))
/**************************************************************************/
/**************************************************************************/
#define PUT_ONE_IN_8BIT(_BIT_NUM_)        ((unsigned char)(1U << (_BIT_NUM_)))
#define PUT_ZERO_IN_8BIT(_BIT_NUM_)       ( ~PUT_ONE_IN_8BIT(_BIT_NUM_))
#define PUT_ONE_IN_16BIT(_BIT_NUM_)       ((unsigned short)(1U << (_BIT_NUM_)))
#define PUT_ZERO_IN_16BIT(_BIT_NUM_)      ( ~PUT_ONE_IN_16BIT(_BIT_NUM_))
#define PUT_ONE_IN_32BIT(_BIT_NUM_)       ((unsigned long)(1U << (_BIT_NUM_)))
#define PUT_ZERO_IN_32BIT(_BIT_NUM_)      ( ~PUT_ONE_IN_32BIT(_BIT_NUM_))
/**************************************************************************/
/**************************************************************************/
#define WRITE_BIT_VLAUE(_REG_ ,_VAL_,_SHIFT_) ((_REG_)=(((_REG_)&(~((1U)<<(_SHIFT_))))|(((_VAL_)&(1U))<<(_SHIFT_))))
#define WRITE_BITS_VLAUE(_REG_,_MSK_,_VAL_,_SHIFT_) ((_REG_)=(((_REG_)&(~((_MSK_)<<(_SHIFT_))))|(((_VAL_)&(_MSK_))<<(_SHIFT_))))
/**************************************************************************/
/**************************************************************************/
#define SHIFT_ONE_TIME                     1U
/**************************************************************************/
/**************************************************************************/
#endif