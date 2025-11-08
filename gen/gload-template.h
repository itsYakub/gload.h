/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  gload.h: OpenGL API Loader:
 *
 *      - version: <<gload-version>>
 *      - made by: <<gload-author>>
 *      - licence: <<gload-licence>>
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_opengl_loader_h_)
#
# if defined (__gl_h_)
#  error "#include <GL/gl.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gl_h_ */
# if defined (__gl_glext_h_)
#  error "#include <GL/glext.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gl_glext_h_ */
# if defined (__gl_glcorearb_h_)
#  error "#include <GL/glcorearb.h> detected. To ensure a proper usage of this loader, remove the include."
# endif /* __gl_glcorearb_h_ */
#
# define _opengl_loader_h_ 1
# define __gl_h_ 1
# define __gl_glext_h_ 1
# define __gl_glcorearb_h_ 1
#
# if defined (__cplusplus)

extern "C" {

# endif /* __cplusplus */
#
# if defined (_WIN32) && !defined (APIENTRY) && !defined (__CYGWIN__) && !defined (__SCITECH_SNAP__)
#  if !defined (WIN32_LEAN_AND_MEAN)
#   define WIN32_LEAN_AND_MEAN 1
#  endif /* WIN32_LEAN_AND_MEAN */
#  include <windows.h>
# endif /* _WIN32, APIENTRY, __CYGWIN__, __SCITECH_SNAP__ */
#
# if !defined (APIENTRY)
#  define APIENTRY
# endif /* APIENTRY */
# if !defined (APIENTRYP)
#  define APIENTRYP APIENTRY *
# endif /* APIENTRYP */
# if !defined (GLAPI)
#  define GLAPI extern
# endif /* GLAPI */
#
#include <stdint.h>
#include <stddef.h>
#
<<gload-version-macro>>

/* SECTION:
 *  gload API
 * * * * * * * * * * */

typedef void    *(*t_gloadLoader)(const char *);

GLAPI int   gloadLoadGL(void);
GLAPI int   gloadLoadGLLoader(t_gloadLoader);

/* SECTION:
 *  OpenGL API
 * * * * * * */

<<gload-typedef>>

<<gload-enums>>
<<gload-funcptr>>
<<gload-declr-1>>
<<gload-declr-2>>



# if defined (__cplusplus)

}

# endif /* __cplusplus */
#
# if defined (GLOAD_IMPLEMENTATION)
#
#  if defined (__linux__)
#   include <GL/glx.h>
#   include <GL/glxext.h>
#  endif /* __linux__ */
#  if defined (_WIN32)
#   include <windows.h>
#  endif /* _WIN32 */
#
#  if defined (__cplusplus)

extern "C" {

#  endif /* __cplusplus */

/* SECTION:
 *  gload API
 * * * * * * * * * * */

GLAPI int   gloadLoadGL(void) {

#  if defined (__linux__)
    return (gloadLoadGLLoader((t_gloadLoader) glXGetProcAddress));
#  endif /* __linux__ */
#  if defined (_WIN32)
    return (gloadLoadGLLoader((t_gloadLoader) wglGetProcAddress));
#  endif /* _WIN32 */

}

GLAPI int   gloadLoadGLLoader(t_gloadLoader load) {

<<gload-loadfunc>>

    return (1);
}

/* SECTION:
 *  OpenGL API
 * * * * * * */

<<gload-declr-0>>
#
#  if defined (__cplusplus)

}

#  endif /* __cplusplus */
#
# endif /* OPENGL_IMPLEMENTATION */
#endif /* _opengl_loader_h_ */
