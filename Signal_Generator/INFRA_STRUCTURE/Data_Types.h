/*
 * Data_Types.h
 *
 *  Created on: Dec 30, 2019
 *      Author: MO._.Hamdy "Wazeer"
 */

#ifndef __INFRA_STRUCTURE_DATA_TYPES_H__
#define __INFRA_STRUCTURE_DATA_TYPES_H__


#define NULL	 	0U
#define INITIAL	 	0U
#define DUMMY	 	0XFFU

#define FALSE 	0U
#define TRUE  	1U


typedef unsigned char 			uint8_t;
typedef unsigned int 			uint16_t; /* typedef unsigned short int 		uint16_t; */
typedef unsigned long int 		uint32_t;
typedef unsigned long long int  uint64_t;

typedef signed char 			sint8_t;
typedef signed short int 		sint16_t;
typedef signed long int 		sint32_t;
typedef signed long long int    sint64_t;

typedef float 					float32_t;
typedef double 					float64_t;
typedef long double 			float128_t;

typedef uint8_t 				error_t;

typedef void(*pfunc_t)(void);
typedef void(*pfunc_u8_t)(uint8_t);
typedef void(*pfunc_u8_u8_t)(uint8_t, uint8_t);
typedef uint8_t(*u8_pfunc_t)(void);


#endif /* __INFRA_STRUCTURE_DATA_TYPES_H__ */
