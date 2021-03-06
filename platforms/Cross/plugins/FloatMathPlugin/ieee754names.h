/* Re-define all of the conflicting names of fdlibm to use __ieee754_ prefix */

#define asinh __ieee754_asinh

#define atan __ieee754_atan

#define cos __ieee754_cos

#define expm1 __ieee754_expm1

#define finite __ieee754_finite

#define ldexp __ieee754_ldexp

#define scalbn __ieee754_scalbn

#define log1p __ieee754_log1p

#define modf __ieee754_modf

#define rint __ieee754_rint

#define sqrt __ieee754_sqrt

#define sin __ieee754_sin

#define tan __ieee754_tan

#define tanh __ieee754_tanh

/* external declarations */
extern double __ieee754_atan(double);
extern double __ieee754_expm1(double);
extern int    __ieee754_finite(double);
extern double __ieee754_log1p(double);
extern double __ieee754_scalbn(double,int);
extern double __ieee754_sinh(double);
extern double copysign(double,double);
extern double fabs(double);
extern double floor(double);
extern int    isnan(double);
extern double rint(double);
