/*
 *  platforms/Cross/plugins/IA32ABI/ia32abi.h
 *
 *  Written by Eliot Miranda 11/2007.
 *	Updated 5/2011 to cope with Cog stack direction.
 *
 * Call foreign functions returning results in either %eax, %edx (Integral)
 * or %f0 (Float, Double).  
 *
 * The primitive will have signatures of the form
 *
 *	<Anywhere> primFFIResult: result <Alien> call: functionAddress <Alien>
 *	  with: firstArg <Alien> ... with: lastArg <Alien>
 *		<primitive: 'primCallOutXXX' module: 'IA32ABI'>
 *
 *	result <Alien> primFFICall: functionAddress <Alien>
 *	  with: firstArg <Alien> ... with: lastArg <Alien>
 *		<primitive: 'primCallOutXXX' module: 'IA32ABI'>
 *
 *	functionAddress <Alien> primFFICallResult: result <Alien>
 *	  with: firstArg <Alien> ... with: lastArg <Alien>
 *		<primitive: 'primCallOutXXX' module: 'IA32ABI'>
 *
 * N.B. In Cog Stack and Cogit VMs numArgs is negative to access args from
 * the downward-growing stack.
 */

#include "sqSetjmpShim.h"

#define SIGNATURE	sqInt *argVector/* call args on stack or in array */, \
					int numArgs,	/* arg count of function to call (*) */ \
					int funcOffset, /* stack offset of func Alien   */ \
					int resultOffset/* stack offset of result Alien */

extern sqInt callIA32IntegralReturn(SIGNATURE);
extern sqInt callIA32FloatReturn   (SIGNATURE);
extern sqInt callIA32DoubleReturn  (SIGNATURE);

#define thunkEntryType long
#define ifIsWithinExecutablePageMakePageWritable(address) 0
#define makePageExecutableAgain(address) 0

#if defined(i386) || defined(__i386) || defined(__i386__) || (defined(_WIN32) && !defined(_WIN64)) || defined(_M_IX86)
# define INT_REG_ARGS /* none */
# define DBL_REG_ARGS /* none */
#elif _WIN64 || defined(_M_X64) || defined(_M_AMD64) || defined(_WIN64)
# undef thunkEntryType
# define thunkEntryType long long
# define INT_REG_ARGS long long,long long,long long,long long,
# define DBL_REG_ARGS /* double,double,double,double, NOT INCLUDED because only 4 parameters are passed in registers, either int or float */
#elif defined(__amd64__) || defined(__x86_64__) || defined(__amd64) || defined(__x86_64)
# define INT_REG_ARGS long,long,long,long,long,long,
# define DBL_REG_ARGS double,double,double,double,double,double,double,double,
#elif defined(__powerpc__) || defined(PPC) || defined(_POWER) || defined(_IBMR2) || defined(__ppc__)
# define INT_REG_ARGS long,long,long,long,long,long,long,long,
# define DBL_REG_ARGS /* none */
#elif defined(__ARM_ARCH_ISA_A64) || defined(__arm64__) || defined(__aarch64__) || defined(ARM64)
# undef thunkEntryType
# define thunkEntryType long long
# define INT_REG_ARGS long,long,long,long,long,long,long,long,
# define DBL_REG_ARGS double,double,double,double,double,double,double,double,
# if __APPLE__
# undef ifIsWithinExecutablePageMakePageWritable
# undef makePageExecutableAgain
extern sqInt ifIsWithinExecutablePageMakePageWritable(char *address);
extern void makePageExecutableAgain(char *address);
# endif
#elif defined(__ARM_ARCH__) || defined(__arm__) || defined(__arm32__) || defined(ARM32)
# undef thunkEntryType
# define thunkEntryType long long
# define INT_REG_ARGS long,long,long,long,
# define DBL_REG_ARGS double,double,double,double,double,double,double,double,
#endif
extern thunkEntryType  thunkEntry (INT_REG_ARGS DBL_REG_ARGS void *,sqIntptr_t *);
extern void *allocateExecutablePage(sqIntptr_t *pagesize);
extern VMCallbackContext *getMostRecentCallbackContext(void);
#undef thunkEntryType
