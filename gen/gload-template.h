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
 *      #define GLOAD_VERBOSE
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables info/warning/error logging to standard-output/standard-error.
 *  
 *      #define GLOAD_VERBOSE_INFO
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables info-logging to standard-output/standard-error.
 *              Enabled by default if GLOAD_VERBOSE is defined.
 *
 *      #define GLOAD_VERBOSE_WARN
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables warning-logging to standard-output/standard-error.
 *              Enabled by default if GLOAD_VERBOSE is defined.
 *
 *      #define GLOAD_VERBOSE_ERROR
 *          - TYPE:
 *              OPTIONAL
 *          - DESCRIPTION:
 *              Enables error-logging to standard-output/standard-error.
 *              Enabled by default if GLOAD_VERBOSE is defined.
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

/* `gloadLoadGL`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.1) loading process.
 * 
 * `gloadLoadGL` auto-detects which backend should be used:
 * `GLX`, `EGL`, `WGL` or `built-in` (using either `dlopen` or `LoadLibraryA`, depending on the platform).
 *
 * \returns `true` on success, `false` on failure.
 * */
GLAPI int   gloadLoadGL(void);

/* `gloadLoadGL`:
 *
 * Unload OpenGL functions and dispose dynamic/shared object handle.
 * This function will execute anything if `gloadGetProcAddress` was used at least once;
 * for other backends (i.e. `GLX`, `EGL`, `WGL` and more) this function will simply return.
 *
 * \returns `true` on success, `false` on failure.
 * */
GLAPI int   gloadUnloadGL(void);

/* `gloadLoadGLLoader`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.1) loading process.
 * 
 * gloadLoadGLLoader expects a pointer to a `*GetProcAddress` function.
 * Most, if not all opengl-oriented libraries support the propper version of `*GetProcAddress`
 * and gload.h provides a built-in solution: `gloadGetProcAddress`.
 *
 * \param `t_gloadLoader load` - pointer to a loader function
 * \returns `true` on success, `false` on failure.
 * */
GLAPI int   gloadLoadGLLoader(t_gloadLoader);

/* `gloadGetProcAddress`:
 *
 * Retrieve the address of the OpenGL symbol from dynamic/shared object.
 * Uses `dlopen` and `dlsym` for GNU/Linux and MacOS platform.
 * Uses `LoadLibraryA` and `GetProcAddress` for Win32 platform.
 *
 * \param `const char *name` - name of the symbol
 * \returns address of the symbol on success, null on failure
 * */
GLAPI void  *gloadGetProcAddress(const char *);

/* SECTION:
 *  OpenGL API
 * * * * * * */

/* <<gload-typedef>> */

/* <<gload-enums>> */
/* <<gload-funcptr>> */
/* <<gload-declr-1>> */
/* <<gload-declr-2>> */
#
# if defined (__cplusplus)

}

