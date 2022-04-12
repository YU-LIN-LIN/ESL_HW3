#ifndef _DIRECTIVES_H_
#define _DIRECTIVES_H_

// This file defines macros that are used as synthesis directives in the DUT
// module. For specific HLS configs (UNROLL_COL and UNROLL_ALL), the macros are 
// defined as either HLS_UNROLL_LOOP directives, or defined as nothing.
// For any other HLS configs, #ifndefs are used to define the macros as nothing.


// Define a group of macros for each configuration
#ifdef UNROLL_COL
#   define COL_LOOP  HLS_UNROLL_LOOP( ON, "col loop" )
#   define ROW_LOOP
#endif

#ifdef UNROLL_ALL
#   define COL_LOOP  HLS_UNROLL_LOOP( ON, "col loop" )
#   define ROW_LOOP HLS_UNROLL_LOOP( ON, "row loop" )
#endif

// Define each macro as an empty string if it is not defined above
#ifndef COL_LOOP
#   define COL_LOOP
#endif
#ifndef ROW_LOOP
#   define ROW_LOOP
#endif

#endif // _DIRECTIVES_H_
