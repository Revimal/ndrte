#ifndef NDRTE_COMPILER_COMMON_H
#define NDRTE_COMPILER_COMMON_H

#define NDRTE_STRONG_INLINE inline __attribute__((always_inline))
#define NDRTE_ALIGN( value ) __attribute__((aligned(value)))

#define NDRTE_UOPTR( type ) \
    __volatile__ type *

#define ndrte_uoptr_set( var ) \
    ((NDRTE_UOPTR( typeof(var) ))&(var))

#define NDRTE_ACCESS_ONCE( var ) \
    (*ndrte_uoptr_set( var ))

#endif