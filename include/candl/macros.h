
   /**------ ( ----------------------------------------------------------**
    **       )\                      CAnDL                               **
    **----- /  ) --------------------------------------------------------**
    **     ( * (                    candl.h                              **
    **----  \#/  --------------------------------------------------------**
    **    .-"#'-.        First version: september 8th 2003               **
    **--- |"-.-"| -------------------------------------------------------**
          |     |
          |     |
 ******** |     | *************************************************************
 * CAnDL  '-._,-' the Chunky Analyzer for Dependences in Loops (experimental) *
 ******************************************************************************
 *                                                                            *
 * Copyright (C) 2003-2008 Cedric Bastoul                                     *
 *                                                                            *
 * This is free software; you can redistribute it and/or modify it under the  *
 * terms of the GNU Lesser General Public License as published by the Free    *
 * Software Foundation; either version 3 of the License, or (at your option)  *
 * any later version.                                                         *
 *                                                                            *
 * This software is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License   *
 * for more details.                                                          *
 *                                                                            *
 * You should have received a copy of the GNU Lesser General Public License   *
 * along with software; if not, write to the Free Software Foundation, Inc.,  *
 * 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA                     *
 *                                                                            *
 * CAnDL, the Chunky Dependence Analyser                                      *
 * Written by Cedric Bastoul, Cedric.Bastoul@inria.fr                         *
 *                                                                            *
 ******************************************************************************/


/******************************************************************************
 *  THIS FILE HAS BEEN AUTOMATICALLY GENERATED FROM macros.h.in BY configure  *
 ******************************************************************************/


#ifndef CANDL_MACROS_H
# define CANDL_MACROS_H

# include <piplib/piplib64.h>
# include <candl/options.h>
# include <candl/matrix.h>
# include <candl/dependence.h>
# include <candl/ddv.h>
# include <candl/violation.h>
# include <candl/pruning.h>

# define CANDL_UNSET -1 /* Must be negative (we do use that property).
                         * All other constants have to be different.
                         */

# define CANDL_RAW    1
# define CANDL_WAR    2
# define CANDL_WAW    3
# define CANDL_RAR    4
# define CANDL_RAW_SCALPRIV	5

# define CANDL_ASSIGNMENT  1
# define CANDL_P_REDUCTION 2
# define CANDL_M_REDUCTION 3
# define CANDL_T_REDUCTION 4

# define CANDL_EQUAL 1
# define CANDL_POSIT 2
# define CANDL_LATER 3
# define CANDL_NEVER 4

# define CANDL_NB_INFOS  3

# define CANDL_MAX_STRING  2048
# define CANDL_TEMP_OUTPUT "candl.temp"

# define CANDL_RELEASE "0.6.2"
# define CANDL_VERSION "64"



/* Useful macros. */
# define CANDL_max(x,y)    ((x) > (y)? (x) : (y))
# define CANDL_min(x,y)    ((x) < (y)? (x) : (y))

# define CANDL_FAIL(msg)   { fprintf(stderr, "[Candl] " msg "\n"); exit(1); }

/******************************************************************************
 *                                   FORMAT                                   *
 ******************************************************************************/
#if defined(LINEAR_VALUE_IS_LONGLONG)
#define CANDL_FMT "%4lld "
#elif defined(LINEAR_VALUE_IS_LONG)
#define CANDL_FMT "%4ld "
#else  /* GNUMP */
#define CANDL_FMT "%4s"
#endif

/******************************************************************************
 *                             CANDL GMP MACROS                               *
 ******************************************************************************/
#ifdef LINEAR_VALUE_IS_MP
/* Basic Macros */
#define CANDL_init(val)                (mpz_init((val)))
#define CANDL_assign(v1,v2)            (mpz_set((v1),(v2)))
#define CANDL_set_si(val,i)            (mpz_set_si((val),(i)))
#define CANDL_get_si(val)              (mpz_get_si((val)))
#define CANDL_clear(val)               (mpz_clear((val)))
#define CANDL_print(Dst,fmt,val)       { char *str; \
                                         str = mpz_get_str(0,10,(val)); \
                                         fprintf((Dst),(fmt),str); free(str); \
                                       }

/* Boolean operators on 'Value' or 'Entier' */
#define CANDL_eq(v1,v2)                (mpz_cmp((v1),(v2)) == 0)
#define CANDL_ne(v1,v2)                (mpz_cmp((v1),(v2)) != 0)

/* Binary operators on 'Value' or 'Entier' */
#define CANDL_increment(ref,val)       (mpz_add_ui((ref),(val),1))
#define CANDL_decrement(ref,val)       (mpz_sub_ui((ref),(val),1))
#define CANDL_subtract(ref,val1,val2) (mpz_sub((ref),(val1),(val2)))
#define CANDL_oppose(ref,val)          (mpz_neg((ref),(val)))

/* Conditional operations on 'Value' or 'Entier' */
#define CANDL_zero_p(val)              (mpz_sgn(val) == 0)
#define CANDL_notzero_p(val)           (mpz_sgn(val) != 0)

/******************************************************************************
 *                          CANDL BASIC TYPES MACROS                          *
 ******************************************************************************/
#else
/* Basic Macros */
#define CANDL_init(val)                ((val) = 0)
#define CANDL_assign(v1,v2)            ((v1)  = (v2))
#define CANDL_set_si(val,i)            ((val) = (Entier)(i))
#define CANDL_get_si(val)              ((val))
#define CANDL_clear(val)               ((val) = 0)
#define CANDL_print(Dst,fmt,val)       (fprintf((Dst),(fmt),(val)))

/* Boolean operators on 'Value' or 'Entier' */
#define CANDL_eq(v1,v2)                ((v1)==(v2))
#define CANDL_ne(v1,v2)                ((v1)!=(v2))

/* Binary operators on 'Value' or 'Entier' */
#define CANDL_increment(ref,val)       ((ref) = (val)+(Entier)(1))
#define CANDL_decrement(ref,val)       ((ref) = (val)-(Entier)(1))
#define CANDL_subtract(ref,val1,val2) ((ref) = (val1)-(val2))
#define CANDL_oppose(ref,val)          ((ref) = (-(val)))

/* Conditional operations on 'Value' or 'Entier' */
#define CANDL_zero_p(val)               CANDL_eq(val,0)
#define CANDL_notzero_p(val)            CANDL_ne(val,0)

#endif

#endif // !CANDL_MACROS_H