# endif /* __cplusplus */
#
# if defined (GLOAD_IMPLEMENTATION)
#
#  if !defined (__cplusplus)
#   include <stdio.h>
#   include <stdint.h>
#   include <stddef.h>
#  else
#   include <cstdio>
#   include <cstdint>
#   include <cstddef>
#   include <string>
#  endif /* __cplusplus */
#
#  if defined (__linux__) || defined (__APPLE__)
#   include <dlfcn.h>
#  endif /* __linux__, __APPLE__ */
#  if defined (_WIN32)
#   include <libloaderapi.h>
#  endif /* _WIN32 */
#
#  if !defined (GLOAD_DLSYM) && !(defined (GLOAD_GLX) || defined (GLOAD_EGL) || defined (GLOAD_WGL))
#   define GLOAD_DLSYM 1
#  endif /* GLOAD_DLSYM, GLOAD_GLX, GLOAD_EGL, GLOAD_WGL */
#
#  if defined (GLOAD_DLSYM)
#   if defined (GLOAD_GLX)
#    error "Multiple backends selected: GLOAD_DLSYM and GLOAD_GLX."
#   endif /* GLOAD_GLX */
#   if defined (GLOAD_EGL)
#    error "Multiple backends selected: GLOAD_DLSYM and GLOAD_EGL."
#   endif /* GLOAD_EGL */
#   if defined (GLOAD_WGL)
#    error "Multiple backends selected: GLOAD_DLSYM and GLOAD_WGL."
#   endif /* GLOAD_WGL */
#  endif /* GLOAD_DLSYM */
#
#  if defined (GLOAD_GLX)
#   if defined (GLOAD_DLSYM)
#    error "Multiple backends selected: GLOAD_GLX and GLOAD_DLSYM."
#   endif /* GLOAD_DLSYM */
#   if defined (GLOAD_EGL)
#    error "Multiple backends selected: GLOAD_GLX and GLOAD_EGL."
#   endif /* GLOAD_EGL */
#   if defined (GLOAD_WGL)
#    error "Multiple backends selected: GLOAD_GLX and GLOAD_WGL."
#   endif /* GLOAD_WGL */
#
#   include <GL/glx.h>
#   include <GL/glxext.h>
#  endif /* GLOAD_GLX */
#
#  if defined (GLOAD_EGL)
#   if defined (GLOAD_DLSYM)
#    error "Multiple backends selected: GLOAD_EGL and GLOAD_DLSYM."
#   endif /* GLOAD_DLSYM */
#   if defined (GLOAD_GLX)
#    error "Multiple backends selected: GLOAD_EGL and GLOAD_GLX."
#   endif /* GLOAD_GLX */
#   if defined (GLOAD_WGL)
#    error "Multiple backends selected: GLOAD_EGL and GLOAD_WGL."
#   endif /* GLOAD_WGL */
#
#   include <EGL/egl.h>
#   include <EGL/eglext.h>
#  endif /* GLOAD_EGL */
#
#  if defined (GLOAD_WGL)
#   if defined (GLOAD_DLSYM)
#    error "Multiple backends selected: GLOAD_WGL and GLOAD_DLSYM."
#   endif /* GLOAD_DLSYM */
#   if defined (GLOAD_GLX)
#    error "Multiple backends selected: GLOAD_WGL and GLOAD_GLX."
#   endif /* GLOAD_EGL */
#   if defined (GLOAD_WGL)
#    error "Multiple backends selected: GLOAD_WGL and GLOAD_WGL."
#   endif /* GLOAD_WGL */
#
#   include <wingdi.h>
#  endif /* GLOAD_WGL */
#
#  if defined (GLOAD_VERBOSE)
#   define GLOAD_VERBOSE_INFO 1
#   define GLOAD_VERBOSE_WARN 1
#   define GLOAD_VERBOSE_ERROR 1
#  endif /* GLOAD_VERBOSE */
#
#  if defined (__cplusplus)

