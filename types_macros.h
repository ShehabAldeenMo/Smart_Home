#pragma once

// Standard Types
#define NULL_PTR    ((void*)0)
typedef unsigned char         uint8;
typedef signed char           sint8;
typedef unsigned short        uint16;
typedef signed short          sint16;
typedef unsigned long         uint32;
typedef signed long           sint32;
typedef unsigned long long    uint64;
typedef signed long long      sint64;
typedef float                 float32;
typedef double                float64;

// Macros
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )
