#pragma once

/** @file */

/////////////////////////////////////////////////////////////////////////////////////
// helper macros to define PUBLIC_EXPORT(DLL_NAME) and TEMPLATE_EXPORT(TEMPLATE_NAME)
/////////////////////////////////////////////////////////////////////////////////////

#define CONCAT(a, ...) a ## __VA_ARGS__

// If macro that takes in 0 for false and 1 for true.
// Usage: IFF(cond)(truebranch, falsebranch)
// This is meant to be used within other macros (preprocessor
// directives can't be used within macros).
#define IIF(c) CONCAT(IIF_, c)
#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t

// Workaround for horrible VS bug:
// http://connect.microsoft.com/VisualStudio/feedback/details/380090/variadic-macro-replacement
// http://stackoverflow.com/questions/21869917/visual-studio-va-args-issue
// Basically, VS expands __VA_ARGS__ as a single token instead of a list of tokens
#define INDIRECT_EXPAND_CHECK(x, args) x args

#define TAKE_SECOND(x, n, ...) n
// Takes the list of arguments, adds 0 at the end, then returns the
// second argument in the list. This allows detecting whether there is a non-zero
// second argument or not.
#define SPECIAL_CHECK(...) INDIRECT_EXPAND_CHECK(TAKE_SECOND, (__VA_ARGS__, 0, dummy))

// Takes a macro and return 1 if the macro expands to 1, returns 0 otherwise.
#define IS_TRUE(x) SPECIAL_CHECK(IS_TRUE_IMPL(x))
// IS_TRUE_IMPL will call IS_TRUE_IMPL_1 iff the argument expands to 1. In this
// case, IS_TRUE_IMPL_1 will expand to "dummy, 1", which will then return 1 when
// passed to SPECIAL_CHECK. If the argument doesn't expand to 1 (we assume it
// will either not expand at all, or expand to a single token), then IS_TRUE_IMPL_XXX
// will be passed to SPECIAL_CHECK, which will then return 0 (because there is only
// one argument.
#define IS_TRUE_IMPL(x) CONCAT(IS_TRUE_IMPL_,x)
// TAKE_SECOND of this will return 1 (true)
#define IS_TRUE_IMPL_1 dummy, 1


////////////////////////
// End of helper macros
////////////////////////



#if (_MSC_VER == 1800)
#define NOEXCEPT
#else
#define NOEXCEPT noexcept
#endif


#ifdef _WIN32
#include "AlgoWIN32Defs.H"
#else

#ifdef __rhel_x86_64__
#define GCC_EXPORT __attribute__ ((visibility ("default")))
#else
#define GCC_EXPORT
#endif

#define WIN32_EXPORT
#define EXPORT_VAR GCC_EXPORT

#define PUBLIC_EXPORT(DLL_NAME) GCC_EXPORT
#define TEMPLATE_EXPORT(TEMPLATE_NAME) \
    IIF(IS_TRUE(LOCAL_##TEMPLATE_NAME))( , GCC_EXPORT)

#ifndef DEPRECATED
#if (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__) >= 40900
#define DEPRECATED [[deprecated]]
#else
#define DEPRECATED __attribute__ ((deprecated))
#endif
#endif

// Size Specification of format used by printf, fprintf etc.
#define AP_PRIz "z" // for size_t or ssize_t

#endif // !Win32

