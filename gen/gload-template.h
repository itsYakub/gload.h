/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  gload.h: OpenGL API Loader:
 *
 *      - version: <<gload-version>>
 *      - made by: <<gload-author>>
 *      - licence: <<gload-licence>>
 *
 *
 *
 *  Configuration:
 *
 *      #define GLOAD_IMPLEMENTATION
 *          - TYPE:
 *              MANDATORY
 *          - DESCRIPTION:
 *              Embed the implementation section of the library into the source file.
 *              NOTE:
 *                  This should be defined only once in the entire codebase.
 *                  Otherwise, defining this option will cause a multiple-definitions error.
 *
 *      #define GLOAD_GLX
 *          - TYPE:
 *              OPTIONAL 
 *          - DESCRIPTION:
 *              Enforce the usage of GLX for context loading.
 *              NOTE:
 *                  gload.h doesn't load GLX dynamically. For this flag to work you must
 *                  link your program with GLX library (libGLX.so: -lGLX).
 *
 *      #define GLOAD_EGL
 *          - TYPE:
 *              OPTIONAL 
 *          - DESCRIPTION:
 *              Enforce the usage of EGL for context loading.
 *              NOTE:
 *                  gload.h doesn't load EGL dynamically. For this flag to work you must
 *                  link your program with EGL library (libEGL.so: -lEGL).
 *
 *      #define GLOAD_WGL
 *          - TYPE:
 *              OPTIONAL 
 *          - DESCRIPTION:
 *              Enforce the usage of Windows's WGL for context loading.
 *              NOTE:
 *                  gload.h doesn't load WGL dynamically. For this flag to work you must
 *                  link your program with WGL library (Windows GDI: -lgdi32) (OpenGL32.dll: -lopengl32).
 *
 *      #define GLOAD_DLSYM
 *          - TYPE:
 *              OPTIONAL (DEFINED BY DEFAULT) 
 *          - DESCRIPTION:
 *              Default, platform-independent option for loading OpenGL. Defined by default.
 *              NOTE:
 *                  This solution may require the linkage with dynamic linking library.
 *                  For unix-based system it would be: libdl, -ldl.
 *                  For win32 system: Kernel32.dll.
 *
 *  
 *
 *  Summary and Notes:
 *
 *      This is gload.h: single-header only OpenGL loader for Windows, MacOS and Linux systems.
 *      The goal of this library is simple: provide users with drag-n-drop solution for loading
 *      legacy and modern OpenGL functions, including OpenGLES1, OpenGLES2 and OpenGLES3.
 *
 *      gload.h is generated based on the OpenGL Registry for core and compatibility profiles,
 *      hosted by KhronosGroup on their github account:
 *      - https://github.com/KhronosGroup/OpenGL-Registry.git
 *
 *      But you'd ask: "Why would you create another OpenGL loader when we have glad, glut, glew...?".
 *      Well, the answer is pretty simple:
*
 *      - I wrote an OpenGL loader in the past: glapi.h. I wasn't completely happy with it,
 *        python script was clumsy, templating sucked and a lot more problems.
 *        I wanted to start fresh, with experience from the past and with inspiration from other projects.
 *
 *      - I was curious why do we need OpenGL loaders in the first place:
 *        I wanted to learn why, or even is it necessary to use loaders in the first place.
 *        I've even looked through libGL.so file looking at the symbols stored in it,
 *        figuring out why should I use, for example, glad instead of classing linking (-lGL).
 *        The answer is pretty simple:
 *
 *        - OpenGL is a specification, not a library by itself. Implementation for the specification is left
 *          to the GPU vendor like nVidia or AMD;
 *        - Leaving an implementation to the GPU vendor allows us to easily switch between implementations
 *          if we so desire;
 *        - Actually, there's a possibility of using modern OpenGL functions by just linking with the .so file.
 *          It is risky however, as the implementation doesn't have to live there. Implementation is guaranteed
 *          to live in the GPU space, that's why it's safer to use loaders.
 *
 *      - It is a nice exercise of building a propper library and practicing python scripting.
 *        Especially if we'd like to create such a project with as little dependencies as possible.
 *        This project is solely dependent on these few external resources:
 *        - C/C++ standard library;
 *        - python's standard library;
 *        - OpenGL Registry provided by KhronosGroup.
 *        
 *      This project is heavily inspired by the following projects:
 *      - nothings/stb: https://github.com/nothings/stb.git
 *      - Dav1dde/glad: https://github.com/Dav1dde/glad.git
 *      - macron/glbind: https://github.com/mackron/glbind.git
 *      - KhronosGroup/OpenGL-Registry: https://github.com/KhronosGroup/OpenGL-Registry.git
 *
 *      Cheers,
 *          <<gload-author>>
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#if defined (__cplusplus)
# pragma once
#endif /* __cplusplus */
#
#if !defined (_gload_h_)
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
# define _gload_h_ 1
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
/* <<gload-version-macro>> */