extern "C" {

#  endif /* __cplusplus */
    
/* SECTION:
 *  Global objects
 * * * * * * * * * * */

/* s_nameaddr - key-value-pair structure of proc. names and addresses. */
/* g_nameaddr - array of s_nameaddr structures, null-terminated. */

struct s_nameaddr {

#  if !defined (__cplusplus)
    const char          *name;
#  else
    const std::string   &name;
#  endif /* __cplusplus */

    void        **addr;
};

static struct s_nameaddr    g_nameaddr[] = {
    
/* <<gload-nameaddr>> */

    { 0, 0 }
};

/* g_handle - handle to shared/dynamic library. */    
static void *g_handle = 0;

/* SECTION:
 *  gload API
 * * * * * * * * * * */

/* `gloadLoadGL`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.1) loading process.
 * 
 * `gloadLoadGL` auto-detects which backend should be used:
 * `GLX`, `EGL`, `WGL` or `built-in` (using either `dlopen` or `LoadLibraryA`, depending on the platform).
 *
 * \returns `true` on success, `false` on failure.
 * */
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

/* `gloadLoadGL`:
 *
 * Unload OpenGL functions and dispose dynamic/shared object handle.
 * This function will execute anything if `gloadGetProcAddress` was used at least once;
 * for other backends (i.e. `GLX`, `EGL`, `WGL` and more) this function will simply return.
 *
 * \returns `true` on success, `false` on failure.
 * */
GLAPI int   gloadUnloadGL(void) {
    if (g_handle) {

#  if defined (__linux__) || defined (__APPLE__)
        dlclose(g_handle), g_handle = 0;
#  endif /* __linux__, __APPLE__ */
#  if defined (_WIN32)
        FreeLibrary(g_handle), g_handle = 0;
#  endif /* _WIN32 */

    }

    return (1);
}

/* `gloadLoadGLLoader`:
 *
 * Perform a simple OpenGL (v.1.0 - v.4.6) and OpenGLES (v.1.0 - v.3.1) loading process.
 * 
 * gloadLoadGLLoader expects a pointer to a `*GetProcAddress` function.
 * Most, if not all opengl-oriented libraries support the propper version of `*GetProcAddress`
 * and gload.h provides a built-in solution: `gloadGetProcAddress`.
 *
 * \param `t_gloadLoader load` - pointer to a loader function
 * \returns `true` on success, `false` on failure.
 * */
GLAPI int   gloadLoadGLLoader(t_gloadLoader load) {
    if (!load) { return (0); }
    for (size_t i = 0; g_nameaddr[i].addr; i++) {
        /* If the function is already loaded, skip it... */
        if (*g_nameaddr[i].addr) { continue; }

#  if !defined (__cplusplus)
        *g_nameaddr[i].addr = load(g_nameaddr[i].name);
#  else
        *g_nameaddr[i].addr = load(g_nameaddr[i].name.c_str());
#  endif /* __cplusplus */

        if (!*g_nameaddr[i].addr) { return (0); }
    }

    return (1);
}

/* `gloadGetProcAddress`:
 *
 * Retrieve the address of the OpenGL symbol from dynamic/shared object.
 * Uses `dlopen` and `dlsym` for GNU/Linux and MacOS platform.
 * Uses `LoadLibraryA` and `GetProcAddress` for Win32 platform.
 *
 * \param `const char *name` - name of the symbol
 * \returns address of the symbol on success, null on failure
 * */
GLAPI void  *gloadGetProcAddress(const char *name) {
    void        *proc;
    const char  *names[] = {

#  if defined (__linux__)
        "libGL.so",
        "libGL.so.1",
        "libGL.so.1.7.0",
        0
#  endif /* __linux__ */
#  if defined (__APPLE__)
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
        0
#  endif /* __APPLE__ */
#  if defined (_WIN32)
        "opengl32.dll",
        0
#  endif /* _WIN32 */

    };
    
    if (!g_handle) {
        for (size_t i = 0; !g_handle && names[i]; i++) {

#  if defined (__linux__) || defined (__APPLE__)
            g_handle = dlopen(names[i], RTLD_NOW | RTLD_GLOBAL);
#  endif /* __linux__, __APPLE__ */
#  if defined (_WIN32)
            g_handle = LoadLibraryA(names[i]);
#  endif /* _WIN32 */

        }

        if (!g_handle) {

#  if defined (GLOAD_VERBOSE_ERROR)
            fprintf(stderr, "gload.h: could not load an OpenGL handle.\n");
#  endif /* GLOAD_VERBOSE_ERROR */

            return (0);

        }
    }

#  if defined (__linux__) || defined (__APPLE__)
    proc = dlsym(g_handle, name);
#  endif /* __linux__, __APPLE__ */
#  if defined (_WIN32)
    proc = GetProcAddress(g_handle, name);
#  endif /* _WIN32 */

    if (!proc) {

#  if defined (GLOAD_VERBOSE_ERROR)
            fprintf(stderr, "gload.h: could not load a procedure: %s\n", name);
#  endif /* GLOAD_VERBOSE_ERROR */
    
            return (0);
    }
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