/* SECTION:
 *  gload API
 * * * * * * * * * * */

typedef void    *(*t_gloadLoader)(const char *);

GLAPI int   gloadLoadGL(void);
GLAPI int   gloadLoadGLLoader(t_gloadLoader);

GLAPI void  *gloadGetProcAddress(const char *);

/* SECTION:
 *  OpenGL API
 * * * * * * */

/* <<gload-typedef>> */

/* <<gload-enums>> */
/* <<gload-funcptr>> */
/* <<gload-declr-1>> */
/* <<gload-declr-2>> */



# if defined (__cplusplus)

}

# endif /* __cplusplus */
#
# if defined (GLOAD_IMPLEMENTATION)
#
#  include <stdint.h>
#  include <stddef.h>
#
#  if !defined (GLOAD_DLSYM) && !(defined (GLOAD_GLX) || defined (GLOAD_EGL) || defined (GLOAD_WGL))
#   define GLOAD_DLSYM 1
#  endif /* GLOAD_DLSYM, GLOAD_GLX, GLOAD_EGL, GLOAD_WGL */

#  if defined (GLOAD_DLSYM)
#   undef GLOAD_GLX
#   undef GLOAD_GLX
#   undef GLOAD_EGL
#   if defined (__linux__) || defined (__unix__)
#    include <dlfcn.h>
#   endif /* __linux__, __unix__ */
#
#   if defined (_WIN32)
#    include <libloaderapi.h>
#   endif /* _WIN32 */
#  endif /* GLOAD_DLSYM */
#
#  if defined (GLOAD_GLX)
#   include <GL/glx.h>
#   include <GL/glxext.h>
#  endif /* GLOAD_GLX */
#
#  if defined (GLOAD_EGL)
#   include <EGL/egl.h>
#   include <EGL/eglext.h>
#  endif /* GLOAD_EGL */
#
#  if defined (GLOAD_WGL)
#   include <wingdi.h>
#  endif /* GLOAD_WGL */
#
#  if defined (__cplusplus)

extern "C" {

#  endif /* __cplusplus */
    
/* SECTION:
 *  Global objects
 * * * * * * * * * * */

static void *g_handle = 0;

/* SECTION:
 *  gload API
 * * * * * * * * * * */

GLAPI int   gloadLoadGL(void) {

#  if defined (GLOAD_GLX)
    return (gloadLoadGLLoader((t_gloadLoader) glXGetProcAddress));
#  endif /* GLOAD_GLX */
#  if defined (GLOAD_EGL)
    return (gloadLoadGLLoader((t_gloadLoader) eglGetProcAddress));
#  endif /* GLOAD_EGL */
#  if defined (GLOAD_WGL)
    return (gloadLoadGLLoader((t_gloadLoader) wglGetProcAddress));
#  endif /* GLOAD_WGL */
#  if defined (GLOAD_DLSYM)
    return (gloadLoadGLLoader((t_gloadLoader) gloadGetProcAddress));
#  endif /* GLOAD_DLSYM */

}

GLAPI int   gloadLoadGLLoader(t_gloadLoader load) {

/* <<gload-loadfunc>> */

    return (1);
}

GLAPI void  *gloadGetProcAddress(const char *name) {
    void    *proc;
    
#  if defined (__linux__) || defined (__APPLE__)

    const char  *names[] = {

#   if defined (__linux__)

        "libGL.so",
        "libGL.so.1",
        "libGL.so.1.7.0",
        0

#   endif /* __linux__ */
#   if defined (__APPLE__)

        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
        0

#   endif /* __APPLE__ */

    };
    
    if (!g_handle) {
        for (size_t i = 0; !g_handle && names[i]; i++) {
            g_handle = dlopen(names[i], RTLD_NOW | RTLD_GLOBAL);
        }

        if (!g_handle) { return (0); }
    }

    proc = dlsym(g_handle, name);
    if (!proc) { return (0); }


#  endif /* __linux__, __APPLE__ */
#  if defined (_WIN32)

    const char  *names[] = {
        "opengl32.dll"
        0
    };

    if (!g_handle) {
        for (size_t i = 0; !g_handle && names[i]; i++) {
            g_handle = LoadLibraryA(names[i]);
        }

        if (!g_handle) { return (0); }
    }
    
    proc = GetProcAddress(g_handle, name);
    if (!proc) { return (0); }

#  endif /* _WIN32 */

    return (proc);
}

/* SECTION:
 *  OpenGL API
 * * * * * * */

/* <<gload-declr-0>> */
#
#  if defined (__cplusplus)

}

#  endif /* __cplusplus */
#
# endif /* OPENGL_IMPLEMENTATION */
#endif /* _gload_h_ */
