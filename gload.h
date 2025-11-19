/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 *  gload.h: OpenGL API Loader:
 *
 *      - version: 1.1
 *      - made by: Jakub Oleksiak (yakubofficialmail@gmail.com)
 *      - licence: GNU LESSER GENERAL PUBLIC LICENSE Version 3, 29 June 2007
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
 *  Constants:
 *
 *      GLOAD_PLATFORM
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Name of the platform gload.h is used on as a string, compile detected.
 *
 *      GLOAD_VERSION
 *          - TYPE:
 *              String
 *          - DESCRIPTION:
 *              Current version of gload.h header file as a string.
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
 *
 *      Cheers,
 *          Jakub Oleksiak (yakubofficialmail@gmail.com)
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
# if defined (__linux__)
#  define GLOAD_LINUX 1
#  define GLOAD_PLATFORM "linux"
# endif /* __linux__ */
# if defined (__APPLE__)
#  define GLOAD_APPLE 1
#  define GLOAD_PLATFORM "apple"
# endif /* __APPLE__ */
# if defined (_WIN32)
#  define GLOAD_WIN32 1
#  define GLOAD_PLATFORM "win32"
# endif /* _WIN32 */
# if !defined (GLOAD_LINUX) && !defined (GLOAD_APPLE) && !defined (GLOAD_WIN32)
#  error "Unrecognized platform. Neither GNU/Linux, nor Apple, nor Win32 platforms were detected."
# endif /* GLOAD_LINUX, GLOAD_APPLE, GLOAD_WIN32 */
#
# if !defined GLOAD_VERSION
#  define GLOAD_VERSION "1.1"
# endif /* GLOAD_VERSION */
#
#  define GL_VERSION_1_0 1
#  define GL_VERSION_1_1 1
#  define GL_VERSION_1_2 1
#  define GL_VERSION_1_3 1
#  define GL_VERSION_1_4 1
#  define GL_VERSION_1_5 1
#  define GL_VERSION_2_0 1
#  define GL_VERSION_2_1 1
#  define GL_VERSION_3_0 1
#  define GL_VERSION_3_1 1
#  define GL_VERSION_3_2 1
#  define GL_VERSION_3_3 1
#  define GL_VERSION_4_0 1
#  define GL_VERSION_4_1 1
#  define GL_VERSION_4_2 1
#  define GL_VERSION_4_3 1
#  define GL_VERSION_4_4 1
#  define GL_VERSION_4_5 1
#  define GL_VERSION_4_6 1
#  define GL_VERSION_ES_CM_1_0 1
#  define GL_ES_VERSION_2_0 1
#  define GL_ES_VERSION_3_0 1
#  define GL_ES_VERSION_3_1 1
#  define GL_ES_VERSION_3_2 1
#  define GL_SC_VERSION_2_0 1

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
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   gloadLoadGL(void);

/* `gloadLoadGL`:
 *
 * Unload OpenGL functions and dispose dynamic/shared object handle.
 * This function will execute anything if `gloadGetProcAddress` was used at least once;
 * for other backends (i.e. `GLX`, `EGL`, `WGL` and more) this function will simply return.
 *
 * - return: `true` on success, `false` on failure.
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
 * - param: `t_gloadLoader load` - pointer to a loader function
 * - return: `true` on success, `false` on failure.
 * */
GLAPI int   gloadLoadGLLoader(t_gloadLoader);

/* `gloadGetProcAddress`:
 *
 * Retrieve the address of the OpenGL symbol from dynamic/shared object.
 * Uses `dlopen` and `dlsym` for GNU/Linux and MacOS platform.
 * Uses `LoadLibraryA` and `GetProcAddress` for Win32 platform.
 *
 * - param: `const char *name` - name of the symbol
 * - returns: address of the symbol on success, null on failure
 * */
GLAPI void  *gloadGetProcAddress(const char *);

/* SECTION:
 *  OpenGL API
 * * * * * * */

# include <KHR/khrplatform.h>
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef void GLvoid;
typedef khronos_int8_t GLbyte;
typedef khronos_uint8_t GLubyte;
typedef khronos_int16_t GLshort;
typedef khronos_uint16_t GLushort;
typedef int GLint;
typedef unsigned int GLuint;
typedef khronos_int32_t GLclampx;
typedef int GLsizei;
typedef khronos_float_t GLfloat;
typedef khronos_float_t GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void *GLeglClientBufferEXT;
typedef void *GLeglImageOES;
typedef char GLchar;
typedef char GLcharARB;

# if defined (__APPLE__)
typedef void *GLhandleARB;
# else
typedef unsigned int GLhandleARB;
# endif /* __APPLE__ */

typedef khronos_uint16_t GLhalf;
typedef khronos_uint16_t GLhalfARB;
typedef khronos_int32_t GLfixed;
typedef khronos_intptr_t GLintptr;
typedef khronos_intptr_t GLintptrARB;
typedef khronos_ssize_t GLsizeiptr;
typedef khronos_ssize_t GLsizeiptrARB;
typedef khronos_int64_t GLint64;
typedef khronos_int64_t GLint64EXT;
typedef khronos_uint64_t GLuint64;
typedef khronos_uint64_t GLuint64EXT;
typedef struct __GLsync *GLsync;
struct _cl_context;
struct _cl_event;
typedef void (APIENTRY *GLDEBUGPROC)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (APIENTRY *GLDEBUGPROCARB)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (APIENTRY *GLDEBUGPROCKHR)(GLenum source,GLenum type,GLuint id,GLenum severity,GLsizei length,const GLchar *message,const void *userParam);
typedef void (APIENTRY *GLDEBUGPROCAMD)(GLuint id,GLenum category,GLenum severity,GLsizei length,const GLchar *message,void *userParam);
typedef unsigned short GLhalfNV;
typedef GLintptr GLvdpauSurfaceNV;
typedef void (APIENTRY *GLVULKANPROCNV)(void);

# if defined GL_VERSION_1_0
# 
#  define GL_DEPTH_BUFFER_BIT 0x00000100
#  define GL_STENCIL_BUFFER_BIT 0x00000400
#  define GL_COLOR_BUFFER_BIT 0x00004000
#  define GL_FALSE 0
#  define GL_TRUE 1
#  define GL_POINTS 0x0000
#  define GL_LINES 0x0001
#  define GL_LINE_LOOP 0x0002
#  define GL_LINE_STRIP 0x0003
#  define GL_TRIANGLES 0x0004
#  define GL_TRIANGLE_STRIP 0x0005
#  define GL_TRIANGLE_FAN 0x0006
#  define GL_QUADS 0x0007
#  define GL_NEVER 0x0200
#  define GL_LESS 0x0201
#  define GL_EQUAL 0x0202
#  define GL_LEQUAL 0x0203
#  define GL_GREATER 0x0204
#  define GL_NOTEQUAL 0x0205
#  define GL_GEQUAL 0x0206
#  define GL_ALWAYS 0x0207
#  define GL_ZERO 0
#  define GL_ONE 1
#  define GL_SRC_COLOR 0x0300
#  define GL_ONE_MINUS_SRC_COLOR 0x0301
#  define GL_SRC_ALPHA 0x0302
#  define GL_ONE_MINUS_SRC_ALPHA 0x0303
#  define GL_DST_ALPHA 0x0304
#  define GL_ONE_MINUS_DST_ALPHA 0x0305
#  define GL_DST_COLOR 0x0306
#  define GL_ONE_MINUS_DST_COLOR 0x0307
#  define GL_SRC_ALPHA_SATURATE 0x0308
#  define GL_NONE 0
#  define GL_FRONT_LEFT 0x0400
#  define GL_FRONT_RIGHT 0x0401
#  define GL_BACK_LEFT 0x0402
#  define GL_BACK_RIGHT 0x0403
#  define GL_FRONT 0x0404
#  define GL_BACK 0x0405
#  define GL_LEFT 0x0406
#  define GL_RIGHT 0x0407
#  define GL_FRONT_AND_BACK 0x0408
#  define GL_NO_ERROR 0
#  define GL_INVALID_ENUM 0x0500
#  define GL_INVALID_VALUE 0x0501
#  define GL_INVALID_OPERATION 0x0502
#  define GL_OUT_OF_MEMORY 0x0505
#  define GL_CW 0x0900
#  define GL_CCW 0x0901
#  define GL_POINT_SIZE 0x0B11
#  define GL_POINT_SIZE_RANGE 0x0B12
#  define GL_POINT_SIZE_GRANULARITY 0x0B13
#  define GL_LINE_SMOOTH 0x0B20
#  define GL_LINE_WIDTH 0x0B21
#  define GL_LINE_WIDTH_RANGE 0x0B22
#  define GL_LINE_WIDTH_GRANULARITY 0x0B23
#  define GL_POLYGON_MODE 0x0B40
#  define GL_POLYGON_SMOOTH 0x0B41
#  define GL_CULL_FACE 0x0B44
#  define GL_CULL_FACE_MODE 0x0B45
#  define GL_FRONT_FACE 0x0B46
#  define GL_DEPTH_RANGE 0x0B70
#  define GL_DEPTH_TEST 0x0B71
#  define GL_DEPTH_WRITEMASK 0x0B72
#  define GL_DEPTH_CLEAR_VALUE 0x0B73
#  define GL_DEPTH_FUNC 0x0B74
#  define GL_STENCIL_TEST 0x0B90
#  define GL_STENCIL_CLEAR_VALUE 0x0B91
#  define GL_STENCIL_FUNC 0x0B92
#  define GL_STENCIL_VALUE_MASK 0x0B93
#  define GL_STENCIL_FAIL 0x0B94
#  define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#  define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#  define GL_STENCIL_REF 0x0B97
#  define GL_STENCIL_WRITEMASK 0x0B98
#  define GL_VIEWPORT 0x0BA2
#  define GL_DITHER 0x0BD0
#  define GL_BLEND_DST 0x0BE0
#  define GL_BLEND_SRC 0x0BE1
#  define GL_BLEND 0x0BE2
#  define GL_LOGIC_OP_MODE 0x0BF0
#  define GL_DRAW_BUFFER 0x0C01
#  define GL_READ_BUFFER 0x0C02
#  define GL_SCISSOR_BOX 0x0C10
#  define GL_SCISSOR_TEST 0x0C11
#  define GL_COLOR_CLEAR_VALUE 0x0C22
#  define GL_COLOR_WRITEMASK 0x0C23
#  define GL_DOUBLEBUFFER 0x0C32
#  define GL_STEREO 0x0C33
#  define GL_LINE_SMOOTH_HINT 0x0C52
#  define GL_POLYGON_SMOOTH_HINT 0x0C53
#  define GL_UNPACK_SWAP_BYTES 0x0CF0
#  define GL_UNPACK_LSB_FIRST 0x0CF1
#  define GL_UNPACK_ROW_LENGTH 0x0CF2
#  define GL_UNPACK_SKIP_ROWS 0x0CF3
#  define GL_UNPACK_SKIP_PIXELS 0x0CF4
#  define GL_UNPACK_ALIGNMENT 0x0CF5
#  define GL_PACK_SWAP_BYTES 0x0D00
#  define GL_PACK_LSB_FIRST 0x0D01
#  define GL_PACK_ROW_LENGTH 0x0D02
#  define GL_PACK_SKIP_ROWS 0x0D03
#  define GL_PACK_SKIP_PIXELS 0x0D04
#  define GL_PACK_ALIGNMENT 0x0D05
#  define GL_MAX_TEXTURE_SIZE 0x0D33
#  define GL_MAX_VIEWPORT_DIMS 0x0D3A
#  define GL_SUBPIXEL_BITS 0x0D50
#  define GL_TEXTURE_1D 0x0DE0
#  define GL_TEXTURE_2D 0x0DE1
#  define GL_TEXTURE_WIDTH 0x1000
#  define GL_TEXTURE_HEIGHT 0x1001
#  define GL_TEXTURE_BORDER_COLOR 0x1004
#  define GL_DONT_CARE 0x1100
#  define GL_FASTEST 0x1101
#  define GL_NICEST 0x1102
#  define GL_BYTE 0x1400
#  define GL_UNSIGNED_BYTE 0x1401
#  define GL_SHORT 0x1402
#  define GL_UNSIGNED_SHORT 0x1403
#  define GL_INT 0x1404
#  define GL_UNSIGNED_INT 0x1405
#  define GL_FLOAT 0x1406
#  define GL_STACK_OVERFLOW 0x0503
#  define GL_STACK_UNDERFLOW 0x0504
#  define GL_CLEAR 0x1500
#  define GL_AND 0x1501
#  define GL_AND_REVERSE 0x1502
#  define GL_COPY 0x1503
#  define GL_AND_INVERTED 0x1504
#  define GL_NOOP 0x1505
#  define GL_XOR 0x1506
#  define GL_OR 0x1507
#  define GL_NOR 0x1508
#  define GL_EQUIV 0x1509
#  define GL_INVERT 0x150A
#  define GL_OR_REVERSE 0x150B
#  define GL_COPY_INVERTED 0x150C
#  define GL_OR_INVERTED 0x150D
#  define GL_NAND 0x150E
#  define GL_SET 0x150F
#  define GL_TEXTURE 0x1702
#  define GL_COLOR 0x1800
#  define GL_DEPTH 0x1801
#  define GL_STENCIL 0x1802
#  define GL_STENCIL_INDEX 0x1901
#  define GL_DEPTH_COMPONENT 0x1902
#  define GL_RED 0x1903
#  define GL_GREEN 0x1904
#  define GL_BLUE 0x1905
#  define GL_ALPHA 0x1906
#  define GL_RGB 0x1907
#  define GL_RGBA 0x1908
#  define GL_POINT 0x1B00
#  define GL_LINE 0x1B01
#  define GL_FILL 0x1B02
#  define GL_KEEP 0x1E00
#  define GL_REPLACE 0x1E01
#  define GL_INCR 0x1E02
#  define GL_DECR 0x1E03
#  define GL_VENDOR 0x1F00
#  define GL_RENDERER 0x1F01
#  define GL_VERSION 0x1F02
#  define GL_EXTENSIONS 0x1F03
#  define GL_NEAREST 0x2600
#  define GL_LINEAR 0x2601
#  define GL_NEAREST_MIPMAP_NEAREST 0x2700
#  define GL_LINEAR_MIPMAP_NEAREST 0x2701
#  define GL_NEAREST_MIPMAP_LINEAR 0x2702
#  define GL_LINEAR_MIPMAP_LINEAR 0x2703
#  define GL_TEXTURE_MAG_FILTER 0x2800
#  define GL_TEXTURE_MIN_FILTER 0x2801
#  define GL_TEXTURE_WRAP_S 0x2802
#  define GL_TEXTURE_WRAP_T 0x2803
#  define GL_REPEAT 0x2901
#  define GL_CURRENT_BIT 0x00000001
#  define GL_POINT_BIT 0x00000002
#  define GL_LINE_BIT 0x00000004
#  define GL_POLYGON_BIT 0x00000008
#  define GL_POLYGON_STIPPLE_BIT 0x00000010
#  define GL_PIXEL_MODE_BIT 0x00000020
#  define GL_LIGHTING_BIT 0x00000040
#  define GL_FOG_BIT 0x00000080
#  define GL_ACCUM_BUFFER_BIT 0x00000200
#  define GL_VIEWPORT_BIT 0x00000800
#  define GL_TRANSFORM_BIT 0x00001000
#  define GL_ENABLE_BIT 0x00002000
#  define GL_HINT_BIT 0x00008000
#  define GL_EVAL_BIT 0x00010000
#  define GL_LIST_BIT 0x00020000
#  define GL_TEXTURE_BIT 0x00040000
#  define GL_SCISSOR_BIT 0x00080000
#  define GL_ALL_ATTRIB_BITS 0xFFFFFFFF
#  define GL_QUAD_STRIP 0x0008
#  define GL_POLYGON 0x0009
#  define GL_ACCUM 0x0100
#  define GL_LOAD 0x0101
#  define GL_RETURN 0x0102
#  define GL_MULT 0x0103
#  define GL_ADD 0x0104
#  define GL_AUX0 0x0409
#  define GL_AUX1 0x040A
#  define GL_AUX2 0x040B
#  define GL_AUX3 0x040C
#  define GL_2D 0x0600
#  define GL_3D 0x0601
#  define GL_3D_COLOR 0x0602
#  define GL_3D_COLOR_TEXTURE 0x0603
#  define GL_4D_COLOR_TEXTURE 0x0604
#  define GL_PASS_THROUGH_TOKEN 0x0700
#  define GL_POINT_TOKEN 0x0701
#  define GL_LINE_TOKEN 0x0702
#  define GL_POLYGON_TOKEN 0x0703
#  define GL_BITMAP_TOKEN 0x0704
#  define GL_DRAW_PIXEL_TOKEN 0x0705
#  define GL_COPY_PIXEL_TOKEN 0x0706
#  define GL_LINE_RESET_TOKEN 0x0707
#  define GL_EXP 0x0800
#  define GL_EXP2 0x0801
#  define GL_COEFF 0x0A00
#  define GL_ORDER 0x0A01
#  define GL_DOMAIN 0x0A02
#  define GL_PIXEL_MAP_I_TO_I 0x0C70
#  define GL_PIXEL_MAP_S_TO_S 0x0C71
#  define GL_PIXEL_MAP_I_TO_R 0x0C72
#  define GL_PIXEL_MAP_I_TO_G 0x0C73
#  define GL_PIXEL_MAP_I_TO_B 0x0C74
#  define GL_PIXEL_MAP_I_TO_A 0x0C75
#  define GL_PIXEL_MAP_R_TO_R 0x0C76
#  define GL_PIXEL_MAP_G_TO_G 0x0C77
#  define GL_PIXEL_MAP_B_TO_B 0x0C78
#  define GL_PIXEL_MAP_A_TO_A 0x0C79
#  define GL_CURRENT_COLOR 0x0B00
#  define GL_CURRENT_INDEX 0x0B01
#  define GL_CURRENT_NORMAL 0x0B02
#  define GL_CURRENT_TEXTURE_COORDS 0x0B03
#  define GL_CURRENT_RASTER_COLOR 0x0B04
#  define GL_CURRENT_RASTER_INDEX 0x0B05
#  define GL_CURRENT_RASTER_TEXTURE_COORDS 0x0B06
#  define GL_CURRENT_RASTER_POSITION 0x0B07
#  define GL_CURRENT_RASTER_POSITION_VALID 0x0B08
#  define GL_CURRENT_RASTER_DISTANCE 0x0B09
#  define GL_POINT_SMOOTH 0x0B10
#  define GL_LINE_STIPPLE 0x0B24
#  define GL_LINE_STIPPLE_PATTERN 0x0B25
#  define GL_LINE_STIPPLE_REPEAT 0x0B26
#  define GL_LIST_MODE 0x0B30
#  define GL_MAX_LIST_NESTING 0x0B31
#  define GL_LIST_BASE 0x0B32
#  define GL_LIST_INDEX 0x0B33
#  define GL_POLYGON_STIPPLE 0x0B42
#  define GL_EDGE_FLAG 0x0B43
#  define GL_LIGHTING 0x0B50
#  define GL_LIGHT_MODEL_LOCAL_VIEWER 0x0B51
#  define GL_LIGHT_MODEL_TWO_SIDE 0x0B52
#  define GL_LIGHT_MODEL_AMBIENT 0x0B53
#  define GL_SHADE_MODEL 0x0B54
#  define GL_COLOR_MATERIAL_FACE 0x0B55
#  define GL_COLOR_MATERIAL_PARAMETER 0x0B56
#  define GL_COLOR_MATERIAL 0x0B57
#  define GL_FOG 0x0B60
#  define GL_FOG_INDEX 0x0B61
#  define GL_FOG_DENSITY 0x0B62
#  define GL_FOG_START 0x0B63
#  define GL_FOG_END 0x0B64
#  define GL_FOG_MODE 0x0B65
#  define GL_FOG_COLOR 0x0B66
#  define GL_ACCUM_CLEAR_VALUE 0x0B80
#  define GL_MATRIX_MODE 0x0BA0
#  define GL_NORMALIZE 0x0BA1
#  define GL_MODELVIEW_STACK_DEPTH 0x0BA3
#  define GL_PROJECTION_STACK_DEPTH 0x0BA4
#  define GL_TEXTURE_STACK_DEPTH 0x0BA5
#  define GL_MODELVIEW_MATRIX 0x0BA6
#  define GL_PROJECTION_MATRIX 0x0BA7
#  define GL_TEXTURE_MATRIX 0x0BA8
#  define GL_ATTRIB_STACK_DEPTH 0x0BB0
#  define GL_ALPHA_TEST 0x0BC0
#  define GL_ALPHA_TEST_FUNC 0x0BC1
#  define GL_ALPHA_TEST_REF 0x0BC2
#  define GL_LOGIC_OP 0x0BF1
#  define GL_AUX_BUFFERS 0x0C00
#  define GL_INDEX_CLEAR_VALUE 0x0C20
#  define GL_INDEX_WRITEMASK 0x0C21
#  define GL_INDEX_MODE 0x0C30
#  define GL_RGBA_MODE 0x0C31
#  define GL_RENDER_MODE 0x0C40
#  define GL_PERSPECTIVE_CORRECTION_HINT 0x0C50
#  define GL_POINT_SMOOTH_HINT 0x0C51
#  define GL_FOG_HINT 0x0C54
#  define GL_TEXTURE_GEN_S 0x0C60
#  define GL_TEXTURE_GEN_T 0x0C61
#  define GL_TEXTURE_GEN_R 0x0C62
#  define GL_TEXTURE_GEN_Q 0x0C63
#  define GL_PIXEL_MAP_I_TO_I_SIZE 0x0CB0
#  define GL_PIXEL_MAP_S_TO_S_SIZE 0x0CB1
#  define GL_PIXEL_MAP_I_TO_R_SIZE 0x0CB2
#  define GL_PIXEL_MAP_I_TO_G_SIZE 0x0CB3
#  define GL_PIXEL_MAP_I_TO_B_SIZE 0x0CB4
#  define GL_PIXEL_MAP_I_TO_A_SIZE 0x0CB5
#  define GL_PIXEL_MAP_R_TO_R_SIZE 0x0CB6
#  define GL_PIXEL_MAP_G_TO_G_SIZE 0x0CB7
#  define GL_PIXEL_MAP_B_TO_B_SIZE 0x0CB8
#  define GL_PIXEL_MAP_A_TO_A_SIZE 0x0CB9
#  define GL_MAP_COLOR 0x0D10
#  define GL_MAP_STENCIL 0x0D11
#  define GL_INDEX_SHIFT 0x0D12
#  define GL_INDEX_OFFSET 0x0D13
#  define GL_RED_SCALE 0x0D14
#  define GL_RED_BIAS 0x0D15
#  define GL_ZOOM_X 0x0D16
#  define GL_ZOOM_Y 0x0D17
#  define GL_GREEN_SCALE 0x0D18
#  define GL_GREEN_BIAS 0x0D19
#  define GL_BLUE_SCALE 0x0D1A
#  define GL_BLUE_BIAS 0x0D1B
#  define GL_ALPHA_SCALE 0x0D1C
#  define GL_ALPHA_BIAS 0x0D1D
#  define GL_DEPTH_SCALE 0x0D1E
#  define GL_DEPTH_BIAS 0x0D1F
#  define GL_MAX_EVAL_ORDER 0x0D30
#  define GL_MAX_LIGHTS 0x0D31
#  define GL_MAX_CLIP_PLANES 0x0D32
#  define GL_MAX_PIXEL_MAP_TABLE 0x0D34
#  define GL_MAX_ATTRIB_STACK_DEPTH 0x0D35
#  define GL_MAX_MODELVIEW_STACK_DEPTH 0x0D36
#  define GL_MAX_NAME_STACK_DEPTH 0x0D37
#  define GL_MAX_PROJECTION_STACK_DEPTH 0x0D38
#  define GL_MAX_TEXTURE_STACK_DEPTH 0x0D39
#  define GL_INDEX_BITS 0x0D51
#  define GL_RED_BITS 0x0D52
#  define GL_GREEN_BITS 0x0D53
#  define GL_BLUE_BITS 0x0D54
#  define GL_ALPHA_BITS 0x0D55
#  define GL_DEPTH_BITS 0x0D56
#  define GL_STENCIL_BITS 0x0D57
#  define GL_ACCUM_RED_BITS 0x0D58
#  define GL_ACCUM_GREEN_BITS 0x0D59
#  define GL_ACCUM_BLUE_BITS 0x0D5A
#  define GL_ACCUM_ALPHA_BITS 0x0D5B
#  define GL_NAME_STACK_DEPTH 0x0D70
#  define GL_AUTO_NORMAL 0x0D80
#  define GL_MAP1_COLOR_4 0x0D90
#  define GL_MAP1_INDEX 0x0D91
#  define GL_MAP1_NORMAL 0x0D92
#  define GL_MAP1_TEXTURE_COORD_1 0x0D93
#  define GL_MAP1_TEXTURE_COORD_2 0x0D94
#  define GL_MAP1_TEXTURE_COORD_3 0x0D95
#  define GL_MAP1_TEXTURE_COORD_4 0x0D96
#  define GL_MAP1_VERTEX_3 0x0D97
#  define GL_MAP1_VERTEX_4 0x0D98
#  define GL_MAP2_COLOR_4 0x0DB0
#  define GL_MAP2_INDEX 0x0DB1
#  define GL_MAP2_NORMAL 0x0DB2
#  define GL_MAP2_TEXTURE_COORD_1 0x0DB3
#  define GL_MAP2_TEXTURE_COORD_2 0x0DB4
#  define GL_MAP2_TEXTURE_COORD_3 0x0DB5
#  define GL_MAP2_TEXTURE_COORD_4 0x0DB6
#  define GL_MAP2_VERTEX_3 0x0DB7
#  define GL_MAP2_VERTEX_4 0x0DB8
#  define GL_MAP1_GRID_DOMAIN 0x0DD0
#  define GL_MAP1_GRID_SEGMENTS 0x0DD1
#  define GL_MAP2_GRID_DOMAIN 0x0DD2
#  define GL_MAP2_GRID_SEGMENTS 0x0DD3
#  define GL_TEXTURE_COMPONENTS 0x1003
#  define GL_TEXTURE_BORDER 0x1005
#  define GL_AMBIENT 0x1200
#  define GL_DIFFUSE 0x1201
#  define GL_SPECULAR 0x1202
#  define GL_POSITION 0x1203
#  define GL_SPOT_DIRECTION 0x1204
#  define GL_SPOT_EXPONENT 0x1205
#  define GL_SPOT_CUTOFF 0x1206
#  define GL_CONSTANT_ATTENUATION 0x1207
#  define GL_LINEAR_ATTENUATION 0x1208
#  define GL_QUADRATIC_ATTENUATION 0x1209
#  define GL_COMPILE 0x1300
#  define GL_COMPILE_AND_EXECUTE 0x1301
#  define GL_2_BYTES 0x1407
#  define GL_3_BYTES 0x1408
#  define GL_4_BYTES 0x1409
#  define GL_EMISSION 0x1600
#  define GL_SHININESS 0x1601
#  define GL_AMBIENT_AND_DIFFUSE 0x1602
#  define GL_COLOR_INDEXES 0x1603
#  define GL_MODELVIEW 0x1700
#  define GL_PROJECTION 0x1701
#  define GL_COLOR_INDEX 0x1900
#  define GL_LUMINANCE 0x1909
#  define GL_LUMINANCE_ALPHA 0x190A
#  define GL_BITMAP 0x1A00
#  define GL_RENDER 0x1C00
#  define GL_FEEDBACK 0x1C01
#  define GL_SELECT 0x1C02
#  define GL_FLAT 0x1D00
#  define GL_SMOOTH 0x1D01
#  define GL_S 0x2000
#  define GL_T 0x2001
#  define GL_R 0x2002
#  define GL_Q 0x2003
#  define GL_MODULATE 0x2100
#  define GL_DECAL 0x2101
#  define GL_TEXTURE_ENV_MODE 0x2200
#  define GL_TEXTURE_ENV_COLOR 0x2201
#  define GL_TEXTURE_ENV 0x2300
#  define GL_EYE_LINEAR 0x2400
#  define GL_OBJECT_LINEAR 0x2401
#  define GL_SPHERE_MAP 0x2402
#  define GL_TEXTURE_GEN_MODE 0x2500
#  define GL_OBJECT_PLANE 0x2501
#  define GL_EYE_PLANE 0x2502
#  define GL_CLAMP 0x2900
#  define GL_CLIP_PLANE0 0x3000
#  define GL_CLIP_PLANE1 0x3001
#  define GL_CLIP_PLANE2 0x3002
#  define GL_CLIP_PLANE3 0x3003
#  define GL_CLIP_PLANE4 0x3004
#  define GL_CLIP_PLANE5 0x3005
#  define GL_LIGHT0 0x4000
#  define GL_LIGHT1 0x4001
#  define GL_LIGHT2 0x4002
#  define GL_LIGHT3 0x4003
#  define GL_LIGHT4 0x4004
#  define GL_LIGHT5 0x4005
#  define GL_LIGHT6 0x4006
#  define GL_LIGHT7 0x4007
# 
# endif /* GL_VERSION_1_0 */
# if defined GL_VERSION_1_1
# 
#  define GL_COLOR_LOGIC_OP 0x0BF2
#  define GL_POLYGON_OFFSET_UNITS 0x2A00
#  define GL_POLYGON_OFFSET_POINT 0x2A01
#  define GL_POLYGON_OFFSET_LINE 0x2A02
#  define GL_POLYGON_OFFSET_FILL 0x8037
#  define GL_POLYGON_OFFSET_FACTOR 0x8038
#  define GL_TEXTURE_BINDING_1D 0x8068
#  define GL_TEXTURE_BINDING_2D 0x8069
#  define GL_TEXTURE_INTERNAL_FORMAT 0x1003
#  define GL_TEXTURE_RED_SIZE 0x805C
#  define GL_TEXTURE_GREEN_SIZE 0x805D
#  define GL_TEXTURE_BLUE_SIZE 0x805E
#  define GL_TEXTURE_ALPHA_SIZE 0x805F
#  define GL_DOUBLE 0x140A
#  define GL_PROXY_TEXTURE_1D 0x8063
#  define GL_PROXY_TEXTURE_2D 0x8064
#  define GL_R3_G3_B2 0x2A10
#  define GL_RGB4 0x804F
#  define GL_RGB5 0x8050
#  define GL_RGB8 0x8051
#  define GL_RGB10 0x8052
#  define GL_RGB12 0x8053
#  define GL_RGB16 0x8054
#  define GL_RGBA2 0x8055
#  define GL_RGBA4 0x8056
#  define GL_RGB5_A1 0x8057
#  define GL_RGBA8 0x8058
#  define GL_RGB10_A2 0x8059
#  define GL_RGBA12 0x805A
#  define GL_RGBA16 0x805B
#  define GL_CLIENT_PIXEL_STORE_BIT 0x00000001
#  define GL_CLIENT_VERTEX_ARRAY_BIT 0x00000002
#  define GL_CLIENT_ALL_ATTRIB_BITS 0xFFFFFFFF
#  define GL_VERTEX_ARRAY_POINTER 0x808E
#  define GL_NORMAL_ARRAY_POINTER 0x808F
#  define GL_COLOR_ARRAY_POINTER 0x8090
#  define GL_INDEX_ARRAY_POINTER 0x8091
#  define GL_TEXTURE_COORD_ARRAY_POINTER 0x8092
#  define GL_EDGE_FLAG_ARRAY_POINTER 0x8093
#  define GL_FEEDBACK_BUFFER_POINTER 0x0DF0
#  define GL_SELECTION_BUFFER_POINTER 0x0DF3
#  define GL_CLIENT_ATTRIB_STACK_DEPTH 0x0BB1
#  define GL_INDEX_LOGIC_OP 0x0BF1
#  define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH 0x0D3B
#  define GL_FEEDBACK_BUFFER_SIZE 0x0DF1
#  define GL_FEEDBACK_BUFFER_TYPE 0x0DF2
#  define GL_SELECTION_BUFFER_SIZE 0x0DF4
#  define GL_VERTEX_ARRAY 0x8074
#  define GL_NORMAL_ARRAY 0x8075
#  define GL_COLOR_ARRAY 0x8076
#  define GL_INDEX_ARRAY 0x8077
#  define GL_TEXTURE_COORD_ARRAY 0x8078
#  define GL_EDGE_FLAG_ARRAY 0x8079
#  define GL_VERTEX_ARRAY_SIZE 0x807A
#  define GL_VERTEX_ARRAY_TYPE 0x807B
#  define GL_VERTEX_ARRAY_STRIDE 0x807C
#  define GL_NORMAL_ARRAY_TYPE 0x807E
#  define GL_NORMAL_ARRAY_STRIDE 0x807F
#  define GL_COLOR_ARRAY_SIZE 0x8081
#  define GL_COLOR_ARRAY_TYPE 0x8082
#  define GL_COLOR_ARRAY_STRIDE 0x8083
#  define GL_INDEX_ARRAY_TYPE 0x8085
#  define GL_INDEX_ARRAY_STRIDE 0x8086
#  define GL_TEXTURE_COORD_ARRAY_SIZE 0x8088
#  define GL_TEXTURE_COORD_ARRAY_TYPE 0x8089
#  define GL_TEXTURE_COORD_ARRAY_STRIDE 0x808A
#  define GL_EDGE_FLAG_ARRAY_STRIDE 0x808C
#  define GL_TEXTURE_LUMINANCE_SIZE 0x8060
#  define GL_TEXTURE_INTENSITY_SIZE 0x8061
#  define GL_TEXTURE_PRIORITY 0x8066
#  define GL_TEXTURE_RESIDENT 0x8067
#  define GL_ALPHA4 0x803B
#  define GL_ALPHA8 0x803C
#  define GL_ALPHA12 0x803D
#  define GL_ALPHA16 0x803E
#  define GL_LUMINANCE4 0x803F
#  define GL_LUMINANCE8 0x8040
#  define GL_LUMINANCE12 0x8041
#  define GL_LUMINANCE16 0x8042
#  define GL_LUMINANCE4_ALPHA4 0x8043
#  define GL_LUMINANCE6_ALPHA2 0x8044
#  define GL_LUMINANCE8_ALPHA8 0x8045
#  define GL_LUMINANCE12_ALPHA4 0x8046
#  define GL_LUMINANCE12_ALPHA12 0x8047
#  define GL_LUMINANCE16_ALPHA16 0x8048
#  define GL_INTENSITY 0x8049
#  define GL_INTENSITY4 0x804A
#  define GL_INTENSITY8 0x804B
#  define GL_INTENSITY12 0x804C
#  define GL_INTENSITY16 0x804D
#  define GL_V2F 0x2A20
#  define GL_V3F 0x2A21
#  define GL_C4UB_V2F 0x2A22
#  define GL_C4UB_V3F 0x2A23
#  define GL_C3F_V3F 0x2A24
#  define GL_N3F_V3F 0x2A25
#  define GL_C4F_N3F_V3F 0x2A26
#  define GL_T2F_V3F 0x2A27
#  define GL_T4F_V4F 0x2A28
#  define GL_T2F_C4UB_V3F 0x2A29
#  define GL_T2F_C3F_V3F 0x2A2A
#  define GL_T2F_N3F_V3F 0x2A2B
#  define GL_T2F_C4F_N3F_V3F 0x2A2C
#  define GL_T4F_C4F_N3F_V4F 0x2A2D
# 
# endif /* GL_VERSION_1_1 */
# if defined GL_VERSION_1_2
# 
#  define GL_UNSIGNED_BYTE_3_3_2 0x8032
#  define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#  define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#  define GL_UNSIGNED_INT_8_8_8_8 0x8035
#  define GL_UNSIGNED_INT_10_10_10_2 0x8036
#  define GL_TEXTURE_BINDING_3D 0x806A
#  define GL_PACK_SKIP_IMAGES 0x806B
#  define GL_PACK_IMAGE_HEIGHT 0x806C
#  define GL_UNPACK_SKIP_IMAGES 0x806D
#  define GL_UNPACK_IMAGE_HEIGHT 0x806E
#  define GL_TEXTURE_3D 0x806F
#  define GL_PROXY_TEXTURE_3D 0x8070
#  define GL_TEXTURE_DEPTH 0x8071
#  define GL_TEXTURE_WRAP_R 0x8072
#  define GL_MAX_3D_TEXTURE_SIZE 0x8073
#  define GL_UNSIGNED_BYTE_2_3_3_REV 0x8362
#  define GL_UNSIGNED_SHORT_5_6_5 0x8363
#  define GL_UNSIGNED_SHORT_5_6_5_REV 0x8364
#  define GL_UNSIGNED_SHORT_4_4_4_4_REV 0x8365
#  define GL_UNSIGNED_SHORT_1_5_5_5_REV 0x8366
#  define GL_UNSIGNED_INT_8_8_8_8_REV 0x8367
#  define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368
#  define GL_BGR 0x80E0
#  define GL_BGRA 0x80E1
#  define GL_MAX_ELEMENTS_VERTICES 0x80E8
#  define GL_MAX_ELEMENTS_INDICES 0x80E9
#  define GL_CLAMP_TO_EDGE 0x812F
#  define GL_TEXTURE_MIN_LOD 0x813A
#  define GL_TEXTURE_MAX_LOD 0x813B
#  define GL_TEXTURE_BASE_LEVEL 0x813C
#  define GL_TEXTURE_MAX_LEVEL 0x813D
#  define GL_SMOOTH_POINT_SIZE_RANGE 0x0B12
#  define GL_SMOOTH_POINT_SIZE_GRANULARITY 0x0B13
#  define GL_SMOOTH_LINE_WIDTH_RANGE 0x0B22
#  define GL_SMOOTH_LINE_WIDTH_GRANULARITY 0x0B23
#  define GL_ALIASED_LINE_WIDTH_RANGE 0x846E
#  define GL_RESCALE_NORMAL 0x803A
#  define GL_LIGHT_MODEL_COLOR_CONTROL 0x81F8
#  define GL_SINGLE_COLOR 0x81F9
#  define GL_SEPARATE_SPECULAR_COLOR 0x81FA
#  define GL_ALIASED_POINT_SIZE_RANGE 0x846D
# 
# endif /* GL_VERSION_1_2 */
# if defined GL_VERSION_1_3
# 
#  define GL_TEXTURE0 0x84C0
#  define GL_TEXTURE1 0x84C1
#  define GL_TEXTURE2 0x84C2
#  define GL_TEXTURE3 0x84C3
#  define GL_TEXTURE4 0x84C4
#  define GL_TEXTURE5 0x84C5
#  define GL_TEXTURE6 0x84C6
#  define GL_TEXTURE7 0x84C7
#  define GL_TEXTURE8 0x84C8
#  define GL_TEXTURE9 0x84C9
#  define GL_TEXTURE10 0x84CA
#  define GL_TEXTURE11 0x84CB
#  define GL_TEXTURE12 0x84CC
#  define GL_TEXTURE13 0x84CD
#  define GL_TEXTURE14 0x84CE
#  define GL_TEXTURE15 0x84CF
#  define GL_TEXTURE16 0x84D0
#  define GL_TEXTURE17 0x84D1
#  define GL_TEXTURE18 0x84D2
#  define GL_TEXTURE19 0x84D3
#  define GL_TEXTURE20 0x84D4
#  define GL_TEXTURE21 0x84D5
#  define GL_TEXTURE22 0x84D6
#  define GL_TEXTURE23 0x84D7
#  define GL_TEXTURE24 0x84D8
#  define GL_TEXTURE25 0x84D9
#  define GL_TEXTURE26 0x84DA
#  define GL_TEXTURE27 0x84DB
#  define GL_TEXTURE28 0x84DC
#  define GL_TEXTURE29 0x84DD
#  define GL_TEXTURE30 0x84DE
#  define GL_TEXTURE31 0x84DF
#  define GL_ACTIVE_TEXTURE 0x84E0
#  define GL_MULTISAMPLE 0x809D
#  define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#  define GL_SAMPLE_ALPHA_TO_ONE 0x809F
#  define GL_SAMPLE_COVERAGE 0x80A0
#  define GL_SAMPLE_BUFFERS 0x80A8
#  define GL_SAMPLES 0x80A9
#  define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#  define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#  define GL_TEXTURE_CUBE_MAP 0x8513
#  define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#  define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#  define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#  define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#  define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#  define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#  define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
#  define GL_PROXY_TEXTURE_CUBE_MAP 0x851B
#  define GL_MAX_CUBE_MAP_TEXTURE_SIZE 0x851C
#  define GL_COMPRESSED_RGB 0x84ED
#  define GL_COMPRESSED_RGBA 0x84EE
#  define GL_TEXTURE_COMPRESSION_HINT 0x84EF
#  define GL_TEXTURE_COMPRESSED_IMAGE_SIZE 0x86A0
#  define GL_TEXTURE_COMPRESSED 0x86A1
#  define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#  define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#  define GL_CLAMP_TO_BORDER 0x812D
#  define GL_CLIENT_ACTIVE_TEXTURE 0x84E1
#  define GL_MAX_TEXTURE_UNITS 0x84E2
#  define GL_TRANSPOSE_MODELVIEW_MATRIX 0x84E3
#  define GL_TRANSPOSE_PROJECTION_MATRIX 0x84E4
#  define GL_TRANSPOSE_TEXTURE_MATRIX 0x84E5
#  define GL_TRANSPOSE_COLOR_MATRIX 0x84E6
#  define GL_MULTISAMPLE_BIT 0x20000000
#  define GL_NORMAL_MAP 0x8511
#  define GL_REFLECTION_MAP 0x8512
#  define GL_COMPRESSED_ALPHA 0x84E9
#  define GL_COMPRESSED_LUMINANCE 0x84EA
#  define GL_COMPRESSED_LUMINANCE_ALPHA 0x84EB
#  define GL_COMPRESSED_INTENSITY 0x84EC
#  define GL_COMBINE 0x8570
#  define GL_COMBINE_RGB 0x8571
#  define GL_COMBINE_ALPHA 0x8572
#  define GL_SOURCE0_RGB 0x8580
#  define GL_SOURCE1_RGB 0x8581
#  define GL_SOURCE2_RGB 0x8582
#  define GL_SOURCE0_ALPHA 0x8588
#  define GL_SOURCE1_ALPHA 0x8589
#  define GL_SOURCE2_ALPHA 0x858A
#  define GL_OPERAND0_RGB 0x8590
#  define GL_OPERAND1_RGB 0x8591
#  define GL_OPERAND2_RGB 0x8592
#  define GL_OPERAND0_ALPHA 0x8598
#  define GL_OPERAND1_ALPHA 0x8599
#  define GL_OPERAND2_ALPHA 0x859A
#  define GL_RGB_SCALE 0x8573
#  define GL_ADD_SIGNED 0x8574
#  define GL_INTERPOLATE 0x8575
#  define GL_SUBTRACT 0x84E7
#  define GL_CONSTANT 0x8576
#  define GL_PRIMARY_COLOR 0x8577
#  define GL_PREVIOUS 0x8578
#  define GL_DOT3_RGB 0x86AE
#  define GL_DOT3_RGBA 0x86AF
# 
# endif /* GL_VERSION_1_3 */
# if defined GL_VERSION_1_4
# 
#  define GL_BLEND_DST_RGB 0x80C8
#  define GL_BLEND_SRC_RGB 0x80C9
#  define GL_BLEND_DST_ALPHA 0x80CA
#  define GL_BLEND_SRC_ALPHA 0x80CB
#  define GL_POINT_FADE_THRESHOLD_SIZE 0x8128
#  define GL_DEPTH_COMPONENT16 0x81A5
#  define GL_DEPTH_COMPONENT24 0x81A6
#  define GL_DEPTH_COMPONENT32 0x81A7
#  define GL_MIRRORED_REPEAT 0x8370
#  define GL_MAX_TEXTURE_LOD_BIAS 0x84FD
#  define GL_TEXTURE_LOD_BIAS 0x8501
#  define GL_INCR_WRAP 0x8507
#  define GL_DECR_WRAP 0x8508
#  define GL_TEXTURE_DEPTH_SIZE 0x884A
#  define GL_TEXTURE_COMPARE_MODE 0x884C
#  define GL_TEXTURE_COMPARE_FUNC 0x884D
#  define GL_POINT_SIZE_MIN 0x8126
#  define GL_POINT_SIZE_MAX 0x8127
#  define GL_POINT_DISTANCE_ATTENUATION 0x8129
#  define GL_GENERATE_MIPMAP 0x8191
#  define GL_GENERATE_MIPMAP_HINT 0x8192
#  define GL_FOG_COORDINATE_SOURCE 0x8450
#  define GL_FOG_COORDINATE 0x8451
#  define GL_FRAGMENT_DEPTH 0x8452
#  define GL_CURRENT_FOG_COORDINATE 0x8453
#  define GL_FOG_COORDINATE_ARRAY_TYPE 0x8454
#  define GL_FOG_COORDINATE_ARRAY_STRIDE 0x8455
#  define GL_FOG_COORDINATE_ARRAY_POINTER 0x8456
#  define GL_FOG_COORDINATE_ARRAY 0x8457
#  define GL_COLOR_SUM 0x8458
#  define GL_CURRENT_SECONDARY_COLOR 0x8459
#  define GL_SECONDARY_COLOR_ARRAY_SIZE 0x845A
#  define GL_SECONDARY_COLOR_ARRAY_TYPE 0x845B
#  define GL_SECONDARY_COLOR_ARRAY_STRIDE 0x845C
#  define GL_SECONDARY_COLOR_ARRAY_POINTER 0x845D
#  define GL_SECONDARY_COLOR_ARRAY 0x845E
#  define GL_TEXTURE_FILTER_CONTROL 0x8500
#  define GL_DEPTH_TEXTURE_MODE 0x884B
#  define GL_COMPARE_R_TO_TEXTURE 0x884E
#  define GL_BLEND_COLOR 0x8005
#  define GL_BLEND_EQUATION 0x8009
#  define GL_CONSTANT_COLOR 0x8001
#  define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#  define GL_CONSTANT_ALPHA 0x8003
#  define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#  define GL_FUNC_ADD 0x8006
#  define GL_FUNC_REVERSE_SUBTRACT 0x800B
#  define GL_FUNC_SUBTRACT 0x800A
#  define GL_MIN 0x8007
#  define GL_MAX 0x8008
# 
# endif /* GL_VERSION_1_4 */
# if defined GL_VERSION_1_5
# 
#  define GL_BUFFER_SIZE 0x8764
#  define GL_BUFFER_USAGE 0x8765
#  define GL_QUERY_COUNTER_BITS 0x8864
#  define GL_CURRENT_QUERY 0x8865
#  define GL_QUERY_RESULT 0x8866
#  define GL_QUERY_RESULT_AVAILABLE 0x8867
#  define GL_ARRAY_BUFFER 0x8892
#  define GL_ELEMENT_ARRAY_BUFFER 0x8893
#  define GL_ARRAY_BUFFER_BINDING 0x8894
#  define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#  define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#  define GL_READ_ONLY 0x88B8
#  define GL_WRITE_ONLY 0x88B9
#  define GL_READ_WRITE 0x88BA
#  define GL_BUFFER_ACCESS 0x88BB
#  define GL_BUFFER_MAPPED 0x88BC
#  define GL_BUFFER_MAP_POINTER 0x88BD
#  define GL_STREAM_DRAW 0x88E0
#  define GL_STREAM_READ 0x88E1
#  define GL_STREAM_COPY 0x88E2
#  define GL_STATIC_DRAW 0x88E4
#  define GL_STATIC_READ 0x88E5
#  define GL_STATIC_COPY 0x88E6
#  define GL_DYNAMIC_DRAW 0x88E8
#  define GL_DYNAMIC_READ 0x88E9
#  define GL_DYNAMIC_COPY 0x88EA
#  define GL_SAMPLES_PASSED 0x8914
#  define GL_SRC1_ALPHA 0x8589
#  define GL_VERTEX_ARRAY_BUFFER_BINDING 0x8896
#  define GL_NORMAL_ARRAY_BUFFER_BINDING 0x8897
#  define GL_COLOR_ARRAY_BUFFER_BINDING 0x8898
#  define GL_INDEX_ARRAY_BUFFER_BINDING 0x8899
#  define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889A
#  define GL_EDGE_FLAG_ARRAY_BUFFER_BINDING 0x889B
#  define GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING 0x889C
#  define GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING 0x889D
#  define GL_WEIGHT_ARRAY_BUFFER_BINDING 0x889E
#  define GL_FOG_COORD_SRC 0x8450
#  define GL_FOG_COORD 0x8451
#  define GL_CURRENT_FOG_COORD 0x8453
#  define GL_FOG_COORD_ARRAY_TYPE 0x8454
#  define GL_FOG_COORD_ARRAY_STRIDE 0x8455
#  define GL_FOG_COORD_ARRAY_POINTER 0x8456
#  define GL_FOG_COORD_ARRAY 0x8457
#  define GL_FOG_COORD_ARRAY_BUFFER_BINDING 0x889D
#  define GL_SRC0_RGB 0x8580
#  define GL_SRC1_RGB 0x8581
#  define GL_SRC2_RGB 0x8582
#  define GL_SRC0_ALPHA 0x8588
#  define GL_SRC2_ALPHA 0x858A
# 
# endif /* GL_VERSION_1_5 */
# if defined GL_VERSION_2_0
# 
#  define GL_BLEND_EQUATION_RGB 0x8009
#  define GL_VERTEX_ATTRIB_ARRAY_ENABLED 0x8622
#  define GL_VERTEX_ATTRIB_ARRAY_SIZE 0x8623
#  define GL_VERTEX_ATTRIB_ARRAY_STRIDE 0x8624
#  define GL_VERTEX_ATTRIB_ARRAY_TYPE 0x8625
#  define GL_CURRENT_VERTEX_ATTRIB 0x8626
#  define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642
#  define GL_VERTEX_ATTRIB_ARRAY_POINTER 0x8645
#  define GL_STENCIL_BACK_FUNC 0x8800
#  define GL_STENCIL_BACK_FAIL 0x8801
#  define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
#  define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
#  define GL_MAX_DRAW_BUFFERS 0x8824
#  define GL_DRAW_BUFFER0 0x8825
#  define GL_DRAW_BUFFER1 0x8826
#  define GL_DRAW_BUFFER2 0x8827
#  define GL_DRAW_BUFFER3 0x8828
#  define GL_DRAW_BUFFER4 0x8829
#  define GL_DRAW_BUFFER5 0x882A
#  define GL_DRAW_BUFFER6 0x882B
#  define GL_DRAW_BUFFER7 0x882C
#  define GL_DRAW_BUFFER8 0x882D
#  define GL_DRAW_BUFFER9 0x882E
#  define GL_DRAW_BUFFER10 0x882F
#  define GL_DRAW_BUFFER11 0x8830
#  define GL_DRAW_BUFFER12 0x8831
#  define GL_DRAW_BUFFER13 0x8832
#  define GL_DRAW_BUFFER14 0x8833
#  define GL_DRAW_BUFFER15 0x8834
#  define GL_BLEND_EQUATION_ALPHA 0x883D
#  define GL_MAX_VERTEX_ATTRIBS 0x8869
#  define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#  define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
#  define GL_FRAGMENT_SHADER 0x8B30
#  define GL_VERTEX_SHADER 0x8B31
#  define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#  define GL_MAX_VERTEX_UNIFORM_COMPONENTS 0x8B4A
#  define GL_MAX_VARYING_FLOATS 0x8B4B
#  define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#  define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#  define GL_SHADER_TYPE 0x8B4F
#  define GL_FLOAT_VEC2 0x8B50
#  define GL_FLOAT_VEC3 0x8B51
#  define GL_FLOAT_VEC4 0x8B52
#  define GL_INT_VEC2 0x8B53
#  define GL_INT_VEC3 0x8B54
#  define GL_INT_VEC4 0x8B55
#  define GL_BOOL 0x8B56
#  define GL_BOOL_VEC2 0x8B57
#  define GL_BOOL_VEC3 0x8B58
#  define GL_BOOL_VEC4 0x8B59
#  define GL_FLOAT_MAT2 0x8B5A
#  define GL_FLOAT_MAT3 0x8B5B
#  define GL_FLOAT_MAT4 0x8B5C
#  define GL_SAMPLER_1D 0x8B5D
#  define GL_SAMPLER_2D 0x8B5E
#  define GL_SAMPLER_3D 0x8B5F
#  define GL_SAMPLER_CUBE 0x8B60
#  define GL_SAMPLER_1D_SHADOW 0x8B61
#  define GL_SAMPLER_2D_SHADOW 0x8B62
#  define GL_DELETE_STATUS 0x8B80
#  define GL_COMPILE_STATUS 0x8B81
#  define GL_LINK_STATUS 0x8B82
#  define GL_VALIDATE_STATUS 0x8B83
#  define GL_INFO_LOG_LENGTH 0x8B84
#  define GL_ATTACHED_SHADERS 0x8B85
#  define GL_ACTIVE_UNIFORMS 0x8B86
#  define GL_ACTIVE_UNIFORM_MAX_LENGTH 0x8B87
#  define GL_SHADER_SOURCE_LENGTH 0x8B88
#  define GL_ACTIVE_ATTRIBUTES 0x8B89
#  define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 0x8B8A
#  define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#  define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#  define GL_CURRENT_PROGRAM 0x8B8D
#  define GL_POINT_SPRITE_COORD_ORIGIN 0x8CA0
#  define GL_LOWER_LEFT 0x8CA1
#  define GL_UPPER_LEFT 0x8CA2
#  define GL_STENCIL_BACK_REF 0x8CA3
#  define GL_STENCIL_BACK_VALUE_MASK 0x8CA4
#  define GL_STENCIL_BACK_WRITEMASK 0x8CA5
#  define GL_VERTEX_PROGRAM_TWO_SIDE 0x8643
#  define GL_POINT_SPRITE 0x8861
#  define GL_COORD_REPLACE 0x8862
#  define GL_MAX_TEXTURE_COORDS 0x8871
# 
# endif /* GL_VERSION_2_0 */
# if defined GL_VERSION_2_1
# 
#  define GL_PIXEL_PACK_BUFFER 0x88EB
#  define GL_PIXEL_UNPACK_BUFFER 0x88EC
#  define GL_PIXEL_PACK_BUFFER_BINDING 0x88ED
#  define GL_PIXEL_UNPACK_BUFFER_BINDING 0x88EF
#  define GL_FLOAT_MAT2x3 0x8B65
#  define GL_FLOAT_MAT2x4 0x8B66
#  define GL_FLOAT_MAT3x2 0x8B67
#  define GL_FLOAT_MAT3x4 0x8B68
#  define GL_FLOAT_MAT4x2 0x8B69
#  define GL_FLOAT_MAT4x3 0x8B6A
#  define GL_SRGB 0x8C40
#  define GL_SRGB8 0x8C41
#  define GL_SRGB_ALPHA 0x8C42
#  define GL_SRGB8_ALPHA8 0x8C43
#  define GL_COMPRESSED_SRGB 0x8C48
#  define GL_COMPRESSED_SRGB_ALPHA 0x8C49
#  define GL_CURRENT_RASTER_SECONDARY_COLOR 0x845F
#  define GL_SLUMINANCE_ALPHA 0x8C44
#  define GL_SLUMINANCE8_ALPHA8 0x8C45
#  define GL_SLUMINANCE 0x8C46
#  define GL_SLUMINANCE8 0x8C47
#  define GL_COMPRESSED_SLUMINANCE 0x8C4A
#  define GL_COMPRESSED_SLUMINANCE_ALPHA 0x8C4B
# 
# endif /* GL_VERSION_2_1 */
# if defined GL_VERSION_3_0
# 
#  define GL_COMPARE_REF_TO_TEXTURE 0x884E
#  define GL_CLIP_DISTANCE0 0x3000
#  define GL_CLIP_DISTANCE1 0x3001
#  define GL_CLIP_DISTANCE2 0x3002
#  define GL_CLIP_DISTANCE3 0x3003
#  define GL_CLIP_DISTANCE4 0x3004
#  define GL_CLIP_DISTANCE5 0x3005
#  define GL_CLIP_DISTANCE6 0x3006
#  define GL_CLIP_DISTANCE7 0x3007
#  define GL_MAX_CLIP_DISTANCES 0x0D32
#  define GL_MAJOR_VERSION 0x821B
#  define GL_MINOR_VERSION 0x821C
#  define GL_NUM_EXTENSIONS 0x821D
#  define GL_CONTEXT_FLAGS 0x821E
#  define GL_COMPRESSED_RED 0x8225
#  define GL_COMPRESSED_RG 0x8226
#  define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x00000001
#  define GL_RGBA32F 0x8814
#  define GL_RGB32F 0x8815
#  define GL_RGBA16F 0x881A
#  define GL_RGB16F 0x881B
#  define GL_VERTEX_ATTRIB_ARRAY_INTEGER 0x88FD
#  define GL_MAX_ARRAY_TEXTURE_LAYERS 0x88FF
#  define GL_MIN_PROGRAM_TEXEL_OFFSET 0x8904
#  define GL_MAX_PROGRAM_TEXEL_OFFSET 0x8905
#  define GL_CLAMP_READ_COLOR 0x891C
#  define GL_FIXED_ONLY 0x891D
#  define GL_MAX_VARYING_COMPONENTS 0x8B4B
#  define GL_TEXTURE_1D_ARRAY 0x8C18
#  define GL_PROXY_TEXTURE_1D_ARRAY 0x8C19
#  define GL_TEXTURE_2D_ARRAY 0x8C1A
#  define GL_PROXY_TEXTURE_2D_ARRAY 0x8C1B
#  define GL_TEXTURE_BINDING_1D_ARRAY 0x8C1C
#  define GL_TEXTURE_BINDING_2D_ARRAY 0x8C1D
#  define GL_R11F_G11F_B10F 0x8C3A
#  define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B
#  define GL_RGB9_E5 0x8C3D
#  define GL_UNSIGNED_INT_5_9_9_9_REV 0x8C3E
#  define GL_TEXTURE_SHARED_SIZE 0x8C3F
#  define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#  define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#  define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#  define GL_TRANSFORM_FEEDBACK_VARYINGS 0x8C83
#  define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#  define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#  define GL_PRIMITIVES_GENERATED 0x8C87
#  define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#  define GL_RASTERIZER_DISCARD 0x8C89
#  define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#  define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#  define GL_INTERLEAVED_ATTRIBS 0x8C8C
#  define GL_SEPARATE_ATTRIBS 0x8C8D
#  define GL_TRANSFORM_FEEDBACK_BUFFER 0x8C8E
#  define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#  define GL_RGBA32UI 0x8D70
#  define GL_RGB32UI 0x8D71
#  define GL_RGBA16UI 0x8D76
#  define GL_RGB16UI 0x8D77
#  define GL_RGBA8UI 0x8D7C
#  define GL_RGB8UI 0x8D7D
#  define GL_RGBA32I 0x8D82
#  define GL_RGB32I 0x8D83
#  define GL_RGBA16I 0x8D88
#  define GL_RGB16I 0x8D89
#  define GL_RGBA8I 0x8D8E
#  define GL_RGB8I 0x8D8F
#  define GL_RED_INTEGER 0x8D94
#  define GL_GREEN_INTEGER 0x8D95
#  define GL_BLUE_INTEGER 0x8D96
#  define GL_RGB_INTEGER 0x8D98
#  define GL_RGBA_INTEGER 0x8D99
#  define GL_BGR_INTEGER 0x8D9A
#  define GL_BGRA_INTEGER 0x8D9B
#  define GL_SAMPLER_1D_ARRAY 0x8DC0
#  define GL_SAMPLER_2D_ARRAY 0x8DC1
#  define GL_SAMPLER_1D_ARRAY_SHADOW 0x8DC3
#  define GL_SAMPLER_2D_ARRAY_SHADOW 0x8DC4
#  define GL_SAMPLER_CUBE_SHADOW 0x8DC5
#  define GL_UNSIGNED_INT_VEC2 0x8DC6
#  define GL_UNSIGNED_INT_VEC3 0x8DC7
#  define GL_UNSIGNED_INT_VEC4 0x8DC8
#  define GL_INT_SAMPLER_1D 0x8DC9
#  define GL_INT_SAMPLER_2D 0x8DCA
#  define GL_INT_SAMPLER_3D 0x8DCB
#  define GL_INT_SAMPLER_CUBE 0x8DCC
#  define GL_INT_SAMPLER_1D_ARRAY 0x8DCE
#  define GL_INT_SAMPLER_2D_ARRAY 0x8DCF
#  define GL_UNSIGNED_INT_SAMPLER_1D 0x8DD1
#  define GL_UNSIGNED_INT_SAMPLER_2D 0x8DD2
#  define GL_UNSIGNED_INT_SAMPLER_3D 0x8DD3
#  define GL_UNSIGNED_INT_SAMPLER_CUBE 0x8DD4
#  define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 0x8DD6
#  define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 0x8DD7
#  define GL_QUERY_WAIT 0x8E13
#  define GL_QUERY_NO_WAIT 0x8E14
#  define GL_QUERY_BY_REGION_WAIT 0x8E15
#  define GL_QUERY_BY_REGION_NO_WAIT 0x8E16
#  define GL_BUFFER_ACCESS_FLAGS 0x911F
#  define GL_BUFFER_MAP_LENGTH 0x9120
#  define GL_BUFFER_MAP_OFFSET 0x9121
#  define GL_DEPTH_COMPONENT32F 0x8CAC
#  define GL_DEPTH32F_STENCIL8 0x8CAD
#  define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#  define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#  define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#  define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#  define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#  define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#  define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#  define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#  define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#  define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#  define GL_FRAMEBUFFER_DEFAULT 0x8218
#  define GL_FRAMEBUFFER_UNDEFINED 0x8219
#  define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#  define GL_MAX_RENDERBUFFER_SIZE 0x84E8
#  define GL_DEPTH_STENCIL 0x84F9
#  define GL_UNSIGNED_INT_24_8 0x84FA
#  define GL_DEPTH24_STENCIL8 0x88F0
#  define GL_TEXTURE_STENCIL_SIZE 0x88F1
#  define GL_TEXTURE_RED_TYPE 0x8C10
#  define GL_TEXTURE_GREEN_TYPE 0x8C11
#  define GL_TEXTURE_BLUE_TYPE 0x8C12
#  define GL_TEXTURE_ALPHA_TYPE 0x8C13
#  define GL_TEXTURE_DEPTH_TYPE 0x8C16
#  define GL_UNSIGNED_NORMALIZED 0x8C17
#  define GL_FRAMEBUFFER_BINDING 0x8CA6
#  define GL_DRAW_FRAMEBUFFER_BINDING 0x8CA6
#  define GL_RENDERBUFFER_BINDING 0x8CA7
#  define GL_READ_FRAMEBUFFER 0x8CA8
#  define GL_DRAW_FRAMEBUFFER 0x8CA9
#  define GL_READ_FRAMEBUFFER_BINDING 0x8CAA
#  define GL_RENDERBUFFER_SAMPLES 0x8CAB
#  define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#  define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#  define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#  define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#  define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#  define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#  define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#  define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#  define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#  define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#  define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
#  define GL_MAX_COLOR_ATTACHMENTS 0x8CDF
#  define GL_COLOR_ATTACHMENT0 0x8CE0
#  define GL_COLOR_ATTACHMENT1 0x8CE1
#  define GL_COLOR_ATTACHMENT2 0x8CE2
#  define GL_COLOR_ATTACHMENT3 0x8CE3
#  define GL_COLOR_ATTACHMENT4 0x8CE4
#  define GL_COLOR_ATTACHMENT5 0x8CE5
#  define GL_COLOR_ATTACHMENT6 0x8CE6
#  define GL_COLOR_ATTACHMENT7 0x8CE7
#  define GL_COLOR_ATTACHMENT8 0x8CE8
#  define GL_COLOR_ATTACHMENT9 0x8CE9
#  define GL_COLOR_ATTACHMENT10 0x8CEA
#  define GL_COLOR_ATTACHMENT11 0x8CEB
#  define GL_COLOR_ATTACHMENT12 0x8CEC
#  define GL_COLOR_ATTACHMENT13 0x8CED
#  define GL_COLOR_ATTACHMENT14 0x8CEE
#  define GL_COLOR_ATTACHMENT15 0x8CEF
#  define GL_COLOR_ATTACHMENT16 0x8CF0
#  define GL_COLOR_ATTACHMENT17 0x8CF1
#  define GL_COLOR_ATTACHMENT18 0x8CF2
#  define GL_COLOR_ATTACHMENT19 0x8CF3
#  define GL_COLOR_ATTACHMENT20 0x8CF4
#  define GL_COLOR_ATTACHMENT21 0x8CF5
#  define GL_COLOR_ATTACHMENT22 0x8CF6
#  define GL_COLOR_ATTACHMENT23 0x8CF7
#  define GL_COLOR_ATTACHMENT24 0x8CF8
#  define GL_COLOR_ATTACHMENT25 0x8CF9
#  define GL_COLOR_ATTACHMENT26 0x8CFA
#  define GL_COLOR_ATTACHMENT27 0x8CFB
#  define GL_COLOR_ATTACHMENT28 0x8CFC
#  define GL_COLOR_ATTACHMENT29 0x8CFD
#  define GL_COLOR_ATTACHMENT30 0x8CFE
#  define GL_COLOR_ATTACHMENT31 0x8CFF
#  define GL_DEPTH_ATTACHMENT 0x8D00
#  define GL_STENCIL_ATTACHMENT 0x8D20
#  define GL_FRAMEBUFFER 0x8D40
#  define GL_RENDERBUFFER 0x8D41
#  define GL_RENDERBUFFER_WIDTH 0x8D42
#  define GL_RENDERBUFFER_HEIGHT 0x8D43
#  define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8D44
#  define GL_STENCIL_INDEX1 0x8D46
#  define GL_STENCIL_INDEX4 0x8D47
#  define GL_STENCIL_INDEX8 0x8D48
#  define GL_STENCIL_INDEX16 0x8D49
#  define GL_RENDERBUFFER_RED_SIZE 0x8D50
#  define GL_RENDERBUFFER_GREEN_SIZE 0x8D51
#  define GL_RENDERBUFFER_BLUE_SIZE 0x8D52
#  define GL_RENDERBUFFER_ALPHA_SIZE 0x8D53
#  define GL_RENDERBUFFER_DEPTH_SIZE 0x8D54
#  define GL_RENDERBUFFER_STENCIL_SIZE 0x8D55
#  define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#  define GL_MAX_SAMPLES 0x8D57
#  define GL_INDEX 0x8222
#  define GL_TEXTURE_LUMINANCE_TYPE 0x8C14
#  define GL_TEXTURE_INTENSITY_TYPE 0x8C15
#  define GL_FRAMEBUFFER_SRGB 0x8DB9
#  define GL_HALF_FLOAT 0x140B
#  define GL_MAP_READ_BIT 0x0001
#  define GL_MAP_WRITE_BIT 0x0002
#  define GL_MAP_INVALIDATE_RANGE_BIT 0x0004
#  define GL_MAP_INVALIDATE_BUFFER_BIT 0x0008
#  define GL_MAP_FLUSH_EXPLICIT_BIT 0x0010
#  define GL_MAP_UNSYNCHRONIZED_BIT 0x0020
#  define GL_COMPRESSED_RED_RGTC1 0x8DBB
#  define GL_COMPRESSED_SIGNED_RED_RGTC1 0x8DBC
#  define GL_COMPRESSED_RG_RGTC2 0x8DBD
#  define GL_COMPRESSED_SIGNED_RG_RGTC2 0x8DBE
#  define GL_RG 0x8227
#  define GL_RG_INTEGER 0x8228
#  define GL_R8 0x8229
#  define GL_R16 0x822A
#  define GL_RG8 0x822B
#  define GL_RG16 0x822C
#  define GL_R16F 0x822D
#  define GL_R32F 0x822E
#  define GL_RG16F 0x822F
#  define GL_RG32F 0x8230
#  define GL_R8I 0x8231
#  define GL_R8UI 0x8232
#  define GL_R16I 0x8233
#  define GL_R16UI 0x8234
#  define GL_R32I 0x8235
#  define GL_R32UI 0x8236
#  define GL_RG8I 0x8237
#  define GL_RG8UI 0x8238
#  define GL_RG16I 0x8239
#  define GL_RG16UI 0x823A
#  define GL_RG32I 0x823B
#  define GL_RG32UI 0x823C
#  define GL_VERTEX_ARRAY_BINDING 0x85B5
#  define GL_CLAMP_VERTEX_COLOR 0x891A
#  define GL_CLAMP_FRAGMENT_COLOR 0x891B
#  define GL_ALPHA_INTEGER 0x8D97
# 
# endif /* GL_VERSION_3_0 */
# if defined GL_VERSION_3_1
# 
#  define GL_SAMPLER_2D_RECT 0x8B63
#  define GL_SAMPLER_2D_RECT_SHADOW 0x8B64
#  define GL_SAMPLER_BUFFER 0x8DC2
#  define GL_INT_SAMPLER_2D_RECT 0x8DCD
#  define GL_INT_SAMPLER_BUFFER 0x8DD0
#  define GL_UNSIGNED_INT_SAMPLER_2D_RECT 0x8DD5
#  define GL_UNSIGNED_INT_SAMPLER_BUFFER 0x8DD8
#  define GL_TEXTURE_BUFFER 0x8C2A
#  define GL_MAX_TEXTURE_BUFFER_SIZE 0x8C2B
#  define GL_TEXTURE_BINDING_BUFFER 0x8C2C
#  define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
#  define GL_TEXTURE_RECTANGLE 0x84F5
#  define GL_TEXTURE_BINDING_RECTANGLE 0x84F6
#  define GL_PROXY_TEXTURE_RECTANGLE 0x84F7
#  define GL_MAX_RECTANGLE_TEXTURE_SIZE 0x84F8
#  define GL_R8_SNORM 0x8F94
#  define GL_RG8_SNORM 0x8F95
#  define GL_RGB8_SNORM 0x8F96
#  define GL_RGBA8_SNORM 0x8F97
#  define GL_R16_SNORM 0x8F98
#  define GL_RG16_SNORM 0x8F99
#  define GL_RGB16_SNORM 0x8F9A
#  define GL_RGBA16_SNORM 0x8F9B
#  define GL_SIGNED_NORMALIZED 0x8F9C
#  define GL_PRIMITIVE_RESTART 0x8F9D
#  define GL_PRIMITIVE_RESTART_INDEX 0x8F9E
#  define GL_COPY_READ_BUFFER 0x8F36
#  define GL_COPY_WRITE_BUFFER 0x8F37
#  define GL_UNIFORM_BUFFER 0x8A11
#  define GL_UNIFORM_BUFFER_BINDING 0x8A28
#  define GL_UNIFORM_BUFFER_START 0x8A29
#  define GL_UNIFORM_BUFFER_SIZE 0x8A2A
#  define GL_MAX_VERTEX_UNIFORM_BLOCKS 0x8A2B
#  define GL_MAX_GEOMETRY_UNIFORM_BLOCKS 0x8A2C
#  define GL_MAX_FRAGMENT_UNIFORM_BLOCKS 0x8A2D
#  define GL_MAX_COMBINED_UNIFORM_BLOCKS 0x8A2E
#  define GL_MAX_UNIFORM_BUFFER_BINDINGS 0x8A2F
#  define GL_MAX_UNIFORM_BLOCK_SIZE 0x8A30
#  define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#  define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#  define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#  define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#  define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#  define GL_ACTIVE_UNIFORM_BLOCKS 0x8A36
#  define GL_UNIFORM_TYPE 0x8A37
#  define GL_UNIFORM_SIZE 0x8A38
#  define GL_UNIFORM_NAME_LENGTH 0x8A39
#  define GL_UNIFORM_BLOCK_INDEX 0x8A3A
#  define GL_UNIFORM_OFFSET 0x8A3B
#  define GL_UNIFORM_ARRAY_STRIDE 0x8A3C
#  define GL_UNIFORM_MATRIX_STRIDE 0x8A3D
#  define GL_UNIFORM_IS_ROW_MAJOR 0x8A3E
#  define GL_UNIFORM_BLOCK_BINDING 0x8A3F
#  define GL_UNIFORM_BLOCK_DATA_SIZE 0x8A40
#  define GL_UNIFORM_BLOCK_NAME_LENGTH 0x8A41
#  define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8A42
#  define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#  define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#  define GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 0x8A45
#  define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#  define GL_INVALID_INDEX 0xFFFFFFFF
# 
# endif /* GL_VERSION_3_1 */
# if defined GL_VERSION_3_2
# 
#  define GL_CONTEXT_CORE_PROFILE_BIT 0x00000001
#  define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#  define GL_LINES_ADJACENCY 0x000A
#  define GL_LINE_STRIP_ADJACENCY 0x000B
#  define GL_TRIANGLES_ADJACENCY 0x000C
#  define GL_TRIANGLE_STRIP_ADJACENCY 0x000D
#  define GL_PROGRAM_POINT_SIZE 0x8642
#  define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#  define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#  define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#  define GL_GEOMETRY_SHADER 0x8DD9
#  define GL_GEOMETRY_VERTICES_OUT 0x8916
#  define GL_GEOMETRY_INPUT_TYPE 0x8917
#  define GL_GEOMETRY_OUTPUT_TYPE 0x8918
#  define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#  define GL_MAX_GEOMETRY_OUTPUT_VERTICES 0x8DE0
#  define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#  define GL_MAX_VERTEX_OUTPUT_COMPONENTS 0x9122
#  define GL_MAX_GEOMETRY_INPUT_COMPONENTS 0x9123
#  define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#  define GL_MAX_FRAGMENT_INPUT_COMPONENTS 0x9125
#  define GL_CONTEXT_PROFILE_MASK 0x9126
#  define GL_DEPTH_CLAMP 0x864F
#  define GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 0x8E4C
#  define GL_FIRST_VERTEX_CONVENTION 0x8E4D
#  define GL_LAST_VERTEX_CONVENTION 0x8E4E
#  define GL_PROVOKING_VERTEX 0x8E4F
#  define GL_TEXTURE_CUBE_MAP_SEAMLESS 0x884F
#  define GL_MAX_SERVER_WAIT_TIMEOUT 0x9111
#  define GL_OBJECT_TYPE 0x9112
#  define GL_SYNC_CONDITION 0x9113
#  define GL_SYNC_STATUS 0x9114
#  define GL_SYNC_FLAGS 0x9115
#  define GL_SYNC_FENCE 0x9116
#  define GL_SYNC_GPU_COMMANDS_COMPLETE 0x9117
#  define GL_UNSIGNALED 0x9118
#  define GL_SIGNALED 0x9119
#  define GL_ALREADY_SIGNALED 0x911A
#  define GL_TIMEOUT_EXPIRED 0x911B
#  define GL_CONDITION_SATISFIED 0x911C
#  define GL_WAIT_FAILED 0x911D
#  define GL_TIMEOUT_IGNORED 0xFFFFFFFFFFFFFFFF
#  define GL_SYNC_FLUSH_COMMANDS_BIT 0x00000001
#  define GL_SAMPLE_POSITION 0x8E50
#  define GL_SAMPLE_MASK 0x8E51
#  define GL_SAMPLE_MASK_VALUE 0x8E52
#  define GL_MAX_SAMPLE_MASK_WORDS 0x8E59
#  define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#  define GL_PROXY_TEXTURE_2D_MULTISAMPLE 0x9101
#  define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#  define GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9103
#  define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#  define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#  define GL_TEXTURE_SAMPLES 0x9106
#  define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#  define GL_SAMPLER_2D_MULTISAMPLE 0x9108
#  define GL_INT_SAMPLER_2D_MULTISAMPLE 0x9109
#  define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#  define GL_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910B
#  define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#  define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
#  define GL_MAX_COLOR_TEXTURE_SAMPLES 0x910E
#  define GL_MAX_DEPTH_TEXTURE_SAMPLES 0x910F
#  define GL_MAX_INTEGER_SAMPLES 0x9110
# 
# endif /* GL_VERSION_3_2 */
# if defined GL_VERSION_3_3
# 
#  define GL_VERTEX_ATTRIB_ARRAY_DIVISOR 0x88FE
#  define GL_SRC1_COLOR 0x88F9
#  define GL_ONE_MINUS_SRC1_COLOR 0x88FA
#  define GL_ONE_MINUS_SRC1_ALPHA 0x88FB
#  define GL_MAX_DUAL_SOURCE_DRAW_BUFFERS 0x88FC
#  define GL_ANY_SAMPLES_PASSED 0x8C2F
#  define GL_SAMPLER_BINDING 0x8919
#  define GL_RGB10_A2UI 0x906F
#  define GL_TEXTURE_SWIZZLE_R 0x8E42
#  define GL_TEXTURE_SWIZZLE_G 0x8E43
#  define GL_TEXTURE_SWIZZLE_B 0x8E44
#  define GL_TEXTURE_SWIZZLE_A 0x8E45
#  define GL_TEXTURE_SWIZZLE_RGBA 0x8E46
#  define GL_TIME_ELAPSED 0x88BF
#  define GL_TIMESTAMP 0x8E28
#  define GL_INT_2_10_10_10_REV 0x8D9F
# 
# endif /* GL_VERSION_3_3 */
# if defined GL_VERSION_4_0
# 
#  define GL_SAMPLE_SHADING 0x8C36
#  define GL_MIN_SAMPLE_SHADING_VALUE 0x8C37
#  define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
#  define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
#  define GL_TEXTURE_CUBE_MAP_ARRAY 0x9009
#  define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#  define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY 0x900B
#  define GL_SAMPLER_CUBE_MAP_ARRAY 0x900C
#  define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 0x900D
#  define GL_INT_SAMPLER_CUBE_MAP_ARRAY 0x900E
#  define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#  define GL_DRAW_INDIRECT_BUFFER 0x8F3F
#  define GL_DRAW_INDIRECT_BUFFER_BINDING 0x8F43
#  define GL_GEOMETRY_SHADER_INVOCATIONS 0x887F
#  define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#  define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
#  define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
#  define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
#  define GL_MAX_VERTEX_STREAMS 0x8E71
#  define GL_DOUBLE_VEC2 0x8FFC
#  define GL_DOUBLE_VEC3 0x8FFD
#  define GL_DOUBLE_VEC4 0x8FFE
#  define GL_DOUBLE_MAT2 0x8F46
#  define GL_DOUBLE_MAT3 0x8F47
#  define GL_DOUBLE_MAT4 0x8F48
#  define GL_DOUBLE_MAT2x3 0x8F49
#  define GL_DOUBLE_MAT2x4 0x8F4A
#  define GL_DOUBLE_MAT3x2 0x8F4B
#  define GL_DOUBLE_MAT3x4 0x8F4C
#  define GL_DOUBLE_MAT4x2 0x8F4D
#  define GL_DOUBLE_MAT4x3 0x8F4E
#  define GL_ACTIVE_SUBROUTINES 0x8DE5
#  define GL_ACTIVE_SUBROUTINE_UNIFORMS 0x8DE6
#  define GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 0x8E47
#  define GL_ACTIVE_SUBROUTINE_MAX_LENGTH 0x8E48
#  define GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 0x8E49
#  define GL_MAX_SUBROUTINES 0x8DE7
#  define GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 0x8DE8
#  define GL_NUM_COMPATIBLE_SUBROUTINES 0x8E4A
#  define GL_COMPATIBLE_SUBROUTINES 0x8E4B
#  define GL_PATCHES 0x000E
#  define GL_PATCH_VERTICES 0x8E72
#  define GL_PATCH_DEFAULT_INNER_LEVEL 0x8E73
#  define GL_PATCH_DEFAULT_OUTER_LEVEL 0x8E74
#  define GL_TESS_CONTROL_OUTPUT_VERTICES 0x8E75
#  define GL_TESS_GEN_MODE 0x8E76
#  define GL_TESS_GEN_SPACING 0x8E77
#  define GL_TESS_GEN_VERTEX_ORDER 0x8E78
#  define GL_TESS_GEN_POINT_MODE 0x8E79
#  define GL_ISOLINES 0x8E7A
#  define GL_QUADS 0x0007
#  define GL_FRACTIONAL_ODD 0x8E7B
#  define GL_FRACTIONAL_EVEN 0x8E7C
#  define GL_MAX_PATCH_VERTICES 0x8E7D
#  define GL_MAX_TESS_GEN_LEVEL 0x8E7E
#  define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
#  define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
#  define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#  define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#  define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#  define GL_MAX_TESS_PATCH_COMPONENTS 0x8E84
#  define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8E85
#  define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#  define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
#  define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
#  define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886C
#  define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886D
#  define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
#  define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
#  define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 0x84F0
#  define GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 0x84F1
#  define GL_TESS_EVALUATION_SHADER 0x8E87
#  define GL_TESS_CONTROL_SHADER 0x8E88
#  define GL_TRANSFORM_FEEDBACK 0x8E22
#  define GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 0x8E23
#  define GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 0x8E24
#  define GL_TRANSFORM_FEEDBACK_BINDING 0x8E25
#  define GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 0x8E70
#  define GL_MAX_VERTEX_STREAMS 0x8E71
# 
# endif /* GL_VERSION_4_0 */
# if defined GL_VERSION_4_1
# 
#  define GL_FIXED 0x140C
#  define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#  define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#  define GL_LOW_FLOAT 0x8DF0
#  define GL_MEDIUM_FLOAT 0x8DF1
#  define GL_HIGH_FLOAT 0x8DF2
#  define GL_LOW_INT 0x8DF3
#  define GL_MEDIUM_INT 0x8DF4
#  define GL_HIGH_INT 0x8DF5
#  define GL_SHADER_COMPILER 0x8DFA
#  define GL_SHADER_BINARY_FORMATS 0x8DF8
#  define GL_NUM_SHADER_BINARY_FORMATS 0x8DF9
#  define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8DFB
#  define GL_MAX_VARYING_VECTORS 0x8DFC
#  define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8DFD
#  define GL_RGB565 0x8D62
#  define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#  define GL_PROGRAM_BINARY_LENGTH 0x8741
#  define GL_NUM_PROGRAM_BINARY_FORMATS 0x87FE
#  define GL_PROGRAM_BINARY_FORMATS 0x87FF
#  define GL_VERTEX_SHADER_BIT 0x00000001
#  define GL_FRAGMENT_SHADER_BIT 0x00000002
#  define GL_GEOMETRY_SHADER_BIT 0x00000004
#  define GL_TESS_CONTROL_SHADER_BIT 0x00000008
#  define GL_TESS_EVALUATION_SHADER_BIT 0x00000010
#  define GL_ALL_SHADER_BITS 0xFFFFFFFF
#  define GL_PROGRAM_SEPARABLE 0x8258
#  define GL_ACTIVE_PROGRAM 0x8259
#  define GL_PROGRAM_PIPELINE_BINDING 0x825A
#  define GL_MAX_VIEWPORTS 0x825B
#  define GL_VIEWPORT_SUBPIXEL_BITS 0x825C
#  define GL_VIEWPORT_BOUNDS_RANGE 0x825D
#  define GL_LAYER_PROVOKING_VERTEX 0x825E
#  define GL_VIEWPORT_INDEX_PROVOKING_VERTEX 0x825F
#  define GL_UNDEFINED_VERTEX 0x8260
# 
# endif /* GL_VERSION_4_1 */
# if defined GL_VERSION_4_2
# 
#  define GL_COPY_READ_BUFFER_BINDING 0x8F36
#  define GL_COPY_WRITE_BUFFER_BINDING 0x8F37
#  define GL_TRANSFORM_FEEDBACK_ACTIVE 0x8E24
#  define GL_TRANSFORM_FEEDBACK_PAUSED 0x8E23
#  define GL_UNPACK_COMPRESSED_BLOCK_WIDTH 0x9127
#  define GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 0x9128
#  define GL_UNPACK_COMPRESSED_BLOCK_DEPTH 0x9129
#  define GL_UNPACK_COMPRESSED_BLOCK_SIZE 0x912A
#  define GL_PACK_COMPRESSED_BLOCK_WIDTH 0x912B
#  define GL_PACK_COMPRESSED_BLOCK_HEIGHT 0x912C
#  define GL_PACK_COMPRESSED_BLOCK_DEPTH 0x912D
#  define GL_PACK_COMPRESSED_BLOCK_SIZE 0x912E
#  define GL_NUM_SAMPLE_COUNTS 0x9380
#  define GL_MIN_MAP_BUFFER_ALIGNMENT 0x90BC
#  define GL_ATOMIC_COUNTER_BUFFER 0x92C0
#  define GL_ATOMIC_COUNTER_BUFFER_BINDING 0x92C1
#  define GL_ATOMIC_COUNTER_BUFFER_START 0x92C2
#  define GL_ATOMIC_COUNTER_BUFFER_SIZE 0x92C3
#  define GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 0x92C4
#  define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 0x92C5
#  define GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 0x92C6
#  define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 0x92C7
#  define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 0x92C8
#  define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 0x92C9
#  define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 0x92CA
#  define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 0x92CB
#  define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92CC
#  define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#  define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#  define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#  define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#  define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#  define GL_MAX_VERTEX_ATOMIC_COUNTERS 0x92D2
#  define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#  define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#  define GL_MAX_GEOMETRY_ATOMIC_COUNTERS 0x92D5
#  define GL_MAX_FRAGMENT_ATOMIC_COUNTERS 0x92D6
#  define GL_MAX_COMBINED_ATOMIC_COUNTERS 0x92D7
#  define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92D8
#  define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92DC
#  define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS 0x92D9
#  define GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 0x92DA
#  define GL_UNSIGNED_INT_ATOMIC_COUNTER 0x92DB
#  define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#  define GL_ELEMENT_ARRAY_BARRIER_BIT 0x00000002
#  define GL_UNIFORM_BARRIER_BIT 0x00000004
#  define GL_TEXTURE_FETCH_BARRIER_BIT 0x00000008
#  define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#  define GL_COMMAND_BARRIER_BIT 0x00000040
#  define GL_PIXEL_BUFFER_BARRIER_BIT 0x00000080
#  define GL_TEXTURE_UPDATE_BARRIER_BIT 0x00000100
#  define GL_BUFFER_UPDATE_BARRIER_BIT 0x00000200
#  define GL_FRAMEBUFFER_BARRIER_BIT 0x00000400
#  define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
#  define GL_ATOMIC_COUNTER_BARRIER_BIT 0x00001000
#  define GL_ALL_BARRIER_BITS 0xFFFFFFFF
#  define GL_MAX_IMAGE_UNITS 0x8F38
#  define GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 0x8F39
#  define GL_IMAGE_BINDING_NAME 0x8F3A
#  define GL_IMAGE_BINDING_LEVEL 0x8F3B
#  define GL_IMAGE_BINDING_LAYERED 0x8F3C
#  define GL_IMAGE_BINDING_LAYER 0x8F3D
#  define GL_IMAGE_BINDING_ACCESS 0x8F3E
#  define GL_IMAGE_1D 0x904C
#  define GL_IMAGE_2D 0x904D
#  define GL_IMAGE_3D 0x904E
#  define GL_IMAGE_2D_RECT 0x904F
#  define GL_IMAGE_CUBE 0x9050
#  define GL_IMAGE_BUFFER 0x9051
#  define GL_IMAGE_1D_ARRAY 0x9052
#  define GL_IMAGE_2D_ARRAY 0x9053
#  define GL_IMAGE_CUBE_MAP_ARRAY 0x9054
#  define GL_IMAGE_2D_MULTISAMPLE 0x9055
#  define GL_IMAGE_2D_MULTISAMPLE_ARRAY 0x9056
#  define GL_INT_IMAGE_1D 0x9057
#  define GL_INT_IMAGE_2D 0x9058
#  define GL_INT_IMAGE_3D 0x9059
#  define GL_INT_IMAGE_2D_RECT 0x905A
#  define GL_INT_IMAGE_CUBE 0x905B
#  define GL_INT_IMAGE_BUFFER 0x905C
#  define GL_INT_IMAGE_1D_ARRAY 0x905D
#  define GL_INT_IMAGE_2D_ARRAY 0x905E
#  define GL_INT_IMAGE_CUBE_MAP_ARRAY 0x905F
#  define GL_INT_IMAGE_2D_MULTISAMPLE 0x9060
#  define GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x9061
#  define GL_UNSIGNED_INT_IMAGE_1D 0x9062
#  define GL_UNSIGNED_INT_IMAGE_2D 0x9063
#  define GL_UNSIGNED_INT_IMAGE_3D 0x9064
#  define GL_UNSIGNED_INT_IMAGE_2D_RECT 0x9065
#  define GL_UNSIGNED_INT_IMAGE_CUBE 0x9066
#  define GL_UNSIGNED_INT_IMAGE_BUFFER 0x9067
#  define GL_UNSIGNED_INT_IMAGE_1D_ARRAY 0x9068
#  define GL_UNSIGNED_INT_IMAGE_2D_ARRAY 0x9069
#  define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#  define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 0x906B
#  define GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 0x906C
#  define GL_MAX_IMAGE_SAMPLES 0x906D
#  define GL_IMAGE_BINDING_FORMAT 0x906E
#  define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#  define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90C8
#  define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#  define GL_MAX_VERTEX_IMAGE_UNIFORMS 0x90CA
#  define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#  define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#  define GL_MAX_GEOMETRY_IMAGE_UNIFORMS 0x90CD
#  define GL_MAX_FRAGMENT_IMAGE_UNIFORMS 0x90CE
#  define GL_MAX_COMBINED_IMAGE_UNIFORMS 0x90CF
#  define GL_COMPRESSED_RGBA_BPTC_UNORM 0x8E8C
#  define GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM 0x8E8D
#  define GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT 0x8E8E
#  define GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT 0x8E8F
#  define GL_TEXTURE_IMMUTABLE_FORMAT 0x912F
# 
# endif /* GL_VERSION_4_2 */
# if defined GL_VERSION_4_3
# 
#  define GL_NUM_SHADING_LANGUAGE_VERSIONS 0x82E9
#  define GL_VERTEX_ATTRIB_ARRAY_LONG 0x874E
#  define GL_COMPRESSED_RGB8_ETC2 0x9274
#  define GL_COMPRESSED_SRGB8_ETC2 0x9275
#  define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#  define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#  define GL_COMPRESSED_RGBA8_ETC2_EAC 0x9278
#  define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#  define GL_COMPRESSED_R11_EAC 0x9270
#  define GL_COMPRESSED_SIGNED_R11_EAC 0x9271
#  define GL_COMPRESSED_RG11_EAC 0x9272
#  define GL_COMPRESSED_SIGNED_RG11_EAC 0x9273
#  define GL_PRIMITIVE_RESTART_FIXED_INDEX 0x8D69
#  define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#  define GL_MAX_ELEMENT_INDEX 0x8D6B
#  define GL_COMPUTE_SHADER 0x91B9
#  define GL_MAX_COMPUTE_UNIFORM_BLOCKS 0x91BB
#  define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#  define GL_MAX_COMPUTE_IMAGE_UNIFORMS 0x91BD
#  define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#  define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#  define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#  define GL_MAX_COMPUTE_ATOMIC_COUNTERS 0x8265
#  define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#  define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90EB
#  define GL_MAX_COMPUTE_WORK_GROUP_COUNT 0x91BE
#  define GL_MAX_COMPUTE_WORK_GROUP_SIZE 0x91BF
#  define GL_COMPUTE_WORK_GROUP_SIZE 0x8267
#  define GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 0x90EC
#  define GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 0x90ED
#  define GL_DISPATCH_INDIRECT_BUFFER 0x90EE
#  define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90EF
#  define GL_COMPUTE_SHADER_BIT 0x00000020
#  define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#  define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#  define GL_DEBUG_CALLBACK_FUNCTION 0x8244
#  define GL_DEBUG_CALLBACK_USER_PARAM 0x8245
#  define GL_DEBUG_SOURCE_API 0x8246
#  define GL_DEBUG_SOURCE_WINDOW_SYSTEM 0x8247
#  define GL_DEBUG_SOURCE_SHADER_COMPILER 0x8248
#  define GL_DEBUG_SOURCE_THIRD_PARTY 0x8249
#  define GL_DEBUG_SOURCE_APPLICATION 0x824A
#  define GL_DEBUG_SOURCE_OTHER 0x824B
#  define GL_DEBUG_TYPE_ERROR 0x824C
#  define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#  define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR 0x824E
#  define GL_DEBUG_TYPE_PORTABILITY 0x824F
#  define GL_DEBUG_TYPE_PERFORMANCE 0x8250
#  define GL_DEBUG_TYPE_OTHER 0x8251
#  define GL_MAX_DEBUG_MESSAGE_LENGTH 0x9143
#  define GL_MAX_DEBUG_LOGGED_MESSAGES 0x9144
#  define GL_DEBUG_LOGGED_MESSAGES 0x9145
#  define GL_DEBUG_SEVERITY_HIGH 0x9146
#  define GL_DEBUG_SEVERITY_MEDIUM 0x9147
#  define GL_DEBUG_SEVERITY_LOW 0x9148
#  define GL_DEBUG_TYPE_MARKER 0x8268
#  define GL_DEBUG_TYPE_PUSH_GROUP 0x8269
#  define GL_DEBUG_TYPE_POP_GROUP 0x826A
#  define GL_DEBUG_SEVERITY_NOTIFICATION 0x826B
#  define GL_MAX_DEBUG_GROUP_STACK_DEPTH 0x826C
#  define GL_DEBUG_GROUP_STACK_DEPTH 0x826D
#  define GL_BUFFER 0x82E0
#  define GL_SHADER 0x82E1
#  define GL_PROGRAM 0x82E2
#  define GL_VERTEX_ARRAY 0x8074
#  define GL_QUERY 0x82E3
#  define GL_PROGRAM_PIPELINE 0x82E4
#  define GL_SAMPLER 0x82E6
#  define GL_MAX_LABEL_LENGTH 0x82E8
#  define GL_DEBUG_OUTPUT 0x92E0
#  define GL_CONTEXT_FLAG_DEBUG_BIT 0x00000002
#  define GL_MAX_UNIFORM_LOCATIONS 0x826E
#  define GL_FRAMEBUFFER_DEFAULT_WIDTH 0x9310
#  define GL_FRAMEBUFFER_DEFAULT_HEIGHT 0x9311
#  define GL_FRAMEBUFFER_DEFAULT_LAYERS 0x9312
#  define GL_FRAMEBUFFER_DEFAULT_SAMPLES 0x9313
#  define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#  define GL_MAX_FRAMEBUFFER_WIDTH 0x9315
#  define GL_MAX_FRAMEBUFFER_HEIGHT 0x9316
#  define GL_MAX_FRAMEBUFFER_LAYERS 0x9317
#  define GL_MAX_FRAMEBUFFER_SAMPLES 0x9318
#  define GL_INTERNALFORMAT_SUPPORTED 0x826F
#  define GL_INTERNALFORMAT_PREFERRED 0x8270
#  define GL_INTERNALFORMAT_RED_SIZE 0x8271
#  define GL_INTERNALFORMAT_GREEN_SIZE 0x8272
#  define GL_INTERNALFORMAT_BLUE_SIZE 0x8273
#  define GL_INTERNALFORMAT_ALPHA_SIZE 0x8274
#  define GL_INTERNALFORMAT_DEPTH_SIZE 0x8275
#  define GL_INTERNALFORMAT_STENCIL_SIZE 0x8276
#  define GL_INTERNALFORMAT_SHARED_SIZE 0x8277
#  define GL_INTERNALFORMAT_RED_TYPE 0x8278
#  define GL_INTERNALFORMAT_GREEN_TYPE 0x8279
#  define GL_INTERNALFORMAT_BLUE_TYPE 0x827A
#  define GL_INTERNALFORMAT_ALPHA_TYPE 0x827B
#  define GL_INTERNALFORMAT_DEPTH_TYPE 0x827C
#  define GL_INTERNALFORMAT_STENCIL_TYPE 0x827D
#  define GL_MAX_WIDTH 0x827E
#  define GL_MAX_HEIGHT 0x827F
#  define GL_MAX_DEPTH 0x8280
#  define GL_MAX_LAYERS 0x8281
#  define GL_MAX_COMBINED_DIMENSIONS 0x8282
#  define GL_COLOR_COMPONENTS 0x8283
#  define GL_DEPTH_COMPONENTS 0x8284
#  define GL_STENCIL_COMPONENTS 0x8285
#  define GL_COLOR_RENDERABLE 0x8286
#  define GL_DEPTH_RENDERABLE 0x8287
#  define GL_STENCIL_RENDERABLE 0x8288
#  define GL_FRAMEBUFFER_RENDERABLE 0x8289
#  define GL_FRAMEBUFFER_RENDERABLE_LAYERED 0x828A
#  define GL_FRAMEBUFFER_BLEND 0x828B
#  define GL_READ_PIXELS 0x828C
#  define GL_READ_PIXELS_FORMAT 0x828D
#  define GL_READ_PIXELS_TYPE 0x828E
#  define GL_TEXTURE_IMAGE_FORMAT 0x828F
#  define GL_TEXTURE_IMAGE_TYPE 0x8290
#  define GL_GET_TEXTURE_IMAGE_FORMAT 0x8291
#  define GL_GET_TEXTURE_IMAGE_TYPE 0x8292
#  define GL_MIPMAP 0x8293
#  define GL_MANUAL_GENERATE_MIPMAP 0x8294
#  define GL_AUTO_GENERATE_MIPMAP 0x8295
#  define GL_COLOR_ENCODING 0x8296
#  define GL_SRGB_READ 0x8297
#  define GL_SRGB_WRITE 0x8298
#  define GL_FILTER 0x829A
#  define GL_VERTEX_TEXTURE 0x829B
#  define GL_TESS_CONTROL_TEXTURE 0x829C
#  define GL_TESS_EVALUATION_TEXTURE 0x829D
#  define GL_GEOMETRY_TEXTURE 0x829E
#  define GL_FRAGMENT_TEXTURE 0x829F
#  define GL_COMPUTE_TEXTURE 0x82A0
#  define GL_TEXTURE_SHADOW 0x82A1
#  define GL_TEXTURE_GATHER 0x82A2
#  define GL_TEXTURE_GATHER_SHADOW 0x82A3
#  define GL_SHADER_IMAGE_LOAD 0x82A4
#  define GL_SHADER_IMAGE_STORE 0x82A5
#  define GL_SHADER_IMAGE_ATOMIC 0x82A6
#  define GL_IMAGE_TEXEL_SIZE 0x82A7
#  define GL_IMAGE_COMPATIBILITY_CLASS 0x82A8
#  define GL_IMAGE_PIXEL_FORMAT 0x82A9
#  define GL_IMAGE_PIXEL_TYPE 0x82AA
#  define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 0x82AC
#  define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 0x82AD
#  define GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 0x82AE
#  define GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 0x82AF
#  define GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 0x82B1
#  define GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 0x82B2
#  define GL_TEXTURE_COMPRESSED_BLOCK_SIZE 0x82B3
#  define GL_CLEAR_BUFFER 0x82B4
#  define GL_TEXTURE_VIEW 0x82B5
#  define GL_VIEW_COMPATIBILITY_CLASS 0x82B6
#  define GL_FULL_SUPPORT 0x82B7
#  define GL_CAVEAT_SUPPORT 0x82B8
#  define GL_IMAGE_CLASS_4_X_32 0x82B9
#  define GL_IMAGE_CLASS_2_X_32 0x82BA
#  define GL_IMAGE_CLASS_1_X_32 0x82BB
#  define GL_IMAGE_CLASS_4_X_16 0x82BC
#  define GL_IMAGE_CLASS_2_X_16 0x82BD
#  define GL_IMAGE_CLASS_1_X_16 0x82BE
#  define GL_IMAGE_CLASS_4_X_8 0x82BF
#  define GL_IMAGE_CLASS_2_X_8 0x82C0
#  define GL_IMAGE_CLASS_1_X_8 0x82C1
#  define GL_IMAGE_CLASS_11_11_10 0x82C2
#  define GL_IMAGE_CLASS_10_10_10_2 0x82C3
#  define GL_VIEW_CLASS_128_BITS 0x82C4
#  define GL_VIEW_CLASS_96_BITS 0x82C5
#  define GL_VIEW_CLASS_64_BITS 0x82C6
#  define GL_VIEW_CLASS_48_BITS 0x82C7
#  define GL_VIEW_CLASS_32_BITS 0x82C8
#  define GL_VIEW_CLASS_24_BITS 0x82C9
#  define GL_VIEW_CLASS_16_BITS 0x82CA
#  define GL_VIEW_CLASS_8_BITS 0x82CB
#  define GL_VIEW_CLASS_S3TC_DXT1_RGB 0x82CC
#  define GL_VIEW_CLASS_S3TC_DXT1_RGBA 0x82CD
#  define GL_VIEW_CLASS_S3TC_DXT3_RGBA 0x82CE
#  define GL_VIEW_CLASS_S3TC_DXT5_RGBA 0x82CF
#  define GL_VIEW_CLASS_RGTC1_RED 0x82D0
#  define GL_VIEW_CLASS_RGTC2_RG 0x82D1
#  define GL_VIEW_CLASS_BPTC_UNORM 0x82D2
#  define GL_VIEW_CLASS_BPTC_FLOAT 0x82D3
#  define GL_UNIFORM 0x92E1
#  define GL_UNIFORM_BLOCK 0x92E2
#  define GL_PROGRAM_INPUT 0x92E3
#  define GL_PROGRAM_OUTPUT 0x92E4
#  define GL_BUFFER_VARIABLE 0x92E5
#  define GL_SHADER_STORAGE_BLOCK 0x92E6
#  define GL_VERTEX_SUBROUTINE 0x92E8
#  define GL_TESS_CONTROL_SUBROUTINE 0x92E9
#  define GL_TESS_EVALUATION_SUBROUTINE 0x92EA
#  define GL_GEOMETRY_SUBROUTINE 0x92EB
#  define GL_FRAGMENT_SUBROUTINE 0x92EC
#  define GL_COMPUTE_SUBROUTINE 0x92ED
#  define GL_VERTEX_SUBROUTINE_UNIFORM 0x92EE
#  define GL_TESS_CONTROL_SUBROUTINE_UNIFORM 0x92EF
#  define GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 0x92F0
#  define GL_GEOMETRY_SUBROUTINE_UNIFORM 0x92F1
#  define GL_FRAGMENT_SUBROUTINE_UNIFORM 0x92F2
#  define GL_COMPUTE_SUBROUTINE_UNIFORM 0x92F3
#  define GL_TRANSFORM_FEEDBACK_VARYING 0x92F4
#  define GL_ACTIVE_RESOURCES 0x92F5
#  define GL_MAX_NAME_LENGTH 0x92F6
#  define GL_MAX_NUM_ACTIVE_VARIABLES 0x92F7
#  define GL_MAX_NUM_COMPATIBLE_SUBROUTINES 0x92F8
#  define GL_NAME_LENGTH 0x92F9
#  define GL_TYPE 0x92FA
#  define GL_ARRAY_SIZE 0x92FB
#  define GL_OFFSET 0x92FC
#  define GL_BLOCK_INDEX 0x92FD
#  define GL_ARRAY_STRIDE 0x92FE
#  define GL_MATRIX_STRIDE 0x92FF
#  define GL_IS_ROW_MAJOR 0x9300
#  define GL_ATOMIC_COUNTER_BUFFER_INDEX 0x9301
#  define GL_BUFFER_BINDING 0x9302
#  define GL_BUFFER_DATA_SIZE 0x9303
#  define GL_NUM_ACTIVE_VARIABLES 0x9304
#  define GL_ACTIVE_VARIABLES 0x9305
#  define GL_REFERENCED_BY_VERTEX_SHADER 0x9306
#  define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#  define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#  define GL_REFERENCED_BY_GEOMETRY_SHADER 0x9309
#  define GL_REFERENCED_BY_FRAGMENT_SHADER 0x930A
#  define GL_REFERENCED_BY_COMPUTE_SHADER 0x930B
#  define GL_TOP_LEVEL_ARRAY_SIZE 0x930C
#  define GL_TOP_LEVEL_ARRAY_STRIDE 0x930D
#  define GL_LOCATION 0x930E
#  define GL_LOCATION_INDEX 0x930F
#  define GL_IS_PER_PATCH 0x92E7
#  define GL_SHADER_STORAGE_BUFFER 0x90D2
#  define GL_SHADER_STORAGE_BUFFER_BINDING 0x90D3
#  define GL_SHADER_STORAGE_BUFFER_START 0x90D4
#  define GL_SHADER_STORAGE_BUFFER_SIZE 0x90D5
#  define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90D6
#  define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90D7
#  define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90D8
#  define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90D9
#  define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90DA
#  define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90DB
#  define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90DC
#  define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90DD
#  define GL_MAX_SHADER_STORAGE_BLOCK_SIZE 0x90DE
#  define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90DF
#  define GL_SHADER_STORAGE_BARRIER_BIT 0x00002000
#  define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#  define GL_DEPTH_STENCIL_TEXTURE_MODE 0x90EA
#  define GL_TEXTURE_BUFFER_OFFSET 0x919D
#  define GL_TEXTURE_BUFFER_SIZE 0x919E
#  define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919F
#  define GL_TEXTURE_VIEW_MIN_LEVEL 0x82DB
#  define GL_TEXTURE_VIEW_NUM_LEVELS 0x82DC
#  define GL_TEXTURE_VIEW_MIN_LAYER 0x82DD
#  define GL_TEXTURE_VIEW_NUM_LAYERS 0x82DE
#  define GL_TEXTURE_IMMUTABLE_LEVELS 0x82DF
#  define GL_VERTEX_ATTRIB_BINDING 0x82D4
#  define GL_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D5
#  define GL_VERTEX_BINDING_DIVISOR 0x82D6
#  define GL_VERTEX_BINDING_OFFSET 0x82D7
#  define GL_VERTEX_BINDING_STRIDE 0x82D8
#  define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D9
#  define GL_MAX_VERTEX_ATTRIB_BINDINGS 0x82DA
#  define GL_VERTEX_BINDING_BUFFER 0x8F4F
#  define GL_DISPLAY_LIST 0x82E7
#  define GL_STACK_UNDERFLOW 0x0504
#  define GL_STACK_OVERFLOW 0x0503
# 
# endif /* GL_VERSION_4_3 */
# if defined GL_VERSION_4_4
# 
#  define GL_MAX_VERTEX_ATTRIB_STRIDE 0x82E5
#  define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#  define GL_TEXTURE_BUFFER_BINDING 0x8C2A
#  define GL_MAP_READ_BIT 0x0001
#  define GL_MAP_WRITE_BIT 0x0002
#  define GL_MAP_PERSISTENT_BIT 0x0040
#  define GL_MAP_COHERENT_BIT 0x0080
#  define GL_DYNAMIC_STORAGE_BIT 0x0100
#  define GL_CLIENT_STORAGE_BIT 0x0200
#  define GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 0x00004000
#  define GL_BUFFER_IMMUTABLE_STORAGE 0x821F
#  define GL_BUFFER_STORAGE_FLAGS 0x8220
#  define GL_CLEAR_TEXTURE 0x9365
#  define GL_LOCATION_COMPONENT 0x934A
#  define GL_TRANSFORM_FEEDBACK_BUFFER 0x8C8E
#  define GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 0x934B
#  define GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 0x934C
#  define GL_QUERY_BUFFER 0x9192
#  define GL_QUERY_BUFFER_BARRIER_BIT 0x00008000
#  define GL_QUERY_BUFFER_BINDING 0x9193
#  define GL_QUERY_RESULT_NO_WAIT 0x9194
#  define GL_MIRROR_CLAMP_TO_EDGE 0x8743
#  define GL_STENCIL_INDEX 0x1901
#  define GL_STENCIL_INDEX8 0x8D48
#  define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B
# 
# endif /* GL_VERSION_4_4 */
# if defined GL_VERSION_4_5
# 
#  define GL_CONTEXT_LOST 0x0507
#  define GL_LOWER_LEFT 0x8CA1
#  define GL_UPPER_LEFT 0x8CA2
#  define GL_NEGATIVE_ONE_TO_ONE 0x935E
#  define GL_ZERO_TO_ONE 0x935F
#  define GL_CLIP_ORIGIN 0x935C
#  define GL_CLIP_DEPTH_MODE 0x935D
#  define GL_QUERY_WAIT_INVERTED 0x8E17
#  define GL_QUERY_NO_WAIT_INVERTED 0x8E18
#  define GL_QUERY_BY_REGION_WAIT_INVERTED 0x8E19
#  define GL_QUERY_BY_REGION_NO_WAIT_INVERTED 0x8E1A
#  define GL_MAX_CULL_DISTANCES 0x82F9
#  define GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 0x82FA
#  define GL_TEXTURE_TARGET 0x1006
#  define GL_QUERY_TARGET 0x82EA
#  define GL_TEXTURE_BINDING_1D 0x8068
#  define GL_TEXTURE_BINDING_1D_ARRAY 0x8C1C
#  define GL_TEXTURE_BINDING_2D 0x8069
#  define GL_TEXTURE_BINDING_2D_ARRAY 0x8C1D
#  define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#  define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#  define GL_TEXTURE_BINDING_3D 0x806A
#  define GL_TEXTURE_BINDING_BUFFER 0x8C2C
#  define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#  define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#  define GL_TEXTURE_BINDING_RECTANGLE 0x84F6
#  define GL_BACK 0x0405
#  define GL_NO_ERROR 0
#  define GL_GUILTY_CONTEXT_RESET 0x8253
#  define GL_INNOCENT_CONTEXT_RESET 0x8254
#  define GL_UNKNOWN_CONTEXT_RESET 0x8255
#  define GL_RESET_NOTIFICATION_STRATEGY 0x8256
#  define GL_LOSE_CONTEXT_ON_RESET 0x8252
#  define GL_NO_RESET_NOTIFICATION 0x8261
#  define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 0x00000004
#  define GL_CONTEXT_LOST 0x0507
#  define GL_COLOR_TABLE 0x80D0
#  define GL_POST_CONVOLUTION_COLOR_TABLE 0x80D1
#  define GL_POST_COLOR_MATRIX_COLOR_TABLE 0x80D2
#  define GL_PROXY_COLOR_TABLE 0x80D3
#  define GL_PROXY_POST_CONVOLUTION_COLOR_TABLE 0x80D4
#  define GL_PROXY_POST_COLOR_MATRIX_COLOR_TABLE 0x80D5
#  define GL_CONVOLUTION_1D 0x8010
#  define GL_CONVOLUTION_2D 0x8011
#  define GL_SEPARABLE_2D 0x8012
#  define GL_HISTOGRAM 0x8024
#  define GL_PROXY_HISTOGRAM 0x8025
#  define GL_MINMAX 0x802E
#  define GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#  define GL_NONE 0
#  define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
# 
# endif /* GL_VERSION_4_5 */
# if defined GL_VERSION_4_6
# 
#  define GL_CONTEXT_RELEASE_BEHAVIOR 0x82FB
#  define GL_NONE 0
#  define GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 0x82FC
#  define GL_SHADER_BINARY_FORMAT_SPIR_V 0x9551
#  define GL_SPIR_V_BINARY 0x9552
#  define GL_PARAMETER_BUFFER 0x80EE
#  define GL_PARAMETER_BUFFER_BINDING 0x80EF
#  define GL_CONTEXT_FLAG_NO_ERROR_BIT 0x00000008
#  define GL_VERTICES_SUBMITTED 0x82EE
#  define GL_PRIMITIVES_SUBMITTED 0x82EF
#  define GL_VERTEX_SHADER_INVOCATIONS 0x82F0
#  define GL_TESS_CONTROL_SHADER_PATCHES 0x82F1
#  define GL_TESS_EVALUATION_SHADER_INVOCATIONS 0x82F2
#  define GL_GEOMETRY_SHADER_INVOCATIONS 0x887F
#  define GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED 0x82F3
#  define GL_FRAGMENT_SHADER_INVOCATIONS 0x82F4
#  define GL_COMPUTE_SHADER_INVOCATIONS 0x82F5
#  define GL_CLIPPING_INPUT_PRIMITIVES 0x82F6
#  define GL_CLIPPING_OUTPUT_PRIMITIVES 0x82F7
#  define GL_POLYGON_OFFSET_CLAMP 0x8E1B
#  define GL_SPIR_V_EXTENSIONS 0x9553
#  define GL_NUM_SPIR_V_EXTENSIONS 0x9554
#  define GL_TEXTURE_MAX_ANISOTROPY 0x84FE
#  define GL_MAX_TEXTURE_MAX_ANISOTROPY 0x84FF
#  define GL_TRANSFORM_FEEDBACK_OVERFLOW 0x82EC
#  define GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW 0x82ED
# 
# endif /* GL_VERSION_4_6 */
# if defined GL_VERSION_ES_CM_1_0
# 
#  define GL_VERSION_ES_CL_1_0 1
#  define GL_VERSION_ES_CM_1_1 1
#  define GL_VERSION_ES_CL_1_1 1
#  define GL_DEPTH_BUFFER_BIT 0x00000100
#  define GL_STENCIL_BUFFER_BIT 0x00000400
#  define GL_COLOR_BUFFER_BIT 0x00004000
#  define GL_FALSE 0
#  define GL_TRUE 1
#  define GL_POINTS 0x0000
#  define GL_LINES 0x0001
#  define GL_LINE_LOOP 0x0002
#  define GL_LINE_STRIP 0x0003
#  define GL_TRIANGLES 0x0004
#  define GL_TRIANGLE_STRIP 0x0005
#  define GL_TRIANGLE_FAN 0x0006
#  define GL_NEVER 0x0200
#  define GL_LESS 0x0201
#  define GL_EQUAL 0x0202
#  define GL_LEQUAL 0x0203
#  define GL_GREATER 0x0204
#  define GL_NOTEQUAL 0x0205
#  define GL_GEQUAL 0x0206
#  define GL_ALWAYS 0x0207
#  define GL_ZERO 0
#  define GL_ONE 1
#  define GL_SRC_COLOR 0x0300
#  define GL_ONE_MINUS_SRC_COLOR 0x0301
#  define GL_SRC_ALPHA 0x0302
#  define GL_ONE_MINUS_SRC_ALPHA 0x0303
#  define GL_DST_ALPHA 0x0304
#  define GL_ONE_MINUS_DST_ALPHA 0x0305
#  define GL_DST_COLOR 0x0306
#  define GL_ONE_MINUS_DST_COLOR 0x0307
#  define GL_SRC_ALPHA_SATURATE 0x0308
#  define GL_CLIP_PLANE0 0x3000
#  define GL_CLIP_PLANE1 0x3001
#  define GL_CLIP_PLANE2 0x3002
#  define GL_CLIP_PLANE3 0x3003
#  define GL_CLIP_PLANE4 0x3004
#  define GL_CLIP_PLANE5 0x3005
#  define GL_FRONT 0x0404
#  define GL_BACK 0x0405
#  define GL_FRONT_AND_BACK 0x0408
#  define GL_FOG 0x0B60
#  define GL_LIGHTING 0x0B50
#  define GL_TEXTURE_2D 0x0DE1
#  define GL_CULL_FACE 0x0B44
#  define GL_ALPHA_TEST 0x0BC0
#  define GL_BLEND 0x0BE2
#  define GL_COLOR_LOGIC_OP 0x0BF2
#  define GL_DITHER 0x0BD0
#  define GL_STENCIL_TEST 0x0B90
#  define GL_DEPTH_TEST 0x0B71
#  define GL_POINT_SMOOTH 0x0B10
#  define GL_LINE_SMOOTH 0x0B20
#  define GL_SCISSOR_TEST 0x0C11
#  define GL_COLOR_MATERIAL 0x0B57
#  define GL_NORMALIZE 0x0BA1
#  define GL_RESCALE_NORMAL 0x803A
#  define GL_VERTEX_ARRAY 0x8074
#  define GL_NORMAL_ARRAY 0x8075
#  define GL_COLOR_ARRAY 0x8076
#  define GL_TEXTURE_COORD_ARRAY 0x8078
#  define GL_MULTISAMPLE 0x809D
#  define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#  define GL_SAMPLE_ALPHA_TO_ONE 0x809F
#  define GL_SAMPLE_COVERAGE 0x80A0
#  define GL_NO_ERROR 0
#  define GL_INVALID_ENUM 0x0500
#  define GL_INVALID_VALUE 0x0501
#  define GL_INVALID_OPERATION 0x0502
#  define GL_STACK_OVERFLOW 0x0503
#  define GL_STACK_UNDERFLOW 0x0504
#  define GL_OUT_OF_MEMORY 0x0505
#  define GL_EXP 0x0800
#  define GL_EXP2 0x0801
#  define GL_FOG_DENSITY 0x0B62
#  define GL_FOG_START 0x0B63
#  define GL_FOG_END 0x0B64
#  define GL_FOG_MODE 0x0B65
#  define GL_FOG_COLOR 0x0B66
#  define GL_CW 0x0900
#  define GL_CCW 0x0901
#  define GL_CURRENT_COLOR 0x0B00
#  define GL_CURRENT_NORMAL 0x0B02
#  define GL_CURRENT_TEXTURE_COORDS 0x0B03
#  define GL_POINT_SIZE 0x0B11
#  define GL_POINT_SIZE_MIN 0x8126
#  define GL_POINT_SIZE_MAX 0x8127
#  define GL_POINT_FADE_THRESHOLD_SIZE 0x8128
#  define GL_POINT_DISTANCE_ATTENUATION 0x8129
#  define GL_SMOOTH_POINT_SIZE_RANGE 0x0B12
#  define GL_LINE_WIDTH 0x0B21
#  define GL_SMOOTH_LINE_WIDTH_RANGE 0x0B22
#  define GL_ALIASED_POINT_SIZE_RANGE 0x846D
#  define GL_ALIASED_LINE_WIDTH_RANGE 0x846E
#  define GL_CULL_FACE_MODE 0x0B45
#  define GL_FRONT_FACE 0x0B46
#  define GL_SHADE_MODEL 0x0B54
#  define GL_DEPTH_RANGE 0x0B70
#  define GL_DEPTH_WRITEMASK 0x0B72
#  define GL_DEPTH_CLEAR_VALUE 0x0B73
#  define GL_DEPTH_FUNC 0x0B74
#  define GL_STENCIL_CLEAR_VALUE 0x0B91
#  define GL_STENCIL_FUNC 0x0B92
#  define GL_STENCIL_VALUE_MASK 0x0B93
#  define GL_STENCIL_FAIL 0x0B94
#  define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#  define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#  define GL_STENCIL_REF 0x0B97
#  define GL_STENCIL_WRITEMASK 0x0B98
#  define GL_MATRIX_MODE 0x0BA0
#  define GL_VIEWPORT 0x0BA2
#  define GL_MODELVIEW_STACK_DEPTH 0x0BA3
#  define GL_PROJECTION_STACK_DEPTH 0x0BA4
#  define GL_TEXTURE_STACK_DEPTH 0x0BA5
#  define GL_MODELVIEW_MATRIX 0x0BA6
#  define GL_PROJECTION_MATRIX 0x0BA7
#  define GL_TEXTURE_MATRIX 0x0BA8
#  define GL_ALPHA_TEST_FUNC 0x0BC1
#  define GL_ALPHA_TEST_REF 0x0BC2
#  define GL_BLEND_DST 0x0BE0
#  define GL_BLEND_SRC 0x0BE1
#  define GL_LOGIC_OP_MODE 0x0BF0
#  define GL_SCISSOR_BOX 0x0C10
#  define GL_COLOR_CLEAR_VALUE 0x0C22
#  define GL_COLOR_WRITEMASK 0x0C23
#  define GL_MAX_LIGHTS 0x0D31
#  define GL_MAX_CLIP_PLANES 0x0D32
#  define GL_MAX_TEXTURE_SIZE 0x0D33
#  define GL_MAX_MODELVIEW_STACK_DEPTH 0x0D36
#  define GL_MAX_PROJECTION_STACK_DEPTH 0x0D38
#  define GL_MAX_TEXTURE_STACK_DEPTH 0x0D39
#  define GL_MAX_VIEWPORT_DIMS 0x0D3A
#  define GL_MAX_TEXTURE_UNITS 0x84E2
#  define GL_SUBPIXEL_BITS 0x0D50
#  define GL_RED_BITS 0x0D52
#  define GL_GREEN_BITS 0x0D53
#  define GL_BLUE_BITS 0x0D54
#  define GL_ALPHA_BITS 0x0D55
#  define GL_DEPTH_BITS 0x0D56
#  define GL_STENCIL_BITS 0x0D57
#  define GL_POLYGON_OFFSET_UNITS 0x2A00
#  define GL_POLYGON_OFFSET_FILL 0x8037
#  define GL_POLYGON_OFFSET_FACTOR 0x8038
#  define GL_TEXTURE_BINDING_2D 0x8069
#  define GL_VERTEX_ARRAY_SIZE 0x807A
#  define GL_VERTEX_ARRAY_TYPE 0x807B
#  define GL_VERTEX_ARRAY_STRIDE 0x807C
#  define GL_NORMAL_ARRAY_TYPE 0x807E
#  define GL_NORMAL_ARRAY_STRIDE 0x807F
#  define GL_COLOR_ARRAY_SIZE 0x8081
#  define GL_COLOR_ARRAY_TYPE 0x8082
#  define GL_COLOR_ARRAY_STRIDE 0x8083
#  define GL_TEXTURE_COORD_ARRAY_SIZE 0x8088
#  define GL_TEXTURE_COORD_ARRAY_TYPE 0x8089
#  define GL_TEXTURE_COORD_ARRAY_STRIDE 0x808A
#  define GL_VERTEX_ARRAY_POINTER 0x808E
#  define GL_NORMAL_ARRAY_POINTER 0x808F
#  define GL_COLOR_ARRAY_POINTER 0x8090
#  define GL_TEXTURE_COORD_ARRAY_POINTER 0x8092
#  define GL_SAMPLE_BUFFERS 0x80A8
#  define GL_SAMPLES 0x80A9
#  define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#  define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#  define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#  define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#  define GL_DONT_CARE 0x1100
#  define GL_FASTEST 0x1101
#  define GL_NICEST 0x1102
#  define GL_PERSPECTIVE_CORRECTION_HINT 0x0C50
#  define GL_POINT_SMOOTH_HINT 0x0C51
#  define GL_LINE_SMOOTH_HINT 0x0C52
#  define GL_FOG_HINT 0x0C54
#  define GL_GENERATE_MIPMAP_HINT 0x8192
#  define GL_LIGHT_MODEL_AMBIENT 0x0B53
#  define GL_LIGHT_MODEL_TWO_SIDE 0x0B52
#  define GL_AMBIENT 0x1200
#  define GL_DIFFUSE 0x1201
#  define GL_SPECULAR 0x1202
#  define GL_POSITION 0x1203
#  define GL_SPOT_DIRECTION 0x1204
#  define GL_SPOT_EXPONENT 0x1205
#  define GL_SPOT_CUTOFF 0x1206
#  define GL_CONSTANT_ATTENUATION 0x1207
#  define GL_LINEAR_ATTENUATION 0x1208
#  define GL_QUADRATIC_ATTENUATION 0x1209
#  define GL_BYTE 0x1400
#  define GL_UNSIGNED_BYTE 0x1401
#  define GL_SHORT 0x1402
#  define GL_UNSIGNED_SHORT 0x1403
#  define GL_FLOAT 0x1406
#  define GL_FIXED 0x140C
#  define GL_CLEAR 0x1500
#  define GL_AND 0x1501
#  define GL_AND_REVERSE 0x1502
#  define GL_COPY 0x1503
#  define GL_AND_INVERTED 0x1504
#  define GL_NOOP 0x1505
#  define GL_XOR 0x1506
#  define GL_OR 0x1507
#  define GL_NOR 0x1508
#  define GL_EQUIV 0x1509
#  define GL_INVERT 0x150A
#  define GL_OR_REVERSE 0x150B
#  define GL_COPY_INVERTED 0x150C
#  define GL_OR_INVERTED 0x150D
#  define GL_NAND 0x150E
#  define GL_SET 0x150F
#  define GL_EMISSION 0x1600
#  define GL_SHININESS 0x1601
#  define GL_AMBIENT_AND_DIFFUSE 0x1602
#  define GL_MODELVIEW 0x1700
#  define GL_PROJECTION 0x1701
#  define GL_TEXTURE 0x1702
#  define GL_ALPHA 0x1906
#  define GL_RGB 0x1907
#  define GL_RGBA 0x1908
#  define GL_LUMINANCE 0x1909
#  define GL_LUMINANCE_ALPHA 0x190A
#  define GL_UNPACK_ALIGNMENT 0x0CF5
#  define GL_PACK_ALIGNMENT 0x0D05
#  define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#  define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#  define GL_UNSIGNED_SHORT_5_6_5 0x8363
#  define GL_FLAT 0x1D00
#  define GL_SMOOTH 0x1D01
#  define GL_KEEP 0x1E00
#  define GL_REPLACE 0x1E01
#  define GL_INCR 0x1E02
#  define GL_DECR 0x1E03
#  define GL_VENDOR 0x1F00
#  define GL_RENDERER 0x1F01
#  define GL_VERSION 0x1F02
#  define GL_EXTENSIONS 0x1F03
#  define GL_MODULATE 0x2100
#  define GL_DECAL 0x2101
#  define GL_ADD 0x0104
#  define GL_TEXTURE_ENV_MODE 0x2200
#  define GL_TEXTURE_ENV_COLOR 0x2201
#  define GL_TEXTURE_ENV 0x2300
#  define GL_NEAREST 0x2600
#  define GL_LINEAR 0x2601
#  define GL_NEAREST_MIPMAP_NEAREST 0x2700
#  define GL_LINEAR_MIPMAP_NEAREST 0x2701
#  define GL_NEAREST_MIPMAP_LINEAR 0x2702
#  define GL_LINEAR_MIPMAP_LINEAR 0x2703
#  define GL_TEXTURE_MAG_FILTER 0x2800
#  define GL_TEXTURE_MIN_FILTER 0x2801
#  define GL_TEXTURE_WRAP_S 0x2802
#  define GL_TEXTURE_WRAP_T 0x2803
#  define GL_GENERATE_MIPMAP 0x8191
#  define GL_TEXTURE0 0x84C0
#  define GL_TEXTURE1 0x84C1
#  define GL_TEXTURE2 0x84C2
#  define GL_TEXTURE3 0x84C3
#  define GL_TEXTURE4 0x84C4
#  define GL_TEXTURE5 0x84C5
#  define GL_TEXTURE6 0x84C6
#  define GL_TEXTURE7 0x84C7
#  define GL_TEXTURE8 0x84C8
#  define GL_TEXTURE9 0x84C9
#  define GL_TEXTURE10 0x84CA
#  define GL_TEXTURE11 0x84CB
#  define GL_TEXTURE12 0x84CC
#  define GL_TEXTURE13 0x84CD
#  define GL_TEXTURE14 0x84CE
#  define GL_TEXTURE15 0x84CF
#  define GL_TEXTURE16 0x84D0
#  define GL_TEXTURE17 0x84D1
#  define GL_TEXTURE18 0x84D2
#  define GL_TEXTURE19 0x84D3
#  define GL_TEXTURE20 0x84D4
#  define GL_TEXTURE21 0x84D5
#  define GL_TEXTURE22 0x84D6
#  define GL_TEXTURE23 0x84D7
#  define GL_TEXTURE24 0x84D8
#  define GL_TEXTURE25 0x84D9
#  define GL_TEXTURE26 0x84DA
#  define GL_TEXTURE27 0x84DB
#  define GL_TEXTURE28 0x84DC
#  define GL_TEXTURE29 0x84DD
#  define GL_TEXTURE30 0x84DE
#  define GL_TEXTURE31 0x84DF
#  define GL_ACTIVE_TEXTURE 0x84E0
#  define GL_CLIENT_ACTIVE_TEXTURE 0x84E1
#  define GL_REPEAT 0x2901
#  define GL_CLAMP_TO_EDGE 0x812F
#  define GL_LIGHT0 0x4000
#  define GL_LIGHT1 0x4001
#  define GL_LIGHT2 0x4002
#  define GL_LIGHT3 0x4003
#  define GL_LIGHT4 0x4004
#  define GL_LIGHT5 0x4005
#  define GL_LIGHT6 0x4006
#  define GL_LIGHT7 0x4007
#  define GL_ARRAY_BUFFER 0x8892
#  define GL_ELEMENT_ARRAY_BUFFER 0x8893
#  define GL_ARRAY_BUFFER_BINDING 0x8894
#  define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#  define GL_VERTEX_ARRAY_BUFFER_BINDING 0x8896
#  define GL_NORMAL_ARRAY_BUFFER_BINDING 0x8897
#  define GL_COLOR_ARRAY_BUFFER_BINDING 0x8898
#  define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING 0x889A
#  define GL_STATIC_DRAW 0x88E4
#  define GL_DYNAMIC_DRAW 0x88E8
#  define GL_BUFFER_SIZE 0x8764
#  define GL_BUFFER_USAGE 0x8765
#  define GL_SUBTRACT 0x84E7
#  define GL_COMBINE 0x8570
#  define GL_COMBINE_RGB 0x8571
#  define GL_COMBINE_ALPHA 0x8572
#  define GL_RGB_SCALE 0x8573
#  define GL_ADD_SIGNED 0x8574
#  define GL_INTERPOLATE 0x8575
#  define GL_CONSTANT 0x8576
#  define GL_PRIMARY_COLOR 0x8577
#  define GL_PREVIOUS 0x8578
#  define GL_OPERAND0_RGB 0x8590
#  define GL_OPERAND1_RGB 0x8591
#  define GL_OPERAND2_RGB 0x8592
#  define GL_OPERAND0_ALPHA 0x8598
#  define GL_OPERAND1_ALPHA 0x8599
#  define GL_OPERAND2_ALPHA 0x859A
#  define GL_ALPHA_SCALE 0x0D1C
#  define GL_SRC0_RGB 0x8580
#  define GL_SRC1_RGB 0x8581
#  define GL_SRC2_RGB 0x8582
#  define GL_SRC0_ALPHA 0x8588
#  define GL_SRC1_ALPHA 0x8589
#  define GL_SRC2_ALPHA 0x858A
#  define GL_DOT3_RGB 0x86AE
#  define GL_DOT3_RGBA 0x86AF
# 
# endif /* GL_VERSION_ES_CM_1_0 */
# if defined GL_ES_VERSION_2_0
# 
#  define GL_DEPTH_BUFFER_BIT 0x00000100
#  define GL_STENCIL_BUFFER_BIT 0x00000400
#  define GL_COLOR_BUFFER_BIT 0x00004000
#  define GL_FALSE 0
#  define GL_TRUE 1
#  define GL_POINTS 0x0000
#  define GL_LINES 0x0001
#  define GL_LINE_LOOP 0x0002
#  define GL_LINE_STRIP 0x0003
#  define GL_TRIANGLES 0x0004
#  define GL_TRIANGLE_STRIP 0x0005
#  define GL_TRIANGLE_FAN 0x0006
#  define GL_ZERO 0
#  define GL_ONE 1
#  define GL_SRC_COLOR 0x0300
#  define GL_ONE_MINUS_SRC_COLOR 0x0301
#  define GL_SRC_ALPHA 0x0302
#  define GL_ONE_MINUS_SRC_ALPHA 0x0303
#  define GL_DST_ALPHA 0x0304
#  define GL_ONE_MINUS_DST_ALPHA 0x0305
#  define GL_DST_COLOR 0x0306
#  define GL_ONE_MINUS_DST_COLOR 0x0307
#  define GL_SRC_ALPHA_SATURATE 0x0308
#  define GL_FUNC_ADD 0x8006
#  define GL_BLEND_EQUATION 0x8009
#  define GL_BLEND_EQUATION_RGB 0x8009
#  define GL_BLEND_EQUATION_ALPHA 0x883D
#  define GL_FUNC_SUBTRACT 0x800A
#  define GL_FUNC_REVERSE_SUBTRACT 0x800B
#  define GL_BLEND_DST_RGB 0x80C8
#  define GL_BLEND_SRC_RGB 0x80C9
#  define GL_BLEND_DST_ALPHA 0x80CA
#  define GL_BLEND_SRC_ALPHA 0x80CB
#  define GL_CONSTANT_COLOR 0x8001
#  define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#  define GL_CONSTANT_ALPHA 0x8003
#  define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#  define GL_BLEND_COLOR 0x8005
#  define GL_ARRAY_BUFFER 0x8892
#  define GL_ELEMENT_ARRAY_BUFFER 0x8893
#  define GL_ARRAY_BUFFER_BINDING 0x8894
#  define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#  define GL_STREAM_DRAW 0x88E0
#  define GL_STATIC_DRAW 0x88E4
#  define GL_DYNAMIC_DRAW 0x88E8
#  define GL_BUFFER_SIZE 0x8764
#  define GL_BUFFER_USAGE 0x8765
#  define GL_CURRENT_VERTEX_ATTRIB 0x8626
#  define GL_FRONT 0x0404
#  define GL_BACK 0x0405
#  define GL_FRONT_AND_BACK 0x0408
#  define GL_TEXTURE_2D 0x0DE1
#  define GL_CULL_FACE 0x0B44
#  define GL_BLEND 0x0BE2
#  define GL_DITHER 0x0BD0
#  define GL_STENCIL_TEST 0x0B90
#  define GL_DEPTH_TEST 0x0B71
#  define GL_SCISSOR_TEST 0x0C11
#  define GL_POLYGON_OFFSET_FILL 0x8037
#  define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#  define GL_SAMPLE_COVERAGE 0x80A0
#  define GL_NO_ERROR 0
#  define GL_INVALID_ENUM 0x0500
#  define GL_INVALID_VALUE 0x0501
#  define GL_INVALID_OPERATION 0x0502
#  define GL_OUT_OF_MEMORY 0x0505
#  define GL_CW 0x0900
#  define GL_CCW 0x0901
#  define GL_LINE_WIDTH 0x0B21
#  define GL_ALIASED_POINT_SIZE_RANGE 0x846D
#  define GL_ALIASED_LINE_WIDTH_RANGE 0x846E
#  define GL_CULL_FACE_MODE 0x0B45
#  define GL_FRONT_FACE 0x0B46
#  define GL_DEPTH_RANGE 0x0B70
#  define GL_DEPTH_WRITEMASK 0x0B72
#  define GL_DEPTH_CLEAR_VALUE 0x0B73
#  define GL_DEPTH_FUNC 0x0B74
#  define GL_STENCIL_CLEAR_VALUE 0x0B91
#  define GL_STENCIL_FUNC 0x0B92
#  define GL_STENCIL_FAIL 0x0B94
#  define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#  define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#  define GL_STENCIL_REF 0x0B97
#  define GL_STENCIL_VALUE_MASK 0x0B93
#  define GL_STENCIL_WRITEMASK 0x0B98
#  define GL_STENCIL_BACK_FUNC 0x8800
#  define GL_STENCIL_BACK_FAIL 0x8801
#  define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
#  define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
#  define GL_STENCIL_BACK_REF 0x8CA3
#  define GL_STENCIL_BACK_VALUE_MASK 0x8CA4
#  define GL_STENCIL_BACK_WRITEMASK 0x8CA5
#  define GL_VIEWPORT 0x0BA2
#  define GL_SCISSOR_BOX 0x0C10
#  define GL_COLOR_CLEAR_VALUE 0x0C22
#  define GL_COLOR_WRITEMASK 0x0C23
#  define GL_UNPACK_ALIGNMENT 0x0CF5
#  define GL_PACK_ALIGNMENT 0x0D05
#  define GL_MAX_TEXTURE_SIZE 0x0D33
#  define GL_MAX_VIEWPORT_DIMS 0x0D3A
#  define GL_SUBPIXEL_BITS 0x0D50
#  define GL_RED_BITS 0x0D52
#  define GL_GREEN_BITS 0x0D53
#  define GL_BLUE_BITS 0x0D54
#  define GL_ALPHA_BITS 0x0D55
#  define GL_DEPTH_BITS 0x0D56
#  define GL_STENCIL_BITS 0x0D57
#  define GL_POLYGON_OFFSET_UNITS 0x2A00
#  define GL_POLYGON_OFFSET_FACTOR 0x8038
#  define GL_TEXTURE_BINDING_2D 0x8069
#  define GL_SAMPLE_BUFFERS 0x80A8
#  define GL_SAMPLES 0x80A9
#  define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#  define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#  define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#  define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#  define GL_DONT_CARE 0x1100
#  define GL_FASTEST 0x1101
#  define GL_NICEST 0x1102
#  define GL_GENERATE_MIPMAP_HINT 0x8192
#  define GL_BYTE 0x1400
#  define GL_UNSIGNED_BYTE 0x1401
#  define GL_SHORT 0x1402
#  define GL_UNSIGNED_SHORT 0x1403
#  define GL_INT 0x1404
#  define GL_UNSIGNED_INT 0x1405
#  define GL_FLOAT 0x1406
#  define GL_FIXED 0x140C
#  define GL_DEPTH_COMPONENT 0x1902
#  define GL_ALPHA 0x1906
#  define GL_RGB 0x1907
#  define GL_RGBA 0x1908
#  define GL_LUMINANCE 0x1909
#  define GL_LUMINANCE_ALPHA 0x190A
#  define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#  define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#  define GL_UNSIGNED_SHORT_5_6_5 0x8363
#  define GL_FRAGMENT_SHADER 0x8B30
#  define GL_VERTEX_SHADER 0x8B31
#  define GL_MAX_VERTEX_ATTRIBS 0x8869
#  define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8DFB
#  define GL_MAX_VARYING_VECTORS 0x8DFC
#  define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#  define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#  define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
#  define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8DFD
#  define GL_SHADER_TYPE 0x8B4F
#  define GL_DELETE_STATUS 0x8B80
#  define GL_LINK_STATUS 0x8B82
#  define GL_VALIDATE_STATUS 0x8B83
#  define GL_ATTACHED_SHADERS 0x8B85
#  define GL_ACTIVE_UNIFORMS 0x8B86
#  define GL_ACTIVE_UNIFORM_MAX_LENGTH 0x8B87
#  define GL_ACTIVE_ATTRIBUTES 0x8B89
#  define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 0x8B8A
#  define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#  define GL_CURRENT_PROGRAM 0x8B8D
#  define GL_NEVER 0x0200
#  define GL_LESS 0x0201
#  define GL_EQUAL 0x0202
#  define GL_LEQUAL 0x0203
#  define GL_GREATER 0x0204
#  define GL_NOTEQUAL 0x0205
#  define GL_GEQUAL 0x0206
#  define GL_ALWAYS 0x0207
#  define GL_KEEP 0x1E00
#  define GL_REPLACE 0x1E01
#  define GL_INCR 0x1E02
#  define GL_DECR 0x1E03
#  define GL_INVERT 0x150A
#  define GL_INCR_WRAP 0x8507
#  define GL_DECR_WRAP 0x8508
#  define GL_VENDOR 0x1F00
#  define GL_RENDERER 0x1F01
#  define GL_VERSION 0x1F02
#  define GL_EXTENSIONS 0x1F03
#  define GL_NEAREST 0x2600
#  define GL_LINEAR 0x2601
#  define GL_NEAREST_MIPMAP_NEAREST 0x2700
#  define GL_LINEAR_MIPMAP_NEAREST 0x2701
#  define GL_NEAREST_MIPMAP_LINEAR 0x2702
#  define GL_LINEAR_MIPMAP_LINEAR 0x2703
#  define GL_TEXTURE_MAG_FILTER 0x2800
#  define GL_TEXTURE_MIN_FILTER 0x2801
#  define GL_TEXTURE_WRAP_S 0x2802
#  define GL_TEXTURE_WRAP_T 0x2803
#  define GL_TEXTURE 0x1702
#  define GL_TEXTURE_CUBE_MAP 0x8513
#  define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#  define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#  define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#  define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#  define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#  define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#  define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
#  define GL_MAX_CUBE_MAP_TEXTURE_SIZE 0x851C
#  define GL_TEXTURE0 0x84C0
#  define GL_TEXTURE1 0x84C1
#  define GL_TEXTURE2 0x84C2
#  define GL_TEXTURE3 0x84C3
#  define GL_TEXTURE4 0x84C4
#  define GL_TEXTURE5 0x84C5
#  define GL_TEXTURE6 0x84C6
#  define GL_TEXTURE7 0x84C7
#  define GL_TEXTURE8 0x84C8
#  define GL_TEXTURE9 0x84C9
#  define GL_TEXTURE10 0x84CA
#  define GL_TEXTURE11 0x84CB
#  define GL_TEXTURE12 0x84CC
#  define GL_TEXTURE13 0x84CD
#  define GL_TEXTURE14 0x84CE
#  define GL_TEXTURE15 0x84CF
#  define GL_TEXTURE16 0x84D0
#  define GL_TEXTURE17 0x84D1
#  define GL_TEXTURE18 0x84D2
#  define GL_TEXTURE19 0x84D3
#  define GL_TEXTURE20 0x84D4
#  define GL_TEXTURE21 0x84D5
#  define GL_TEXTURE22 0x84D6
#  define GL_TEXTURE23 0x84D7
#  define GL_TEXTURE24 0x84D8
#  define GL_TEXTURE25 0x84D9
#  define GL_TEXTURE26 0x84DA
#  define GL_TEXTURE27 0x84DB
#  define GL_TEXTURE28 0x84DC
#  define GL_TEXTURE29 0x84DD
#  define GL_TEXTURE30 0x84DE
#  define GL_TEXTURE31 0x84DF
#  define GL_ACTIVE_TEXTURE 0x84E0
#  define GL_REPEAT 0x2901
#  define GL_CLAMP_TO_EDGE 0x812F
#  define GL_MIRRORED_REPEAT 0x8370
#  define GL_FLOAT_VEC2 0x8B50
#  define GL_FLOAT_VEC3 0x8B51
#  define GL_FLOAT_VEC4 0x8B52
#  define GL_INT_VEC2 0x8B53
#  define GL_INT_VEC3 0x8B54
#  define GL_INT_VEC4 0x8B55
#  define GL_BOOL 0x8B56
#  define GL_BOOL_VEC2 0x8B57
#  define GL_BOOL_VEC3 0x8B58
#  define GL_BOOL_VEC4 0x8B59
#  define GL_FLOAT_MAT2 0x8B5A
#  define GL_FLOAT_MAT3 0x8B5B
#  define GL_FLOAT_MAT4 0x8B5C
#  define GL_SAMPLER_2D 0x8B5E
#  define GL_SAMPLER_CUBE 0x8B60
#  define GL_VERTEX_ATTRIB_ARRAY_ENABLED 0x8622
#  define GL_VERTEX_ATTRIB_ARRAY_SIZE 0x8623
#  define GL_VERTEX_ATTRIB_ARRAY_STRIDE 0x8624
#  define GL_VERTEX_ATTRIB_ARRAY_TYPE 0x8625
#  define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#  define GL_VERTEX_ATTRIB_ARRAY_POINTER 0x8645
#  define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#  define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#  define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#  define GL_COMPILE_STATUS 0x8B81
#  define GL_INFO_LOG_LENGTH 0x8B84
#  define GL_SHADER_SOURCE_LENGTH 0x8B88
#  define GL_SHADER_COMPILER 0x8DFA
#  define GL_SHADER_BINARY_FORMATS 0x8DF8
#  define GL_NUM_SHADER_BINARY_FORMATS 0x8DF9
#  define GL_LOW_FLOAT 0x8DF0
#  define GL_MEDIUM_FLOAT 0x8DF1
#  define GL_HIGH_FLOAT 0x8DF2
#  define GL_LOW_INT 0x8DF3
#  define GL_MEDIUM_INT 0x8DF4
#  define GL_HIGH_INT 0x8DF5
#  define GL_FRAMEBUFFER 0x8D40
#  define GL_RENDERBUFFER 0x8D41
#  define GL_RGBA4 0x8056
#  define GL_RGB5_A1 0x8057
#  define GL_RGB565 0x8D62
#  define GL_DEPTH_COMPONENT16 0x81A5
#  define GL_STENCIL_INDEX8 0x8D48
#  define GL_RENDERBUFFER_WIDTH 0x8D42
#  define GL_RENDERBUFFER_HEIGHT 0x8D43
#  define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8D44
#  define GL_RENDERBUFFER_RED_SIZE 0x8D50
#  define GL_RENDERBUFFER_GREEN_SIZE 0x8D51
#  define GL_RENDERBUFFER_BLUE_SIZE 0x8D52
#  define GL_RENDERBUFFER_ALPHA_SIZE 0x8D53
#  define GL_RENDERBUFFER_DEPTH_SIZE 0x8D54
#  define GL_RENDERBUFFER_STENCIL_SIZE 0x8D55
#  define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#  define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#  define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#  define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#  define GL_COLOR_ATTACHMENT0 0x8CE0
#  define GL_DEPTH_ATTACHMENT 0x8D00
#  define GL_STENCIL_ATTACHMENT 0x8D20
#  define GL_NONE 0
#  define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#  define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#  define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#  define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#  define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
#  define GL_FRAMEBUFFER_BINDING 0x8CA6
#  define GL_RENDERBUFFER_BINDING 0x8CA7
#  define GL_MAX_RENDERBUFFER_SIZE 0x84E8
#  define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
# 
# endif /* GL_ES_VERSION_2_0 */
# if defined GL_ES_VERSION_3_0
# 
#  define GL_READ_BUFFER 0x0C02
#  define GL_UNPACK_ROW_LENGTH 0x0CF2
#  define GL_UNPACK_SKIP_ROWS 0x0CF3
#  define GL_UNPACK_SKIP_PIXELS 0x0CF4
#  define GL_PACK_ROW_LENGTH 0x0D02
#  define GL_PACK_SKIP_ROWS 0x0D03
#  define GL_PACK_SKIP_PIXELS 0x0D04
#  define GL_COLOR 0x1800
#  define GL_DEPTH 0x1801
#  define GL_STENCIL 0x1802
#  define GL_RED 0x1903
#  define GL_RGB8 0x8051
#  define GL_RGBA8 0x8058
#  define GL_RGB10_A2 0x8059
#  define GL_TEXTURE_BINDING_3D 0x806A
#  define GL_UNPACK_SKIP_IMAGES 0x806D
#  define GL_UNPACK_IMAGE_HEIGHT 0x806E
#  define GL_TEXTURE_3D 0x806F
#  define GL_TEXTURE_WRAP_R 0x8072
#  define GL_MAX_3D_TEXTURE_SIZE 0x8073
#  define GL_UNSIGNED_INT_2_10_10_10_REV 0x8368
#  define GL_MAX_ELEMENTS_VERTICES 0x80E8
#  define GL_MAX_ELEMENTS_INDICES 0x80E9
#  define GL_TEXTURE_MIN_LOD 0x813A
#  define GL_TEXTURE_MAX_LOD 0x813B
#  define GL_TEXTURE_BASE_LEVEL 0x813C
#  define GL_TEXTURE_MAX_LEVEL 0x813D
#  define GL_MIN 0x8007
#  define GL_MAX 0x8008
#  define GL_DEPTH_COMPONENT24 0x81A6
#  define GL_MAX_TEXTURE_LOD_BIAS 0x84FD
#  define GL_TEXTURE_COMPARE_MODE 0x884C
#  define GL_TEXTURE_COMPARE_FUNC 0x884D
#  define GL_CURRENT_QUERY 0x8865
#  define GL_QUERY_RESULT 0x8866
#  define GL_QUERY_RESULT_AVAILABLE 0x8867
#  define GL_BUFFER_MAPPED 0x88BC
#  define GL_BUFFER_MAP_POINTER 0x88BD
#  define GL_STREAM_READ 0x88E1
#  define GL_STREAM_COPY 0x88E2
#  define GL_STATIC_READ 0x88E5
#  define GL_STATIC_COPY 0x88E6
#  define GL_DYNAMIC_READ 0x88E9
#  define GL_DYNAMIC_COPY 0x88EA
#  define GL_MAX_DRAW_BUFFERS 0x8824
#  define GL_DRAW_BUFFER0 0x8825
#  define GL_DRAW_BUFFER1 0x8826
#  define GL_DRAW_BUFFER2 0x8827
#  define GL_DRAW_BUFFER3 0x8828
#  define GL_DRAW_BUFFER4 0x8829
#  define GL_DRAW_BUFFER5 0x882A
#  define GL_DRAW_BUFFER6 0x882B
#  define GL_DRAW_BUFFER7 0x882C
#  define GL_DRAW_BUFFER8 0x882D
#  define GL_DRAW_BUFFER9 0x882E
#  define GL_DRAW_BUFFER10 0x882F
#  define GL_DRAW_BUFFER11 0x8830
#  define GL_DRAW_BUFFER12 0x8831
#  define GL_DRAW_BUFFER13 0x8832
#  define GL_DRAW_BUFFER14 0x8833
#  define GL_DRAW_BUFFER15 0x8834
#  define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#  define GL_MAX_VERTEX_UNIFORM_COMPONENTS 0x8B4A
#  define GL_SAMPLER_3D 0x8B5F
#  define GL_SAMPLER_2D_SHADOW 0x8B62
#  define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#  define GL_PIXEL_PACK_BUFFER 0x88EB
#  define GL_PIXEL_UNPACK_BUFFER 0x88EC
#  define GL_PIXEL_PACK_BUFFER_BINDING 0x88ED
#  define GL_PIXEL_UNPACK_BUFFER_BINDING 0x88EF
#  define GL_FLOAT_MAT2x3 0x8B65
#  define GL_FLOAT_MAT2x4 0x8B66
#  define GL_FLOAT_MAT3x2 0x8B67
#  define GL_FLOAT_MAT3x4 0x8B68
#  define GL_FLOAT_MAT4x2 0x8B69
#  define GL_FLOAT_MAT4x3 0x8B6A
#  define GL_SRGB 0x8C40
#  define GL_SRGB8 0x8C41
#  define GL_SRGB8_ALPHA8 0x8C43
#  define GL_COMPARE_REF_TO_TEXTURE 0x884E
#  define GL_MAJOR_VERSION 0x821B
#  define GL_MINOR_VERSION 0x821C
#  define GL_NUM_EXTENSIONS 0x821D
#  define GL_RGBA32F 0x8814
#  define GL_RGB32F 0x8815
#  define GL_RGBA16F 0x881A
#  define GL_RGB16F 0x881B
#  define GL_VERTEX_ATTRIB_ARRAY_INTEGER 0x88FD
#  define GL_MAX_ARRAY_TEXTURE_LAYERS 0x88FF
#  define GL_MIN_PROGRAM_TEXEL_OFFSET 0x8904
#  define GL_MAX_PROGRAM_TEXEL_OFFSET 0x8905
#  define GL_MAX_VARYING_COMPONENTS 0x8B4B
#  define GL_TEXTURE_2D_ARRAY 0x8C1A
#  define GL_TEXTURE_BINDING_2D_ARRAY 0x8C1D
#  define GL_R11F_G11F_B10F 0x8C3A
#  define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B
#  define GL_RGB9_E5 0x8C3D
#  define GL_UNSIGNED_INT_5_9_9_9_REV 0x8C3E
#  define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#  define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#  define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#  define GL_TRANSFORM_FEEDBACK_VARYINGS 0x8C83
#  define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#  define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#  define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#  define GL_RASTERIZER_DISCARD 0x8C89
#  define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#  define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#  define GL_INTERLEAVED_ATTRIBS 0x8C8C
#  define GL_SEPARATE_ATTRIBS 0x8C8D
#  define GL_TRANSFORM_FEEDBACK_BUFFER 0x8C8E
#  define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#  define GL_RGBA32UI 0x8D70
#  define GL_RGB32UI 0x8D71
#  define GL_RGBA16UI 0x8D76
#  define GL_RGB16UI 0x8D77
#  define GL_RGBA8UI 0x8D7C
#  define GL_RGB8UI 0x8D7D
#  define GL_RGBA32I 0x8D82
#  define GL_RGB32I 0x8D83
#  define GL_RGBA16I 0x8D88
#  define GL_RGB16I 0x8D89
#  define GL_RGBA8I 0x8D8E
#  define GL_RGB8I 0x8D8F
#  define GL_RED_INTEGER 0x8D94
#  define GL_RGB_INTEGER 0x8D98
#  define GL_RGBA_INTEGER 0x8D99
#  define GL_SAMPLER_2D_ARRAY 0x8DC1
#  define GL_SAMPLER_2D_ARRAY_SHADOW 0x8DC4
#  define GL_SAMPLER_CUBE_SHADOW 0x8DC5
#  define GL_UNSIGNED_INT_VEC2 0x8DC6
#  define GL_UNSIGNED_INT_VEC3 0x8DC7
#  define GL_UNSIGNED_INT_VEC4 0x8DC8
#  define GL_INT_SAMPLER_2D 0x8DCA
#  define GL_INT_SAMPLER_3D 0x8DCB
#  define GL_INT_SAMPLER_CUBE 0x8DCC
#  define GL_INT_SAMPLER_2D_ARRAY 0x8DCF
#  define GL_UNSIGNED_INT_SAMPLER_2D 0x8DD2
#  define GL_UNSIGNED_INT_SAMPLER_3D 0x8DD3
#  define GL_UNSIGNED_INT_SAMPLER_CUBE 0x8DD4
#  define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 0x8DD7
#  define GL_BUFFER_ACCESS_FLAGS 0x911F
#  define GL_BUFFER_MAP_LENGTH 0x9120
#  define GL_BUFFER_MAP_OFFSET 0x9121
#  define GL_DEPTH_COMPONENT32F 0x8CAC
#  define GL_DEPTH32F_STENCIL8 0x8CAD
#  define GL_FLOAT_32_UNSIGNED_INT_24_8_REV 0x8DAD
#  define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#  define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#  define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#  define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#  define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#  define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#  define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#  define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#  define GL_FRAMEBUFFER_DEFAULT 0x8218
#  define GL_FRAMEBUFFER_UNDEFINED 0x8219
#  define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#  define GL_DEPTH_STENCIL 0x84F9
#  define GL_UNSIGNED_INT_24_8 0x84FA
#  define GL_DEPTH24_STENCIL8 0x88F0
#  define GL_UNSIGNED_NORMALIZED 0x8C17
#  define GL_DRAW_FRAMEBUFFER_BINDING 0x8CA6
#  define GL_READ_FRAMEBUFFER 0x8CA8
#  define GL_DRAW_FRAMEBUFFER 0x8CA9
#  define GL_READ_FRAMEBUFFER_BINDING 0x8CAA
#  define GL_RENDERBUFFER_SAMPLES 0x8CAB
#  define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#  define GL_MAX_COLOR_ATTACHMENTS 0x8CDF
#  define GL_COLOR_ATTACHMENT1 0x8CE1
#  define GL_COLOR_ATTACHMENT2 0x8CE2
#  define GL_COLOR_ATTACHMENT3 0x8CE3
#  define GL_COLOR_ATTACHMENT4 0x8CE4
#  define GL_COLOR_ATTACHMENT5 0x8CE5
#  define GL_COLOR_ATTACHMENT6 0x8CE6
#  define GL_COLOR_ATTACHMENT7 0x8CE7
#  define GL_COLOR_ATTACHMENT8 0x8CE8
#  define GL_COLOR_ATTACHMENT9 0x8CE9
#  define GL_COLOR_ATTACHMENT10 0x8CEA
#  define GL_COLOR_ATTACHMENT11 0x8CEB
#  define GL_COLOR_ATTACHMENT12 0x8CEC
#  define GL_COLOR_ATTACHMENT13 0x8CED
#  define GL_COLOR_ATTACHMENT14 0x8CEE
#  define GL_COLOR_ATTACHMENT15 0x8CEF
#  define GL_COLOR_ATTACHMENT16 0x8CF0
#  define GL_COLOR_ATTACHMENT17 0x8CF1
#  define GL_COLOR_ATTACHMENT18 0x8CF2
#  define GL_COLOR_ATTACHMENT19 0x8CF3
#  define GL_COLOR_ATTACHMENT20 0x8CF4
#  define GL_COLOR_ATTACHMENT21 0x8CF5
#  define GL_COLOR_ATTACHMENT22 0x8CF6
#  define GL_COLOR_ATTACHMENT23 0x8CF7
#  define GL_COLOR_ATTACHMENT24 0x8CF8
#  define GL_COLOR_ATTACHMENT25 0x8CF9
#  define GL_COLOR_ATTACHMENT26 0x8CFA
#  define GL_COLOR_ATTACHMENT27 0x8CFB
#  define GL_COLOR_ATTACHMENT28 0x8CFC
#  define GL_COLOR_ATTACHMENT29 0x8CFD
#  define GL_COLOR_ATTACHMENT30 0x8CFE
#  define GL_COLOR_ATTACHMENT31 0x8CFF
#  define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#  define GL_MAX_SAMPLES 0x8D57
#  define GL_HALF_FLOAT 0x140B
#  define GL_MAP_READ_BIT 0x0001
#  define GL_MAP_WRITE_BIT 0x0002
#  define GL_MAP_INVALIDATE_RANGE_BIT 0x0004
#  define GL_MAP_INVALIDATE_BUFFER_BIT 0x0008
#  define GL_MAP_FLUSH_EXPLICIT_BIT 0x0010
#  define GL_MAP_UNSYNCHRONIZED_BIT 0x0020
#  define GL_RG 0x8227
#  define GL_RG_INTEGER 0x8228
#  define GL_R8 0x8229
#  define GL_RG8 0x822B
#  define GL_R16F 0x822D
#  define GL_R32F 0x822E
#  define GL_RG16F 0x822F
#  define GL_RG32F 0x8230
#  define GL_R8I 0x8231
#  define GL_R8UI 0x8232
#  define GL_R16I 0x8233
#  define GL_R16UI 0x8234
#  define GL_R32I 0x8235
#  define GL_R32UI 0x8236
#  define GL_RG8I 0x8237
#  define GL_RG8UI 0x8238
#  define GL_RG16I 0x8239
#  define GL_RG16UI 0x823A
#  define GL_RG32I 0x823B
#  define GL_RG32UI 0x823C
#  define GL_VERTEX_ARRAY_BINDING 0x85B5
#  define GL_R8_SNORM 0x8F94
#  define GL_RG8_SNORM 0x8F95
#  define GL_RGB8_SNORM 0x8F96
#  define GL_RGBA8_SNORM 0x8F97
#  define GL_SIGNED_NORMALIZED 0x8F9C
#  define GL_PRIMITIVE_RESTART_FIXED_INDEX 0x8D69
#  define GL_COPY_READ_BUFFER 0x8F36
#  define GL_COPY_WRITE_BUFFER 0x8F37
#  define GL_COPY_READ_BUFFER_BINDING 0x8F36
#  define GL_COPY_WRITE_BUFFER_BINDING 0x8F37
#  define GL_UNIFORM_BUFFER 0x8A11
#  define GL_UNIFORM_BUFFER_BINDING 0x8A28
#  define GL_UNIFORM_BUFFER_START 0x8A29
#  define GL_UNIFORM_BUFFER_SIZE 0x8A2A
#  define GL_MAX_VERTEX_UNIFORM_BLOCKS 0x8A2B
#  define GL_MAX_FRAGMENT_UNIFORM_BLOCKS 0x8A2D
#  define GL_MAX_COMBINED_UNIFORM_BLOCKS 0x8A2E
#  define GL_MAX_UNIFORM_BUFFER_BINDINGS 0x8A2F
#  define GL_MAX_UNIFORM_BLOCK_SIZE 0x8A30
#  define GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 0x8A31
#  define GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 0x8A33
#  define GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 0x8A34
#  define GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 0x8A35
#  define GL_ACTIVE_UNIFORM_BLOCKS 0x8A36
#  define GL_UNIFORM_TYPE 0x8A37
#  define GL_UNIFORM_SIZE 0x8A38
#  define GL_UNIFORM_NAME_LENGTH 0x8A39
#  define GL_UNIFORM_BLOCK_INDEX 0x8A3A
#  define GL_UNIFORM_OFFSET 0x8A3B
#  define GL_UNIFORM_ARRAY_STRIDE 0x8A3C
#  define GL_UNIFORM_MATRIX_STRIDE 0x8A3D
#  define GL_UNIFORM_IS_ROW_MAJOR 0x8A3E
#  define GL_UNIFORM_BLOCK_BINDING 0x8A3F
#  define GL_UNIFORM_BLOCK_DATA_SIZE 0x8A40
#  define GL_UNIFORM_BLOCK_NAME_LENGTH 0x8A41
#  define GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 0x8A42
#  define GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 0x8A43
#  define GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 0x8A44
#  define GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 0x8A46
#  define GL_INVALID_INDEX 0xFFFFFFFF
#  define GL_MAX_VERTEX_OUTPUT_COMPONENTS 0x9122
#  define GL_MAX_FRAGMENT_INPUT_COMPONENTS 0x9125
#  define GL_MAX_SERVER_WAIT_TIMEOUT 0x9111
#  define GL_OBJECT_TYPE 0x9112
#  define GL_SYNC_CONDITION 0x9113
#  define GL_SYNC_STATUS 0x9114
#  define GL_SYNC_FLAGS 0x9115
#  define GL_SYNC_FENCE 0x9116
#  define GL_SYNC_GPU_COMMANDS_COMPLETE 0x9117
#  define GL_UNSIGNALED 0x9118
#  define GL_SIGNALED 0x9119
#  define GL_ALREADY_SIGNALED 0x911A
#  define GL_TIMEOUT_EXPIRED 0x911B
#  define GL_CONDITION_SATISFIED 0x911C
#  define GL_WAIT_FAILED 0x911D
#  define GL_SYNC_FLUSH_COMMANDS_BIT 0x00000001
#  define GL_TIMEOUT_IGNORED 0xFFFFFFFFFFFFFFFF
#  define GL_VERTEX_ATTRIB_ARRAY_DIVISOR 0x88FE
#  define GL_ANY_SAMPLES_PASSED 0x8C2F
#  define GL_ANY_SAMPLES_PASSED_CONSERVATIVE 0x8D6A
#  define GL_SAMPLER_BINDING 0x8919
#  define GL_RGB10_A2UI 0x906F
#  define GL_TEXTURE_SWIZZLE_R 0x8E42
#  define GL_TEXTURE_SWIZZLE_G 0x8E43
#  define GL_TEXTURE_SWIZZLE_B 0x8E44
#  define GL_TEXTURE_SWIZZLE_A 0x8E45
#  define GL_GREEN 0x1904
#  define GL_BLUE 0x1905
#  define GL_INT_2_10_10_10_REV 0x8D9F
#  define GL_TRANSFORM_FEEDBACK 0x8E22
#  define GL_TRANSFORM_FEEDBACK_PAUSED 0x8E23
#  define GL_TRANSFORM_FEEDBACK_ACTIVE 0x8E24
#  define GL_TRANSFORM_FEEDBACK_BINDING 0x8E25
#  define GL_PROGRAM_BINARY_RETRIEVABLE_HINT 0x8257
#  define GL_PROGRAM_BINARY_LENGTH 0x8741
#  define GL_NUM_PROGRAM_BINARY_FORMATS 0x87FE
#  define GL_PROGRAM_BINARY_FORMATS 0x87FF
#  define GL_COMPRESSED_R11_EAC 0x9270
#  define GL_COMPRESSED_SIGNED_R11_EAC 0x9271
#  define GL_COMPRESSED_RG11_EAC 0x9272
#  define GL_COMPRESSED_SIGNED_RG11_EAC 0x9273
#  define GL_COMPRESSED_RGB8_ETC2 0x9274
#  define GL_COMPRESSED_SRGB8_ETC2 0x9275
#  define GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9276
#  define GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 0x9277
#  define GL_COMPRESSED_RGBA8_ETC2_EAC 0x9278
#  define GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 0x9279
#  define GL_TEXTURE_IMMUTABLE_FORMAT 0x912F
#  define GL_MAX_ELEMENT_INDEX 0x8D6B
#  define GL_NUM_SAMPLE_COUNTS 0x9380
#  define GL_TEXTURE_IMMUTABLE_LEVELS 0x82DF
# 
# endif /* GL_ES_VERSION_3_0 */
# if defined GL_ES_VERSION_3_1
# 
#  define GL_COMPUTE_SHADER 0x91B9
#  define GL_MAX_COMPUTE_UNIFORM_BLOCKS 0x91BB
#  define GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 0x91BC
#  define GL_MAX_COMPUTE_IMAGE_UNIFORMS 0x91BD
#  define GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 0x8262
#  define GL_MAX_COMPUTE_UNIFORM_COMPONENTS 0x8263
#  define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#  define GL_MAX_COMPUTE_ATOMIC_COUNTERS 0x8265
#  define GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 0x8266
#  define GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 0x90EB
#  define GL_MAX_COMPUTE_WORK_GROUP_COUNT 0x91BE
#  define GL_MAX_COMPUTE_WORK_GROUP_SIZE 0x91BF
#  define GL_COMPUTE_WORK_GROUP_SIZE 0x8267
#  define GL_DISPATCH_INDIRECT_BUFFER 0x90EE
#  define GL_DISPATCH_INDIRECT_BUFFER_BINDING 0x90EF
#  define GL_COMPUTE_SHADER_BIT 0x00000020
#  define GL_DRAW_INDIRECT_BUFFER 0x8F3F
#  define GL_DRAW_INDIRECT_BUFFER_BINDING 0x8F43
#  define GL_MAX_UNIFORM_LOCATIONS 0x826E
#  define GL_FRAMEBUFFER_DEFAULT_WIDTH 0x9310
#  define GL_FRAMEBUFFER_DEFAULT_HEIGHT 0x9311
#  define GL_FRAMEBUFFER_DEFAULT_SAMPLES 0x9313
#  define GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 0x9314
#  define GL_MAX_FRAMEBUFFER_WIDTH 0x9315
#  define GL_MAX_FRAMEBUFFER_HEIGHT 0x9316
#  define GL_MAX_FRAMEBUFFER_SAMPLES 0x9318
#  define GL_UNIFORM 0x92E1
#  define GL_UNIFORM_BLOCK 0x92E2
#  define GL_PROGRAM_INPUT 0x92E3
#  define GL_PROGRAM_OUTPUT 0x92E4
#  define GL_BUFFER_VARIABLE 0x92E5
#  define GL_SHADER_STORAGE_BLOCK 0x92E6
#  define GL_ATOMIC_COUNTER_BUFFER 0x92C0
#  define GL_TRANSFORM_FEEDBACK_VARYING 0x92F4
#  define GL_ACTIVE_RESOURCES 0x92F5
#  define GL_MAX_NAME_LENGTH 0x92F6
#  define GL_MAX_NUM_ACTIVE_VARIABLES 0x92F7
#  define GL_NAME_LENGTH 0x92F9
#  define GL_TYPE 0x92FA
#  define GL_ARRAY_SIZE 0x92FB
#  define GL_OFFSET 0x92FC
#  define GL_BLOCK_INDEX 0x92FD
#  define GL_ARRAY_STRIDE 0x92FE
#  define GL_MATRIX_STRIDE 0x92FF
#  define GL_IS_ROW_MAJOR 0x9300
#  define GL_ATOMIC_COUNTER_BUFFER_INDEX 0x9301
#  define GL_BUFFER_BINDING 0x9302
#  define GL_BUFFER_DATA_SIZE 0x9303
#  define GL_NUM_ACTIVE_VARIABLES 0x9304
#  define GL_ACTIVE_VARIABLES 0x9305
#  define GL_REFERENCED_BY_VERTEX_SHADER 0x9306
#  define GL_REFERENCED_BY_FRAGMENT_SHADER 0x930A
#  define GL_REFERENCED_BY_COMPUTE_SHADER 0x930B
#  define GL_TOP_LEVEL_ARRAY_SIZE 0x930C
#  define GL_TOP_LEVEL_ARRAY_STRIDE 0x930D
#  define GL_LOCATION 0x930E
#  define GL_VERTEX_SHADER_BIT 0x00000001
#  define GL_FRAGMENT_SHADER_BIT 0x00000002
#  define GL_ALL_SHADER_BITS 0xFFFFFFFF
#  define GL_PROGRAM_SEPARABLE 0x8258
#  define GL_ACTIVE_PROGRAM 0x8259
#  define GL_PROGRAM_PIPELINE_BINDING 0x825A
#  define GL_ATOMIC_COUNTER_BUFFER 0x92C0
#  define GL_ATOMIC_COUNTER_BUFFER_BINDING 0x92C1
#  define GL_ATOMIC_COUNTER_BUFFER_START 0x92C2
#  define GL_ATOMIC_COUNTER_BUFFER_SIZE 0x92C3
#  define GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 0x92CC
#  define GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 0x92D0
#  define GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 0x8264
#  define GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 0x92D1
#  define GL_MAX_VERTEX_ATOMIC_COUNTERS 0x92D2
#  define GL_MAX_FRAGMENT_ATOMIC_COUNTERS 0x92D6
#  define GL_MAX_COMPUTE_ATOMIC_COUNTERS 0x8265
#  define GL_MAX_COMBINED_ATOMIC_COUNTERS 0x92D7
#  define GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 0x92D8
#  define GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 0x92DC
#  define GL_ACTIVE_ATOMIC_COUNTER_BUFFERS 0x92D9
#  define GL_UNSIGNED_INT_ATOMIC_COUNTER 0x92DB
#  define GL_MAX_IMAGE_UNITS 0x8F38
#  define GL_MAX_VERTEX_IMAGE_UNIFORMS 0x90CA
#  define GL_MAX_FRAGMENT_IMAGE_UNIFORMS 0x90CE
#  define GL_MAX_COMPUTE_IMAGE_UNIFORMS 0x91BD
#  define GL_MAX_COMBINED_IMAGE_UNIFORMS 0x90CF
#  define GL_IMAGE_BINDING_NAME 0x8F3A
#  define GL_IMAGE_BINDING_LEVEL 0x8F3B
#  define GL_IMAGE_BINDING_LAYERED 0x8F3C
#  define GL_IMAGE_BINDING_LAYER 0x8F3D
#  define GL_IMAGE_BINDING_ACCESS 0x8F3E
#  define GL_IMAGE_BINDING_FORMAT 0x906E
#  define GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 0x00000001
#  define GL_ELEMENT_ARRAY_BARRIER_BIT 0x00000002
#  define GL_UNIFORM_BARRIER_BIT 0x00000004
#  define GL_TEXTURE_FETCH_BARRIER_BIT 0x00000008
#  define GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 0x00000020
#  define GL_COMMAND_BARRIER_BIT 0x00000040
#  define GL_PIXEL_BUFFER_BARRIER_BIT 0x00000080
#  define GL_TEXTURE_UPDATE_BARRIER_BIT 0x00000100
#  define GL_BUFFER_UPDATE_BARRIER_BIT 0x00000200
#  define GL_FRAMEBUFFER_BARRIER_BIT 0x00000400
#  define GL_TRANSFORM_FEEDBACK_BARRIER_BIT 0x00000800
#  define GL_ATOMIC_COUNTER_BARRIER_BIT 0x00001000
#  define GL_ALL_BARRIER_BITS 0xFFFFFFFF
#  define GL_IMAGE_2D 0x904D
#  define GL_IMAGE_3D 0x904E
#  define GL_IMAGE_CUBE 0x9050
#  define GL_IMAGE_2D_ARRAY 0x9053
#  define GL_INT_IMAGE_2D 0x9058
#  define GL_INT_IMAGE_3D 0x9059
#  define GL_INT_IMAGE_CUBE 0x905B
#  define GL_INT_IMAGE_2D_ARRAY 0x905E
#  define GL_UNSIGNED_INT_IMAGE_2D 0x9063
#  define GL_UNSIGNED_INT_IMAGE_3D 0x9064
#  define GL_UNSIGNED_INT_IMAGE_CUBE 0x9066
#  define GL_UNSIGNED_INT_IMAGE_2D_ARRAY 0x9069
#  define GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 0x90C7
#  define GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 0x90C8
#  define GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 0x90C9
#  define GL_READ_ONLY 0x88B8
#  define GL_WRITE_ONLY 0x88B9
#  define GL_READ_WRITE 0x88BA
#  define GL_SHADER_STORAGE_BUFFER 0x90D2
#  define GL_SHADER_STORAGE_BUFFER_BINDING 0x90D3
#  define GL_SHADER_STORAGE_BUFFER_START 0x90D4
#  define GL_SHADER_STORAGE_BUFFER_SIZE 0x90D5
#  define GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 0x90D6
#  define GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 0x90DA
#  define GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 0x90DB
#  define GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 0x90DC
#  define GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 0x90DD
#  define GL_MAX_SHADER_STORAGE_BLOCK_SIZE 0x90DE
#  define GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 0x90DF
#  define GL_SHADER_STORAGE_BARRIER_BIT 0x00002000
#  define GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 0x8F39
#  define GL_DEPTH_STENCIL_TEXTURE_MODE 0x90EA
#  define GL_STENCIL_INDEX 0x1901
#  define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
#  define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
#  define GL_SAMPLE_POSITION 0x8E50
#  define GL_SAMPLE_MASK 0x8E51
#  define GL_SAMPLE_MASK_VALUE 0x8E52
#  define GL_TEXTURE_2D_MULTISAMPLE 0x9100
#  define GL_MAX_SAMPLE_MASK_WORDS 0x8E59
#  define GL_MAX_COLOR_TEXTURE_SAMPLES 0x910E
#  define GL_MAX_DEPTH_TEXTURE_SAMPLES 0x910F
#  define GL_MAX_INTEGER_SAMPLES 0x9110
#  define GL_TEXTURE_BINDING_2D_MULTISAMPLE 0x9104
#  define GL_TEXTURE_SAMPLES 0x9106
#  define GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 0x9107
#  define GL_TEXTURE_WIDTH 0x1000
#  define GL_TEXTURE_HEIGHT 0x1001
#  define GL_TEXTURE_DEPTH 0x8071
#  define GL_TEXTURE_INTERNAL_FORMAT 0x1003
#  define GL_TEXTURE_RED_SIZE 0x805C
#  define GL_TEXTURE_GREEN_SIZE 0x805D
#  define GL_TEXTURE_BLUE_SIZE 0x805E
#  define GL_TEXTURE_ALPHA_SIZE 0x805F
#  define GL_TEXTURE_DEPTH_SIZE 0x884A
#  define GL_TEXTURE_STENCIL_SIZE 0x88F1
#  define GL_TEXTURE_SHARED_SIZE 0x8C3F
#  define GL_TEXTURE_RED_TYPE 0x8C10
#  define GL_TEXTURE_GREEN_TYPE 0x8C11
#  define GL_TEXTURE_BLUE_TYPE 0x8C12
#  define GL_TEXTURE_ALPHA_TYPE 0x8C13
#  define GL_TEXTURE_DEPTH_TYPE 0x8C16
#  define GL_TEXTURE_COMPRESSED 0x86A1
#  define GL_SAMPLER_2D_MULTISAMPLE 0x9108
#  define GL_INT_SAMPLER_2D_MULTISAMPLE 0x9109
#  define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 0x910A
#  define GL_VERTEX_ATTRIB_BINDING 0x82D4
#  define GL_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D5
#  define GL_VERTEX_BINDING_DIVISOR 0x82D6
#  define GL_VERTEX_BINDING_OFFSET 0x82D7
#  define GL_VERTEX_BINDING_STRIDE 0x82D8
#  define GL_VERTEX_BINDING_BUFFER 0x8F4F
#  define GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 0x82D9
#  define GL_MAX_VERTEX_ATTRIB_BINDINGS 0x82DA
#  define GL_MAX_VERTEX_ATTRIB_STRIDE 0x82E5
# 
# endif /* GL_ES_VERSION_3_1 */
# if defined GL_ES_VERSION_3_2
# 
#  define GL_MULTISAMPLE_LINE_WIDTH_RANGE 0x9381
#  define GL_MULTISAMPLE_LINE_WIDTH_GRANULARITY 0x9382
#  define GL_MULTIPLY 0x9294
#  define GL_SCREEN 0x9295
#  define GL_OVERLAY 0x9296
#  define GL_DARKEN 0x9297
#  define GL_LIGHTEN 0x9298
#  define GL_COLORDODGE 0x9299
#  define GL_COLORBURN 0x929A
#  define GL_HARDLIGHT 0x929B
#  define GL_SOFTLIGHT 0x929C
#  define GL_DIFFERENCE 0x929E
#  define GL_EXCLUSION 0x92A0
#  define GL_HSL_HUE 0x92AD
#  define GL_HSL_SATURATION 0x92AE
#  define GL_HSL_COLOR 0x92AF
#  define GL_HSL_LUMINOSITY 0x92B0
#  define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#  define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#  define GL_DEBUG_CALLBACK_FUNCTION 0x8244
#  define GL_DEBUG_CALLBACK_USER_PARAM 0x8245
#  define GL_DEBUG_SOURCE_API 0x8246
#  define GL_DEBUG_SOURCE_WINDOW_SYSTEM 0x8247
#  define GL_DEBUG_SOURCE_SHADER_COMPILER 0x8248
#  define GL_DEBUG_SOURCE_THIRD_PARTY 0x8249
#  define GL_DEBUG_SOURCE_APPLICATION 0x824A
#  define GL_DEBUG_SOURCE_OTHER 0x824B
#  define GL_DEBUG_TYPE_ERROR 0x824C
#  define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#  define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR 0x824E
#  define GL_DEBUG_TYPE_PORTABILITY 0x824F
#  define GL_DEBUG_TYPE_PERFORMANCE 0x8250
#  define GL_DEBUG_TYPE_OTHER 0x8251
#  define GL_DEBUG_TYPE_MARKER 0x8268
#  define GL_DEBUG_TYPE_PUSH_GROUP 0x8269
#  define GL_DEBUG_TYPE_POP_GROUP 0x826A
#  define GL_DEBUG_SEVERITY_NOTIFICATION 0x826B
#  define GL_MAX_DEBUG_GROUP_STACK_DEPTH 0x826C
#  define GL_DEBUG_GROUP_STACK_DEPTH 0x826D
#  define GL_BUFFER 0x82E0
#  define GL_SHADER 0x82E1
#  define GL_PROGRAM 0x82E2
#  define GL_VERTEX_ARRAY 0x8074
#  define GL_QUERY 0x82E3
#  define GL_PROGRAM_PIPELINE 0x82E4
#  define GL_SAMPLER 0x82E6
#  define GL_MAX_LABEL_LENGTH 0x82E8
#  define GL_MAX_DEBUG_MESSAGE_LENGTH 0x9143
#  define GL_MAX_DEBUG_LOGGED_MESSAGES 0x9144
#  define GL_DEBUG_LOGGED_MESSAGES 0x9145
#  define GL_DEBUG_SEVERITY_HIGH 0x9146
#  define GL_DEBUG_SEVERITY_MEDIUM 0x9147
#  define GL_DEBUG_SEVERITY_LOW 0x9148
#  define GL_DEBUG_OUTPUT 0x92E0
#  define GL_CONTEXT_FLAG_DEBUG_BIT 0x00000002
#  define GL_STACK_OVERFLOW 0x0503
#  define GL_STACK_UNDERFLOW 0x0504
#  define GL_GEOMETRY_SHADER 0x8DD9
#  define GL_GEOMETRY_SHADER_BIT 0x00000004
#  define GL_GEOMETRY_VERTICES_OUT 0x8916
#  define GL_GEOMETRY_INPUT_TYPE 0x8917
#  define GL_GEOMETRY_OUTPUT_TYPE 0x8918
#  define GL_GEOMETRY_SHADER_INVOCATIONS 0x887F
#  define GL_LAYER_PROVOKING_VERTEX 0x825E
#  define GL_LINES_ADJACENCY 0x000A
#  define GL_LINE_STRIP_ADJACENCY 0x000B
#  define GL_TRIANGLES_ADJACENCY 0x000C
#  define GL_TRIANGLE_STRIP_ADJACENCY 0x000D
#  define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#  define GL_MAX_GEOMETRY_UNIFORM_BLOCKS 0x8A2C
#  define GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 0x8A32
#  define GL_MAX_GEOMETRY_INPUT_COMPONENTS 0x9123
#  define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#  define GL_MAX_GEOMETRY_OUTPUT_VERTICES 0x8DE0
#  define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#  define GL_MAX_GEOMETRY_SHADER_INVOCATIONS 0x8E5A
#  define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#  define GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 0x92CF
#  define GL_MAX_GEOMETRY_ATOMIC_COUNTERS 0x92D5
#  define GL_MAX_GEOMETRY_IMAGE_UNIFORMS 0x90CD
#  define GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 0x90D7
#  define GL_FIRST_VERTEX_CONVENTION 0x8E4D
#  define GL_LAST_VERTEX_CONVENTION 0x8E4E
#  define GL_UNDEFINED_VERTEX 0x8260
#  define GL_PRIMITIVES_GENERATED 0x8C87
#  define GL_FRAMEBUFFER_DEFAULT_LAYERS 0x9312
#  define GL_MAX_FRAMEBUFFER_LAYERS 0x9317
#  define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#  define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#  define GL_REFERENCED_BY_GEOMETRY_SHADER 0x9309
#  define GL_PRIMITIVE_BOUNDING_BOX 0x92BE
#  define GL_NO_ERROR 0
#  define GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 0x00000004
#  define GL_CONTEXT_FLAGS 0x821E
#  define GL_LOSE_CONTEXT_ON_RESET 0x8252
#  define GL_GUILTY_CONTEXT_RESET 0x8253
#  define GL_INNOCENT_CONTEXT_RESET 0x8254
#  define GL_UNKNOWN_CONTEXT_RESET 0x8255
#  define GL_RESET_NOTIFICATION_STRATEGY 0x8256
#  define GL_NO_RESET_NOTIFICATION 0x8261
#  define GL_CONTEXT_LOST 0x0507
#  define GL_SAMPLE_SHADING 0x8C36
#  define GL_MIN_SAMPLE_SHADING_VALUE 0x8C37
#  define GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 0x8E5B
#  define GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 0x8E5C
#  define GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 0x8E5D
#  define GL_PATCHES 0x000E
#  define GL_PATCH_VERTICES 0x8E72
#  define GL_TESS_CONTROL_OUTPUT_VERTICES 0x8E75
#  define GL_TESS_GEN_MODE 0x8E76
#  define GL_TESS_GEN_SPACING 0x8E77
#  define GL_TESS_GEN_VERTEX_ORDER 0x8E78
#  define GL_TESS_GEN_POINT_MODE 0x8E79
#  define GL_TRIANGLES 0x0004
#  define GL_ISOLINES 0x8E7A
#  define GL_QUADS 0x0007
#  define GL_EQUAL 0x0202
#  define GL_FRACTIONAL_ODD 0x8E7B
#  define GL_FRACTIONAL_EVEN 0x8E7C
#  define GL_CCW 0x0901
#  define GL_CW 0x0900
#  define GL_MAX_PATCH_VERTICES 0x8E7D
#  define GL_MAX_TESS_GEN_LEVEL 0x8E7E
#  define GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E7F
#  define GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E80
#  define GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 0x8E81
#  define GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 0x8E82
#  define GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 0x8E83
#  define GL_MAX_TESS_PATCH_COMPONENTS 0x8E84
#  define GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 0x8E85
#  define GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 0x8E86
#  define GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 0x8E89
#  define GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 0x8E8A
#  define GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 0x886C
#  define GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 0x886D
#  define GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 0x8E1E
#  define GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 0x8E1F
#  define GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 0x92CD
#  define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 0x92CE
#  define GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 0x92D3
#  define GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 0x92D4
#  define GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 0x90CB
#  define GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 0x90CC
#  define GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 0x90D8
#  define GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 0x90D9
#  define GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 0x8221
#  define GL_IS_PER_PATCH 0x92E7
#  define GL_REFERENCED_BY_TESS_CONTROL_SHADER 0x9307
#  define GL_REFERENCED_BY_TESS_EVALUATION_SHADER 0x9308
#  define GL_TESS_CONTROL_SHADER 0x8E88
#  define GL_TESS_EVALUATION_SHADER 0x8E87
#  define GL_TESS_CONTROL_SHADER_BIT 0x00000008
#  define GL_TESS_EVALUATION_SHADER_BIT 0x00000010
#  define GL_TEXTURE_BORDER_COLOR 0x1004
#  define GL_CLAMP_TO_BORDER 0x812D
#  define GL_TEXTURE_BUFFER 0x8C2A
#  define GL_TEXTURE_BUFFER_BINDING 0x8C2A
#  define GL_MAX_TEXTURE_BUFFER_SIZE 0x8C2B
#  define GL_TEXTURE_BINDING_BUFFER 0x8C2C
#  define GL_TEXTURE_BUFFER_DATA_STORE_BINDING 0x8C2D
#  define GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 0x919F
#  define GL_SAMPLER_BUFFER 0x8DC2
#  define GL_INT_SAMPLER_BUFFER 0x8DD0
#  define GL_UNSIGNED_INT_SAMPLER_BUFFER 0x8DD8
#  define GL_IMAGE_BUFFER 0x9051
#  define GL_INT_IMAGE_BUFFER 0x905C
#  define GL_UNSIGNED_INT_IMAGE_BUFFER 0x9067
#  define GL_TEXTURE_BUFFER_OFFSET 0x919D
#  define GL_TEXTURE_BUFFER_SIZE 0x919E
#  define GL_COMPRESSED_RGBA_ASTC_4x4 0x93B0
#  define GL_COMPRESSED_RGBA_ASTC_5x4 0x93B1
#  define GL_COMPRESSED_RGBA_ASTC_5x5 0x93B2
#  define GL_COMPRESSED_RGBA_ASTC_6x5 0x93B3
#  define GL_COMPRESSED_RGBA_ASTC_6x6 0x93B4
#  define GL_COMPRESSED_RGBA_ASTC_8x5 0x93B5
#  define GL_COMPRESSED_RGBA_ASTC_8x6 0x93B6
#  define GL_COMPRESSED_RGBA_ASTC_8x8 0x93B7
#  define GL_COMPRESSED_RGBA_ASTC_10x5 0x93B8
#  define GL_COMPRESSED_RGBA_ASTC_10x6 0x93B9
#  define GL_COMPRESSED_RGBA_ASTC_10x8 0x93BA
#  define GL_COMPRESSED_RGBA_ASTC_10x10 0x93BB
#  define GL_COMPRESSED_RGBA_ASTC_12x10 0x93BC
#  define GL_COMPRESSED_RGBA_ASTC_12x12 0x93BD
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_4x4 0x93D0
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x4 0x93D1
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_5x5 0x93D2
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x5 0x93D3
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_6x6 0x93D4
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x5 0x93D5
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x6 0x93D6
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_8x8 0x93D7
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x5 0x93D8
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x6 0x93D9
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x8 0x93DA
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_10x10 0x93DB
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x10 0x93DC
#  define GL_COMPRESSED_SRGB8_ALPHA8_ASTC_12x12 0x93DD
#  define GL_TEXTURE_CUBE_MAP_ARRAY 0x9009
#  define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#  define GL_SAMPLER_CUBE_MAP_ARRAY 0x900C
#  define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 0x900D
#  define GL_INT_SAMPLER_CUBE_MAP_ARRAY 0x900E
#  define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
#  define GL_IMAGE_CUBE_MAP_ARRAY 0x9054
#  define GL_INT_IMAGE_CUBE_MAP_ARRAY 0x905F
#  define GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 0x906A
#  define GL_STENCIL_INDEX 0x1901
#  define GL_STENCIL_INDEX8 0x8D48
#  define GL_TEXTURE_2D_MULTISAMPLE_ARRAY 0x9102
#  define GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 0x9105
#  define GL_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910B
#  define GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910C
#  define GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 0x910D
# 
# endif /* GL_ES_VERSION_3_2 */
# if defined GL_SC_VERSION_2_0
# 
#  define GL_DEPTH_BUFFER_BIT 0x00000100
#  define GL_STENCIL_BUFFER_BIT 0x00000400
#  define GL_COLOR_BUFFER_BIT 0x00004000
#  define GL_FALSE 0
#  define GL_TRUE 1
#  define GL_POINTS 0x0000
#  define GL_LINES 0x0001
#  define GL_LINE_LOOP 0x0002
#  define GL_LINE_STRIP 0x0003
#  define GL_TRIANGLES 0x0004
#  define GL_TRIANGLE_STRIP 0x0005
#  define GL_TRIANGLE_FAN 0x0006
#  define GL_ZERO 0
#  define GL_ONE 1
#  define GL_SRC_COLOR 0x0300
#  define GL_ONE_MINUS_SRC_COLOR 0x0301
#  define GL_SRC_ALPHA 0x0302
#  define GL_ONE_MINUS_SRC_ALPHA 0x0303
#  define GL_DST_ALPHA 0x0304
#  define GL_ONE_MINUS_DST_ALPHA 0x0305
#  define GL_DST_COLOR 0x0306
#  define GL_ONE_MINUS_DST_COLOR 0x0307
#  define GL_SRC_ALPHA_SATURATE 0x0308
#  define GL_FUNC_ADD 0x8006
#  define GL_BLEND_EQUATION 0x8009
#  define GL_BLEND_EQUATION_RGB 0x8009
#  define GL_BLEND_EQUATION_ALPHA 0x883D
#  define GL_FUNC_SUBTRACT 0x800A
#  define GL_FUNC_REVERSE_SUBTRACT 0x800B
#  define GL_BLEND_DST_RGB 0x80C8
#  define GL_BLEND_SRC_RGB 0x80C9
#  define GL_BLEND_DST_ALPHA 0x80CA
#  define GL_BLEND_SRC_ALPHA 0x80CB
#  define GL_CONSTANT_COLOR 0x8001
#  define GL_ONE_MINUS_CONSTANT_COLOR 0x8002
#  define GL_CONSTANT_ALPHA 0x8003
#  define GL_ONE_MINUS_CONSTANT_ALPHA 0x8004
#  define GL_BLEND_COLOR 0x8005
#  define GL_ARRAY_BUFFER 0x8892
#  define GL_ELEMENT_ARRAY_BUFFER 0x8893
#  define GL_ARRAY_BUFFER_BINDING 0x8894
#  define GL_ELEMENT_ARRAY_BUFFER_BINDING 0x8895
#  define GL_STREAM_DRAW 0x88E0
#  define GL_STATIC_DRAW 0x88E4
#  define GL_DYNAMIC_DRAW 0x88E8
#  define GL_BUFFER_SIZE 0x8764
#  define GL_BUFFER_USAGE 0x8765
#  define GL_CURRENT_VERTEX_ATTRIB 0x8626
#  define GL_FRONT 0x0404
#  define GL_BACK 0x0405
#  define GL_FRONT_AND_BACK 0x0408
#  define GL_TEXTURE_2D 0x0DE1
#  define GL_CULL_FACE 0x0B44
#  define GL_BLEND 0x0BE2
#  define GL_DITHER 0x0BD0
#  define GL_STENCIL_TEST 0x0B90
#  define GL_DEPTH_TEST 0x0B71
#  define GL_SCISSOR_TEST 0x0C11
#  define GL_POLYGON_OFFSET_FILL 0x8037
#  define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#  define GL_SAMPLE_COVERAGE 0x80A0
#  define GL_NO_ERROR 0
#  define GL_INVALID_ENUM 0x0500
#  define GL_INVALID_VALUE 0x0501
#  define GL_INVALID_OPERATION 0x0502
#  define GL_OUT_OF_MEMORY 0x0505
#  define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#  define GL_CONTEXT_LOST 0x0507
#  define GL_CW 0x0900
#  define GL_CCW 0x0901
#  define GL_LINE_WIDTH 0x0B21
#  define GL_ALIASED_POINT_SIZE_RANGE 0x846D
#  define GL_ALIASED_LINE_WIDTH_RANGE 0x846E
#  define GL_CULL_FACE_MODE 0x0B45
#  define GL_FRONT_FACE 0x0B46
#  define GL_DEPTH_RANGE 0x0B70
#  define GL_DEPTH_WRITEMASK 0x0B72
#  define GL_DEPTH_CLEAR_VALUE 0x0B73
#  define GL_DEPTH_FUNC 0x0B74
#  define GL_STENCIL_CLEAR_VALUE 0x0B91
#  define GL_STENCIL_FUNC 0x0B92
#  define GL_STENCIL_FAIL 0x0B94
#  define GL_STENCIL_PASS_DEPTH_FAIL 0x0B95
#  define GL_STENCIL_PASS_DEPTH_PASS 0x0B96
#  define GL_STENCIL_REF 0x0B97
#  define GL_STENCIL_VALUE_MASK 0x0B93
#  define GL_STENCIL_WRITEMASK 0x0B98
#  define GL_STENCIL_BACK_FUNC 0x8800
#  define GL_STENCIL_BACK_FAIL 0x8801
#  define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
#  define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
#  define GL_STENCIL_BACK_REF 0x8CA3
#  define GL_STENCIL_BACK_VALUE_MASK 0x8CA4
#  define GL_STENCIL_BACK_WRITEMASK 0x8CA5
#  define GL_VIEWPORT 0x0BA2
#  define GL_SCISSOR_BOX 0x0C10
#  define GL_COLOR_CLEAR_VALUE 0x0C22
#  define GL_COLOR_WRITEMASK 0x0C23
#  define GL_UNPACK_ALIGNMENT 0x0CF5
#  define GL_PACK_ALIGNMENT 0x0D05
#  define GL_MAX_TEXTURE_SIZE 0x0D33
#  define GL_MAX_VIEWPORT_DIMS 0x0D3A
#  define GL_SUBPIXEL_BITS 0x0D50
#  define GL_RED_BITS 0x0D52
#  define GL_GREEN_BITS 0x0D53
#  define GL_BLUE_BITS 0x0D54
#  define GL_ALPHA_BITS 0x0D55
#  define GL_DEPTH_BITS 0x0D56
#  define GL_STENCIL_BITS 0x0D57
#  define GL_POLYGON_OFFSET_UNITS 0x2A00
#  define GL_POLYGON_OFFSET_FACTOR 0x8038
#  define GL_TEXTURE_BINDING_2D 0x8069
#  define GL_SAMPLE_BUFFERS 0x80A8
#  define GL_SAMPLES 0x80A9
#  define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#  define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#  define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#  define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#  define GL_DONT_CARE 0x1100
#  define GL_FASTEST 0x1101
#  define GL_NICEST 0x1102
#  define GL_GENERATE_MIPMAP_HINT 0x8192
#  define GL_BYTE 0x1400
#  define GL_UNSIGNED_BYTE 0x1401
#  define GL_SHORT 0x1402
#  define GL_UNSIGNED_SHORT 0x1403
#  define GL_INT 0x1404
#  define GL_UNSIGNED_INT 0x1405
#  define GL_FLOAT 0x1406
#  define GL_RED 0x1903
#  define GL_RG 0x8227
#  define GL_RGB 0x1907
#  define GL_RGBA 0x1908
#  define GL_UNSIGNED_SHORT_4_4_4_4 0x8033
#  define GL_UNSIGNED_SHORT_5_5_5_1 0x8034
#  define GL_UNSIGNED_SHORT_5_6_5 0x8363
#  define GL_MAX_VERTEX_ATTRIBS 0x8869
#  define GL_MAX_VERTEX_UNIFORM_VECTORS 0x8DFB
#  define GL_MAX_VARYING_VECTORS 0x8DFC
#  define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#  define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#  define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
#  define GL_MAX_FRAGMENT_UNIFORM_VECTORS 0x8DFD
#  define GL_LINK_STATUS 0x8B82
#  define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#  define GL_CURRENT_PROGRAM 0x8B8D
#  define GL_NEVER 0x0200
#  define GL_LESS 0x0201
#  define GL_EQUAL 0x0202
#  define GL_LEQUAL 0x0203
#  define GL_GREATER 0x0204
#  define GL_NOTEQUAL 0x0205
#  define GL_GEQUAL 0x0206
#  define GL_ALWAYS 0x0207
#  define GL_KEEP 0x1E00
#  define GL_REPLACE 0x1E01
#  define GL_INCR 0x1E02
#  define GL_DECR 0x1E03
#  define GL_INVERT 0x150A
#  define GL_INCR_WRAP 0x8507
#  define GL_DECR_WRAP 0x8508
#  define GL_VENDOR 0x1F00
#  define GL_RENDERER 0x1F01
#  define GL_VERSION 0x1F02
#  define GL_EXTENSIONS 0x1F03
#  define GL_NEAREST 0x2600
#  define GL_LINEAR 0x2601
#  define GL_NEAREST_MIPMAP_NEAREST 0x2700
#  define GL_LINEAR_MIPMAP_NEAREST 0x2701
#  define GL_NEAREST_MIPMAP_LINEAR 0x2702
#  define GL_LINEAR_MIPMAP_LINEAR 0x2703
#  define GL_TEXTURE_MAG_FILTER 0x2800
#  define GL_TEXTURE_MIN_FILTER 0x2801
#  define GL_TEXTURE_WRAP_S 0x2802
#  define GL_TEXTURE_WRAP_T 0x2803
#  define GL_TEXTURE_IMMUTABLE_FORMAT 0x912F
#  define GL_TEXTURE 0x1702
#  define GL_TEXTURE0 0x84C0
#  define GL_TEXTURE1 0x84C1
#  define GL_TEXTURE2 0x84C2
#  define GL_TEXTURE3 0x84C3
#  define GL_TEXTURE4 0x84C4
#  define GL_TEXTURE5 0x84C5
#  define GL_TEXTURE6 0x84C6
#  define GL_TEXTURE7 0x84C7
#  define GL_TEXTURE8 0x84C8
#  define GL_TEXTURE9 0x84C9
#  define GL_TEXTURE10 0x84CA
#  define GL_TEXTURE11 0x84CB
#  define GL_TEXTURE12 0x84CC
#  define GL_TEXTURE13 0x84CD
#  define GL_TEXTURE14 0x84CE
#  define GL_TEXTURE15 0x84CF
#  define GL_TEXTURE16 0x84D0
#  define GL_TEXTURE17 0x84D1
#  define GL_TEXTURE18 0x84D2
#  define GL_TEXTURE19 0x84D3
#  define GL_TEXTURE20 0x84D4
#  define GL_TEXTURE21 0x84D5
#  define GL_TEXTURE22 0x84D6
#  define GL_TEXTURE23 0x84D7
#  define GL_TEXTURE24 0x84D8
#  define GL_TEXTURE25 0x84D9
#  define GL_TEXTURE26 0x84DA
#  define GL_TEXTURE27 0x84DB
#  define GL_TEXTURE28 0x84DC
#  define GL_TEXTURE29 0x84DD
#  define GL_TEXTURE30 0x84DE
#  define GL_TEXTURE31 0x84DF
#  define GL_ACTIVE_TEXTURE 0x84E0
#  define GL_REPEAT 0x2901
#  define GL_CLAMP_TO_EDGE 0x812F
#  define GL_MIRRORED_REPEAT 0x8370
#  define GL_SAMPLER_2D 0x8B5E
#  define GL_VERTEX_ATTRIB_ARRAY_ENABLED 0x8622
#  define GL_VERTEX_ATTRIB_ARRAY_SIZE 0x8623
#  define GL_VERTEX_ATTRIB_ARRAY_STRIDE 0x8624
#  define GL_VERTEX_ATTRIB_ARRAY_TYPE 0x8625
#  define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#  define GL_VERTEX_ATTRIB_ARRAY_POINTER 0x8645
#  define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 0x889F
#  define GL_IMPLEMENTATION_COLOR_READ_TYPE 0x8B9A
#  define GL_IMPLEMENTATION_COLOR_READ_FORMAT 0x8B9B
#  define GL_NUM_PROGRAM_BINARY_FORMATS 0x87FE
#  define GL_PROGRAM_BINARY_FORMATS 0x87FF
#  define GL_LOW_FLOAT 0x8DF0
#  define GL_MEDIUM_FLOAT 0x8DF1
#  define GL_HIGH_FLOAT 0x8DF2
#  define GL_LOW_INT 0x8DF3
#  define GL_MEDIUM_INT 0x8DF4
#  define GL_HIGH_INT 0x8DF5
#  define GL_FRAMEBUFFER 0x8D40
#  define GL_RENDERBUFFER 0x8D41
#  define GL_R8 0x8229
#  define GL_RG8 0x822B
#  define GL_RGB8 0x8051
#  define GL_RGBA8 0x8058
#  define GL_RGBA4 0x8056
#  define GL_RGB5_A1 0x8057
#  define GL_RGB565 0x8D62
#  define GL_DEPTH_COMPONENT16 0x81A5
#  define GL_STENCIL_INDEX8 0x8D48
#  define GL_RENDERBUFFER_WIDTH 0x8D42
#  define GL_RENDERBUFFER_HEIGHT 0x8D43
#  define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8D44
#  define GL_RENDERBUFFER_RED_SIZE 0x8D50
#  define GL_RENDERBUFFER_GREEN_SIZE 0x8D51
#  define GL_RENDERBUFFER_BLUE_SIZE 0x8D52
#  define GL_RENDERBUFFER_ALPHA_SIZE 0x8D53
#  define GL_RENDERBUFFER_DEPTH_SIZE 0x8D54
#  define GL_RENDERBUFFER_STENCIL_SIZE 0x8D55
#  define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#  define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#  define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#  define GL_COLOR_ATTACHMENT0 0x8CE0
#  define GL_DEPTH_ATTACHMENT 0x8D00
#  define GL_STENCIL_ATTACHMENT 0x8D20
#  define GL_NONE 0
#  define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#  define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#  define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#  define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS 0x8CD9
#  define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
#  define GL_FRAMEBUFFER_UNDEFINED 0x8219
#  define GL_FRAMEBUFFER_BINDING 0x8CA6
#  define GL_RENDERBUFFER_BINDING 0x8CA7
#  define GL_MAX_RENDERBUFFER_SIZE 0x84E8
#  define GL_GUILTY_CONTEXT_RESET 0x8253
#  define GL_INNOCENT_CONTEXT_RESET 0x8254
#  define GL_UNKNOWN_CONTEXT_RESET 0x8255
#  define GL_CONTEXT_ROBUST_ACCESS 0x90F3
#  define GL_RESET_NOTIFICATION_STRATEGY 0x8256
#  define GL_LOSE_CONTEXT_ON_RESET 0x8252
# 
# endif /* GL_SC_VERSION_2_0 */
# if defined GL_VERSION_1_0

typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum);
typedef void (APIENTRYP PFNGLFRONTFACEPROC) (GLenum);
typedef void (APIENTRYP PFNGLHINTPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat);
typedef void (APIENTRYP PFNGLPOINTSIZEPROC) (GLfloat);
typedef void (APIENTRYP PFNGLPOLYGONMODEPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLTEXIMAGE1DPROC) (GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLDRAWBUFFERPROC) (GLenum);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint);
typedef void (APIENTRYP PFNGLCLEARDEPTHPROC) (GLdouble);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint);
typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean);
typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum);
typedef void (APIENTRYP PFNGLFINISHPROC) (void);
typedef void (APIENTRYP PFNGLFLUSHPROC) (void);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLLOGICOPPROC) (GLenum);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum, GLint, GLuint);
typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum);
typedef void (APIENTRYP PFNGLPIXELSTOREFPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLREADBUFFERPROC) (GLenum);
typedef void (APIENTRYP PFNGLREADPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum, GLboolean *);
typedef void (APIENTRYP PFNGLGETDOUBLEVPROC) (GLenum, GLdouble *);
typedef GLenum (APIENTRYP PFNGLGETERRORPROC) (void);
typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum, GLint *);
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC) (GLenum);
typedef void (APIENTRYP PFNGLGETTEXIMAGEPROC) (GLenum, GLint, GLenum, GLenum, void *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum, GLint, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum, GLint, GLenum, GLint *);
typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC) (GLenum);
typedef void (APIENTRYP PFNGLDEPTHRANGEPROC) (GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLNEWLISTPROC) (GLuint, GLenum);
typedef void (APIENTRYP PFNGLENDLISTPROC) (void);
typedef void (APIENTRYP PFNGLCALLLISTPROC) (GLuint);
typedef void (APIENTRYP PFNGLCALLLISTSPROC) (GLsizei, GLenum, const void *);
typedef void (APIENTRYP PFNGLDELETELISTSPROC) (GLuint, GLsizei);
typedef GLuint (APIENTRYP PFNGLGENLISTSPROC) (GLsizei);
typedef void (APIENTRYP PFNGLLISTBASEPROC) (GLuint);
typedef void (APIENTRYP PFNGLBEGINPROC) (GLenum);
typedef void (APIENTRYP PFNGLBITMAPPROC) (GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat, const GLubyte *);
typedef void (APIENTRYP PFNGLCOLOR3BPROC) (GLbyte, GLbyte, GLbyte);
typedef void (APIENTRYP PFNGLCOLOR3BVPROC) (const GLbyte *);
typedef void (APIENTRYP PFNGLCOLOR3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLCOLOR3DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLCOLOR3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCOLOR3FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLCOLOR3IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLCOLOR3IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLCOLOR3SPROC) (GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLCOLOR3SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLCOLOR3UBPROC) (GLubyte, GLubyte, GLubyte);
typedef void (APIENTRYP PFNGLCOLOR3UBVPROC) (const GLubyte *);
typedef void (APIENTRYP PFNGLCOLOR3UIPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLCOLOR3UIVPROC) (const GLuint *);
typedef void (APIENTRYP PFNGLCOLOR3USPROC) (GLushort, GLushort, GLushort);
typedef void (APIENTRYP PFNGLCOLOR3USVPROC) (const GLushort *);
typedef void (APIENTRYP PFNGLCOLOR4BPROC) (GLbyte, GLbyte, GLbyte, GLbyte);
typedef void (APIENTRYP PFNGLCOLOR4BVPROC) (const GLbyte *);
typedef void (APIENTRYP PFNGLCOLOR4DPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLCOLOR4DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLCOLOR4FPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCOLOR4FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLCOLOR4IPROC) (GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLCOLOR4IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLCOLOR4SPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLCOLOR4SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLCOLOR4UBPROC) (GLubyte, GLubyte, GLubyte, GLubyte);
typedef void (APIENTRYP PFNGLCOLOR4UBVPROC) (const GLubyte *);
typedef void (APIENTRYP PFNGLCOLOR4UIPROC) (GLuint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLCOLOR4UIVPROC) (const GLuint *);
typedef void (APIENTRYP PFNGLCOLOR4USPROC) (GLushort, GLushort, GLushort, GLushort);
typedef void (APIENTRYP PFNGLCOLOR4USVPROC) (const GLushort *);
typedef void (APIENTRYP PFNGLEDGEFLAGPROC) (GLboolean);
typedef void (APIENTRYP PFNGLEDGEFLAGVPROC) (const GLboolean *);
typedef void (APIENTRYP PFNGLENDPROC) (void);
typedef void (APIENTRYP PFNGLINDEXDPROC) (GLdouble);
typedef void (APIENTRYP PFNGLINDEXDVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLINDEXFPROC) (GLfloat);
typedef void (APIENTRYP PFNGLINDEXFVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLINDEXIPROC) (GLint);
typedef void (APIENTRYP PFNGLINDEXIVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLINDEXSPROC) (GLshort);
typedef void (APIENTRYP PFNGLINDEXSVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLNORMAL3BPROC) (GLbyte, GLbyte, GLbyte);
typedef void (APIENTRYP PFNGLNORMAL3BVPROC) (const GLbyte *);
typedef void (APIENTRYP PFNGLNORMAL3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLNORMAL3DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLNORMAL3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLNORMAL3FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLNORMAL3IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLNORMAL3IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLNORMAL3SPROC) (GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLNORMAL3SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLRASTERPOS2DPROC) (GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLRASTERPOS2DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLRASTERPOS2FPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLRASTERPOS2FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLRASTERPOS2IPROC) (GLint, GLint);
typedef void (APIENTRYP PFNGLRASTERPOS2IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLRASTERPOS2SPROC) (GLshort, GLshort);
typedef void (APIENTRYP PFNGLRASTERPOS2SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLRASTERPOS3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLRASTERPOS3DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLRASTERPOS3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLRASTERPOS3FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLRASTERPOS3IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLRASTERPOS3IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLRASTERPOS3SPROC) (GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLRASTERPOS3SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLRASTERPOS4DPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLRASTERPOS4DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLRASTERPOS4FPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLRASTERPOS4FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLRASTERPOS4IPROC) (GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLRASTERPOS4IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLRASTERPOS4SPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLRASTERPOS4SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLRECTDPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLRECTDVPROC) (const GLdouble *, const GLdouble *);
typedef void (APIENTRYP PFNGLRECTFPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLRECTFVPROC) (const GLfloat *, const GLfloat *);
typedef void (APIENTRYP PFNGLRECTIPROC) (GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLRECTIVPROC) (const GLint *, const GLint *);
typedef void (APIENTRYP PFNGLRECTSPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLRECTSVPROC) (const GLshort *, const GLshort *);
typedef void (APIENTRYP PFNGLTEXCOORD1DPROC) (GLdouble);
typedef void (APIENTRYP PFNGLTEXCOORD1DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLTEXCOORD1FPROC) (GLfloat);
typedef void (APIENTRYP PFNGLTEXCOORD1FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLTEXCOORD1IPROC) (GLint);
typedef void (APIENTRYP PFNGLTEXCOORD1IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLTEXCOORD1SPROC) (GLshort);
typedef void (APIENTRYP PFNGLTEXCOORD1SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLTEXCOORD2DPROC) (GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLTEXCOORD2DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLTEXCOORD2FPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLTEXCOORD2FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLTEXCOORD2IPROC) (GLint, GLint);
typedef void (APIENTRYP PFNGLTEXCOORD2IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLTEXCOORD2SPROC) (GLshort, GLshort);
typedef void (APIENTRYP PFNGLTEXCOORD2SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLTEXCOORD3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLTEXCOORD3DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLTEXCOORD3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLTEXCOORD3FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLTEXCOORD3IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLTEXCOORD3IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLTEXCOORD3SPROC) (GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLTEXCOORD3SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLTEXCOORD4DPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLTEXCOORD4DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLTEXCOORD4FPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLTEXCOORD4FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLTEXCOORD4IPROC) (GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLTEXCOORD4IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLTEXCOORD4SPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLTEXCOORD4SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLVERTEX2DPROC) (GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVERTEX2DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEX2FPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEX2FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEX2IPROC) (GLint, GLint);
typedef void (APIENTRYP PFNGLVERTEX2IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLVERTEX2SPROC) (GLshort, GLshort);
typedef void (APIENTRYP PFNGLVERTEX2SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLVERTEX3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVERTEX3DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEX3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEX3FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEX3IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLVERTEX3IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLVERTEX3SPROC) (GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLVERTEX3SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLVERTEX4DPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVERTEX4DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEX4FPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEX4FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEX4IPROC) (GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLVERTEX4IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLVERTEX4SPROC) (GLshort, GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLVERTEX4SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLCLIPPLANEPROC) (GLenum, const GLdouble *);
typedef void (APIENTRYP PFNGLCOLORMATERIALPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLFOGFPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLFOGFVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLFOGIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLFOGIVPROC) (GLenum, const GLint *);
typedef void (APIENTRYP PFNGLLIGHTFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLLIGHTFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLLIGHTIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLLIGHTIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLLIGHTMODELFPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLLIGHTMODELFVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLLIGHTMODELIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLLIGHTMODELIVPROC) (GLenum, const GLint *);
typedef void (APIENTRYP PFNGLLINESTIPPLEPROC) (GLint, GLushort);
typedef void (APIENTRYP PFNGLMATERIALFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLMATERIALFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLMATERIALIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLMATERIALIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLPOLYGONSTIPPLEPROC) (const GLubyte *);
typedef void (APIENTRYP PFNGLSHADEMODELPROC) (GLenum);
typedef void (APIENTRYP PFNGLTEXENVFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLTEXENVFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLTEXENVIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLTEXENVIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLTEXGENDPROC) (GLenum, GLenum, GLdouble);
typedef void (APIENTRYP PFNGLTEXGENDVPROC) (GLenum, GLenum, const GLdouble *);
typedef void (APIENTRYP PFNGLTEXGENFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLTEXGENFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLTEXGENIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLTEXGENIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLFEEDBACKBUFFERPROC) (GLsizei, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLSELECTBUFFERPROC) (GLsizei, GLuint *);
typedef GLint (APIENTRYP PFNGLRENDERMODEPROC) (GLenum);
typedef void (APIENTRYP PFNGLINITNAMESPROC) (void);
typedef void (APIENTRYP PFNGLLOADNAMEPROC) (GLuint);
typedef void (APIENTRYP PFNGLPASSTHROUGHPROC) (GLfloat);
typedef void (APIENTRYP PFNGLPOPNAMEPROC) (void);
typedef void (APIENTRYP PFNGLPUSHNAMEPROC) (GLuint);
typedef void (APIENTRYP PFNGLCLEARACCUMPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCLEARINDEXPROC) (GLfloat);
typedef void (APIENTRYP PFNGLINDEXMASKPROC) (GLuint);
typedef void (APIENTRYP PFNGLACCUMPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLPOPATTRIBPROC) (void);
typedef void (APIENTRYP PFNGLPUSHATTRIBPROC) (GLbitfield);
typedef void (APIENTRYP PFNGLMAP1DPROC) (GLenum, GLdouble, GLdouble, GLint, GLint, const GLdouble *);
typedef void (APIENTRYP PFNGLMAP1FPROC) (GLenum, GLfloat, GLfloat, GLint, GLint, const GLfloat *);
typedef void (APIENTRYP PFNGLMAP2DPROC) (GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, const GLdouble *);
typedef void (APIENTRYP PFNGLMAP2FPROC) (GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, const GLfloat *);
typedef void (APIENTRYP PFNGLMAPGRID1DPROC) (GLint, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLMAPGRID1FPROC) (GLint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLMAPGRID2DPROC) (GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLMAPGRID2FPROC) (GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLEVALCOORD1DPROC) (GLdouble);
typedef void (APIENTRYP PFNGLEVALCOORD1DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLEVALCOORD1FPROC) (GLfloat);
typedef void (APIENTRYP PFNGLEVALCOORD1FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLEVALCOORD2DPROC) (GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLEVALCOORD2DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLEVALCOORD2FPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLEVALCOORD2FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLEVALMESH1PROC) (GLenum, GLint, GLint);
typedef void (APIENTRYP PFNGLEVALPOINT1PROC) (GLint);
typedef void (APIENTRYP PFNGLEVALMESH2PROC) (GLenum, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLEVALPOINT2PROC) (GLint, GLint);
typedef void (APIENTRYP PFNGLALPHAFUNCPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLPIXELZOOMPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLPIXELTRANSFERFPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLPIXELTRANSFERIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLPIXELMAPFVPROC) (GLenum, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLPIXELMAPUIVPROC) (GLenum, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLPIXELMAPUSVPROC) (GLenum, GLsizei, const GLushort *);
typedef void (APIENTRYP PFNGLCOPYPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum);
typedef void (APIENTRYP PFNGLDRAWPIXELSPROC) (GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLGETCLIPPLANEPROC) (GLenum, GLdouble *);
typedef void (APIENTRYP PFNGLGETLIGHTFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETLIGHTIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETMAPDVPROC) (GLenum, GLenum, GLdouble *);
typedef void (APIENTRYP PFNGLGETMAPFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETMAPIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETMATERIALFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETMATERIALIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETPIXELMAPFVPROC) (GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETPIXELMAPUIVPROC) (GLenum, GLuint *);
typedef void (APIENTRYP PFNGLGETPIXELMAPUSVPROC) (GLenum, GLushort *);
typedef void (APIENTRYP PFNGLGETPOLYGONSTIPPLEPROC) (GLubyte *);
typedef void (APIENTRYP PFNGLGETTEXENVFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXENVIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTEXGENDVPROC) (GLenum, GLenum, GLdouble *);
typedef void (APIENTRYP PFNGLGETTEXGENFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXGENIVPROC) (GLenum, GLenum, GLint *);
typedef GLboolean (APIENTRYP PFNGLISLISTPROC) (GLuint);
typedef void (APIENTRYP PFNGLFRUSTUMPROC) (GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLLOADIDENTITYPROC) (void);
typedef void (APIENTRYP PFNGLLOADMATRIXFPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLLOADMATRIXDPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLMATRIXMODEPROC) (GLenum);
typedef void (APIENTRYP PFNGLMULTMATRIXFPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLMULTMATRIXDPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLORTHOPROC) (GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLPOPMATRIXPROC) (void);
typedef void (APIENTRYP PFNGLPUSHMATRIXPROC) (void);
typedef void (APIENTRYP PFNGLROTATEDPROC) (GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLROTATEFPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLSCALEDPROC) (GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLSCALEFPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLTRANSLATEDPROC) (GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLTRANSLATEFPROC) (GLfloat, GLfloat, GLfloat);

# endif /* GL_VERSION_1_0 */
# if defined GL_VERSION_1_1

typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum, GLint, GLsizei);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum, GLsizei, GLenum, const void *);
typedef void (APIENTRYP PFNGLGETPOINTERVPROC) (GLenum, void **);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE1DPROC) (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE1DPROC) (GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei, GLuint *);
typedef GLboolean (APIENTRYP PFNGLISTEXTUREPROC) (GLuint);
typedef void (APIENTRYP PFNGLARRAYELEMENTPROC) (GLint);
typedef void (APIENTRYP PFNGLCOLORPOINTERPROC) (GLint, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLDISABLECLIENTSTATEPROC) (GLenum);
typedef void (APIENTRYP PFNGLEDGEFLAGPOINTERPROC) (GLsizei, const void *);
typedef void (APIENTRYP PFNGLENABLECLIENTSTATEPROC) (GLenum);
typedef void (APIENTRYP PFNGLINDEXPOINTERPROC) (GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLINTERLEAVEDARRAYSPROC) (GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLNORMALPOINTERPROC) (GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLTEXCOORDPOINTERPROC) (GLint, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLVERTEXPOINTERPROC) (GLint, GLenum, GLsizei, const void *);
typedef GLboolean (APIENTRYP PFNGLARETEXTURESRESIDENTPROC) (GLsizei, const GLuint *, GLboolean *);
typedef void (APIENTRYP PFNGLPRIORITIZETEXTURESPROC) (GLsizei, const GLuint *, const GLfloat *);
typedef void (APIENTRYP PFNGLINDEXUBPROC) (GLubyte);
typedef void (APIENTRYP PFNGLINDEXUBVPROC) (const GLubyte *);
typedef void (APIENTRYP PFNGLPOPCLIENTATTRIBPROC) (void);
typedef void (APIENTRYP PFNGLPUSHCLIENTATTRIBPROC) (GLbitfield);

# endif /* GL_VERSION_1_1 */
# if defined GL_VERSION_1_2

typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum, GLuint, GLuint, GLsizei, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);

# endif /* GL_VERSION_1_2 */
# if defined GL_VERSION_1_3

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat, GLboolean);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC) (GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC) (GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC) (GLenum, GLint, void *);
typedef void (APIENTRYP PFNGLCLIENTACTIVETEXTUREPROC) (GLenum);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1DPROC) (GLenum, GLdouble);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1DVPROC) (GLenum, const GLdouble *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1FPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1FVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1IPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1IVPROC) (GLenum, const GLint *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1SPROC) (GLenum, GLshort);
typedef void (APIENTRYP PFNGLMULTITEXCOORD1SVPROC) (GLenum, const GLshort *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2DPROC) (GLenum, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2DVPROC) (GLenum, const GLdouble *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2FPROC) (GLenum, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2FVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2IPROC) (GLenum, GLint, GLint);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2IVPROC) (GLenum, const GLint *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2SPROC) (GLenum, GLshort, GLshort);
typedef void (APIENTRYP PFNGLMULTITEXCOORD2SVPROC) (GLenum, const GLshort *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3DPROC) (GLenum, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3DVPROC) (GLenum, const GLdouble *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3FPROC) (GLenum, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3FVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3IPROC) (GLenum, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3IVPROC) (GLenum, const GLint *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3SPROC) (GLenum, GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLMULTITEXCOORD3SVPROC) (GLenum, const GLshort *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4DPROC) (GLenum, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4DVPROC) (GLenum, const GLdouble *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4FPROC) (GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4FVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4IPROC) (GLenum, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4IVPROC) (GLenum, const GLint *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4SPROC) (GLenum, GLshort, GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4SVPROC) (GLenum, const GLshort *);
typedef void (APIENTRYP PFNGLLOADTRANSPOSEMATRIXFPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLLOADTRANSPOSEMATRIXDPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLMULTTRANSPOSEMATRIXFPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLMULTTRANSPOSEMATRIXDPROC) (const GLdouble *);

# endif /* GL_VERSION_1_3 */
# if defined GL_VERSION_1_4

typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSPROC) (GLenum, const GLint *, const GLsizei *, GLsizei);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSPROC) (GLenum, const GLsizei *, GLenum, const void *const*, GLsizei);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLPOINTPARAMETERIVPROC) (GLenum, const GLint *);
typedef void (APIENTRYP PFNGLFOGCOORDFPROC) (GLfloat);
typedef void (APIENTRYP PFNGLFOGCOORDFVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLFOGCOORDDPROC) (GLdouble);
typedef void (APIENTRYP PFNGLFOGCOORDDVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLFOGCOORDPOINTERPROC) (GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3BPROC) (GLbyte, GLbyte, GLbyte);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3BVPROC) (const GLbyte *);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3SPROC) (GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3UBPROC) (GLubyte, GLubyte, GLubyte);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3UBVPROC) (const GLubyte *);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3UIPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3UIVPROC) (const GLuint *);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3USPROC) (GLushort, GLushort, GLushort);
typedef void (APIENTRYP PFNGLSECONDARYCOLOR3USVPROC) (const GLushort *);
typedef void (APIENTRYP PFNGLSECONDARYCOLORPOINTERPROC) (GLint, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLWINDOWPOS2DPROC) (GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLWINDOWPOS2DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLWINDOWPOS2FPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLWINDOWPOS2FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLWINDOWPOS2IPROC) (GLint, GLint);
typedef void (APIENTRYP PFNGLWINDOWPOS2IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLWINDOWPOS2SPROC) (GLshort, GLshort);
typedef void (APIENTRYP PFNGLWINDOWPOS2SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLWINDOWPOS3DPROC) (GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLWINDOWPOS3DVPROC) (const GLdouble *);
typedef void (APIENTRYP PFNGLWINDOWPOS3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLWINDOWPOS3FVPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLWINDOWPOS3IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLWINDOWPOS3IVPROC) (const GLint *);
typedef void (APIENTRYP PFNGLWINDOWPOS3SPROC) (GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLWINDOWPOS3SVPROC) (const GLshort *);
typedef void (APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum);

# endif /* GL_VERSION_1_4 */
# if defined GL_VERSION_1_5

typedef void (APIENTRYP PFNGLGENQUERIESPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei, const GLuint *);
typedef GLboolean (APIENTRYP PFNGLISQUERYPROC) (GLuint);
typedef void (APIENTRYP PFNGLBEGINQUERYPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLENDQUERYPROC) (GLenum);
typedef void (APIENTRYP PFNGLGETQUERYIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint, GLenum, GLuint *);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei, GLuint *);
typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC) (GLuint);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum, GLsizeiptr, const void *, GLenum);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum, GLintptr, GLsizeiptr, const void *);
typedef void (APIENTRYP PFNGLGETBUFFERSUBDATAPROC) (GLenum, GLintptr, GLsizeiptr, void *);
typedef void * (APIENTRYP PFNGLMAPBUFFERPROC) (GLenum, GLenum);
typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum, GLenum, void **);

# endif /* GL_VERSION_1_5 */
# if defined GL_VERSION_2_0

typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei, const GLenum *);
typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum, GLenum, GLint, GLuint);
typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint, GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC) (GLenum);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint);
typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint);
typedef void (APIENTRYP PFNGLDETACHSHADERPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint, GLsizei, GLsizei *, GLuint *);
typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint, GLint, GLfloat *);
typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint, GLint, GLint *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBDVPROC) (GLuint, GLenum, GLdouble *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint, GLenum, void **);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPROC) (GLuint);
typedef GLboolean (APIENTRYP PFNGLISSHADERPROC) (GLuint);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint, GLsizei, const GLchar *const*, const GLint *);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC) (GLint, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC) (GLint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM3FPROC) (GLint, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM4FPROC) (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM2IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM3IPROC) (GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM4IPROC) (GLint, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DPROC) (GLuint, GLdouble);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1DVPROC) (GLuint, const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SPROC) (GLuint, GLshort);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1SVPROC) (GLuint, const GLshort *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DPROC) (GLuint, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2DVPROC) (GLuint, const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SPROC) (GLuint, GLshort, GLshort);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2SVPROC) (GLuint, const GLshort *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DPROC) (GLuint, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3DVPROC) (GLuint, const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SPROC) (GLuint, GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3SVPROC) (GLuint, const GLshort *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NBVPROC) (GLuint, const GLbyte *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NIVPROC) (GLuint, const GLint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NSVPROC) (GLuint, const GLshort *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBPROC) (GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC) (GLuint, const GLubyte *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC) (GLuint, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC) (GLuint, const GLushort *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4BVPROC) (GLuint, const GLbyte *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DPROC) (GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4DVPROC) (GLuint, const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4IVPROC) (GLuint, const GLint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SPROC) (GLuint, GLshort, GLshort, GLshort, GLshort);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4SVPROC) (GLuint, const GLshort *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UBVPROC) (GLuint, const GLubyte *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4UIVPROC) (GLuint, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4USVPROC) (GLuint, const GLushort *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);

# endif /* GL_VERSION_2_0 */
# if defined GL_VERSION_2_1

typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);

# endif /* GL_VERSION_2_1 */
# if defined GL_VERSION_3_0

typedef void (APIENTRYP PFNGLCOLORMASKIPROC) (GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum, GLuint, GLboolean *);
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum, GLuint, GLint *);
typedef void (APIENTRYP PFNGLENABLEIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDISABLEIPROC) (GLenum, GLuint);
typedef GLboolean (APIENTRYP PFNGLISENABLEDIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum);
typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum, GLuint, GLuint);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint, GLsizei, const GLchar *const*, GLenum);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *);
typedef void (APIENTRYP PFNGLCLAMPCOLORPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC) (GLuint, GLenum);
typedef void (APIENTRYP PFNGLENDCONDITIONALRENDERPROC) (void);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint, GLint, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint, GLenum, GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IPROC) (GLuint, GLint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IPROC) (GLuint, GLint, GLint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IPROC) (GLuint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIPROC) (GLuint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint, GLuint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1IVPROC) (GLuint, const GLint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2IVPROC) (GLuint, const GLint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3IVPROC) (GLuint, const GLint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint, const GLint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC) (GLuint, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC) (GLuint, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC) (GLuint, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4BVPROC) (GLuint, const GLbyte *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4SVPROC) (GLuint, const GLshort *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC) (GLuint, const GLubyte *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4USVPROC) (GLuint, const GLushort *);
typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint, GLint, GLuint *);
typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC) (GLuint, GLuint, const GLchar *);
typedef GLint (APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLUNIFORM1UIPROC) (GLint, GLuint);
typedef void (APIENTRYP PFNGLUNIFORM2UIPROC) (GLint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLUNIFORM3UIPROC) (GLint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLUNIFORM4UIPROC) (GLint, GLuint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum, GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum, GLenum, GLuint *);
typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum, GLint, const GLint *);
typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum, GLint, const GLuint *);
typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum, GLint, const GLfloat *);
typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum, GLint, GLfloat, GLint);
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGIPROC) (GLenum, GLuint);
typedef GLboolean (APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef GLboolean (APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei, GLuint *);
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC) (GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC) (GLenum, GLenum, GLenum, GLuint, GLint, GLint);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum, GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum, GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum);
typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum, GLenum, GLuint, GLint, GLint);
typedef void * (APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum, GLintptr, GLsizeiptr, GLbitfield);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei, GLuint *);
typedef GLboolean (APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint);

# endif /* GL_VERSION_3_0 */
# if defined GL_VERSION_3_1

typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum, GLsizei, GLenum, const void *, GLsizei);
typedef void (APIENTRYP PFNGLTEXBUFFERPROC) (GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLPRIMITIVERESTARTINDEXPROC) (GLuint);
typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint, GLsizei, const GLchar *const*, GLuint *);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint, GLsizei, const GLuint *, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMNAMEPROC) (GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
typedef GLuint (APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint, GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum, GLuint, GLuint);
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum, GLuint, GLint *);

# endif /* GL_VERSION_3_1 */
# if defined GL_VERSION_3_2

typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum, GLsizei, GLenum, const void *, GLint);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum, GLsizei, GLenum, const void *, GLsizei, GLint);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC) (GLenum, const GLsizei *, GLenum, const void *const*, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLPROVOKINGVERTEXPROC) (GLenum);
typedef GLsync (APIENTRYP PFNGLFENCESYNCPROC) (GLenum, GLbitfield);
typedef GLboolean (APIENTRYP PFNGLISSYNCPROC) (GLsync);
typedef void (APIENTRYP PFNGLDELETESYNCPROC) (GLsync);
typedef GLenum (APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync, GLbitfield, GLuint64);
typedef void (APIENTRYP PFNGLWAITSYNCPROC) (GLsync, GLbitfield, GLuint64);
typedef void (APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum, GLint64 *);
typedef void (APIENTRYP PFNGLGETSYNCIVPROC) (GLsync, GLenum, GLsizei, GLsizei *, GLint *);
typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum, GLuint, GLint64 *);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum, GLenum, GLint64 *);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum, GLenum, GLuint, GLint);
typedef void (APIENTRYP PFNGLTEXIMAGE2DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
typedef void (APIENTRYP PFNGLTEXIMAGE3DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum, GLuint, GLfloat *);
typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint, GLbitfield);

# endif /* GL_VERSION_3_2 */
# if defined GL_VERSION_3_3

typedef void (APIENTRYP PFNGLBINDFRAGDATALOCATIONINDEXEDPROC) (GLuint, GLuint, GLuint, const GLchar *);
typedef GLint (APIENTRYP PFNGLGETFRAGDATAINDEXPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei, const GLuint *);
typedef GLboolean (APIENTRYP PFNGLISSAMPLERPROC) (GLuint);
typedef void (APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint, GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint, GLenum, GLuint *);
typedef void (APIENTRYP PFNGLQUERYCOUNTERPROC) (GLuint, GLenum);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTI64VPROC) (GLuint, GLenum, GLint64 *);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUI64VPROC) (GLuint, GLenum, GLuint64 *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIPROC) (GLuint, GLenum, GLboolean, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP1UIVPROC) (GLuint, GLenum, GLboolean, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIPROC) (GLuint, GLenum, GLboolean, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP2UIVPROC) (GLuint, GLenum, GLboolean, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIPROC) (GLuint, GLenum, GLboolean, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP3UIVPROC) (GLuint, GLenum, GLboolean, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIPROC) (GLuint, GLenum, GLboolean, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBP4UIVPROC) (GLuint, GLenum, GLboolean, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXP2UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLVERTEXP2UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXP3UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLVERTEXP3UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLVERTEXP4UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLVERTEXP4UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLTEXCOORDP1UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLTEXCOORDP1UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLTEXCOORDP2UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLTEXCOORDP2UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLTEXCOORDP3UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLTEXCOORDP3UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLTEXCOORDP4UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLTEXCOORDP4UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIPROC) (GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP1UIVPROC) (GLenum, GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIPROC) (GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP2UIVPROC) (GLenum, GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIPROC) (GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP3UIVPROC) (GLenum, GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIPROC) (GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLMULTITEXCOORDP4UIVPROC) (GLenum, GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLNORMALP3UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLNORMALP3UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLCOLORP3UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLCOLORP3UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLCOLORP4UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLCOLORP4UIVPROC) (GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLSECONDARYCOLORP3UIVPROC) (GLenum, const GLuint *);

# endif /* GL_VERSION_3_3 */
# if defined GL_VERSION_4_0

typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat);
typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint, GLenum);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint, GLenum, GLenum);
typedef void (APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint, GLenum, GLenum);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint, GLenum, GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum, const void *);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLUNIFORM1DPROC) (GLint, GLdouble);
typedef void (APIENTRYP PFNGLUNIFORM2DPROC) (GLint, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLUNIFORM3DPROC) (GLint, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLUNIFORM4DPROC) (GLint, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLUNIFORM1DVPROC) (GLint, GLsizei, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORM2DVPROC) (GLint, GLsizei, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORM3DVPROC) (GLint, GLsizei, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORM4DVPROC) (GLint, GLsizei, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2DVPROC) (GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3DVPROC) (GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4DVPROC) (GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3DVPROC) (GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4DVPROC) (GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2DVPROC) (GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4DVPROC) (GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2DVPROC) (GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3DVPROC) (GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLGETUNIFORMDVPROC) (GLuint, GLint, GLdouble *);
typedef GLint (APIENTRYP PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC) (GLuint, GLenum, const GLchar *);
typedef GLuint (APIENTRYP PFNGLGETSUBROUTINEINDEXPROC) (GLuint, GLenum, const GLchar *);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC) (GLuint, GLenum, GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC) (GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLGETACTIVESUBROUTINENAMEPROC) (GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLUNIFORMSUBROUTINESUIVPROC) (GLenum, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGETUNIFORMSUBROUTINEUIVPROC) (GLenum, GLint, GLuint *);
typedef void (APIENTRYP PFNGLGETPROGRAMSTAGEIVPROC) (GLuint, GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLPATCHPARAMETERFVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei, GLuint *);
typedef GLboolean (APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint);
typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC) (GLenum, GLuint, GLuint);
typedef void (APIENTRYP PFNGLBEGINQUERYINDEXEDPROC) (GLenum, GLuint, GLuint);
typedef void (APIENTRYP PFNGLENDQUERYINDEXEDPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLGETQUERYINDEXEDIVPROC) (GLenum, GLuint, GLenum, GLint *);

# endif /* GL_VERSION_4_0 */
# if defined GL_VERSION_4_1

typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (void);
typedef void (APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei, const GLuint *, GLenum, const void *, GLsizei);
typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum, GLenum, GLint *, GLint *);
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat);
typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint, GLsizei, GLsizei *, GLenum *, void *);
typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint, GLenum, const void *, GLsizei);
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint, GLbitfield, GLuint);
typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint, GLuint);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum, GLsizei, const GLchar *const*);
typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei, GLuint *);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint, GLint, GLint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint, GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint, GLint, GLfloat);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint, GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DPROC) (GLuint, GLint, GLdouble);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1DVPROC) (GLuint, GLint, GLsizei, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint, GLint, GLuint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint, GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint, GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint, GLint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint, GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DPROC) (GLuint, GLint, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2DVPROC) (GLuint, GLint, GLsizei, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint, GLint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint, GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint, GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint, GLint, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint, GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DPROC) (GLuint, GLint, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3DVPROC) (GLuint, GLint, GLsizei, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint, GLint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint, GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint, GLint, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint, GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint, GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DPROC) (GLuint, GLint, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4DVPROC) (GLuint, GLint, GLsizei, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint, GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2DVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3DVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4DVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLdouble *);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DPROC) (GLuint, GLdouble);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DPROC) (GLuint, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DPROC) (GLuint, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DPROC) (GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL1DVPROC) (GLuint, const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL2DVPROC) (GLuint, const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL3DVPROC) (GLuint, const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBL4DVPROC) (GLuint, const GLdouble *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLPOINTERPROC) (GLuint, GLint, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBLDVPROC) (GLuint, GLenum, GLdouble *);
typedef void (APIENTRYP PFNGLVIEWPORTARRAYVPROC) (GLuint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFPROC) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVIEWPORTINDEXEDFVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLSCISSORARRAYVPROC) (GLuint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDPROC) (GLuint, GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLSCISSORINDEXEDVPROC) (GLuint, const GLint *);
typedef void (APIENTRYP PFNGLDEPTHRANGEARRAYVPROC) (GLuint, GLsizei, const GLdouble *);
typedef void (APIENTRYP PFNGLDEPTHRANGEINDEXEDPROC) (GLuint, GLdouble, GLdouble);
typedef void (APIENTRYP PFNGLGETFLOATI_VPROC) (GLenum, GLuint, GLfloat *);
typedef void (APIENTRYP PFNGLGETDOUBLEI_VPROC) (GLenum, GLuint, GLdouble *);

# endif /* GL_VERSION_4_1 */
# if defined GL_VERSION_4_2

typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC) (GLenum, GLint, GLsizei, GLsizei, GLuint);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC) (GLenum, GLsizei, GLenum, const void *, GLsizei, GLuint);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC) (GLenum, GLsizei, GLenum, const void *, GLsizei, GLint, GLuint);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum, GLenum, GLenum, GLsizei, GLint *);
typedef void (APIENTRYP PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC) (GLuint, GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
typedef void (APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield);
typedef void (APIENTRYP PFNGLTEXSTORAGE1DPROC) (GLenum, GLsizei, GLenum, GLsizei);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC) (GLenum, GLuint, GLsizei);
typedef void (APIENTRYP PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC) (GLenum, GLuint, GLuint, GLsizei);

# endif /* GL_VERSION_4_2 */
# if defined GL_VERSION_4_3

typedef void (APIENTRYP PFNGLCLEARBUFFERDATAPROC) (GLenum, GLenum, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLCLEARBUFFERSUBDATAPROC) (GLenum, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr);
typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATI64VPROC) (GLenum, GLenum, GLenum, GLsizei, GLint64 *);
typedef void (APIENTRYP PFNGLINVALIDATETEXSUBIMAGEPROC) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLINVALIDATETEXIMAGEPROC) (GLuint, GLint);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERSUBDATAPROC) (GLuint, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLINVALIDATEBUFFERDATAPROC) (GLuint);
typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum, GLsizei, const GLenum *);
typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTPROC) (GLenum, const void *, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTPROC) (GLenum, GLenum, const void *, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint, GLenum, GLenum, GLint *);
typedef GLuint (APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint, GLenum, const GLchar *);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint, GLenum, const GLchar *);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC) (GLuint, GLenum, const GLchar *);
typedef void (APIENTRYP PFNGLSHADERSTORAGEBLOCKBINDINGPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
typedef void (APIENTRYP PFNGLTEXTUREVIEWPROC) (GLuint, GLenum, GLuint, GLenum, GLuint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint, GLuint, GLintptr, GLsizei);
typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint, GLint, GLenum, GLboolean, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint, GLint, GLenum, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBLFORMATPROC) (GLuint, GLint, GLenum, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC, const void *);
typedef GLuint (APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum, GLuint, GLsizei, const GLchar *);
typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC) (void);
typedef void (APIENTRYP PFNGLOBJECTLABELPROC) (GLenum, GLuint, GLsizei, const GLchar *);
typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC) (const void *, GLsizei, const GLchar *);
typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (const void *, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLGETPOINTERVPROC) (GLenum, void **);

# endif /* GL_VERSION_4_3 */
# if defined GL_VERSION_4_4

typedef void (APIENTRYP PFNGLBUFFERSTORAGEPROC) (GLenum, GLsizeiptr, const void *, GLbitfield);
typedef void (APIENTRYP PFNGLCLEARTEXIMAGEPROC) (GLuint, GLint, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLCLEARTEXSUBIMAGEPROC) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLBINDBUFFERSBASEPROC) (GLenum, GLuint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLBINDBUFFERSRANGEPROC) (GLenum, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizeiptr *);
typedef void (APIENTRYP PFNGLBINDTEXTURESPROC) (GLuint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLBINDSAMPLERSPROC) (GLuint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTURESPROC) (GLuint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERSPROC) (GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);

# endif /* GL_VERSION_4_4 */
# if defined GL_VERSION_4_5

typedef void (APIENTRYP PFNGLCLIPCONTROLPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLCREATETRANSFORMFEEDBACKSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC) (GLuint, GLuint, GLuint, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI_VPROC) (GLuint, GLenum, GLuint, GLint *);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKI64_VPROC) (GLuint, GLenum, GLuint, GLint64 *);
typedef void (APIENTRYP PFNGLCREATEBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSTORAGEPROC) (GLuint, GLsizeiptr, const void *, GLbitfield);
typedef void (APIENTRYP PFNGLNAMEDBUFFERDATAPROC) (GLuint, GLsizeiptr, const void *, GLenum);
typedef void (APIENTRYP PFNGLNAMEDBUFFERSUBDATAPROC) (GLuint, GLintptr, GLsizeiptr, const void *);
typedef void (APIENTRYP PFNGLCOPYNAMEDBUFFERSUBDATAPROC) (GLuint, GLuint, GLintptr, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERDATAPROC) (GLuint, GLenum, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLCLEARNAMEDBUFFERSUBDATAPROC) (GLuint, GLenum, GLintptr, GLsizeiptr, GLenum, GLenum, const void *);
typedef void * (APIENTRYP PFNGLMAPNAMEDBUFFERPROC) (GLuint, GLenum);
typedef void * (APIENTRYP PFNGLMAPNAMEDBUFFERRANGEPROC) (GLuint, GLintptr, GLsizeiptr, GLbitfield);
typedef GLboolean (APIENTRYP PFNGLUNMAPNAMEDBUFFERPROC) (GLuint);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC) (GLuint, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPARAMETERI64VPROC) (GLuint, GLenum, GLint64 *);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERPOINTERVPROC) (GLuint, GLenum, void **);
typedef void (APIENTRYP PFNGLGETNAMEDBUFFERSUBDATAPROC) (GLuint, GLintptr, GLsizeiptr, void *);
typedef void (APIENTRYP PFNGLCREATEFRAMEBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC) (GLuint, GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTUREPROC) (GLuint, GLenum, GLuint, GLint);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC) (GLuint, GLenum, GLuint, GLint, GLint);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC) (GLuint, GLenum);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC) (GLuint, GLsizei, const GLenum *);
typedef void (APIENTRYP PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC) (GLuint, GLenum);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC) (GLuint, GLsizei, const GLenum *);
typedef void (APIENTRYP PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC) (GLuint, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERIVPROC) (GLuint, GLenum, GLint, const GLint *);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC) (GLuint, GLenum, GLint, const GLuint *);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFVPROC) (GLuint, GLenum, GLint, const GLfloat *);
typedef void (APIENTRYP PFNGLCLEARNAMEDFRAMEBUFFERFIPROC) (GLuint, GLenum, GLint, GLfloat, GLint);
typedef void (APIENTRYP PFNGLBLITNAMEDFRAMEBUFFERPROC) (GLuint, GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
typedef GLenum (APIENTRYP PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC) (GLuint, GLenum);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLuint, GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLCREATERENDERBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEPROC) (GLuint, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLuint, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLCREATETEXTURESPROC) (GLenum, GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERPROC) (GLuint, GLenum, GLuint);
typedef void (APIENTRYP PFNGLTEXTUREBUFFERRANGEPROC) (GLuint, GLenum, GLuint, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE1DPROC) (GLuint, GLsizei, GLenum, GLsizei);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DPROC) (GLuint, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DPROC) (GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC) (GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
typedef void (APIENTRYP PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC) (GLuint, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE1DPROC) (GLuint, GLint, GLint, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE2DPROC) (GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXTURESUBIMAGE3DPROC) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC) (GLuint, GLint, GLint, GLsizei, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC) (GLuint, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE1DPROC) (GLuint, GLint, GLint, GLint, GLint, GLsizei);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE2DPROC) (GLuint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLCOPYTEXTURESUBIMAGE3DPROC) (GLuint, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFPROC) (GLuint, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERFVPROC) (GLuint, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIIVPROC) (GLuint, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIUIVPROC) (GLuint, GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLTEXTUREPARAMETERIVPROC) (GLuint, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLGENERATETEXTUREMIPMAPPROC) (GLuint);
typedef void (APIENTRYP PFNGLBINDTEXTUREUNITPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLGETTEXTUREIMAGEPROC) (GLuint, GLint, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC) (GLuint, GLint, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERFVPROC) (GLuint, GLint, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXTURELEVELPARAMETERIVPROC) (GLuint, GLint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERFVPROC) (GLuint, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIUIVPROC) (GLuint, GLenum, GLuint *);
typedef void (APIENTRYP PFNGLGETTEXTUREPARAMETERIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLCREATEVERTEXARRAYSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLDISABLEVERTEXARRAYATTRIBPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLENABLEVERTEXARRAYATTRIBPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXARRAYELEMENTBUFFERPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERPROC) (GLuint, GLuint, GLuint, GLintptr, GLsizei);
typedef void (APIENTRYP PFNGLVERTEXARRAYVERTEXBUFFERSPROC) (GLuint, GLuint, GLsizei, const GLuint *, const GLintptr *, const GLsizei *);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBBINDINGPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBFORMATPROC) (GLuint, GLuint, GLint, GLenum, GLboolean, GLuint);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBIFORMATPROC) (GLuint, GLuint, GLint, GLenum, GLuint);
typedef void (APIENTRYP PFNGLVERTEXARRAYATTRIBLFORMATPROC) (GLuint, GLuint, GLint, GLenum, GLuint);
typedef void (APIENTRYP PFNGLVERTEXARRAYBINDINGDIVISORPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXEDIVPROC) (GLuint, GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETVERTEXARRAYINDEXED64IVPROC) (GLuint, GLuint, GLenum, GLint64 *);
typedef void (APIENTRYP PFNGLCREATESAMPLERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLCREATEPROGRAMPIPELINESPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLCREATEQUERIESPROC) (GLenum, GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTI64VPROC) (GLuint, GLuint, GLenum, GLintptr);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTIVPROC) (GLuint, GLuint, GLenum, GLintptr);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUI64VPROC) (GLuint, GLuint, GLenum, GLintptr);
typedef void (APIENTRYP PFNGLGETQUERYBUFFEROBJECTUIVPROC) (GLuint, GLuint, GLenum, GLintptr);
typedef void (APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield);
typedef void (APIENTRYP PFNGLGETTEXTURESUBIMAGEPROC) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC) (GLuint, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLsizei, void *);
typedef GLenum (APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (void);
typedef void (APIENTRYP PFNGLGETNCOMPRESSEDTEXIMAGEPROC) (GLenum, GLint, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETNTEXIMAGEPROC) (GLenum, GLint, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETNUNIFORMDVPROC) (GLuint, GLint, GLsizei, GLdouble *);
typedef void (APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint, GLint, GLsizei, GLfloat *);
typedef void (APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint, GLint, GLsizei, GLint *);
typedef void (APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint, GLint, GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLREADNPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETNMAPDVPROC) (GLenum, GLenum, GLsizei, GLdouble *);
typedef void (APIENTRYP PFNGLGETNMAPFVPROC) (GLenum, GLenum, GLsizei, GLfloat *);
typedef void (APIENTRYP PFNGLGETNMAPIVPROC) (GLenum, GLenum, GLsizei, GLint *);
typedef void (APIENTRYP PFNGLGETNPIXELMAPFVPROC) (GLenum, GLsizei, GLfloat *);
typedef void (APIENTRYP PFNGLGETNPIXELMAPUIVPROC) (GLenum, GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGETNPIXELMAPUSVPROC) (GLenum, GLsizei, GLushort *);
typedef void (APIENTRYP PFNGLGETNPOLYGONSTIPPLEPROC) (GLsizei, GLubyte *);
typedef void (APIENTRYP PFNGLGETNCOLORTABLEPROC) (GLenum, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETNCONVOLUTIONFILTERPROC) (GLenum, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETNSEPARABLEFILTERPROC) (GLenum, GLenum, GLenum, GLsizei, void *, GLsizei, void *, void *);
typedef void (APIENTRYP PFNGLGETNHISTOGRAMPROC) (GLenum, GLboolean, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETNMINMAXPROC) (GLenum, GLboolean, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLTEXTUREBARRIERPROC) (void);

# endif /* GL_VERSION_4_5 */
# if defined GL_VERSION_4_6

typedef void (APIENTRYP PFNGLSPECIALIZESHADERPROC) (GLuint, const GLchar *, GLuint, const GLuint *, const GLuint *);
typedef void (APIENTRYP PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC) (GLenum, const void *, GLintptr, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC) (GLenum, GLenum, const void *, GLintptr, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETCLAMPPROC) (GLfloat, GLfloat, GLfloat);

# endif /* GL_VERSION_4_6 */
# if defined GL_VERSION_ES_CM_1_0

typedef void (APIENTRYP PFNGLALPHAFUNCPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat);
typedef void (APIENTRYP PFNGLCLIPPLANEFPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLCOLOR4FPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLFOGFPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLFOGFVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLFRUSTUMFPROC) (GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLGETCLIPPLANEFPROC) (GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETLIGHTFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETMATERIALFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXENVFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLLIGHTMODELFPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLLIGHTMODELFVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLLIGHTFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLLIGHTFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat);
typedef void (APIENTRYP PFNGLLOADMATRIXFPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLMATERIALFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLMATERIALFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLMULTMATRIXFPROC) (const GLfloat *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4FPROC) (GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLNORMAL3FPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLORTHOFPROC) (GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFPROC) (GLenum, GLfloat);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVPROC) (GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLPOINTSIZEPROC) (GLfloat);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLROTATEFPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLSCALEFPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLTEXENVFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLTEXENVFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLTRANSLATEFPROC) (GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum);
typedef void (APIENTRYP PFNGLALPHAFUNCXPROC) (GLenum, GLfixed);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum, GLsizeiptr, const void *, GLenum);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum, GLintptr, GLsizeiptr, const void *);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield);
typedef void (APIENTRYP PFNGLCLEARCOLORXPROC) (GLfixed, GLfixed, GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLCLEARDEPTHXPROC) (GLfixed);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint);
typedef void (APIENTRYP PFNGLCLIENTACTIVETEXTUREPROC) (GLenum);
typedef void (APIENTRYP PFNGLCLIPPLANEXPROC) (GLenum, const GLfixed *);
typedef void (APIENTRYP PFNGLCOLOR4UBPROC) (GLubyte, GLubyte, GLubyte, GLubyte);
typedef void (APIENTRYP PFNGLCOLOR4XPROC) (GLfixed, GLfixed, GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (APIENTRYP PFNGLCOLORPOINTERPROC) (GLint, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean);
typedef void (APIENTRYP PFNGLDEPTHRANGEXPROC) (GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum);
typedef void (APIENTRYP PFNGLDISABLECLIENTSTATEPROC) (GLenum);
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum, GLint, GLsizei);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum, GLsizei, GLenum, const void *);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum);
typedef void (APIENTRYP PFNGLENABLECLIENTSTATEPROC) (GLenum);
typedef void (APIENTRYP PFNGLFINISHPROC) (void);
typedef void (APIENTRYP PFNGLFLUSHPROC) (void);
typedef void (APIENTRYP PFNGLFOGXPROC) (GLenum, GLfixed);
typedef void (APIENTRYP PFNGLFOGXVPROC) (GLenum, const GLfixed *);
typedef void (APIENTRYP PFNGLFRONTFACEPROC) (GLenum);
typedef void (APIENTRYP PFNGLFRUSTUMXPROC) (GLfixed, GLfixed, GLfixed, GLfixed, GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum, GLboolean *);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETCLIPPLANEXPROC) (GLenum, GLfixed *);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei, GLuint *);
typedef GLenum (APIENTRYP PFNGLGETERRORPROC) (void);
typedef void (APIENTRYP PFNGLGETFIXEDVPROC) (GLenum, GLfixed *);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETLIGHTXVPROC) (GLenum, GLenum, GLfixed *);
typedef void (APIENTRYP PFNGLGETMATERIALXVPROC) (GLenum, GLenum, GLfixed *);
typedef void (APIENTRYP PFNGLGETPOINTERVPROC) (GLenum, void **);
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC) (GLenum);
typedef void (APIENTRYP PFNGLGETTEXENVIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTEXENVXVPROC) (GLenum, GLenum, GLfixed *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERXVPROC) (GLenum, GLenum, GLfixed *);
typedef void (APIENTRYP PFNGLHINTPROC) (GLenum, GLenum);
typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC) (GLuint);
typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC) (GLenum);
typedef GLboolean (APIENTRYP PFNGLISTEXTUREPROC) (GLuint);
typedef void (APIENTRYP PFNGLLIGHTMODELXPROC) (GLenum, GLfixed);
typedef void (APIENTRYP PFNGLLIGHTMODELXVPROC) (GLenum, const GLfixed *);
typedef void (APIENTRYP PFNGLLIGHTXPROC) (GLenum, GLenum, GLfixed);
typedef void (APIENTRYP PFNGLLIGHTXVPROC) (GLenum, GLenum, const GLfixed *);
typedef void (APIENTRYP PFNGLLINEWIDTHXPROC) (GLfixed);
typedef void (APIENTRYP PFNGLLOADIDENTITYPROC) (void);
typedef void (APIENTRYP PFNGLLOADMATRIXXPROC) (const GLfixed *);
typedef void (APIENTRYP PFNGLLOGICOPPROC) (GLenum);
typedef void (APIENTRYP PFNGLMATERIALXPROC) (GLenum, GLenum, GLfixed);
typedef void (APIENTRYP PFNGLMATERIALXVPROC) (GLenum, GLenum, const GLfixed *);
typedef void (APIENTRYP PFNGLMATRIXMODEPROC) (GLenum);
typedef void (APIENTRYP PFNGLMULTMATRIXXPROC) (const GLfixed *);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4XPROC) (GLenum, GLfixed, GLfixed, GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLNORMAL3XPROC) (GLfixed, GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLNORMALPOINTERPROC) (GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLORTHOXPROC) (GLfixed, GLfixed, GLfixed, GLfixed, GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLPOINTPARAMETERXPROC) (GLenum, GLfixed);
typedef void (APIENTRYP PFNGLPOINTPARAMETERXVPROC) (GLenum, const GLfixed *);
typedef void (APIENTRYP PFNGLPOINTSIZEXPROC) (GLfixed);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETXPROC) (GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLPOPMATRIXPROC) (void);
typedef void (APIENTRYP PFNGLPUSHMATRIXPROC) (void);
typedef void (APIENTRYP PFNGLREADPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
typedef void (APIENTRYP PFNGLROTATEXPROC) (GLfixed, GLfixed, GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat, GLboolean);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEXPROC) (GLclampx, GLboolean);
typedef void (APIENTRYP PFNGLSCALEXPROC) (GLfixed, GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLSHADEMODELPROC) (GLenum);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum, GLint, GLuint);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint);
typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLTEXCOORDPOINTERPROC) (GLint, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLTEXENVIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLTEXENVXPROC) (GLenum, GLenum, GLfixed);
typedef void (APIENTRYP PFNGLTEXENVIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLTEXENVXVPROC) (GLenum, GLenum, const GLfixed *);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLTEXPARAMETERXPROC) (GLenum, GLenum, GLfixed);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLTEXPARAMETERXVPROC) (GLenum, GLenum, const GLfixed *);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLTRANSLATEXPROC) (GLfixed, GLfixed, GLfixed);
typedef void (APIENTRYP PFNGLVERTEXPOINTERPROC) (GLint, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint, GLint, GLsizei, GLsizei);

# endif /* GL_VERSION_ES_CM_1_0 */
# if defined GL_ES_VERSION_2_0

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum);
typedef void (APIENTRYP PFNGLATTACHSHADERPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLBINDATTRIBLOCATIONPROC) (GLuint, GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum, GLsizeiptr, const void *, GLenum);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum, GLintptr, GLsizeiptr, const void *);
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint);
typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (APIENTRYP PFNGLCOMPILESHADERPROC) (GLuint);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOPYTEXIMAGE2DPROC) (GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC) (GLenum);
typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum);
typedef void (APIENTRYP PFNGLDELETEBUFFERSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPROC) (GLuint);
typedef void (APIENTRYP PFNGLDELETERENDERBUFFERSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLDELETESHADERPROC) (GLuint);
typedef void (APIENTRYP PFNGLDELETETEXTURESPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean);
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLDETACHSHADERPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum);
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum, GLint, GLsizei);
typedef void (APIENTRYP PFNGLDRAWELEMENTSPROC) (GLenum, GLsizei, GLenum, const void *);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (APIENTRYP PFNGLFINISHPROC) (void);
typedef void (APIENTRYP PFNGLFLUSHPROC) (void);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum, GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (APIENTRYP PFNGLFRONTFACEPROC) (GLenum);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGETACTIVEATTRIBPROC) (GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMPROC) (GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *);
typedef void (APIENTRYP PFNGLGETATTACHEDSHADERSPROC) (GLuint, GLsizei, GLsizei *, GLuint *);
typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum, GLboolean *);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef GLenum (APIENTRYP PFNGLGETERRORPROC) (void);
typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum, GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETSHADERIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLGETSHADERPRECISIONFORMATPROC) (GLenum, GLenum, GLint *, GLint *);
typedef void (APIENTRYP PFNGLGETSHADERSOURCEPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC) (GLenum);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETUNIFORMFVPROC) (GLuint, GLint, GLfloat *);
typedef void (APIENTRYP PFNGLGETUNIFORMIVPROC) (GLuint, GLint, GLint *);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint, GLenum, void **);
typedef void (APIENTRYP PFNGLHINTPROC) (GLenum, GLenum);
typedef GLboolean (APIENTRYP PFNGLISBUFFERPROC) (GLuint);
typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC) (GLenum);
typedef GLboolean (APIENTRYP PFNGLISFRAMEBUFFERPROC) (GLuint);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPROC) (GLuint);
typedef GLboolean (APIENTRYP PFNGLISRENDERBUFFERPROC) (GLuint);
typedef GLboolean (APIENTRYP PFNGLISSHADERPROC) (GLuint);
typedef GLboolean (APIENTRYP PFNGLISTEXTUREPROC) (GLuint);
typedef void (APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat);
typedef void (APIENTRYP PFNGLLINKPROGRAMPROC) (GLuint);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLREADPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, void *);
typedef void (APIENTRYP PFNGLRELEASESHADERCOMPILERPROC) (void);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat, GLboolean);
typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLSHADERBINARYPROC) (GLsizei, const GLuint *, GLenum, const void *, GLsizei);
typedef void (APIENTRYP PFNGLSHADERSOURCEPROC) (GLuint, GLsizei, const GLchar *const*, const GLint *);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum, GLint, GLuint);
typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum, GLenum, GLint, GLuint);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint);
typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLTEXIMAGE2DPROC) (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC) (GLint, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC) (GLint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM2IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORM3FPROC) (GLint, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM3IPROC) (GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORM4FPROC) (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM4IPROC) (GLint, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPROC) (GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint, GLint, GLsizei, GLsizei);

# endif /* GL_ES_VERSION_2_0 */
# if defined GL_ES_VERSION_3_0

typedef void (APIENTRYP PFNGLREADBUFFERPROC) (GLenum);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum, GLuint, GLuint, GLsizei, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXIMAGE3DPROC) (GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC) (GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const void *);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC) (GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLGENQUERIESPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLDELETEQUERIESPROC) (GLsizei, const GLuint *);
typedef GLboolean (APIENTRYP PFNGLISQUERYPROC) (GLuint);
typedef void (APIENTRYP PFNGLBEGINQUERYPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLENDQUERYPROC) (GLenum);
typedef void (APIENTRYP PFNGLGETQUERYIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETQUERYOBJECTUIVPROC) (GLuint, GLenum, GLuint *);
typedef GLboolean (APIENTRYP PFNGLUNMAPBUFFERPROC) (GLenum);
typedef void (APIENTRYP PFNGLGETBUFFERPOINTERVPROC) (GLenum, GLenum, void **);
typedef void (APIENTRYP PFNGLDRAWBUFFERSPROC) (GLsizei, const GLenum *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLBLITFRAMEBUFFERPROC) (GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC) (GLenum, GLenum, GLuint, GLint, GLint);
typedef void * (APIENTRYP PFNGLMAPBUFFERRANGEPROC) (GLenum, GLintptr, GLsizeiptr, GLbitfield);
typedef void (APIENTRYP PFNGLFLUSHMAPPEDBUFFERRANGEPROC) (GLenum, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC) (GLuint);
typedef void (APIENTRYP PFNGLDELETEVERTEXARRAYSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC) (GLsizei, GLuint *);
typedef GLboolean (APIENTRYP PFNGLISVERTEXARRAYPROC) (GLuint);
typedef void (APIENTRYP PFNGLGETINTEGERI_VPROC) (GLenum, GLuint, GLint *);
typedef void (APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC) (GLenum);
typedef void (APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLBINDBUFFERRANGEPROC) (GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLBINDBUFFERBASEPROC) (GLenum, GLuint, GLuint);
typedef void (APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC) (GLuint, GLsizei, const GLchar *const*, GLenum);
typedef void (APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC) (GLuint, GLuint, GLsizei, GLsizei *, GLsizei *, GLenum *, GLchar *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC) (GLuint, GLint, GLenum, GLsizei, const void *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC) (GLuint, GLenum, GLuint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IPROC) (GLuint, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIPROC) (GLuint, GLuint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4IVPROC) (GLuint, const GLint *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC) (GLuint, const GLuint *);
typedef void (APIENTRYP PFNGLGETUNIFORMUIVPROC) (GLuint, GLint, GLuint *);
typedef GLint (APIENTRYP PFNGLGETFRAGDATALOCATIONPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLUNIFORM1UIPROC) (GLint, GLuint);
typedef void (APIENTRYP PFNGLUNIFORM2UIPROC) (GLint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLUNIFORM3UIPROC) (GLint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLUNIFORM4UIPROC) (GLint, GLuint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLUNIFORM1UIVPROC) (GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLUNIFORM2UIVPROC) (GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLUNIFORM3UIVPROC) (GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLUNIFORM4UIVPROC) (GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLCLEARBUFFERIVPROC) (GLenum, GLint, const GLint *);
typedef void (APIENTRYP PFNGLCLEARBUFFERUIVPROC) (GLenum, GLint, const GLuint *);
typedef void (APIENTRYP PFNGLCLEARBUFFERFVPROC) (GLenum, GLint, const GLfloat *);
typedef void (APIENTRYP PFNGLCLEARBUFFERFIPROC) (GLenum, GLint, GLfloat, GLint);
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLCOPYBUFFERSUBDATAPROC) (GLenum, GLenum, GLintptr, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLGETUNIFORMINDICESPROC) (GLuint, GLsizei, const GLchar *const*, GLuint *);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMSIVPROC) (GLuint, GLsizei, const GLuint *, GLenum, GLint *);
typedef GLuint (APIENTRYP PFNGLGETUNIFORMBLOCKINDEXPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKIVPROC) (GLuint, GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC) (GLuint, GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLUNIFORMBLOCKBINDINGPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLDRAWARRAYSINSTANCEDPROC) (GLenum, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDPROC) (GLenum, GLsizei, GLenum, const void *, GLsizei);
typedef GLsync (APIENTRYP PFNGLFENCESYNCPROC) (GLenum, GLbitfield);
typedef GLboolean (APIENTRYP PFNGLISSYNCPROC) (GLsync);
typedef void (APIENTRYP PFNGLDELETESYNCPROC) (GLsync);
typedef GLenum (APIENTRYP PFNGLCLIENTWAITSYNCPROC) (GLsync, GLbitfield, GLuint64);
typedef void (APIENTRYP PFNGLWAITSYNCPROC) (GLsync, GLbitfield, GLuint64);
typedef void (APIENTRYP PFNGLGETINTEGER64VPROC) (GLenum, GLint64 *);
typedef void (APIENTRYP PFNGLGETSYNCIVPROC) (GLsync, GLenum, GLsizei, GLsizei *, GLint *);
typedef void (APIENTRYP PFNGLGETINTEGER64I_VPROC) (GLenum, GLuint, GLint64 *);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERI64VPROC) (GLenum, GLenum, GLint64 *);
typedef void (APIENTRYP PFNGLGENSAMPLERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLDELETESAMPLERSPROC) (GLsizei, const GLuint *);
typedef GLboolean (APIENTRYP PFNGLISSAMPLERPROC) (GLuint);
typedef void (APIENTRYP PFNGLBINDSAMPLERPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIVPROC) (GLuint, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFPROC) (GLuint, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERFVPROC) (GLuint, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERFVPROC) (GLuint, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBDIVISORPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLBINDTRANSFORMFEEDBACKPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDELETETRANSFORMFEEDBACKSPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENTRANSFORMFEEDBACKSPROC) (GLsizei, GLuint *);
typedef GLboolean (APIENTRYP PFNGLISTRANSFORMFEEDBACKPROC) (GLuint);
typedef void (APIENTRYP PFNGLPAUSETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLRESUMETRANSFORMFEEDBACKPROC) (void);
typedef void (APIENTRYP PFNGLGETPROGRAMBINARYPROC) (GLuint, GLsizei, GLsizei *, GLenum *, void *);
typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint, GLenum, const void *, GLsizei);
typedef void (APIENTRYP PFNGLPROGRAMPARAMETERIPROC) (GLuint, GLenum, GLint);
typedef void (APIENTRYP PFNGLINVALIDATEFRAMEBUFFERPROC) (GLenum, GLsizei, const GLenum *);
typedef void (APIENTRYP PFNGLINVALIDATESUBFRAMEBUFFERPROC) (GLenum, GLsizei, const GLenum *, GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLGETINTERNALFORMATIVPROC) (GLenum, GLenum, GLenum, GLsizei, GLint *);

# endif /* GL_ES_VERSION_3_0 */
# if defined GL_ES_VERSION_3_1

typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEPROC) (GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLDISPATCHCOMPUTEINDIRECTPROC) (GLintptr);
typedef void (APIENTRYP PFNGLDRAWARRAYSINDIRECTPROC) (GLenum, const void *);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINDIRECTPROC) (GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLFRAMEBUFFERPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETPROGRAMINTERFACEIVPROC) (GLuint, GLenum, GLenum, GLint *);
typedef GLuint (APIENTRYP PFNGLGETPROGRAMRESOURCEINDEXPROC) (GLuint, GLenum, const GLchar *);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCENAMEPROC) (GLuint, GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLGETPROGRAMRESOURCEIVPROC) (GLuint, GLenum, GLuint, GLsizei, const GLenum *, GLsizei, GLsizei *, GLint *);
typedef GLint (APIENTRYP PFNGLGETPROGRAMRESOURCELOCATIONPROC) (GLuint, GLenum, const GLchar *);
typedef void (APIENTRYP PFNGLUSEPROGRAMSTAGESPROC) (GLuint, GLbitfield, GLuint);
typedef void (APIENTRYP PFNGLACTIVESHADERPROGRAMPROC) (GLuint, GLuint);
typedef GLuint (APIENTRYP PFNGLCREATESHADERPROGRAMVPROC) (GLenum, GLsizei, const GLchar *const*);
typedef void (APIENTRYP PFNGLBINDPROGRAMPIPELINEPROC) (GLuint);
typedef void (APIENTRYP PFNGLDELETEPROGRAMPIPELINESPROC) (GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLGENPROGRAMPIPELINESPROC) (GLsizei, GLuint *);
typedef GLboolean (APIENTRYP PFNGLISPROGRAMPIPELINEPROC) (GLuint);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IPROC) (GLuint, GLint, GLint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IPROC) (GLuint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IPROC) (GLuint, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IPROC) (GLuint, GLint, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIPROC) (GLuint, GLint, GLuint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIPROC) (GLuint, GLint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIPROC) (GLuint, GLint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIPROC) (GLuint, GLint, GLuint, GLuint, GLuint, GLuint);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FPROC) (GLuint, GLint, GLfloat);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FPROC) (GLuint, GLint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FPROC) (GLuint, GLint, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FPROC) (GLuint, GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1IVPROC) (GLuint, GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2IVPROC) (GLuint, GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3IVPROC) (GLuint, GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4IVPROC) (GLuint, GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1UIVPROC) (GLuint, GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2UIVPROC) (GLuint, GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3UIVPROC) (GLuint, GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4UIVPROC) (GLuint, GLint, GLsizei, const GLuint *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM1FVPROC) (GLuint, GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM2FVPROC) (GLuint, GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM3FVPROC) (GLuint, GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORM4FVPROC) (GLuint, GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC) (GLuint, GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLVALIDATEPROGRAMPIPELINEPROC) (GLuint);
typedef void (APIENTRYP PFNGLGETPROGRAMPIPELINEINFOLOGPROC) (GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLBINDIMAGETEXTUREPROC) (GLuint, GLuint, GLint, GLboolean, GLint, GLenum, GLenum);
typedef void (APIENTRYP PFNGLGETBOOLEANI_VPROC) (GLenum, GLuint, GLboolean *);
typedef void (APIENTRYP PFNGLMEMORYBARRIERPROC) (GLbitfield);
typedef void (APIENTRYP PFNGLMEMORYBARRIERBYREGIONPROC) (GLbitfield);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLboolean);
typedef void (APIENTRYP PFNGLGETMULTISAMPLEFVPROC) (GLenum, GLuint, GLfloat *);
typedef void (APIENTRYP PFNGLSAMPLEMASKIPROC) (GLuint, GLbitfield);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERIVPROC) (GLenum, GLint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTEXLEVELPARAMETERFVPROC) (GLenum, GLint, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLBINDVERTEXBUFFERPROC) (GLuint, GLuint, GLintptr, GLsizei);
typedef void (APIENTRYP PFNGLVERTEXATTRIBFORMATPROC) (GLuint, GLint, GLenum, GLboolean, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBIFORMATPROC) (GLuint, GLint, GLenum, GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIBBINDINGPROC) (GLuint, GLuint);
typedef void (APIENTRYP PFNGLVERTEXBINDINGDIVISORPROC) (GLuint, GLuint);

# endif /* GL_ES_VERSION_3_1 */
# if defined GL_ES_VERSION_3_2

typedef void (APIENTRYP PFNGLBLENDBARRIERPROC) (void);
typedef void (APIENTRYP PFNGLCOPYIMAGESUBDATAPROC) (GLuint, GLenum, GLint, GLint, GLint, GLint, GLuint, GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECONTROLPROC) (GLenum, GLenum, GLenum, GLsizei, const GLuint *, GLboolean);
typedef void (APIENTRYP PFNGLDEBUGMESSAGEINSERTPROC) (GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *);
typedef void (APIENTRYP PFNGLDEBUGMESSAGECALLBACKPROC) (GLDEBUGPROC, const void *);
typedef GLuint (APIENTRYP PFNGLGETDEBUGMESSAGELOGPROC) (GLuint, GLsizei, GLenum *, GLenum *, GLuint *, GLenum *, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLPUSHDEBUGGROUPPROC) (GLenum, GLuint, GLsizei, const GLchar *);
typedef void (APIENTRYP PFNGLPOPDEBUGGROUPPROC) (void);
typedef void (APIENTRYP PFNGLOBJECTLABELPROC) (GLenum, GLuint, GLsizei, const GLchar *);
typedef void (APIENTRYP PFNGLGETOBJECTLABELPROC) (GLenum, GLuint, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLOBJECTPTRLABELPROC) (const void *, GLsizei, const GLchar *);
typedef void (APIENTRYP PFNGLGETOBJECTPTRLABELPROC) (const void *, GLsizei, GLsizei *, GLchar *);
typedef void (APIENTRYP PFNGLGETPOINTERVPROC) (GLenum, void **);
typedef void (APIENTRYP PFNGLENABLEIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDISABLEIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBLENDEQUATIONIPROC) (GLuint, GLenum);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEIPROC) (GLuint, GLenum, GLenum);
typedef void (APIENTRYP PFNGLBLENDFUNCIPROC) (GLuint, GLenum, GLenum);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEIPROC) (GLuint, GLenum, GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLCOLORMASKIPROC) (GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
typedef GLboolean (APIENTRYP PFNGLISENABLEDIPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLDRAWELEMENTSBASEVERTEXPROC) (GLenum, GLsizei, GLenum, const void *, GLint);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC) (GLenum, GLuint, GLuint, GLsizei, GLenum, const void *, GLint);
typedef void (APIENTRYP PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC) (GLenum, GLsizei, GLenum, const void *, GLsizei, GLint);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTUREPROC) (GLenum, GLenum, GLuint, GLint);
typedef void (APIENTRYP PFNGLPRIMITIVEBOUNDINGBOXPROC) (GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
typedef GLenum (APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (void);
typedef void (APIENTRYP PFNGLREADNPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint, GLint, GLsizei, GLfloat *);
typedef void (APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint, GLint, GLsizei, GLint *);
typedef void (APIENTRYP PFNGLGETNUNIFORMUIVPROC) (GLuint, GLint, GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLMINSAMPLESHADINGPROC) (GLfloat);
typedef void (APIENTRYP PFNGLPATCHPARAMETERIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLTEXPARAMETERIIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLTEXPARAMETERIUIVPROC) (GLenum, GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC) (GLenum, GLenum, GLuint *);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIIVPROC) (GLuint, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLSAMPLERPARAMETERIUIVPROC) (GLuint, GLenum, const GLuint *);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETSAMPLERPARAMETERIUIVPROC) (GLuint, GLenum, GLuint *);
typedef void (APIENTRYP PFNGLTEXBUFFERPROC) (GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLTEXBUFFERRANGEPROC) (GLenum, GLenum, GLuint, GLintptr, GLsizeiptr);
typedef void (APIENTRYP PFNGLTEXSTORAGE3DMULTISAMPLEPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei, GLsizei, GLboolean);

# endif /* GL_ES_VERSION_3_2 */
# if defined GL_SC_VERSION_2_0

typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum);
typedef void (APIENTRYP PFNGLBINDBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBINDFRAMEBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBINDRENDERBUFFERPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBINDTEXTUREPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLBLENDCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLBLENDEQUATIONPROC) (GLenum);
typedef void (APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLBLENDFUNCPROC) (GLenum, GLenum);
typedef void (APIENTRYP PFNGLBLENDFUNCSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLBUFFERDATAPROC) (GLenum, GLsizeiptr, const void *, GLenum);
typedef void (APIENTRYP PFNGLBUFFERSUBDATAPROC) (GLenum, GLintptr, GLsizeiptr, const void *);
typedef GLenum (APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC) (GLenum);
typedef void (APIENTRYP PFNGLCLEARPROC) (GLbitfield);
typedef void (APIENTRYP PFNGLCLEARCOLORPROC) (GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLCLEARDEPTHFPROC) (GLfloat);
typedef void (APIENTRYP PFNGLCLEARSTENCILPROC) (GLint);
typedef void (APIENTRYP PFNGLCOLORMASKPROC) (GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const void *);
typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC) (void);
typedef void (APIENTRYP PFNGLCULLFACEPROC) (GLenum);
typedef void (APIENTRYP PFNGLDEPTHFUNCPROC) (GLenum);
typedef void (APIENTRYP PFNGLDEPTHMASKPROC) (GLboolean);
typedef void (APIENTRYP PFNGLDEPTHRANGEFPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLDISABLEPROC) (GLenum);
typedef void (APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (APIENTRYP PFNGLDRAWARRAYSPROC) (GLenum, GLint, GLsizei);
typedef void (APIENTRYP PFNGLDRAWRANGEELEMENTSPROC) (GLenum, GLuint, GLuint, GLsizei, GLenum, const void *);
typedef void (APIENTRYP PFNGLENABLEPROC) (GLenum);
typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint);
typedef void (APIENTRYP PFNGLFINISHPROC) (void);
typedef void (APIENTRYP PFNGLFLUSHPROC) (void);
typedef void (APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC) (GLenum, GLenum, GLenum, GLuint);
typedef void (APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (APIENTRYP PFNGLFRONTFACEPROC) (GLenum);
typedef void (APIENTRYP PFNGLGENBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGENERATEMIPMAPPROC) (GLenum);
typedef void (APIENTRYP PFNGLGENFRAMEBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGENRENDERBUFFERSPROC) (GLsizei, GLuint *);
typedef void (APIENTRYP PFNGLGENTEXTURESPROC) (GLsizei, GLuint *);
typedef GLint (APIENTRYP PFNGLGETATTRIBLOCATIONPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLGETBOOLEANVPROC) (GLenum, GLboolean *);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef GLenum (APIENTRYP PFNGLGETERRORPROC) (void);
typedef void (APIENTRYP PFNGLGETFLOATVPROC) (GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC) (GLenum, GLenum, GLenum, GLint *);
typedef GLenum (APIENTRYP PFNGLGETGRAPHICSRESETSTATUSPROC) (void);
typedef void (APIENTRYP PFNGLGETINTEGERVPROC) (GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC) (GLenum);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERFVPROC) (GLenum, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETTEXPARAMETERIVPROC) (GLenum, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETNUNIFORMFVPROC) (GLuint, GLint, GLsizei, GLfloat *);
typedef void (APIENTRYP PFNGLGETNUNIFORMIVPROC) (GLuint, GLint, GLsizei, GLint *);
typedef GLint (APIENTRYP PFNGLGETUNIFORMLOCATIONPROC) (GLuint, const GLchar *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBFVPROC) (GLuint, GLenum, GLfloat *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBIVPROC) (GLuint, GLenum, GLint *);
typedef void (APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC) (GLuint, GLenum, void **);
typedef void (APIENTRYP PFNGLHINTPROC) (GLenum, GLenum);
typedef GLboolean (APIENTRYP PFNGLISENABLEDPROC) (GLenum);
typedef void (APIENTRYP PFNGLLINEWIDTHPROC) (GLfloat);
typedef void (APIENTRYP PFNGLPIXELSTOREIPROC) (GLenum, GLint);
typedef void (APIENTRYP PFNGLPOLYGONOFFSETPROC) (GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLPROGRAMBINARYPROC) (GLuint, GLenum, const void *, GLsizei);
typedef void (APIENTRYP PFNGLREADNPIXELSPROC) (GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLsizei, void *);
typedef void (APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC) (GLenum, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEPROC) (GLfloat, GLboolean);
typedef void (APIENTRYP PFNGLSCISSORPROC) (GLint, GLint, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLSTENCILFUNCPROC) (GLenum, GLint, GLuint);
typedef void (APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC) (GLenum, GLenum, GLint, GLuint);
typedef void (APIENTRYP PFNGLSTENCILMASKPROC) (GLuint);
typedef void (APIENTRYP PFNGLSTENCILMASKSEPARATEPROC) (GLenum, GLuint);
typedef void (APIENTRYP PFNGLSTENCILOPPROC) (GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLSTENCILOPSEPARATEPROC) (GLenum, GLenum, GLenum, GLenum);
typedef void (APIENTRYP PFNGLTEXSTORAGE2DPROC) (GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (APIENTRYP PFNGLTEXPARAMETERFPROC) (GLenum, GLenum, GLfloat);
typedef void (APIENTRYP PFNGLTEXPARAMETERFVPROC) (GLenum, GLenum, const GLfloat *);
typedef void (APIENTRYP PFNGLTEXPARAMETERIPROC) (GLenum, GLenum, GLint);
typedef void (APIENTRYP PFNGLTEXPARAMETERIVPROC) (GLenum, GLenum, const GLint *);
typedef void (APIENTRYP PFNGLTEXSUBIMAGE2DPROC) (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const void *);
typedef void (APIENTRYP PFNGLUNIFORM1FPROC) (GLint, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM1FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM1IPROC) (GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM1IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORM2FPROC) (GLint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM2FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM2IPROC) (GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM2IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORM3FPROC) (GLint, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM3FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM3IPROC) (GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM3IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORM4FPROC) (GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLUNIFORM4FVPROC) (GLint, GLsizei, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORM4IPROC) (GLint, GLint, GLint, GLint, GLint);
typedef void (APIENTRYP PFNGLUNIFORM4IVPROC) (GLint, GLsizei, const GLint *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX2FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX3FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUNIFORMMATRIX4FVPROC) (GLint, GLsizei, GLboolean, const GLfloat *);
typedef void (APIENTRYP PFNGLUSEPROGRAMPROC) (GLuint);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FPROC) (GLuint, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB1FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FPROC) (GLuint, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB2FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FPROC) (GLuint, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB3FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FPROC) (GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (APIENTRYP PFNGLVERTEXATTRIB4FVPROC) (GLuint, const GLfloat *);
typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC) (GLuint, GLint, GLenum, GLboolean, GLsizei, const void *);
typedef void (APIENTRYP PFNGLVIEWPORTPROC) (GLint, GLint, GLsizei, GLsizei);

# endif /* GL_SC_VERSION_2_0 */
# if defined GL_VERSION_1_0

extern PFNGLCULLFACEPROC gload_glCullFace;
extern PFNGLFRONTFACEPROC gload_glFrontFace;
extern PFNGLHINTPROC gload_glHint;
extern PFNGLLINEWIDTHPROC gload_glLineWidth;
extern PFNGLPOINTSIZEPROC gload_glPointSize;
extern PFNGLPOLYGONMODEPROC gload_glPolygonMode;
extern PFNGLSCISSORPROC gload_glScissor;
extern PFNGLTEXPARAMETERFPROC gload_glTexParameterf;
extern PFNGLTEXPARAMETERFVPROC gload_glTexParameterfv;
extern PFNGLTEXPARAMETERIPROC gload_glTexParameteri;
extern PFNGLTEXPARAMETERIVPROC gload_glTexParameteriv;
extern PFNGLTEXIMAGE1DPROC gload_glTexImage1D;
extern PFNGLTEXIMAGE2DPROC gload_glTexImage2D;
extern PFNGLDRAWBUFFERPROC gload_glDrawBuffer;
extern PFNGLCLEARPROC gload_glClear;
extern PFNGLCLEARCOLORPROC gload_glClearColor;
extern PFNGLCLEARSTENCILPROC gload_glClearStencil;
extern PFNGLCLEARDEPTHPROC gload_glClearDepth;
extern PFNGLSTENCILMASKPROC gload_glStencilMask;
extern PFNGLCOLORMASKPROC gload_glColorMask;
extern PFNGLDEPTHMASKPROC gload_glDepthMask;
extern PFNGLDISABLEPROC gload_glDisable;
extern PFNGLENABLEPROC gload_glEnable;
extern PFNGLFINISHPROC gload_glFinish;
extern PFNGLFLUSHPROC gload_glFlush;
extern PFNGLBLENDFUNCPROC gload_glBlendFunc;
extern PFNGLLOGICOPPROC gload_glLogicOp;
extern PFNGLSTENCILFUNCPROC gload_glStencilFunc;
extern PFNGLSTENCILOPPROC gload_glStencilOp;
extern PFNGLDEPTHFUNCPROC gload_glDepthFunc;
extern PFNGLPIXELSTOREFPROC gload_glPixelStoref;
extern PFNGLPIXELSTOREIPROC gload_glPixelStorei;
extern PFNGLREADBUFFERPROC gload_glReadBuffer;
extern PFNGLREADPIXELSPROC gload_glReadPixels;
extern PFNGLGETBOOLEANVPROC gload_glGetBooleanv;
extern PFNGLGETDOUBLEVPROC gload_glGetDoublev;
extern PFNGLGETERRORPROC gload_glGetError;
extern PFNGLGETFLOATVPROC gload_glGetFloatv;
extern PFNGLGETINTEGERVPROC gload_glGetIntegerv;
extern PFNGLGETSTRINGPROC gload_glGetString;
extern PFNGLGETTEXIMAGEPROC gload_glGetTexImage;
extern PFNGLGETTEXPARAMETERFVPROC gload_glGetTexParameterfv;
extern PFNGLGETTEXPARAMETERIVPROC gload_glGetTexParameteriv;
extern PFNGLGETTEXLEVELPARAMETERFVPROC gload_glGetTexLevelParameterfv;
extern PFNGLGETTEXLEVELPARAMETERIVPROC gload_glGetTexLevelParameteriv;
extern PFNGLISENABLEDPROC gload_glIsEnabled;
extern PFNGLDEPTHRANGEPROC gload_glDepthRange;
extern PFNGLVIEWPORTPROC gload_glViewport;
extern PFNGLNEWLISTPROC gload_glNewList;
extern PFNGLENDLISTPROC gload_glEndList;
extern PFNGLCALLLISTPROC gload_glCallList;
extern PFNGLCALLLISTSPROC gload_glCallLists;
extern PFNGLDELETELISTSPROC gload_glDeleteLists;
extern PFNGLGENLISTSPROC gload_glGenLists;
extern PFNGLLISTBASEPROC gload_glListBase;
extern PFNGLBEGINPROC gload_glBegin;
extern PFNGLBITMAPPROC gload_glBitmap;
extern PFNGLCOLOR3BPROC gload_glColor3b;
extern PFNGLCOLOR3BVPROC gload_glColor3bv;
extern PFNGLCOLOR3DPROC gload_glColor3d;
extern PFNGLCOLOR3DVPROC gload_glColor3dv;
extern PFNGLCOLOR3FPROC gload_glColor3f;
extern PFNGLCOLOR3FVPROC gload_glColor3fv;
extern PFNGLCOLOR3IPROC gload_glColor3i;
extern PFNGLCOLOR3IVPROC gload_glColor3iv;
extern PFNGLCOLOR3SPROC gload_glColor3s;
extern PFNGLCOLOR3SVPROC gload_glColor3sv;
extern PFNGLCOLOR3UBPROC gload_glColor3ub;
extern PFNGLCOLOR3UBVPROC gload_glColor3ubv;
extern PFNGLCOLOR3UIPROC gload_glColor3ui;
extern PFNGLCOLOR3UIVPROC gload_glColor3uiv;
extern PFNGLCOLOR3USPROC gload_glColor3us;
extern PFNGLCOLOR3USVPROC gload_glColor3usv;
extern PFNGLCOLOR4BPROC gload_glColor4b;
extern PFNGLCOLOR4BVPROC gload_glColor4bv;
extern PFNGLCOLOR4DPROC gload_glColor4d;
extern PFNGLCOLOR4DVPROC gload_glColor4dv;
extern PFNGLCOLOR4FPROC gload_glColor4f;
extern PFNGLCOLOR4FVPROC gload_glColor4fv;
extern PFNGLCOLOR4IPROC gload_glColor4i;
extern PFNGLCOLOR4IVPROC gload_glColor4iv;
extern PFNGLCOLOR4SPROC gload_glColor4s;
extern PFNGLCOLOR4SVPROC gload_glColor4sv;
extern PFNGLCOLOR4UBPROC gload_glColor4ub;
extern PFNGLCOLOR4UBVPROC gload_glColor4ubv;
extern PFNGLCOLOR4UIPROC gload_glColor4ui;
extern PFNGLCOLOR4UIVPROC gload_glColor4uiv;
extern PFNGLCOLOR4USPROC gload_glColor4us;
extern PFNGLCOLOR4USVPROC gload_glColor4usv;
extern PFNGLEDGEFLAGPROC gload_glEdgeFlag;
extern PFNGLEDGEFLAGVPROC gload_glEdgeFlagv;
extern PFNGLENDPROC gload_glEnd;
extern PFNGLINDEXDPROC gload_glIndexd;
extern PFNGLINDEXDVPROC gload_glIndexdv;
extern PFNGLINDEXFPROC gload_glIndexf;
extern PFNGLINDEXFVPROC gload_glIndexfv;
extern PFNGLINDEXIPROC gload_glIndexi;
extern PFNGLINDEXIVPROC gload_glIndexiv;
extern PFNGLINDEXSPROC gload_glIndexs;
extern PFNGLINDEXSVPROC gload_glIndexsv;
extern PFNGLNORMAL3BPROC gload_glNormal3b;
extern PFNGLNORMAL3BVPROC gload_glNormal3bv;
extern PFNGLNORMAL3DPROC gload_glNormal3d;
extern PFNGLNORMAL3DVPROC gload_glNormal3dv;
extern PFNGLNORMAL3FPROC gload_glNormal3f;
extern PFNGLNORMAL3FVPROC gload_glNormal3fv;
extern PFNGLNORMAL3IPROC gload_glNormal3i;
extern PFNGLNORMAL3IVPROC gload_glNormal3iv;
extern PFNGLNORMAL3SPROC gload_glNormal3s;
extern PFNGLNORMAL3SVPROC gload_glNormal3sv;
extern PFNGLRASTERPOS2DPROC gload_glRasterPos2d;
extern PFNGLRASTERPOS2DVPROC gload_glRasterPos2dv;
extern PFNGLRASTERPOS2FPROC gload_glRasterPos2f;
extern PFNGLRASTERPOS2FVPROC gload_glRasterPos2fv;
extern PFNGLRASTERPOS2IPROC gload_glRasterPos2i;
extern PFNGLRASTERPOS2IVPROC gload_glRasterPos2iv;
extern PFNGLRASTERPOS2SPROC gload_glRasterPos2s;
extern PFNGLRASTERPOS2SVPROC gload_glRasterPos2sv;
extern PFNGLRASTERPOS3DPROC gload_glRasterPos3d;
extern PFNGLRASTERPOS3DVPROC gload_glRasterPos3dv;
extern PFNGLRASTERPOS3FPROC gload_glRasterPos3f;
extern PFNGLRASTERPOS3FVPROC gload_glRasterPos3fv;
extern PFNGLRASTERPOS3IPROC gload_glRasterPos3i;
extern PFNGLRASTERPOS3IVPROC gload_glRasterPos3iv;
extern PFNGLRASTERPOS3SPROC gload_glRasterPos3s;
extern PFNGLRASTERPOS3SVPROC gload_glRasterPos3sv;
extern PFNGLRASTERPOS4DPROC gload_glRasterPos4d;
extern PFNGLRASTERPOS4DVPROC gload_glRasterPos4dv;
extern PFNGLRASTERPOS4FPROC gload_glRasterPos4f;
extern PFNGLRASTERPOS4FVPROC gload_glRasterPos4fv;
extern PFNGLRASTERPOS4IPROC gload_glRasterPos4i;
extern PFNGLRASTERPOS4IVPROC gload_glRasterPos4iv;
extern PFNGLRASTERPOS4SPROC gload_glRasterPos4s;
extern PFNGLRASTERPOS4SVPROC gload_glRasterPos4sv;
extern PFNGLRECTDPROC gload_glRectd;
extern PFNGLRECTDVPROC gload_glRectdv;
extern PFNGLRECTFPROC gload_glRectf;
extern PFNGLRECTFVPROC gload_glRectfv;
extern PFNGLRECTIPROC gload_glRecti;
extern PFNGLRECTIVPROC gload_glRectiv;
extern PFNGLRECTSPROC gload_glRects;
extern PFNGLRECTSVPROC gload_glRectsv;
extern PFNGLTEXCOORD1DPROC gload_glTexCoord1d;
extern PFNGLTEXCOORD1DVPROC gload_glTexCoord1dv;
extern PFNGLTEXCOORD1FPROC gload_glTexCoord1f;
extern PFNGLTEXCOORD1FVPROC gload_glTexCoord1fv;
extern PFNGLTEXCOORD1IPROC gload_glTexCoord1i;
extern PFNGLTEXCOORD1IVPROC gload_glTexCoord1iv;
extern PFNGLTEXCOORD1SPROC gload_glTexCoord1s;
extern PFNGLTEXCOORD1SVPROC gload_glTexCoord1sv;
extern PFNGLTEXCOORD2DPROC gload_glTexCoord2d;
extern PFNGLTEXCOORD2DVPROC gload_glTexCoord2dv;
extern PFNGLTEXCOORD2FPROC gload_glTexCoord2f;
extern PFNGLTEXCOORD2FVPROC gload_glTexCoord2fv;
extern PFNGLTEXCOORD2IPROC gload_glTexCoord2i;
extern PFNGLTEXCOORD2IVPROC gload_glTexCoord2iv;
extern PFNGLTEXCOORD2SPROC gload_glTexCoord2s;
extern PFNGLTEXCOORD2SVPROC gload_glTexCoord2sv;
extern PFNGLTEXCOORD3DPROC gload_glTexCoord3d;
extern PFNGLTEXCOORD3DVPROC gload_glTexCoord3dv;
extern PFNGLTEXCOORD3FPROC gload_glTexCoord3f;
extern PFNGLTEXCOORD3FVPROC gload_glTexCoord3fv;
extern PFNGLTEXCOORD3IPROC gload_glTexCoord3i;
extern PFNGLTEXCOORD3IVPROC gload_glTexCoord3iv;
extern PFNGLTEXCOORD3SPROC gload_glTexCoord3s;
extern PFNGLTEXCOORD3SVPROC gload_glTexCoord3sv;
extern PFNGLTEXCOORD4DPROC gload_glTexCoord4d;
extern PFNGLTEXCOORD4DVPROC gload_glTexCoord4dv;
extern PFNGLTEXCOORD4FPROC gload_glTexCoord4f;
extern PFNGLTEXCOORD4FVPROC gload_glTexCoord4fv;
extern PFNGLTEXCOORD4IPROC gload_glTexCoord4i;
extern PFNGLTEXCOORD4IVPROC gload_glTexCoord4iv;
extern PFNGLTEXCOORD4SPROC gload_glTexCoord4s;
extern PFNGLTEXCOORD4SVPROC gload_glTexCoord4sv;
extern PFNGLVERTEX2DPROC gload_glVertex2d;
extern PFNGLVERTEX2DVPROC gload_glVertex2dv;
extern PFNGLVERTEX2FPROC gload_glVertex2f;
extern PFNGLVERTEX2FVPROC gload_glVertex2fv;
extern PFNGLVERTEX2IPROC gload_glVertex2i;
extern PFNGLVERTEX2IVPROC gload_glVertex2iv;
extern PFNGLVERTEX2SPROC gload_glVertex2s;
extern PFNGLVERTEX2SVPROC gload_glVertex2sv;
extern PFNGLVERTEX3DPROC gload_glVertex3d;
extern PFNGLVERTEX3DVPROC gload_glVertex3dv;
extern PFNGLVERTEX3FPROC gload_glVertex3f;
extern PFNGLVERTEX3FVPROC gload_glVertex3fv;
extern PFNGLVERTEX3IPROC gload_glVertex3i;
extern PFNGLVERTEX3IVPROC gload_glVertex3iv;
extern PFNGLVERTEX3SPROC gload_glVertex3s;
extern PFNGLVERTEX3SVPROC gload_glVertex3sv;
extern PFNGLVERTEX4DPROC gload_glVertex4d;
extern PFNGLVERTEX4DVPROC gload_glVertex4dv;
extern PFNGLVERTEX4FPROC gload_glVertex4f;
extern PFNGLVERTEX4FVPROC gload_glVertex4fv;
extern PFNGLVERTEX4IPROC gload_glVertex4i;
extern PFNGLVERTEX4IVPROC gload_glVertex4iv;
extern PFNGLVERTEX4SPROC gload_glVertex4s;
extern PFNGLVERTEX4SVPROC gload_glVertex4sv;
extern PFNGLCLIPPLANEPROC gload_glClipPlane;
extern PFNGLCOLORMATERIALPROC gload_glColorMaterial;
extern PFNGLFOGFPROC gload_glFogf;
extern PFNGLFOGFVPROC gload_glFogfv;
extern PFNGLFOGIPROC gload_glFogi;
extern PFNGLFOGIVPROC gload_glFogiv;
extern PFNGLLIGHTFPROC gload_glLightf;
extern PFNGLLIGHTFVPROC gload_glLightfv;
extern PFNGLLIGHTIPROC gload_glLighti;
extern PFNGLLIGHTIVPROC gload_glLightiv;
extern PFNGLLIGHTMODELFPROC gload_glLightModelf;
extern PFNGLLIGHTMODELFVPROC gload_glLightModelfv;
extern PFNGLLIGHTMODELIPROC gload_glLightModeli;
extern PFNGLLIGHTMODELIVPROC gload_glLightModeliv;
extern PFNGLLINESTIPPLEPROC gload_glLineStipple;
extern PFNGLMATERIALFPROC gload_glMaterialf;
extern PFNGLMATERIALFVPROC gload_glMaterialfv;
extern PFNGLMATERIALIPROC gload_glMateriali;
extern PFNGLMATERIALIVPROC gload_glMaterialiv;
extern PFNGLPOLYGONSTIPPLEPROC gload_glPolygonStipple;
extern PFNGLSHADEMODELPROC gload_glShadeModel;
extern PFNGLTEXENVFPROC gload_glTexEnvf;
extern PFNGLTEXENVFVPROC gload_glTexEnvfv;
extern PFNGLTEXENVIPROC gload_glTexEnvi;
extern PFNGLTEXENVIVPROC gload_glTexEnviv;
extern PFNGLTEXGENDPROC gload_glTexGend;
extern PFNGLTEXGENDVPROC gload_glTexGendv;
extern PFNGLTEXGENFPROC gload_glTexGenf;
extern PFNGLTEXGENFVPROC gload_glTexGenfv;
extern PFNGLTEXGENIPROC gload_glTexGeni;
extern PFNGLTEXGENIVPROC gload_glTexGeniv;
extern PFNGLFEEDBACKBUFFERPROC gload_glFeedbackBuffer;
extern PFNGLSELECTBUFFERPROC gload_glSelectBuffer;
extern PFNGLRENDERMODEPROC gload_glRenderMode;
extern PFNGLINITNAMESPROC gload_glInitNames;
extern PFNGLLOADNAMEPROC gload_glLoadName;
extern PFNGLPASSTHROUGHPROC gload_glPassThrough;
extern PFNGLPOPNAMEPROC gload_glPopName;
extern PFNGLPUSHNAMEPROC gload_glPushName;
extern PFNGLCLEARACCUMPROC gload_glClearAccum;
extern PFNGLCLEARINDEXPROC gload_glClearIndex;
extern PFNGLINDEXMASKPROC gload_glIndexMask;
extern PFNGLACCUMPROC gload_glAccum;
extern PFNGLPOPATTRIBPROC gload_glPopAttrib;
extern PFNGLPUSHATTRIBPROC gload_glPushAttrib;
extern PFNGLMAP1DPROC gload_glMap1d;
extern PFNGLMAP1FPROC gload_glMap1f;
extern PFNGLMAP2DPROC gload_glMap2d;
extern PFNGLMAP2FPROC gload_glMap2f;
extern PFNGLMAPGRID1DPROC gload_glMapGrid1d;
extern PFNGLMAPGRID1FPROC gload_glMapGrid1f;
extern PFNGLMAPGRID2DPROC gload_glMapGrid2d;
extern PFNGLMAPGRID2FPROC gload_glMapGrid2f;
extern PFNGLEVALCOORD1DPROC gload_glEvalCoord1d;
extern PFNGLEVALCOORD1DVPROC gload_glEvalCoord1dv;
extern PFNGLEVALCOORD1FPROC gload_glEvalCoord1f;
extern PFNGLEVALCOORD1FVPROC gload_glEvalCoord1fv;
extern PFNGLEVALCOORD2DPROC gload_glEvalCoord2d;
extern PFNGLEVALCOORD2DVPROC gload_glEvalCoord2dv;
extern PFNGLEVALCOORD2FPROC gload_glEvalCoord2f;
extern PFNGLEVALCOORD2FVPROC gload_glEvalCoord2fv;
extern PFNGLEVALMESH1PROC gload_glEvalMesh1;
extern PFNGLEVALPOINT1PROC gload_glEvalPoint1;
extern PFNGLEVALMESH2PROC gload_glEvalMesh2;
extern PFNGLEVALPOINT2PROC gload_glEvalPoint2;
extern PFNGLALPHAFUNCPROC gload_glAlphaFunc;
extern PFNGLPIXELZOOMPROC gload_glPixelZoom;
extern PFNGLPIXELTRANSFERFPROC gload_glPixelTransferf;
extern PFNGLPIXELTRANSFERIPROC gload_glPixelTransferi;
extern PFNGLPIXELMAPFVPROC gload_glPixelMapfv;
extern PFNGLPIXELMAPUIVPROC gload_glPixelMapuiv;
extern PFNGLPIXELMAPUSVPROC gload_glPixelMapusv;
extern PFNGLCOPYPIXELSPROC gload_glCopyPixels;
extern PFNGLDRAWPIXELSPROC gload_glDrawPixels;
extern PFNGLGETCLIPPLANEPROC gload_glGetClipPlane;
extern PFNGLGETLIGHTFVPROC gload_glGetLightfv;
extern PFNGLGETLIGHTIVPROC gload_glGetLightiv;
extern PFNGLGETMAPDVPROC gload_glGetMapdv;
extern PFNGLGETMAPFVPROC gload_glGetMapfv;
extern PFNGLGETMAPIVPROC gload_glGetMapiv;
extern PFNGLGETMATERIALFVPROC gload_glGetMaterialfv;
extern PFNGLGETMATERIALIVPROC gload_glGetMaterialiv;
extern PFNGLGETPIXELMAPFVPROC gload_glGetPixelMapfv;
extern PFNGLGETPIXELMAPUIVPROC gload_glGetPixelMapuiv;
extern PFNGLGETPIXELMAPUSVPROC gload_glGetPixelMapusv;
extern PFNGLGETPOLYGONSTIPPLEPROC gload_glGetPolygonStipple;
extern PFNGLGETTEXENVFVPROC gload_glGetTexEnvfv;
extern PFNGLGETTEXENVIVPROC gload_glGetTexEnviv;
extern PFNGLGETTEXGENDVPROC gload_glGetTexGendv;
extern PFNGLGETTEXGENFVPROC gload_glGetTexGenfv;
extern PFNGLGETTEXGENIVPROC gload_glGetTexGeniv;
extern PFNGLISLISTPROC gload_glIsList;
extern PFNGLFRUSTUMPROC gload_glFrustum;
extern PFNGLLOADIDENTITYPROC gload_glLoadIdentity;
extern PFNGLLOADMATRIXFPROC gload_glLoadMatrixf;
extern PFNGLLOADMATRIXDPROC gload_glLoadMatrixd;
extern PFNGLMATRIXMODEPROC gload_glMatrixMode;
extern PFNGLMULTMATRIXFPROC gload_glMultMatrixf;
extern PFNGLMULTMATRIXDPROC gload_glMultMatrixd;
extern PFNGLORTHOPROC gload_glOrtho;
extern PFNGLPOPMATRIXPROC gload_glPopMatrix;
extern PFNGLPUSHMATRIXPROC gload_glPushMatrix;
extern PFNGLROTATEDPROC gload_glRotated;
extern PFNGLROTATEFPROC gload_glRotatef;
extern PFNGLSCALEDPROC gload_glScaled;
extern PFNGLSCALEFPROC gload_glScalef;
extern PFNGLTRANSLATEDPROC gload_glTranslated;
extern PFNGLTRANSLATEFPROC gload_glTranslatef;

# endif /* GL_VERSION_1_0 */
# if defined GL_VERSION_1_1

extern PFNGLDRAWARRAYSPROC gload_glDrawArrays;
extern PFNGLDRAWELEMENTSPROC gload_glDrawElements;
extern PFNGLGETPOINTERVPROC gload_glGetPointerv;
extern PFNGLPOLYGONOFFSETPROC gload_glPolygonOffset;
extern PFNGLCOPYTEXIMAGE1DPROC gload_glCopyTexImage1D;
extern PFNGLCOPYTEXIMAGE2DPROC gload_glCopyTexImage2D;
extern PFNGLCOPYTEXSUBIMAGE1DPROC gload_glCopyTexSubImage1D;
extern PFNGLCOPYTEXSUBIMAGE2DPROC gload_glCopyTexSubImage2D;
extern PFNGLTEXSUBIMAGE1DPROC gload_glTexSubImage1D;
extern PFNGLTEXSUBIMAGE2DPROC gload_glTexSubImage2D;
extern PFNGLBINDTEXTUREPROC gload_glBindTexture;
extern PFNGLDELETETEXTURESPROC gload_glDeleteTextures;
extern PFNGLGENTEXTURESPROC gload_glGenTextures;
extern PFNGLISTEXTUREPROC gload_glIsTexture;
extern PFNGLARRAYELEMENTPROC gload_glArrayElement;
extern PFNGLCOLORPOINTERPROC gload_glColorPointer;
extern PFNGLDISABLECLIENTSTATEPROC gload_glDisableClientState;
extern PFNGLEDGEFLAGPOINTERPROC gload_glEdgeFlagPointer;
extern PFNGLENABLECLIENTSTATEPROC gload_glEnableClientState;
extern PFNGLINDEXPOINTERPROC gload_glIndexPointer;
extern PFNGLINTERLEAVEDARRAYSPROC gload_glInterleavedArrays;
extern PFNGLNORMALPOINTERPROC gload_glNormalPointer;
extern PFNGLTEXCOORDPOINTERPROC gload_glTexCoordPointer;
extern PFNGLVERTEXPOINTERPROC gload_glVertexPointer;
extern PFNGLARETEXTURESRESIDENTPROC gload_glAreTexturesResident;
extern PFNGLPRIORITIZETEXTURESPROC gload_glPrioritizeTextures;
extern PFNGLINDEXUBPROC gload_glIndexub;
extern PFNGLINDEXUBVPROC gload_glIndexubv;
extern PFNGLPOPCLIENTATTRIBPROC gload_glPopClientAttrib;
extern PFNGLPUSHCLIENTATTRIBPROC gload_glPushClientAttrib;

# endif /* GL_VERSION_1_1 */
# if defined GL_VERSION_1_2

extern PFNGLDRAWRANGEELEMENTSPROC gload_glDrawRangeElements;
extern PFNGLTEXIMAGE3DPROC gload_glTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC gload_glTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC gload_glCopyTexSubImage3D;

# endif /* GL_VERSION_1_2 */
# if defined GL_VERSION_1_3

extern PFNGLACTIVETEXTUREPROC gload_glActiveTexture;
extern PFNGLSAMPLECOVERAGEPROC gload_glSampleCoverage;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC gload_glCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC gload_glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC gload_glCompressedTexImage1D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC gload_glCompressedTexSubImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC gload_glCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC gload_glCompressedTexSubImage1D;
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC gload_glGetCompressedTexImage;
extern PFNGLCLIENTACTIVETEXTUREPROC gload_glClientActiveTexture;
extern PFNGLMULTITEXCOORD1DPROC gload_glMultiTexCoord1d;
extern PFNGLMULTITEXCOORD1DVPROC gload_glMultiTexCoord1dv;
extern PFNGLMULTITEXCOORD1FPROC gload_glMultiTexCoord1f;
extern PFNGLMULTITEXCOORD1FVPROC gload_glMultiTexCoord1fv;
extern PFNGLMULTITEXCOORD1IPROC gload_glMultiTexCoord1i;
extern PFNGLMULTITEXCOORD1IVPROC gload_glMultiTexCoord1iv;
extern PFNGLMULTITEXCOORD1SPROC gload_glMultiTexCoord1s;
extern PFNGLMULTITEXCOORD1SVPROC gload_glMultiTexCoord1sv;
extern PFNGLMULTITEXCOORD2DPROC gload_glMultiTexCoord2d;
extern PFNGLMULTITEXCOORD2DVPROC gload_glMultiTexCoord2dv;
extern PFNGLMULTITEXCOORD2FPROC gload_glMultiTexCoord2f;
extern PFNGLMULTITEXCOORD2FVPROC gload_glMultiTexCoord2fv;
extern PFNGLMULTITEXCOORD2IPROC gload_glMultiTexCoord2i;
extern PFNGLMULTITEXCOORD2IVPROC gload_glMultiTexCoord2iv;
extern PFNGLMULTITEXCOORD2SPROC gload_glMultiTexCoord2s;
extern PFNGLMULTITEXCOORD2SVPROC gload_glMultiTexCoord2sv;
extern PFNGLMULTITEXCOORD3DPROC gload_glMultiTexCoord3d;
extern PFNGLMULTITEXCOORD3DVPROC gload_glMultiTexCoord3dv;
extern PFNGLMULTITEXCOORD3FPROC gload_glMultiTexCoord3f;
extern PFNGLMULTITEXCOORD3FVPROC gload_glMultiTexCoord3fv;
extern PFNGLMULTITEXCOORD3IPROC gload_glMultiTexCoord3i;
extern PFNGLMULTITEXCOORD3IVPROC gload_glMultiTexCoord3iv;
extern PFNGLMULTITEXCOORD3SPROC gload_glMultiTexCoord3s;
extern PFNGLMULTITEXCOORD3SVPROC gload_glMultiTexCoord3sv;
extern PFNGLMULTITEXCOORD4DPROC gload_glMultiTexCoord4d;
extern PFNGLMULTITEXCOORD4DVPROC gload_glMultiTexCoord4dv;
extern PFNGLMULTITEXCOORD4FPROC gload_glMultiTexCoord4f;
extern PFNGLMULTITEXCOORD4FVPROC gload_glMultiTexCoord4fv;
extern PFNGLMULTITEXCOORD4IPROC gload_glMultiTexCoord4i;
extern PFNGLMULTITEXCOORD4IVPROC gload_glMultiTexCoord4iv;
extern PFNGLMULTITEXCOORD4SPROC gload_glMultiTexCoord4s;
extern PFNGLMULTITEXCOORD4SVPROC gload_glMultiTexCoord4sv;
extern PFNGLLOADTRANSPOSEMATRIXFPROC gload_glLoadTransposeMatrixf;
extern PFNGLLOADTRANSPOSEMATRIXDPROC gload_glLoadTransposeMatrixd;
extern PFNGLMULTTRANSPOSEMATRIXFPROC gload_glMultTransposeMatrixf;
extern PFNGLMULTTRANSPOSEMATRIXDPROC gload_glMultTransposeMatrixd;

# endif /* GL_VERSION_1_3 */
# if defined GL_VERSION_1_4

extern PFNGLBLENDFUNCSEPARATEPROC gload_glBlendFuncSeparate;
extern PFNGLMULTIDRAWARRAYSPROC gload_glMultiDrawArrays;
extern PFNGLMULTIDRAWELEMENTSPROC gload_glMultiDrawElements;
extern PFNGLPOINTPARAMETERFPROC gload_glPointParameterf;
extern PFNGLPOINTPARAMETERFVPROC gload_glPointParameterfv;
extern PFNGLPOINTPARAMETERIPROC gload_glPointParameteri;
extern PFNGLPOINTPARAMETERIVPROC gload_glPointParameteriv;
extern PFNGLFOGCOORDFPROC gload_glFogCoordf;
extern PFNGLFOGCOORDFVPROC gload_glFogCoordfv;
extern PFNGLFOGCOORDDPROC gload_glFogCoordd;
extern PFNGLFOGCOORDDVPROC gload_glFogCoorddv;
extern PFNGLFOGCOORDPOINTERPROC gload_glFogCoordPointer;
extern PFNGLSECONDARYCOLOR3BPROC gload_glSecondaryColor3b;
extern PFNGLSECONDARYCOLOR3BVPROC gload_glSecondaryColor3bv;
extern PFNGLSECONDARYCOLOR3DPROC gload_glSecondaryColor3d;
extern PFNGLSECONDARYCOLOR3DVPROC gload_glSecondaryColor3dv;
extern PFNGLSECONDARYCOLOR3FPROC gload_glSecondaryColor3f;
extern PFNGLSECONDARYCOLOR3FVPROC gload_glSecondaryColor3fv;
extern PFNGLSECONDARYCOLOR3IPROC gload_glSecondaryColor3i;
extern PFNGLSECONDARYCOLOR3IVPROC gload_glSecondaryColor3iv;
extern PFNGLSECONDARYCOLOR3SPROC gload_glSecondaryColor3s;
extern PFNGLSECONDARYCOLOR3SVPROC gload_glSecondaryColor3sv;
extern PFNGLSECONDARYCOLOR3UBPROC gload_glSecondaryColor3ub;
extern PFNGLSECONDARYCOLOR3UBVPROC gload_glSecondaryColor3ubv;
extern PFNGLSECONDARYCOLOR3UIPROC gload_glSecondaryColor3ui;
extern PFNGLSECONDARYCOLOR3UIVPROC gload_glSecondaryColor3uiv;
extern PFNGLSECONDARYCOLOR3USPROC gload_glSecondaryColor3us;
extern PFNGLSECONDARYCOLOR3USVPROC gload_glSecondaryColor3usv;
extern PFNGLSECONDARYCOLORPOINTERPROC gload_glSecondaryColorPointer;
extern PFNGLWINDOWPOS2DPROC gload_glWindowPos2d;
extern PFNGLWINDOWPOS2DVPROC gload_glWindowPos2dv;
extern PFNGLWINDOWPOS2FPROC gload_glWindowPos2f;
extern PFNGLWINDOWPOS2FVPROC gload_glWindowPos2fv;
extern PFNGLWINDOWPOS2IPROC gload_glWindowPos2i;
extern PFNGLWINDOWPOS2IVPROC gload_glWindowPos2iv;
extern PFNGLWINDOWPOS2SPROC gload_glWindowPos2s;
extern PFNGLWINDOWPOS2SVPROC gload_glWindowPos2sv;
extern PFNGLWINDOWPOS3DPROC gload_glWindowPos3d;
extern PFNGLWINDOWPOS3DVPROC gload_glWindowPos3dv;
extern PFNGLWINDOWPOS3FPROC gload_glWindowPos3f;
extern PFNGLWINDOWPOS3FVPROC gload_glWindowPos3fv;
extern PFNGLWINDOWPOS3IPROC gload_glWindowPos3i;
extern PFNGLWINDOWPOS3IVPROC gload_glWindowPos3iv;
extern PFNGLWINDOWPOS3SPROC gload_glWindowPos3s;
extern PFNGLWINDOWPOS3SVPROC gload_glWindowPos3sv;
extern PFNGLBLENDCOLORPROC gload_glBlendColor;
extern PFNGLBLENDEQUATIONPROC gload_glBlendEquation;

# endif /* GL_VERSION_1_4 */
# if defined GL_VERSION_1_5

extern PFNGLGENQUERIESPROC gload_glGenQueries;
extern PFNGLDELETEQUERIESPROC gload_glDeleteQueries;
extern PFNGLISQUERYPROC gload_glIsQuery;
extern PFNGLBEGINQUERYPROC gload_glBeginQuery;
extern PFNGLENDQUERYPROC gload_glEndQuery;
extern PFNGLGETQUERYIVPROC gload_glGetQueryiv;
extern PFNGLGETQUERYOBJECTIVPROC gload_glGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTUIVPROC gload_glGetQueryObjectuiv;
extern PFNGLBINDBUFFERPROC gload_glBindBuffer;
extern PFNGLDELETEBUFFERSPROC gload_glDeleteBuffers;
extern PFNGLGENBUFFERSPROC gload_glGenBuffers;
extern PFNGLISBUFFERPROC gload_glIsBuffer;
extern PFNGLBUFFERDATAPROC gload_glBufferData;
extern PFNGLBUFFERSUBDATAPROC gload_glBufferSubData;
extern PFNGLGETBUFFERSUBDATAPROC gload_glGetBufferSubData;
extern PFNGLMAPBUFFERPROC gload_glMapBuffer;
extern PFNGLUNMAPBUFFERPROC gload_glUnmapBuffer;
extern PFNGLGETBUFFERPARAMETERIVPROC gload_glGetBufferParameteriv;
extern PFNGLGETBUFFERPOINTERVPROC gload_glGetBufferPointerv;

# endif /* GL_VERSION_1_5 */
# if defined GL_VERSION_2_0

extern PFNGLBLENDEQUATIONSEPARATEPROC gload_glBlendEquationSeparate;
extern PFNGLDRAWBUFFERSPROC gload_glDrawBuffers;
extern PFNGLSTENCILOPSEPARATEPROC gload_glStencilOpSeparate;
extern PFNGLSTENCILFUNCSEPARATEPROC gload_glStencilFuncSeparate;
extern PFNGLSTENCILMASKSEPARATEPROC gload_glStencilMaskSeparate;
extern PFNGLATTACHSHADERPROC gload_glAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC gload_glBindAttribLocation;
extern PFNGLCOMPILESHADERPROC gload_glCompileShader;
extern PFNGLCREATEPROGRAMPROC gload_glCreateProgram;
extern PFNGLCREATESHADERPROC gload_glCreateShader;
extern PFNGLDELETEPROGRAMPROC gload_glDeleteProgram;
extern PFNGLDELETESHADERPROC gload_glDeleteShader;
extern PFNGLDETACHSHADERPROC gload_glDetachShader;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC gload_glDisableVertexAttribArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC gload_glEnableVertexAttribArray;
extern PFNGLGETACTIVEATTRIBPROC gload_glGetActiveAttrib;
extern PFNGLGETACTIVEUNIFORMPROC gload_glGetActiveUniform;
extern PFNGLGETATTACHEDSHADERSPROC gload_glGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC gload_glGetAttribLocation;
extern PFNGLGETPROGRAMIVPROC gload_glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC gload_glGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC gload_glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC gload_glGetShaderInfoLog;
extern PFNGLGETSHADERSOURCEPROC gload_glGetShaderSource;
extern PFNGLGETUNIFORMLOCATIONPROC gload_glGetUniformLocation;
extern PFNGLGETUNIFORMFVPROC gload_glGetUniformfv;
extern PFNGLGETUNIFORMIVPROC gload_glGetUniformiv;
extern PFNGLGETVERTEXATTRIBDVPROC gload_glGetVertexAttribdv;
extern PFNGLGETVERTEXATTRIBFVPROC gload_glGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC gload_glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC gload_glGetVertexAttribPointerv;
extern PFNGLISPROGRAMPROC gload_glIsProgram;
extern PFNGLISSHADERPROC gload_glIsShader;
extern PFNGLLINKPROGRAMPROC gload_glLinkProgram;
extern PFNGLSHADERSOURCEPROC gload_glShaderSource;
extern PFNGLUSEPROGRAMPROC gload_glUseProgram;
extern PFNGLUNIFORM1FPROC gload_glUniform1f;
extern PFNGLUNIFORM2FPROC gload_glUniform2f;
extern PFNGLUNIFORM3FPROC gload_glUniform3f;
extern PFNGLUNIFORM4FPROC gload_glUniform4f;
extern PFNGLUNIFORM1IPROC gload_glUniform1i;
extern PFNGLUNIFORM2IPROC gload_glUniform2i;
extern PFNGLUNIFORM3IPROC gload_glUniform3i;
extern PFNGLUNIFORM4IPROC gload_glUniform4i;
extern PFNGLUNIFORM1FVPROC gload_glUniform1fv;
extern PFNGLUNIFORM2FVPROC gload_glUniform2fv;
extern PFNGLUNIFORM3FVPROC gload_glUniform3fv;
extern PFNGLUNIFORM4FVPROC gload_glUniform4fv;
extern PFNGLUNIFORM1IVPROC gload_glUniform1iv;
extern PFNGLUNIFORM2IVPROC gload_glUniform2iv;
extern PFNGLUNIFORM3IVPROC gload_glUniform3iv;
extern PFNGLUNIFORM4IVPROC gload_glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC gload_glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC gload_glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC gload_glUniformMatrix4fv;
extern PFNGLVALIDATEPROGRAMPROC gload_glValidateProgram;
extern PFNGLVERTEXATTRIB1DPROC gload_glVertexAttrib1d;
extern PFNGLVERTEXATTRIB1DVPROC gload_glVertexAttrib1dv;
extern PFNGLVERTEXATTRIB1FPROC gload_glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC gload_glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB1SPROC gload_glVertexAttrib1s;
extern PFNGLVERTEXATTRIB1SVPROC gload_glVertexAttrib1sv;
extern PFNGLVERTEXATTRIB2DPROC gload_glVertexAttrib2d;
extern PFNGLVERTEXATTRIB2DVPROC gload_glVertexAttrib2dv;
extern PFNGLVERTEXATTRIB2FPROC gload_glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC gload_glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB2SPROC gload_glVertexAttrib2s;
extern PFNGLVERTEXATTRIB2SVPROC gload_glVertexAttrib2sv;
extern PFNGLVERTEXATTRIB3DPROC gload_glVertexAttrib3d;
extern PFNGLVERTEXATTRIB3DVPROC gload_glVertexAttrib3dv;
extern PFNGLVERTEXATTRIB3FPROC gload_glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC gload_glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB3SPROC gload_glVertexAttrib3s;
extern PFNGLVERTEXATTRIB3SVPROC gload_glVertexAttrib3sv;
extern PFNGLVERTEXATTRIB4NBVPROC gload_glVertexAttrib4Nbv;
extern PFNGLVERTEXATTRIB4NIVPROC gload_glVertexAttrib4Niv;
extern PFNGLVERTEXATTRIB4NSVPROC gload_glVertexAttrib4Nsv;
extern PFNGLVERTEXATTRIB4NUBPROC gload_glVertexAttrib4Nub;
extern PFNGLVERTEXATTRIB4NUBVPROC gload_glVertexAttrib4Nubv;
extern PFNGLVERTEXATTRIB4NUIVPROC gload_glVertexAttrib4Nuiv;
extern PFNGLVERTEXATTRIB4NUSVPROC gload_glVertexAttrib4Nusv;
extern PFNGLVERTEXATTRIB4BVPROC gload_glVertexAttrib4bv;
extern PFNGLVERTEXATTRIB4DPROC gload_glVertexAttrib4d;
extern PFNGLVERTEXATTRIB4DVPROC gload_glVertexAttrib4dv;
extern PFNGLVERTEXATTRIB4FPROC gload_glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC gload_glVertexAttrib4fv;
extern PFNGLVERTEXATTRIB4IVPROC gload_glVertexAttrib4iv;
extern PFNGLVERTEXATTRIB4SPROC gload_glVertexAttrib4s;
extern PFNGLVERTEXATTRIB4SVPROC gload_glVertexAttrib4sv;
extern PFNGLVERTEXATTRIB4UBVPROC gload_glVertexAttrib4ubv;
extern PFNGLVERTEXATTRIB4UIVPROC gload_glVertexAttrib4uiv;
extern PFNGLVERTEXATTRIB4USVPROC gload_glVertexAttrib4usv;
extern PFNGLVERTEXATTRIBPOINTERPROC gload_glVertexAttribPointer;

# endif /* GL_VERSION_2_0 */
# if defined GL_VERSION_2_1

extern PFNGLUNIFORMMATRIX2X3FVPROC gload_glUniformMatrix2x3fv;
extern PFNGLUNIFORMMATRIX3X2FVPROC gload_glUniformMatrix3x2fv;
extern PFNGLUNIFORMMATRIX2X4FVPROC gload_glUniformMatrix2x4fv;
extern PFNGLUNIFORMMATRIX4X2FVPROC gload_glUniformMatrix4x2fv;
extern PFNGLUNIFORMMATRIX3X4FVPROC gload_glUniformMatrix3x4fv;
extern PFNGLUNIFORMMATRIX4X3FVPROC gload_glUniformMatrix4x3fv;

# endif /* GL_VERSION_2_1 */
# if defined GL_VERSION_3_0

extern PFNGLCOLORMASKIPROC gload_glColorMaski;
extern PFNGLGETBOOLEANI_VPROC gload_glGetBooleani_v;
extern PFNGLGETINTEGERI_VPROC gload_glGetIntegeri_v;
extern PFNGLENABLEIPROC gload_glEnablei;
extern PFNGLDISABLEIPROC gload_glDisablei;
extern PFNGLISENABLEDIPROC gload_glIsEnabledi;
extern PFNGLBEGINTRANSFORMFEEDBACKPROC gload_glBeginTransformFeedback;
extern PFNGLENDTRANSFORMFEEDBACKPROC gload_glEndTransformFeedback;
extern PFNGLBINDBUFFERRANGEPROC gload_glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC gload_glBindBufferBase;
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC gload_glTransformFeedbackVaryings;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC gload_glGetTransformFeedbackVarying;
extern PFNGLCLAMPCOLORPROC gload_glClampColor;
extern PFNGLBEGINCONDITIONALRENDERPROC gload_glBeginConditionalRender;
extern PFNGLENDCONDITIONALRENDERPROC gload_glEndConditionalRender;
extern PFNGLVERTEXATTRIBIPOINTERPROC gload_glVertexAttribIPointer;
extern PFNGLGETVERTEXATTRIBIIVPROC gload_glGetVertexAttribIiv;
extern PFNGLGETVERTEXATTRIBIUIVPROC gload_glGetVertexAttribIuiv;
extern PFNGLVERTEXATTRIBI1IPROC gload_glVertexAttribI1i;
extern PFNGLVERTEXATTRIBI2IPROC gload_glVertexAttribI2i;
extern PFNGLVERTEXATTRIBI3IPROC gload_glVertexAttribI3i;
extern PFNGLVERTEXATTRIBI4IPROC gload_glVertexAttribI4i;
extern PFNGLVERTEXATTRIBI1UIPROC gload_glVertexAttribI1ui;
extern PFNGLVERTEXATTRIBI2UIPROC gload_glVertexAttribI2ui;
extern PFNGLVERTEXATTRIBI3UIPROC gload_glVertexAttribI3ui;
extern PFNGLVERTEXATTRIBI4UIPROC gload_glVertexAttribI4ui;
extern PFNGLVERTEXATTRIBI1IVPROC gload_glVertexAttribI1iv;
extern PFNGLVERTEXATTRIBI2IVPROC gload_glVertexAttribI2iv;
extern PFNGLVERTEXATTRIBI3IVPROC gload_glVertexAttribI3iv;
extern PFNGLVERTEXATTRIBI4IVPROC gload_glVertexAttribI4iv;
extern PFNGLVERTEXATTRIBI1UIVPROC gload_glVertexAttribI1uiv;
extern PFNGLVERTEXATTRIBI2UIVPROC gload_glVertexAttribI2uiv;
extern PFNGLVERTEXATTRIBI3UIVPROC gload_glVertexAttribI3uiv;
extern PFNGLVERTEXATTRIBI4UIVPROC gload_glVertexAttribI4uiv;
extern PFNGLVERTEXATTRIBI4BVPROC gload_glVertexAttribI4bv;
extern PFNGLVERTEXATTRIBI4SVPROC gload_glVertexAttribI4sv;
extern PFNGLVERTEXATTRIBI4UBVPROC gload_glVertexAttribI4ubv;
extern PFNGLVERTEXATTRIBI4USVPROC gload_glVertexAttribI4usv;
extern PFNGLGETUNIFORMUIVPROC gload_glGetUniformuiv;
extern PFNGLBINDFRAGDATALOCATIONPROC gload_glBindFragDataLocation;
extern PFNGLGETFRAGDATALOCATIONPROC gload_glGetFragDataLocation;
extern PFNGLUNIFORM1UIPROC gload_glUniform1ui;
extern PFNGLUNIFORM2UIPROC gload_glUniform2ui;
extern PFNGLUNIFORM3UIPROC gload_glUniform3ui;
extern PFNGLUNIFORM4UIPROC gload_glUniform4ui;
extern PFNGLUNIFORM1UIVPROC gload_glUniform1uiv;
extern PFNGLUNIFORM2UIVPROC gload_glUniform2uiv;
extern PFNGLUNIFORM3UIVPROC gload_glUniform3uiv;
extern PFNGLUNIFORM4UIVPROC gload_glUniform4uiv;
extern PFNGLTEXPARAMETERIIVPROC gload_glTexParameterIiv;
extern PFNGLTEXPARAMETERIUIVPROC gload_glTexParameterIuiv;
extern PFNGLGETTEXPARAMETERIIVPROC gload_glGetTexParameterIiv;
extern PFNGLGETTEXPARAMETERIUIVPROC gload_glGetTexParameterIuiv;
extern PFNGLCLEARBUFFERIVPROC gload_glClearBufferiv;
extern PFNGLCLEARBUFFERUIVPROC gload_glClearBufferuiv;
extern PFNGLCLEARBUFFERFVPROC gload_glClearBufferfv;
extern PFNGLCLEARBUFFERFIPROC gload_glClearBufferfi;
extern PFNGLGETSTRINGIPROC gload_glGetStringi;
extern PFNGLISRENDERBUFFERPROC gload_glIsRenderbuffer;
extern PFNGLBINDRENDERBUFFERPROC gload_glBindRenderbuffer;
extern PFNGLDELETERENDERBUFFERSPROC gload_glDeleteRenderbuffers;
extern PFNGLGENRENDERBUFFERSPROC gload_glGenRenderbuffers;
extern PFNGLRENDERBUFFERSTORAGEPROC gload_glRenderbufferStorage;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC gload_glGetRenderbufferParameteriv;
extern PFNGLISFRAMEBUFFERPROC gload_glIsFramebuffer;
extern PFNGLBINDFRAMEBUFFERPROC gload_glBindFramebuffer;
extern PFNGLDELETEFRAMEBUFFERSPROC gload_glDeleteFramebuffers;
extern PFNGLGENFRAMEBUFFERSPROC gload_glGenFramebuffers;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC gload_glCheckFramebufferStatus;
extern PFNGLFRAMEBUFFERTEXTURE1DPROC gload_glFramebufferTexture1D;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC gload_glFramebufferTexture2D;
extern PFNGLFRAMEBUFFERTEXTURE3DPROC gload_glFramebufferTexture3D;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC gload_glFramebufferRenderbuffer;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC gload_glGetFramebufferAttachmentParameteriv;
extern PFNGLGENERATEMIPMAPPROC gload_glGenerateMipmap;
extern PFNGLBLITFRAMEBUFFERPROC gload_glBlitFramebuffer;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC gload_glRenderbufferStorageMultisample;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC gload_glFramebufferTextureLayer;
extern PFNGLMAPBUFFERRANGEPROC gload_glMapBufferRange;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC gload_glFlushMappedBufferRange;
extern PFNGLBINDVERTEXARRAYPROC gload_glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC gload_glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC gload_glGenVertexArrays;
extern PFNGLISVERTEXARRAYPROC gload_glIsVertexArray;

# endif /* GL_VERSION_3_0 */
# if defined GL_VERSION_3_1

extern PFNGLDRAWARRAYSINSTANCEDPROC gload_glDrawArraysInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDPROC gload_glDrawElementsInstanced;
extern PFNGLTEXBUFFERPROC gload_glTexBuffer;
extern PFNGLPRIMITIVERESTARTINDEXPROC gload_glPrimitiveRestartIndex;
extern PFNGLCOPYBUFFERSUBDATAPROC gload_glCopyBufferSubData;
extern PFNGLGETUNIFORMINDICESPROC gload_glGetUniformIndices;
extern PFNGLGETACTIVEUNIFORMSIVPROC gload_glGetActiveUniformsiv;
extern PFNGLGETACTIVEUNIFORMNAMEPROC gload_glGetActiveUniformName;
extern PFNGLGETUNIFORMBLOCKINDEXPROC gload_glGetUniformBlockIndex;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC gload_glGetActiveUniformBlockiv;
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC gload_glGetActiveUniformBlockName;
extern PFNGLUNIFORMBLOCKBINDINGPROC gload_glUniformBlockBinding;
extern PFNGLBINDBUFFERRANGEPROC gload_glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC gload_glBindBufferBase;
extern PFNGLGETINTEGERI_VPROC gload_glGetIntegeri_v;

# endif /* GL_VERSION_3_1 */
# if defined GL_VERSION_3_2

extern PFNGLDRAWELEMENTSBASEVERTEXPROC gload_glDrawElementsBaseVertex;
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC gload_glDrawRangeElementsBaseVertex;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC gload_glDrawElementsInstancedBaseVertex;
extern PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC gload_glMultiDrawElementsBaseVertex;
extern PFNGLPROVOKINGVERTEXPROC gload_glProvokingVertex;
extern PFNGLFENCESYNCPROC gload_glFenceSync;
extern PFNGLISSYNCPROC gload_glIsSync;
extern PFNGLDELETESYNCPROC gload_glDeleteSync;
extern PFNGLCLIENTWAITSYNCPROC gload_glClientWaitSync;
extern PFNGLWAITSYNCPROC gload_glWaitSync;
extern PFNGLGETINTEGER64VPROC gload_glGetInteger64v;
extern PFNGLGETSYNCIVPROC gload_glGetSynciv;
extern PFNGLGETINTEGER64I_VPROC gload_glGetInteger64i_v;
extern PFNGLGETBUFFERPARAMETERI64VPROC gload_glGetBufferParameteri64v;
extern PFNGLFRAMEBUFFERTEXTUREPROC gload_glFramebufferTexture;
extern PFNGLTEXIMAGE2DMULTISAMPLEPROC gload_glTexImage2DMultisample;
extern PFNGLTEXIMAGE3DMULTISAMPLEPROC gload_glTexImage3DMultisample;
extern PFNGLGETMULTISAMPLEFVPROC gload_glGetMultisamplefv;
extern PFNGLSAMPLEMASKIPROC gload_glSampleMaski;

# endif /* GL_VERSION_3_2 */
# if defined GL_VERSION_3_3

extern PFNGLBINDFRAGDATALOCATIONINDEXEDPROC gload_glBindFragDataLocationIndexed;
extern PFNGLGETFRAGDATAINDEXPROC gload_glGetFragDataIndex;
extern PFNGLGENSAMPLERSPROC gload_glGenSamplers;
extern PFNGLDELETESAMPLERSPROC gload_glDeleteSamplers;
extern PFNGLISSAMPLERPROC gload_glIsSampler;
extern PFNGLBINDSAMPLERPROC gload_glBindSampler;
extern PFNGLSAMPLERPARAMETERIPROC gload_glSamplerParameteri;
extern PFNGLSAMPLERPARAMETERIVPROC gload_glSamplerParameteriv;
extern PFNGLSAMPLERPARAMETERFPROC gload_glSamplerParameterf;
extern PFNGLSAMPLERPARAMETERFVPROC gload_glSamplerParameterfv;
extern PFNGLSAMPLERPARAMETERIIVPROC gload_glSamplerParameterIiv;
extern PFNGLSAMPLERPARAMETERIUIVPROC gload_glSamplerParameterIuiv;
extern PFNGLGETSAMPLERPARAMETERIVPROC gload_glGetSamplerParameteriv;
extern PFNGLGETSAMPLERPARAMETERIIVPROC gload_glGetSamplerParameterIiv;
extern PFNGLGETSAMPLERPARAMETERFVPROC gload_glGetSamplerParameterfv;
extern PFNGLGETSAMPLERPARAMETERIUIVPROC gload_glGetSamplerParameterIuiv;
extern PFNGLQUERYCOUNTERPROC gload_glQueryCounter;
extern PFNGLGETQUERYOBJECTI64VPROC gload_glGetQueryObjecti64v;
extern PFNGLGETQUERYOBJECTUI64VPROC gload_glGetQueryObjectui64v;
extern PFNGLVERTEXATTRIBDIVISORPROC gload_glVertexAttribDivisor;
extern PFNGLVERTEXATTRIBP1UIPROC gload_glVertexAttribP1ui;
extern PFNGLVERTEXATTRIBP1UIVPROC gload_glVertexAttribP1uiv;
extern PFNGLVERTEXATTRIBP2UIPROC gload_glVertexAttribP2ui;
extern PFNGLVERTEXATTRIBP2UIVPROC gload_glVertexAttribP2uiv;
extern PFNGLVERTEXATTRIBP3UIPROC gload_glVertexAttribP3ui;
extern PFNGLVERTEXATTRIBP3UIVPROC gload_glVertexAttribP3uiv;
extern PFNGLVERTEXATTRIBP4UIPROC gload_glVertexAttribP4ui;
extern PFNGLVERTEXATTRIBP4UIVPROC gload_glVertexAttribP4uiv;
extern PFNGLVERTEXP2UIPROC gload_glVertexP2ui;
extern PFNGLVERTEXP2UIVPROC gload_glVertexP2uiv;
extern PFNGLVERTEXP3UIPROC gload_glVertexP3ui;
extern PFNGLVERTEXP3UIVPROC gload_glVertexP3uiv;
extern PFNGLVERTEXP4UIPROC gload_glVertexP4ui;
extern PFNGLVERTEXP4UIVPROC gload_glVertexP4uiv;
extern PFNGLTEXCOORDP1UIPROC gload_glTexCoordP1ui;
extern PFNGLTEXCOORDP1UIVPROC gload_glTexCoordP1uiv;
extern PFNGLTEXCOORDP2UIPROC gload_glTexCoordP2ui;
extern PFNGLTEXCOORDP2UIVPROC gload_glTexCoordP2uiv;
extern PFNGLTEXCOORDP3UIPROC gload_glTexCoordP3ui;
extern PFNGLTEXCOORDP3UIVPROC gload_glTexCoordP3uiv;
extern PFNGLTEXCOORDP4UIPROC gload_glTexCoordP4ui;
extern PFNGLTEXCOORDP4UIVPROC gload_glTexCoordP4uiv;
extern PFNGLMULTITEXCOORDP1UIPROC gload_glMultiTexCoordP1ui;
extern PFNGLMULTITEXCOORDP1UIVPROC gload_glMultiTexCoordP1uiv;
extern PFNGLMULTITEXCOORDP2UIPROC gload_glMultiTexCoordP2ui;
extern PFNGLMULTITEXCOORDP2UIVPROC gload_glMultiTexCoordP2uiv;
extern PFNGLMULTITEXCOORDP3UIPROC gload_glMultiTexCoordP3ui;
extern PFNGLMULTITEXCOORDP3UIVPROC gload_glMultiTexCoordP3uiv;
extern PFNGLMULTITEXCOORDP4UIPROC gload_glMultiTexCoordP4ui;
extern PFNGLMULTITEXCOORDP4UIVPROC gload_glMultiTexCoordP4uiv;
extern PFNGLNORMALP3UIPROC gload_glNormalP3ui;
extern PFNGLNORMALP3UIVPROC gload_glNormalP3uiv;
extern PFNGLCOLORP3UIPROC gload_glColorP3ui;
extern PFNGLCOLORP3UIVPROC gload_glColorP3uiv;
extern PFNGLCOLORP4UIPROC gload_glColorP4ui;
extern PFNGLCOLORP4UIVPROC gload_glColorP4uiv;
extern PFNGLSECONDARYCOLORP3UIPROC gload_glSecondaryColorP3ui;
extern PFNGLSECONDARYCOLORP3UIVPROC gload_glSecondaryColorP3uiv;

# endif /* GL_VERSION_3_3 */
# if defined GL_VERSION_4_0

extern PFNGLMINSAMPLESHADINGPROC gload_glMinSampleShading;
extern PFNGLBLENDEQUATIONIPROC gload_glBlendEquationi;
extern PFNGLBLENDEQUATIONSEPARATEIPROC gload_glBlendEquationSeparatei;
extern PFNGLBLENDFUNCIPROC gload_glBlendFunci;
extern PFNGLBLENDFUNCSEPARATEIPROC gload_glBlendFuncSeparatei;
extern PFNGLDRAWARRAYSINDIRECTPROC gload_glDrawArraysIndirect;
extern PFNGLDRAWELEMENTSINDIRECTPROC gload_glDrawElementsIndirect;
extern PFNGLUNIFORM1DPROC gload_glUniform1d;
extern PFNGLUNIFORM2DPROC gload_glUniform2d;
extern PFNGLUNIFORM3DPROC gload_glUniform3d;
extern PFNGLUNIFORM4DPROC gload_glUniform4d;
extern PFNGLUNIFORM1DVPROC gload_glUniform1dv;
extern PFNGLUNIFORM2DVPROC gload_glUniform2dv;
extern PFNGLUNIFORM3DVPROC gload_glUniform3dv;
extern PFNGLUNIFORM4DVPROC gload_glUniform4dv;
extern PFNGLUNIFORMMATRIX2DVPROC gload_glUniformMatrix2dv;
extern PFNGLUNIFORMMATRIX3DVPROC gload_glUniformMatrix3dv;
extern PFNGLUNIFORMMATRIX4DVPROC gload_glUniformMatrix4dv;
extern PFNGLUNIFORMMATRIX2X3DVPROC gload_glUniformMatrix2x3dv;
extern PFNGLUNIFORMMATRIX2X4DVPROC gload_glUniformMatrix2x4dv;
extern PFNGLUNIFORMMATRIX3X2DVPROC gload_glUniformMatrix3x2dv;
extern PFNGLUNIFORMMATRIX3X4DVPROC gload_glUniformMatrix3x4dv;
extern PFNGLUNIFORMMATRIX4X2DVPROC gload_glUniformMatrix4x2dv;
extern PFNGLUNIFORMMATRIX4X3DVPROC gload_glUniformMatrix4x3dv;
extern PFNGLGETUNIFORMDVPROC gload_glGetUniformdv;
extern PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC gload_glGetSubroutineUniformLocation;
extern PFNGLGETSUBROUTINEINDEXPROC gload_glGetSubroutineIndex;
extern PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC gload_glGetActiveSubroutineUniformiv;
extern PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC gload_glGetActiveSubroutineUniformName;
extern PFNGLGETACTIVESUBROUTINENAMEPROC gload_glGetActiveSubroutineName;
extern PFNGLUNIFORMSUBROUTINESUIVPROC gload_glUniformSubroutinesuiv;
extern PFNGLGETUNIFORMSUBROUTINEUIVPROC gload_glGetUniformSubroutineuiv;
extern PFNGLGETPROGRAMSTAGEIVPROC gload_glGetProgramStageiv;
extern PFNGLPATCHPARAMETERIPROC gload_glPatchParameteri;
extern PFNGLPATCHPARAMETERFVPROC gload_glPatchParameterfv;
extern PFNGLBINDTRANSFORMFEEDBACKPROC gload_glBindTransformFeedback;
extern PFNGLDELETETRANSFORMFEEDBACKSPROC gload_glDeleteTransformFeedbacks;
extern PFNGLGENTRANSFORMFEEDBACKSPROC gload_glGenTransformFeedbacks;
extern PFNGLISTRANSFORMFEEDBACKPROC gload_glIsTransformFeedback;
extern PFNGLPAUSETRANSFORMFEEDBACKPROC gload_glPauseTransformFeedback;
extern PFNGLRESUMETRANSFORMFEEDBACKPROC gload_glResumeTransformFeedback;
extern PFNGLDRAWTRANSFORMFEEDBACKPROC gload_glDrawTransformFeedback;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC gload_glDrawTransformFeedbackStream;
extern PFNGLBEGINQUERYINDEXEDPROC gload_glBeginQueryIndexed;
extern PFNGLENDQUERYINDEXEDPROC gload_glEndQueryIndexed;
extern PFNGLGETQUERYINDEXEDIVPROC gload_glGetQueryIndexediv;

# endif /* GL_VERSION_4_0 */
# if defined GL_VERSION_4_1

extern PFNGLRELEASESHADERCOMPILERPROC gload_glReleaseShaderCompiler;
extern PFNGLSHADERBINARYPROC gload_glShaderBinary;
extern PFNGLGETSHADERPRECISIONFORMATPROC gload_glGetShaderPrecisionFormat;
extern PFNGLDEPTHRANGEFPROC gload_glDepthRangef;
extern PFNGLCLEARDEPTHFPROC gload_glClearDepthf;
extern PFNGLGETPROGRAMBINARYPROC gload_glGetProgramBinary;
extern PFNGLPROGRAMBINARYPROC gload_glProgramBinary;
extern PFNGLPROGRAMPARAMETERIPROC gload_glProgramParameteri;
extern PFNGLUSEPROGRAMSTAGESPROC gload_glUseProgramStages;
extern PFNGLACTIVESHADERPROGRAMPROC gload_glActiveShaderProgram;
extern PFNGLCREATESHADERPROGRAMVPROC gload_glCreateShaderProgramv;
extern PFNGLBINDPROGRAMPIPELINEPROC gload_glBindProgramPipeline;
extern PFNGLDELETEPROGRAMPIPELINESPROC gload_glDeleteProgramPipelines;
extern PFNGLGENPROGRAMPIPELINESPROC gload_glGenProgramPipelines;
extern PFNGLISPROGRAMPIPELINEPROC gload_glIsProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEIVPROC gload_glGetProgramPipelineiv;
extern PFNGLPROGRAMPARAMETERIPROC gload_glProgramParameteri;
extern PFNGLPROGRAMUNIFORM1IPROC gload_glProgramUniform1i;
extern PFNGLPROGRAMUNIFORM1IVPROC gload_glProgramUniform1iv;
extern PFNGLPROGRAMUNIFORM1FPROC gload_glProgramUniform1f;
extern PFNGLPROGRAMUNIFORM1FVPROC gload_glProgramUniform1fv;
extern PFNGLPROGRAMUNIFORM1DPROC gload_glProgramUniform1d;
extern PFNGLPROGRAMUNIFORM1DVPROC gload_glProgramUniform1dv;
extern PFNGLPROGRAMUNIFORM1UIPROC gload_glProgramUniform1ui;
extern PFNGLPROGRAMUNIFORM1UIVPROC gload_glProgramUniform1uiv;
extern PFNGLPROGRAMUNIFORM2IPROC gload_glProgramUniform2i;
extern PFNGLPROGRAMUNIFORM2IVPROC gload_glProgramUniform2iv;
extern PFNGLPROGRAMUNIFORM2FPROC gload_glProgramUniform2f;
extern PFNGLPROGRAMUNIFORM2FVPROC gload_glProgramUniform2fv;
extern PFNGLPROGRAMUNIFORM2DPROC gload_glProgramUniform2d;
extern PFNGLPROGRAMUNIFORM2DVPROC gload_glProgramUniform2dv;
extern PFNGLPROGRAMUNIFORM2UIPROC gload_glProgramUniform2ui;
extern PFNGLPROGRAMUNIFORM2UIVPROC gload_glProgramUniform2uiv;
extern PFNGLPROGRAMUNIFORM3IPROC gload_glProgramUniform3i;
extern PFNGLPROGRAMUNIFORM3IVPROC gload_glProgramUniform3iv;
extern PFNGLPROGRAMUNIFORM3FPROC gload_glProgramUniform3f;
extern PFNGLPROGRAMUNIFORM3FVPROC gload_glProgramUniform3fv;
extern PFNGLPROGRAMUNIFORM3DPROC gload_glProgramUniform3d;
extern PFNGLPROGRAMUNIFORM3DVPROC gload_glProgramUniform3dv;
extern PFNGLPROGRAMUNIFORM3UIPROC gload_glProgramUniform3ui;
extern PFNGLPROGRAMUNIFORM3UIVPROC gload_glProgramUniform3uiv;
extern PFNGLPROGRAMUNIFORM4IPROC gload_glProgramUniform4i;
extern PFNGLPROGRAMUNIFORM4IVPROC gload_glProgramUniform4iv;
extern PFNGLPROGRAMUNIFORM4FPROC gload_glProgramUniform4f;
extern PFNGLPROGRAMUNIFORM4FVPROC gload_glProgramUniform4fv;
extern PFNGLPROGRAMUNIFORM4DPROC gload_glProgramUniform4d;
extern PFNGLPROGRAMUNIFORM4DVPROC gload_glProgramUniform4dv;
extern PFNGLPROGRAMUNIFORM4UIPROC gload_glProgramUniform4ui;
extern PFNGLPROGRAMUNIFORM4UIVPROC gload_glProgramUniform4uiv;
extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC gload_glProgramUniformMatrix2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC gload_glProgramUniformMatrix3fv;
extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC gload_glProgramUniformMatrix4fv;
extern PFNGLPROGRAMUNIFORMMATRIX2DVPROC gload_glProgramUniformMatrix2dv;
extern PFNGLPROGRAMUNIFORMMATRIX3DVPROC gload_glProgramUniformMatrix3dv;
extern PFNGLPROGRAMUNIFORMMATRIX4DVPROC gload_glProgramUniformMatrix4dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC gload_glProgramUniformMatrix2x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC gload_glProgramUniformMatrix3x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC gload_glProgramUniformMatrix2x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC gload_glProgramUniformMatrix4x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC gload_glProgramUniformMatrix3x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC gload_glProgramUniformMatrix4x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC gload_glProgramUniformMatrix2x3dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC gload_glProgramUniformMatrix3x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC gload_glProgramUniformMatrix2x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC gload_glProgramUniformMatrix4x2dv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC gload_glProgramUniformMatrix3x4dv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC gload_glProgramUniformMatrix4x3dv;
extern PFNGLVALIDATEPROGRAMPIPELINEPROC gload_glValidateProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC gload_glGetProgramPipelineInfoLog;
extern PFNGLVERTEXATTRIBL1DPROC gload_glVertexAttribL1d;
extern PFNGLVERTEXATTRIBL2DPROC gload_glVertexAttribL2d;
extern PFNGLVERTEXATTRIBL3DPROC gload_glVertexAttribL3d;
extern PFNGLVERTEXATTRIBL4DPROC gload_glVertexAttribL4d;
extern PFNGLVERTEXATTRIBL1DVPROC gload_glVertexAttribL1dv;
extern PFNGLVERTEXATTRIBL2DVPROC gload_glVertexAttribL2dv;
extern PFNGLVERTEXATTRIBL3DVPROC gload_glVertexAttribL3dv;
extern PFNGLVERTEXATTRIBL4DVPROC gload_glVertexAttribL4dv;
extern PFNGLVERTEXATTRIBLPOINTERPROC gload_glVertexAttribLPointer;
extern PFNGLGETVERTEXATTRIBLDVPROC gload_glGetVertexAttribLdv;
extern PFNGLVIEWPORTARRAYVPROC gload_glViewportArrayv;
extern PFNGLVIEWPORTINDEXEDFPROC gload_glViewportIndexedf;
extern PFNGLVIEWPORTINDEXEDFVPROC gload_glViewportIndexedfv;
extern PFNGLSCISSORARRAYVPROC gload_glScissorArrayv;
extern PFNGLSCISSORINDEXEDPROC gload_glScissorIndexed;
extern PFNGLSCISSORINDEXEDVPROC gload_glScissorIndexedv;
extern PFNGLDEPTHRANGEARRAYVPROC gload_glDepthRangeArrayv;
extern PFNGLDEPTHRANGEINDEXEDPROC gload_glDepthRangeIndexed;
extern PFNGLGETFLOATI_VPROC gload_glGetFloati_v;
extern PFNGLGETDOUBLEI_VPROC gload_glGetDoublei_v;

# endif /* GL_VERSION_4_1 */
# if defined GL_VERSION_4_2

extern PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC gload_glDrawArraysInstancedBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC gload_glDrawElementsInstancedBaseInstance;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC gload_glDrawElementsInstancedBaseVertexBaseInstance;
extern PFNGLGETINTERNALFORMATIVPROC gload_glGetInternalformativ;
extern PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC gload_glGetActiveAtomicCounterBufferiv;
extern PFNGLBINDIMAGETEXTUREPROC gload_glBindImageTexture;
extern PFNGLMEMORYBARRIERPROC gload_glMemoryBarrier;
extern PFNGLTEXSTORAGE1DPROC gload_glTexStorage1D;
extern PFNGLTEXSTORAGE2DPROC gload_glTexStorage2D;
extern PFNGLTEXSTORAGE3DPROC gload_glTexStorage3D;
extern PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC gload_glDrawTransformFeedbackInstanced;
extern PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC gload_glDrawTransformFeedbackStreamInstanced;

# endif /* GL_VERSION_4_2 */
# if defined GL_VERSION_4_3

extern PFNGLCLEARBUFFERDATAPROC gload_glClearBufferData;
extern PFNGLCLEARBUFFERSUBDATAPROC gload_glClearBufferSubData;
extern PFNGLDISPATCHCOMPUTEPROC gload_glDispatchCompute;
extern PFNGLDISPATCHCOMPUTEINDIRECTPROC gload_glDispatchComputeIndirect;
extern PFNGLCOPYIMAGESUBDATAPROC gload_glCopyImageSubData;
extern PFNGLFRAMEBUFFERPARAMETERIPROC gload_glFramebufferParameteri;
extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC gload_glGetFramebufferParameteriv;
extern PFNGLGETINTERNALFORMATI64VPROC gload_glGetInternalformati64v;
extern PFNGLINVALIDATETEXSUBIMAGEPROC gload_glInvalidateTexSubImage;
extern PFNGLINVALIDATETEXIMAGEPROC gload_glInvalidateTexImage;
extern PFNGLINVALIDATEBUFFERSUBDATAPROC gload_glInvalidateBufferSubData;
extern PFNGLINVALIDATEBUFFERDATAPROC gload_glInvalidateBufferData;
extern PFNGLINVALIDATEFRAMEBUFFERPROC gload_glInvalidateFramebuffer;
extern PFNGLINVALIDATESUBFRAMEBUFFERPROC gload_glInvalidateSubFramebuffer;
extern PFNGLMULTIDRAWARRAYSINDIRECTPROC gload_glMultiDrawArraysIndirect;
extern PFNGLMULTIDRAWELEMENTSINDIRECTPROC gload_glMultiDrawElementsIndirect;
extern PFNGLGETPROGRAMINTERFACEIVPROC gload_glGetProgramInterfaceiv;
extern PFNGLGETPROGRAMRESOURCEINDEXPROC gload_glGetProgramResourceIndex;
extern PFNGLGETPROGRAMRESOURCENAMEPROC gload_glGetProgramResourceName;
extern PFNGLGETPROGRAMRESOURCEIVPROC gload_glGetProgramResourceiv;
extern PFNGLGETPROGRAMRESOURCELOCATIONPROC gload_glGetProgramResourceLocation;
extern PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC gload_glGetProgramResourceLocationIndex;
extern PFNGLSHADERSTORAGEBLOCKBINDINGPROC gload_glShaderStorageBlockBinding;
extern PFNGLTEXBUFFERRANGEPROC gload_glTexBufferRange;
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC gload_glTexStorage2DMultisample;
extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC gload_glTexStorage3DMultisample;
extern PFNGLTEXTUREVIEWPROC gload_glTextureView;
extern PFNGLBINDVERTEXBUFFERPROC gload_glBindVertexBuffer;
extern PFNGLVERTEXATTRIBFORMATPROC gload_glVertexAttribFormat;
extern PFNGLVERTEXATTRIBIFORMATPROC gload_glVertexAttribIFormat;
extern PFNGLVERTEXATTRIBLFORMATPROC gload_glVertexAttribLFormat;
extern PFNGLVERTEXATTRIBBINDINGPROC gload_glVertexAttribBinding;
extern PFNGLVERTEXBINDINGDIVISORPROC gload_glVertexBindingDivisor;
extern PFNGLDEBUGMESSAGECONTROLPROC gload_glDebugMessageControl;
extern PFNGLDEBUGMESSAGEINSERTPROC gload_glDebugMessageInsert;
extern PFNGLDEBUGMESSAGECALLBACKPROC gload_glDebugMessageCallback;
extern PFNGLGETDEBUGMESSAGELOGPROC gload_glGetDebugMessageLog;
extern PFNGLPUSHDEBUGGROUPPROC gload_glPushDebugGroup;
extern PFNGLPOPDEBUGGROUPPROC gload_glPopDebugGroup;
extern PFNGLOBJECTLABELPROC gload_glObjectLabel;
extern PFNGLGETOBJECTLABELPROC gload_glGetObjectLabel;
extern PFNGLOBJECTPTRLABELPROC gload_glObjectPtrLabel;
extern PFNGLGETOBJECTPTRLABELPROC gload_glGetObjectPtrLabel;
extern PFNGLGETPOINTERVPROC gload_glGetPointerv;

# endif /* GL_VERSION_4_3 */
# if defined GL_VERSION_4_4

extern PFNGLBUFFERSTORAGEPROC gload_glBufferStorage;
extern PFNGLCLEARTEXIMAGEPROC gload_glClearTexImage;
extern PFNGLCLEARTEXSUBIMAGEPROC gload_glClearTexSubImage;
extern PFNGLBINDBUFFERSBASEPROC gload_glBindBuffersBase;
extern PFNGLBINDBUFFERSRANGEPROC gload_glBindBuffersRange;
extern PFNGLBINDTEXTURESPROC gload_glBindTextures;
extern PFNGLBINDSAMPLERSPROC gload_glBindSamplers;
extern PFNGLBINDIMAGETEXTURESPROC gload_glBindImageTextures;
extern PFNGLBINDVERTEXBUFFERSPROC gload_glBindVertexBuffers;

# endif /* GL_VERSION_4_4 */
# if defined GL_VERSION_4_5

extern PFNGLCLIPCONTROLPROC gload_glClipControl;
extern PFNGLCREATETRANSFORMFEEDBACKSPROC gload_glCreateTransformFeedbacks;
extern PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC gload_glTransformFeedbackBufferBase;
extern PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC gload_glTransformFeedbackBufferRange;
extern PFNGLGETTRANSFORMFEEDBACKIVPROC gload_glGetTransformFeedbackiv;
extern PFNGLGETTRANSFORMFEEDBACKI_VPROC gload_glGetTransformFeedbacki_v;
extern PFNGLGETTRANSFORMFEEDBACKI64_VPROC gload_glGetTransformFeedbacki64_v;
extern PFNGLCREATEBUFFERSPROC gload_glCreateBuffers;
extern PFNGLNAMEDBUFFERSTORAGEPROC gload_glNamedBufferStorage;
extern PFNGLNAMEDBUFFERDATAPROC gload_glNamedBufferData;
extern PFNGLNAMEDBUFFERSUBDATAPROC gload_glNamedBufferSubData;
extern PFNGLCOPYNAMEDBUFFERSUBDATAPROC gload_glCopyNamedBufferSubData;
extern PFNGLCLEARNAMEDBUFFERDATAPROC gload_glClearNamedBufferData;
extern PFNGLCLEARNAMEDBUFFERSUBDATAPROC gload_glClearNamedBufferSubData;
extern PFNGLMAPNAMEDBUFFERPROC gload_glMapNamedBuffer;
extern PFNGLMAPNAMEDBUFFERRANGEPROC gload_glMapNamedBufferRange;
extern PFNGLUNMAPNAMEDBUFFERPROC gload_glUnmapNamedBuffer;
extern PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC gload_glFlushMappedNamedBufferRange;
extern PFNGLGETNAMEDBUFFERPARAMETERIVPROC gload_glGetNamedBufferParameteriv;
extern PFNGLGETNAMEDBUFFERPARAMETERI64VPROC gload_glGetNamedBufferParameteri64v;
extern PFNGLGETNAMEDBUFFERPOINTERVPROC gload_glGetNamedBufferPointerv;
extern PFNGLGETNAMEDBUFFERSUBDATAPROC gload_glGetNamedBufferSubData;
extern PFNGLCREATEFRAMEBUFFERSPROC gload_glCreateFramebuffers;
extern PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC gload_glNamedFramebufferRenderbuffer;
extern PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC gload_glNamedFramebufferParameteri;
extern PFNGLNAMEDFRAMEBUFFERTEXTUREPROC gload_glNamedFramebufferTexture;
extern PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC gload_glNamedFramebufferTextureLayer;
extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC gload_glNamedFramebufferDrawBuffer;
extern PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC gload_glNamedFramebufferDrawBuffers;
extern PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC gload_glNamedFramebufferReadBuffer;
extern PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC gload_glInvalidateNamedFramebufferData;
extern PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC gload_glInvalidateNamedFramebufferSubData;
extern PFNGLCLEARNAMEDFRAMEBUFFERIVPROC gload_glClearNamedFramebufferiv;
extern PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC gload_glClearNamedFramebufferuiv;
extern PFNGLCLEARNAMEDFRAMEBUFFERFVPROC gload_glClearNamedFramebufferfv;
extern PFNGLCLEARNAMEDFRAMEBUFFERFIPROC gload_glClearNamedFramebufferfi;
extern PFNGLBLITNAMEDFRAMEBUFFERPROC gload_glBlitNamedFramebuffer;
extern PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC gload_glCheckNamedFramebufferStatus;
extern PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC gload_glGetNamedFramebufferParameteriv;
extern PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC gload_glGetNamedFramebufferAttachmentParameteriv;
extern PFNGLCREATERENDERBUFFERSPROC gload_glCreateRenderbuffers;
extern PFNGLNAMEDRENDERBUFFERSTORAGEPROC gload_glNamedRenderbufferStorage;
extern PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC gload_glNamedRenderbufferStorageMultisample;
extern PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC gload_glGetNamedRenderbufferParameteriv;
extern PFNGLCREATETEXTURESPROC gload_glCreateTextures;
extern PFNGLTEXTUREBUFFERPROC gload_glTextureBuffer;
extern PFNGLTEXTUREBUFFERRANGEPROC gload_glTextureBufferRange;
extern PFNGLTEXTURESTORAGE1DPROC gload_glTextureStorage1D;
extern PFNGLTEXTURESTORAGE2DPROC gload_glTextureStorage2D;
extern PFNGLTEXTURESTORAGE3DPROC gload_glTextureStorage3D;
extern PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC gload_glTextureStorage2DMultisample;
extern PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC gload_glTextureStorage3DMultisample;
extern PFNGLTEXTURESUBIMAGE1DPROC gload_glTextureSubImage1D;
extern PFNGLTEXTURESUBIMAGE2DPROC gload_glTextureSubImage2D;
extern PFNGLTEXTURESUBIMAGE3DPROC gload_glTextureSubImage3D;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC gload_glCompressedTextureSubImage1D;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC gload_glCompressedTextureSubImage2D;
extern PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC gload_glCompressedTextureSubImage3D;
extern PFNGLCOPYTEXTURESUBIMAGE1DPROC gload_glCopyTextureSubImage1D;
extern PFNGLCOPYTEXTURESUBIMAGE2DPROC gload_glCopyTextureSubImage2D;
extern PFNGLCOPYTEXTURESUBIMAGE3DPROC gload_glCopyTextureSubImage3D;
extern PFNGLTEXTUREPARAMETERFPROC gload_glTextureParameterf;
extern PFNGLTEXTUREPARAMETERFVPROC gload_glTextureParameterfv;
extern PFNGLTEXTUREPARAMETERIPROC gload_glTextureParameteri;
extern PFNGLTEXTUREPARAMETERIIVPROC gload_glTextureParameterIiv;
extern PFNGLTEXTUREPARAMETERIUIVPROC gload_glTextureParameterIuiv;
extern PFNGLTEXTUREPARAMETERIVPROC gload_glTextureParameteriv;
extern PFNGLGENERATETEXTUREMIPMAPPROC gload_glGenerateTextureMipmap;
extern PFNGLBINDTEXTUREUNITPROC gload_glBindTextureUnit;
extern PFNGLGETTEXTUREIMAGEPROC gload_glGetTextureImage;
extern PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC gload_glGetCompressedTextureImage;
extern PFNGLGETTEXTURELEVELPARAMETERFVPROC gload_glGetTextureLevelParameterfv;
extern PFNGLGETTEXTURELEVELPARAMETERIVPROC gload_glGetTextureLevelParameteriv;
extern PFNGLGETTEXTUREPARAMETERFVPROC gload_glGetTextureParameterfv;
extern PFNGLGETTEXTUREPARAMETERIIVPROC gload_glGetTextureParameterIiv;
extern PFNGLGETTEXTUREPARAMETERIUIVPROC gload_glGetTextureParameterIuiv;
extern PFNGLGETTEXTUREPARAMETERIVPROC gload_glGetTextureParameteriv;
extern PFNGLCREATEVERTEXARRAYSPROC gload_glCreateVertexArrays;
extern PFNGLDISABLEVERTEXARRAYATTRIBPROC gload_glDisableVertexArrayAttrib;
extern PFNGLENABLEVERTEXARRAYATTRIBPROC gload_glEnableVertexArrayAttrib;
extern PFNGLVERTEXARRAYELEMENTBUFFERPROC gload_glVertexArrayElementBuffer;
extern PFNGLVERTEXARRAYVERTEXBUFFERPROC gload_glVertexArrayVertexBuffer;
extern PFNGLVERTEXARRAYVERTEXBUFFERSPROC gload_glVertexArrayVertexBuffers;
extern PFNGLVERTEXARRAYATTRIBBINDINGPROC gload_glVertexArrayAttribBinding;
extern PFNGLVERTEXARRAYATTRIBFORMATPROC gload_glVertexArrayAttribFormat;
extern PFNGLVERTEXARRAYATTRIBIFORMATPROC gload_glVertexArrayAttribIFormat;
extern PFNGLVERTEXARRAYATTRIBLFORMATPROC gload_glVertexArrayAttribLFormat;
extern PFNGLVERTEXARRAYBINDINGDIVISORPROC gload_glVertexArrayBindingDivisor;
extern PFNGLGETVERTEXARRAYIVPROC gload_glGetVertexArrayiv;
extern PFNGLGETVERTEXARRAYINDEXEDIVPROC gload_glGetVertexArrayIndexediv;
extern PFNGLGETVERTEXARRAYINDEXED64IVPROC gload_glGetVertexArrayIndexed64iv;
extern PFNGLCREATESAMPLERSPROC gload_glCreateSamplers;
extern PFNGLCREATEPROGRAMPIPELINESPROC gload_glCreateProgramPipelines;
extern PFNGLCREATEQUERIESPROC gload_glCreateQueries;
extern PFNGLGETQUERYBUFFEROBJECTI64VPROC gload_glGetQueryBufferObjecti64v;
extern PFNGLGETQUERYBUFFEROBJECTIVPROC gload_glGetQueryBufferObjectiv;
extern PFNGLGETQUERYBUFFEROBJECTUI64VPROC gload_glGetQueryBufferObjectui64v;
extern PFNGLGETQUERYBUFFEROBJECTUIVPROC gload_glGetQueryBufferObjectuiv;
extern PFNGLMEMORYBARRIERBYREGIONPROC gload_glMemoryBarrierByRegion;
extern PFNGLGETTEXTURESUBIMAGEPROC gload_glGetTextureSubImage;
extern PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC gload_glGetCompressedTextureSubImage;
extern PFNGLGETGRAPHICSRESETSTATUSPROC gload_glGetGraphicsResetStatus;
extern PFNGLGETNCOMPRESSEDTEXIMAGEPROC gload_glGetnCompressedTexImage;
extern PFNGLGETNTEXIMAGEPROC gload_glGetnTexImage;
extern PFNGLGETNUNIFORMDVPROC gload_glGetnUniformdv;
extern PFNGLGETNUNIFORMFVPROC gload_glGetnUniformfv;
extern PFNGLGETNUNIFORMIVPROC gload_glGetnUniformiv;
extern PFNGLGETNUNIFORMUIVPROC gload_glGetnUniformuiv;
extern PFNGLREADNPIXELSPROC gload_glReadnPixels;
extern PFNGLGETNMAPDVPROC gload_glGetnMapdv;
extern PFNGLGETNMAPFVPROC gload_glGetnMapfv;
extern PFNGLGETNMAPIVPROC gload_glGetnMapiv;
extern PFNGLGETNPIXELMAPFVPROC gload_glGetnPixelMapfv;
extern PFNGLGETNPIXELMAPUIVPROC gload_glGetnPixelMapuiv;
extern PFNGLGETNPIXELMAPUSVPROC gload_glGetnPixelMapusv;
extern PFNGLGETNPOLYGONSTIPPLEPROC gload_glGetnPolygonStipple;
extern PFNGLGETNCOLORTABLEPROC gload_glGetnColorTable;
extern PFNGLGETNCONVOLUTIONFILTERPROC gload_glGetnConvolutionFilter;
extern PFNGLGETNSEPARABLEFILTERPROC gload_glGetnSeparableFilter;
extern PFNGLGETNHISTOGRAMPROC gload_glGetnHistogram;
extern PFNGLGETNMINMAXPROC gload_glGetnMinmax;
extern PFNGLTEXTUREBARRIERPROC gload_glTextureBarrier;

# endif /* GL_VERSION_4_5 */
# if defined GL_VERSION_4_6

extern PFNGLSPECIALIZESHADERPROC gload_glSpecializeShader;
extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC gload_glMultiDrawArraysIndirectCount;
extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC gload_glMultiDrawElementsIndirectCount;
extern PFNGLPOLYGONOFFSETCLAMPPROC gload_glPolygonOffsetClamp;

# endif /* GL_VERSION_4_6 */
# if defined GL_VERSION_ES_CM_1_0

extern PFNGLALPHAFUNCPROC gload_glAlphaFunc;
extern PFNGLCLEARCOLORPROC gload_glClearColor;
extern PFNGLCLEARDEPTHFPROC gload_glClearDepthf;
extern PFNGLCLIPPLANEFPROC gload_glClipPlanef;
extern PFNGLCOLOR4FPROC gload_glColor4f;
extern PFNGLDEPTHRANGEFPROC gload_glDepthRangef;
extern PFNGLFOGFPROC gload_glFogf;
extern PFNGLFOGFVPROC gload_glFogfv;
extern PFNGLFRUSTUMFPROC gload_glFrustumf;
extern PFNGLGETCLIPPLANEFPROC gload_glGetClipPlanef;
extern PFNGLGETFLOATVPROC gload_glGetFloatv;
extern PFNGLGETLIGHTFVPROC gload_glGetLightfv;
extern PFNGLGETMATERIALFVPROC gload_glGetMaterialfv;
extern PFNGLGETTEXENVFVPROC gload_glGetTexEnvfv;
extern PFNGLGETTEXPARAMETERFVPROC gload_glGetTexParameterfv;
extern PFNGLLIGHTMODELFPROC gload_glLightModelf;
extern PFNGLLIGHTMODELFVPROC gload_glLightModelfv;
extern PFNGLLIGHTFPROC gload_glLightf;
extern PFNGLLIGHTFVPROC gload_glLightfv;
extern PFNGLLINEWIDTHPROC gload_glLineWidth;
extern PFNGLLOADMATRIXFPROC gload_glLoadMatrixf;
extern PFNGLMATERIALFPROC gload_glMaterialf;
extern PFNGLMATERIALFVPROC gload_glMaterialfv;
extern PFNGLMULTMATRIXFPROC gload_glMultMatrixf;
extern PFNGLMULTITEXCOORD4FPROC gload_glMultiTexCoord4f;
extern PFNGLNORMAL3FPROC gload_glNormal3f;
extern PFNGLORTHOFPROC gload_glOrthof;
extern PFNGLPOINTPARAMETERFPROC gload_glPointParameterf;
extern PFNGLPOINTPARAMETERFVPROC gload_glPointParameterfv;
extern PFNGLPOINTSIZEPROC gload_glPointSize;
extern PFNGLPOLYGONOFFSETPROC gload_glPolygonOffset;
extern PFNGLROTATEFPROC gload_glRotatef;
extern PFNGLSCALEFPROC gload_glScalef;
extern PFNGLTEXENVFPROC gload_glTexEnvf;
extern PFNGLTEXENVFVPROC gload_glTexEnvfv;
extern PFNGLTEXPARAMETERFPROC gload_glTexParameterf;
extern PFNGLTEXPARAMETERFVPROC gload_glTexParameterfv;
extern PFNGLTRANSLATEFPROC gload_glTranslatef;
extern PFNGLACTIVETEXTUREPROC gload_glActiveTexture;
extern PFNGLALPHAFUNCXPROC gload_glAlphaFuncx;
extern PFNGLBINDBUFFERPROC gload_glBindBuffer;
extern PFNGLBINDTEXTUREPROC gload_glBindTexture;
extern PFNGLBLENDFUNCPROC gload_glBlendFunc;
extern PFNGLBUFFERDATAPROC gload_glBufferData;
extern PFNGLBUFFERSUBDATAPROC gload_glBufferSubData;
extern PFNGLCLEARPROC gload_glClear;
extern PFNGLCLEARCOLORXPROC gload_glClearColorx;
extern PFNGLCLEARDEPTHXPROC gload_glClearDepthx;
extern PFNGLCLEARSTENCILPROC gload_glClearStencil;
extern PFNGLCLIENTACTIVETEXTUREPROC gload_glClientActiveTexture;
extern PFNGLCLIPPLANEXPROC gload_glClipPlanex;
extern PFNGLCOLOR4UBPROC gload_glColor4ub;
extern PFNGLCOLOR4XPROC gload_glColor4x;
extern PFNGLCOLORMASKPROC gload_glColorMask;
extern PFNGLCOLORPOINTERPROC gload_glColorPointer;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC gload_glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC gload_glCompressedTexSubImage2D;
extern PFNGLCOPYTEXIMAGE2DPROC gload_glCopyTexImage2D;
extern PFNGLCOPYTEXSUBIMAGE2DPROC gload_glCopyTexSubImage2D;
extern PFNGLCULLFACEPROC gload_glCullFace;
extern PFNGLDELETEBUFFERSPROC gload_glDeleteBuffers;
extern PFNGLDELETETEXTURESPROC gload_glDeleteTextures;
extern PFNGLDEPTHFUNCPROC gload_glDepthFunc;
extern PFNGLDEPTHMASKPROC gload_glDepthMask;
extern PFNGLDEPTHRANGEXPROC gload_glDepthRangex;
extern PFNGLDISABLEPROC gload_glDisable;
extern PFNGLDISABLECLIENTSTATEPROC gload_glDisableClientState;
extern PFNGLDRAWARRAYSPROC gload_glDrawArrays;
extern PFNGLDRAWELEMENTSPROC gload_glDrawElements;
extern PFNGLENABLEPROC gload_glEnable;
extern PFNGLENABLECLIENTSTATEPROC gload_glEnableClientState;
extern PFNGLFINISHPROC gload_glFinish;
extern PFNGLFLUSHPROC gload_glFlush;
extern PFNGLFOGXPROC gload_glFogx;
extern PFNGLFOGXVPROC gload_glFogxv;
extern PFNGLFRONTFACEPROC gload_glFrontFace;
extern PFNGLFRUSTUMXPROC gload_glFrustumx;
extern PFNGLGETBOOLEANVPROC gload_glGetBooleanv;
extern PFNGLGETBUFFERPARAMETERIVPROC gload_glGetBufferParameteriv;
extern PFNGLGETCLIPPLANEXPROC gload_glGetClipPlanex;
extern PFNGLGENBUFFERSPROC gload_glGenBuffers;
extern PFNGLGENTEXTURESPROC gload_glGenTextures;
extern PFNGLGETERRORPROC gload_glGetError;
extern PFNGLGETFIXEDVPROC gload_glGetFixedv;
extern PFNGLGETINTEGERVPROC gload_glGetIntegerv;
extern PFNGLGETLIGHTXVPROC gload_glGetLightxv;
extern PFNGLGETMATERIALXVPROC gload_glGetMaterialxv;
extern PFNGLGETPOINTERVPROC gload_glGetPointerv;
extern PFNGLGETSTRINGPROC gload_glGetString;
extern PFNGLGETTEXENVIVPROC gload_glGetTexEnviv;
extern PFNGLGETTEXENVXVPROC gload_glGetTexEnvxv;
extern PFNGLGETTEXPARAMETERIVPROC gload_glGetTexParameteriv;
extern PFNGLGETTEXPARAMETERXVPROC gload_glGetTexParameterxv;
extern PFNGLHINTPROC gload_glHint;
extern PFNGLISBUFFERPROC gload_glIsBuffer;
extern PFNGLISENABLEDPROC gload_glIsEnabled;
extern PFNGLISTEXTUREPROC gload_glIsTexture;
extern PFNGLLIGHTMODELXPROC gload_glLightModelx;
extern PFNGLLIGHTMODELXVPROC gload_glLightModelxv;
extern PFNGLLIGHTXPROC gload_glLightx;
extern PFNGLLIGHTXVPROC gload_glLightxv;
extern PFNGLLINEWIDTHXPROC gload_glLineWidthx;
extern PFNGLLOADIDENTITYPROC gload_glLoadIdentity;
extern PFNGLLOADMATRIXXPROC gload_glLoadMatrixx;
extern PFNGLLOGICOPPROC gload_glLogicOp;
extern PFNGLMATERIALXPROC gload_glMaterialx;
extern PFNGLMATERIALXVPROC gload_glMaterialxv;
extern PFNGLMATRIXMODEPROC gload_glMatrixMode;
extern PFNGLMULTMATRIXXPROC gload_glMultMatrixx;
extern PFNGLMULTITEXCOORD4XPROC gload_glMultiTexCoord4x;
extern PFNGLNORMAL3XPROC gload_glNormal3x;
extern PFNGLNORMALPOINTERPROC gload_glNormalPointer;
extern PFNGLORTHOXPROC gload_glOrthox;
extern PFNGLPIXELSTOREIPROC gload_glPixelStorei;
extern PFNGLPOINTPARAMETERXPROC gload_glPointParameterx;
extern PFNGLPOINTPARAMETERXVPROC gload_glPointParameterxv;
extern PFNGLPOINTSIZEXPROC gload_glPointSizex;
extern PFNGLPOLYGONOFFSETXPROC gload_glPolygonOffsetx;
extern PFNGLPOPMATRIXPROC gload_glPopMatrix;
extern PFNGLPUSHMATRIXPROC gload_glPushMatrix;
extern PFNGLREADPIXELSPROC gload_glReadPixels;
extern PFNGLROTATEXPROC gload_glRotatex;
extern PFNGLSAMPLECOVERAGEPROC gload_glSampleCoverage;
extern PFNGLSAMPLECOVERAGEXPROC gload_glSampleCoveragex;
extern PFNGLSCALEXPROC gload_glScalex;
extern PFNGLSCISSORPROC gload_glScissor;
extern PFNGLSHADEMODELPROC gload_glShadeModel;
extern PFNGLSTENCILFUNCPROC gload_glStencilFunc;
extern PFNGLSTENCILMASKPROC gload_glStencilMask;
extern PFNGLSTENCILOPPROC gload_glStencilOp;
extern PFNGLTEXCOORDPOINTERPROC gload_glTexCoordPointer;
extern PFNGLTEXENVIPROC gload_glTexEnvi;
extern PFNGLTEXENVXPROC gload_glTexEnvx;
extern PFNGLTEXENVIVPROC gload_glTexEnviv;
extern PFNGLTEXENVXVPROC gload_glTexEnvxv;
extern PFNGLTEXIMAGE2DPROC gload_glTexImage2D;
extern PFNGLTEXPARAMETERIPROC gload_glTexParameteri;
extern PFNGLTEXPARAMETERXPROC gload_glTexParameterx;
extern PFNGLTEXPARAMETERIVPROC gload_glTexParameteriv;
extern PFNGLTEXPARAMETERXVPROC gload_glTexParameterxv;
extern PFNGLTEXSUBIMAGE2DPROC gload_glTexSubImage2D;
extern PFNGLTRANSLATEXPROC gload_glTranslatex;
extern PFNGLVERTEXPOINTERPROC gload_glVertexPointer;
extern PFNGLVIEWPORTPROC gload_glViewport;

# endif /* GL_VERSION_ES_CM_1_0 */
# if defined GL_ES_VERSION_2_0

extern PFNGLACTIVETEXTUREPROC gload_glActiveTexture;
extern PFNGLATTACHSHADERPROC gload_glAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC gload_glBindAttribLocation;
extern PFNGLBINDBUFFERPROC gload_glBindBuffer;
extern PFNGLBINDFRAMEBUFFERPROC gload_glBindFramebuffer;
extern PFNGLBINDRENDERBUFFERPROC gload_glBindRenderbuffer;
extern PFNGLBINDTEXTUREPROC gload_glBindTexture;
extern PFNGLBLENDCOLORPROC gload_glBlendColor;
extern PFNGLBLENDEQUATIONPROC gload_glBlendEquation;
extern PFNGLBLENDEQUATIONSEPARATEPROC gload_glBlendEquationSeparate;
extern PFNGLBLENDFUNCPROC gload_glBlendFunc;
extern PFNGLBLENDFUNCSEPARATEPROC gload_glBlendFuncSeparate;
extern PFNGLBUFFERDATAPROC gload_glBufferData;
extern PFNGLBUFFERSUBDATAPROC gload_glBufferSubData;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC gload_glCheckFramebufferStatus;
extern PFNGLCLEARPROC gload_glClear;
extern PFNGLCLEARCOLORPROC gload_glClearColor;
extern PFNGLCLEARDEPTHFPROC gload_glClearDepthf;
extern PFNGLCLEARSTENCILPROC gload_glClearStencil;
extern PFNGLCOLORMASKPROC gload_glColorMask;
extern PFNGLCOMPILESHADERPROC gload_glCompileShader;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC gload_glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC gload_glCompressedTexSubImage2D;
extern PFNGLCOPYTEXIMAGE2DPROC gload_glCopyTexImage2D;
extern PFNGLCOPYTEXSUBIMAGE2DPROC gload_glCopyTexSubImage2D;
extern PFNGLCREATEPROGRAMPROC gload_glCreateProgram;
extern PFNGLCREATESHADERPROC gload_glCreateShader;
extern PFNGLCULLFACEPROC gload_glCullFace;
extern PFNGLDELETEBUFFERSPROC gload_glDeleteBuffers;
extern PFNGLDELETEFRAMEBUFFERSPROC gload_glDeleteFramebuffers;
extern PFNGLDELETEPROGRAMPROC gload_glDeleteProgram;
extern PFNGLDELETERENDERBUFFERSPROC gload_glDeleteRenderbuffers;
extern PFNGLDELETESHADERPROC gload_glDeleteShader;
extern PFNGLDELETETEXTURESPROC gload_glDeleteTextures;
extern PFNGLDEPTHFUNCPROC gload_glDepthFunc;
extern PFNGLDEPTHMASKPROC gload_glDepthMask;
extern PFNGLDEPTHRANGEFPROC gload_glDepthRangef;
extern PFNGLDETACHSHADERPROC gload_glDetachShader;
extern PFNGLDISABLEPROC gload_glDisable;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC gload_glDisableVertexAttribArray;
extern PFNGLDRAWARRAYSPROC gload_glDrawArrays;
extern PFNGLDRAWELEMENTSPROC gload_glDrawElements;
extern PFNGLENABLEPROC gload_glEnable;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC gload_glEnableVertexAttribArray;
extern PFNGLFINISHPROC gload_glFinish;
extern PFNGLFLUSHPROC gload_glFlush;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC gload_glFramebufferRenderbuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC gload_glFramebufferTexture2D;
extern PFNGLFRONTFACEPROC gload_glFrontFace;
extern PFNGLGENBUFFERSPROC gload_glGenBuffers;
extern PFNGLGENERATEMIPMAPPROC gload_glGenerateMipmap;
extern PFNGLGENFRAMEBUFFERSPROC gload_glGenFramebuffers;
extern PFNGLGENRENDERBUFFERSPROC gload_glGenRenderbuffers;
extern PFNGLGENTEXTURESPROC gload_glGenTextures;
extern PFNGLGETACTIVEATTRIBPROC gload_glGetActiveAttrib;
extern PFNGLGETACTIVEUNIFORMPROC gload_glGetActiveUniform;
extern PFNGLGETATTACHEDSHADERSPROC gload_glGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC gload_glGetAttribLocation;
extern PFNGLGETBOOLEANVPROC gload_glGetBooleanv;
extern PFNGLGETBUFFERPARAMETERIVPROC gload_glGetBufferParameteriv;
extern PFNGLGETERRORPROC gload_glGetError;
extern PFNGLGETFLOATVPROC gload_glGetFloatv;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC gload_glGetFramebufferAttachmentParameteriv;
extern PFNGLGETINTEGERVPROC gload_glGetIntegerv;
extern PFNGLGETPROGRAMIVPROC gload_glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC gload_glGetProgramInfoLog;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC gload_glGetRenderbufferParameteriv;
extern PFNGLGETSHADERIVPROC gload_glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC gload_glGetShaderInfoLog;
extern PFNGLGETSHADERPRECISIONFORMATPROC gload_glGetShaderPrecisionFormat;
extern PFNGLGETSHADERSOURCEPROC gload_glGetShaderSource;
extern PFNGLGETSTRINGPROC gload_glGetString;
extern PFNGLGETTEXPARAMETERFVPROC gload_glGetTexParameterfv;
extern PFNGLGETTEXPARAMETERIVPROC gload_glGetTexParameteriv;
extern PFNGLGETUNIFORMFVPROC gload_glGetUniformfv;
extern PFNGLGETUNIFORMIVPROC gload_glGetUniformiv;
extern PFNGLGETUNIFORMLOCATIONPROC gload_glGetUniformLocation;
extern PFNGLGETVERTEXATTRIBFVPROC gload_glGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC gload_glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC gload_glGetVertexAttribPointerv;
extern PFNGLHINTPROC gload_glHint;
extern PFNGLISBUFFERPROC gload_glIsBuffer;
extern PFNGLISENABLEDPROC gload_glIsEnabled;
extern PFNGLISFRAMEBUFFERPROC gload_glIsFramebuffer;
extern PFNGLISPROGRAMPROC gload_glIsProgram;
extern PFNGLISRENDERBUFFERPROC gload_glIsRenderbuffer;
extern PFNGLISSHADERPROC gload_glIsShader;
extern PFNGLISTEXTUREPROC gload_glIsTexture;
extern PFNGLLINEWIDTHPROC gload_glLineWidth;
extern PFNGLLINKPROGRAMPROC gload_glLinkProgram;
extern PFNGLPIXELSTOREIPROC gload_glPixelStorei;
extern PFNGLPOLYGONOFFSETPROC gload_glPolygonOffset;
extern PFNGLREADPIXELSPROC gload_glReadPixels;
extern PFNGLRELEASESHADERCOMPILERPROC gload_glReleaseShaderCompiler;
extern PFNGLRENDERBUFFERSTORAGEPROC gload_glRenderbufferStorage;
extern PFNGLSAMPLECOVERAGEPROC gload_glSampleCoverage;
extern PFNGLSCISSORPROC gload_glScissor;
extern PFNGLSHADERBINARYPROC gload_glShaderBinary;
extern PFNGLSHADERSOURCEPROC gload_glShaderSource;
extern PFNGLSTENCILFUNCPROC gload_glStencilFunc;
extern PFNGLSTENCILFUNCSEPARATEPROC gload_glStencilFuncSeparate;
extern PFNGLSTENCILMASKPROC gload_glStencilMask;
extern PFNGLSTENCILMASKSEPARATEPROC gload_glStencilMaskSeparate;
extern PFNGLSTENCILOPPROC gload_glStencilOp;
extern PFNGLSTENCILOPSEPARATEPROC gload_glStencilOpSeparate;
extern PFNGLTEXIMAGE2DPROC gload_glTexImage2D;
extern PFNGLTEXPARAMETERFPROC gload_glTexParameterf;
extern PFNGLTEXPARAMETERFVPROC gload_glTexParameterfv;
extern PFNGLTEXPARAMETERIPROC gload_glTexParameteri;
extern PFNGLTEXPARAMETERIVPROC gload_glTexParameteriv;
extern PFNGLTEXSUBIMAGE2DPROC gload_glTexSubImage2D;
extern PFNGLUNIFORM1FPROC gload_glUniform1f;
extern PFNGLUNIFORM1FVPROC gload_glUniform1fv;
extern PFNGLUNIFORM1IPROC gload_glUniform1i;
extern PFNGLUNIFORM1IVPROC gload_glUniform1iv;
extern PFNGLUNIFORM2FPROC gload_glUniform2f;
extern PFNGLUNIFORM2FVPROC gload_glUniform2fv;
extern PFNGLUNIFORM2IPROC gload_glUniform2i;
extern PFNGLUNIFORM2IVPROC gload_glUniform2iv;
extern PFNGLUNIFORM3FPROC gload_glUniform3f;
extern PFNGLUNIFORM3FVPROC gload_glUniform3fv;
extern PFNGLUNIFORM3IPROC gload_glUniform3i;
extern PFNGLUNIFORM3IVPROC gload_glUniform3iv;
extern PFNGLUNIFORM4FPROC gload_glUniform4f;
extern PFNGLUNIFORM4FVPROC gload_glUniform4fv;
extern PFNGLUNIFORM4IPROC gload_glUniform4i;
extern PFNGLUNIFORM4IVPROC gload_glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC gload_glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC gload_glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC gload_glUniformMatrix4fv;
extern PFNGLUSEPROGRAMPROC gload_glUseProgram;
extern PFNGLVALIDATEPROGRAMPROC gload_glValidateProgram;
extern PFNGLVERTEXATTRIB1FPROC gload_glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC gload_glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB2FPROC gload_glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC gload_glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB3FPROC gload_glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC gload_glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB4FPROC gload_glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC gload_glVertexAttrib4fv;
extern PFNGLVERTEXATTRIBPOINTERPROC gload_glVertexAttribPointer;
extern PFNGLVIEWPORTPROC gload_glViewport;

# endif /* GL_ES_VERSION_2_0 */
# if defined GL_ES_VERSION_3_0

extern PFNGLREADBUFFERPROC gload_glReadBuffer;
extern PFNGLDRAWRANGEELEMENTSPROC gload_glDrawRangeElements;
extern PFNGLTEXIMAGE3DPROC gload_glTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC gload_glTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC gload_glCopyTexSubImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC gload_glCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC gload_glCompressedTexSubImage3D;
extern PFNGLGENQUERIESPROC gload_glGenQueries;
extern PFNGLDELETEQUERIESPROC gload_glDeleteQueries;
extern PFNGLISQUERYPROC gload_glIsQuery;
extern PFNGLBEGINQUERYPROC gload_glBeginQuery;
extern PFNGLENDQUERYPROC gload_glEndQuery;
extern PFNGLGETQUERYIVPROC gload_glGetQueryiv;
extern PFNGLGETQUERYOBJECTUIVPROC gload_glGetQueryObjectuiv;
extern PFNGLUNMAPBUFFERPROC gload_glUnmapBuffer;
extern PFNGLGETBUFFERPOINTERVPROC gload_glGetBufferPointerv;
extern PFNGLDRAWBUFFERSPROC gload_glDrawBuffers;
extern PFNGLUNIFORMMATRIX2X3FVPROC gload_glUniformMatrix2x3fv;
extern PFNGLUNIFORMMATRIX3X2FVPROC gload_glUniformMatrix3x2fv;
extern PFNGLUNIFORMMATRIX2X4FVPROC gload_glUniformMatrix2x4fv;
extern PFNGLUNIFORMMATRIX4X2FVPROC gload_glUniformMatrix4x2fv;
extern PFNGLUNIFORMMATRIX3X4FVPROC gload_glUniformMatrix3x4fv;
extern PFNGLUNIFORMMATRIX4X3FVPROC gload_glUniformMatrix4x3fv;
extern PFNGLBLITFRAMEBUFFERPROC gload_glBlitFramebuffer;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC gload_glRenderbufferStorageMultisample;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC gload_glFramebufferTextureLayer;
extern PFNGLMAPBUFFERRANGEPROC gload_glMapBufferRange;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC gload_glFlushMappedBufferRange;
extern PFNGLBINDVERTEXARRAYPROC gload_glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC gload_glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC gload_glGenVertexArrays;
extern PFNGLISVERTEXARRAYPROC gload_glIsVertexArray;
extern PFNGLGETINTEGERI_VPROC gload_glGetIntegeri_v;
extern PFNGLBEGINTRANSFORMFEEDBACKPROC gload_glBeginTransformFeedback;
extern PFNGLENDTRANSFORMFEEDBACKPROC gload_glEndTransformFeedback;
extern PFNGLBINDBUFFERRANGEPROC gload_glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC gload_glBindBufferBase;
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC gload_glTransformFeedbackVaryings;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC gload_glGetTransformFeedbackVarying;
extern PFNGLVERTEXATTRIBIPOINTERPROC gload_glVertexAttribIPointer;
extern PFNGLGETVERTEXATTRIBIIVPROC gload_glGetVertexAttribIiv;
extern PFNGLGETVERTEXATTRIBIUIVPROC gload_glGetVertexAttribIuiv;
extern PFNGLVERTEXATTRIBI4IPROC gload_glVertexAttribI4i;
extern PFNGLVERTEXATTRIBI4UIPROC gload_glVertexAttribI4ui;
extern PFNGLVERTEXATTRIBI4IVPROC gload_glVertexAttribI4iv;
extern PFNGLVERTEXATTRIBI4UIVPROC gload_glVertexAttribI4uiv;
extern PFNGLGETUNIFORMUIVPROC gload_glGetUniformuiv;
extern PFNGLGETFRAGDATALOCATIONPROC gload_glGetFragDataLocation;
extern PFNGLUNIFORM1UIPROC gload_glUniform1ui;
extern PFNGLUNIFORM2UIPROC gload_glUniform2ui;
extern PFNGLUNIFORM3UIPROC gload_glUniform3ui;
extern PFNGLUNIFORM4UIPROC gload_glUniform4ui;
extern PFNGLUNIFORM1UIVPROC gload_glUniform1uiv;
extern PFNGLUNIFORM2UIVPROC gload_glUniform2uiv;
extern PFNGLUNIFORM3UIVPROC gload_glUniform3uiv;
extern PFNGLUNIFORM4UIVPROC gload_glUniform4uiv;
extern PFNGLCLEARBUFFERIVPROC gload_glClearBufferiv;
extern PFNGLCLEARBUFFERUIVPROC gload_glClearBufferuiv;
extern PFNGLCLEARBUFFERFVPROC gload_glClearBufferfv;
extern PFNGLCLEARBUFFERFIPROC gload_glClearBufferfi;
extern PFNGLGETSTRINGIPROC gload_glGetStringi;
extern PFNGLCOPYBUFFERSUBDATAPROC gload_glCopyBufferSubData;
extern PFNGLGETUNIFORMINDICESPROC gload_glGetUniformIndices;
extern PFNGLGETACTIVEUNIFORMSIVPROC gload_glGetActiveUniformsiv;
extern PFNGLGETUNIFORMBLOCKINDEXPROC gload_glGetUniformBlockIndex;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC gload_glGetActiveUniformBlockiv;
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC gload_glGetActiveUniformBlockName;
extern PFNGLUNIFORMBLOCKBINDINGPROC gload_glUniformBlockBinding;
extern PFNGLDRAWARRAYSINSTANCEDPROC gload_glDrawArraysInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDPROC gload_glDrawElementsInstanced;
extern PFNGLFENCESYNCPROC gload_glFenceSync;
extern PFNGLISSYNCPROC gload_glIsSync;
extern PFNGLDELETESYNCPROC gload_glDeleteSync;
extern PFNGLCLIENTWAITSYNCPROC gload_glClientWaitSync;
extern PFNGLWAITSYNCPROC gload_glWaitSync;
extern PFNGLGETINTEGER64VPROC gload_glGetInteger64v;
extern PFNGLGETSYNCIVPROC gload_glGetSynciv;
extern PFNGLGETINTEGER64I_VPROC gload_glGetInteger64i_v;
extern PFNGLGETBUFFERPARAMETERI64VPROC gload_glGetBufferParameteri64v;
extern PFNGLGENSAMPLERSPROC gload_glGenSamplers;
extern PFNGLDELETESAMPLERSPROC gload_glDeleteSamplers;
extern PFNGLISSAMPLERPROC gload_glIsSampler;
extern PFNGLBINDSAMPLERPROC gload_glBindSampler;
extern PFNGLSAMPLERPARAMETERIPROC gload_glSamplerParameteri;
extern PFNGLSAMPLERPARAMETERIVPROC gload_glSamplerParameteriv;
extern PFNGLSAMPLERPARAMETERFPROC gload_glSamplerParameterf;
extern PFNGLSAMPLERPARAMETERFVPROC gload_glSamplerParameterfv;
extern PFNGLGETSAMPLERPARAMETERIVPROC gload_glGetSamplerParameteriv;
extern PFNGLGETSAMPLERPARAMETERFVPROC gload_glGetSamplerParameterfv;
extern PFNGLVERTEXATTRIBDIVISORPROC gload_glVertexAttribDivisor;
extern PFNGLBINDTRANSFORMFEEDBACKPROC gload_glBindTransformFeedback;
extern PFNGLDELETETRANSFORMFEEDBACKSPROC gload_glDeleteTransformFeedbacks;
extern PFNGLGENTRANSFORMFEEDBACKSPROC gload_glGenTransformFeedbacks;
extern PFNGLISTRANSFORMFEEDBACKPROC gload_glIsTransformFeedback;
extern PFNGLPAUSETRANSFORMFEEDBACKPROC gload_glPauseTransformFeedback;
extern PFNGLRESUMETRANSFORMFEEDBACKPROC gload_glResumeTransformFeedback;
extern PFNGLGETPROGRAMBINARYPROC gload_glGetProgramBinary;
extern PFNGLPROGRAMBINARYPROC gload_glProgramBinary;
extern PFNGLPROGRAMPARAMETERIPROC gload_glProgramParameteri;
extern PFNGLINVALIDATEFRAMEBUFFERPROC gload_glInvalidateFramebuffer;
extern PFNGLINVALIDATESUBFRAMEBUFFERPROC gload_glInvalidateSubFramebuffer;
extern PFNGLTEXSTORAGE2DPROC gload_glTexStorage2D;
extern PFNGLTEXSTORAGE3DPROC gload_glTexStorage3D;
extern PFNGLGETINTERNALFORMATIVPROC gload_glGetInternalformativ;

# endif /* GL_ES_VERSION_3_0 */
# if defined GL_ES_VERSION_3_1

extern PFNGLDISPATCHCOMPUTEPROC gload_glDispatchCompute;
extern PFNGLDISPATCHCOMPUTEINDIRECTPROC gload_glDispatchComputeIndirect;
extern PFNGLDRAWARRAYSINDIRECTPROC gload_glDrawArraysIndirect;
extern PFNGLDRAWELEMENTSINDIRECTPROC gload_glDrawElementsIndirect;
extern PFNGLFRAMEBUFFERPARAMETERIPROC gload_glFramebufferParameteri;
extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC gload_glGetFramebufferParameteriv;
extern PFNGLGETPROGRAMINTERFACEIVPROC gload_glGetProgramInterfaceiv;
extern PFNGLGETPROGRAMRESOURCEINDEXPROC gload_glGetProgramResourceIndex;
extern PFNGLGETPROGRAMRESOURCENAMEPROC gload_glGetProgramResourceName;
extern PFNGLGETPROGRAMRESOURCEIVPROC gload_glGetProgramResourceiv;
extern PFNGLGETPROGRAMRESOURCELOCATIONPROC gload_glGetProgramResourceLocation;
extern PFNGLUSEPROGRAMSTAGESPROC gload_glUseProgramStages;
extern PFNGLACTIVESHADERPROGRAMPROC gload_glActiveShaderProgram;
extern PFNGLCREATESHADERPROGRAMVPROC gload_glCreateShaderProgramv;
extern PFNGLBINDPROGRAMPIPELINEPROC gload_glBindProgramPipeline;
extern PFNGLDELETEPROGRAMPIPELINESPROC gload_glDeleteProgramPipelines;
extern PFNGLGENPROGRAMPIPELINESPROC gload_glGenProgramPipelines;
extern PFNGLISPROGRAMPIPELINEPROC gload_glIsProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEIVPROC gload_glGetProgramPipelineiv;
extern PFNGLPROGRAMUNIFORM1IPROC gload_glProgramUniform1i;
extern PFNGLPROGRAMUNIFORM2IPROC gload_glProgramUniform2i;
extern PFNGLPROGRAMUNIFORM3IPROC gload_glProgramUniform3i;
extern PFNGLPROGRAMUNIFORM4IPROC gload_glProgramUniform4i;
extern PFNGLPROGRAMUNIFORM1UIPROC gload_glProgramUniform1ui;
extern PFNGLPROGRAMUNIFORM2UIPROC gload_glProgramUniform2ui;
extern PFNGLPROGRAMUNIFORM3UIPROC gload_glProgramUniform3ui;
extern PFNGLPROGRAMUNIFORM4UIPROC gload_glProgramUniform4ui;
extern PFNGLPROGRAMUNIFORM1FPROC gload_glProgramUniform1f;
extern PFNGLPROGRAMUNIFORM2FPROC gload_glProgramUniform2f;
extern PFNGLPROGRAMUNIFORM3FPROC gload_glProgramUniform3f;
extern PFNGLPROGRAMUNIFORM4FPROC gload_glProgramUniform4f;
extern PFNGLPROGRAMUNIFORM1IVPROC gload_glProgramUniform1iv;
extern PFNGLPROGRAMUNIFORM2IVPROC gload_glProgramUniform2iv;
extern PFNGLPROGRAMUNIFORM3IVPROC gload_glProgramUniform3iv;
extern PFNGLPROGRAMUNIFORM4IVPROC gload_glProgramUniform4iv;
extern PFNGLPROGRAMUNIFORM1UIVPROC gload_glProgramUniform1uiv;
extern PFNGLPROGRAMUNIFORM2UIVPROC gload_glProgramUniform2uiv;
extern PFNGLPROGRAMUNIFORM3UIVPROC gload_glProgramUniform3uiv;
extern PFNGLPROGRAMUNIFORM4UIVPROC gload_glProgramUniform4uiv;
extern PFNGLPROGRAMUNIFORM1FVPROC gload_glProgramUniform1fv;
extern PFNGLPROGRAMUNIFORM2FVPROC gload_glProgramUniform2fv;
extern PFNGLPROGRAMUNIFORM3FVPROC gload_glProgramUniform3fv;
extern PFNGLPROGRAMUNIFORM4FVPROC gload_glProgramUniform4fv;
extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC gload_glProgramUniformMatrix2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC gload_glProgramUniformMatrix3fv;
extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC gload_glProgramUniformMatrix4fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC gload_glProgramUniformMatrix2x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC gload_glProgramUniformMatrix3x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC gload_glProgramUniformMatrix2x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC gload_glProgramUniformMatrix4x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC gload_glProgramUniformMatrix3x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC gload_glProgramUniformMatrix4x3fv;
extern PFNGLVALIDATEPROGRAMPIPELINEPROC gload_glValidateProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC gload_glGetProgramPipelineInfoLog;
extern PFNGLBINDIMAGETEXTUREPROC gload_glBindImageTexture;
extern PFNGLGETBOOLEANI_VPROC gload_glGetBooleani_v;
extern PFNGLMEMORYBARRIERPROC gload_glMemoryBarrier;
extern PFNGLMEMORYBARRIERBYREGIONPROC gload_glMemoryBarrierByRegion;
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC gload_glTexStorage2DMultisample;
extern PFNGLGETMULTISAMPLEFVPROC gload_glGetMultisamplefv;
extern PFNGLSAMPLEMASKIPROC gload_glSampleMaski;
extern PFNGLGETTEXLEVELPARAMETERIVPROC gload_glGetTexLevelParameteriv;
extern PFNGLGETTEXLEVELPARAMETERFVPROC gload_glGetTexLevelParameterfv;
extern PFNGLBINDVERTEXBUFFERPROC gload_glBindVertexBuffer;
extern PFNGLVERTEXATTRIBFORMATPROC gload_glVertexAttribFormat;
extern PFNGLVERTEXATTRIBIFORMATPROC gload_glVertexAttribIFormat;
extern PFNGLVERTEXATTRIBBINDINGPROC gload_glVertexAttribBinding;
extern PFNGLVERTEXBINDINGDIVISORPROC gload_glVertexBindingDivisor;

# endif /* GL_ES_VERSION_3_1 */
# if defined GL_ES_VERSION_3_2

extern PFNGLBLENDBARRIERPROC gload_glBlendBarrier;
extern PFNGLCOPYIMAGESUBDATAPROC gload_glCopyImageSubData;
extern PFNGLDEBUGMESSAGECONTROLPROC gload_glDebugMessageControl;
extern PFNGLDEBUGMESSAGEINSERTPROC gload_glDebugMessageInsert;
extern PFNGLDEBUGMESSAGECALLBACKPROC gload_glDebugMessageCallback;
extern PFNGLGETDEBUGMESSAGELOGPROC gload_glGetDebugMessageLog;
extern PFNGLPUSHDEBUGGROUPPROC gload_glPushDebugGroup;
extern PFNGLPOPDEBUGGROUPPROC gload_glPopDebugGroup;
extern PFNGLOBJECTLABELPROC gload_glObjectLabel;
extern PFNGLGETOBJECTLABELPROC gload_glGetObjectLabel;
extern PFNGLOBJECTPTRLABELPROC gload_glObjectPtrLabel;
extern PFNGLGETOBJECTPTRLABELPROC gload_glGetObjectPtrLabel;
extern PFNGLGETPOINTERVPROC gload_glGetPointerv;
extern PFNGLENABLEIPROC gload_glEnablei;
extern PFNGLDISABLEIPROC gload_glDisablei;
extern PFNGLBLENDEQUATIONIPROC gload_glBlendEquationi;
extern PFNGLBLENDEQUATIONSEPARATEIPROC gload_glBlendEquationSeparatei;
extern PFNGLBLENDFUNCIPROC gload_glBlendFunci;
extern PFNGLBLENDFUNCSEPARATEIPROC gload_glBlendFuncSeparatei;
extern PFNGLCOLORMASKIPROC gload_glColorMaski;
extern PFNGLISENABLEDIPROC gload_glIsEnabledi;
extern PFNGLDRAWELEMENTSBASEVERTEXPROC gload_glDrawElementsBaseVertex;
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC gload_glDrawRangeElementsBaseVertex;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC gload_glDrawElementsInstancedBaseVertex;
extern PFNGLFRAMEBUFFERTEXTUREPROC gload_glFramebufferTexture;
extern PFNGLPRIMITIVEBOUNDINGBOXPROC gload_glPrimitiveBoundingBox;
extern PFNGLGETGRAPHICSRESETSTATUSPROC gload_glGetGraphicsResetStatus;
extern PFNGLREADNPIXELSPROC gload_glReadnPixels;
extern PFNGLGETNUNIFORMFVPROC gload_glGetnUniformfv;
extern PFNGLGETNUNIFORMIVPROC gload_glGetnUniformiv;
extern PFNGLGETNUNIFORMUIVPROC gload_glGetnUniformuiv;
extern PFNGLMINSAMPLESHADINGPROC gload_glMinSampleShading;
extern PFNGLPATCHPARAMETERIPROC gload_glPatchParameteri;
extern PFNGLTEXPARAMETERIIVPROC gload_glTexParameterIiv;
extern PFNGLTEXPARAMETERIUIVPROC gload_glTexParameterIuiv;
extern PFNGLGETTEXPARAMETERIIVPROC gload_glGetTexParameterIiv;
extern PFNGLGETTEXPARAMETERIUIVPROC gload_glGetTexParameterIuiv;
extern PFNGLSAMPLERPARAMETERIIVPROC gload_glSamplerParameterIiv;
extern PFNGLSAMPLERPARAMETERIUIVPROC gload_glSamplerParameterIuiv;
extern PFNGLGETSAMPLERPARAMETERIIVPROC gload_glGetSamplerParameterIiv;
extern PFNGLGETSAMPLERPARAMETERIUIVPROC gload_glGetSamplerParameterIuiv;
extern PFNGLTEXBUFFERPROC gload_glTexBuffer;
extern PFNGLTEXBUFFERRANGEPROC gload_glTexBufferRange;
extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC gload_glTexStorage3DMultisample;

# endif /* GL_ES_VERSION_3_2 */
# if defined GL_SC_VERSION_2_0

extern PFNGLACTIVETEXTUREPROC gload_glActiveTexture;
extern PFNGLBINDBUFFERPROC gload_glBindBuffer;
extern PFNGLBINDFRAMEBUFFERPROC gload_glBindFramebuffer;
extern PFNGLBINDRENDERBUFFERPROC gload_glBindRenderbuffer;
extern PFNGLBINDTEXTUREPROC gload_glBindTexture;
extern PFNGLBLENDCOLORPROC gload_glBlendColor;
extern PFNGLBLENDEQUATIONPROC gload_glBlendEquation;
extern PFNGLBLENDEQUATIONSEPARATEPROC gload_glBlendEquationSeparate;
extern PFNGLBLENDFUNCPROC gload_glBlendFunc;
extern PFNGLBLENDFUNCSEPARATEPROC gload_glBlendFuncSeparate;
extern PFNGLBUFFERDATAPROC gload_glBufferData;
extern PFNGLBUFFERSUBDATAPROC gload_glBufferSubData;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC gload_glCheckFramebufferStatus;
extern PFNGLCLEARPROC gload_glClear;
extern PFNGLCLEARCOLORPROC gload_glClearColor;
extern PFNGLCLEARDEPTHFPROC gload_glClearDepthf;
extern PFNGLCLEARSTENCILPROC gload_glClearStencil;
extern PFNGLCOLORMASKPROC gload_glColorMask;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC gload_glCompressedTexSubImage2D;
extern PFNGLCREATEPROGRAMPROC gload_glCreateProgram;
extern PFNGLCULLFACEPROC gload_glCullFace;
extern PFNGLDEPTHFUNCPROC gload_glDepthFunc;
extern PFNGLDEPTHMASKPROC gload_glDepthMask;
extern PFNGLDEPTHRANGEFPROC gload_glDepthRangef;
extern PFNGLDISABLEPROC gload_glDisable;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC gload_glDisableVertexAttribArray;
extern PFNGLDRAWARRAYSPROC gload_glDrawArrays;
extern PFNGLDRAWRANGEELEMENTSPROC gload_glDrawRangeElements;
extern PFNGLENABLEPROC gload_glEnable;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC gload_glEnableVertexAttribArray;
extern PFNGLFINISHPROC gload_glFinish;
extern PFNGLFLUSHPROC gload_glFlush;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC gload_glFramebufferRenderbuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC gload_glFramebufferTexture2D;
extern PFNGLFRONTFACEPROC gload_glFrontFace;
extern PFNGLGENBUFFERSPROC gload_glGenBuffers;
extern PFNGLGENERATEMIPMAPPROC gload_glGenerateMipmap;
extern PFNGLGENFRAMEBUFFERSPROC gload_glGenFramebuffers;
extern PFNGLGENRENDERBUFFERSPROC gload_glGenRenderbuffers;
extern PFNGLGENTEXTURESPROC gload_glGenTextures;
extern PFNGLGETATTRIBLOCATIONPROC gload_glGetAttribLocation;
extern PFNGLGETBOOLEANVPROC gload_glGetBooleanv;
extern PFNGLGETBUFFERPARAMETERIVPROC gload_glGetBufferParameteriv;
extern PFNGLGETERRORPROC gload_glGetError;
extern PFNGLGETFLOATVPROC gload_glGetFloatv;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC gload_glGetFramebufferAttachmentParameteriv;
extern PFNGLGETGRAPHICSRESETSTATUSPROC gload_glGetGraphicsResetStatus;
extern PFNGLGETINTEGERVPROC gload_glGetIntegerv;
extern PFNGLGETPROGRAMIVPROC gload_glGetProgramiv;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC gload_glGetRenderbufferParameteriv;
extern PFNGLGETSTRINGPROC gload_glGetString;
extern PFNGLGETTEXPARAMETERFVPROC gload_glGetTexParameterfv;
extern PFNGLGETTEXPARAMETERIVPROC gload_glGetTexParameteriv;
extern PFNGLGETNUNIFORMFVPROC gload_glGetnUniformfv;
extern PFNGLGETNUNIFORMIVPROC gload_glGetnUniformiv;
extern PFNGLGETUNIFORMLOCATIONPROC gload_glGetUniformLocation;
extern PFNGLGETVERTEXATTRIBFVPROC gload_glGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC gload_glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC gload_glGetVertexAttribPointerv;
extern PFNGLHINTPROC gload_glHint;
extern PFNGLISENABLEDPROC gload_glIsEnabled;
extern PFNGLLINEWIDTHPROC gload_glLineWidth;
extern PFNGLPIXELSTOREIPROC gload_glPixelStorei;
extern PFNGLPOLYGONOFFSETPROC gload_glPolygonOffset;
extern PFNGLPROGRAMBINARYPROC gload_glProgramBinary;
extern PFNGLREADNPIXELSPROC gload_glReadnPixels;
extern PFNGLRENDERBUFFERSTORAGEPROC gload_glRenderbufferStorage;
extern PFNGLSAMPLECOVERAGEPROC gload_glSampleCoverage;
extern PFNGLSCISSORPROC gload_glScissor;
extern PFNGLSTENCILFUNCPROC gload_glStencilFunc;
extern PFNGLSTENCILFUNCSEPARATEPROC gload_glStencilFuncSeparate;
extern PFNGLSTENCILMASKPROC gload_glStencilMask;
extern PFNGLSTENCILMASKSEPARATEPROC gload_glStencilMaskSeparate;
extern PFNGLSTENCILOPPROC gload_glStencilOp;
extern PFNGLSTENCILOPSEPARATEPROC gload_glStencilOpSeparate;
extern PFNGLTEXSTORAGE2DPROC gload_glTexStorage2D;
extern PFNGLTEXPARAMETERFPROC gload_glTexParameterf;
extern PFNGLTEXPARAMETERFVPROC gload_glTexParameterfv;
extern PFNGLTEXPARAMETERIPROC gload_glTexParameteri;
extern PFNGLTEXPARAMETERIVPROC gload_glTexParameteriv;
extern PFNGLTEXSUBIMAGE2DPROC gload_glTexSubImage2D;
extern PFNGLUNIFORM1FPROC gload_glUniform1f;
extern PFNGLUNIFORM1FVPROC gload_glUniform1fv;
extern PFNGLUNIFORM1IPROC gload_glUniform1i;
extern PFNGLUNIFORM1IVPROC gload_glUniform1iv;
extern PFNGLUNIFORM2FPROC gload_glUniform2f;
extern PFNGLUNIFORM2FVPROC gload_glUniform2fv;
extern PFNGLUNIFORM2IPROC gload_glUniform2i;
extern PFNGLUNIFORM2IVPROC gload_glUniform2iv;
extern PFNGLUNIFORM3FPROC gload_glUniform3f;
extern PFNGLUNIFORM3FVPROC gload_glUniform3fv;
extern PFNGLUNIFORM3IPROC gload_glUniform3i;
extern PFNGLUNIFORM3IVPROC gload_glUniform3iv;
extern PFNGLUNIFORM4FPROC gload_glUniform4f;
extern PFNGLUNIFORM4FVPROC gload_glUniform4fv;
extern PFNGLUNIFORM4IPROC gload_glUniform4i;
extern PFNGLUNIFORM4IVPROC gload_glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC gload_glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC gload_glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC gload_glUniformMatrix4fv;
extern PFNGLUSEPROGRAMPROC gload_glUseProgram;
extern PFNGLVERTEXATTRIB1FPROC gload_glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC gload_glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB2FPROC gload_glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC gload_glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB3FPROC gload_glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC gload_glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB4FPROC gload_glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC gload_glVertexAttrib4fv;
extern PFNGLVERTEXATTRIBPOINTERPROC gload_glVertexAttribPointer;
extern PFNGLVIEWPORTPROC gload_glViewport;

# endif /* GL_SC_VERSION_2_0 */
# if defined GL_VERSION_1_0
#  define glCullFace gload_glCullFace
#  define glFrontFace gload_glFrontFace
#  define glHint gload_glHint
#  define glLineWidth gload_glLineWidth
#  define glPointSize gload_glPointSize
#  define glPolygonMode gload_glPolygonMode
#  define glScissor gload_glScissor
#  define glTexParameterf gload_glTexParameterf
#  define glTexParameterfv gload_glTexParameterfv
#  define glTexParameteri gload_glTexParameteri
#  define glTexParameteriv gload_glTexParameteriv
#  define glTexImage1D gload_glTexImage1D
#  define glTexImage2D gload_glTexImage2D
#  define glDrawBuffer gload_glDrawBuffer
#  define glClear gload_glClear
#  define glClearColor gload_glClearColor
#  define glClearStencil gload_glClearStencil
#  define glClearDepth gload_glClearDepth
#  define glStencilMask gload_glStencilMask
#  define glColorMask gload_glColorMask
#  define glDepthMask gload_glDepthMask
#  define glDisable gload_glDisable
#  define glEnable gload_glEnable
#  define glFinish gload_glFinish
#  define glFlush gload_glFlush
#  define glBlendFunc gload_glBlendFunc
#  define glLogicOp gload_glLogicOp
#  define glStencilFunc gload_glStencilFunc
#  define glStencilOp gload_glStencilOp
#  define glDepthFunc gload_glDepthFunc
#  define glPixelStoref gload_glPixelStoref
#  define glPixelStorei gload_glPixelStorei
#  define glReadBuffer gload_glReadBuffer
#  define glReadPixels gload_glReadPixels
#  define glGetBooleanv gload_glGetBooleanv
#  define glGetDoublev gload_glGetDoublev
#  define glGetError gload_glGetError
#  define glGetFloatv gload_glGetFloatv
#  define glGetIntegerv gload_glGetIntegerv
#  define glGetString gload_glGetString
#  define glGetTexImage gload_glGetTexImage
#  define glGetTexParameterfv gload_glGetTexParameterfv
#  define glGetTexParameteriv gload_glGetTexParameteriv
#  define glGetTexLevelParameterfv gload_glGetTexLevelParameterfv
#  define glGetTexLevelParameteriv gload_glGetTexLevelParameteriv
#  define glIsEnabled gload_glIsEnabled
#  define glDepthRange gload_glDepthRange
#  define glViewport gload_glViewport
#  define glNewList gload_glNewList
#  define glEndList gload_glEndList
#  define glCallList gload_glCallList
#  define glCallLists gload_glCallLists
#  define glDeleteLists gload_glDeleteLists
#  define glGenLists gload_glGenLists
#  define glListBase gload_glListBase
#  define glBegin gload_glBegin
#  define glBitmap gload_glBitmap
#  define glColor3b gload_glColor3b
#  define glColor3bv gload_glColor3bv
#  define glColor3d gload_glColor3d
#  define glColor3dv gload_glColor3dv
#  define glColor3f gload_glColor3f
#  define glColor3fv gload_glColor3fv
#  define glColor3i gload_glColor3i
#  define glColor3iv gload_glColor3iv
#  define glColor3s gload_glColor3s
#  define glColor3sv gload_glColor3sv
#  define glColor3ub gload_glColor3ub
#  define glColor3ubv gload_glColor3ubv
#  define glColor3ui gload_glColor3ui
#  define glColor3uiv gload_glColor3uiv
#  define glColor3us gload_glColor3us
#  define glColor3usv gload_glColor3usv
#  define glColor4b gload_glColor4b
#  define glColor4bv gload_glColor4bv
#  define glColor4d gload_glColor4d
#  define glColor4dv gload_glColor4dv
#  define glColor4f gload_glColor4f
#  define glColor4fv gload_glColor4fv
#  define glColor4i gload_glColor4i
#  define glColor4iv gload_glColor4iv
#  define glColor4s gload_glColor4s
#  define glColor4sv gload_glColor4sv
#  define glColor4ub gload_glColor4ub
#  define glColor4ubv gload_glColor4ubv
#  define glColor4ui gload_glColor4ui
#  define glColor4uiv gload_glColor4uiv
#  define glColor4us gload_glColor4us
#  define glColor4usv gload_glColor4usv
#  define glEdgeFlag gload_glEdgeFlag
#  define glEdgeFlagv gload_glEdgeFlagv
#  define glEnd gload_glEnd
#  define glIndexd gload_glIndexd
#  define glIndexdv gload_glIndexdv
#  define glIndexf gload_glIndexf
#  define glIndexfv gload_glIndexfv
#  define glIndexi gload_glIndexi
#  define glIndexiv gload_glIndexiv
#  define glIndexs gload_glIndexs
#  define glIndexsv gload_glIndexsv
#  define glNormal3b gload_glNormal3b
#  define glNormal3bv gload_glNormal3bv
#  define glNormal3d gload_glNormal3d
#  define glNormal3dv gload_glNormal3dv
#  define glNormal3f gload_glNormal3f
#  define glNormal3fv gload_glNormal3fv
#  define glNormal3i gload_glNormal3i
#  define glNormal3iv gload_glNormal3iv
#  define glNormal3s gload_glNormal3s
#  define glNormal3sv gload_glNormal3sv
#  define glRasterPos2d gload_glRasterPos2d
#  define glRasterPos2dv gload_glRasterPos2dv
#  define glRasterPos2f gload_glRasterPos2f
#  define glRasterPos2fv gload_glRasterPos2fv
#  define glRasterPos2i gload_glRasterPos2i
#  define glRasterPos2iv gload_glRasterPos2iv
#  define glRasterPos2s gload_glRasterPos2s
#  define glRasterPos2sv gload_glRasterPos2sv
#  define glRasterPos3d gload_glRasterPos3d
#  define glRasterPos3dv gload_glRasterPos3dv
#  define glRasterPos3f gload_glRasterPos3f
#  define glRasterPos3fv gload_glRasterPos3fv
#  define glRasterPos3i gload_glRasterPos3i
#  define glRasterPos3iv gload_glRasterPos3iv
#  define glRasterPos3s gload_glRasterPos3s
#  define glRasterPos3sv gload_glRasterPos3sv
#  define glRasterPos4d gload_glRasterPos4d
#  define glRasterPos4dv gload_glRasterPos4dv
#  define glRasterPos4f gload_glRasterPos4f
#  define glRasterPos4fv gload_glRasterPos4fv
#  define glRasterPos4i gload_glRasterPos4i
#  define glRasterPos4iv gload_glRasterPos4iv
#  define glRasterPos4s gload_glRasterPos4s
#  define glRasterPos4sv gload_glRasterPos4sv
#  define glRectd gload_glRectd
#  define glRectdv gload_glRectdv
#  define glRectf gload_glRectf
#  define glRectfv gload_glRectfv
#  define glRecti gload_glRecti
#  define glRectiv gload_glRectiv
#  define glRects gload_glRects
#  define glRectsv gload_glRectsv
#  define glTexCoord1d gload_glTexCoord1d
#  define glTexCoord1dv gload_glTexCoord1dv
#  define glTexCoord1f gload_glTexCoord1f
#  define glTexCoord1fv gload_glTexCoord1fv
#  define glTexCoord1i gload_glTexCoord1i
#  define glTexCoord1iv gload_glTexCoord1iv
#  define glTexCoord1s gload_glTexCoord1s
#  define glTexCoord1sv gload_glTexCoord1sv
#  define glTexCoord2d gload_glTexCoord2d
#  define glTexCoord2dv gload_glTexCoord2dv
#  define glTexCoord2f gload_glTexCoord2f
#  define glTexCoord2fv gload_glTexCoord2fv
#  define glTexCoord2i gload_glTexCoord2i
#  define glTexCoord2iv gload_glTexCoord2iv
#  define glTexCoord2s gload_glTexCoord2s
#  define glTexCoord2sv gload_glTexCoord2sv
#  define glTexCoord3d gload_glTexCoord3d
#  define glTexCoord3dv gload_glTexCoord3dv
#  define glTexCoord3f gload_glTexCoord3f
#  define glTexCoord3fv gload_glTexCoord3fv
#  define glTexCoord3i gload_glTexCoord3i
#  define glTexCoord3iv gload_glTexCoord3iv
#  define glTexCoord3s gload_glTexCoord3s
#  define glTexCoord3sv gload_glTexCoord3sv
#  define glTexCoord4d gload_glTexCoord4d
#  define glTexCoord4dv gload_glTexCoord4dv
#  define glTexCoord4f gload_glTexCoord4f
#  define glTexCoord4fv gload_glTexCoord4fv
#  define glTexCoord4i gload_glTexCoord4i
#  define glTexCoord4iv gload_glTexCoord4iv
#  define glTexCoord4s gload_glTexCoord4s
#  define glTexCoord4sv gload_glTexCoord4sv
#  define glVertex2d gload_glVertex2d
#  define glVertex2dv gload_glVertex2dv
#  define glVertex2f gload_glVertex2f
#  define glVertex2fv gload_glVertex2fv
#  define glVertex2i gload_glVertex2i
#  define glVertex2iv gload_glVertex2iv
#  define glVertex2s gload_glVertex2s
#  define glVertex2sv gload_glVertex2sv
#  define glVertex3d gload_glVertex3d
#  define glVertex3dv gload_glVertex3dv
#  define glVertex3f gload_glVertex3f
#  define glVertex3fv gload_glVertex3fv
#  define glVertex3i gload_glVertex3i
#  define glVertex3iv gload_glVertex3iv
#  define glVertex3s gload_glVertex3s
#  define glVertex3sv gload_glVertex3sv
#  define glVertex4d gload_glVertex4d
#  define glVertex4dv gload_glVertex4dv
#  define glVertex4f gload_glVertex4f
#  define glVertex4fv gload_glVertex4fv
#  define glVertex4i gload_glVertex4i
#  define glVertex4iv gload_glVertex4iv
#  define glVertex4s gload_glVertex4s
#  define glVertex4sv gload_glVertex4sv
#  define glClipPlane gload_glClipPlane
#  define glColorMaterial gload_glColorMaterial
#  define glFogf gload_glFogf
#  define glFogfv gload_glFogfv
#  define glFogi gload_glFogi
#  define glFogiv gload_glFogiv
#  define glLightf gload_glLightf
#  define glLightfv gload_glLightfv
#  define glLighti gload_glLighti
#  define glLightiv gload_glLightiv
#  define glLightModelf gload_glLightModelf
#  define glLightModelfv gload_glLightModelfv
#  define glLightModeli gload_glLightModeli
#  define glLightModeliv gload_glLightModeliv
#  define glLineStipple gload_glLineStipple
#  define glMaterialf gload_glMaterialf
#  define glMaterialfv gload_glMaterialfv
#  define glMateriali gload_glMateriali
#  define glMaterialiv gload_glMaterialiv
#  define glPolygonStipple gload_glPolygonStipple
#  define glShadeModel gload_glShadeModel
#  define glTexEnvf gload_glTexEnvf
#  define glTexEnvfv gload_glTexEnvfv
#  define glTexEnvi gload_glTexEnvi
#  define glTexEnviv gload_glTexEnviv
#  define glTexGend gload_glTexGend
#  define glTexGendv gload_glTexGendv
#  define glTexGenf gload_glTexGenf
#  define glTexGenfv gload_glTexGenfv
#  define glTexGeni gload_glTexGeni
#  define glTexGeniv gload_glTexGeniv
#  define glFeedbackBuffer gload_glFeedbackBuffer
#  define glSelectBuffer gload_glSelectBuffer
#  define glRenderMode gload_glRenderMode
#  define glInitNames gload_glInitNames
#  define glLoadName gload_glLoadName
#  define glPassThrough gload_glPassThrough
#  define glPopName gload_glPopName
#  define glPushName gload_glPushName
#  define glClearAccum gload_glClearAccum
#  define glClearIndex gload_glClearIndex
#  define glIndexMask gload_glIndexMask
#  define glAccum gload_glAccum
#  define glPopAttrib gload_glPopAttrib
#  define glPushAttrib gload_glPushAttrib
#  define glMap1d gload_glMap1d
#  define glMap1f gload_glMap1f
#  define glMap2d gload_glMap2d
#  define glMap2f gload_glMap2f
#  define glMapGrid1d gload_glMapGrid1d
#  define glMapGrid1f gload_glMapGrid1f
#  define glMapGrid2d gload_glMapGrid2d
#  define glMapGrid2f gload_glMapGrid2f
#  define glEvalCoord1d gload_glEvalCoord1d
#  define glEvalCoord1dv gload_glEvalCoord1dv
#  define glEvalCoord1f gload_glEvalCoord1f
#  define glEvalCoord1fv gload_glEvalCoord1fv
#  define glEvalCoord2d gload_glEvalCoord2d
#  define glEvalCoord2dv gload_glEvalCoord2dv
#  define glEvalCoord2f gload_glEvalCoord2f
#  define glEvalCoord2fv gload_glEvalCoord2fv
#  define glEvalMesh1 gload_glEvalMesh1
#  define glEvalPoint1 gload_glEvalPoint1
#  define glEvalMesh2 gload_glEvalMesh2
#  define glEvalPoint2 gload_glEvalPoint2
#  define glAlphaFunc gload_glAlphaFunc
#  define glPixelZoom gload_glPixelZoom
#  define glPixelTransferf gload_glPixelTransferf
#  define glPixelTransferi gload_glPixelTransferi
#  define glPixelMapfv gload_glPixelMapfv
#  define glPixelMapuiv gload_glPixelMapuiv
#  define glPixelMapusv gload_glPixelMapusv
#  define glCopyPixels gload_glCopyPixels
#  define glDrawPixels gload_glDrawPixels
#  define glGetClipPlane gload_glGetClipPlane
#  define glGetLightfv gload_glGetLightfv
#  define glGetLightiv gload_glGetLightiv
#  define glGetMapdv gload_glGetMapdv
#  define glGetMapfv gload_glGetMapfv
#  define glGetMapiv gload_glGetMapiv
#  define glGetMaterialfv gload_glGetMaterialfv
#  define glGetMaterialiv gload_glGetMaterialiv
#  define glGetPixelMapfv gload_glGetPixelMapfv
#  define glGetPixelMapuiv gload_glGetPixelMapuiv
#  define glGetPixelMapusv gload_glGetPixelMapusv
#  define glGetPolygonStipple gload_glGetPolygonStipple
#  define glGetTexEnvfv gload_glGetTexEnvfv
#  define glGetTexEnviv gload_glGetTexEnviv
#  define glGetTexGendv gload_glGetTexGendv
#  define glGetTexGenfv gload_glGetTexGenfv
#  define glGetTexGeniv gload_glGetTexGeniv
#  define glIsList gload_glIsList
#  define glFrustum gload_glFrustum
#  define glLoadIdentity gload_glLoadIdentity
#  define glLoadMatrixf gload_glLoadMatrixf
#  define glLoadMatrixd gload_glLoadMatrixd
#  define glMatrixMode gload_glMatrixMode
#  define glMultMatrixf gload_glMultMatrixf
#  define glMultMatrixd gload_glMultMatrixd
#  define glOrtho gload_glOrtho
#  define glPopMatrix gload_glPopMatrix
#  define glPushMatrix gload_glPushMatrix
#  define glRotated gload_glRotated
#  define glRotatef gload_glRotatef
#  define glScaled gload_glScaled
#  define glScalef gload_glScalef
#  define glTranslated gload_glTranslated
#  define glTranslatef gload_glTranslatef
# endif /* GL_VERSION_1_0 */
# if defined GL_VERSION_1_1
#  define glDrawArrays gload_glDrawArrays
#  define glDrawElements gload_glDrawElements
#  define glGetPointerv gload_glGetPointerv
#  define glPolygonOffset gload_glPolygonOffset
#  define glCopyTexImage1D gload_glCopyTexImage1D
#  define glCopyTexImage2D gload_glCopyTexImage2D
#  define glCopyTexSubImage1D gload_glCopyTexSubImage1D
#  define glCopyTexSubImage2D gload_glCopyTexSubImage2D
#  define glTexSubImage1D gload_glTexSubImage1D
#  define glTexSubImage2D gload_glTexSubImage2D
#  define glBindTexture gload_glBindTexture
#  define glDeleteTextures gload_glDeleteTextures
#  define glGenTextures gload_glGenTextures
#  define glIsTexture gload_glIsTexture
#  define glArrayElement gload_glArrayElement
#  define glColorPointer gload_glColorPointer
#  define glDisableClientState gload_glDisableClientState
#  define glEdgeFlagPointer gload_glEdgeFlagPointer
#  define glEnableClientState gload_glEnableClientState
#  define glIndexPointer gload_glIndexPointer
#  define glInterleavedArrays gload_glInterleavedArrays
#  define glNormalPointer gload_glNormalPointer
#  define glTexCoordPointer gload_glTexCoordPointer
#  define glVertexPointer gload_glVertexPointer
#  define glAreTexturesResident gload_glAreTexturesResident
#  define glPrioritizeTextures gload_glPrioritizeTextures
#  define glIndexub gload_glIndexub
#  define glIndexubv gload_glIndexubv
#  define glPopClientAttrib gload_glPopClientAttrib
#  define glPushClientAttrib gload_glPushClientAttrib
# endif /* GL_VERSION_1_1 */
# if defined GL_VERSION_1_2
#  define glDrawRangeElements gload_glDrawRangeElements
#  define glTexImage3D gload_glTexImage3D
#  define glTexSubImage3D gload_glTexSubImage3D
#  define glCopyTexSubImage3D gload_glCopyTexSubImage3D
# endif /* GL_VERSION_1_2 */
# if defined GL_VERSION_1_3
#  define glActiveTexture gload_glActiveTexture
#  define glSampleCoverage gload_glSampleCoverage
#  define glCompressedTexImage3D gload_glCompressedTexImage3D
#  define glCompressedTexImage2D gload_glCompressedTexImage2D
#  define glCompressedTexImage1D gload_glCompressedTexImage1D
#  define glCompressedTexSubImage3D gload_glCompressedTexSubImage3D
#  define glCompressedTexSubImage2D gload_glCompressedTexSubImage2D
#  define glCompressedTexSubImage1D gload_glCompressedTexSubImage1D
#  define glGetCompressedTexImage gload_glGetCompressedTexImage
#  define glClientActiveTexture gload_glClientActiveTexture
#  define glMultiTexCoord1d gload_glMultiTexCoord1d
#  define glMultiTexCoord1dv gload_glMultiTexCoord1dv
#  define glMultiTexCoord1f gload_glMultiTexCoord1f
#  define glMultiTexCoord1fv gload_glMultiTexCoord1fv
#  define glMultiTexCoord1i gload_glMultiTexCoord1i
#  define glMultiTexCoord1iv gload_glMultiTexCoord1iv
#  define glMultiTexCoord1s gload_glMultiTexCoord1s
#  define glMultiTexCoord1sv gload_glMultiTexCoord1sv
#  define glMultiTexCoord2d gload_glMultiTexCoord2d
#  define glMultiTexCoord2dv gload_glMultiTexCoord2dv
#  define glMultiTexCoord2f gload_glMultiTexCoord2f
#  define glMultiTexCoord2fv gload_glMultiTexCoord2fv
#  define glMultiTexCoord2i gload_glMultiTexCoord2i
#  define glMultiTexCoord2iv gload_glMultiTexCoord2iv
#  define glMultiTexCoord2s gload_glMultiTexCoord2s
#  define glMultiTexCoord2sv gload_glMultiTexCoord2sv
#  define glMultiTexCoord3d gload_glMultiTexCoord3d
#  define glMultiTexCoord3dv gload_glMultiTexCoord3dv
#  define glMultiTexCoord3f gload_glMultiTexCoord3f
#  define glMultiTexCoord3fv gload_glMultiTexCoord3fv
#  define glMultiTexCoord3i gload_glMultiTexCoord3i
#  define glMultiTexCoord3iv gload_glMultiTexCoord3iv
#  define glMultiTexCoord3s gload_glMultiTexCoord3s
#  define glMultiTexCoord3sv gload_glMultiTexCoord3sv
#  define glMultiTexCoord4d gload_glMultiTexCoord4d
#  define glMultiTexCoord4dv gload_glMultiTexCoord4dv
#  define glMultiTexCoord4f gload_glMultiTexCoord4f
#  define glMultiTexCoord4fv gload_glMultiTexCoord4fv
#  define glMultiTexCoord4i gload_glMultiTexCoord4i
#  define glMultiTexCoord4iv gload_glMultiTexCoord4iv
#  define glMultiTexCoord4s gload_glMultiTexCoord4s
#  define glMultiTexCoord4sv gload_glMultiTexCoord4sv
#  define glLoadTransposeMatrixf gload_glLoadTransposeMatrixf
#  define glLoadTransposeMatrixd gload_glLoadTransposeMatrixd
#  define glMultTransposeMatrixf gload_glMultTransposeMatrixf
#  define glMultTransposeMatrixd gload_glMultTransposeMatrixd
# endif /* GL_VERSION_1_3 */
# if defined GL_VERSION_1_4
#  define glBlendFuncSeparate gload_glBlendFuncSeparate
#  define glMultiDrawArrays gload_glMultiDrawArrays
#  define glMultiDrawElements gload_glMultiDrawElements
#  define glPointParameterf gload_glPointParameterf
#  define glPointParameterfv gload_glPointParameterfv
#  define glPointParameteri gload_glPointParameteri
#  define glPointParameteriv gload_glPointParameteriv
#  define glFogCoordf gload_glFogCoordf
#  define glFogCoordfv gload_glFogCoordfv
#  define glFogCoordd gload_glFogCoordd
#  define glFogCoorddv gload_glFogCoorddv
#  define glFogCoordPointer gload_glFogCoordPointer
#  define glSecondaryColor3b gload_glSecondaryColor3b
#  define glSecondaryColor3bv gload_glSecondaryColor3bv
#  define glSecondaryColor3d gload_glSecondaryColor3d
#  define glSecondaryColor3dv gload_glSecondaryColor3dv
#  define glSecondaryColor3f gload_glSecondaryColor3f
#  define glSecondaryColor3fv gload_glSecondaryColor3fv
#  define glSecondaryColor3i gload_glSecondaryColor3i
#  define glSecondaryColor3iv gload_glSecondaryColor3iv
#  define glSecondaryColor3s gload_glSecondaryColor3s
#  define glSecondaryColor3sv gload_glSecondaryColor3sv
#  define glSecondaryColor3ub gload_glSecondaryColor3ub
#  define glSecondaryColor3ubv gload_glSecondaryColor3ubv
#  define glSecondaryColor3ui gload_glSecondaryColor3ui
#  define glSecondaryColor3uiv gload_glSecondaryColor3uiv
#  define glSecondaryColor3us gload_glSecondaryColor3us
#  define glSecondaryColor3usv gload_glSecondaryColor3usv
#  define glSecondaryColorPointer gload_glSecondaryColorPointer
#  define glWindowPos2d gload_glWindowPos2d
#  define glWindowPos2dv gload_glWindowPos2dv
#  define glWindowPos2f gload_glWindowPos2f
#  define glWindowPos2fv gload_glWindowPos2fv
#  define glWindowPos2i gload_glWindowPos2i
#  define glWindowPos2iv gload_glWindowPos2iv
#  define glWindowPos2s gload_glWindowPos2s
#  define glWindowPos2sv gload_glWindowPos2sv
#  define glWindowPos3d gload_glWindowPos3d
#  define glWindowPos3dv gload_glWindowPos3dv
#  define glWindowPos3f gload_glWindowPos3f
#  define glWindowPos3fv gload_glWindowPos3fv
#  define glWindowPos3i gload_glWindowPos3i
#  define glWindowPos3iv gload_glWindowPos3iv
#  define glWindowPos3s gload_glWindowPos3s
#  define glWindowPos3sv gload_glWindowPos3sv
#  define glBlendColor gload_glBlendColor
#  define glBlendEquation gload_glBlendEquation
# endif /* GL_VERSION_1_4 */
# if defined GL_VERSION_1_5
#  define glGenQueries gload_glGenQueries
#  define glDeleteQueries gload_glDeleteQueries
#  define glIsQuery gload_glIsQuery
#  define glBeginQuery gload_glBeginQuery
#  define glEndQuery gload_glEndQuery
#  define glGetQueryiv gload_glGetQueryiv
#  define glGetQueryObjectiv gload_glGetQueryObjectiv
#  define glGetQueryObjectuiv gload_glGetQueryObjectuiv
#  define glBindBuffer gload_glBindBuffer
#  define glDeleteBuffers gload_glDeleteBuffers
#  define glGenBuffers gload_glGenBuffers
#  define glIsBuffer gload_glIsBuffer
#  define glBufferData gload_glBufferData
#  define glBufferSubData gload_glBufferSubData
#  define glGetBufferSubData gload_glGetBufferSubData
#  define glMapBuffer gload_glMapBuffer
#  define glUnmapBuffer gload_glUnmapBuffer
#  define glGetBufferParameteriv gload_glGetBufferParameteriv
#  define glGetBufferPointerv gload_glGetBufferPointerv
# endif /* GL_VERSION_1_5 */
# if defined GL_VERSION_2_0
#  define glBlendEquationSeparate gload_glBlendEquationSeparate
#  define glDrawBuffers gload_glDrawBuffers
#  define glStencilOpSeparate gload_glStencilOpSeparate
#  define glStencilFuncSeparate gload_glStencilFuncSeparate
#  define glStencilMaskSeparate gload_glStencilMaskSeparate
#  define glAttachShader gload_glAttachShader
#  define glBindAttribLocation gload_glBindAttribLocation
#  define glCompileShader gload_glCompileShader
#  define glCreateProgram gload_glCreateProgram
#  define glCreateShader gload_glCreateShader
#  define glDeleteProgram gload_glDeleteProgram
#  define glDeleteShader gload_glDeleteShader
#  define glDetachShader gload_glDetachShader
#  define glDisableVertexAttribArray gload_glDisableVertexAttribArray
#  define glEnableVertexAttribArray gload_glEnableVertexAttribArray
#  define glGetActiveAttrib gload_glGetActiveAttrib
#  define glGetActiveUniform gload_glGetActiveUniform
#  define glGetAttachedShaders gload_glGetAttachedShaders
#  define glGetAttribLocation gload_glGetAttribLocation
#  define glGetProgramiv gload_glGetProgramiv
#  define glGetProgramInfoLog gload_glGetProgramInfoLog
#  define glGetShaderiv gload_glGetShaderiv
#  define glGetShaderInfoLog gload_glGetShaderInfoLog
#  define glGetShaderSource gload_glGetShaderSource
#  define glGetUniformLocation gload_glGetUniformLocation
#  define glGetUniformfv gload_glGetUniformfv
#  define glGetUniformiv gload_glGetUniformiv
#  define glGetVertexAttribdv gload_glGetVertexAttribdv
#  define glGetVertexAttribfv gload_glGetVertexAttribfv
#  define glGetVertexAttribiv gload_glGetVertexAttribiv
#  define glGetVertexAttribPointerv gload_glGetVertexAttribPointerv
#  define glIsProgram gload_glIsProgram
#  define glIsShader gload_glIsShader
#  define glLinkProgram gload_glLinkProgram
#  define glShaderSource gload_glShaderSource
#  define glUseProgram gload_glUseProgram
#  define glUniform1f gload_glUniform1f
#  define glUniform2f gload_glUniform2f
#  define glUniform3f gload_glUniform3f
#  define glUniform4f gload_glUniform4f
#  define glUniform1i gload_glUniform1i
#  define glUniform2i gload_glUniform2i
#  define glUniform3i gload_glUniform3i
#  define glUniform4i gload_glUniform4i
#  define glUniform1fv gload_glUniform1fv
#  define glUniform2fv gload_glUniform2fv
#  define glUniform3fv gload_glUniform3fv
#  define glUniform4fv gload_glUniform4fv
#  define glUniform1iv gload_glUniform1iv
#  define glUniform2iv gload_glUniform2iv
#  define glUniform3iv gload_glUniform3iv
#  define glUniform4iv gload_glUniform4iv
#  define glUniformMatrix2fv gload_glUniformMatrix2fv
#  define glUniformMatrix3fv gload_glUniformMatrix3fv
#  define glUniformMatrix4fv gload_glUniformMatrix4fv
#  define glValidateProgram gload_glValidateProgram
#  define glVertexAttrib1d gload_glVertexAttrib1d
#  define glVertexAttrib1dv gload_glVertexAttrib1dv
#  define glVertexAttrib1f gload_glVertexAttrib1f
#  define glVertexAttrib1fv gload_glVertexAttrib1fv
#  define glVertexAttrib1s gload_glVertexAttrib1s
#  define glVertexAttrib1sv gload_glVertexAttrib1sv
#  define glVertexAttrib2d gload_glVertexAttrib2d
#  define glVertexAttrib2dv gload_glVertexAttrib2dv
#  define glVertexAttrib2f gload_glVertexAttrib2f
#  define glVertexAttrib2fv gload_glVertexAttrib2fv
#  define glVertexAttrib2s gload_glVertexAttrib2s
#  define glVertexAttrib2sv gload_glVertexAttrib2sv
#  define glVertexAttrib3d gload_glVertexAttrib3d
#  define glVertexAttrib3dv gload_glVertexAttrib3dv
#  define glVertexAttrib3f gload_glVertexAttrib3f
#  define glVertexAttrib3fv gload_glVertexAttrib3fv
#  define glVertexAttrib3s gload_glVertexAttrib3s
#  define glVertexAttrib3sv gload_glVertexAttrib3sv
#  define glVertexAttrib4Nbv gload_glVertexAttrib4Nbv
#  define glVertexAttrib4Niv gload_glVertexAttrib4Niv
#  define glVertexAttrib4Nsv gload_glVertexAttrib4Nsv
#  define glVertexAttrib4Nub gload_glVertexAttrib4Nub
#  define glVertexAttrib4Nubv gload_glVertexAttrib4Nubv
#  define glVertexAttrib4Nuiv gload_glVertexAttrib4Nuiv
#  define glVertexAttrib4Nusv gload_glVertexAttrib4Nusv
#  define glVertexAttrib4bv gload_glVertexAttrib4bv
#  define glVertexAttrib4d gload_glVertexAttrib4d
#  define glVertexAttrib4dv gload_glVertexAttrib4dv
#  define glVertexAttrib4f gload_glVertexAttrib4f
#  define glVertexAttrib4fv gload_glVertexAttrib4fv
#  define glVertexAttrib4iv gload_glVertexAttrib4iv
#  define glVertexAttrib4s gload_glVertexAttrib4s
#  define glVertexAttrib4sv gload_glVertexAttrib4sv
#  define glVertexAttrib4ubv gload_glVertexAttrib4ubv
#  define glVertexAttrib4uiv gload_glVertexAttrib4uiv
#  define glVertexAttrib4usv gload_glVertexAttrib4usv
#  define glVertexAttribPointer gload_glVertexAttribPointer
# endif /* GL_VERSION_2_0 */
# if defined GL_VERSION_2_1
#  define glUniformMatrix2x3fv gload_glUniformMatrix2x3fv
#  define glUniformMatrix3x2fv gload_glUniformMatrix3x2fv
#  define glUniformMatrix2x4fv gload_glUniformMatrix2x4fv
#  define glUniformMatrix4x2fv gload_glUniformMatrix4x2fv
#  define glUniformMatrix3x4fv gload_glUniformMatrix3x4fv
#  define glUniformMatrix4x3fv gload_glUniformMatrix4x3fv
# endif /* GL_VERSION_2_1 */
# if defined GL_VERSION_3_0
#  define glColorMaski gload_glColorMaski
#  define glGetBooleani_v gload_glGetBooleani_v
#  define glGetIntegeri_v gload_glGetIntegeri_v
#  define glEnablei gload_glEnablei
#  define glDisablei gload_glDisablei
#  define glIsEnabledi gload_glIsEnabledi
#  define glBeginTransformFeedback gload_glBeginTransformFeedback
#  define glEndTransformFeedback gload_glEndTransformFeedback
#  define glBindBufferRange gload_glBindBufferRange
#  define glBindBufferBase gload_glBindBufferBase
#  define glTransformFeedbackVaryings gload_glTransformFeedbackVaryings
#  define glGetTransformFeedbackVarying gload_glGetTransformFeedbackVarying
#  define glClampColor gload_glClampColor
#  define glBeginConditionalRender gload_glBeginConditionalRender
#  define glEndConditionalRender gload_glEndConditionalRender
#  define glVertexAttribIPointer gload_glVertexAttribIPointer
#  define glGetVertexAttribIiv gload_glGetVertexAttribIiv
#  define glGetVertexAttribIuiv gload_glGetVertexAttribIuiv
#  define glVertexAttribI1i gload_glVertexAttribI1i
#  define glVertexAttribI2i gload_glVertexAttribI2i
#  define glVertexAttribI3i gload_glVertexAttribI3i
#  define glVertexAttribI4i gload_glVertexAttribI4i
#  define glVertexAttribI1ui gload_glVertexAttribI1ui
#  define glVertexAttribI2ui gload_glVertexAttribI2ui
#  define glVertexAttribI3ui gload_glVertexAttribI3ui
#  define glVertexAttribI4ui gload_glVertexAttribI4ui
#  define glVertexAttribI1iv gload_glVertexAttribI1iv
#  define glVertexAttribI2iv gload_glVertexAttribI2iv
#  define glVertexAttribI3iv gload_glVertexAttribI3iv
#  define glVertexAttribI4iv gload_glVertexAttribI4iv
#  define glVertexAttribI1uiv gload_glVertexAttribI1uiv
#  define glVertexAttribI2uiv gload_glVertexAttribI2uiv
#  define glVertexAttribI3uiv gload_glVertexAttribI3uiv
#  define glVertexAttribI4uiv gload_glVertexAttribI4uiv
#  define glVertexAttribI4bv gload_glVertexAttribI4bv
#  define glVertexAttribI4sv gload_glVertexAttribI4sv
#  define glVertexAttribI4ubv gload_glVertexAttribI4ubv
#  define glVertexAttribI4usv gload_glVertexAttribI4usv
#  define glGetUniformuiv gload_glGetUniformuiv
#  define glBindFragDataLocation gload_glBindFragDataLocation
#  define glGetFragDataLocation gload_glGetFragDataLocation
#  define glUniform1ui gload_glUniform1ui
#  define glUniform2ui gload_glUniform2ui
#  define glUniform3ui gload_glUniform3ui
#  define glUniform4ui gload_glUniform4ui
#  define glUniform1uiv gload_glUniform1uiv
#  define glUniform2uiv gload_glUniform2uiv
#  define glUniform3uiv gload_glUniform3uiv
#  define glUniform4uiv gload_glUniform4uiv
#  define glTexParameterIiv gload_glTexParameterIiv
#  define glTexParameterIuiv gload_glTexParameterIuiv
#  define glGetTexParameterIiv gload_glGetTexParameterIiv
#  define glGetTexParameterIuiv gload_glGetTexParameterIuiv
#  define glClearBufferiv gload_glClearBufferiv
#  define glClearBufferuiv gload_glClearBufferuiv
#  define glClearBufferfv gload_glClearBufferfv
#  define glClearBufferfi gload_glClearBufferfi
#  define glGetStringi gload_glGetStringi
#  define glIsRenderbuffer gload_glIsRenderbuffer
#  define glBindRenderbuffer gload_glBindRenderbuffer
#  define glDeleteRenderbuffers gload_glDeleteRenderbuffers
#  define glGenRenderbuffers gload_glGenRenderbuffers
#  define glRenderbufferStorage gload_glRenderbufferStorage
#  define glGetRenderbufferParameteriv gload_glGetRenderbufferParameteriv
#  define glIsFramebuffer gload_glIsFramebuffer
#  define glBindFramebuffer gload_glBindFramebuffer
#  define glDeleteFramebuffers gload_glDeleteFramebuffers
#  define glGenFramebuffers gload_glGenFramebuffers
#  define glCheckFramebufferStatus gload_glCheckFramebufferStatus
#  define glFramebufferTexture1D gload_glFramebufferTexture1D
#  define glFramebufferTexture2D gload_glFramebufferTexture2D
#  define glFramebufferTexture3D gload_glFramebufferTexture3D
#  define glFramebufferRenderbuffer gload_glFramebufferRenderbuffer
#  define glGetFramebufferAttachmentParameteriv gload_glGetFramebufferAttachmentParameteriv
#  define glGenerateMipmap gload_glGenerateMipmap
#  define glBlitFramebuffer gload_glBlitFramebuffer
#  define glRenderbufferStorageMultisample gload_glRenderbufferStorageMultisample
#  define glFramebufferTextureLayer gload_glFramebufferTextureLayer
#  define glMapBufferRange gload_glMapBufferRange
#  define glFlushMappedBufferRange gload_glFlushMappedBufferRange
#  define glBindVertexArray gload_glBindVertexArray
#  define glDeleteVertexArrays gload_glDeleteVertexArrays
#  define glGenVertexArrays gload_glGenVertexArrays
#  define glIsVertexArray gload_glIsVertexArray
# endif /* GL_VERSION_3_0 */
# if defined GL_VERSION_3_1
#  define glDrawArraysInstanced gload_glDrawArraysInstanced
#  define glDrawElementsInstanced gload_glDrawElementsInstanced
#  define glTexBuffer gload_glTexBuffer
#  define glPrimitiveRestartIndex gload_glPrimitiveRestartIndex
#  define glCopyBufferSubData gload_glCopyBufferSubData
#  define glGetUniformIndices gload_glGetUniformIndices
#  define glGetActiveUniformsiv gload_glGetActiveUniformsiv
#  define glGetActiveUniformName gload_glGetActiveUniformName
#  define glGetUniformBlockIndex gload_glGetUniformBlockIndex
#  define glGetActiveUniformBlockiv gload_glGetActiveUniformBlockiv
#  define glGetActiveUniformBlockName gload_glGetActiveUniformBlockName
#  define glUniformBlockBinding gload_glUniformBlockBinding
#  define glBindBufferRange gload_glBindBufferRange
#  define glBindBufferBase gload_glBindBufferBase
#  define glGetIntegeri_v gload_glGetIntegeri_v
# endif /* GL_VERSION_3_1 */
# if defined GL_VERSION_3_2
#  define glDrawElementsBaseVertex gload_glDrawElementsBaseVertex
#  define glDrawRangeElementsBaseVertex gload_glDrawRangeElementsBaseVertex
#  define glDrawElementsInstancedBaseVertex gload_glDrawElementsInstancedBaseVertex
#  define glMultiDrawElementsBaseVertex gload_glMultiDrawElementsBaseVertex
#  define glProvokingVertex gload_glProvokingVertex
#  define glFenceSync gload_glFenceSync
#  define glIsSync gload_glIsSync
#  define glDeleteSync gload_glDeleteSync
#  define glClientWaitSync gload_glClientWaitSync
#  define glWaitSync gload_glWaitSync
#  define glGetInteger64v gload_glGetInteger64v
#  define glGetSynciv gload_glGetSynciv
#  define glGetInteger64i_v gload_glGetInteger64i_v
#  define glGetBufferParameteri64v gload_glGetBufferParameteri64v
#  define glFramebufferTexture gload_glFramebufferTexture
#  define glTexImage2DMultisample gload_glTexImage2DMultisample
#  define glTexImage3DMultisample gload_glTexImage3DMultisample
#  define glGetMultisamplefv gload_glGetMultisamplefv
#  define glSampleMaski gload_glSampleMaski
# endif /* GL_VERSION_3_2 */
# if defined GL_VERSION_3_3
#  define glBindFragDataLocationIndexed gload_glBindFragDataLocationIndexed
#  define glGetFragDataIndex gload_glGetFragDataIndex
#  define glGenSamplers gload_glGenSamplers
#  define glDeleteSamplers gload_glDeleteSamplers
#  define glIsSampler gload_glIsSampler
#  define glBindSampler gload_glBindSampler
#  define glSamplerParameteri gload_glSamplerParameteri
#  define glSamplerParameteriv gload_glSamplerParameteriv
#  define glSamplerParameterf gload_glSamplerParameterf
#  define glSamplerParameterfv gload_glSamplerParameterfv
#  define glSamplerParameterIiv gload_glSamplerParameterIiv
#  define glSamplerParameterIuiv gload_glSamplerParameterIuiv
#  define glGetSamplerParameteriv gload_glGetSamplerParameteriv
#  define glGetSamplerParameterIiv gload_glGetSamplerParameterIiv
#  define glGetSamplerParameterfv gload_glGetSamplerParameterfv
#  define glGetSamplerParameterIuiv gload_glGetSamplerParameterIuiv
#  define glQueryCounter gload_glQueryCounter
#  define glGetQueryObjecti64v gload_glGetQueryObjecti64v
#  define glGetQueryObjectui64v gload_glGetQueryObjectui64v
#  define glVertexAttribDivisor gload_glVertexAttribDivisor
#  define glVertexAttribP1ui gload_glVertexAttribP1ui
#  define glVertexAttribP1uiv gload_glVertexAttribP1uiv
#  define glVertexAttribP2ui gload_glVertexAttribP2ui
#  define glVertexAttribP2uiv gload_glVertexAttribP2uiv
#  define glVertexAttribP3ui gload_glVertexAttribP3ui
#  define glVertexAttribP3uiv gload_glVertexAttribP3uiv
#  define glVertexAttribP4ui gload_glVertexAttribP4ui
#  define glVertexAttribP4uiv gload_glVertexAttribP4uiv
#  define glVertexP2ui gload_glVertexP2ui
#  define glVertexP2uiv gload_glVertexP2uiv
#  define glVertexP3ui gload_glVertexP3ui
#  define glVertexP3uiv gload_glVertexP3uiv
#  define glVertexP4ui gload_glVertexP4ui
#  define glVertexP4uiv gload_glVertexP4uiv
#  define glTexCoordP1ui gload_glTexCoordP1ui
#  define glTexCoordP1uiv gload_glTexCoordP1uiv
#  define glTexCoordP2ui gload_glTexCoordP2ui
#  define glTexCoordP2uiv gload_glTexCoordP2uiv
#  define glTexCoordP3ui gload_glTexCoordP3ui
#  define glTexCoordP3uiv gload_glTexCoordP3uiv
#  define glTexCoordP4ui gload_glTexCoordP4ui
#  define glTexCoordP4uiv gload_glTexCoordP4uiv
#  define glMultiTexCoordP1ui gload_glMultiTexCoordP1ui
#  define glMultiTexCoordP1uiv gload_glMultiTexCoordP1uiv
#  define glMultiTexCoordP2ui gload_glMultiTexCoordP2ui
#  define glMultiTexCoordP2uiv gload_glMultiTexCoordP2uiv
#  define glMultiTexCoordP3ui gload_glMultiTexCoordP3ui
#  define glMultiTexCoordP3uiv gload_glMultiTexCoordP3uiv
#  define glMultiTexCoordP4ui gload_glMultiTexCoordP4ui
#  define glMultiTexCoordP4uiv gload_glMultiTexCoordP4uiv
#  define glNormalP3ui gload_glNormalP3ui
#  define glNormalP3uiv gload_glNormalP3uiv
#  define glColorP3ui gload_glColorP3ui
#  define glColorP3uiv gload_glColorP3uiv
#  define glColorP4ui gload_glColorP4ui
#  define glColorP4uiv gload_glColorP4uiv
#  define glSecondaryColorP3ui gload_glSecondaryColorP3ui
#  define glSecondaryColorP3uiv gload_glSecondaryColorP3uiv
# endif /* GL_VERSION_3_3 */
# if defined GL_VERSION_4_0
#  define glMinSampleShading gload_glMinSampleShading
#  define glBlendEquationi gload_glBlendEquationi
#  define glBlendEquationSeparatei gload_glBlendEquationSeparatei
#  define glBlendFunci gload_glBlendFunci
#  define glBlendFuncSeparatei gload_glBlendFuncSeparatei
#  define glDrawArraysIndirect gload_glDrawArraysIndirect
#  define glDrawElementsIndirect gload_glDrawElementsIndirect
#  define glUniform1d gload_glUniform1d
#  define glUniform2d gload_glUniform2d
#  define glUniform3d gload_glUniform3d
#  define glUniform4d gload_glUniform4d
#  define glUniform1dv gload_glUniform1dv
#  define glUniform2dv gload_glUniform2dv
#  define glUniform3dv gload_glUniform3dv
#  define glUniform4dv gload_glUniform4dv
#  define glUniformMatrix2dv gload_glUniformMatrix2dv
#  define glUniformMatrix3dv gload_glUniformMatrix3dv
#  define glUniformMatrix4dv gload_glUniformMatrix4dv
#  define glUniformMatrix2x3dv gload_glUniformMatrix2x3dv
#  define glUniformMatrix2x4dv gload_glUniformMatrix2x4dv
#  define glUniformMatrix3x2dv gload_glUniformMatrix3x2dv
#  define glUniformMatrix3x4dv gload_glUniformMatrix3x4dv
#  define glUniformMatrix4x2dv gload_glUniformMatrix4x2dv
#  define glUniformMatrix4x3dv gload_glUniformMatrix4x3dv
#  define glGetUniformdv gload_glGetUniformdv
#  define glGetSubroutineUniformLocation gload_glGetSubroutineUniformLocation
#  define glGetSubroutineIndex gload_glGetSubroutineIndex
#  define glGetActiveSubroutineUniformiv gload_glGetActiveSubroutineUniformiv
#  define glGetActiveSubroutineUniformName gload_glGetActiveSubroutineUniformName
#  define glGetActiveSubroutineName gload_glGetActiveSubroutineName
#  define glUniformSubroutinesuiv gload_glUniformSubroutinesuiv
#  define glGetUniformSubroutineuiv gload_glGetUniformSubroutineuiv
#  define glGetProgramStageiv gload_glGetProgramStageiv
#  define glPatchParameteri gload_glPatchParameteri
#  define glPatchParameterfv gload_glPatchParameterfv
#  define glBindTransformFeedback gload_glBindTransformFeedback
#  define glDeleteTransformFeedbacks gload_glDeleteTransformFeedbacks
#  define glGenTransformFeedbacks gload_glGenTransformFeedbacks
#  define glIsTransformFeedback gload_glIsTransformFeedback
#  define glPauseTransformFeedback gload_glPauseTransformFeedback
#  define glResumeTransformFeedback gload_glResumeTransformFeedback
#  define glDrawTransformFeedback gload_glDrawTransformFeedback
#  define glDrawTransformFeedbackStream gload_glDrawTransformFeedbackStream
#  define glBeginQueryIndexed gload_glBeginQueryIndexed
#  define glEndQueryIndexed gload_glEndQueryIndexed
#  define glGetQueryIndexediv gload_glGetQueryIndexediv
# endif /* GL_VERSION_4_0 */
# if defined GL_VERSION_4_1
#  define glReleaseShaderCompiler gload_glReleaseShaderCompiler
#  define glShaderBinary gload_glShaderBinary
#  define glGetShaderPrecisionFormat gload_glGetShaderPrecisionFormat
#  define glDepthRangef gload_glDepthRangef
#  define glClearDepthf gload_glClearDepthf
#  define glGetProgramBinary gload_glGetProgramBinary
#  define glProgramBinary gload_glProgramBinary
#  define glProgramParameteri gload_glProgramParameteri
#  define glUseProgramStages gload_glUseProgramStages
#  define glActiveShaderProgram gload_glActiveShaderProgram
#  define glCreateShaderProgramv gload_glCreateShaderProgramv
#  define glBindProgramPipeline gload_glBindProgramPipeline
#  define glDeleteProgramPipelines gload_glDeleteProgramPipelines
#  define glGenProgramPipelines gload_glGenProgramPipelines
#  define glIsProgramPipeline gload_glIsProgramPipeline
#  define glGetProgramPipelineiv gload_glGetProgramPipelineiv
#  define glProgramParameteri gload_glProgramParameteri
#  define glProgramUniform1i gload_glProgramUniform1i
#  define glProgramUniform1iv gload_glProgramUniform1iv
#  define glProgramUniform1f gload_glProgramUniform1f
#  define glProgramUniform1fv gload_glProgramUniform1fv
#  define glProgramUniform1d gload_glProgramUniform1d
#  define glProgramUniform1dv gload_glProgramUniform1dv
#  define glProgramUniform1ui gload_glProgramUniform1ui
#  define glProgramUniform1uiv gload_glProgramUniform1uiv
#  define glProgramUniform2i gload_glProgramUniform2i
#  define glProgramUniform2iv gload_glProgramUniform2iv
#  define glProgramUniform2f gload_glProgramUniform2f
#  define glProgramUniform2fv gload_glProgramUniform2fv
#  define glProgramUniform2d gload_glProgramUniform2d
#  define glProgramUniform2dv gload_glProgramUniform2dv
#  define glProgramUniform2ui gload_glProgramUniform2ui
#  define glProgramUniform2uiv gload_glProgramUniform2uiv
#  define glProgramUniform3i gload_glProgramUniform3i
#  define glProgramUniform3iv gload_glProgramUniform3iv
#  define glProgramUniform3f gload_glProgramUniform3f
#  define glProgramUniform3fv gload_glProgramUniform3fv
#  define glProgramUniform3d gload_glProgramUniform3d
#  define glProgramUniform3dv gload_glProgramUniform3dv
#  define glProgramUniform3ui gload_glProgramUniform3ui
#  define glProgramUniform3uiv gload_glProgramUniform3uiv
#  define glProgramUniform4i gload_glProgramUniform4i
#  define glProgramUniform4iv gload_glProgramUniform4iv
#  define glProgramUniform4f gload_glProgramUniform4f
#  define glProgramUniform4fv gload_glProgramUniform4fv
#  define glProgramUniform4d gload_glProgramUniform4d
#  define glProgramUniform4dv gload_glProgramUniform4dv
#  define glProgramUniform4ui gload_glProgramUniform4ui
#  define glProgramUniform4uiv gload_glProgramUniform4uiv
#  define glProgramUniformMatrix2fv gload_glProgramUniformMatrix2fv
#  define glProgramUniformMatrix3fv gload_glProgramUniformMatrix3fv
#  define glProgramUniformMatrix4fv gload_glProgramUniformMatrix4fv
#  define glProgramUniformMatrix2dv gload_glProgramUniformMatrix2dv
#  define glProgramUniformMatrix3dv gload_glProgramUniformMatrix3dv
#  define glProgramUniformMatrix4dv gload_glProgramUniformMatrix4dv
#  define glProgramUniformMatrix2x3fv gload_glProgramUniformMatrix2x3fv
#  define glProgramUniformMatrix3x2fv gload_glProgramUniformMatrix3x2fv
#  define glProgramUniformMatrix2x4fv gload_glProgramUniformMatrix2x4fv
#  define glProgramUniformMatrix4x2fv gload_glProgramUniformMatrix4x2fv
#  define glProgramUniformMatrix3x4fv gload_glProgramUniformMatrix3x4fv
#  define glProgramUniformMatrix4x3fv gload_glProgramUniformMatrix4x3fv
#  define glProgramUniformMatrix2x3dv gload_glProgramUniformMatrix2x3dv
#  define glProgramUniformMatrix3x2dv gload_glProgramUniformMatrix3x2dv
#  define glProgramUniformMatrix2x4dv gload_glProgramUniformMatrix2x4dv
#  define glProgramUniformMatrix4x2dv gload_glProgramUniformMatrix4x2dv
#  define glProgramUniformMatrix3x4dv gload_glProgramUniformMatrix3x4dv
#  define glProgramUniformMatrix4x3dv gload_glProgramUniformMatrix4x3dv
#  define glValidateProgramPipeline gload_glValidateProgramPipeline
#  define glGetProgramPipelineInfoLog gload_glGetProgramPipelineInfoLog
#  define glVertexAttribL1d gload_glVertexAttribL1d
#  define glVertexAttribL2d gload_glVertexAttribL2d
#  define glVertexAttribL3d gload_glVertexAttribL3d
#  define glVertexAttribL4d gload_glVertexAttribL4d
#  define glVertexAttribL1dv gload_glVertexAttribL1dv
#  define glVertexAttribL2dv gload_glVertexAttribL2dv
#  define glVertexAttribL3dv gload_glVertexAttribL3dv
#  define glVertexAttribL4dv gload_glVertexAttribL4dv
#  define glVertexAttribLPointer gload_glVertexAttribLPointer
#  define glGetVertexAttribLdv gload_glGetVertexAttribLdv
#  define glViewportArrayv gload_glViewportArrayv
#  define glViewportIndexedf gload_glViewportIndexedf
#  define glViewportIndexedfv gload_glViewportIndexedfv
#  define glScissorArrayv gload_glScissorArrayv
#  define glScissorIndexed gload_glScissorIndexed
#  define glScissorIndexedv gload_glScissorIndexedv
#  define glDepthRangeArrayv gload_glDepthRangeArrayv
#  define glDepthRangeIndexed gload_glDepthRangeIndexed
#  define glGetFloati_v gload_glGetFloati_v
#  define glGetDoublei_v gload_glGetDoublei_v
# endif /* GL_VERSION_4_1 */
# if defined GL_VERSION_4_2
#  define glDrawArraysInstancedBaseInstance gload_glDrawArraysInstancedBaseInstance
#  define glDrawElementsInstancedBaseInstance gload_glDrawElementsInstancedBaseInstance
#  define glDrawElementsInstancedBaseVertexBaseInstance gload_glDrawElementsInstancedBaseVertexBaseInstance
#  define glGetInternalformativ gload_glGetInternalformativ
#  define glGetActiveAtomicCounterBufferiv gload_glGetActiveAtomicCounterBufferiv
#  define glBindImageTexture gload_glBindImageTexture
#  define glMemoryBarrier gload_glMemoryBarrier
#  define glTexStorage1D gload_glTexStorage1D
#  define glTexStorage2D gload_glTexStorage2D
#  define glTexStorage3D gload_glTexStorage3D
#  define glDrawTransformFeedbackInstanced gload_glDrawTransformFeedbackInstanced
#  define glDrawTransformFeedbackStreamInstanced gload_glDrawTransformFeedbackStreamInstanced
# endif /* GL_VERSION_4_2 */
# if defined GL_VERSION_4_3
#  define glClearBufferData gload_glClearBufferData
#  define glClearBufferSubData gload_glClearBufferSubData
#  define glDispatchCompute gload_glDispatchCompute
#  define glDispatchComputeIndirect gload_glDispatchComputeIndirect
#  define glCopyImageSubData gload_glCopyImageSubData
#  define glFramebufferParameteri gload_glFramebufferParameteri
#  define glGetFramebufferParameteriv gload_glGetFramebufferParameteriv
#  define glGetInternalformati64v gload_glGetInternalformati64v
#  define glInvalidateTexSubImage gload_glInvalidateTexSubImage
#  define glInvalidateTexImage gload_glInvalidateTexImage
#  define glInvalidateBufferSubData gload_glInvalidateBufferSubData
#  define glInvalidateBufferData gload_glInvalidateBufferData
#  define glInvalidateFramebuffer gload_glInvalidateFramebuffer
#  define glInvalidateSubFramebuffer gload_glInvalidateSubFramebuffer
#  define glMultiDrawArraysIndirect gload_glMultiDrawArraysIndirect
#  define glMultiDrawElementsIndirect gload_glMultiDrawElementsIndirect
#  define glGetProgramInterfaceiv gload_glGetProgramInterfaceiv
#  define glGetProgramResourceIndex gload_glGetProgramResourceIndex
#  define glGetProgramResourceName gload_glGetProgramResourceName
#  define glGetProgramResourceiv gload_glGetProgramResourceiv
#  define glGetProgramResourceLocation gload_glGetProgramResourceLocation
#  define glGetProgramResourceLocationIndex gload_glGetProgramResourceLocationIndex
#  define glShaderStorageBlockBinding gload_glShaderStorageBlockBinding
#  define glTexBufferRange gload_glTexBufferRange
#  define glTexStorage2DMultisample gload_glTexStorage2DMultisample
#  define glTexStorage3DMultisample gload_glTexStorage3DMultisample
#  define glTextureView gload_glTextureView
#  define glBindVertexBuffer gload_glBindVertexBuffer
#  define glVertexAttribFormat gload_glVertexAttribFormat
#  define glVertexAttribIFormat gload_glVertexAttribIFormat
#  define glVertexAttribLFormat gload_glVertexAttribLFormat
#  define glVertexAttribBinding gload_glVertexAttribBinding
#  define glVertexBindingDivisor gload_glVertexBindingDivisor
#  define glDebugMessageControl gload_glDebugMessageControl
#  define glDebugMessageInsert gload_glDebugMessageInsert
#  define glDebugMessageCallback gload_glDebugMessageCallback
#  define glGetDebugMessageLog gload_glGetDebugMessageLog
#  define glPushDebugGroup gload_glPushDebugGroup
#  define glPopDebugGroup gload_glPopDebugGroup
#  define glObjectLabel gload_glObjectLabel
#  define glGetObjectLabel gload_glGetObjectLabel
#  define glObjectPtrLabel gload_glObjectPtrLabel
#  define glGetObjectPtrLabel gload_glGetObjectPtrLabel
#  define glGetPointerv gload_glGetPointerv
# endif /* GL_VERSION_4_3 */
# if defined GL_VERSION_4_4
#  define glBufferStorage gload_glBufferStorage
#  define glClearTexImage gload_glClearTexImage
#  define glClearTexSubImage gload_glClearTexSubImage
#  define glBindBuffersBase gload_glBindBuffersBase
#  define glBindBuffersRange gload_glBindBuffersRange
#  define glBindTextures gload_glBindTextures
#  define glBindSamplers gload_glBindSamplers
#  define glBindImageTextures gload_glBindImageTextures
#  define glBindVertexBuffers gload_glBindVertexBuffers
# endif /* GL_VERSION_4_4 */
# if defined GL_VERSION_4_5
#  define glClipControl gload_glClipControl
#  define glCreateTransformFeedbacks gload_glCreateTransformFeedbacks
#  define glTransformFeedbackBufferBase gload_glTransformFeedbackBufferBase
#  define glTransformFeedbackBufferRange gload_glTransformFeedbackBufferRange
#  define glGetTransformFeedbackiv gload_glGetTransformFeedbackiv
#  define glGetTransformFeedbacki_v gload_glGetTransformFeedbacki_v
#  define glGetTransformFeedbacki64_v gload_glGetTransformFeedbacki64_v
#  define glCreateBuffers gload_glCreateBuffers
#  define glNamedBufferStorage gload_glNamedBufferStorage
#  define glNamedBufferData gload_glNamedBufferData
#  define glNamedBufferSubData gload_glNamedBufferSubData
#  define glCopyNamedBufferSubData gload_glCopyNamedBufferSubData
#  define glClearNamedBufferData gload_glClearNamedBufferData
#  define glClearNamedBufferSubData gload_glClearNamedBufferSubData
#  define glMapNamedBuffer gload_glMapNamedBuffer
#  define glMapNamedBufferRange gload_glMapNamedBufferRange
#  define glUnmapNamedBuffer gload_glUnmapNamedBuffer
#  define glFlushMappedNamedBufferRange gload_glFlushMappedNamedBufferRange
#  define glGetNamedBufferParameteriv gload_glGetNamedBufferParameteriv
#  define glGetNamedBufferParameteri64v gload_glGetNamedBufferParameteri64v
#  define glGetNamedBufferPointerv gload_glGetNamedBufferPointerv
#  define glGetNamedBufferSubData gload_glGetNamedBufferSubData
#  define glCreateFramebuffers gload_glCreateFramebuffers
#  define glNamedFramebufferRenderbuffer gload_glNamedFramebufferRenderbuffer
#  define glNamedFramebufferParameteri gload_glNamedFramebufferParameteri
#  define glNamedFramebufferTexture gload_glNamedFramebufferTexture
#  define glNamedFramebufferTextureLayer gload_glNamedFramebufferTextureLayer
#  define glNamedFramebufferDrawBuffer gload_glNamedFramebufferDrawBuffer
#  define glNamedFramebufferDrawBuffers gload_glNamedFramebufferDrawBuffers
#  define glNamedFramebufferReadBuffer gload_glNamedFramebufferReadBuffer
#  define glInvalidateNamedFramebufferData gload_glInvalidateNamedFramebufferData
#  define glInvalidateNamedFramebufferSubData gload_glInvalidateNamedFramebufferSubData
#  define glClearNamedFramebufferiv gload_glClearNamedFramebufferiv
#  define glClearNamedFramebufferuiv gload_glClearNamedFramebufferuiv
#  define glClearNamedFramebufferfv gload_glClearNamedFramebufferfv
#  define glClearNamedFramebufferfi gload_glClearNamedFramebufferfi
#  define glBlitNamedFramebuffer gload_glBlitNamedFramebuffer
#  define glCheckNamedFramebufferStatus gload_glCheckNamedFramebufferStatus
#  define glGetNamedFramebufferParameteriv gload_glGetNamedFramebufferParameteriv
#  define glGetNamedFramebufferAttachmentParameteriv gload_glGetNamedFramebufferAttachmentParameteriv
#  define glCreateRenderbuffers gload_glCreateRenderbuffers
#  define glNamedRenderbufferStorage gload_glNamedRenderbufferStorage
#  define glNamedRenderbufferStorageMultisample gload_glNamedRenderbufferStorageMultisample
#  define glGetNamedRenderbufferParameteriv gload_glGetNamedRenderbufferParameteriv
#  define glCreateTextures gload_glCreateTextures
#  define glTextureBuffer gload_glTextureBuffer
#  define glTextureBufferRange gload_glTextureBufferRange
#  define glTextureStorage1D gload_glTextureStorage1D
#  define glTextureStorage2D gload_glTextureStorage2D
#  define glTextureStorage3D gload_glTextureStorage3D
#  define glTextureStorage2DMultisample gload_glTextureStorage2DMultisample
#  define glTextureStorage3DMultisample gload_glTextureStorage3DMultisample
#  define glTextureSubImage1D gload_glTextureSubImage1D
#  define glTextureSubImage2D gload_glTextureSubImage2D
#  define glTextureSubImage3D gload_glTextureSubImage3D
#  define glCompressedTextureSubImage1D gload_glCompressedTextureSubImage1D
#  define glCompressedTextureSubImage2D gload_glCompressedTextureSubImage2D
#  define glCompressedTextureSubImage3D gload_glCompressedTextureSubImage3D
#  define glCopyTextureSubImage1D gload_glCopyTextureSubImage1D
#  define glCopyTextureSubImage2D gload_glCopyTextureSubImage2D
#  define glCopyTextureSubImage3D gload_glCopyTextureSubImage3D
#  define glTextureParameterf gload_glTextureParameterf
#  define glTextureParameterfv gload_glTextureParameterfv
#  define glTextureParameteri gload_glTextureParameteri
#  define glTextureParameterIiv gload_glTextureParameterIiv
#  define glTextureParameterIuiv gload_glTextureParameterIuiv
#  define glTextureParameteriv gload_glTextureParameteriv
#  define glGenerateTextureMipmap gload_glGenerateTextureMipmap
#  define glBindTextureUnit gload_glBindTextureUnit
#  define glGetTextureImage gload_glGetTextureImage
#  define glGetCompressedTextureImage gload_glGetCompressedTextureImage
#  define glGetTextureLevelParameterfv gload_glGetTextureLevelParameterfv
#  define glGetTextureLevelParameteriv gload_glGetTextureLevelParameteriv
#  define glGetTextureParameterfv gload_glGetTextureParameterfv
#  define glGetTextureParameterIiv gload_glGetTextureParameterIiv
#  define glGetTextureParameterIuiv gload_glGetTextureParameterIuiv
#  define glGetTextureParameteriv gload_glGetTextureParameteriv
#  define glCreateVertexArrays gload_glCreateVertexArrays
#  define glDisableVertexArrayAttrib gload_glDisableVertexArrayAttrib
#  define glEnableVertexArrayAttrib gload_glEnableVertexArrayAttrib
#  define glVertexArrayElementBuffer gload_glVertexArrayElementBuffer
#  define glVertexArrayVertexBuffer gload_glVertexArrayVertexBuffer
#  define glVertexArrayVertexBuffers gload_glVertexArrayVertexBuffers
#  define glVertexArrayAttribBinding gload_glVertexArrayAttribBinding
#  define glVertexArrayAttribFormat gload_glVertexArrayAttribFormat
#  define glVertexArrayAttribIFormat gload_glVertexArrayAttribIFormat
#  define glVertexArrayAttribLFormat gload_glVertexArrayAttribLFormat
#  define glVertexArrayBindingDivisor gload_glVertexArrayBindingDivisor
#  define glGetVertexArrayiv gload_glGetVertexArrayiv
#  define glGetVertexArrayIndexediv gload_glGetVertexArrayIndexediv
#  define glGetVertexArrayIndexed64iv gload_glGetVertexArrayIndexed64iv
#  define glCreateSamplers gload_glCreateSamplers
#  define glCreateProgramPipelines gload_glCreateProgramPipelines
#  define glCreateQueries gload_glCreateQueries
#  define glGetQueryBufferObjecti64v gload_glGetQueryBufferObjecti64v
#  define glGetQueryBufferObjectiv gload_glGetQueryBufferObjectiv
#  define glGetQueryBufferObjectui64v gload_glGetQueryBufferObjectui64v
#  define glGetQueryBufferObjectuiv gload_glGetQueryBufferObjectuiv
#  define glMemoryBarrierByRegion gload_glMemoryBarrierByRegion
#  define glGetTextureSubImage gload_glGetTextureSubImage
#  define glGetCompressedTextureSubImage gload_glGetCompressedTextureSubImage
#  define glGetGraphicsResetStatus gload_glGetGraphicsResetStatus
#  define glGetnCompressedTexImage gload_glGetnCompressedTexImage
#  define glGetnTexImage gload_glGetnTexImage
#  define glGetnUniformdv gload_glGetnUniformdv
#  define glGetnUniformfv gload_glGetnUniformfv
#  define glGetnUniformiv gload_glGetnUniformiv
#  define glGetnUniformuiv gload_glGetnUniformuiv
#  define glReadnPixels gload_glReadnPixels
#  define glGetnMapdv gload_glGetnMapdv
#  define glGetnMapfv gload_glGetnMapfv
#  define glGetnMapiv gload_glGetnMapiv
#  define glGetnPixelMapfv gload_glGetnPixelMapfv
#  define glGetnPixelMapuiv gload_glGetnPixelMapuiv
#  define glGetnPixelMapusv gload_glGetnPixelMapusv
#  define glGetnPolygonStipple gload_glGetnPolygonStipple
#  define glGetnColorTable gload_glGetnColorTable
#  define glGetnConvolutionFilter gload_glGetnConvolutionFilter
#  define glGetnSeparableFilter gload_glGetnSeparableFilter
#  define glGetnHistogram gload_glGetnHistogram
#  define glGetnMinmax gload_glGetnMinmax
#  define glTextureBarrier gload_glTextureBarrier
# endif /* GL_VERSION_4_5 */
# if defined GL_VERSION_4_6
#  define glSpecializeShader gload_glSpecializeShader
#  define glMultiDrawArraysIndirectCount gload_glMultiDrawArraysIndirectCount
#  define glMultiDrawElementsIndirectCount gload_glMultiDrawElementsIndirectCount
#  define glPolygonOffsetClamp gload_glPolygonOffsetClamp
# endif /* GL_VERSION_4_6 */
# if defined GL_VERSION_ES_CM_1_0
#  define glAlphaFunc gload_glAlphaFunc
#  define glClearColor gload_glClearColor
#  define glClearDepthf gload_glClearDepthf
#  define glClipPlanef gload_glClipPlanef
#  define glColor4f gload_glColor4f
#  define glDepthRangef gload_glDepthRangef
#  define glFogf gload_glFogf
#  define glFogfv gload_glFogfv
#  define glFrustumf gload_glFrustumf
#  define glGetClipPlanef gload_glGetClipPlanef
#  define glGetFloatv gload_glGetFloatv
#  define glGetLightfv gload_glGetLightfv
#  define glGetMaterialfv gload_glGetMaterialfv
#  define glGetTexEnvfv gload_glGetTexEnvfv
#  define glGetTexParameterfv gload_glGetTexParameterfv
#  define glLightModelf gload_glLightModelf
#  define glLightModelfv gload_glLightModelfv
#  define glLightf gload_glLightf
#  define glLightfv gload_glLightfv
#  define glLineWidth gload_glLineWidth
#  define glLoadMatrixf gload_glLoadMatrixf
#  define glMaterialf gload_glMaterialf
#  define glMaterialfv gload_glMaterialfv
#  define glMultMatrixf gload_glMultMatrixf
#  define glMultiTexCoord4f gload_glMultiTexCoord4f
#  define glNormal3f gload_glNormal3f
#  define glOrthof gload_glOrthof
#  define glPointParameterf gload_glPointParameterf
#  define glPointParameterfv gload_glPointParameterfv
#  define glPointSize gload_glPointSize
#  define glPolygonOffset gload_glPolygonOffset
#  define glRotatef gload_glRotatef
#  define glScalef gload_glScalef
#  define glTexEnvf gload_glTexEnvf
#  define glTexEnvfv gload_glTexEnvfv
#  define glTexParameterf gload_glTexParameterf
#  define glTexParameterfv gload_glTexParameterfv
#  define glTranslatef gload_glTranslatef
#  define glActiveTexture gload_glActiveTexture
#  define glAlphaFuncx gload_glAlphaFuncx
#  define glBindBuffer gload_glBindBuffer
#  define glBindTexture gload_glBindTexture
#  define glBlendFunc gload_glBlendFunc
#  define glBufferData gload_glBufferData
#  define glBufferSubData gload_glBufferSubData
#  define glClear gload_glClear
#  define glClearColorx gload_glClearColorx
#  define glClearDepthx gload_glClearDepthx
#  define glClearStencil gload_glClearStencil
#  define glClientActiveTexture gload_glClientActiveTexture
#  define glClipPlanex gload_glClipPlanex
#  define glColor4ub gload_glColor4ub
#  define glColor4x gload_glColor4x
#  define glColorMask gload_glColorMask
#  define glColorPointer gload_glColorPointer
#  define glCompressedTexImage2D gload_glCompressedTexImage2D
#  define glCompressedTexSubImage2D gload_glCompressedTexSubImage2D
#  define glCopyTexImage2D gload_glCopyTexImage2D
#  define glCopyTexSubImage2D gload_glCopyTexSubImage2D
#  define glCullFace gload_glCullFace
#  define glDeleteBuffers gload_glDeleteBuffers
#  define glDeleteTextures gload_glDeleteTextures
#  define glDepthFunc gload_glDepthFunc
#  define glDepthMask gload_glDepthMask
#  define glDepthRangex gload_glDepthRangex
#  define glDisable gload_glDisable
#  define glDisableClientState gload_glDisableClientState
#  define glDrawArrays gload_glDrawArrays
#  define glDrawElements gload_glDrawElements
#  define glEnable gload_glEnable
#  define glEnableClientState gload_glEnableClientState
#  define glFinish gload_glFinish
#  define glFlush gload_glFlush
#  define glFogx gload_glFogx
#  define glFogxv gload_glFogxv
#  define glFrontFace gload_glFrontFace
#  define glFrustumx gload_glFrustumx
#  define glGetBooleanv gload_glGetBooleanv
#  define glGetBufferParameteriv gload_glGetBufferParameteriv
#  define glGetClipPlanex gload_glGetClipPlanex
#  define glGenBuffers gload_glGenBuffers
#  define glGenTextures gload_glGenTextures
#  define glGetError gload_glGetError
#  define glGetFixedv gload_glGetFixedv
#  define glGetIntegerv gload_glGetIntegerv
#  define glGetLightxv gload_glGetLightxv
#  define glGetMaterialxv gload_glGetMaterialxv
#  define glGetPointerv gload_glGetPointerv
#  define glGetString gload_glGetString
#  define glGetTexEnviv gload_glGetTexEnviv
#  define glGetTexEnvxv gload_glGetTexEnvxv
#  define glGetTexParameteriv gload_glGetTexParameteriv
#  define glGetTexParameterxv gload_glGetTexParameterxv
#  define glHint gload_glHint
#  define glIsBuffer gload_glIsBuffer
#  define glIsEnabled gload_glIsEnabled
#  define glIsTexture gload_glIsTexture
#  define glLightModelx gload_glLightModelx
#  define glLightModelxv gload_glLightModelxv
#  define glLightx gload_glLightx
#  define glLightxv gload_glLightxv
#  define glLineWidthx gload_glLineWidthx
#  define glLoadIdentity gload_glLoadIdentity
#  define glLoadMatrixx gload_glLoadMatrixx
#  define glLogicOp gload_glLogicOp
#  define glMaterialx gload_glMaterialx
#  define glMaterialxv gload_glMaterialxv
#  define glMatrixMode gload_glMatrixMode
#  define glMultMatrixx gload_glMultMatrixx
#  define glMultiTexCoord4x gload_glMultiTexCoord4x
#  define glNormal3x gload_glNormal3x
#  define glNormalPointer gload_glNormalPointer
#  define glOrthox gload_glOrthox
#  define glPixelStorei gload_glPixelStorei
#  define glPointParameterx gload_glPointParameterx
#  define glPointParameterxv gload_glPointParameterxv
#  define glPointSizex gload_glPointSizex
#  define glPolygonOffsetx gload_glPolygonOffsetx
#  define glPopMatrix gload_glPopMatrix
#  define glPushMatrix gload_glPushMatrix
#  define glReadPixels gload_glReadPixels
#  define glRotatex gload_glRotatex
#  define glSampleCoverage gload_glSampleCoverage
#  define glSampleCoveragex gload_glSampleCoveragex
#  define glScalex gload_glScalex
#  define glScissor gload_glScissor
#  define glShadeModel gload_glShadeModel
#  define glStencilFunc gload_glStencilFunc
#  define glStencilMask gload_glStencilMask
#  define glStencilOp gload_glStencilOp
#  define glTexCoordPointer gload_glTexCoordPointer
#  define glTexEnvi gload_glTexEnvi
#  define glTexEnvx gload_glTexEnvx
#  define glTexEnviv gload_glTexEnviv
#  define glTexEnvxv gload_glTexEnvxv
#  define glTexImage2D gload_glTexImage2D
#  define glTexParameteri gload_glTexParameteri
#  define glTexParameterx gload_glTexParameterx
#  define glTexParameteriv gload_glTexParameteriv
#  define glTexParameterxv gload_glTexParameterxv
#  define glTexSubImage2D gload_glTexSubImage2D
#  define glTranslatex gload_glTranslatex
#  define glVertexPointer gload_glVertexPointer
#  define glViewport gload_glViewport
# endif /* GL_VERSION_ES_CM_1_0 */
# if defined GL_ES_VERSION_2_0
#  define glActiveTexture gload_glActiveTexture
#  define glAttachShader gload_glAttachShader
#  define glBindAttribLocation gload_glBindAttribLocation
#  define glBindBuffer gload_glBindBuffer
#  define glBindFramebuffer gload_glBindFramebuffer
#  define glBindRenderbuffer gload_glBindRenderbuffer
#  define glBindTexture gload_glBindTexture
#  define glBlendColor gload_glBlendColor
#  define glBlendEquation gload_glBlendEquation
#  define glBlendEquationSeparate gload_glBlendEquationSeparate
#  define glBlendFunc gload_glBlendFunc
#  define glBlendFuncSeparate gload_glBlendFuncSeparate
#  define glBufferData gload_glBufferData
#  define glBufferSubData gload_glBufferSubData
#  define glCheckFramebufferStatus gload_glCheckFramebufferStatus
#  define glClear gload_glClear
#  define glClearColor gload_glClearColor
#  define glClearDepthf gload_glClearDepthf
#  define glClearStencil gload_glClearStencil
#  define glColorMask gload_glColorMask
#  define glCompileShader gload_glCompileShader
#  define glCompressedTexImage2D gload_glCompressedTexImage2D
#  define glCompressedTexSubImage2D gload_glCompressedTexSubImage2D
#  define glCopyTexImage2D gload_glCopyTexImage2D
#  define glCopyTexSubImage2D gload_glCopyTexSubImage2D
#  define glCreateProgram gload_glCreateProgram
#  define glCreateShader gload_glCreateShader
#  define glCullFace gload_glCullFace
#  define glDeleteBuffers gload_glDeleteBuffers
#  define glDeleteFramebuffers gload_glDeleteFramebuffers
#  define glDeleteProgram gload_glDeleteProgram
#  define glDeleteRenderbuffers gload_glDeleteRenderbuffers
#  define glDeleteShader gload_glDeleteShader
#  define glDeleteTextures gload_glDeleteTextures
#  define glDepthFunc gload_glDepthFunc
#  define glDepthMask gload_glDepthMask
#  define glDepthRangef gload_glDepthRangef
#  define glDetachShader gload_glDetachShader
#  define glDisable gload_glDisable
#  define glDisableVertexAttribArray gload_glDisableVertexAttribArray
#  define glDrawArrays gload_glDrawArrays
#  define glDrawElements gload_glDrawElements
#  define glEnable gload_glEnable
#  define glEnableVertexAttribArray gload_glEnableVertexAttribArray
#  define glFinish gload_glFinish
#  define glFlush gload_glFlush
#  define glFramebufferRenderbuffer gload_glFramebufferRenderbuffer
#  define glFramebufferTexture2D gload_glFramebufferTexture2D
#  define glFrontFace gload_glFrontFace
#  define glGenBuffers gload_glGenBuffers
#  define glGenerateMipmap gload_glGenerateMipmap
#  define glGenFramebuffers gload_glGenFramebuffers
#  define glGenRenderbuffers gload_glGenRenderbuffers
#  define glGenTextures gload_glGenTextures
#  define glGetActiveAttrib gload_glGetActiveAttrib
#  define glGetActiveUniform gload_glGetActiveUniform
#  define glGetAttachedShaders gload_glGetAttachedShaders
#  define glGetAttribLocation gload_glGetAttribLocation
#  define glGetBooleanv gload_glGetBooleanv
#  define glGetBufferParameteriv gload_glGetBufferParameteriv
#  define glGetError gload_glGetError
#  define glGetFloatv gload_glGetFloatv
#  define glGetFramebufferAttachmentParameteriv gload_glGetFramebufferAttachmentParameteriv
#  define glGetIntegerv gload_glGetIntegerv
#  define glGetProgramiv gload_glGetProgramiv
#  define glGetProgramInfoLog gload_glGetProgramInfoLog
#  define glGetRenderbufferParameteriv gload_glGetRenderbufferParameteriv
#  define glGetShaderiv gload_glGetShaderiv
#  define glGetShaderInfoLog gload_glGetShaderInfoLog
#  define glGetShaderPrecisionFormat gload_glGetShaderPrecisionFormat
#  define glGetShaderSource gload_glGetShaderSource
#  define glGetString gload_glGetString
#  define glGetTexParameterfv gload_glGetTexParameterfv
#  define glGetTexParameteriv gload_glGetTexParameteriv
#  define glGetUniformfv gload_glGetUniformfv
#  define glGetUniformiv gload_glGetUniformiv
#  define glGetUniformLocation gload_glGetUniformLocation
#  define glGetVertexAttribfv gload_glGetVertexAttribfv
#  define glGetVertexAttribiv gload_glGetVertexAttribiv
#  define glGetVertexAttribPointerv gload_glGetVertexAttribPointerv
#  define glHint gload_glHint
#  define glIsBuffer gload_glIsBuffer
#  define glIsEnabled gload_glIsEnabled
#  define glIsFramebuffer gload_glIsFramebuffer
#  define glIsProgram gload_glIsProgram
#  define glIsRenderbuffer gload_glIsRenderbuffer
#  define glIsShader gload_glIsShader
#  define glIsTexture gload_glIsTexture
#  define glLineWidth gload_glLineWidth
#  define glLinkProgram gload_glLinkProgram
#  define glPixelStorei gload_glPixelStorei
#  define glPolygonOffset gload_glPolygonOffset
#  define glReadPixels gload_glReadPixels
#  define glReleaseShaderCompiler gload_glReleaseShaderCompiler
#  define glRenderbufferStorage gload_glRenderbufferStorage
#  define glSampleCoverage gload_glSampleCoverage
#  define glScissor gload_glScissor
#  define glShaderBinary gload_glShaderBinary
#  define glShaderSource gload_glShaderSource
#  define glStencilFunc gload_glStencilFunc
#  define glStencilFuncSeparate gload_glStencilFuncSeparate
#  define glStencilMask gload_glStencilMask
#  define glStencilMaskSeparate gload_glStencilMaskSeparate
#  define glStencilOp gload_glStencilOp
#  define glStencilOpSeparate gload_glStencilOpSeparate
#  define glTexImage2D gload_glTexImage2D
#  define glTexParameterf gload_glTexParameterf
#  define glTexParameterfv gload_glTexParameterfv
#  define glTexParameteri gload_glTexParameteri
#  define glTexParameteriv gload_glTexParameteriv
#  define glTexSubImage2D gload_glTexSubImage2D
#  define glUniform1f gload_glUniform1f
#  define glUniform1fv gload_glUniform1fv
#  define glUniform1i gload_glUniform1i
#  define glUniform1iv gload_glUniform1iv
#  define glUniform2f gload_glUniform2f
#  define glUniform2fv gload_glUniform2fv
#  define glUniform2i gload_glUniform2i
#  define glUniform2iv gload_glUniform2iv
#  define glUniform3f gload_glUniform3f
#  define glUniform3fv gload_glUniform3fv
#  define glUniform3i gload_glUniform3i
#  define glUniform3iv gload_glUniform3iv
#  define glUniform4f gload_glUniform4f
#  define glUniform4fv gload_glUniform4fv
#  define glUniform4i gload_glUniform4i
#  define glUniform4iv gload_glUniform4iv
#  define glUniformMatrix2fv gload_glUniformMatrix2fv
#  define glUniformMatrix3fv gload_glUniformMatrix3fv
#  define glUniformMatrix4fv gload_glUniformMatrix4fv
#  define glUseProgram gload_glUseProgram
#  define glValidateProgram gload_glValidateProgram
#  define glVertexAttrib1f gload_glVertexAttrib1f
#  define glVertexAttrib1fv gload_glVertexAttrib1fv
#  define glVertexAttrib2f gload_glVertexAttrib2f
#  define glVertexAttrib2fv gload_glVertexAttrib2fv
#  define glVertexAttrib3f gload_glVertexAttrib3f
#  define glVertexAttrib3fv gload_glVertexAttrib3fv
#  define glVertexAttrib4f gload_glVertexAttrib4f
#  define glVertexAttrib4fv gload_glVertexAttrib4fv
#  define glVertexAttribPointer gload_glVertexAttribPointer
#  define glViewport gload_glViewport
# endif /* GL_ES_VERSION_2_0 */
# if defined GL_ES_VERSION_3_0
#  define glReadBuffer gload_glReadBuffer
#  define glDrawRangeElements gload_glDrawRangeElements
#  define glTexImage3D gload_glTexImage3D
#  define glTexSubImage3D gload_glTexSubImage3D
#  define glCopyTexSubImage3D gload_glCopyTexSubImage3D
#  define glCompressedTexImage3D gload_glCompressedTexImage3D
#  define glCompressedTexSubImage3D gload_glCompressedTexSubImage3D
#  define glGenQueries gload_glGenQueries
#  define glDeleteQueries gload_glDeleteQueries
#  define glIsQuery gload_glIsQuery
#  define glBeginQuery gload_glBeginQuery
#  define glEndQuery gload_glEndQuery
#  define glGetQueryiv gload_glGetQueryiv
#  define glGetQueryObjectuiv gload_glGetQueryObjectuiv
#  define glUnmapBuffer gload_glUnmapBuffer
#  define glGetBufferPointerv gload_glGetBufferPointerv
#  define glDrawBuffers gload_glDrawBuffers
#  define glUniformMatrix2x3fv gload_glUniformMatrix2x3fv
#  define glUniformMatrix3x2fv gload_glUniformMatrix3x2fv
#  define glUniformMatrix2x4fv gload_glUniformMatrix2x4fv
#  define glUniformMatrix4x2fv gload_glUniformMatrix4x2fv
#  define glUniformMatrix3x4fv gload_glUniformMatrix3x4fv
#  define glUniformMatrix4x3fv gload_glUniformMatrix4x3fv
#  define glBlitFramebuffer gload_glBlitFramebuffer
#  define glRenderbufferStorageMultisample gload_glRenderbufferStorageMultisample
#  define glFramebufferTextureLayer gload_glFramebufferTextureLayer
#  define glMapBufferRange gload_glMapBufferRange
#  define glFlushMappedBufferRange gload_glFlushMappedBufferRange
#  define glBindVertexArray gload_glBindVertexArray
#  define glDeleteVertexArrays gload_glDeleteVertexArrays
#  define glGenVertexArrays gload_glGenVertexArrays
#  define glIsVertexArray gload_glIsVertexArray
#  define glGetIntegeri_v gload_glGetIntegeri_v
#  define glBeginTransformFeedback gload_glBeginTransformFeedback
#  define glEndTransformFeedback gload_glEndTransformFeedback
#  define glBindBufferRange gload_glBindBufferRange
#  define glBindBufferBase gload_glBindBufferBase
#  define glTransformFeedbackVaryings gload_glTransformFeedbackVaryings
#  define glGetTransformFeedbackVarying gload_glGetTransformFeedbackVarying
#  define glVertexAttribIPointer gload_glVertexAttribIPointer
#  define glGetVertexAttribIiv gload_glGetVertexAttribIiv
#  define glGetVertexAttribIuiv gload_glGetVertexAttribIuiv
#  define glVertexAttribI4i gload_glVertexAttribI4i
#  define glVertexAttribI4ui gload_glVertexAttribI4ui
#  define glVertexAttribI4iv gload_glVertexAttribI4iv
#  define glVertexAttribI4uiv gload_glVertexAttribI4uiv
#  define glGetUniformuiv gload_glGetUniformuiv
#  define glGetFragDataLocation gload_glGetFragDataLocation
#  define glUniform1ui gload_glUniform1ui
#  define glUniform2ui gload_glUniform2ui
#  define glUniform3ui gload_glUniform3ui
#  define glUniform4ui gload_glUniform4ui
#  define glUniform1uiv gload_glUniform1uiv
#  define glUniform2uiv gload_glUniform2uiv
#  define glUniform3uiv gload_glUniform3uiv
#  define glUniform4uiv gload_glUniform4uiv
#  define glClearBufferiv gload_glClearBufferiv
#  define glClearBufferuiv gload_glClearBufferuiv
#  define glClearBufferfv gload_glClearBufferfv
#  define glClearBufferfi gload_glClearBufferfi
#  define glGetStringi gload_glGetStringi
#  define glCopyBufferSubData gload_glCopyBufferSubData
#  define glGetUniformIndices gload_glGetUniformIndices
#  define glGetActiveUniformsiv gload_glGetActiveUniformsiv
#  define glGetUniformBlockIndex gload_glGetUniformBlockIndex
#  define glGetActiveUniformBlockiv gload_glGetActiveUniformBlockiv
#  define glGetActiveUniformBlockName gload_glGetActiveUniformBlockName
#  define glUniformBlockBinding gload_glUniformBlockBinding
#  define glDrawArraysInstanced gload_glDrawArraysInstanced
#  define glDrawElementsInstanced gload_glDrawElementsInstanced
#  define glFenceSync gload_glFenceSync
#  define glIsSync gload_glIsSync
#  define glDeleteSync gload_glDeleteSync
#  define glClientWaitSync gload_glClientWaitSync
#  define glWaitSync gload_glWaitSync
#  define glGetInteger64v gload_glGetInteger64v
#  define glGetSynciv gload_glGetSynciv
#  define glGetInteger64i_v gload_glGetInteger64i_v
#  define glGetBufferParameteri64v gload_glGetBufferParameteri64v
#  define glGenSamplers gload_glGenSamplers
#  define glDeleteSamplers gload_glDeleteSamplers
#  define glIsSampler gload_glIsSampler
#  define glBindSampler gload_glBindSampler
#  define glSamplerParameteri gload_glSamplerParameteri
#  define glSamplerParameteriv gload_glSamplerParameteriv
#  define glSamplerParameterf gload_glSamplerParameterf
#  define glSamplerParameterfv gload_glSamplerParameterfv
#  define glGetSamplerParameteriv gload_glGetSamplerParameteriv
#  define glGetSamplerParameterfv gload_glGetSamplerParameterfv
#  define glVertexAttribDivisor gload_glVertexAttribDivisor
#  define glBindTransformFeedback gload_glBindTransformFeedback
#  define glDeleteTransformFeedbacks gload_glDeleteTransformFeedbacks
#  define glGenTransformFeedbacks gload_glGenTransformFeedbacks
#  define glIsTransformFeedback gload_glIsTransformFeedback
#  define glPauseTransformFeedback gload_glPauseTransformFeedback
#  define glResumeTransformFeedback gload_glResumeTransformFeedback
#  define glGetProgramBinary gload_glGetProgramBinary
#  define glProgramBinary gload_glProgramBinary
#  define glProgramParameteri gload_glProgramParameteri
#  define glInvalidateFramebuffer gload_glInvalidateFramebuffer
#  define glInvalidateSubFramebuffer gload_glInvalidateSubFramebuffer
#  define glTexStorage2D gload_glTexStorage2D
#  define glTexStorage3D gload_glTexStorage3D
#  define glGetInternalformativ gload_glGetInternalformativ
# endif /* GL_ES_VERSION_3_0 */
# if defined GL_ES_VERSION_3_1
#  define glDispatchCompute gload_glDispatchCompute
#  define glDispatchComputeIndirect gload_glDispatchComputeIndirect
#  define glDrawArraysIndirect gload_glDrawArraysIndirect
#  define glDrawElementsIndirect gload_glDrawElementsIndirect
#  define glFramebufferParameteri gload_glFramebufferParameteri
#  define glGetFramebufferParameteriv gload_glGetFramebufferParameteriv
#  define glGetProgramInterfaceiv gload_glGetProgramInterfaceiv
#  define glGetProgramResourceIndex gload_glGetProgramResourceIndex
#  define glGetProgramResourceName gload_glGetProgramResourceName
#  define glGetProgramResourceiv gload_glGetProgramResourceiv
#  define glGetProgramResourceLocation gload_glGetProgramResourceLocation
#  define glUseProgramStages gload_glUseProgramStages
#  define glActiveShaderProgram gload_glActiveShaderProgram
#  define glCreateShaderProgramv gload_glCreateShaderProgramv
#  define glBindProgramPipeline gload_glBindProgramPipeline
#  define glDeleteProgramPipelines gload_glDeleteProgramPipelines
#  define glGenProgramPipelines gload_glGenProgramPipelines
#  define glIsProgramPipeline gload_glIsProgramPipeline
#  define glGetProgramPipelineiv gload_glGetProgramPipelineiv
#  define glProgramUniform1i gload_glProgramUniform1i
#  define glProgramUniform2i gload_glProgramUniform2i
#  define glProgramUniform3i gload_glProgramUniform3i
#  define glProgramUniform4i gload_glProgramUniform4i
#  define glProgramUniform1ui gload_glProgramUniform1ui
#  define glProgramUniform2ui gload_glProgramUniform2ui
#  define glProgramUniform3ui gload_glProgramUniform3ui
#  define glProgramUniform4ui gload_glProgramUniform4ui
#  define glProgramUniform1f gload_glProgramUniform1f
#  define glProgramUniform2f gload_glProgramUniform2f
#  define glProgramUniform3f gload_glProgramUniform3f
#  define glProgramUniform4f gload_glProgramUniform4f
#  define glProgramUniform1iv gload_glProgramUniform1iv
#  define glProgramUniform2iv gload_glProgramUniform2iv
#  define glProgramUniform3iv gload_glProgramUniform3iv
#  define glProgramUniform4iv gload_glProgramUniform4iv
#  define glProgramUniform1uiv gload_glProgramUniform1uiv
#  define glProgramUniform2uiv gload_glProgramUniform2uiv
#  define glProgramUniform3uiv gload_glProgramUniform3uiv
#  define glProgramUniform4uiv gload_glProgramUniform4uiv
#  define glProgramUniform1fv gload_glProgramUniform1fv
#  define glProgramUniform2fv gload_glProgramUniform2fv
#  define glProgramUniform3fv gload_glProgramUniform3fv
#  define glProgramUniform4fv gload_glProgramUniform4fv
#  define glProgramUniformMatrix2fv gload_glProgramUniformMatrix2fv
#  define glProgramUniformMatrix3fv gload_glProgramUniformMatrix3fv
#  define glProgramUniformMatrix4fv gload_glProgramUniformMatrix4fv
#  define glProgramUniformMatrix2x3fv gload_glProgramUniformMatrix2x3fv
#  define glProgramUniformMatrix3x2fv gload_glProgramUniformMatrix3x2fv
#  define glProgramUniformMatrix2x4fv gload_glProgramUniformMatrix2x4fv
#  define glProgramUniformMatrix4x2fv gload_glProgramUniformMatrix4x2fv
#  define glProgramUniformMatrix3x4fv gload_glProgramUniformMatrix3x4fv
#  define glProgramUniformMatrix4x3fv gload_glProgramUniformMatrix4x3fv
#  define glValidateProgramPipeline gload_glValidateProgramPipeline
#  define glGetProgramPipelineInfoLog gload_glGetProgramPipelineInfoLog
#  define glBindImageTexture gload_glBindImageTexture
#  define glGetBooleani_v gload_glGetBooleani_v
#  define glMemoryBarrier gload_glMemoryBarrier
#  define glMemoryBarrierByRegion gload_glMemoryBarrierByRegion
#  define glTexStorage2DMultisample gload_glTexStorage2DMultisample
#  define glGetMultisamplefv gload_glGetMultisamplefv
#  define glSampleMaski gload_glSampleMaski
#  define glGetTexLevelParameteriv gload_glGetTexLevelParameteriv
#  define glGetTexLevelParameterfv gload_glGetTexLevelParameterfv
#  define glBindVertexBuffer gload_glBindVertexBuffer
#  define glVertexAttribFormat gload_glVertexAttribFormat
#  define glVertexAttribIFormat gload_glVertexAttribIFormat
#  define glVertexAttribBinding gload_glVertexAttribBinding
#  define glVertexBindingDivisor gload_glVertexBindingDivisor
# endif /* GL_ES_VERSION_3_1 */
# if defined GL_ES_VERSION_3_2
#  define glBlendBarrier gload_glBlendBarrier
#  define glCopyImageSubData gload_glCopyImageSubData
#  define glDebugMessageControl gload_glDebugMessageControl
#  define glDebugMessageInsert gload_glDebugMessageInsert
#  define glDebugMessageCallback gload_glDebugMessageCallback
#  define glGetDebugMessageLog gload_glGetDebugMessageLog
#  define glPushDebugGroup gload_glPushDebugGroup
#  define glPopDebugGroup gload_glPopDebugGroup
#  define glObjectLabel gload_glObjectLabel
#  define glGetObjectLabel gload_glGetObjectLabel
#  define glObjectPtrLabel gload_glObjectPtrLabel
#  define glGetObjectPtrLabel gload_glGetObjectPtrLabel
#  define glGetPointerv gload_glGetPointerv
#  define glEnablei gload_glEnablei
#  define glDisablei gload_glDisablei
#  define glBlendEquationi gload_glBlendEquationi
#  define glBlendEquationSeparatei gload_glBlendEquationSeparatei
#  define glBlendFunci gload_glBlendFunci
#  define glBlendFuncSeparatei gload_glBlendFuncSeparatei
#  define glColorMaski gload_glColorMaski
#  define glIsEnabledi gload_glIsEnabledi
#  define glDrawElementsBaseVertex gload_glDrawElementsBaseVertex
#  define glDrawRangeElementsBaseVertex gload_glDrawRangeElementsBaseVertex
#  define glDrawElementsInstancedBaseVertex gload_glDrawElementsInstancedBaseVertex
#  define glFramebufferTexture gload_glFramebufferTexture
#  define glPrimitiveBoundingBox gload_glPrimitiveBoundingBox
#  define glGetGraphicsResetStatus gload_glGetGraphicsResetStatus
#  define glReadnPixels gload_glReadnPixels
#  define glGetnUniformfv gload_glGetnUniformfv
#  define glGetnUniformiv gload_glGetnUniformiv
#  define glGetnUniformuiv gload_glGetnUniformuiv
#  define glMinSampleShading gload_glMinSampleShading
#  define glPatchParameteri gload_glPatchParameteri
#  define glTexParameterIiv gload_glTexParameterIiv
#  define glTexParameterIuiv gload_glTexParameterIuiv
#  define glGetTexParameterIiv gload_glGetTexParameterIiv
#  define glGetTexParameterIuiv gload_glGetTexParameterIuiv
#  define glSamplerParameterIiv gload_glSamplerParameterIiv
#  define glSamplerParameterIuiv gload_glSamplerParameterIuiv
#  define glGetSamplerParameterIiv gload_glGetSamplerParameterIiv
#  define glGetSamplerParameterIuiv gload_glGetSamplerParameterIuiv
#  define glTexBuffer gload_glTexBuffer
#  define glTexBufferRange gload_glTexBufferRange
#  define glTexStorage3DMultisample gload_glTexStorage3DMultisample
# endif /* GL_ES_VERSION_3_2 */
# if defined GL_SC_VERSION_2_0
#  define glActiveTexture gload_glActiveTexture
#  define glBindBuffer gload_glBindBuffer
#  define glBindFramebuffer gload_glBindFramebuffer
#  define glBindRenderbuffer gload_glBindRenderbuffer
#  define glBindTexture gload_glBindTexture
#  define glBlendColor gload_glBlendColor
#  define glBlendEquation gload_glBlendEquation
#  define glBlendEquationSeparate gload_glBlendEquationSeparate
#  define glBlendFunc gload_glBlendFunc
#  define glBlendFuncSeparate gload_glBlendFuncSeparate
#  define glBufferData gload_glBufferData
#  define glBufferSubData gload_glBufferSubData
#  define glCheckFramebufferStatus gload_glCheckFramebufferStatus
#  define glClear gload_glClear
#  define glClearColor gload_glClearColor
#  define glClearDepthf gload_glClearDepthf
#  define glClearStencil gload_glClearStencil
#  define glColorMask gload_glColorMask
#  define glCompressedTexSubImage2D gload_glCompressedTexSubImage2D
#  define glCreateProgram gload_glCreateProgram
#  define glCullFace gload_glCullFace
#  define glDepthFunc gload_glDepthFunc
#  define glDepthMask gload_glDepthMask
#  define glDepthRangef gload_glDepthRangef
#  define glDisable gload_glDisable
#  define glDisableVertexAttribArray gload_glDisableVertexAttribArray
#  define glDrawArrays gload_glDrawArrays
#  define glDrawRangeElements gload_glDrawRangeElements
#  define glEnable gload_glEnable
#  define glEnableVertexAttribArray gload_glEnableVertexAttribArray
#  define glFinish gload_glFinish
#  define glFlush gload_glFlush
#  define glFramebufferRenderbuffer gload_glFramebufferRenderbuffer
#  define glFramebufferTexture2D gload_glFramebufferTexture2D
#  define glFrontFace gload_glFrontFace
#  define glGenBuffers gload_glGenBuffers
#  define glGenerateMipmap gload_glGenerateMipmap
#  define glGenFramebuffers gload_glGenFramebuffers
#  define glGenRenderbuffers gload_glGenRenderbuffers
#  define glGenTextures gload_glGenTextures
#  define glGetAttribLocation gload_glGetAttribLocation
#  define glGetBooleanv gload_glGetBooleanv
#  define glGetBufferParameteriv gload_glGetBufferParameteriv
#  define glGetError gload_glGetError
#  define glGetFloatv gload_glGetFloatv
#  define glGetFramebufferAttachmentParameteriv gload_glGetFramebufferAttachmentParameteriv
#  define glGetGraphicsResetStatus gload_glGetGraphicsResetStatus
#  define glGetIntegerv gload_glGetIntegerv
#  define glGetProgramiv gload_glGetProgramiv
#  define glGetRenderbufferParameteriv gload_glGetRenderbufferParameteriv
#  define glGetString gload_glGetString
#  define glGetTexParameterfv gload_glGetTexParameterfv
#  define glGetTexParameteriv gload_glGetTexParameteriv
#  define glGetnUniformfv gload_glGetnUniformfv
#  define glGetnUniformiv gload_glGetnUniformiv
#  define glGetUniformLocation gload_glGetUniformLocation
#  define glGetVertexAttribfv gload_glGetVertexAttribfv
#  define glGetVertexAttribiv gload_glGetVertexAttribiv
#  define glGetVertexAttribPointerv gload_glGetVertexAttribPointerv
#  define glHint gload_glHint
#  define glIsEnabled gload_glIsEnabled
#  define glLineWidth gload_glLineWidth
#  define glPixelStorei gload_glPixelStorei
#  define glPolygonOffset gload_glPolygonOffset
#  define glProgramBinary gload_glProgramBinary
#  define glReadnPixels gload_glReadnPixels
#  define glRenderbufferStorage gload_glRenderbufferStorage
#  define glSampleCoverage gload_glSampleCoverage
#  define glScissor gload_glScissor
#  define glStencilFunc gload_glStencilFunc
#  define glStencilFuncSeparate gload_glStencilFuncSeparate
#  define glStencilMask gload_glStencilMask
#  define glStencilMaskSeparate gload_glStencilMaskSeparate
#  define glStencilOp gload_glStencilOp
#  define glStencilOpSeparate gload_glStencilOpSeparate
#  define glTexStorage2D gload_glTexStorage2D
#  define glTexParameterf gload_glTexParameterf
#  define glTexParameterfv gload_glTexParameterfv
#  define glTexParameteri gload_glTexParameteri
#  define glTexParameteriv gload_glTexParameteriv
#  define glTexSubImage2D gload_glTexSubImage2D
#  define glUniform1f gload_glUniform1f
#  define glUniform1fv gload_glUniform1fv
#  define glUniform1i gload_glUniform1i
#  define glUniform1iv gload_glUniform1iv
#  define glUniform2f gload_glUniform2f
#  define glUniform2fv gload_glUniform2fv
#  define glUniform2i gload_glUniform2i
#  define glUniform2iv gload_glUniform2iv
#  define glUniform3f gload_glUniform3f
#  define glUniform3fv gload_glUniform3fv
#  define glUniform3i gload_glUniform3i
#  define glUniform3iv gload_glUniform3iv
#  define glUniform4f gload_glUniform4f
#  define glUniform4fv gload_glUniform4fv
#  define glUniform4i gload_glUniform4i
#  define glUniform4iv gload_glUniform4iv
#  define glUniformMatrix2fv gload_glUniformMatrix2fv
#  define glUniformMatrix3fv gload_glUniformMatrix3fv
#  define glUniformMatrix4fv gload_glUniformMatrix4fv
#  define glUseProgram gload_glUseProgram
#  define glVertexAttrib1f gload_glVertexAttrib1f
#  define glVertexAttrib1fv gload_glVertexAttrib1fv
#  define glVertexAttrib2f gload_glVertexAttrib2f
#  define glVertexAttrib2fv gload_glVertexAttrib2fv
#  define glVertexAttrib3f gload_glVertexAttrib3f
#  define glVertexAttrib3fv gload_glVertexAttrib3fv
#  define glVertexAttrib4f gload_glVertexAttrib4f
#  define glVertexAttrib4fv gload_glVertexAttrib4fv
#  define glVertexAttribPointer gload_glVertexAttribPointer
#  define glViewport gload_glViewport
# endif /* GL_SC_VERSION_2_0 */
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
#  if defined (GLOAD_LINUX) || defined (GLOAD_APPLE)
#   include <dlfcn.h>
#  endif /* GLOAD_LINUX, GLOAD_APPLE*/
#  if defined (GLOAD_WIN32)
#   include <libloaderapi.h>
#  endif /* GLOAD_WIN32 */
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

/* `struct s_nameaddr` - key-value-pair structure of proc. names and addresses.
 * */

struct s_nameaddr {

#  if !defined (__cplusplus)
    const char          *name;
#  else
    const std::string   &name;
#  endif /* __cplusplus */

    void        **addr;
};

/* `static struct s_nameaddr g_nameaddr` - array of s_nameaddr structures, null-terminated.
 * */

static struct s_nameaddr    g_nameaddr[] = {
    
#  if defined GL_VERSION_1_0

   { "glCullFace", (void **) &gload_glCullFace },
   { "glFrontFace", (void **) &gload_glFrontFace },
   { "glHint", (void **) &gload_glHint },
   { "glLineWidth", (void **) &gload_glLineWidth },
   { "glPointSize", (void **) &gload_glPointSize },
   { "glPolygonMode", (void **) &gload_glPolygonMode },
   { "glScissor", (void **) &gload_glScissor },
   { "glTexParameterf", (void **) &gload_glTexParameterf },
   { "glTexParameterfv", (void **) &gload_glTexParameterfv },
   { "glTexParameteri", (void **) &gload_glTexParameteri },
   { "glTexParameteriv", (void **) &gload_glTexParameteriv },
   { "glTexImage1D", (void **) &gload_glTexImage1D },
   { "glTexImage2D", (void **) &gload_glTexImage2D },
   { "glDrawBuffer", (void **) &gload_glDrawBuffer },
   { "glClear", (void **) &gload_glClear },
   { "glClearColor", (void **) &gload_glClearColor },
   { "glClearStencil", (void **) &gload_glClearStencil },
   { "glClearDepth", (void **) &gload_glClearDepth },
   { "glStencilMask", (void **) &gload_glStencilMask },
   { "glColorMask", (void **) &gload_glColorMask },
   { "glDepthMask", (void **) &gload_glDepthMask },
   { "glDisable", (void **) &gload_glDisable },
   { "glEnable", (void **) &gload_glEnable },
   { "glFinish", (void **) &gload_glFinish },
   { "glFlush", (void **) &gload_glFlush },
   { "glBlendFunc", (void **) &gload_glBlendFunc },
   { "glLogicOp", (void **) &gload_glLogicOp },
   { "glStencilFunc", (void **) &gload_glStencilFunc },
   { "glStencilOp", (void **) &gload_glStencilOp },
   { "glDepthFunc", (void **) &gload_glDepthFunc },
   { "glPixelStoref", (void **) &gload_glPixelStoref },
   { "glPixelStorei", (void **) &gload_glPixelStorei },
   { "glReadBuffer", (void **) &gload_glReadBuffer },
   { "glReadPixels", (void **) &gload_glReadPixels },
   { "glGetBooleanv", (void **) &gload_glGetBooleanv },
   { "glGetDoublev", (void **) &gload_glGetDoublev },
   { "glGetError", (void **) &gload_glGetError },
   { "glGetFloatv", (void **) &gload_glGetFloatv },
   { "glGetIntegerv", (void **) &gload_glGetIntegerv },
   { "glGetString", (void **) &gload_glGetString },
   { "glGetTexImage", (void **) &gload_glGetTexImage },
   { "glGetTexParameterfv", (void **) &gload_glGetTexParameterfv },
   { "glGetTexParameteriv", (void **) &gload_glGetTexParameteriv },
   { "glGetTexLevelParameterfv", (void **) &gload_glGetTexLevelParameterfv },
   { "glGetTexLevelParameteriv", (void **) &gload_glGetTexLevelParameteriv },
   { "glIsEnabled", (void **) &gload_glIsEnabled },
   { "glDepthRange", (void **) &gload_glDepthRange },
   { "glViewport", (void **) &gload_glViewport },
   { "glNewList", (void **) &gload_glNewList },
   { "glEndList", (void **) &gload_glEndList },
   { "glCallList", (void **) &gload_glCallList },
   { "glCallLists", (void **) &gload_glCallLists },
   { "glDeleteLists", (void **) &gload_glDeleteLists },
   { "glGenLists", (void **) &gload_glGenLists },
   { "glListBase", (void **) &gload_glListBase },
   { "glBegin", (void **) &gload_glBegin },
   { "glBitmap", (void **) &gload_glBitmap },
   { "glColor3b", (void **) &gload_glColor3b },
   { "glColor3bv", (void **) &gload_glColor3bv },
   { "glColor3d", (void **) &gload_glColor3d },
   { "glColor3dv", (void **) &gload_glColor3dv },
   { "glColor3f", (void **) &gload_glColor3f },
   { "glColor3fv", (void **) &gload_glColor3fv },
   { "glColor3i", (void **) &gload_glColor3i },
   { "glColor3iv", (void **) &gload_glColor3iv },
   { "glColor3s", (void **) &gload_glColor3s },
   { "glColor3sv", (void **) &gload_glColor3sv },
   { "glColor3ub", (void **) &gload_glColor3ub },
   { "glColor3ubv", (void **) &gload_glColor3ubv },
   { "glColor3ui", (void **) &gload_glColor3ui },
   { "glColor3uiv", (void **) &gload_glColor3uiv },
   { "glColor3us", (void **) &gload_glColor3us },
   { "glColor3usv", (void **) &gload_glColor3usv },
   { "glColor4b", (void **) &gload_glColor4b },
   { "glColor4bv", (void **) &gload_glColor4bv },
   { "glColor4d", (void **) &gload_glColor4d },
   { "glColor4dv", (void **) &gload_glColor4dv },
   { "glColor4f", (void **) &gload_glColor4f },
   { "glColor4fv", (void **) &gload_glColor4fv },
   { "glColor4i", (void **) &gload_glColor4i },
   { "glColor4iv", (void **) &gload_glColor4iv },
   { "glColor4s", (void **) &gload_glColor4s },
   { "glColor4sv", (void **) &gload_glColor4sv },
   { "glColor4ub", (void **) &gload_glColor4ub },
   { "glColor4ubv", (void **) &gload_glColor4ubv },
   { "glColor4ui", (void **) &gload_glColor4ui },
   { "glColor4uiv", (void **) &gload_glColor4uiv },
   { "glColor4us", (void **) &gload_glColor4us },
   { "glColor4usv", (void **) &gload_glColor4usv },
   { "glEdgeFlag", (void **) &gload_glEdgeFlag },
   { "glEdgeFlagv", (void **) &gload_glEdgeFlagv },
   { "glEnd", (void **) &gload_glEnd },
   { "glIndexd", (void **) &gload_glIndexd },
   { "glIndexdv", (void **) &gload_glIndexdv },
   { "glIndexf", (void **) &gload_glIndexf },
   { "glIndexfv", (void **) &gload_glIndexfv },
   { "glIndexi", (void **) &gload_glIndexi },
   { "glIndexiv", (void **) &gload_glIndexiv },
   { "glIndexs", (void **) &gload_glIndexs },
   { "glIndexsv", (void **) &gload_glIndexsv },
   { "glNormal3b", (void **) &gload_glNormal3b },
   { "glNormal3bv", (void **) &gload_glNormal3bv },
   { "glNormal3d", (void **) &gload_glNormal3d },
   { "glNormal3dv", (void **) &gload_glNormal3dv },
   { "glNormal3f", (void **) &gload_glNormal3f },
   { "glNormal3fv", (void **) &gload_glNormal3fv },
   { "glNormal3i", (void **) &gload_glNormal3i },
   { "glNormal3iv", (void **) &gload_glNormal3iv },
   { "glNormal3s", (void **) &gload_glNormal3s },
   { "glNormal3sv", (void **) &gload_glNormal3sv },
   { "glRasterPos2d", (void **) &gload_glRasterPos2d },
   { "glRasterPos2dv", (void **) &gload_glRasterPos2dv },
   { "glRasterPos2f", (void **) &gload_glRasterPos2f },
   { "glRasterPos2fv", (void **) &gload_glRasterPos2fv },
   { "glRasterPos2i", (void **) &gload_glRasterPos2i },
   { "glRasterPos2iv", (void **) &gload_glRasterPos2iv },
   { "glRasterPos2s", (void **) &gload_glRasterPos2s },
   { "glRasterPos2sv", (void **) &gload_glRasterPos2sv },
   { "glRasterPos3d", (void **) &gload_glRasterPos3d },
   { "glRasterPos3dv", (void **) &gload_glRasterPos3dv },
   { "glRasterPos3f", (void **) &gload_glRasterPos3f },
   { "glRasterPos3fv", (void **) &gload_glRasterPos3fv },
   { "glRasterPos3i", (void **) &gload_glRasterPos3i },
   { "glRasterPos3iv", (void **) &gload_glRasterPos3iv },
   { "glRasterPos3s", (void **) &gload_glRasterPos3s },
   { "glRasterPos3sv", (void **) &gload_glRasterPos3sv },
   { "glRasterPos4d", (void **) &gload_glRasterPos4d },
   { "glRasterPos4dv", (void **) &gload_glRasterPos4dv },
   { "glRasterPos4f", (void **) &gload_glRasterPos4f },
   { "glRasterPos4fv", (void **) &gload_glRasterPos4fv },
   { "glRasterPos4i", (void **) &gload_glRasterPos4i },
   { "glRasterPos4iv", (void **) &gload_glRasterPos4iv },
   { "glRasterPos4s", (void **) &gload_glRasterPos4s },
   { "glRasterPos4sv", (void **) &gload_glRasterPos4sv },
   { "glRectd", (void **) &gload_glRectd },
   { "glRectdv", (void **) &gload_glRectdv },
   { "glRectf", (void **) &gload_glRectf },
   { "glRectfv", (void **) &gload_glRectfv },
   { "glRecti", (void **) &gload_glRecti },
   { "glRectiv", (void **) &gload_glRectiv },
   { "glRects", (void **) &gload_glRects },
   { "glRectsv", (void **) &gload_glRectsv },
   { "glTexCoord1d", (void **) &gload_glTexCoord1d },
   { "glTexCoord1dv", (void **) &gload_glTexCoord1dv },
   { "glTexCoord1f", (void **) &gload_glTexCoord1f },
   { "glTexCoord1fv", (void **) &gload_glTexCoord1fv },
   { "glTexCoord1i", (void **) &gload_glTexCoord1i },
   { "glTexCoord1iv", (void **) &gload_glTexCoord1iv },
   { "glTexCoord1s", (void **) &gload_glTexCoord1s },
   { "glTexCoord1sv", (void **) &gload_glTexCoord1sv },
   { "glTexCoord2d", (void **) &gload_glTexCoord2d },
   { "glTexCoord2dv", (void **) &gload_glTexCoord2dv },
   { "glTexCoord2f", (void **) &gload_glTexCoord2f },
   { "glTexCoord2fv", (void **) &gload_glTexCoord2fv },
   { "glTexCoord2i", (void **) &gload_glTexCoord2i },
   { "glTexCoord2iv", (void **) &gload_glTexCoord2iv },
   { "glTexCoord2s", (void **) &gload_glTexCoord2s },
   { "glTexCoord2sv", (void **) &gload_glTexCoord2sv },
   { "glTexCoord3d", (void **) &gload_glTexCoord3d },
   { "glTexCoord3dv", (void **) &gload_glTexCoord3dv },
   { "glTexCoord3f", (void **) &gload_glTexCoord3f },
   { "glTexCoord3fv", (void **) &gload_glTexCoord3fv },
   { "glTexCoord3i", (void **) &gload_glTexCoord3i },
   { "glTexCoord3iv", (void **) &gload_glTexCoord3iv },
   { "glTexCoord3s", (void **) &gload_glTexCoord3s },
   { "glTexCoord3sv", (void **) &gload_glTexCoord3sv },
   { "glTexCoord4d", (void **) &gload_glTexCoord4d },
   { "glTexCoord4dv", (void **) &gload_glTexCoord4dv },
   { "glTexCoord4f", (void **) &gload_glTexCoord4f },
   { "glTexCoord4fv", (void **) &gload_glTexCoord4fv },
   { "glTexCoord4i", (void **) &gload_glTexCoord4i },
   { "glTexCoord4iv", (void **) &gload_glTexCoord4iv },
   { "glTexCoord4s", (void **) &gload_glTexCoord4s },
   { "glTexCoord4sv", (void **) &gload_glTexCoord4sv },
   { "glVertex2d", (void **) &gload_glVertex2d },
   { "glVertex2dv", (void **) &gload_glVertex2dv },
   { "glVertex2f", (void **) &gload_glVertex2f },
   { "glVertex2fv", (void **) &gload_glVertex2fv },
   { "glVertex2i", (void **) &gload_glVertex2i },
   { "glVertex2iv", (void **) &gload_glVertex2iv },
   { "glVertex2s", (void **) &gload_glVertex2s },
   { "glVertex2sv", (void **) &gload_glVertex2sv },
   { "glVertex3d", (void **) &gload_glVertex3d },
   { "glVertex3dv", (void **) &gload_glVertex3dv },
   { "glVertex3f", (void **) &gload_glVertex3f },
   { "glVertex3fv", (void **) &gload_glVertex3fv },
   { "glVertex3i", (void **) &gload_glVertex3i },
   { "glVertex3iv", (void **) &gload_glVertex3iv },
   { "glVertex3s", (void **) &gload_glVertex3s },
   { "glVertex3sv", (void **) &gload_glVertex3sv },
   { "glVertex4d", (void **) &gload_glVertex4d },
   { "glVertex4dv", (void **) &gload_glVertex4dv },
   { "glVertex4f", (void **) &gload_glVertex4f },
   { "glVertex4fv", (void **) &gload_glVertex4fv },
   { "glVertex4i", (void **) &gload_glVertex4i },
   { "glVertex4iv", (void **) &gload_glVertex4iv },
   { "glVertex4s", (void **) &gload_glVertex4s },
   { "glVertex4sv", (void **) &gload_glVertex4sv },
   { "glClipPlane", (void **) &gload_glClipPlane },
   { "glColorMaterial", (void **) &gload_glColorMaterial },
   { "glFogf", (void **) &gload_glFogf },
   { "glFogfv", (void **) &gload_glFogfv },
   { "glFogi", (void **) &gload_glFogi },
   { "glFogiv", (void **) &gload_glFogiv },
   { "glLightf", (void **) &gload_glLightf },
   { "glLightfv", (void **) &gload_glLightfv },
   { "glLighti", (void **) &gload_glLighti },
   { "glLightiv", (void **) &gload_glLightiv },
   { "glLightModelf", (void **) &gload_glLightModelf },
   { "glLightModelfv", (void **) &gload_glLightModelfv },
   { "glLightModeli", (void **) &gload_glLightModeli },
   { "glLightModeliv", (void **) &gload_glLightModeliv },
   { "glLineStipple", (void **) &gload_glLineStipple },
   { "glMaterialf", (void **) &gload_glMaterialf },
   { "glMaterialfv", (void **) &gload_glMaterialfv },
   { "glMateriali", (void **) &gload_glMateriali },
   { "glMaterialiv", (void **) &gload_glMaterialiv },
   { "glPolygonStipple", (void **) &gload_glPolygonStipple },
   { "glShadeModel", (void **) &gload_glShadeModel },
   { "glTexEnvf", (void **) &gload_glTexEnvf },
   { "glTexEnvfv", (void **) &gload_glTexEnvfv },
   { "glTexEnvi", (void **) &gload_glTexEnvi },
   { "glTexEnviv", (void **) &gload_glTexEnviv },
   { "glTexGend", (void **) &gload_glTexGend },
   { "glTexGendv", (void **) &gload_glTexGendv },
   { "glTexGenf", (void **) &gload_glTexGenf },
   { "glTexGenfv", (void **) &gload_glTexGenfv },
   { "glTexGeni", (void **) &gload_glTexGeni },
   { "glTexGeniv", (void **) &gload_glTexGeniv },
   { "glFeedbackBuffer", (void **) &gload_glFeedbackBuffer },
   { "glSelectBuffer", (void **) &gload_glSelectBuffer },
   { "glRenderMode", (void **) &gload_glRenderMode },
   { "glInitNames", (void **) &gload_glInitNames },
   { "glLoadName", (void **) &gload_glLoadName },
   { "glPassThrough", (void **) &gload_glPassThrough },
   { "glPopName", (void **) &gload_glPopName },
   { "glPushName", (void **) &gload_glPushName },
   { "glClearAccum", (void **) &gload_glClearAccum },
   { "glClearIndex", (void **) &gload_glClearIndex },
   { "glIndexMask", (void **) &gload_glIndexMask },
   { "glAccum", (void **) &gload_glAccum },
   { "glPopAttrib", (void **) &gload_glPopAttrib },
   { "glPushAttrib", (void **) &gload_glPushAttrib },
   { "glMap1d", (void **) &gload_glMap1d },
   { "glMap1f", (void **) &gload_glMap1f },
   { "glMap2d", (void **) &gload_glMap2d },
   { "glMap2f", (void **) &gload_glMap2f },
   { "glMapGrid1d", (void **) &gload_glMapGrid1d },
   { "glMapGrid1f", (void **) &gload_glMapGrid1f },
   { "glMapGrid2d", (void **) &gload_glMapGrid2d },
   { "glMapGrid2f", (void **) &gload_glMapGrid2f },
   { "glEvalCoord1d", (void **) &gload_glEvalCoord1d },
   { "glEvalCoord1dv", (void **) &gload_glEvalCoord1dv },
   { "glEvalCoord1f", (void **) &gload_glEvalCoord1f },
   { "glEvalCoord1fv", (void **) &gload_glEvalCoord1fv },
   { "glEvalCoord2d", (void **) &gload_glEvalCoord2d },
   { "glEvalCoord2dv", (void **) &gload_glEvalCoord2dv },
   { "glEvalCoord2f", (void **) &gload_glEvalCoord2f },
   { "glEvalCoord2fv", (void **) &gload_glEvalCoord2fv },
   { "glEvalMesh1", (void **) &gload_glEvalMesh1 },
   { "glEvalPoint1", (void **) &gload_glEvalPoint1 },
   { "glEvalMesh2", (void **) &gload_glEvalMesh2 },
   { "glEvalPoint2", (void **) &gload_glEvalPoint2 },
   { "glAlphaFunc", (void **) &gload_glAlphaFunc },
   { "glPixelZoom", (void **) &gload_glPixelZoom },
   { "glPixelTransferf", (void **) &gload_glPixelTransferf },
   { "glPixelTransferi", (void **) &gload_glPixelTransferi },
   { "glPixelMapfv", (void **) &gload_glPixelMapfv },
   { "glPixelMapuiv", (void **) &gload_glPixelMapuiv },
   { "glPixelMapusv", (void **) &gload_glPixelMapusv },
   { "glCopyPixels", (void **) &gload_glCopyPixels },
   { "glDrawPixels", (void **) &gload_glDrawPixels },
   { "glGetClipPlane", (void **) &gload_glGetClipPlane },
   { "glGetLightfv", (void **) &gload_glGetLightfv },
   { "glGetLightiv", (void **) &gload_glGetLightiv },
   { "glGetMapdv", (void **) &gload_glGetMapdv },
   { "glGetMapfv", (void **) &gload_glGetMapfv },
   { "glGetMapiv", (void **) &gload_glGetMapiv },
   { "glGetMaterialfv", (void **) &gload_glGetMaterialfv },
   { "glGetMaterialiv", (void **) &gload_glGetMaterialiv },
   { "glGetPixelMapfv", (void **) &gload_glGetPixelMapfv },
   { "glGetPixelMapuiv", (void **) &gload_glGetPixelMapuiv },
   { "glGetPixelMapusv", (void **) &gload_glGetPixelMapusv },
   { "glGetPolygonStipple", (void **) &gload_glGetPolygonStipple },
   { "glGetTexEnvfv", (void **) &gload_glGetTexEnvfv },
   { "glGetTexEnviv", (void **) &gload_glGetTexEnviv },
   { "glGetTexGendv", (void **) &gload_glGetTexGendv },
   { "glGetTexGenfv", (void **) &gload_glGetTexGenfv },
   { "glGetTexGeniv", (void **) &gload_glGetTexGeniv },
   { "glIsList", (void **) &gload_glIsList },
   { "glFrustum", (void **) &gload_glFrustum },
   { "glLoadIdentity", (void **) &gload_glLoadIdentity },
   { "glLoadMatrixf", (void **) &gload_glLoadMatrixf },
   { "glLoadMatrixd", (void **) &gload_glLoadMatrixd },
   { "glMatrixMode", (void **) &gload_glMatrixMode },
   { "glMultMatrixf", (void **) &gload_glMultMatrixf },
   { "glMultMatrixd", (void **) &gload_glMultMatrixd },
   { "glOrtho", (void **) &gload_glOrtho },
   { "glPopMatrix", (void **) &gload_glPopMatrix },
   { "glPushMatrix", (void **) &gload_glPushMatrix },
   { "glRotated", (void **) &gload_glRotated },
   { "glRotatef", (void **) &gload_glRotatef },
   { "glScaled", (void **) &gload_glScaled },
   { "glScalef", (void **) &gload_glScalef },
   { "glTranslated", (void **) &gload_glTranslated },
   { "glTranslatef", (void **) &gload_glTranslatef },

#  endif /* GL_VERSION_1_0 */
#  if defined GL_VERSION_1_1

   { "glDrawArrays", (void **) &gload_glDrawArrays },
   { "glDrawElements", (void **) &gload_glDrawElements },
   { "glGetPointerv", (void **) &gload_glGetPointerv },
   { "glPolygonOffset", (void **) &gload_glPolygonOffset },
   { "glCopyTexImage1D", (void **) &gload_glCopyTexImage1D },
   { "glCopyTexImage2D", (void **) &gload_glCopyTexImage2D },
   { "glCopyTexSubImage1D", (void **) &gload_glCopyTexSubImage1D },
   { "glCopyTexSubImage2D", (void **) &gload_glCopyTexSubImage2D },
   { "glTexSubImage1D", (void **) &gload_glTexSubImage1D },
   { "glTexSubImage2D", (void **) &gload_glTexSubImage2D },
   { "glBindTexture", (void **) &gload_glBindTexture },
   { "glDeleteTextures", (void **) &gload_glDeleteTextures },
   { "glGenTextures", (void **) &gload_glGenTextures },
   { "glIsTexture", (void **) &gload_glIsTexture },
   { "glArrayElement", (void **) &gload_glArrayElement },
   { "glColorPointer", (void **) &gload_glColorPointer },
   { "glDisableClientState", (void **) &gload_glDisableClientState },
   { "glEdgeFlagPointer", (void **) &gload_glEdgeFlagPointer },
   { "glEnableClientState", (void **) &gload_glEnableClientState },
   { "glIndexPointer", (void **) &gload_glIndexPointer },
   { "glInterleavedArrays", (void **) &gload_glInterleavedArrays },
   { "glNormalPointer", (void **) &gload_glNormalPointer },
   { "glTexCoordPointer", (void **) &gload_glTexCoordPointer },
   { "glVertexPointer", (void **) &gload_glVertexPointer },
   { "glAreTexturesResident", (void **) &gload_glAreTexturesResident },
   { "glPrioritizeTextures", (void **) &gload_glPrioritizeTextures },
   { "glIndexub", (void **) &gload_glIndexub },
   { "glIndexubv", (void **) &gload_glIndexubv },
   { "glPopClientAttrib", (void **) &gload_glPopClientAttrib },
   { "glPushClientAttrib", (void **) &gload_glPushClientAttrib },

#  endif /* GL_VERSION_1_1 */
#  if defined GL_VERSION_1_2

   { "glDrawRangeElements", (void **) &gload_glDrawRangeElements },
   { "glTexImage3D", (void **) &gload_glTexImage3D },
   { "glTexSubImage3D", (void **) &gload_glTexSubImage3D },
   { "glCopyTexSubImage3D", (void **) &gload_glCopyTexSubImage3D },

#  endif /* GL_VERSION_1_2 */
#  if defined GL_VERSION_1_3

   { "glActiveTexture", (void **) &gload_glActiveTexture },
   { "glSampleCoverage", (void **) &gload_glSampleCoverage },
   { "glCompressedTexImage3D", (void **) &gload_glCompressedTexImage3D },
   { "glCompressedTexImage2D", (void **) &gload_glCompressedTexImage2D },
   { "glCompressedTexImage1D", (void **) &gload_glCompressedTexImage1D },
   { "glCompressedTexSubImage3D", (void **) &gload_glCompressedTexSubImage3D },
   { "glCompressedTexSubImage2D", (void **) &gload_glCompressedTexSubImage2D },
   { "glCompressedTexSubImage1D", (void **) &gload_glCompressedTexSubImage1D },
   { "glGetCompressedTexImage", (void **) &gload_glGetCompressedTexImage },
   { "glClientActiveTexture", (void **) &gload_glClientActiveTexture },
   { "glMultiTexCoord1d", (void **) &gload_glMultiTexCoord1d },
   { "glMultiTexCoord1dv", (void **) &gload_glMultiTexCoord1dv },
   { "glMultiTexCoord1f", (void **) &gload_glMultiTexCoord1f },
   { "glMultiTexCoord1fv", (void **) &gload_glMultiTexCoord1fv },
   { "glMultiTexCoord1i", (void **) &gload_glMultiTexCoord1i },
   { "glMultiTexCoord1iv", (void **) &gload_glMultiTexCoord1iv },
   { "glMultiTexCoord1s", (void **) &gload_glMultiTexCoord1s },
   { "glMultiTexCoord1sv", (void **) &gload_glMultiTexCoord1sv },
   { "glMultiTexCoord2d", (void **) &gload_glMultiTexCoord2d },
   { "glMultiTexCoord2dv", (void **) &gload_glMultiTexCoord2dv },
   { "glMultiTexCoord2f", (void **) &gload_glMultiTexCoord2f },
   { "glMultiTexCoord2fv", (void **) &gload_glMultiTexCoord2fv },
   { "glMultiTexCoord2i", (void **) &gload_glMultiTexCoord2i },
   { "glMultiTexCoord2iv", (void **) &gload_glMultiTexCoord2iv },
   { "glMultiTexCoord2s", (void **) &gload_glMultiTexCoord2s },
   { "glMultiTexCoord2sv", (void **) &gload_glMultiTexCoord2sv },
   { "glMultiTexCoord3d", (void **) &gload_glMultiTexCoord3d },
   { "glMultiTexCoord3dv", (void **) &gload_glMultiTexCoord3dv },
   { "glMultiTexCoord3f", (void **) &gload_glMultiTexCoord3f },
   { "glMultiTexCoord3fv", (void **) &gload_glMultiTexCoord3fv },
   { "glMultiTexCoord3i", (void **) &gload_glMultiTexCoord3i },
   { "glMultiTexCoord3iv", (void **) &gload_glMultiTexCoord3iv },
   { "glMultiTexCoord3s", (void **) &gload_glMultiTexCoord3s },
   { "glMultiTexCoord3sv", (void **) &gload_glMultiTexCoord3sv },
   { "glMultiTexCoord4d", (void **) &gload_glMultiTexCoord4d },
   { "glMultiTexCoord4dv", (void **) &gload_glMultiTexCoord4dv },
   { "glMultiTexCoord4f", (void **) &gload_glMultiTexCoord4f },
   { "glMultiTexCoord4fv", (void **) &gload_glMultiTexCoord4fv },
   { "glMultiTexCoord4i", (void **) &gload_glMultiTexCoord4i },
   { "glMultiTexCoord4iv", (void **) &gload_glMultiTexCoord4iv },
   { "glMultiTexCoord4s", (void **) &gload_glMultiTexCoord4s },
   { "glMultiTexCoord4sv", (void **) &gload_glMultiTexCoord4sv },
   { "glLoadTransposeMatrixf", (void **) &gload_glLoadTransposeMatrixf },
   { "glLoadTransposeMatrixd", (void **) &gload_glLoadTransposeMatrixd },
   { "glMultTransposeMatrixf", (void **) &gload_glMultTransposeMatrixf },
   { "glMultTransposeMatrixd", (void **) &gload_glMultTransposeMatrixd },

#  endif /* GL_VERSION_1_3 */
#  if defined GL_VERSION_1_4

   { "glBlendFuncSeparate", (void **) &gload_glBlendFuncSeparate },
   { "glMultiDrawArrays", (void **) &gload_glMultiDrawArrays },
   { "glMultiDrawElements", (void **) &gload_glMultiDrawElements },
   { "glPointParameterf", (void **) &gload_glPointParameterf },
   { "glPointParameterfv", (void **) &gload_glPointParameterfv },
   { "glPointParameteri", (void **) &gload_glPointParameteri },
   { "glPointParameteriv", (void **) &gload_glPointParameteriv },
   { "glFogCoordf", (void **) &gload_glFogCoordf },
   { "glFogCoordfv", (void **) &gload_glFogCoordfv },
   { "glFogCoordd", (void **) &gload_glFogCoordd },
   { "glFogCoorddv", (void **) &gload_glFogCoorddv },
   { "glFogCoordPointer", (void **) &gload_glFogCoordPointer },
   { "glSecondaryColor3b", (void **) &gload_glSecondaryColor3b },
   { "glSecondaryColor3bv", (void **) &gload_glSecondaryColor3bv },
   { "glSecondaryColor3d", (void **) &gload_glSecondaryColor3d },
   { "glSecondaryColor3dv", (void **) &gload_glSecondaryColor3dv },
   { "glSecondaryColor3f", (void **) &gload_glSecondaryColor3f },
   { "glSecondaryColor3fv", (void **) &gload_glSecondaryColor3fv },
   { "glSecondaryColor3i", (void **) &gload_glSecondaryColor3i },
   { "glSecondaryColor3iv", (void **) &gload_glSecondaryColor3iv },
   { "glSecondaryColor3s", (void **) &gload_glSecondaryColor3s },
   { "glSecondaryColor3sv", (void **) &gload_glSecondaryColor3sv },
   { "glSecondaryColor3ub", (void **) &gload_glSecondaryColor3ub },
   { "glSecondaryColor3ubv", (void **) &gload_glSecondaryColor3ubv },
   { "glSecondaryColor3ui", (void **) &gload_glSecondaryColor3ui },
   { "glSecondaryColor3uiv", (void **) &gload_glSecondaryColor3uiv },
   { "glSecondaryColor3us", (void **) &gload_glSecondaryColor3us },
   { "glSecondaryColor3usv", (void **) &gload_glSecondaryColor3usv },
   { "glSecondaryColorPointer", (void **) &gload_glSecondaryColorPointer },
   { "glWindowPos2d", (void **) &gload_glWindowPos2d },
   { "glWindowPos2dv", (void **) &gload_glWindowPos2dv },
   { "glWindowPos2f", (void **) &gload_glWindowPos2f },
   { "glWindowPos2fv", (void **) &gload_glWindowPos2fv },
   { "glWindowPos2i", (void **) &gload_glWindowPos2i },
   { "glWindowPos2iv", (void **) &gload_glWindowPos2iv },
   { "glWindowPos2s", (void **) &gload_glWindowPos2s },
   { "glWindowPos2sv", (void **) &gload_glWindowPos2sv },
   { "glWindowPos3d", (void **) &gload_glWindowPos3d },
   { "glWindowPos3dv", (void **) &gload_glWindowPos3dv },
   { "glWindowPos3f", (void **) &gload_glWindowPos3f },
   { "glWindowPos3fv", (void **) &gload_glWindowPos3fv },
   { "glWindowPos3i", (void **) &gload_glWindowPos3i },
   { "glWindowPos3iv", (void **) &gload_glWindowPos3iv },
   { "glWindowPos3s", (void **) &gload_glWindowPos3s },
   { "glWindowPos3sv", (void **) &gload_glWindowPos3sv },
   { "glBlendColor", (void **) &gload_glBlendColor },
   { "glBlendEquation", (void **) &gload_glBlendEquation },

#  endif /* GL_VERSION_1_4 */
#  if defined GL_VERSION_1_5

   { "glGenQueries", (void **) &gload_glGenQueries },
   { "glDeleteQueries", (void **) &gload_glDeleteQueries },
   { "glIsQuery", (void **) &gload_glIsQuery },
   { "glBeginQuery", (void **) &gload_glBeginQuery },
   { "glEndQuery", (void **) &gload_glEndQuery },
   { "glGetQueryiv", (void **) &gload_glGetQueryiv },
   { "glGetQueryObjectiv", (void **) &gload_glGetQueryObjectiv },
   { "glGetQueryObjectuiv", (void **) &gload_glGetQueryObjectuiv },
   { "glBindBuffer", (void **) &gload_glBindBuffer },
   { "glDeleteBuffers", (void **) &gload_glDeleteBuffers },
   { "glGenBuffers", (void **) &gload_glGenBuffers },
   { "glIsBuffer", (void **) &gload_glIsBuffer },
   { "glBufferData", (void **) &gload_glBufferData },
   { "glBufferSubData", (void **) &gload_glBufferSubData },
   { "glGetBufferSubData", (void **) &gload_glGetBufferSubData },
   { "glMapBuffer", (void **) &gload_glMapBuffer },
   { "glUnmapBuffer", (void **) &gload_glUnmapBuffer },
   { "glGetBufferParameteriv", (void **) &gload_glGetBufferParameteriv },
   { "glGetBufferPointerv", (void **) &gload_glGetBufferPointerv },

#  endif /* GL_VERSION_1_5 */
#  if defined GL_VERSION_2_0

   { "glBlendEquationSeparate", (void **) &gload_glBlendEquationSeparate },
   { "glDrawBuffers", (void **) &gload_glDrawBuffers },
   { "glStencilOpSeparate", (void **) &gload_glStencilOpSeparate },
   { "glStencilFuncSeparate", (void **) &gload_glStencilFuncSeparate },
   { "glStencilMaskSeparate", (void **) &gload_glStencilMaskSeparate },
   { "glAttachShader", (void **) &gload_glAttachShader },
   { "glBindAttribLocation", (void **) &gload_glBindAttribLocation },
   { "glCompileShader", (void **) &gload_glCompileShader },
   { "glCreateProgram", (void **) &gload_glCreateProgram },
   { "glCreateShader", (void **) &gload_glCreateShader },
   { "glDeleteProgram", (void **) &gload_glDeleteProgram },
   { "glDeleteShader", (void **) &gload_glDeleteShader },
   { "glDetachShader", (void **) &gload_glDetachShader },
   { "glDisableVertexAttribArray", (void **) &gload_glDisableVertexAttribArray },
   { "glEnableVertexAttribArray", (void **) &gload_glEnableVertexAttribArray },
   { "glGetActiveAttrib", (void **) &gload_glGetActiveAttrib },
   { "glGetActiveUniform", (void **) &gload_glGetActiveUniform },
   { "glGetAttachedShaders", (void **) &gload_glGetAttachedShaders },
   { "glGetAttribLocation", (void **) &gload_glGetAttribLocation },
   { "glGetProgramiv", (void **) &gload_glGetProgramiv },
   { "glGetProgramInfoLog", (void **) &gload_glGetProgramInfoLog },
   { "glGetShaderiv", (void **) &gload_glGetShaderiv },
   { "glGetShaderInfoLog", (void **) &gload_glGetShaderInfoLog },
   { "glGetShaderSource", (void **) &gload_glGetShaderSource },
   { "glGetUniformLocation", (void **) &gload_glGetUniformLocation },
   { "glGetUniformfv", (void **) &gload_glGetUniformfv },
   { "glGetUniformiv", (void **) &gload_glGetUniformiv },
   { "glGetVertexAttribdv", (void **) &gload_glGetVertexAttribdv },
   { "glGetVertexAttribfv", (void **) &gload_glGetVertexAttribfv },
   { "glGetVertexAttribiv", (void **) &gload_glGetVertexAttribiv },
   { "glGetVertexAttribPointerv", (void **) &gload_glGetVertexAttribPointerv },
   { "glIsProgram", (void **) &gload_glIsProgram },
   { "glIsShader", (void **) &gload_glIsShader },
   { "glLinkProgram", (void **) &gload_glLinkProgram },
   { "glShaderSource", (void **) &gload_glShaderSource },
   { "glUseProgram", (void **) &gload_glUseProgram },
   { "glUniform1f", (void **) &gload_glUniform1f },
   { "glUniform2f", (void **) &gload_glUniform2f },
   { "glUniform3f", (void **) &gload_glUniform3f },
   { "glUniform4f", (void **) &gload_glUniform4f },
   { "glUniform1i", (void **) &gload_glUniform1i },
   { "glUniform2i", (void **) &gload_glUniform2i },
   { "glUniform3i", (void **) &gload_glUniform3i },
   { "glUniform4i", (void **) &gload_glUniform4i },
   { "glUniform1fv", (void **) &gload_glUniform1fv },
   { "glUniform2fv", (void **) &gload_glUniform2fv },
   { "glUniform3fv", (void **) &gload_glUniform3fv },
   { "glUniform4fv", (void **) &gload_glUniform4fv },
   { "glUniform1iv", (void **) &gload_glUniform1iv },
   { "glUniform2iv", (void **) &gload_glUniform2iv },
   { "glUniform3iv", (void **) &gload_glUniform3iv },
   { "glUniform4iv", (void **) &gload_glUniform4iv },
   { "glUniformMatrix2fv", (void **) &gload_glUniformMatrix2fv },
   { "glUniformMatrix3fv", (void **) &gload_glUniformMatrix3fv },
   { "glUniformMatrix4fv", (void **) &gload_glUniformMatrix4fv },
   { "glValidateProgram", (void **) &gload_glValidateProgram },
   { "glVertexAttrib1d", (void **) &gload_glVertexAttrib1d },
   { "glVertexAttrib1dv", (void **) &gload_glVertexAttrib1dv },
   { "glVertexAttrib1f", (void **) &gload_glVertexAttrib1f },
   { "glVertexAttrib1fv", (void **) &gload_glVertexAttrib1fv },
   { "glVertexAttrib1s", (void **) &gload_glVertexAttrib1s },
   { "glVertexAttrib1sv", (void **) &gload_glVertexAttrib1sv },
   { "glVertexAttrib2d", (void **) &gload_glVertexAttrib2d },
   { "glVertexAttrib2dv", (void **) &gload_glVertexAttrib2dv },
   { "glVertexAttrib2f", (void **) &gload_glVertexAttrib2f },
   { "glVertexAttrib2fv", (void **) &gload_glVertexAttrib2fv },
   { "glVertexAttrib2s", (void **) &gload_glVertexAttrib2s },
   { "glVertexAttrib2sv", (void **) &gload_glVertexAttrib2sv },
   { "glVertexAttrib3d", (void **) &gload_glVertexAttrib3d },
   { "glVertexAttrib3dv", (void **) &gload_glVertexAttrib3dv },
   { "glVertexAttrib3f", (void **) &gload_glVertexAttrib3f },
   { "glVertexAttrib3fv", (void **) &gload_glVertexAttrib3fv },
   { "glVertexAttrib3s", (void **) &gload_glVertexAttrib3s },
   { "glVertexAttrib3sv", (void **) &gload_glVertexAttrib3sv },
   { "glVertexAttrib4Nbv", (void **) &gload_glVertexAttrib4Nbv },
   { "glVertexAttrib4Niv", (void **) &gload_glVertexAttrib4Niv },
   { "glVertexAttrib4Nsv", (void **) &gload_glVertexAttrib4Nsv },
   { "glVertexAttrib4Nub", (void **) &gload_glVertexAttrib4Nub },
   { "glVertexAttrib4Nubv", (void **) &gload_glVertexAttrib4Nubv },
   { "glVertexAttrib4Nuiv", (void **) &gload_glVertexAttrib4Nuiv },
   { "glVertexAttrib4Nusv", (void **) &gload_glVertexAttrib4Nusv },
   { "glVertexAttrib4bv", (void **) &gload_glVertexAttrib4bv },
   { "glVertexAttrib4d", (void **) &gload_glVertexAttrib4d },
   { "glVertexAttrib4dv", (void **) &gload_glVertexAttrib4dv },
   { "glVertexAttrib4f", (void **) &gload_glVertexAttrib4f },
   { "glVertexAttrib4fv", (void **) &gload_glVertexAttrib4fv },
   { "glVertexAttrib4iv", (void **) &gload_glVertexAttrib4iv },
   { "glVertexAttrib4s", (void **) &gload_glVertexAttrib4s },
   { "glVertexAttrib4sv", (void **) &gload_glVertexAttrib4sv },
   { "glVertexAttrib4ubv", (void **) &gload_glVertexAttrib4ubv },
   { "glVertexAttrib4uiv", (void **) &gload_glVertexAttrib4uiv },
   { "glVertexAttrib4usv", (void **) &gload_glVertexAttrib4usv },
   { "glVertexAttribPointer", (void **) &gload_glVertexAttribPointer },

#  endif /* GL_VERSION_2_0 */
#  if defined GL_VERSION_2_1

   { "glUniformMatrix2x3fv", (void **) &gload_glUniformMatrix2x3fv },
   { "glUniformMatrix3x2fv", (void **) &gload_glUniformMatrix3x2fv },
   { "glUniformMatrix2x4fv", (void **) &gload_glUniformMatrix2x4fv },
   { "glUniformMatrix4x2fv", (void **) &gload_glUniformMatrix4x2fv },
   { "glUniformMatrix3x4fv", (void **) &gload_glUniformMatrix3x4fv },
   { "glUniformMatrix4x3fv", (void **) &gload_glUniformMatrix4x3fv },

#  endif /* GL_VERSION_2_1 */
#  if defined GL_VERSION_3_0

   { "glColorMaski", (void **) &gload_glColorMaski },
   { "glGetBooleani_v", (void **) &gload_glGetBooleani_v },
   { "glGetIntegeri_v", (void **) &gload_glGetIntegeri_v },
   { "glEnablei", (void **) &gload_glEnablei },
   { "glDisablei", (void **) &gload_glDisablei },
   { "glIsEnabledi", (void **) &gload_glIsEnabledi },
   { "glBeginTransformFeedback", (void **) &gload_glBeginTransformFeedback },
   { "glEndTransformFeedback", (void **) &gload_glEndTransformFeedback },
   { "glBindBufferRange", (void **) &gload_glBindBufferRange },
   { "glBindBufferBase", (void **) &gload_glBindBufferBase },
   { "glTransformFeedbackVaryings", (void **) &gload_glTransformFeedbackVaryings },
   { "glGetTransformFeedbackVarying", (void **) &gload_glGetTransformFeedbackVarying },
   { "glClampColor", (void **) &gload_glClampColor },
   { "glBeginConditionalRender", (void **) &gload_glBeginConditionalRender },
   { "glEndConditionalRender", (void **) &gload_glEndConditionalRender },
   { "glVertexAttribIPointer", (void **) &gload_glVertexAttribIPointer },
   { "glGetVertexAttribIiv", (void **) &gload_glGetVertexAttribIiv },
   { "glGetVertexAttribIuiv", (void **) &gload_glGetVertexAttribIuiv },
   { "glVertexAttribI1i", (void **) &gload_glVertexAttribI1i },
   { "glVertexAttribI2i", (void **) &gload_glVertexAttribI2i },
   { "glVertexAttribI3i", (void **) &gload_glVertexAttribI3i },
   { "glVertexAttribI4i", (void **) &gload_glVertexAttribI4i },
   { "glVertexAttribI1ui", (void **) &gload_glVertexAttribI1ui },
   { "glVertexAttribI2ui", (void **) &gload_glVertexAttribI2ui },
   { "glVertexAttribI3ui", (void **) &gload_glVertexAttribI3ui },
   { "glVertexAttribI4ui", (void **) &gload_glVertexAttribI4ui },
   { "glVertexAttribI1iv", (void **) &gload_glVertexAttribI1iv },
   { "glVertexAttribI2iv", (void **) &gload_glVertexAttribI2iv },
   { "glVertexAttribI3iv", (void **) &gload_glVertexAttribI3iv },
   { "glVertexAttribI4iv", (void **) &gload_glVertexAttribI4iv },
   { "glVertexAttribI1uiv", (void **) &gload_glVertexAttribI1uiv },
   { "glVertexAttribI2uiv", (void **) &gload_glVertexAttribI2uiv },
   { "glVertexAttribI3uiv", (void **) &gload_glVertexAttribI3uiv },
   { "glVertexAttribI4uiv", (void **) &gload_glVertexAttribI4uiv },
   { "glVertexAttribI4bv", (void **) &gload_glVertexAttribI4bv },
   { "glVertexAttribI4sv", (void **) &gload_glVertexAttribI4sv },
   { "glVertexAttribI4ubv", (void **) &gload_glVertexAttribI4ubv },
   { "glVertexAttribI4usv", (void **) &gload_glVertexAttribI4usv },
   { "glGetUniformuiv", (void **) &gload_glGetUniformuiv },
   { "glBindFragDataLocation", (void **) &gload_glBindFragDataLocation },
   { "glGetFragDataLocation", (void **) &gload_glGetFragDataLocation },
   { "glUniform1ui", (void **) &gload_glUniform1ui },
   { "glUniform2ui", (void **) &gload_glUniform2ui },
   { "glUniform3ui", (void **) &gload_glUniform3ui },
   { "glUniform4ui", (void **) &gload_glUniform4ui },
   { "glUniform1uiv", (void **) &gload_glUniform1uiv },
   { "glUniform2uiv", (void **) &gload_glUniform2uiv },
   { "glUniform3uiv", (void **) &gload_glUniform3uiv },
   { "glUniform4uiv", (void **) &gload_glUniform4uiv },
   { "glTexParameterIiv", (void **) &gload_glTexParameterIiv },
   { "glTexParameterIuiv", (void **) &gload_glTexParameterIuiv },
   { "glGetTexParameterIiv", (void **) &gload_glGetTexParameterIiv },
   { "glGetTexParameterIuiv", (void **) &gload_glGetTexParameterIuiv },
   { "glClearBufferiv", (void **) &gload_glClearBufferiv },
   { "glClearBufferuiv", (void **) &gload_glClearBufferuiv },
   { "glClearBufferfv", (void **) &gload_glClearBufferfv },
   { "glClearBufferfi", (void **) &gload_glClearBufferfi },
   { "glGetStringi", (void **) &gload_glGetStringi },
   { "glIsRenderbuffer", (void **) &gload_glIsRenderbuffer },
   { "glBindRenderbuffer", (void **) &gload_glBindRenderbuffer },
   { "glDeleteRenderbuffers", (void **) &gload_glDeleteRenderbuffers },
   { "glGenRenderbuffers", (void **) &gload_glGenRenderbuffers },
   { "glRenderbufferStorage", (void **) &gload_glRenderbufferStorage },
   { "glGetRenderbufferParameteriv", (void **) &gload_glGetRenderbufferParameteriv },
   { "glIsFramebuffer", (void **) &gload_glIsFramebuffer },
   { "glBindFramebuffer", (void **) &gload_glBindFramebuffer },
   { "glDeleteFramebuffers", (void **) &gload_glDeleteFramebuffers },
   { "glGenFramebuffers", (void **) &gload_glGenFramebuffers },
   { "glCheckFramebufferStatus", (void **) &gload_glCheckFramebufferStatus },
   { "glFramebufferTexture1D", (void **) &gload_glFramebufferTexture1D },
   { "glFramebufferTexture2D", (void **) &gload_glFramebufferTexture2D },
   { "glFramebufferTexture3D", (void **) &gload_glFramebufferTexture3D },
   { "glFramebufferRenderbuffer", (void **) &gload_glFramebufferRenderbuffer },
   { "glGetFramebufferAttachmentParameteriv", (void **) &gload_glGetFramebufferAttachmentParameteriv },
   { "glGenerateMipmap", (void **) &gload_glGenerateMipmap },
   { "glBlitFramebuffer", (void **) &gload_glBlitFramebuffer },
   { "glRenderbufferStorageMultisample", (void **) &gload_glRenderbufferStorageMultisample },
   { "glFramebufferTextureLayer", (void **) &gload_glFramebufferTextureLayer },
   { "glMapBufferRange", (void **) &gload_glMapBufferRange },
   { "glFlushMappedBufferRange", (void **) &gload_glFlushMappedBufferRange },
   { "glBindVertexArray", (void **) &gload_glBindVertexArray },
   { "glDeleteVertexArrays", (void **) &gload_glDeleteVertexArrays },
   { "glGenVertexArrays", (void **) &gload_glGenVertexArrays },
   { "glIsVertexArray", (void **) &gload_glIsVertexArray },

#  endif /* GL_VERSION_3_0 */
#  if defined GL_VERSION_3_1

   { "glDrawArraysInstanced", (void **) &gload_glDrawArraysInstanced },
   { "glDrawElementsInstanced", (void **) &gload_glDrawElementsInstanced },
   { "glTexBuffer", (void **) &gload_glTexBuffer },
   { "glPrimitiveRestartIndex", (void **) &gload_glPrimitiveRestartIndex },
   { "glCopyBufferSubData", (void **) &gload_glCopyBufferSubData },
   { "glGetUniformIndices", (void **) &gload_glGetUniformIndices },
   { "glGetActiveUniformsiv", (void **) &gload_glGetActiveUniformsiv },
   { "glGetActiveUniformName", (void **) &gload_glGetActiveUniformName },
   { "glGetUniformBlockIndex", (void **) &gload_glGetUniformBlockIndex },
   { "glGetActiveUniformBlockiv", (void **) &gload_glGetActiveUniformBlockiv },
   { "glGetActiveUniformBlockName", (void **) &gload_glGetActiveUniformBlockName },
   { "glUniformBlockBinding", (void **) &gload_glUniformBlockBinding },
   { "glBindBufferRange", (void **) &gload_glBindBufferRange },
   { "glBindBufferBase", (void **) &gload_glBindBufferBase },
   { "glGetIntegeri_v", (void **) &gload_glGetIntegeri_v },

#  endif /* GL_VERSION_3_1 */
#  if defined GL_VERSION_3_2

   { "glDrawElementsBaseVertex", (void **) &gload_glDrawElementsBaseVertex },
   { "glDrawRangeElementsBaseVertex", (void **) &gload_glDrawRangeElementsBaseVertex },
   { "glDrawElementsInstancedBaseVertex", (void **) &gload_glDrawElementsInstancedBaseVertex },
   { "glMultiDrawElementsBaseVertex", (void **) &gload_glMultiDrawElementsBaseVertex },
   { "glProvokingVertex", (void **) &gload_glProvokingVertex },
   { "glFenceSync", (void **) &gload_glFenceSync },
   { "glIsSync", (void **) &gload_glIsSync },
   { "glDeleteSync", (void **) &gload_glDeleteSync },
   { "glClientWaitSync", (void **) &gload_glClientWaitSync },
   { "glWaitSync", (void **) &gload_glWaitSync },
   { "glGetInteger64v", (void **) &gload_glGetInteger64v },
   { "glGetSynciv", (void **) &gload_glGetSynciv },
   { "glGetInteger64i_v", (void **) &gload_glGetInteger64i_v },
   { "glGetBufferParameteri64v", (void **) &gload_glGetBufferParameteri64v },
   { "glFramebufferTexture", (void **) &gload_glFramebufferTexture },
   { "glTexImage2DMultisample", (void **) &gload_glTexImage2DMultisample },
   { "glTexImage3DMultisample", (void **) &gload_glTexImage3DMultisample },
   { "glGetMultisamplefv", (void **) &gload_glGetMultisamplefv },
   { "glSampleMaski", (void **) &gload_glSampleMaski },

#  endif /* GL_VERSION_3_2 */
#  if defined GL_VERSION_3_3

   { "glBindFragDataLocationIndexed", (void **) &gload_glBindFragDataLocationIndexed },
   { "glGetFragDataIndex", (void **) &gload_glGetFragDataIndex },
   { "glGenSamplers", (void **) &gload_glGenSamplers },
   { "glDeleteSamplers", (void **) &gload_glDeleteSamplers },
   { "glIsSampler", (void **) &gload_glIsSampler },
   { "glBindSampler", (void **) &gload_glBindSampler },
   { "glSamplerParameteri", (void **) &gload_glSamplerParameteri },
   { "glSamplerParameteriv", (void **) &gload_glSamplerParameteriv },
   { "glSamplerParameterf", (void **) &gload_glSamplerParameterf },
   { "glSamplerParameterfv", (void **) &gload_glSamplerParameterfv },
   { "glSamplerParameterIiv", (void **) &gload_glSamplerParameterIiv },
   { "glSamplerParameterIuiv", (void **) &gload_glSamplerParameterIuiv },
   { "glGetSamplerParameteriv", (void **) &gload_glGetSamplerParameteriv },
   { "glGetSamplerParameterIiv", (void **) &gload_glGetSamplerParameterIiv },
   { "glGetSamplerParameterfv", (void **) &gload_glGetSamplerParameterfv },
   { "glGetSamplerParameterIuiv", (void **) &gload_glGetSamplerParameterIuiv },
   { "glQueryCounter", (void **) &gload_glQueryCounter },
   { "glGetQueryObjecti64v", (void **) &gload_glGetQueryObjecti64v },
   { "glGetQueryObjectui64v", (void **) &gload_glGetQueryObjectui64v },
   { "glVertexAttribDivisor", (void **) &gload_glVertexAttribDivisor },
   { "glVertexAttribP1ui", (void **) &gload_glVertexAttribP1ui },
   { "glVertexAttribP1uiv", (void **) &gload_glVertexAttribP1uiv },
   { "glVertexAttribP2ui", (void **) &gload_glVertexAttribP2ui },
   { "glVertexAttribP2uiv", (void **) &gload_glVertexAttribP2uiv },
   { "glVertexAttribP3ui", (void **) &gload_glVertexAttribP3ui },
   { "glVertexAttribP3uiv", (void **) &gload_glVertexAttribP3uiv },
   { "glVertexAttribP4ui", (void **) &gload_glVertexAttribP4ui },
   { "glVertexAttribP4uiv", (void **) &gload_glVertexAttribP4uiv },
   { "glVertexP2ui", (void **) &gload_glVertexP2ui },
   { "glVertexP2uiv", (void **) &gload_glVertexP2uiv },
   { "glVertexP3ui", (void **) &gload_glVertexP3ui },
   { "glVertexP3uiv", (void **) &gload_glVertexP3uiv },
   { "glVertexP4ui", (void **) &gload_glVertexP4ui },
   { "glVertexP4uiv", (void **) &gload_glVertexP4uiv },
   { "glTexCoordP1ui", (void **) &gload_glTexCoordP1ui },
   { "glTexCoordP1uiv", (void **) &gload_glTexCoordP1uiv },
   { "glTexCoordP2ui", (void **) &gload_glTexCoordP2ui },
   { "glTexCoordP2uiv", (void **) &gload_glTexCoordP2uiv },
   { "glTexCoordP3ui", (void **) &gload_glTexCoordP3ui },
   { "glTexCoordP3uiv", (void **) &gload_glTexCoordP3uiv },
   { "glTexCoordP4ui", (void **) &gload_glTexCoordP4ui },
   { "glTexCoordP4uiv", (void **) &gload_glTexCoordP4uiv },
   { "glMultiTexCoordP1ui", (void **) &gload_glMultiTexCoordP1ui },
   { "glMultiTexCoordP1uiv", (void **) &gload_glMultiTexCoordP1uiv },
   { "glMultiTexCoordP2ui", (void **) &gload_glMultiTexCoordP2ui },
   { "glMultiTexCoordP2uiv", (void **) &gload_glMultiTexCoordP2uiv },
   { "glMultiTexCoordP3ui", (void **) &gload_glMultiTexCoordP3ui },
   { "glMultiTexCoordP3uiv", (void **) &gload_glMultiTexCoordP3uiv },
   { "glMultiTexCoordP4ui", (void **) &gload_glMultiTexCoordP4ui },
   { "glMultiTexCoordP4uiv", (void **) &gload_glMultiTexCoordP4uiv },
   { "glNormalP3ui", (void **) &gload_glNormalP3ui },
   { "glNormalP3uiv", (void **) &gload_glNormalP3uiv },
   { "glColorP3ui", (void **) &gload_glColorP3ui },
   { "glColorP3uiv", (void **) &gload_glColorP3uiv },
   { "glColorP4ui", (void **) &gload_glColorP4ui },
   { "glColorP4uiv", (void **) &gload_glColorP4uiv },
   { "glSecondaryColorP3ui", (void **) &gload_glSecondaryColorP3ui },
   { "glSecondaryColorP3uiv", (void **) &gload_glSecondaryColorP3uiv },

#  endif /* GL_VERSION_3_3 */
#  if defined GL_VERSION_4_0

   { "glMinSampleShading", (void **) &gload_glMinSampleShading },
   { "glBlendEquationi", (void **) &gload_glBlendEquationi },
   { "glBlendEquationSeparatei", (void **) &gload_glBlendEquationSeparatei },
   { "glBlendFunci", (void **) &gload_glBlendFunci },
   { "glBlendFuncSeparatei", (void **) &gload_glBlendFuncSeparatei },
   { "glDrawArraysIndirect", (void **) &gload_glDrawArraysIndirect },
   { "glDrawElementsIndirect", (void **) &gload_glDrawElementsIndirect },
   { "glUniform1d", (void **) &gload_glUniform1d },
   { "glUniform2d", (void **) &gload_glUniform2d },
   { "glUniform3d", (void **) &gload_glUniform3d },
   { "glUniform4d", (void **) &gload_glUniform4d },
   { "glUniform1dv", (void **) &gload_glUniform1dv },
   { "glUniform2dv", (void **) &gload_glUniform2dv },
   { "glUniform3dv", (void **) &gload_glUniform3dv },
   { "glUniform4dv", (void **) &gload_glUniform4dv },
   { "glUniformMatrix2dv", (void **) &gload_glUniformMatrix2dv },
   { "glUniformMatrix3dv", (void **) &gload_glUniformMatrix3dv },
   { "glUniformMatrix4dv", (void **) &gload_glUniformMatrix4dv },
   { "glUniformMatrix2x3dv", (void **) &gload_glUniformMatrix2x3dv },
   { "glUniformMatrix2x4dv", (void **) &gload_glUniformMatrix2x4dv },
   { "glUniformMatrix3x2dv", (void **) &gload_glUniformMatrix3x2dv },
   { "glUniformMatrix3x4dv", (void **) &gload_glUniformMatrix3x4dv },
   { "glUniformMatrix4x2dv", (void **) &gload_glUniformMatrix4x2dv },
   { "glUniformMatrix4x3dv", (void **) &gload_glUniformMatrix4x3dv },
   { "glGetUniformdv", (void **) &gload_glGetUniformdv },
   { "glGetSubroutineUniformLocation", (void **) &gload_glGetSubroutineUniformLocation },
   { "glGetSubroutineIndex", (void **) &gload_glGetSubroutineIndex },
   { "glGetActiveSubroutineUniformiv", (void **) &gload_glGetActiveSubroutineUniformiv },
   { "glGetActiveSubroutineUniformName", (void **) &gload_glGetActiveSubroutineUniformName },
   { "glGetActiveSubroutineName", (void **) &gload_glGetActiveSubroutineName },
   { "glUniformSubroutinesuiv", (void **) &gload_glUniformSubroutinesuiv },
   { "glGetUniformSubroutineuiv", (void **) &gload_glGetUniformSubroutineuiv },
   { "glGetProgramStageiv", (void **) &gload_glGetProgramStageiv },
   { "glPatchParameteri", (void **) &gload_glPatchParameteri },
   { "glPatchParameterfv", (void **) &gload_glPatchParameterfv },
   { "glBindTransformFeedback", (void **) &gload_glBindTransformFeedback },
   { "glDeleteTransformFeedbacks", (void **) &gload_glDeleteTransformFeedbacks },
   { "glGenTransformFeedbacks", (void **) &gload_glGenTransformFeedbacks },
   { "glIsTransformFeedback", (void **) &gload_glIsTransformFeedback },
   { "glPauseTransformFeedback", (void **) &gload_glPauseTransformFeedback },
   { "glResumeTransformFeedback", (void **) &gload_glResumeTransformFeedback },
   { "glDrawTransformFeedback", (void **) &gload_glDrawTransformFeedback },
   { "glDrawTransformFeedbackStream", (void **) &gload_glDrawTransformFeedbackStream },
   { "glBeginQueryIndexed", (void **) &gload_glBeginQueryIndexed },
   { "glEndQueryIndexed", (void **) &gload_glEndQueryIndexed },
   { "glGetQueryIndexediv", (void **) &gload_glGetQueryIndexediv },

#  endif /* GL_VERSION_4_0 */
#  if defined GL_VERSION_4_1

   { "glReleaseShaderCompiler", (void **) &gload_glReleaseShaderCompiler },
   { "glShaderBinary", (void **) &gload_glShaderBinary },
   { "glGetShaderPrecisionFormat", (void **) &gload_glGetShaderPrecisionFormat },
   { "glDepthRangef", (void **) &gload_glDepthRangef },
   { "glClearDepthf", (void **) &gload_glClearDepthf },
   { "glGetProgramBinary", (void **) &gload_glGetProgramBinary },
   { "glProgramBinary", (void **) &gload_glProgramBinary },
   { "glProgramParameteri", (void **) &gload_glProgramParameteri },
   { "glUseProgramStages", (void **) &gload_glUseProgramStages },
   { "glActiveShaderProgram", (void **) &gload_glActiveShaderProgram },
   { "glCreateShaderProgramv", (void **) &gload_glCreateShaderProgramv },
   { "glBindProgramPipeline", (void **) &gload_glBindProgramPipeline },
   { "glDeleteProgramPipelines", (void **) &gload_glDeleteProgramPipelines },
   { "glGenProgramPipelines", (void **) &gload_glGenProgramPipelines },
   { "glIsProgramPipeline", (void **) &gload_glIsProgramPipeline },
   { "glGetProgramPipelineiv", (void **) &gload_glGetProgramPipelineiv },
   { "glProgramParameteri", (void **) &gload_glProgramParameteri },
   { "glProgramUniform1i", (void **) &gload_glProgramUniform1i },
   { "glProgramUniform1iv", (void **) &gload_glProgramUniform1iv },
   { "glProgramUniform1f", (void **) &gload_glProgramUniform1f },
   { "glProgramUniform1fv", (void **) &gload_glProgramUniform1fv },
   { "glProgramUniform1d", (void **) &gload_glProgramUniform1d },
   { "glProgramUniform1dv", (void **) &gload_glProgramUniform1dv },
   { "glProgramUniform1ui", (void **) &gload_glProgramUniform1ui },
   { "glProgramUniform1uiv", (void **) &gload_glProgramUniform1uiv },
   { "glProgramUniform2i", (void **) &gload_glProgramUniform2i },
   { "glProgramUniform2iv", (void **) &gload_glProgramUniform2iv },
   { "glProgramUniform2f", (void **) &gload_glProgramUniform2f },
   { "glProgramUniform2fv", (void **) &gload_glProgramUniform2fv },
   { "glProgramUniform2d", (void **) &gload_glProgramUniform2d },
   { "glProgramUniform2dv", (void **) &gload_glProgramUniform2dv },
   { "glProgramUniform2ui", (void **) &gload_glProgramUniform2ui },
   { "glProgramUniform2uiv", (void **) &gload_glProgramUniform2uiv },
   { "glProgramUniform3i", (void **) &gload_glProgramUniform3i },
   { "glProgramUniform3iv", (void **) &gload_glProgramUniform3iv },
   { "glProgramUniform3f", (void **) &gload_glProgramUniform3f },
   { "glProgramUniform3fv", (void **) &gload_glProgramUniform3fv },
   { "glProgramUniform3d", (void **) &gload_glProgramUniform3d },
   { "glProgramUniform3dv", (void **) &gload_glProgramUniform3dv },
   { "glProgramUniform3ui", (void **) &gload_glProgramUniform3ui },
   { "glProgramUniform3uiv", (void **) &gload_glProgramUniform3uiv },
   { "glProgramUniform4i", (void **) &gload_glProgramUniform4i },
   { "glProgramUniform4iv", (void **) &gload_glProgramUniform4iv },
   { "glProgramUniform4f", (void **) &gload_glProgramUniform4f },
   { "glProgramUniform4fv", (void **) &gload_glProgramUniform4fv },
   { "glProgramUniform4d", (void **) &gload_glProgramUniform4d },
   { "glProgramUniform4dv", (void **) &gload_glProgramUniform4dv },
   { "glProgramUniform4ui", (void **) &gload_glProgramUniform4ui },
   { "glProgramUniform4uiv", (void **) &gload_glProgramUniform4uiv },
   { "glProgramUniformMatrix2fv", (void **) &gload_glProgramUniformMatrix2fv },
   { "glProgramUniformMatrix3fv", (void **) &gload_glProgramUniformMatrix3fv },
   { "glProgramUniformMatrix4fv", (void **) &gload_glProgramUniformMatrix4fv },
   { "glProgramUniformMatrix2dv", (void **) &gload_glProgramUniformMatrix2dv },
   { "glProgramUniformMatrix3dv", (void **) &gload_glProgramUniformMatrix3dv },
   { "glProgramUniformMatrix4dv", (void **) &gload_glProgramUniformMatrix4dv },
   { "glProgramUniformMatrix2x3fv", (void **) &gload_glProgramUniformMatrix2x3fv },
   { "glProgramUniformMatrix3x2fv", (void **) &gload_glProgramUniformMatrix3x2fv },
   { "glProgramUniformMatrix2x4fv", (void **) &gload_glProgramUniformMatrix2x4fv },
   { "glProgramUniformMatrix4x2fv", (void **) &gload_glProgramUniformMatrix4x2fv },
   { "glProgramUniformMatrix3x4fv", (void **) &gload_glProgramUniformMatrix3x4fv },
   { "glProgramUniformMatrix4x3fv", (void **) &gload_glProgramUniformMatrix4x3fv },
   { "glProgramUniformMatrix2x3dv", (void **) &gload_glProgramUniformMatrix2x3dv },
   { "glProgramUniformMatrix3x2dv", (void **) &gload_glProgramUniformMatrix3x2dv },
   { "glProgramUniformMatrix2x4dv", (void **) &gload_glProgramUniformMatrix2x4dv },
   { "glProgramUniformMatrix4x2dv", (void **) &gload_glProgramUniformMatrix4x2dv },
   { "glProgramUniformMatrix3x4dv", (void **) &gload_glProgramUniformMatrix3x4dv },
   { "glProgramUniformMatrix4x3dv", (void **) &gload_glProgramUniformMatrix4x3dv },
   { "glValidateProgramPipeline", (void **) &gload_glValidateProgramPipeline },
   { "glGetProgramPipelineInfoLog", (void **) &gload_glGetProgramPipelineInfoLog },
   { "glVertexAttribL1d", (void **) &gload_glVertexAttribL1d },
   { "glVertexAttribL2d", (void **) &gload_glVertexAttribL2d },
   { "glVertexAttribL3d", (void **) &gload_glVertexAttribL3d },
   { "glVertexAttribL4d", (void **) &gload_glVertexAttribL4d },
   { "glVertexAttribL1dv", (void **) &gload_glVertexAttribL1dv },
   { "glVertexAttribL2dv", (void **) &gload_glVertexAttribL2dv },
   { "glVertexAttribL3dv", (void **) &gload_glVertexAttribL3dv },
   { "glVertexAttribL4dv", (void **) &gload_glVertexAttribL4dv },
   { "glVertexAttribLPointer", (void **) &gload_glVertexAttribLPointer },
   { "glGetVertexAttribLdv", (void **) &gload_glGetVertexAttribLdv },
   { "glViewportArrayv", (void **) &gload_glViewportArrayv },
   { "glViewportIndexedf", (void **) &gload_glViewportIndexedf },
   { "glViewportIndexedfv", (void **) &gload_glViewportIndexedfv },
   { "glScissorArrayv", (void **) &gload_glScissorArrayv },
   { "glScissorIndexed", (void **) &gload_glScissorIndexed },
   { "glScissorIndexedv", (void **) &gload_glScissorIndexedv },
   { "glDepthRangeArrayv", (void **) &gload_glDepthRangeArrayv },
   { "glDepthRangeIndexed", (void **) &gload_glDepthRangeIndexed },
   { "glGetFloati_v", (void **) &gload_glGetFloati_v },
   { "glGetDoublei_v", (void **) &gload_glGetDoublei_v },

#  endif /* GL_VERSION_4_1 */
#  if defined GL_VERSION_4_2

   { "glDrawArraysInstancedBaseInstance", (void **) &gload_glDrawArraysInstancedBaseInstance },
   { "glDrawElementsInstancedBaseInstance", (void **) &gload_glDrawElementsInstancedBaseInstance },
   { "glDrawElementsInstancedBaseVertexBaseInstance", (void **) &gload_glDrawElementsInstancedBaseVertexBaseInstance },
   { "glGetInternalformativ", (void **) &gload_glGetInternalformativ },
   { "glGetActiveAtomicCounterBufferiv", (void **) &gload_glGetActiveAtomicCounterBufferiv },
   { "glBindImageTexture", (void **) &gload_glBindImageTexture },
   { "glMemoryBarrier", (void **) &gload_glMemoryBarrier },
   { "glTexStorage1D", (void **) &gload_glTexStorage1D },
   { "glTexStorage2D", (void **) &gload_glTexStorage2D },
   { "glTexStorage3D", (void **) &gload_glTexStorage3D },
   { "glDrawTransformFeedbackInstanced", (void **) &gload_glDrawTransformFeedbackInstanced },
   { "glDrawTransformFeedbackStreamInstanced", (void **) &gload_glDrawTransformFeedbackStreamInstanced },

#  endif /* GL_VERSION_4_2 */
#  if defined GL_VERSION_4_3

   { "glClearBufferData", (void **) &gload_glClearBufferData },
   { "glClearBufferSubData", (void **) &gload_glClearBufferSubData },
   { "glDispatchCompute", (void **) &gload_glDispatchCompute },
   { "glDispatchComputeIndirect", (void **) &gload_glDispatchComputeIndirect },
   { "glCopyImageSubData", (void **) &gload_glCopyImageSubData },
   { "glFramebufferParameteri", (void **) &gload_glFramebufferParameteri },
   { "glGetFramebufferParameteriv", (void **) &gload_glGetFramebufferParameteriv },
   { "glGetInternalformati64v", (void **) &gload_glGetInternalformati64v },
   { "glInvalidateTexSubImage", (void **) &gload_glInvalidateTexSubImage },
   { "glInvalidateTexImage", (void **) &gload_glInvalidateTexImage },
   { "glInvalidateBufferSubData", (void **) &gload_glInvalidateBufferSubData },
   { "glInvalidateBufferData", (void **) &gload_glInvalidateBufferData },
   { "glInvalidateFramebuffer", (void **) &gload_glInvalidateFramebuffer },
   { "glInvalidateSubFramebuffer", (void **) &gload_glInvalidateSubFramebuffer },
   { "glMultiDrawArraysIndirect", (void **) &gload_glMultiDrawArraysIndirect },
   { "glMultiDrawElementsIndirect", (void **) &gload_glMultiDrawElementsIndirect },
   { "glGetProgramInterfaceiv", (void **) &gload_glGetProgramInterfaceiv },
   { "glGetProgramResourceIndex", (void **) &gload_glGetProgramResourceIndex },
   { "glGetProgramResourceName", (void **) &gload_glGetProgramResourceName },
   { "glGetProgramResourceiv", (void **) &gload_glGetProgramResourceiv },
   { "glGetProgramResourceLocation", (void **) &gload_glGetProgramResourceLocation },
   { "glGetProgramResourceLocationIndex", (void **) &gload_glGetProgramResourceLocationIndex },
   { "glShaderStorageBlockBinding", (void **) &gload_glShaderStorageBlockBinding },
   { "glTexBufferRange", (void **) &gload_glTexBufferRange },
   { "glTexStorage2DMultisample", (void **) &gload_glTexStorage2DMultisample },
   { "glTexStorage3DMultisample", (void **) &gload_glTexStorage3DMultisample },
   { "glTextureView", (void **) &gload_glTextureView },
   { "glBindVertexBuffer", (void **) &gload_glBindVertexBuffer },
   { "glVertexAttribFormat", (void **) &gload_glVertexAttribFormat },
   { "glVertexAttribIFormat", (void **) &gload_glVertexAttribIFormat },
   { "glVertexAttribLFormat", (void **) &gload_glVertexAttribLFormat },
   { "glVertexAttribBinding", (void **) &gload_glVertexAttribBinding },
   { "glVertexBindingDivisor", (void **) &gload_glVertexBindingDivisor },
   { "glDebugMessageControl", (void **) &gload_glDebugMessageControl },
   { "glDebugMessageInsert", (void **) &gload_glDebugMessageInsert },
   { "glDebugMessageCallback", (void **) &gload_glDebugMessageCallback },
   { "glGetDebugMessageLog", (void **) &gload_glGetDebugMessageLog },
   { "glPushDebugGroup", (void **) &gload_glPushDebugGroup },
   { "glPopDebugGroup", (void **) &gload_glPopDebugGroup },
   { "glObjectLabel", (void **) &gload_glObjectLabel },
   { "glGetObjectLabel", (void **) &gload_glGetObjectLabel },
   { "glObjectPtrLabel", (void **) &gload_glObjectPtrLabel },
   { "glGetObjectPtrLabel", (void **) &gload_glGetObjectPtrLabel },
   { "glGetPointerv", (void **) &gload_glGetPointerv },

#  endif /* GL_VERSION_4_3 */
#  if defined GL_VERSION_4_4

   { "glBufferStorage", (void **) &gload_glBufferStorage },
   { "glClearTexImage", (void **) &gload_glClearTexImage },
   { "glClearTexSubImage", (void **) &gload_glClearTexSubImage },
   { "glBindBuffersBase", (void **) &gload_glBindBuffersBase },
   { "glBindBuffersRange", (void **) &gload_glBindBuffersRange },
   { "glBindTextures", (void **) &gload_glBindTextures },
   { "glBindSamplers", (void **) &gload_glBindSamplers },
   { "glBindImageTextures", (void **) &gload_glBindImageTextures },
   { "glBindVertexBuffers", (void **) &gload_glBindVertexBuffers },

#  endif /* GL_VERSION_4_4 */
#  if defined GL_VERSION_4_5

   { "glClipControl", (void **) &gload_glClipControl },
   { "glCreateTransformFeedbacks", (void **) &gload_glCreateTransformFeedbacks },
   { "glTransformFeedbackBufferBase", (void **) &gload_glTransformFeedbackBufferBase },
   { "glTransformFeedbackBufferRange", (void **) &gload_glTransformFeedbackBufferRange },
   { "glGetTransformFeedbackiv", (void **) &gload_glGetTransformFeedbackiv },
   { "glGetTransformFeedbacki_v", (void **) &gload_glGetTransformFeedbacki_v },
   { "glGetTransformFeedbacki64_v", (void **) &gload_glGetTransformFeedbacki64_v },
   { "glCreateBuffers", (void **) &gload_glCreateBuffers },
   { "glNamedBufferStorage", (void **) &gload_glNamedBufferStorage },
   { "glNamedBufferData", (void **) &gload_glNamedBufferData },
   { "glNamedBufferSubData", (void **) &gload_glNamedBufferSubData },
   { "glCopyNamedBufferSubData", (void **) &gload_glCopyNamedBufferSubData },
   { "glClearNamedBufferData", (void **) &gload_glClearNamedBufferData },
   { "glClearNamedBufferSubData", (void **) &gload_glClearNamedBufferSubData },
   { "glMapNamedBuffer", (void **) &gload_glMapNamedBuffer },
   { "glMapNamedBufferRange", (void **) &gload_glMapNamedBufferRange },
   { "glUnmapNamedBuffer", (void **) &gload_glUnmapNamedBuffer },
   { "glFlushMappedNamedBufferRange", (void **) &gload_glFlushMappedNamedBufferRange },
   { "glGetNamedBufferParameteriv", (void **) &gload_glGetNamedBufferParameteriv },
   { "glGetNamedBufferParameteri64v", (void **) &gload_glGetNamedBufferParameteri64v },
   { "glGetNamedBufferPointerv", (void **) &gload_glGetNamedBufferPointerv },
   { "glGetNamedBufferSubData", (void **) &gload_glGetNamedBufferSubData },
   { "glCreateFramebuffers", (void **) &gload_glCreateFramebuffers },
   { "glNamedFramebufferRenderbuffer", (void **) &gload_glNamedFramebufferRenderbuffer },
   { "glNamedFramebufferParameteri", (void **) &gload_glNamedFramebufferParameteri },
   { "glNamedFramebufferTexture", (void **) &gload_glNamedFramebufferTexture },
   { "glNamedFramebufferTextureLayer", (void **) &gload_glNamedFramebufferTextureLayer },
   { "glNamedFramebufferDrawBuffer", (void **) &gload_glNamedFramebufferDrawBuffer },
   { "glNamedFramebufferDrawBuffers", (void **) &gload_glNamedFramebufferDrawBuffers },
   { "glNamedFramebufferReadBuffer", (void **) &gload_glNamedFramebufferReadBuffer },
   { "glInvalidateNamedFramebufferData", (void **) &gload_glInvalidateNamedFramebufferData },
   { "glInvalidateNamedFramebufferSubData", (void **) &gload_glInvalidateNamedFramebufferSubData },
   { "glClearNamedFramebufferiv", (void **) &gload_glClearNamedFramebufferiv },
   { "glClearNamedFramebufferuiv", (void **) &gload_glClearNamedFramebufferuiv },
   { "glClearNamedFramebufferfv", (void **) &gload_glClearNamedFramebufferfv },
   { "glClearNamedFramebufferfi", (void **) &gload_glClearNamedFramebufferfi },
   { "glBlitNamedFramebuffer", (void **) &gload_glBlitNamedFramebuffer },
   { "glCheckNamedFramebufferStatus", (void **) &gload_glCheckNamedFramebufferStatus },
   { "glGetNamedFramebufferParameteriv", (void **) &gload_glGetNamedFramebufferParameteriv },
   { "glGetNamedFramebufferAttachmentParameteriv", (void **) &gload_glGetNamedFramebufferAttachmentParameteriv },
   { "glCreateRenderbuffers", (void **) &gload_glCreateRenderbuffers },
   { "glNamedRenderbufferStorage", (void **) &gload_glNamedRenderbufferStorage },
   { "glNamedRenderbufferStorageMultisample", (void **) &gload_glNamedRenderbufferStorageMultisample },
   { "glGetNamedRenderbufferParameteriv", (void **) &gload_glGetNamedRenderbufferParameteriv },
   { "glCreateTextures", (void **) &gload_glCreateTextures },
   { "glTextureBuffer", (void **) &gload_glTextureBuffer },
   { "glTextureBufferRange", (void **) &gload_glTextureBufferRange },
   { "glTextureStorage1D", (void **) &gload_glTextureStorage1D },
   { "glTextureStorage2D", (void **) &gload_glTextureStorage2D },
   { "glTextureStorage3D", (void **) &gload_glTextureStorage3D },
   { "glTextureStorage2DMultisample", (void **) &gload_glTextureStorage2DMultisample },
   { "glTextureStorage3DMultisample", (void **) &gload_glTextureStorage3DMultisample },
   { "glTextureSubImage1D", (void **) &gload_glTextureSubImage1D },
   { "glTextureSubImage2D", (void **) &gload_glTextureSubImage2D },
   { "glTextureSubImage3D", (void **) &gload_glTextureSubImage3D },
   { "glCompressedTextureSubImage1D", (void **) &gload_glCompressedTextureSubImage1D },
   { "glCompressedTextureSubImage2D", (void **) &gload_glCompressedTextureSubImage2D },
   { "glCompressedTextureSubImage3D", (void **) &gload_glCompressedTextureSubImage3D },
   { "glCopyTextureSubImage1D", (void **) &gload_glCopyTextureSubImage1D },
   { "glCopyTextureSubImage2D", (void **) &gload_glCopyTextureSubImage2D },
   { "glCopyTextureSubImage3D", (void **) &gload_glCopyTextureSubImage3D },
   { "glTextureParameterf", (void **) &gload_glTextureParameterf },
   { "glTextureParameterfv", (void **) &gload_glTextureParameterfv },
   { "glTextureParameteri", (void **) &gload_glTextureParameteri },
   { "glTextureParameterIiv", (void **) &gload_glTextureParameterIiv },
   { "glTextureParameterIuiv", (void **) &gload_glTextureParameterIuiv },
   { "glTextureParameteriv", (void **) &gload_glTextureParameteriv },
   { "glGenerateTextureMipmap", (void **) &gload_glGenerateTextureMipmap },
   { "glBindTextureUnit", (void **) &gload_glBindTextureUnit },
   { "glGetTextureImage", (void **) &gload_glGetTextureImage },
   { "glGetCompressedTextureImage", (void **) &gload_glGetCompressedTextureImage },
   { "glGetTextureLevelParameterfv", (void **) &gload_glGetTextureLevelParameterfv },
   { "glGetTextureLevelParameteriv", (void **) &gload_glGetTextureLevelParameteriv },
   { "glGetTextureParameterfv", (void **) &gload_glGetTextureParameterfv },
   { "glGetTextureParameterIiv", (void **) &gload_glGetTextureParameterIiv },
   { "glGetTextureParameterIuiv", (void **) &gload_glGetTextureParameterIuiv },
   { "glGetTextureParameteriv", (void **) &gload_glGetTextureParameteriv },
   { "glCreateVertexArrays", (void **) &gload_glCreateVertexArrays },
   { "glDisableVertexArrayAttrib", (void **) &gload_glDisableVertexArrayAttrib },
   { "glEnableVertexArrayAttrib", (void **) &gload_glEnableVertexArrayAttrib },
   { "glVertexArrayElementBuffer", (void **) &gload_glVertexArrayElementBuffer },
   { "glVertexArrayVertexBuffer", (void **) &gload_glVertexArrayVertexBuffer },
   { "glVertexArrayVertexBuffers", (void **) &gload_glVertexArrayVertexBuffers },
   { "glVertexArrayAttribBinding", (void **) &gload_glVertexArrayAttribBinding },
   { "glVertexArrayAttribFormat", (void **) &gload_glVertexArrayAttribFormat },
   { "glVertexArrayAttribIFormat", (void **) &gload_glVertexArrayAttribIFormat },
   { "glVertexArrayAttribLFormat", (void **) &gload_glVertexArrayAttribLFormat },
   { "glVertexArrayBindingDivisor", (void **) &gload_glVertexArrayBindingDivisor },
   { "glGetVertexArrayiv", (void **) &gload_glGetVertexArrayiv },
   { "glGetVertexArrayIndexediv", (void **) &gload_glGetVertexArrayIndexediv },
   { "glGetVertexArrayIndexed64iv", (void **) &gload_glGetVertexArrayIndexed64iv },
   { "glCreateSamplers", (void **) &gload_glCreateSamplers },
   { "glCreateProgramPipelines", (void **) &gload_glCreateProgramPipelines },
   { "glCreateQueries", (void **) &gload_glCreateQueries },
   { "glGetQueryBufferObjecti64v", (void **) &gload_glGetQueryBufferObjecti64v },
   { "glGetQueryBufferObjectiv", (void **) &gload_glGetQueryBufferObjectiv },
   { "glGetQueryBufferObjectui64v", (void **) &gload_glGetQueryBufferObjectui64v },
   { "glGetQueryBufferObjectuiv", (void **) &gload_glGetQueryBufferObjectuiv },
   { "glMemoryBarrierByRegion", (void **) &gload_glMemoryBarrierByRegion },
   { "glGetTextureSubImage", (void **) &gload_glGetTextureSubImage },
   { "glGetCompressedTextureSubImage", (void **) &gload_glGetCompressedTextureSubImage },
   { "glGetGraphicsResetStatus", (void **) &gload_glGetGraphicsResetStatus },
   { "glGetnCompressedTexImage", (void **) &gload_glGetnCompressedTexImage },
   { "glGetnTexImage", (void **) &gload_glGetnTexImage },
   { "glGetnUniformdv", (void **) &gload_glGetnUniformdv },
   { "glGetnUniformfv", (void **) &gload_glGetnUniformfv },
   { "glGetnUniformiv", (void **) &gload_glGetnUniformiv },
   { "glGetnUniformuiv", (void **) &gload_glGetnUniformuiv },
   { "glReadnPixels", (void **) &gload_glReadnPixels },
   { "glGetnMapdv", (void **) &gload_glGetnMapdv },
   { "glGetnMapfv", (void **) &gload_glGetnMapfv },
   { "glGetnMapiv", (void **) &gload_glGetnMapiv },
   { "glGetnPixelMapfv", (void **) &gload_glGetnPixelMapfv },
   { "glGetnPixelMapuiv", (void **) &gload_glGetnPixelMapuiv },
   { "glGetnPixelMapusv", (void **) &gload_glGetnPixelMapusv },
   { "glGetnPolygonStipple", (void **) &gload_glGetnPolygonStipple },
   { "glGetnColorTable", (void **) &gload_glGetnColorTable },
   { "glGetnConvolutionFilter", (void **) &gload_glGetnConvolutionFilter },
   { "glGetnSeparableFilter", (void **) &gload_glGetnSeparableFilter },
   { "glGetnHistogram", (void **) &gload_glGetnHistogram },
   { "glGetnMinmax", (void **) &gload_glGetnMinmax },
   { "glTextureBarrier", (void **) &gload_glTextureBarrier },

#  endif /* GL_VERSION_4_5 */
#  if defined GL_VERSION_4_6

   { "glSpecializeShader", (void **) &gload_glSpecializeShader },
   { "glMultiDrawArraysIndirectCount", (void **) &gload_glMultiDrawArraysIndirectCount },
   { "glMultiDrawElementsIndirectCount", (void **) &gload_glMultiDrawElementsIndirectCount },
   { "glPolygonOffsetClamp", (void **) &gload_glPolygonOffsetClamp },

#  endif /* GL_VERSION_4_6 */
#  if defined GL_VERSION_ES_CM_1_0

   { "glAlphaFunc", (void **) &gload_glAlphaFunc },
   { "glClearColor", (void **) &gload_glClearColor },
   { "glClearDepthf", (void **) &gload_glClearDepthf },
   { "glClipPlanef", (void **) &gload_glClipPlanef },
   { "glColor4f", (void **) &gload_glColor4f },
   { "glDepthRangef", (void **) &gload_glDepthRangef },
   { "glFogf", (void **) &gload_glFogf },
   { "glFogfv", (void **) &gload_glFogfv },
   { "glFrustumf", (void **) &gload_glFrustumf },
   { "glGetClipPlanef", (void **) &gload_glGetClipPlanef },
   { "glGetFloatv", (void **) &gload_glGetFloatv },
   { "glGetLightfv", (void **) &gload_glGetLightfv },
   { "glGetMaterialfv", (void **) &gload_glGetMaterialfv },
   { "glGetTexEnvfv", (void **) &gload_glGetTexEnvfv },
   { "glGetTexParameterfv", (void **) &gload_glGetTexParameterfv },
   { "glLightModelf", (void **) &gload_glLightModelf },
   { "glLightModelfv", (void **) &gload_glLightModelfv },
   { "glLightf", (void **) &gload_glLightf },
   { "glLightfv", (void **) &gload_glLightfv },
   { "glLineWidth", (void **) &gload_glLineWidth },
   { "glLoadMatrixf", (void **) &gload_glLoadMatrixf },
   { "glMaterialf", (void **) &gload_glMaterialf },
   { "glMaterialfv", (void **) &gload_glMaterialfv },
   { "glMultMatrixf", (void **) &gload_glMultMatrixf },
   { "glMultiTexCoord4f", (void **) &gload_glMultiTexCoord4f },
   { "glNormal3f", (void **) &gload_glNormal3f },
   { "glOrthof", (void **) &gload_glOrthof },
   { "glPointParameterf", (void **) &gload_glPointParameterf },
   { "glPointParameterfv", (void **) &gload_glPointParameterfv },
   { "glPointSize", (void **) &gload_glPointSize },
   { "glPolygonOffset", (void **) &gload_glPolygonOffset },
   { "glRotatef", (void **) &gload_glRotatef },
   { "glScalef", (void **) &gload_glScalef },
   { "glTexEnvf", (void **) &gload_glTexEnvf },
   { "glTexEnvfv", (void **) &gload_glTexEnvfv },
   { "glTexParameterf", (void **) &gload_glTexParameterf },
   { "glTexParameterfv", (void **) &gload_glTexParameterfv },
   { "glTranslatef", (void **) &gload_glTranslatef },
   { "glActiveTexture", (void **) &gload_glActiveTexture },
   { "glAlphaFuncx", (void **) &gload_glAlphaFuncx },
   { "glBindBuffer", (void **) &gload_glBindBuffer },
   { "glBindTexture", (void **) &gload_glBindTexture },
   { "glBlendFunc", (void **) &gload_glBlendFunc },
   { "glBufferData", (void **) &gload_glBufferData },
   { "glBufferSubData", (void **) &gload_glBufferSubData },
   { "glClear", (void **) &gload_glClear },
   { "glClearColorx", (void **) &gload_glClearColorx },
   { "glClearDepthx", (void **) &gload_glClearDepthx },
   { "glClearStencil", (void **) &gload_glClearStencil },
   { "glClientActiveTexture", (void **) &gload_glClientActiveTexture },
   { "glClipPlanex", (void **) &gload_glClipPlanex },
   { "glColor4ub", (void **) &gload_glColor4ub },
   { "glColor4x", (void **) &gload_glColor4x },
   { "glColorMask", (void **) &gload_glColorMask },
   { "glColorPointer", (void **) &gload_glColorPointer },
   { "glCompressedTexImage2D", (void **) &gload_glCompressedTexImage2D },
   { "glCompressedTexSubImage2D", (void **) &gload_glCompressedTexSubImage2D },
   { "glCopyTexImage2D", (void **) &gload_glCopyTexImage2D },
   { "glCopyTexSubImage2D", (void **) &gload_glCopyTexSubImage2D },
   { "glCullFace", (void **) &gload_glCullFace },
   { "glDeleteBuffers", (void **) &gload_glDeleteBuffers },
   { "glDeleteTextures", (void **) &gload_glDeleteTextures },
   { "glDepthFunc", (void **) &gload_glDepthFunc },
   { "glDepthMask", (void **) &gload_glDepthMask },
   { "glDepthRangex", (void **) &gload_glDepthRangex },
   { "glDisable", (void **) &gload_glDisable },
   { "glDisableClientState", (void **) &gload_glDisableClientState },
   { "glDrawArrays", (void **) &gload_glDrawArrays },
   { "glDrawElements", (void **) &gload_glDrawElements },
   { "glEnable", (void **) &gload_glEnable },
   { "glEnableClientState", (void **) &gload_glEnableClientState },
   { "glFinish", (void **) &gload_glFinish },
   { "glFlush", (void **) &gload_glFlush },
   { "glFogx", (void **) &gload_glFogx },
   { "glFogxv", (void **) &gload_glFogxv },
   { "glFrontFace", (void **) &gload_glFrontFace },
   { "glFrustumx", (void **) &gload_glFrustumx },
   { "glGetBooleanv", (void **) &gload_glGetBooleanv },
   { "glGetBufferParameteriv", (void **) &gload_glGetBufferParameteriv },
   { "glGetClipPlanex", (void **) &gload_glGetClipPlanex },
   { "glGenBuffers", (void **) &gload_glGenBuffers },
   { "glGenTextures", (void **) &gload_glGenTextures },
   { "glGetError", (void **) &gload_glGetError },
   { "glGetFixedv", (void **) &gload_glGetFixedv },
   { "glGetIntegerv", (void **) &gload_glGetIntegerv },
   { "glGetLightxv", (void **) &gload_glGetLightxv },
   { "glGetMaterialxv", (void **) &gload_glGetMaterialxv },
   { "glGetPointerv", (void **) &gload_glGetPointerv },
   { "glGetString", (void **) &gload_glGetString },
   { "glGetTexEnviv", (void **) &gload_glGetTexEnviv },
   { "glGetTexEnvxv", (void **) &gload_glGetTexEnvxv },
   { "glGetTexParameteriv", (void **) &gload_glGetTexParameteriv },
   { "glGetTexParameterxv", (void **) &gload_glGetTexParameterxv },
   { "glHint", (void **) &gload_glHint },
   { "glIsBuffer", (void **) &gload_glIsBuffer },
   { "glIsEnabled", (void **) &gload_glIsEnabled },
   { "glIsTexture", (void **) &gload_glIsTexture },
   { "glLightModelx", (void **) &gload_glLightModelx },
   { "glLightModelxv", (void **) &gload_glLightModelxv },
   { "glLightx", (void **) &gload_glLightx },
   { "glLightxv", (void **) &gload_glLightxv },
   { "glLineWidthx", (void **) &gload_glLineWidthx },
   { "glLoadIdentity", (void **) &gload_glLoadIdentity },
   { "glLoadMatrixx", (void **) &gload_glLoadMatrixx },
   { "glLogicOp", (void **) &gload_glLogicOp },
   { "glMaterialx", (void **) &gload_glMaterialx },
   { "glMaterialxv", (void **) &gload_glMaterialxv },
   { "glMatrixMode", (void **) &gload_glMatrixMode },
   { "glMultMatrixx", (void **) &gload_glMultMatrixx },
   { "glMultiTexCoord4x", (void **) &gload_glMultiTexCoord4x },
   { "glNormal3x", (void **) &gload_glNormal3x },
   { "glNormalPointer", (void **) &gload_glNormalPointer },
   { "glOrthox", (void **) &gload_glOrthox },
   { "glPixelStorei", (void **) &gload_glPixelStorei },
   { "glPointParameterx", (void **) &gload_glPointParameterx },
   { "glPointParameterxv", (void **) &gload_glPointParameterxv },
   { "glPointSizex", (void **) &gload_glPointSizex },
   { "glPolygonOffsetx", (void **) &gload_glPolygonOffsetx },
   { "glPopMatrix", (void **) &gload_glPopMatrix },
   { "glPushMatrix", (void **) &gload_glPushMatrix },
   { "glReadPixels", (void **) &gload_glReadPixels },
   { "glRotatex", (void **) &gload_glRotatex },
   { "glSampleCoverage", (void **) &gload_glSampleCoverage },
   { "glSampleCoveragex", (void **) &gload_glSampleCoveragex },
   { "glScalex", (void **) &gload_glScalex },
   { "glScissor", (void **) &gload_glScissor },
   { "glShadeModel", (void **) &gload_glShadeModel },
   { "glStencilFunc", (void **) &gload_glStencilFunc },
   { "glStencilMask", (void **) &gload_glStencilMask },
   { "glStencilOp", (void **) &gload_glStencilOp },
   { "glTexCoordPointer", (void **) &gload_glTexCoordPointer },
   { "glTexEnvi", (void **) &gload_glTexEnvi },
   { "glTexEnvx", (void **) &gload_glTexEnvx },
   { "glTexEnviv", (void **) &gload_glTexEnviv },
   { "glTexEnvxv", (void **) &gload_glTexEnvxv },
   { "glTexImage2D", (void **) &gload_glTexImage2D },
   { "glTexParameteri", (void **) &gload_glTexParameteri },
   { "glTexParameterx", (void **) &gload_glTexParameterx },
   { "glTexParameteriv", (void **) &gload_glTexParameteriv },
   { "glTexParameterxv", (void **) &gload_glTexParameterxv },
   { "glTexSubImage2D", (void **) &gload_glTexSubImage2D },
   { "glTranslatex", (void **) &gload_glTranslatex },
   { "glVertexPointer", (void **) &gload_glVertexPointer },
   { "glViewport", (void **) &gload_glViewport },

#  endif /* GL_VERSION_ES_CM_1_0 */
#  if defined GL_ES_VERSION_2_0

   { "glActiveTexture", (void **) &gload_glActiveTexture },
   { "glAttachShader", (void **) &gload_glAttachShader },
   { "glBindAttribLocation", (void **) &gload_glBindAttribLocation },
   { "glBindBuffer", (void **) &gload_glBindBuffer },
   { "glBindFramebuffer", (void **) &gload_glBindFramebuffer },
   { "glBindRenderbuffer", (void **) &gload_glBindRenderbuffer },
   { "glBindTexture", (void **) &gload_glBindTexture },
   { "glBlendColor", (void **) &gload_glBlendColor },
   { "glBlendEquation", (void **) &gload_glBlendEquation },
   { "glBlendEquationSeparate", (void **) &gload_glBlendEquationSeparate },
   { "glBlendFunc", (void **) &gload_glBlendFunc },
   { "glBlendFuncSeparate", (void **) &gload_glBlendFuncSeparate },
   { "glBufferData", (void **) &gload_glBufferData },
   { "glBufferSubData", (void **) &gload_glBufferSubData },
   { "glCheckFramebufferStatus", (void **) &gload_glCheckFramebufferStatus },
   { "glClear", (void **) &gload_glClear },
   { "glClearColor", (void **) &gload_glClearColor },
   { "glClearDepthf", (void **) &gload_glClearDepthf },
   { "glClearStencil", (void **) &gload_glClearStencil },
   { "glColorMask", (void **) &gload_glColorMask },
   { "glCompileShader", (void **) &gload_glCompileShader },
   { "glCompressedTexImage2D", (void **) &gload_glCompressedTexImage2D },
   { "glCompressedTexSubImage2D", (void **) &gload_glCompressedTexSubImage2D },
   { "glCopyTexImage2D", (void **) &gload_glCopyTexImage2D },
   { "glCopyTexSubImage2D", (void **) &gload_glCopyTexSubImage2D },
   { "glCreateProgram", (void **) &gload_glCreateProgram },
   { "glCreateShader", (void **) &gload_glCreateShader },
   { "glCullFace", (void **) &gload_glCullFace },
   { "glDeleteBuffers", (void **) &gload_glDeleteBuffers },
   { "glDeleteFramebuffers", (void **) &gload_glDeleteFramebuffers },
   { "glDeleteProgram", (void **) &gload_glDeleteProgram },
   { "glDeleteRenderbuffers", (void **) &gload_glDeleteRenderbuffers },
   { "glDeleteShader", (void **) &gload_glDeleteShader },
   { "glDeleteTextures", (void **) &gload_glDeleteTextures },
   { "glDepthFunc", (void **) &gload_glDepthFunc },
   { "glDepthMask", (void **) &gload_glDepthMask },
   { "glDepthRangef", (void **) &gload_glDepthRangef },
   { "glDetachShader", (void **) &gload_glDetachShader },
   { "glDisable", (void **) &gload_glDisable },
   { "glDisableVertexAttribArray", (void **) &gload_glDisableVertexAttribArray },
   { "glDrawArrays", (void **) &gload_glDrawArrays },
   { "glDrawElements", (void **) &gload_glDrawElements },
   { "glEnable", (void **) &gload_glEnable },
   { "glEnableVertexAttribArray", (void **) &gload_glEnableVertexAttribArray },
   { "glFinish", (void **) &gload_glFinish },
   { "glFlush", (void **) &gload_glFlush },
   { "glFramebufferRenderbuffer", (void **) &gload_glFramebufferRenderbuffer },
   { "glFramebufferTexture2D", (void **) &gload_glFramebufferTexture2D },
   { "glFrontFace", (void **) &gload_glFrontFace },
   { "glGenBuffers", (void **) &gload_glGenBuffers },
   { "glGenerateMipmap", (void **) &gload_glGenerateMipmap },
   { "glGenFramebuffers", (void **) &gload_glGenFramebuffers },
   { "glGenRenderbuffers", (void **) &gload_glGenRenderbuffers },
   { "glGenTextures", (void **) &gload_glGenTextures },
   { "glGetActiveAttrib", (void **) &gload_glGetActiveAttrib },
   { "glGetActiveUniform", (void **) &gload_glGetActiveUniform },
   { "glGetAttachedShaders", (void **) &gload_glGetAttachedShaders },
   { "glGetAttribLocation", (void **) &gload_glGetAttribLocation },
   { "glGetBooleanv", (void **) &gload_glGetBooleanv },
   { "glGetBufferParameteriv", (void **) &gload_glGetBufferParameteriv },
   { "glGetError", (void **) &gload_glGetError },
   { "glGetFloatv", (void **) &gload_glGetFloatv },
   { "glGetFramebufferAttachmentParameteriv", (void **) &gload_glGetFramebufferAttachmentParameteriv },
   { "glGetIntegerv", (void **) &gload_glGetIntegerv },
   { "glGetProgramiv", (void **) &gload_glGetProgramiv },
   { "glGetProgramInfoLog", (void **) &gload_glGetProgramInfoLog },
   { "glGetRenderbufferParameteriv", (void **) &gload_glGetRenderbufferParameteriv },
   { "glGetShaderiv", (void **) &gload_glGetShaderiv },
   { "glGetShaderInfoLog", (void **) &gload_glGetShaderInfoLog },
   { "glGetShaderPrecisionFormat", (void **) &gload_glGetShaderPrecisionFormat },
   { "glGetShaderSource", (void **) &gload_glGetShaderSource },
   { "glGetString", (void **) &gload_glGetString },
   { "glGetTexParameterfv", (void **) &gload_glGetTexParameterfv },
   { "glGetTexParameteriv", (void **) &gload_glGetTexParameteriv },
   { "glGetUniformfv", (void **) &gload_glGetUniformfv },
   { "glGetUniformiv", (void **) &gload_glGetUniformiv },
   { "glGetUniformLocation", (void **) &gload_glGetUniformLocation },
   { "glGetVertexAttribfv", (void **) &gload_glGetVertexAttribfv },
   { "glGetVertexAttribiv", (void **) &gload_glGetVertexAttribiv },
   { "glGetVertexAttribPointerv", (void **) &gload_glGetVertexAttribPointerv },
   { "glHint", (void **) &gload_glHint },
   { "glIsBuffer", (void **) &gload_glIsBuffer },
   { "glIsEnabled", (void **) &gload_glIsEnabled },
   { "glIsFramebuffer", (void **) &gload_glIsFramebuffer },
   { "glIsProgram", (void **) &gload_glIsProgram },
   { "glIsRenderbuffer", (void **) &gload_glIsRenderbuffer },
   { "glIsShader", (void **) &gload_glIsShader },
   { "glIsTexture", (void **) &gload_glIsTexture },
   { "glLineWidth", (void **) &gload_glLineWidth },
   { "glLinkProgram", (void **) &gload_glLinkProgram },
   { "glPixelStorei", (void **) &gload_glPixelStorei },
   { "glPolygonOffset", (void **) &gload_glPolygonOffset },
   { "glReadPixels", (void **) &gload_glReadPixels },
   { "glReleaseShaderCompiler", (void **) &gload_glReleaseShaderCompiler },
   { "glRenderbufferStorage", (void **) &gload_glRenderbufferStorage },
   { "glSampleCoverage", (void **) &gload_glSampleCoverage },
   { "glScissor", (void **) &gload_glScissor },
   { "glShaderBinary", (void **) &gload_glShaderBinary },
   { "glShaderSource", (void **) &gload_glShaderSource },
   { "glStencilFunc", (void **) &gload_glStencilFunc },
   { "glStencilFuncSeparate", (void **) &gload_glStencilFuncSeparate },
   { "glStencilMask", (void **) &gload_glStencilMask },
   { "glStencilMaskSeparate", (void **) &gload_glStencilMaskSeparate },
   { "glStencilOp", (void **) &gload_glStencilOp },
   { "glStencilOpSeparate", (void **) &gload_glStencilOpSeparate },
   { "glTexImage2D", (void **) &gload_glTexImage2D },
   { "glTexParameterf", (void **) &gload_glTexParameterf },
   { "glTexParameterfv", (void **) &gload_glTexParameterfv },
   { "glTexParameteri", (void **) &gload_glTexParameteri },
   { "glTexParameteriv", (void **) &gload_glTexParameteriv },
   { "glTexSubImage2D", (void **) &gload_glTexSubImage2D },
   { "glUniform1f", (void **) &gload_glUniform1f },
   { "glUniform1fv", (void **) &gload_glUniform1fv },
   { "glUniform1i", (void **) &gload_glUniform1i },
   { "glUniform1iv", (void **) &gload_glUniform1iv },
   { "glUniform2f", (void **) &gload_glUniform2f },
   { "glUniform2fv", (void **) &gload_glUniform2fv },
   { "glUniform2i", (void **) &gload_glUniform2i },
   { "glUniform2iv", (void **) &gload_glUniform2iv },
   { "glUniform3f", (void **) &gload_glUniform3f },
   { "glUniform3fv", (void **) &gload_glUniform3fv },
   { "glUniform3i", (void **) &gload_glUniform3i },
   { "glUniform3iv", (void **) &gload_glUniform3iv },
   { "glUniform4f", (void **) &gload_glUniform4f },
   { "glUniform4fv", (void **) &gload_glUniform4fv },
   { "glUniform4i", (void **) &gload_glUniform4i },
   { "glUniform4iv", (void **) &gload_glUniform4iv },
   { "glUniformMatrix2fv", (void **) &gload_glUniformMatrix2fv },
   { "glUniformMatrix3fv", (void **) &gload_glUniformMatrix3fv },
   { "glUniformMatrix4fv", (void **) &gload_glUniformMatrix4fv },
   { "glUseProgram", (void **) &gload_glUseProgram },
   { "glValidateProgram", (void **) &gload_glValidateProgram },
   { "glVertexAttrib1f", (void **) &gload_glVertexAttrib1f },
   { "glVertexAttrib1fv", (void **) &gload_glVertexAttrib1fv },
   { "glVertexAttrib2f", (void **) &gload_glVertexAttrib2f },
   { "glVertexAttrib2fv", (void **) &gload_glVertexAttrib2fv },
   { "glVertexAttrib3f", (void **) &gload_glVertexAttrib3f },
   { "glVertexAttrib3fv", (void **) &gload_glVertexAttrib3fv },
   { "glVertexAttrib4f", (void **) &gload_glVertexAttrib4f },
   { "glVertexAttrib4fv", (void **) &gload_glVertexAttrib4fv },
   { "glVertexAttribPointer", (void **) &gload_glVertexAttribPointer },
   { "glViewport", (void **) &gload_glViewport },

#  endif /* GL_ES_VERSION_2_0 */
#  if defined GL_ES_VERSION_3_0

   { "glReadBuffer", (void **) &gload_glReadBuffer },
   { "glDrawRangeElements", (void **) &gload_glDrawRangeElements },
   { "glTexImage3D", (void **) &gload_glTexImage3D },
   { "glTexSubImage3D", (void **) &gload_glTexSubImage3D },
   { "glCopyTexSubImage3D", (void **) &gload_glCopyTexSubImage3D },
   { "glCompressedTexImage3D", (void **) &gload_glCompressedTexImage3D },
   { "glCompressedTexSubImage3D", (void **) &gload_glCompressedTexSubImage3D },
   { "glGenQueries", (void **) &gload_glGenQueries },
   { "glDeleteQueries", (void **) &gload_glDeleteQueries },
   { "glIsQuery", (void **) &gload_glIsQuery },
   { "glBeginQuery", (void **) &gload_glBeginQuery },
   { "glEndQuery", (void **) &gload_glEndQuery },
   { "glGetQueryiv", (void **) &gload_glGetQueryiv },
   { "glGetQueryObjectuiv", (void **) &gload_glGetQueryObjectuiv },
   { "glUnmapBuffer", (void **) &gload_glUnmapBuffer },
   { "glGetBufferPointerv", (void **) &gload_glGetBufferPointerv },
   { "glDrawBuffers", (void **) &gload_glDrawBuffers },
   { "glUniformMatrix2x3fv", (void **) &gload_glUniformMatrix2x3fv },
   { "glUniformMatrix3x2fv", (void **) &gload_glUniformMatrix3x2fv },
   { "glUniformMatrix2x4fv", (void **) &gload_glUniformMatrix2x4fv },
   { "glUniformMatrix4x2fv", (void **) &gload_glUniformMatrix4x2fv },
   { "glUniformMatrix3x4fv", (void **) &gload_glUniformMatrix3x4fv },
   { "glUniformMatrix4x3fv", (void **) &gload_glUniformMatrix4x3fv },
   { "glBlitFramebuffer", (void **) &gload_glBlitFramebuffer },
   { "glRenderbufferStorageMultisample", (void **) &gload_glRenderbufferStorageMultisample },
   { "glFramebufferTextureLayer", (void **) &gload_glFramebufferTextureLayer },
   { "glMapBufferRange", (void **) &gload_glMapBufferRange },
   { "glFlushMappedBufferRange", (void **) &gload_glFlushMappedBufferRange },
   { "glBindVertexArray", (void **) &gload_glBindVertexArray },
   { "glDeleteVertexArrays", (void **) &gload_glDeleteVertexArrays },
   { "glGenVertexArrays", (void **) &gload_glGenVertexArrays },
   { "glIsVertexArray", (void **) &gload_glIsVertexArray },
   { "glGetIntegeri_v", (void **) &gload_glGetIntegeri_v },
   { "glBeginTransformFeedback", (void **) &gload_glBeginTransformFeedback },
   { "glEndTransformFeedback", (void **) &gload_glEndTransformFeedback },
   { "glBindBufferRange", (void **) &gload_glBindBufferRange },
   { "glBindBufferBase", (void **) &gload_glBindBufferBase },
   { "glTransformFeedbackVaryings", (void **) &gload_glTransformFeedbackVaryings },
   { "glGetTransformFeedbackVarying", (void **) &gload_glGetTransformFeedbackVarying },
   { "glVertexAttribIPointer", (void **) &gload_glVertexAttribIPointer },
   { "glGetVertexAttribIiv", (void **) &gload_glGetVertexAttribIiv },
   { "glGetVertexAttribIuiv", (void **) &gload_glGetVertexAttribIuiv },
   { "glVertexAttribI4i", (void **) &gload_glVertexAttribI4i },
   { "glVertexAttribI4ui", (void **) &gload_glVertexAttribI4ui },
   { "glVertexAttribI4iv", (void **) &gload_glVertexAttribI4iv },
   { "glVertexAttribI4uiv", (void **) &gload_glVertexAttribI4uiv },
   { "glGetUniformuiv", (void **) &gload_glGetUniformuiv },
   { "glGetFragDataLocation", (void **) &gload_glGetFragDataLocation },
   { "glUniform1ui", (void **) &gload_glUniform1ui },
   { "glUniform2ui", (void **) &gload_glUniform2ui },
   { "glUniform3ui", (void **) &gload_glUniform3ui },
   { "glUniform4ui", (void **) &gload_glUniform4ui },
   { "glUniform1uiv", (void **) &gload_glUniform1uiv },
   { "glUniform2uiv", (void **) &gload_glUniform2uiv },
   { "glUniform3uiv", (void **) &gload_glUniform3uiv },
   { "glUniform4uiv", (void **) &gload_glUniform4uiv },
   { "glClearBufferiv", (void **) &gload_glClearBufferiv },
   { "glClearBufferuiv", (void **) &gload_glClearBufferuiv },
   { "glClearBufferfv", (void **) &gload_glClearBufferfv },
   { "glClearBufferfi", (void **) &gload_glClearBufferfi },
   { "glGetStringi", (void **) &gload_glGetStringi },
   { "glCopyBufferSubData", (void **) &gload_glCopyBufferSubData },
   { "glGetUniformIndices", (void **) &gload_glGetUniformIndices },
   { "glGetActiveUniformsiv", (void **) &gload_glGetActiveUniformsiv },
   { "glGetUniformBlockIndex", (void **) &gload_glGetUniformBlockIndex },
   { "glGetActiveUniformBlockiv", (void **) &gload_glGetActiveUniformBlockiv },
   { "glGetActiveUniformBlockName", (void **) &gload_glGetActiveUniformBlockName },
   { "glUniformBlockBinding", (void **) &gload_glUniformBlockBinding },
   { "glDrawArraysInstanced", (void **) &gload_glDrawArraysInstanced },
   { "glDrawElementsInstanced", (void **) &gload_glDrawElementsInstanced },
   { "glFenceSync", (void **) &gload_glFenceSync },
   { "glIsSync", (void **) &gload_glIsSync },
   { "glDeleteSync", (void **) &gload_glDeleteSync },
   { "glClientWaitSync", (void **) &gload_glClientWaitSync },
   { "glWaitSync", (void **) &gload_glWaitSync },
   { "glGetInteger64v", (void **) &gload_glGetInteger64v },
   { "glGetSynciv", (void **) &gload_glGetSynciv },
   { "glGetInteger64i_v", (void **) &gload_glGetInteger64i_v },
   { "glGetBufferParameteri64v", (void **) &gload_glGetBufferParameteri64v },
   { "glGenSamplers", (void **) &gload_glGenSamplers },
   { "glDeleteSamplers", (void **) &gload_glDeleteSamplers },
   { "glIsSampler", (void **) &gload_glIsSampler },
   { "glBindSampler", (void **) &gload_glBindSampler },
   { "glSamplerParameteri", (void **) &gload_glSamplerParameteri },
   { "glSamplerParameteriv", (void **) &gload_glSamplerParameteriv },
   { "glSamplerParameterf", (void **) &gload_glSamplerParameterf },
   { "glSamplerParameterfv", (void **) &gload_glSamplerParameterfv },
   { "glGetSamplerParameteriv", (void **) &gload_glGetSamplerParameteriv },
   { "glGetSamplerParameterfv", (void **) &gload_glGetSamplerParameterfv },
   { "glVertexAttribDivisor", (void **) &gload_glVertexAttribDivisor },
   { "glBindTransformFeedback", (void **) &gload_glBindTransformFeedback },
   { "glDeleteTransformFeedbacks", (void **) &gload_glDeleteTransformFeedbacks },
   { "glGenTransformFeedbacks", (void **) &gload_glGenTransformFeedbacks },
   { "glIsTransformFeedback", (void **) &gload_glIsTransformFeedback },
   { "glPauseTransformFeedback", (void **) &gload_glPauseTransformFeedback },
   { "glResumeTransformFeedback", (void **) &gload_glResumeTransformFeedback },
   { "glGetProgramBinary", (void **) &gload_glGetProgramBinary },
   { "glProgramBinary", (void **) &gload_glProgramBinary },
   { "glProgramParameteri", (void **) &gload_glProgramParameteri },
   { "glInvalidateFramebuffer", (void **) &gload_glInvalidateFramebuffer },
   { "glInvalidateSubFramebuffer", (void **) &gload_glInvalidateSubFramebuffer },
   { "glTexStorage2D", (void **) &gload_glTexStorage2D },
   { "glTexStorage3D", (void **) &gload_glTexStorage3D },
   { "glGetInternalformativ", (void **) &gload_glGetInternalformativ },

#  endif /* GL_ES_VERSION_3_0 */
#  if defined GL_ES_VERSION_3_1

   { "glDispatchCompute", (void **) &gload_glDispatchCompute },
   { "glDispatchComputeIndirect", (void **) &gload_glDispatchComputeIndirect },
   { "glDrawArraysIndirect", (void **) &gload_glDrawArraysIndirect },
   { "glDrawElementsIndirect", (void **) &gload_glDrawElementsIndirect },
   { "glFramebufferParameteri", (void **) &gload_glFramebufferParameteri },
   { "glGetFramebufferParameteriv", (void **) &gload_glGetFramebufferParameteriv },
   { "glGetProgramInterfaceiv", (void **) &gload_glGetProgramInterfaceiv },
   { "glGetProgramResourceIndex", (void **) &gload_glGetProgramResourceIndex },
   { "glGetProgramResourceName", (void **) &gload_glGetProgramResourceName },
   { "glGetProgramResourceiv", (void **) &gload_glGetProgramResourceiv },
   { "glGetProgramResourceLocation", (void **) &gload_glGetProgramResourceLocation },
   { "glUseProgramStages", (void **) &gload_glUseProgramStages },
   { "glActiveShaderProgram", (void **) &gload_glActiveShaderProgram },
   { "glCreateShaderProgramv", (void **) &gload_glCreateShaderProgramv },
   { "glBindProgramPipeline", (void **) &gload_glBindProgramPipeline },
   { "glDeleteProgramPipelines", (void **) &gload_glDeleteProgramPipelines },
   { "glGenProgramPipelines", (void **) &gload_glGenProgramPipelines },
   { "glIsProgramPipeline", (void **) &gload_glIsProgramPipeline },
   { "glGetProgramPipelineiv", (void **) &gload_glGetProgramPipelineiv },
   { "glProgramUniform1i", (void **) &gload_glProgramUniform1i },
   { "glProgramUniform2i", (void **) &gload_glProgramUniform2i },
   { "glProgramUniform3i", (void **) &gload_glProgramUniform3i },
   { "glProgramUniform4i", (void **) &gload_glProgramUniform4i },
   { "glProgramUniform1ui", (void **) &gload_glProgramUniform1ui },
   { "glProgramUniform2ui", (void **) &gload_glProgramUniform2ui },
   { "glProgramUniform3ui", (void **) &gload_glProgramUniform3ui },
   { "glProgramUniform4ui", (void **) &gload_glProgramUniform4ui },
   { "glProgramUniform1f", (void **) &gload_glProgramUniform1f },
   { "glProgramUniform2f", (void **) &gload_glProgramUniform2f },
   { "glProgramUniform3f", (void **) &gload_glProgramUniform3f },
   { "glProgramUniform4f", (void **) &gload_glProgramUniform4f },
   { "glProgramUniform1iv", (void **) &gload_glProgramUniform1iv },
   { "glProgramUniform2iv", (void **) &gload_glProgramUniform2iv },
   { "glProgramUniform3iv", (void **) &gload_glProgramUniform3iv },
   { "glProgramUniform4iv", (void **) &gload_glProgramUniform4iv },
   { "glProgramUniform1uiv", (void **) &gload_glProgramUniform1uiv },
   { "glProgramUniform2uiv", (void **) &gload_glProgramUniform2uiv },
   { "glProgramUniform3uiv", (void **) &gload_glProgramUniform3uiv },
   { "glProgramUniform4uiv", (void **) &gload_glProgramUniform4uiv },
   { "glProgramUniform1fv", (void **) &gload_glProgramUniform1fv },
   { "glProgramUniform2fv", (void **) &gload_glProgramUniform2fv },
   { "glProgramUniform3fv", (void **) &gload_glProgramUniform3fv },
   { "glProgramUniform4fv", (void **) &gload_glProgramUniform4fv },
   { "glProgramUniformMatrix2fv", (void **) &gload_glProgramUniformMatrix2fv },
   { "glProgramUniformMatrix3fv", (void **) &gload_glProgramUniformMatrix3fv },
   { "glProgramUniformMatrix4fv", (void **) &gload_glProgramUniformMatrix4fv },
   { "glProgramUniformMatrix2x3fv", (void **) &gload_glProgramUniformMatrix2x3fv },
   { "glProgramUniformMatrix3x2fv", (void **) &gload_glProgramUniformMatrix3x2fv },
   { "glProgramUniformMatrix2x4fv", (void **) &gload_glProgramUniformMatrix2x4fv },
   { "glProgramUniformMatrix4x2fv", (void **) &gload_glProgramUniformMatrix4x2fv },
   { "glProgramUniformMatrix3x4fv", (void **) &gload_glProgramUniformMatrix3x4fv },
   { "glProgramUniformMatrix4x3fv", (void **) &gload_glProgramUniformMatrix4x3fv },
   { "glValidateProgramPipeline", (void **) &gload_glValidateProgramPipeline },
   { "glGetProgramPipelineInfoLog", (void **) &gload_glGetProgramPipelineInfoLog },
   { "glBindImageTexture", (void **) &gload_glBindImageTexture },
   { "glGetBooleani_v", (void **) &gload_glGetBooleani_v },
   { "glMemoryBarrier", (void **) &gload_glMemoryBarrier },
   { "glMemoryBarrierByRegion", (void **) &gload_glMemoryBarrierByRegion },
   { "glTexStorage2DMultisample", (void **) &gload_glTexStorage2DMultisample },
   { "glGetMultisamplefv", (void **) &gload_glGetMultisamplefv },
   { "glSampleMaski", (void **) &gload_glSampleMaski },
   { "glGetTexLevelParameteriv", (void **) &gload_glGetTexLevelParameteriv },
   { "glGetTexLevelParameterfv", (void **) &gload_glGetTexLevelParameterfv },
   { "glBindVertexBuffer", (void **) &gload_glBindVertexBuffer },
   { "glVertexAttribFormat", (void **) &gload_glVertexAttribFormat },
   { "glVertexAttribIFormat", (void **) &gload_glVertexAttribIFormat },
   { "glVertexAttribBinding", (void **) &gload_glVertexAttribBinding },
   { "glVertexBindingDivisor", (void **) &gload_glVertexBindingDivisor },

#  endif /* GL_ES_VERSION_3_1 */
#  if defined GL_ES_VERSION_3_2

   { "glBlendBarrier", (void **) &gload_glBlendBarrier },
   { "glCopyImageSubData", (void **) &gload_glCopyImageSubData },
   { "glDebugMessageControl", (void **) &gload_glDebugMessageControl },
   { "glDebugMessageInsert", (void **) &gload_glDebugMessageInsert },
   { "glDebugMessageCallback", (void **) &gload_glDebugMessageCallback },
   { "glGetDebugMessageLog", (void **) &gload_glGetDebugMessageLog },
   { "glPushDebugGroup", (void **) &gload_glPushDebugGroup },
   { "glPopDebugGroup", (void **) &gload_glPopDebugGroup },
   { "glObjectLabel", (void **) &gload_glObjectLabel },
   { "glGetObjectLabel", (void **) &gload_glGetObjectLabel },
   { "glObjectPtrLabel", (void **) &gload_glObjectPtrLabel },
   { "glGetObjectPtrLabel", (void **) &gload_glGetObjectPtrLabel },
   { "glGetPointerv", (void **) &gload_glGetPointerv },
   { "glEnablei", (void **) &gload_glEnablei },
   { "glDisablei", (void **) &gload_glDisablei },
   { "glBlendEquationi", (void **) &gload_glBlendEquationi },
   { "glBlendEquationSeparatei", (void **) &gload_glBlendEquationSeparatei },
   { "glBlendFunci", (void **) &gload_glBlendFunci },
   { "glBlendFuncSeparatei", (void **) &gload_glBlendFuncSeparatei },
   { "glColorMaski", (void **) &gload_glColorMaski },
   { "glIsEnabledi", (void **) &gload_glIsEnabledi },
   { "glDrawElementsBaseVertex", (void **) &gload_glDrawElementsBaseVertex },
   { "glDrawRangeElementsBaseVertex", (void **) &gload_glDrawRangeElementsBaseVertex },
   { "glDrawElementsInstancedBaseVertex", (void **) &gload_glDrawElementsInstancedBaseVertex },
   { "glFramebufferTexture", (void **) &gload_glFramebufferTexture },
   { "glPrimitiveBoundingBox", (void **) &gload_glPrimitiveBoundingBox },
   { "glGetGraphicsResetStatus", (void **) &gload_glGetGraphicsResetStatus },
   { "glReadnPixels", (void **) &gload_glReadnPixels },
   { "glGetnUniformfv", (void **) &gload_glGetnUniformfv },
   { "glGetnUniformiv", (void **) &gload_glGetnUniformiv },
   { "glGetnUniformuiv", (void **) &gload_glGetnUniformuiv },
   { "glMinSampleShading", (void **) &gload_glMinSampleShading },
   { "glPatchParameteri", (void **) &gload_glPatchParameteri },
   { "glTexParameterIiv", (void **) &gload_glTexParameterIiv },
   { "glTexParameterIuiv", (void **) &gload_glTexParameterIuiv },
   { "glGetTexParameterIiv", (void **) &gload_glGetTexParameterIiv },
   { "glGetTexParameterIuiv", (void **) &gload_glGetTexParameterIuiv },
   { "glSamplerParameterIiv", (void **) &gload_glSamplerParameterIiv },
   { "glSamplerParameterIuiv", (void **) &gload_glSamplerParameterIuiv },
   { "glGetSamplerParameterIiv", (void **) &gload_glGetSamplerParameterIiv },
   { "glGetSamplerParameterIuiv", (void **) &gload_glGetSamplerParameterIuiv },
   { "glTexBuffer", (void **) &gload_glTexBuffer },
   { "glTexBufferRange", (void **) &gload_glTexBufferRange },
   { "glTexStorage3DMultisample", (void **) &gload_glTexStorage3DMultisample },

#  endif /* GL_ES_VERSION_3_2 */
#  if defined GL_SC_VERSION_2_0

   { "glActiveTexture", (void **) &gload_glActiveTexture },
   { "glBindBuffer", (void **) &gload_glBindBuffer },
   { "glBindFramebuffer", (void **) &gload_glBindFramebuffer },
   { "glBindRenderbuffer", (void **) &gload_glBindRenderbuffer },
   { "glBindTexture", (void **) &gload_glBindTexture },
   { "glBlendColor", (void **) &gload_glBlendColor },
   { "glBlendEquation", (void **) &gload_glBlendEquation },
   { "glBlendEquationSeparate", (void **) &gload_glBlendEquationSeparate },
   { "glBlendFunc", (void **) &gload_glBlendFunc },
   { "glBlendFuncSeparate", (void **) &gload_glBlendFuncSeparate },
   { "glBufferData", (void **) &gload_glBufferData },
   { "glBufferSubData", (void **) &gload_glBufferSubData },
   { "glCheckFramebufferStatus", (void **) &gload_glCheckFramebufferStatus },
   { "glClear", (void **) &gload_glClear },
   { "glClearColor", (void **) &gload_glClearColor },
   { "glClearDepthf", (void **) &gload_glClearDepthf },
   { "glClearStencil", (void **) &gload_glClearStencil },
   { "glColorMask", (void **) &gload_glColorMask },
   { "glCompressedTexSubImage2D", (void **) &gload_glCompressedTexSubImage2D },
   { "glCreateProgram", (void **) &gload_glCreateProgram },
   { "glCullFace", (void **) &gload_glCullFace },
   { "glDepthFunc", (void **) &gload_glDepthFunc },
   { "glDepthMask", (void **) &gload_glDepthMask },
   { "glDepthRangef", (void **) &gload_glDepthRangef },
   { "glDisable", (void **) &gload_glDisable },
   { "glDisableVertexAttribArray", (void **) &gload_glDisableVertexAttribArray },
   { "glDrawArrays", (void **) &gload_glDrawArrays },
   { "glDrawRangeElements", (void **) &gload_glDrawRangeElements },
   { "glEnable", (void **) &gload_glEnable },
   { "glEnableVertexAttribArray", (void **) &gload_glEnableVertexAttribArray },
   { "glFinish", (void **) &gload_glFinish },
   { "glFlush", (void **) &gload_glFlush },
   { "glFramebufferRenderbuffer", (void **) &gload_glFramebufferRenderbuffer },
   { "glFramebufferTexture2D", (void **) &gload_glFramebufferTexture2D },
   { "glFrontFace", (void **) &gload_glFrontFace },
   { "glGenBuffers", (void **) &gload_glGenBuffers },
   { "glGenerateMipmap", (void **) &gload_glGenerateMipmap },
   { "glGenFramebuffers", (void **) &gload_glGenFramebuffers },
   { "glGenRenderbuffers", (void **) &gload_glGenRenderbuffers },
   { "glGenTextures", (void **) &gload_glGenTextures },
   { "glGetAttribLocation", (void **) &gload_glGetAttribLocation },
   { "glGetBooleanv", (void **) &gload_glGetBooleanv },
   { "glGetBufferParameteriv", (void **) &gload_glGetBufferParameteriv },
   { "glGetError", (void **) &gload_glGetError },
   { "glGetFloatv", (void **) &gload_glGetFloatv },
   { "glGetFramebufferAttachmentParameteriv", (void **) &gload_glGetFramebufferAttachmentParameteriv },
   { "glGetGraphicsResetStatus", (void **) &gload_glGetGraphicsResetStatus },
   { "glGetIntegerv", (void **) &gload_glGetIntegerv },
   { "glGetProgramiv", (void **) &gload_glGetProgramiv },
   { "glGetRenderbufferParameteriv", (void **) &gload_glGetRenderbufferParameteriv },
   { "glGetString", (void **) &gload_glGetString },
   { "glGetTexParameterfv", (void **) &gload_glGetTexParameterfv },
   { "glGetTexParameteriv", (void **) &gload_glGetTexParameteriv },
   { "glGetnUniformfv", (void **) &gload_glGetnUniformfv },
   { "glGetnUniformiv", (void **) &gload_glGetnUniformiv },
   { "glGetUniformLocation", (void **) &gload_glGetUniformLocation },
   { "glGetVertexAttribfv", (void **) &gload_glGetVertexAttribfv },
   { "glGetVertexAttribiv", (void **) &gload_glGetVertexAttribiv },
   { "glGetVertexAttribPointerv", (void **) &gload_glGetVertexAttribPointerv },
   { "glHint", (void **) &gload_glHint },
   { "glIsEnabled", (void **) &gload_glIsEnabled },
   { "glLineWidth", (void **) &gload_glLineWidth },
   { "glPixelStorei", (void **) &gload_glPixelStorei },
   { "glPolygonOffset", (void **) &gload_glPolygonOffset },
   { "glProgramBinary", (void **) &gload_glProgramBinary },
   { "glReadnPixels", (void **) &gload_glReadnPixels },
   { "glRenderbufferStorage", (void **) &gload_glRenderbufferStorage },
   { "glSampleCoverage", (void **) &gload_glSampleCoverage },
   { "glScissor", (void **) &gload_glScissor },
   { "glStencilFunc", (void **) &gload_glStencilFunc },
   { "glStencilFuncSeparate", (void **) &gload_glStencilFuncSeparate },
   { "glStencilMask", (void **) &gload_glStencilMask },
   { "glStencilMaskSeparate", (void **) &gload_glStencilMaskSeparate },
   { "glStencilOp", (void **) &gload_glStencilOp },
   { "glStencilOpSeparate", (void **) &gload_glStencilOpSeparate },
   { "glTexStorage2D", (void **) &gload_glTexStorage2D },
   { "glTexParameterf", (void **) &gload_glTexParameterf },
   { "glTexParameterfv", (void **) &gload_glTexParameterfv },
   { "glTexParameteri", (void **) &gload_glTexParameteri },
   { "glTexParameteriv", (void **) &gload_glTexParameteriv },
   { "glTexSubImage2D", (void **) &gload_glTexSubImage2D },
   { "glUniform1f", (void **) &gload_glUniform1f },
   { "glUniform1fv", (void **) &gload_glUniform1fv },
   { "glUniform1i", (void **) &gload_glUniform1i },
   { "glUniform1iv", (void **) &gload_glUniform1iv },
   { "glUniform2f", (void **) &gload_glUniform2f },
   { "glUniform2fv", (void **) &gload_glUniform2fv },
   { "glUniform2i", (void **) &gload_glUniform2i },
   { "glUniform2iv", (void **) &gload_glUniform2iv },
   { "glUniform3f", (void **) &gload_glUniform3f },
   { "glUniform3fv", (void **) &gload_glUniform3fv },
   { "glUniform3i", (void **) &gload_glUniform3i },
   { "glUniform3iv", (void **) &gload_glUniform3iv },
   { "glUniform4f", (void **) &gload_glUniform4f },
   { "glUniform4fv", (void **) &gload_glUniform4fv },
   { "glUniform4i", (void **) &gload_glUniform4i },
   { "glUniform4iv", (void **) &gload_glUniform4iv },
   { "glUniformMatrix2fv", (void **) &gload_glUniformMatrix2fv },
   { "glUniformMatrix3fv", (void **) &gload_glUniformMatrix3fv },
   { "glUniformMatrix4fv", (void **) &gload_glUniformMatrix4fv },
   { "glUseProgram", (void **) &gload_glUseProgram },
   { "glVertexAttrib1f", (void **) &gload_glVertexAttrib1f },
   { "glVertexAttrib1fv", (void **) &gload_glVertexAttrib1fv },
   { "glVertexAttrib2f", (void **) &gload_glVertexAttrib2f },
   { "glVertexAttrib2fv", (void **) &gload_glVertexAttrib2fv },
   { "glVertexAttrib3f", (void **) &gload_glVertexAttrib3f },
   { "glVertexAttrib3fv", (void **) &gload_glVertexAttrib3fv },
   { "glVertexAttrib4f", (void **) &gload_glVertexAttrib4f },
   { "glVertexAttrib4fv", (void **) &gload_glVertexAttrib4fv },
   { "glVertexAttribPointer", (void **) &gload_glVertexAttribPointer },
   { "glViewport", (void **) &gload_glViewport },

#  endif /* GL_SC_VERSION_2_0 */

    { "", 0 }
};

/* `static void *g_handle` - handle to shared/dynamic library.
 * */
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
 * - return: `true` on success, `false` on failure.
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
 * - returns: `true` on success, `false` on failure.
 * */
GLAPI int   gloadUnloadGL(void) {
    if (g_handle) {

#  if defined (GLOAD_LINUX) || defined (GLOAD_APPLE)
        dlclose(g_handle), g_handle = 0;
#  endif /* GLOAD_LINUX, GLOAD_APPLE */
#  if defined (GLOAD_WIN32)
        FreeLibrary(g_handle), g_handle = 0;
#  endif /* GLOAD_WIN32 */

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
 * - param: `t_gloadLoader load` - pointer to a loader function
 * - return: `true` on success, `false` on failure.
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
 * - param: `const char *name` - name of the symbol
 * - return: address of the symbol on success, null on failure
 * */
GLAPI void  *gloadGetProcAddress(const char *name) {
    void        *proc;
    const char  *names[] = {

#  if defined (GLOAD_LINUX)
        "libGL.so",
        "libGL.so.1",
        "libGL.so.1.7.0",
        0
#  endif /* __linux__ */
#  if defined (GLOAD_APPLE)
        "../Frameworks/OpenGL.framework/OpenGL",
        "/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/OpenGL",
        "/System/Library/Frameworks/OpenGL.framework/Versions/Current/OpenGL"
        0
#  endif /* __APPLE__ */
#  if defined (GLOAD_WIN32)
        "opengl32.dll",
        0
#  endif /* _WIN32 */

    };
    
    if (!g_handle) {
        for (size_t i = 0; !g_handle && names[i]; i++) {

#  if defined (GLOAD_LINUX) || defined (GLOAD_APPLE)
            g_handle = dlopen(names[i], RTLD_NOW | RTLD_GLOBAL);
#  endif /* GLOAD_LINUX, GLOAD_APPLE */
#  if defined (GLOAD_WIN32)
            g_handle = LoadLibraryA(names[i]);
#  endif /* GLOAD_WIN32 */

        }

        if (!g_handle) {

#  if defined (GLOAD_VERBOSE_ERROR)
            fprintf(stderr, "gload.h: could not load an OpenGL handle.\n");
#  endif /* GLOAD_VERBOSE_ERROR */

            return (0);

        }
    }

#  if defined (GLOAD_LINUX) || defined (GLOAD_APPLE)
    proc = dlsym(g_handle, name);
#  endif /* GLOAD_LINUX, GLOAD_APPLE */
#  if defined (GLOAD_WIN32)
    proc = GetProcAddress(g_handle, name);
#  endif /* GLOAD_WIN32 */

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

#  if defined GL_VERSION_1_0

PFNGLCULLFACEPROC gload_glCullFace;
PFNGLFRONTFACEPROC gload_glFrontFace;
PFNGLHINTPROC gload_glHint;
PFNGLLINEWIDTHPROC gload_glLineWidth;
PFNGLPOINTSIZEPROC gload_glPointSize;
PFNGLPOLYGONMODEPROC gload_glPolygonMode;
PFNGLSCISSORPROC gload_glScissor;
PFNGLTEXPARAMETERFPROC gload_glTexParameterf;
PFNGLTEXPARAMETERFVPROC gload_glTexParameterfv;
PFNGLTEXPARAMETERIPROC gload_glTexParameteri;
PFNGLTEXPARAMETERIVPROC gload_glTexParameteriv;
PFNGLTEXIMAGE1DPROC gload_glTexImage1D;
PFNGLTEXIMAGE2DPROC gload_glTexImage2D;
PFNGLDRAWBUFFERPROC gload_glDrawBuffer;
PFNGLCLEARPROC gload_glClear;
PFNGLCLEARCOLORPROC gload_glClearColor;
PFNGLCLEARSTENCILPROC gload_glClearStencil;
PFNGLCLEARDEPTHPROC gload_glClearDepth;
PFNGLSTENCILMASKPROC gload_glStencilMask;
PFNGLCOLORMASKPROC gload_glColorMask;
PFNGLDEPTHMASKPROC gload_glDepthMask;
PFNGLDISABLEPROC gload_glDisable;
PFNGLENABLEPROC gload_glEnable;
PFNGLFINISHPROC gload_glFinish;
PFNGLFLUSHPROC gload_glFlush;
PFNGLBLENDFUNCPROC gload_glBlendFunc;
PFNGLLOGICOPPROC gload_glLogicOp;
PFNGLSTENCILFUNCPROC gload_glStencilFunc;
PFNGLSTENCILOPPROC gload_glStencilOp;
PFNGLDEPTHFUNCPROC gload_glDepthFunc;
PFNGLPIXELSTOREFPROC gload_glPixelStoref;
PFNGLPIXELSTOREIPROC gload_glPixelStorei;
PFNGLREADBUFFERPROC gload_glReadBuffer;
PFNGLREADPIXELSPROC gload_glReadPixels;
PFNGLGETBOOLEANVPROC gload_glGetBooleanv;
PFNGLGETDOUBLEVPROC gload_glGetDoublev;
PFNGLGETERRORPROC gload_glGetError;
PFNGLGETFLOATVPROC gload_glGetFloatv;
PFNGLGETINTEGERVPROC gload_glGetIntegerv;
PFNGLGETSTRINGPROC gload_glGetString;
PFNGLGETTEXIMAGEPROC gload_glGetTexImage;
PFNGLGETTEXPARAMETERFVPROC gload_glGetTexParameterfv;
PFNGLGETTEXPARAMETERIVPROC gload_glGetTexParameteriv;
PFNGLGETTEXLEVELPARAMETERFVPROC gload_glGetTexLevelParameterfv;
PFNGLGETTEXLEVELPARAMETERIVPROC gload_glGetTexLevelParameteriv;
PFNGLISENABLEDPROC gload_glIsEnabled;
PFNGLDEPTHRANGEPROC gload_glDepthRange;
PFNGLVIEWPORTPROC gload_glViewport;
PFNGLNEWLISTPROC gload_glNewList;
PFNGLENDLISTPROC gload_glEndList;
PFNGLCALLLISTPROC gload_glCallList;
PFNGLCALLLISTSPROC gload_glCallLists;
PFNGLDELETELISTSPROC gload_glDeleteLists;
PFNGLGENLISTSPROC gload_glGenLists;
PFNGLLISTBASEPROC gload_glListBase;
PFNGLBEGINPROC gload_glBegin;
PFNGLBITMAPPROC gload_glBitmap;
PFNGLCOLOR3BPROC gload_glColor3b;
PFNGLCOLOR3BVPROC gload_glColor3bv;
PFNGLCOLOR3DPROC gload_glColor3d;
PFNGLCOLOR3DVPROC gload_glColor3dv;
PFNGLCOLOR3FPROC gload_glColor3f;
PFNGLCOLOR3FVPROC gload_glColor3fv;
PFNGLCOLOR3IPROC gload_glColor3i;
PFNGLCOLOR3IVPROC gload_glColor3iv;
PFNGLCOLOR3SPROC gload_glColor3s;
PFNGLCOLOR3SVPROC gload_glColor3sv;
PFNGLCOLOR3UBPROC gload_glColor3ub;
PFNGLCOLOR3UBVPROC gload_glColor3ubv;
PFNGLCOLOR3UIPROC gload_glColor3ui;
PFNGLCOLOR3UIVPROC gload_glColor3uiv;
PFNGLCOLOR3USPROC gload_glColor3us;
PFNGLCOLOR3USVPROC gload_glColor3usv;
PFNGLCOLOR4BPROC gload_glColor4b;
PFNGLCOLOR4BVPROC gload_glColor4bv;
PFNGLCOLOR4DPROC gload_glColor4d;
PFNGLCOLOR4DVPROC gload_glColor4dv;
PFNGLCOLOR4FPROC gload_glColor4f;
PFNGLCOLOR4FVPROC gload_glColor4fv;
PFNGLCOLOR4IPROC gload_glColor4i;
PFNGLCOLOR4IVPROC gload_glColor4iv;
PFNGLCOLOR4SPROC gload_glColor4s;
PFNGLCOLOR4SVPROC gload_glColor4sv;
PFNGLCOLOR4UBPROC gload_glColor4ub;
PFNGLCOLOR4UBVPROC gload_glColor4ubv;
PFNGLCOLOR4UIPROC gload_glColor4ui;
PFNGLCOLOR4UIVPROC gload_glColor4uiv;
PFNGLCOLOR4USPROC gload_glColor4us;
PFNGLCOLOR4USVPROC gload_glColor4usv;
PFNGLEDGEFLAGPROC gload_glEdgeFlag;
PFNGLEDGEFLAGVPROC gload_glEdgeFlagv;
PFNGLENDPROC gload_glEnd;
PFNGLINDEXDPROC gload_glIndexd;
PFNGLINDEXDVPROC gload_glIndexdv;
PFNGLINDEXFPROC gload_glIndexf;
PFNGLINDEXFVPROC gload_glIndexfv;
PFNGLINDEXIPROC gload_glIndexi;
PFNGLINDEXIVPROC gload_glIndexiv;
PFNGLINDEXSPROC gload_glIndexs;
PFNGLINDEXSVPROC gload_glIndexsv;
PFNGLNORMAL3BPROC gload_glNormal3b;
PFNGLNORMAL3BVPROC gload_glNormal3bv;
PFNGLNORMAL3DPROC gload_glNormal3d;
PFNGLNORMAL3DVPROC gload_glNormal3dv;
PFNGLNORMAL3FPROC gload_glNormal3f;
PFNGLNORMAL3FVPROC gload_glNormal3fv;
PFNGLNORMAL3IPROC gload_glNormal3i;
PFNGLNORMAL3IVPROC gload_glNormal3iv;
PFNGLNORMAL3SPROC gload_glNormal3s;
PFNGLNORMAL3SVPROC gload_glNormal3sv;
PFNGLRASTERPOS2DPROC gload_glRasterPos2d;
PFNGLRASTERPOS2DVPROC gload_glRasterPos2dv;
PFNGLRASTERPOS2FPROC gload_glRasterPos2f;
PFNGLRASTERPOS2FVPROC gload_glRasterPos2fv;
PFNGLRASTERPOS2IPROC gload_glRasterPos2i;
PFNGLRASTERPOS2IVPROC gload_glRasterPos2iv;
PFNGLRASTERPOS2SPROC gload_glRasterPos2s;
PFNGLRASTERPOS2SVPROC gload_glRasterPos2sv;
PFNGLRASTERPOS3DPROC gload_glRasterPos3d;
PFNGLRASTERPOS3DVPROC gload_glRasterPos3dv;
PFNGLRASTERPOS3FPROC gload_glRasterPos3f;
PFNGLRASTERPOS3FVPROC gload_glRasterPos3fv;
PFNGLRASTERPOS3IPROC gload_glRasterPos3i;
PFNGLRASTERPOS3IVPROC gload_glRasterPos3iv;
PFNGLRASTERPOS3SPROC gload_glRasterPos3s;
PFNGLRASTERPOS3SVPROC gload_glRasterPos3sv;
PFNGLRASTERPOS4DPROC gload_glRasterPos4d;
PFNGLRASTERPOS4DVPROC gload_glRasterPos4dv;
PFNGLRASTERPOS4FPROC gload_glRasterPos4f;
PFNGLRASTERPOS4FVPROC gload_glRasterPos4fv;
PFNGLRASTERPOS4IPROC gload_glRasterPos4i;
PFNGLRASTERPOS4IVPROC gload_glRasterPos4iv;
PFNGLRASTERPOS4SPROC gload_glRasterPos4s;
PFNGLRASTERPOS4SVPROC gload_glRasterPos4sv;
PFNGLRECTDPROC gload_glRectd;
PFNGLRECTDVPROC gload_glRectdv;
PFNGLRECTFPROC gload_glRectf;
PFNGLRECTFVPROC gload_glRectfv;
PFNGLRECTIPROC gload_glRecti;
PFNGLRECTIVPROC gload_glRectiv;
PFNGLRECTSPROC gload_glRects;
PFNGLRECTSVPROC gload_glRectsv;
PFNGLTEXCOORD1DPROC gload_glTexCoord1d;
PFNGLTEXCOORD1DVPROC gload_glTexCoord1dv;
PFNGLTEXCOORD1FPROC gload_glTexCoord1f;
PFNGLTEXCOORD1FVPROC gload_glTexCoord1fv;
PFNGLTEXCOORD1IPROC gload_glTexCoord1i;
PFNGLTEXCOORD1IVPROC gload_glTexCoord1iv;
PFNGLTEXCOORD1SPROC gload_glTexCoord1s;
PFNGLTEXCOORD1SVPROC gload_glTexCoord1sv;
PFNGLTEXCOORD2DPROC gload_glTexCoord2d;
PFNGLTEXCOORD2DVPROC gload_glTexCoord2dv;
PFNGLTEXCOORD2FPROC gload_glTexCoord2f;
PFNGLTEXCOORD2FVPROC gload_glTexCoord2fv;
PFNGLTEXCOORD2IPROC gload_glTexCoord2i;
PFNGLTEXCOORD2IVPROC gload_glTexCoord2iv;
PFNGLTEXCOORD2SPROC gload_glTexCoord2s;
PFNGLTEXCOORD2SVPROC gload_glTexCoord2sv;
PFNGLTEXCOORD3DPROC gload_glTexCoord3d;
PFNGLTEXCOORD3DVPROC gload_glTexCoord3dv;
PFNGLTEXCOORD3FPROC gload_glTexCoord3f;
PFNGLTEXCOORD3FVPROC gload_glTexCoord3fv;
PFNGLTEXCOORD3IPROC gload_glTexCoord3i;
PFNGLTEXCOORD3IVPROC gload_glTexCoord3iv;
PFNGLTEXCOORD3SPROC gload_glTexCoord3s;
PFNGLTEXCOORD3SVPROC gload_glTexCoord3sv;
PFNGLTEXCOORD4DPROC gload_glTexCoord4d;
PFNGLTEXCOORD4DVPROC gload_glTexCoord4dv;
PFNGLTEXCOORD4FPROC gload_glTexCoord4f;
PFNGLTEXCOORD4FVPROC gload_glTexCoord4fv;
PFNGLTEXCOORD4IPROC gload_glTexCoord4i;
PFNGLTEXCOORD4IVPROC gload_glTexCoord4iv;
PFNGLTEXCOORD4SPROC gload_glTexCoord4s;
PFNGLTEXCOORD4SVPROC gload_glTexCoord4sv;
PFNGLVERTEX2DPROC gload_glVertex2d;
PFNGLVERTEX2DVPROC gload_glVertex2dv;
PFNGLVERTEX2FPROC gload_glVertex2f;
PFNGLVERTEX2FVPROC gload_glVertex2fv;
PFNGLVERTEX2IPROC gload_glVertex2i;
PFNGLVERTEX2IVPROC gload_glVertex2iv;
PFNGLVERTEX2SPROC gload_glVertex2s;
PFNGLVERTEX2SVPROC gload_glVertex2sv;
PFNGLVERTEX3DPROC gload_glVertex3d;
PFNGLVERTEX3DVPROC gload_glVertex3dv;
PFNGLVERTEX3FPROC gload_glVertex3f;
PFNGLVERTEX3FVPROC gload_glVertex3fv;
PFNGLVERTEX3IPROC gload_glVertex3i;
PFNGLVERTEX3IVPROC gload_glVertex3iv;
PFNGLVERTEX3SPROC gload_glVertex3s;
PFNGLVERTEX3SVPROC gload_glVertex3sv;
PFNGLVERTEX4DPROC gload_glVertex4d;
PFNGLVERTEX4DVPROC gload_glVertex4dv;
PFNGLVERTEX4FPROC gload_glVertex4f;
PFNGLVERTEX4FVPROC gload_glVertex4fv;
PFNGLVERTEX4IPROC gload_glVertex4i;
PFNGLVERTEX4IVPROC gload_glVertex4iv;
PFNGLVERTEX4SPROC gload_glVertex4s;
PFNGLVERTEX4SVPROC gload_glVertex4sv;
PFNGLCLIPPLANEPROC gload_glClipPlane;
PFNGLCOLORMATERIALPROC gload_glColorMaterial;
PFNGLFOGFPROC gload_glFogf;
PFNGLFOGFVPROC gload_glFogfv;
PFNGLFOGIPROC gload_glFogi;
PFNGLFOGIVPROC gload_glFogiv;
PFNGLLIGHTFPROC gload_glLightf;
PFNGLLIGHTFVPROC gload_glLightfv;
PFNGLLIGHTIPROC gload_glLighti;
PFNGLLIGHTIVPROC gload_glLightiv;
PFNGLLIGHTMODELFPROC gload_glLightModelf;
PFNGLLIGHTMODELFVPROC gload_glLightModelfv;
PFNGLLIGHTMODELIPROC gload_glLightModeli;
PFNGLLIGHTMODELIVPROC gload_glLightModeliv;
PFNGLLINESTIPPLEPROC gload_glLineStipple;
PFNGLMATERIALFPROC gload_glMaterialf;
PFNGLMATERIALFVPROC gload_glMaterialfv;
PFNGLMATERIALIPROC gload_glMateriali;
PFNGLMATERIALIVPROC gload_glMaterialiv;
PFNGLPOLYGONSTIPPLEPROC gload_glPolygonStipple;
PFNGLSHADEMODELPROC gload_glShadeModel;
PFNGLTEXENVFPROC gload_glTexEnvf;
PFNGLTEXENVFVPROC gload_glTexEnvfv;
PFNGLTEXENVIPROC gload_glTexEnvi;
PFNGLTEXENVIVPROC gload_glTexEnviv;
PFNGLTEXGENDPROC gload_glTexGend;
PFNGLTEXGENDVPROC gload_glTexGendv;
PFNGLTEXGENFPROC gload_glTexGenf;
PFNGLTEXGENFVPROC gload_glTexGenfv;
PFNGLTEXGENIPROC gload_glTexGeni;
PFNGLTEXGENIVPROC gload_glTexGeniv;
PFNGLFEEDBACKBUFFERPROC gload_glFeedbackBuffer;
PFNGLSELECTBUFFERPROC gload_glSelectBuffer;
PFNGLRENDERMODEPROC gload_glRenderMode;
PFNGLINITNAMESPROC gload_glInitNames;
PFNGLLOADNAMEPROC gload_glLoadName;
PFNGLPASSTHROUGHPROC gload_glPassThrough;
PFNGLPOPNAMEPROC gload_glPopName;
PFNGLPUSHNAMEPROC gload_glPushName;
PFNGLCLEARACCUMPROC gload_glClearAccum;
PFNGLCLEARINDEXPROC gload_glClearIndex;
PFNGLINDEXMASKPROC gload_glIndexMask;
PFNGLACCUMPROC gload_glAccum;
PFNGLPOPATTRIBPROC gload_glPopAttrib;
PFNGLPUSHATTRIBPROC gload_glPushAttrib;
PFNGLMAP1DPROC gload_glMap1d;
PFNGLMAP1FPROC gload_glMap1f;
PFNGLMAP2DPROC gload_glMap2d;
PFNGLMAP2FPROC gload_glMap2f;
PFNGLMAPGRID1DPROC gload_glMapGrid1d;
PFNGLMAPGRID1FPROC gload_glMapGrid1f;
PFNGLMAPGRID2DPROC gload_glMapGrid2d;
PFNGLMAPGRID2FPROC gload_glMapGrid2f;
PFNGLEVALCOORD1DPROC gload_glEvalCoord1d;
PFNGLEVALCOORD1DVPROC gload_glEvalCoord1dv;
PFNGLEVALCOORD1FPROC gload_glEvalCoord1f;
PFNGLEVALCOORD1FVPROC gload_glEvalCoord1fv;
PFNGLEVALCOORD2DPROC gload_glEvalCoord2d;
PFNGLEVALCOORD2DVPROC gload_glEvalCoord2dv;
PFNGLEVALCOORD2FPROC gload_glEvalCoord2f;
PFNGLEVALCOORD2FVPROC gload_glEvalCoord2fv;
PFNGLEVALMESH1PROC gload_glEvalMesh1;
PFNGLEVALPOINT1PROC gload_glEvalPoint1;
PFNGLEVALMESH2PROC gload_glEvalMesh2;
PFNGLEVALPOINT2PROC gload_glEvalPoint2;
PFNGLALPHAFUNCPROC gload_glAlphaFunc;
PFNGLPIXELZOOMPROC gload_glPixelZoom;
PFNGLPIXELTRANSFERFPROC gload_glPixelTransferf;
PFNGLPIXELTRANSFERIPROC gload_glPixelTransferi;
PFNGLPIXELMAPFVPROC gload_glPixelMapfv;
PFNGLPIXELMAPUIVPROC gload_glPixelMapuiv;
PFNGLPIXELMAPUSVPROC gload_glPixelMapusv;
PFNGLCOPYPIXELSPROC gload_glCopyPixels;
PFNGLDRAWPIXELSPROC gload_glDrawPixels;
PFNGLGETCLIPPLANEPROC gload_glGetClipPlane;
PFNGLGETLIGHTFVPROC gload_glGetLightfv;
PFNGLGETLIGHTIVPROC gload_glGetLightiv;
PFNGLGETMAPDVPROC gload_glGetMapdv;
PFNGLGETMAPFVPROC gload_glGetMapfv;
PFNGLGETMAPIVPROC gload_glGetMapiv;
PFNGLGETMATERIALFVPROC gload_glGetMaterialfv;
PFNGLGETMATERIALIVPROC gload_glGetMaterialiv;
PFNGLGETPIXELMAPFVPROC gload_glGetPixelMapfv;
PFNGLGETPIXELMAPUIVPROC gload_glGetPixelMapuiv;
PFNGLGETPIXELMAPUSVPROC gload_glGetPixelMapusv;
PFNGLGETPOLYGONSTIPPLEPROC gload_glGetPolygonStipple;
PFNGLGETTEXENVFVPROC gload_glGetTexEnvfv;
PFNGLGETTEXENVIVPROC gload_glGetTexEnviv;
PFNGLGETTEXGENDVPROC gload_glGetTexGendv;
PFNGLGETTEXGENFVPROC gload_glGetTexGenfv;
PFNGLGETTEXGENIVPROC gload_glGetTexGeniv;
PFNGLISLISTPROC gload_glIsList;
PFNGLFRUSTUMPROC gload_glFrustum;
PFNGLLOADIDENTITYPROC gload_glLoadIdentity;
PFNGLLOADMATRIXFPROC gload_glLoadMatrixf;
PFNGLLOADMATRIXDPROC gload_glLoadMatrixd;
PFNGLMATRIXMODEPROC gload_glMatrixMode;
PFNGLMULTMATRIXFPROC gload_glMultMatrixf;
PFNGLMULTMATRIXDPROC gload_glMultMatrixd;
PFNGLORTHOPROC gload_glOrtho;
PFNGLPOPMATRIXPROC gload_glPopMatrix;
PFNGLPUSHMATRIXPROC gload_glPushMatrix;
PFNGLROTATEDPROC gload_glRotated;
PFNGLROTATEFPROC gload_glRotatef;
PFNGLSCALEDPROC gload_glScaled;
PFNGLSCALEFPROC gload_glScalef;
PFNGLTRANSLATEDPROC gload_glTranslated;
PFNGLTRANSLATEFPROC gload_glTranslatef;

#  endif /* GL_VERSION_1_0 */
#  if defined GL_VERSION_1_1

PFNGLDRAWARRAYSPROC gload_glDrawArrays;
PFNGLDRAWELEMENTSPROC gload_glDrawElements;
PFNGLGETPOINTERVPROC gload_glGetPointerv;
PFNGLPOLYGONOFFSETPROC gload_glPolygonOffset;
PFNGLCOPYTEXIMAGE1DPROC gload_glCopyTexImage1D;
PFNGLCOPYTEXIMAGE2DPROC gload_glCopyTexImage2D;
PFNGLCOPYTEXSUBIMAGE1DPROC gload_glCopyTexSubImage1D;
PFNGLCOPYTEXSUBIMAGE2DPROC gload_glCopyTexSubImage2D;
PFNGLTEXSUBIMAGE1DPROC gload_glTexSubImage1D;
PFNGLTEXSUBIMAGE2DPROC gload_glTexSubImage2D;
PFNGLBINDTEXTUREPROC gload_glBindTexture;
PFNGLDELETETEXTURESPROC gload_glDeleteTextures;
PFNGLGENTEXTURESPROC gload_glGenTextures;
PFNGLISTEXTUREPROC gload_glIsTexture;
PFNGLARRAYELEMENTPROC gload_glArrayElement;
PFNGLCOLORPOINTERPROC gload_glColorPointer;
PFNGLDISABLECLIENTSTATEPROC gload_glDisableClientState;
PFNGLEDGEFLAGPOINTERPROC gload_glEdgeFlagPointer;
PFNGLENABLECLIENTSTATEPROC gload_glEnableClientState;
PFNGLINDEXPOINTERPROC gload_glIndexPointer;
PFNGLINTERLEAVEDARRAYSPROC gload_glInterleavedArrays;
PFNGLNORMALPOINTERPROC gload_glNormalPointer;
PFNGLTEXCOORDPOINTERPROC gload_glTexCoordPointer;
PFNGLVERTEXPOINTERPROC gload_glVertexPointer;
PFNGLARETEXTURESRESIDENTPROC gload_glAreTexturesResident;
PFNGLPRIORITIZETEXTURESPROC gload_glPrioritizeTextures;
PFNGLINDEXUBPROC gload_glIndexub;
PFNGLINDEXUBVPROC gload_glIndexubv;
PFNGLPOPCLIENTATTRIBPROC gload_glPopClientAttrib;
PFNGLPUSHCLIENTATTRIBPROC gload_glPushClientAttrib;

#  endif /* GL_VERSION_1_1 */
#  if defined GL_VERSION_1_2

PFNGLDRAWRANGEELEMENTSPROC gload_glDrawRangeElements;
PFNGLTEXIMAGE3DPROC gload_glTexImage3D;
PFNGLTEXSUBIMAGE3DPROC gload_glTexSubImage3D;
PFNGLCOPYTEXSUBIMAGE3DPROC gload_glCopyTexSubImage3D;

#  endif /* GL_VERSION_1_2 */
#  if defined GL_VERSION_1_3

PFNGLACTIVETEXTUREPROC gload_glActiveTexture;
PFNGLSAMPLECOVERAGEPROC gload_glSampleCoverage;
PFNGLCOMPRESSEDTEXIMAGE3DPROC gload_glCompressedTexImage3D;
PFNGLCOMPRESSEDTEXIMAGE2DPROC gload_glCompressedTexImage2D;
PFNGLCOMPRESSEDTEXIMAGE1DPROC gload_glCompressedTexImage1D;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC gload_glCompressedTexSubImage3D;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC gload_glCompressedTexSubImage2D;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC gload_glCompressedTexSubImage1D;
PFNGLGETCOMPRESSEDTEXIMAGEPROC gload_glGetCompressedTexImage;
PFNGLCLIENTACTIVETEXTUREPROC gload_glClientActiveTexture;
PFNGLMULTITEXCOORD1DPROC gload_glMultiTexCoord1d;
PFNGLMULTITEXCOORD1DVPROC gload_glMultiTexCoord1dv;
PFNGLMULTITEXCOORD1FPROC gload_glMultiTexCoord1f;
PFNGLMULTITEXCOORD1FVPROC gload_glMultiTexCoord1fv;
PFNGLMULTITEXCOORD1IPROC gload_glMultiTexCoord1i;
PFNGLMULTITEXCOORD1IVPROC gload_glMultiTexCoord1iv;
PFNGLMULTITEXCOORD1SPROC gload_glMultiTexCoord1s;
PFNGLMULTITEXCOORD1SVPROC gload_glMultiTexCoord1sv;
PFNGLMULTITEXCOORD2DPROC gload_glMultiTexCoord2d;
PFNGLMULTITEXCOORD2DVPROC gload_glMultiTexCoord2dv;
PFNGLMULTITEXCOORD2FPROC gload_glMultiTexCoord2f;
PFNGLMULTITEXCOORD2FVPROC gload_glMultiTexCoord2fv;
PFNGLMULTITEXCOORD2IPROC gload_glMultiTexCoord2i;
PFNGLMULTITEXCOORD2IVPROC gload_glMultiTexCoord2iv;
PFNGLMULTITEXCOORD2SPROC gload_glMultiTexCoord2s;
PFNGLMULTITEXCOORD2SVPROC gload_glMultiTexCoord2sv;
PFNGLMULTITEXCOORD3DPROC gload_glMultiTexCoord3d;
PFNGLMULTITEXCOORD3DVPROC gload_glMultiTexCoord3dv;
PFNGLMULTITEXCOORD3FPROC gload_glMultiTexCoord3f;
PFNGLMULTITEXCOORD3FVPROC gload_glMultiTexCoord3fv;
PFNGLMULTITEXCOORD3IPROC gload_glMultiTexCoord3i;
PFNGLMULTITEXCOORD3IVPROC gload_glMultiTexCoord3iv;
PFNGLMULTITEXCOORD3SPROC gload_glMultiTexCoord3s;
PFNGLMULTITEXCOORD3SVPROC gload_glMultiTexCoord3sv;
PFNGLMULTITEXCOORD4DPROC gload_glMultiTexCoord4d;
PFNGLMULTITEXCOORD4DVPROC gload_glMultiTexCoord4dv;
PFNGLMULTITEXCOORD4FPROC gload_glMultiTexCoord4f;
PFNGLMULTITEXCOORD4FVPROC gload_glMultiTexCoord4fv;
PFNGLMULTITEXCOORD4IPROC gload_glMultiTexCoord4i;
PFNGLMULTITEXCOORD4IVPROC gload_glMultiTexCoord4iv;
PFNGLMULTITEXCOORD4SPROC gload_glMultiTexCoord4s;
PFNGLMULTITEXCOORD4SVPROC gload_glMultiTexCoord4sv;
PFNGLLOADTRANSPOSEMATRIXFPROC gload_glLoadTransposeMatrixf;
PFNGLLOADTRANSPOSEMATRIXDPROC gload_glLoadTransposeMatrixd;
PFNGLMULTTRANSPOSEMATRIXFPROC gload_glMultTransposeMatrixf;
PFNGLMULTTRANSPOSEMATRIXDPROC gload_glMultTransposeMatrixd;

#  endif /* GL_VERSION_1_3 */
#  if defined GL_VERSION_1_4

PFNGLBLENDFUNCSEPARATEPROC gload_glBlendFuncSeparate;
PFNGLMULTIDRAWARRAYSPROC gload_glMultiDrawArrays;
PFNGLMULTIDRAWELEMENTSPROC gload_glMultiDrawElements;
PFNGLPOINTPARAMETERFPROC gload_glPointParameterf;
PFNGLPOINTPARAMETERFVPROC gload_glPointParameterfv;
PFNGLPOINTPARAMETERIPROC gload_glPointParameteri;
PFNGLPOINTPARAMETERIVPROC gload_glPointParameteriv;
PFNGLFOGCOORDFPROC gload_glFogCoordf;
PFNGLFOGCOORDFVPROC gload_glFogCoordfv;
PFNGLFOGCOORDDPROC gload_glFogCoordd;
PFNGLFOGCOORDDVPROC gload_glFogCoorddv;
PFNGLFOGCOORDPOINTERPROC gload_glFogCoordPointer;
PFNGLSECONDARYCOLOR3BPROC gload_glSecondaryColor3b;
PFNGLSECONDARYCOLOR3BVPROC gload_glSecondaryColor3bv;
PFNGLSECONDARYCOLOR3DPROC gload_glSecondaryColor3d;
PFNGLSECONDARYCOLOR3DVPROC gload_glSecondaryColor3dv;
PFNGLSECONDARYCOLOR3FPROC gload_glSecondaryColor3f;
PFNGLSECONDARYCOLOR3FVPROC gload_glSecondaryColor3fv;
PFNGLSECONDARYCOLOR3IPROC gload_glSecondaryColor3i;
PFNGLSECONDARYCOLOR3IVPROC gload_glSecondaryColor3iv;
PFNGLSECONDARYCOLOR3SPROC gload_glSecondaryColor3s;
PFNGLSECONDARYCOLOR3SVPROC gload_glSecondaryColor3sv;
PFNGLSECONDARYCOLOR3UBPROC gload_glSecondaryColor3ub;
PFNGLSECONDARYCOLOR3UBVPROC gload_glSecondaryColor3ubv;
PFNGLSECONDARYCOLOR3UIPROC gload_glSecondaryColor3ui;
PFNGLSECONDARYCOLOR3UIVPROC gload_glSecondaryColor3uiv;
PFNGLSECONDARYCOLOR3USPROC gload_glSecondaryColor3us;
PFNGLSECONDARYCOLOR3USVPROC gload_glSecondaryColor3usv;
PFNGLSECONDARYCOLORPOINTERPROC gload_glSecondaryColorPointer;
PFNGLWINDOWPOS2DPROC gload_glWindowPos2d;
PFNGLWINDOWPOS2DVPROC gload_glWindowPos2dv;
PFNGLWINDOWPOS2FPROC gload_glWindowPos2f;
PFNGLWINDOWPOS2FVPROC gload_glWindowPos2fv;
PFNGLWINDOWPOS2IPROC gload_glWindowPos2i;
PFNGLWINDOWPOS2IVPROC gload_glWindowPos2iv;
PFNGLWINDOWPOS2SPROC gload_glWindowPos2s;
PFNGLWINDOWPOS2SVPROC gload_glWindowPos2sv;
PFNGLWINDOWPOS3DPROC gload_glWindowPos3d;
PFNGLWINDOWPOS3DVPROC gload_glWindowPos3dv;
PFNGLWINDOWPOS3FPROC gload_glWindowPos3f;
PFNGLWINDOWPOS3FVPROC gload_glWindowPos3fv;
PFNGLWINDOWPOS3IPROC gload_glWindowPos3i;
PFNGLWINDOWPOS3IVPROC gload_glWindowPos3iv;
PFNGLWINDOWPOS3SPROC gload_glWindowPos3s;
PFNGLWINDOWPOS3SVPROC gload_glWindowPos3sv;
PFNGLBLENDCOLORPROC gload_glBlendColor;
PFNGLBLENDEQUATIONPROC gload_glBlendEquation;

#  endif /* GL_VERSION_1_4 */
#  if defined GL_VERSION_1_5

PFNGLGENQUERIESPROC gload_glGenQueries;
PFNGLDELETEQUERIESPROC gload_glDeleteQueries;
PFNGLISQUERYPROC gload_glIsQuery;
PFNGLBEGINQUERYPROC gload_glBeginQuery;
PFNGLENDQUERYPROC gload_glEndQuery;
PFNGLGETQUERYIVPROC gload_glGetQueryiv;
PFNGLGETQUERYOBJECTIVPROC gload_glGetQueryObjectiv;
PFNGLGETQUERYOBJECTUIVPROC gload_glGetQueryObjectuiv;
PFNGLBINDBUFFERPROC gload_glBindBuffer;
PFNGLDELETEBUFFERSPROC gload_glDeleteBuffers;
PFNGLGENBUFFERSPROC gload_glGenBuffers;
PFNGLISBUFFERPROC gload_glIsBuffer;
PFNGLBUFFERDATAPROC gload_glBufferData;
PFNGLBUFFERSUBDATAPROC gload_glBufferSubData;
PFNGLGETBUFFERSUBDATAPROC gload_glGetBufferSubData;
PFNGLMAPBUFFERPROC gload_glMapBuffer;
PFNGLUNMAPBUFFERPROC gload_glUnmapBuffer;
PFNGLGETBUFFERPARAMETERIVPROC gload_glGetBufferParameteriv;
PFNGLGETBUFFERPOINTERVPROC gload_glGetBufferPointerv;

#  endif /* GL_VERSION_1_5 */
#  if defined GL_VERSION_2_0

PFNGLBLENDEQUATIONSEPARATEPROC gload_glBlendEquationSeparate;
PFNGLDRAWBUFFERSPROC gload_glDrawBuffers;
PFNGLSTENCILOPSEPARATEPROC gload_glStencilOpSeparate;
PFNGLSTENCILFUNCSEPARATEPROC gload_glStencilFuncSeparate;
PFNGLSTENCILMASKSEPARATEPROC gload_glStencilMaskSeparate;
PFNGLATTACHSHADERPROC gload_glAttachShader;
PFNGLBINDATTRIBLOCATIONPROC gload_glBindAttribLocation;
PFNGLCOMPILESHADERPROC gload_glCompileShader;
PFNGLCREATEPROGRAMPROC gload_glCreateProgram;
PFNGLCREATESHADERPROC gload_glCreateShader;
PFNGLDELETEPROGRAMPROC gload_glDeleteProgram;
PFNGLDELETESHADERPROC gload_glDeleteShader;
PFNGLDETACHSHADERPROC gload_glDetachShader;
PFNGLDISABLEVERTEXATTRIBARRAYPROC gload_glDisableVertexAttribArray;
PFNGLENABLEVERTEXATTRIBARRAYPROC gload_glEnableVertexAttribArray;
PFNGLGETACTIVEATTRIBPROC gload_glGetActiveAttrib;
PFNGLGETACTIVEUNIFORMPROC gload_glGetActiveUniform;
PFNGLGETATTACHEDSHADERSPROC gload_glGetAttachedShaders;
PFNGLGETATTRIBLOCATIONPROC gload_glGetAttribLocation;
PFNGLGETPROGRAMIVPROC gload_glGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC gload_glGetProgramInfoLog;
PFNGLGETSHADERIVPROC gload_glGetShaderiv;
PFNGLGETSHADERINFOLOGPROC gload_glGetShaderInfoLog;
PFNGLGETSHADERSOURCEPROC gload_glGetShaderSource;
PFNGLGETUNIFORMLOCATIONPROC gload_glGetUniformLocation;
PFNGLGETUNIFORMFVPROC gload_glGetUniformfv;
PFNGLGETUNIFORMIVPROC gload_glGetUniformiv;
PFNGLGETVERTEXATTRIBDVPROC gload_glGetVertexAttribdv;
PFNGLGETVERTEXATTRIBFVPROC gload_glGetVertexAttribfv;
PFNGLGETVERTEXATTRIBIVPROC gload_glGetVertexAttribiv;
PFNGLGETVERTEXATTRIBPOINTERVPROC gload_glGetVertexAttribPointerv;
PFNGLISPROGRAMPROC gload_glIsProgram;
PFNGLISSHADERPROC gload_glIsShader;
PFNGLLINKPROGRAMPROC gload_glLinkProgram;
PFNGLSHADERSOURCEPROC gload_glShaderSource;
PFNGLUSEPROGRAMPROC gload_glUseProgram;
PFNGLUNIFORM1FPROC gload_glUniform1f;
PFNGLUNIFORM2FPROC gload_glUniform2f;
PFNGLUNIFORM3FPROC gload_glUniform3f;
PFNGLUNIFORM4FPROC gload_glUniform4f;
PFNGLUNIFORM1IPROC gload_glUniform1i;
PFNGLUNIFORM2IPROC gload_glUniform2i;
PFNGLUNIFORM3IPROC gload_glUniform3i;
PFNGLUNIFORM4IPROC gload_glUniform4i;
PFNGLUNIFORM1FVPROC gload_glUniform1fv;
PFNGLUNIFORM2FVPROC gload_glUniform2fv;
PFNGLUNIFORM3FVPROC gload_glUniform3fv;
PFNGLUNIFORM4FVPROC gload_glUniform4fv;
PFNGLUNIFORM1IVPROC gload_glUniform1iv;
PFNGLUNIFORM2IVPROC gload_glUniform2iv;
PFNGLUNIFORM3IVPROC gload_glUniform3iv;
PFNGLUNIFORM4IVPROC gload_glUniform4iv;
PFNGLUNIFORMMATRIX2FVPROC gload_glUniformMatrix2fv;
PFNGLUNIFORMMATRIX3FVPROC gload_glUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC gload_glUniformMatrix4fv;
PFNGLVALIDATEPROGRAMPROC gload_glValidateProgram;
PFNGLVERTEXATTRIB1DPROC gload_glVertexAttrib1d;
PFNGLVERTEXATTRIB1DVPROC gload_glVertexAttrib1dv;
PFNGLVERTEXATTRIB1FPROC gload_glVertexAttrib1f;
PFNGLVERTEXATTRIB1FVPROC gload_glVertexAttrib1fv;
PFNGLVERTEXATTRIB1SPROC gload_glVertexAttrib1s;
PFNGLVERTEXATTRIB1SVPROC gload_glVertexAttrib1sv;
PFNGLVERTEXATTRIB2DPROC gload_glVertexAttrib2d;
PFNGLVERTEXATTRIB2DVPROC gload_glVertexAttrib2dv;
PFNGLVERTEXATTRIB2FPROC gload_glVertexAttrib2f;
PFNGLVERTEXATTRIB2FVPROC gload_glVertexAttrib2fv;
PFNGLVERTEXATTRIB2SPROC gload_glVertexAttrib2s;
PFNGLVERTEXATTRIB2SVPROC gload_glVertexAttrib2sv;
PFNGLVERTEXATTRIB3DPROC gload_glVertexAttrib3d;
PFNGLVERTEXATTRIB3DVPROC gload_glVertexAttrib3dv;
PFNGLVERTEXATTRIB3FPROC gload_glVertexAttrib3f;
PFNGLVERTEXATTRIB3FVPROC gload_glVertexAttrib3fv;
PFNGLVERTEXATTRIB3SPROC gload_glVertexAttrib3s;
PFNGLVERTEXATTRIB3SVPROC gload_glVertexAttrib3sv;
PFNGLVERTEXATTRIB4NBVPROC gload_glVertexAttrib4Nbv;
PFNGLVERTEXATTRIB4NIVPROC gload_glVertexAttrib4Niv;
PFNGLVERTEXATTRIB4NSVPROC gload_glVertexAttrib4Nsv;
PFNGLVERTEXATTRIB4NUBPROC gload_glVertexAttrib4Nub;
PFNGLVERTEXATTRIB4NUBVPROC gload_glVertexAttrib4Nubv;
PFNGLVERTEXATTRIB4NUIVPROC gload_glVertexAttrib4Nuiv;
PFNGLVERTEXATTRIB4NUSVPROC gload_glVertexAttrib4Nusv;
PFNGLVERTEXATTRIB4BVPROC gload_glVertexAttrib4bv;
PFNGLVERTEXATTRIB4DPROC gload_glVertexAttrib4d;
PFNGLVERTEXATTRIB4DVPROC gload_glVertexAttrib4dv;
PFNGLVERTEXATTRIB4FPROC gload_glVertexAttrib4f;
PFNGLVERTEXATTRIB4FVPROC gload_glVertexAttrib4fv;
PFNGLVERTEXATTRIB4IVPROC gload_glVertexAttrib4iv;
PFNGLVERTEXATTRIB4SPROC gload_glVertexAttrib4s;
PFNGLVERTEXATTRIB4SVPROC gload_glVertexAttrib4sv;
PFNGLVERTEXATTRIB4UBVPROC gload_glVertexAttrib4ubv;
PFNGLVERTEXATTRIB4UIVPROC gload_glVertexAttrib4uiv;
PFNGLVERTEXATTRIB4USVPROC gload_glVertexAttrib4usv;
PFNGLVERTEXATTRIBPOINTERPROC gload_glVertexAttribPointer;

#  endif /* GL_VERSION_2_0 */
#  if defined GL_VERSION_2_1

PFNGLUNIFORMMATRIX2X3FVPROC gload_glUniformMatrix2x3fv;
PFNGLUNIFORMMATRIX3X2FVPROC gload_glUniformMatrix3x2fv;
PFNGLUNIFORMMATRIX2X4FVPROC gload_glUniformMatrix2x4fv;
PFNGLUNIFORMMATRIX4X2FVPROC gload_glUniformMatrix4x2fv;
PFNGLUNIFORMMATRIX3X4FVPROC gload_glUniformMatrix3x4fv;
PFNGLUNIFORMMATRIX4X3FVPROC gload_glUniformMatrix4x3fv;

#  endif /* GL_VERSION_2_1 */
#  if defined GL_VERSION_3_0

PFNGLCOLORMASKIPROC gload_glColorMaski;
PFNGLGETBOOLEANI_VPROC gload_glGetBooleani_v;
PFNGLGETINTEGERI_VPROC gload_glGetIntegeri_v;
PFNGLENABLEIPROC gload_glEnablei;
PFNGLDISABLEIPROC gload_glDisablei;
PFNGLISENABLEDIPROC gload_glIsEnabledi;
PFNGLBEGINTRANSFORMFEEDBACKPROC gload_glBeginTransformFeedback;
PFNGLENDTRANSFORMFEEDBACKPROC gload_glEndTransformFeedback;
PFNGLBINDBUFFERRANGEPROC gload_glBindBufferRange;
PFNGLBINDBUFFERBASEPROC gload_glBindBufferBase;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC gload_glTransformFeedbackVaryings;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC gload_glGetTransformFeedbackVarying;
PFNGLCLAMPCOLORPROC gload_glClampColor;
PFNGLBEGINCONDITIONALRENDERPROC gload_glBeginConditionalRender;
PFNGLENDCONDITIONALRENDERPROC gload_glEndConditionalRender;
PFNGLVERTEXATTRIBIPOINTERPROC gload_glVertexAttribIPointer;
PFNGLGETVERTEXATTRIBIIVPROC gload_glGetVertexAttribIiv;
PFNGLGETVERTEXATTRIBIUIVPROC gload_glGetVertexAttribIuiv;
PFNGLVERTEXATTRIBI1IPROC gload_glVertexAttribI1i;
PFNGLVERTEXATTRIBI2IPROC gload_glVertexAttribI2i;
PFNGLVERTEXATTRIBI3IPROC gload_glVertexAttribI3i;
PFNGLVERTEXATTRIBI4IPROC gload_glVertexAttribI4i;
PFNGLVERTEXATTRIBI1UIPROC gload_glVertexAttribI1ui;
PFNGLVERTEXATTRIBI2UIPROC gload_glVertexAttribI2ui;
PFNGLVERTEXATTRIBI3UIPROC gload_glVertexAttribI3ui;
PFNGLVERTEXATTRIBI4UIPROC gload_glVertexAttribI4ui;
PFNGLVERTEXATTRIBI1IVPROC gload_glVertexAttribI1iv;
PFNGLVERTEXATTRIBI2IVPROC gload_glVertexAttribI2iv;
PFNGLVERTEXATTRIBI3IVPROC gload_glVertexAttribI3iv;
PFNGLVERTEXATTRIBI4IVPROC gload_glVertexAttribI4iv;
PFNGLVERTEXATTRIBI1UIVPROC gload_glVertexAttribI1uiv;
PFNGLVERTEXATTRIBI2UIVPROC gload_glVertexAttribI2uiv;
PFNGLVERTEXATTRIBI3UIVPROC gload_glVertexAttribI3uiv;
PFNGLVERTEXATTRIBI4UIVPROC gload_glVertexAttribI4uiv;
PFNGLVERTEXATTRIBI4BVPROC gload_glVertexAttribI4bv;
PFNGLVERTEXATTRIBI4SVPROC gload_glVertexAttribI4sv;
PFNGLVERTEXATTRIBI4UBVPROC gload_glVertexAttribI4ubv;
PFNGLVERTEXATTRIBI4USVPROC gload_glVertexAttribI4usv;
PFNGLGETUNIFORMUIVPROC gload_glGetUniformuiv;
PFNGLBINDFRAGDATALOCATIONPROC gload_glBindFragDataLocation;
PFNGLGETFRAGDATALOCATIONPROC gload_glGetFragDataLocation;
PFNGLUNIFORM1UIPROC gload_glUniform1ui;
PFNGLUNIFORM2UIPROC gload_glUniform2ui;
PFNGLUNIFORM3UIPROC gload_glUniform3ui;
PFNGLUNIFORM4UIPROC gload_glUniform4ui;
PFNGLUNIFORM1UIVPROC gload_glUniform1uiv;
PFNGLUNIFORM2UIVPROC gload_glUniform2uiv;
PFNGLUNIFORM3UIVPROC gload_glUniform3uiv;
PFNGLUNIFORM4UIVPROC gload_glUniform4uiv;
PFNGLTEXPARAMETERIIVPROC gload_glTexParameterIiv;
PFNGLTEXPARAMETERIUIVPROC gload_glTexParameterIuiv;
PFNGLGETTEXPARAMETERIIVPROC gload_glGetTexParameterIiv;
PFNGLGETTEXPARAMETERIUIVPROC gload_glGetTexParameterIuiv;
PFNGLCLEARBUFFERIVPROC gload_glClearBufferiv;
PFNGLCLEARBUFFERUIVPROC gload_glClearBufferuiv;
PFNGLCLEARBUFFERFVPROC gload_glClearBufferfv;
PFNGLCLEARBUFFERFIPROC gload_glClearBufferfi;
PFNGLGETSTRINGIPROC gload_glGetStringi;
PFNGLISRENDERBUFFERPROC gload_glIsRenderbuffer;
PFNGLBINDRENDERBUFFERPROC gload_glBindRenderbuffer;
PFNGLDELETERENDERBUFFERSPROC gload_glDeleteRenderbuffers;
PFNGLGENRENDERBUFFERSPROC gload_glGenRenderbuffers;
PFNGLRENDERBUFFERSTORAGEPROC gload_glRenderbufferStorage;
PFNGLGETRENDERBUFFERPARAMETERIVPROC gload_glGetRenderbufferParameteriv;
PFNGLISFRAMEBUFFERPROC gload_glIsFramebuffer;
PFNGLBINDFRAMEBUFFERPROC gload_glBindFramebuffer;
PFNGLDELETEFRAMEBUFFERSPROC gload_glDeleteFramebuffers;
PFNGLGENFRAMEBUFFERSPROC gload_glGenFramebuffers;
PFNGLCHECKFRAMEBUFFERSTATUSPROC gload_glCheckFramebufferStatus;
PFNGLFRAMEBUFFERTEXTURE1DPROC gload_glFramebufferTexture1D;
PFNGLFRAMEBUFFERTEXTURE2DPROC gload_glFramebufferTexture2D;
PFNGLFRAMEBUFFERTEXTURE3DPROC gload_glFramebufferTexture3D;
PFNGLFRAMEBUFFERRENDERBUFFERPROC gload_glFramebufferRenderbuffer;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC gload_glGetFramebufferAttachmentParameteriv;
PFNGLGENERATEMIPMAPPROC gload_glGenerateMipmap;
PFNGLBLITFRAMEBUFFERPROC gload_glBlitFramebuffer;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC gload_glRenderbufferStorageMultisample;
PFNGLFRAMEBUFFERTEXTURELAYERPROC gload_glFramebufferTextureLayer;
PFNGLMAPBUFFERRANGEPROC gload_glMapBufferRange;
PFNGLFLUSHMAPPEDBUFFERRANGEPROC gload_glFlushMappedBufferRange;
PFNGLBINDVERTEXARRAYPROC gload_glBindVertexArray;
PFNGLDELETEVERTEXARRAYSPROC gload_glDeleteVertexArrays;
PFNGLGENVERTEXARRAYSPROC gload_glGenVertexArrays;
PFNGLISVERTEXARRAYPROC gload_glIsVertexArray;

#  endif /* GL_VERSION_3_0 */
#  if defined GL_VERSION_3_1

PFNGLDRAWARRAYSINSTANCEDPROC gload_glDrawArraysInstanced;
PFNGLDRAWELEMENTSINSTANCEDPROC gload_glDrawElementsInstanced;
PFNGLTEXBUFFERPROC gload_glTexBuffer;
PFNGLPRIMITIVERESTARTINDEXPROC gload_glPrimitiveRestartIndex;
PFNGLCOPYBUFFERSUBDATAPROC gload_glCopyBufferSubData;
PFNGLGETUNIFORMINDICESPROC gload_glGetUniformIndices;
PFNGLGETACTIVEUNIFORMSIVPROC gload_glGetActiveUniformsiv;
PFNGLGETACTIVEUNIFORMNAMEPROC gload_glGetActiveUniformName;
PFNGLGETUNIFORMBLOCKINDEXPROC gload_glGetUniformBlockIndex;
PFNGLGETACTIVEUNIFORMBLOCKIVPROC gload_glGetActiveUniformBlockiv;
PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC gload_glGetActiveUniformBlockName;
PFNGLUNIFORMBLOCKBINDINGPROC gload_glUniformBlockBinding;
extern PFNGLBINDBUFFERRANGEPROC gload_glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC gload_glBindBufferBase;
extern PFNGLGETINTEGERI_VPROC gload_glGetIntegeri_v;

#  endif /* GL_VERSION_3_1 */
#  if defined GL_VERSION_3_2

PFNGLDRAWELEMENTSBASEVERTEXPROC gload_glDrawElementsBaseVertex;
PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC gload_glDrawRangeElementsBaseVertex;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC gload_glDrawElementsInstancedBaseVertex;
PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC gload_glMultiDrawElementsBaseVertex;
PFNGLPROVOKINGVERTEXPROC gload_glProvokingVertex;
PFNGLFENCESYNCPROC gload_glFenceSync;
PFNGLISSYNCPROC gload_glIsSync;
PFNGLDELETESYNCPROC gload_glDeleteSync;
PFNGLCLIENTWAITSYNCPROC gload_glClientWaitSync;
PFNGLWAITSYNCPROC gload_glWaitSync;
PFNGLGETINTEGER64VPROC gload_glGetInteger64v;
PFNGLGETSYNCIVPROC gload_glGetSynciv;
PFNGLGETINTEGER64I_VPROC gload_glGetInteger64i_v;
PFNGLGETBUFFERPARAMETERI64VPROC gload_glGetBufferParameteri64v;
PFNGLFRAMEBUFFERTEXTUREPROC gload_glFramebufferTexture;
PFNGLTEXIMAGE2DMULTISAMPLEPROC gload_glTexImage2DMultisample;
PFNGLTEXIMAGE3DMULTISAMPLEPROC gload_glTexImage3DMultisample;
PFNGLGETMULTISAMPLEFVPROC gload_glGetMultisamplefv;
PFNGLSAMPLEMASKIPROC gload_glSampleMaski;

#  endif /* GL_VERSION_3_2 */
#  if defined GL_VERSION_3_3

PFNGLBINDFRAGDATALOCATIONINDEXEDPROC gload_glBindFragDataLocationIndexed;
PFNGLGETFRAGDATAINDEXPROC gload_glGetFragDataIndex;
PFNGLGENSAMPLERSPROC gload_glGenSamplers;
PFNGLDELETESAMPLERSPROC gload_glDeleteSamplers;
PFNGLISSAMPLERPROC gload_glIsSampler;
PFNGLBINDSAMPLERPROC gload_glBindSampler;
PFNGLSAMPLERPARAMETERIPROC gload_glSamplerParameteri;
PFNGLSAMPLERPARAMETERIVPROC gload_glSamplerParameteriv;
PFNGLSAMPLERPARAMETERFPROC gload_glSamplerParameterf;
PFNGLSAMPLERPARAMETERFVPROC gload_glSamplerParameterfv;
PFNGLSAMPLERPARAMETERIIVPROC gload_glSamplerParameterIiv;
PFNGLSAMPLERPARAMETERIUIVPROC gload_glSamplerParameterIuiv;
PFNGLGETSAMPLERPARAMETERIVPROC gload_glGetSamplerParameteriv;
PFNGLGETSAMPLERPARAMETERIIVPROC gload_glGetSamplerParameterIiv;
PFNGLGETSAMPLERPARAMETERFVPROC gload_glGetSamplerParameterfv;
PFNGLGETSAMPLERPARAMETERIUIVPROC gload_glGetSamplerParameterIuiv;
PFNGLQUERYCOUNTERPROC gload_glQueryCounter;
PFNGLGETQUERYOBJECTI64VPROC gload_glGetQueryObjecti64v;
PFNGLGETQUERYOBJECTUI64VPROC gload_glGetQueryObjectui64v;
PFNGLVERTEXATTRIBDIVISORPROC gload_glVertexAttribDivisor;
PFNGLVERTEXATTRIBP1UIPROC gload_glVertexAttribP1ui;
PFNGLVERTEXATTRIBP1UIVPROC gload_glVertexAttribP1uiv;
PFNGLVERTEXATTRIBP2UIPROC gload_glVertexAttribP2ui;
PFNGLVERTEXATTRIBP2UIVPROC gload_glVertexAttribP2uiv;
PFNGLVERTEXATTRIBP3UIPROC gload_glVertexAttribP3ui;
PFNGLVERTEXATTRIBP3UIVPROC gload_glVertexAttribP3uiv;
PFNGLVERTEXATTRIBP4UIPROC gload_glVertexAttribP4ui;
PFNGLVERTEXATTRIBP4UIVPROC gload_glVertexAttribP4uiv;
PFNGLVERTEXP2UIPROC gload_glVertexP2ui;
PFNGLVERTEXP2UIVPROC gload_glVertexP2uiv;
PFNGLVERTEXP3UIPROC gload_glVertexP3ui;
PFNGLVERTEXP3UIVPROC gload_glVertexP3uiv;
PFNGLVERTEXP4UIPROC gload_glVertexP4ui;
PFNGLVERTEXP4UIVPROC gload_glVertexP4uiv;
PFNGLTEXCOORDP1UIPROC gload_glTexCoordP1ui;
PFNGLTEXCOORDP1UIVPROC gload_glTexCoordP1uiv;
PFNGLTEXCOORDP2UIPROC gload_glTexCoordP2ui;
PFNGLTEXCOORDP2UIVPROC gload_glTexCoordP2uiv;
PFNGLTEXCOORDP3UIPROC gload_glTexCoordP3ui;
PFNGLTEXCOORDP3UIVPROC gload_glTexCoordP3uiv;
PFNGLTEXCOORDP4UIPROC gload_glTexCoordP4ui;
PFNGLTEXCOORDP4UIVPROC gload_glTexCoordP4uiv;
PFNGLMULTITEXCOORDP1UIPROC gload_glMultiTexCoordP1ui;
PFNGLMULTITEXCOORDP1UIVPROC gload_glMultiTexCoordP1uiv;
PFNGLMULTITEXCOORDP2UIPROC gload_glMultiTexCoordP2ui;
PFNGLMULTITEXCOORDP2UIVPROC gload_glMultiTexCoordP2uiv;
PFNGLMULTITEXCOORDP3UIPROC gload_glMultiTexCoordP3ui;
PFNGLMULTITEXCOORDP3UIVPROC gload_glMultiTexCoordP3uiv;
PFNGLMULTITEXCOORDP4UIPROC gload_glMultiTexCoordP4ui;
PFNGLMULTITEXCOORDP4UIVPROC gload_glMultiTexCoordP4uiv;
PFNGLNORMALP3UIPROC gload_glNormalP3ui;
PFNGLNORMALP3UIVPROC gload_glNormalP3uiv;
PFNGLCOLORP3UIPROC gload_glColorP3ui;
PFNGLCOLORP3UIVPROC gload_glColorP3uiv;
PFNGLCOLORP4UIPROC gload_glColorP4ui;
PFNGLCOLORP4UIVPROC gload_glColorP4uiv;
PFNGLSECONDARYCOLORP3UIPROC gload_glSecondaryColorP3ui;
PFNGLSECONDARYCOLORP3UIVPROC gload_glSecondaryColorP3uiv;

#  endif /* GL_VERSION_3_3 */
#  if defined GL_VERSION_4_0

PFNGLMINSAMPLESHADINGPROC gload_glMinSampleShading;
PFNGLBLENDEQUATIONIPROC gload_glBlendEquationi;
PFNGLBLENDEQUATIONSEPARATEIPROC gload_glBlendEquationSeparatei;
PFNGLBLENDFUNCIPROC gload_glBlendFunci;
PFNGLBLENDFUNCSEPARATEIPROC gload_glBlendFuncSeparatei;
PFNGLDRAWARRAYSINDIRECTPROC gload_glDrawArraysIndirect;
PFNGLDRAWELEMENTSINDIRECTPROC gload_glDrawElementsIndirect;
PFNGLUNIFORM1DPROC gload_glUniform1d;
PFNGLUNIFORM2DPROC gload_glUniform2d;
PFNGLUNIFORM3DPROC gload_glUniform3d;
PFNGLUNIFORM4DPROC gload_glUniform4d;
PFNGLUNIFORM1DVPROC gload_glUniform1dv;
PFNGLUNIFORM2DVPROC gload_glUniform2dv;
PFNGLUNIFORM3DVPROC gload_glUniform3dv;
PFNGLUNIFORM4DVPROC gload_glUniform4dv;
PFNGLUNIFORMMATRIX2DVPROC gload_glUniformMatrix2dv;
PFNGLUNIFORMMATRIX3DVPROC gload_glUniformMatrix3dv;
PFNGLUNIFORMMATRIX4DVPROC gload_glUniformMatrix4dv;
PFNGLUNIFORMMATRIX2X3DVPROC gload_glUniformMatrix2x3dv;
PFNGLUNIFORMMATRIX2X4DVPROC gload_glUniformMatrix2x4dv;
PFNGLUNIFORMMATRIX3X2DVPROC gload_glUniformMatrix3x2dv;
PFNGLUNIFORMMATRIX3X4DVPROC gload_glUniformMatrix3x4dv;
PFNGLUNIFORMMATRIX4X2DVPROC gload_glUniformMatrix4x2dv;
PFNGLUNIFORMMATRIX4X3DVPROC gload_glUniformMatrix4x3dv;
PFNGLGETUNIFORMDVPROC gload_glGetUniformdv;
PFNGLGETSUBROUTINEUNIFORMLOCATIONPROC gload_glGetSubroutineUniformLocation;
PFNGLGETSUBROUTINEINDEXPROC gload_glGetSubroutineIndex;
PFNGLGETACTIVESUBROUTINEUNIFORMIVPROC gload_glGetActiveSubroutineUniformiv;
PFNGLGETACTIVESUBROUTINEUNIFORMNAMEPROC gload_glGetActiveSubroutineUniformName;
PFNGLGETACTIVESUBROUTINENAMEPROC gload_glGetActiveSubroutineName;
PFNGLUNIFORMSUBROUTINESUIVPROC gload_glUniformSubroutinesuiv;
PFNGLGETUNIFORMSUBROUTINEUIVPROC gload_glGetUniformSubroutineuiv;
PFNGLGETPROGRAMSTAGEIVPROC gload_glGetProgramStageiv;
PFNGLPATCHPARAMETERIPROC gload_glPatchParameteri;
PFNGLPATCHPARAMETERFVPROC gload_glPatchParameterfv;
PFNGLBINDTRANSFORMFEEDBACKPROC gload_glBindTransformFeedback;
PFNGLDELETETRANSFORMFEEDBACKSPROC gload_glDeleteTransformFeedbacks;
PFNGLGENTRANSFORMFEEDBACKSPROC gload_glGenTransformFeedbacks;
PFNGLISTRANSFORMFEEDBACKPROC gload_glIsTransformFeedback;
PFNGLPAUSETRANSFORMFEEDBACKPROC gload_glPauseTransformFeedback;
PFNGLRESUMETRANSFORMFEEDBACKPROC gload_glResumeTransformFeedback;
PFNGLDRAWTRANSFORMFEEDBACKPROC gload_glDrawTransformFeedback;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMPROC gload_glDrawTransformFeedbackStream;
PFNGLBEGINQUERYINDEXEDPROC gload_glBeginQueryIndexed;
PFNGLENDQUERYINDEXEDPROC gload_glEndQueryIndexed;
PFNGLGETQUERYINDEXEDIVPROC gload_glGetQueryIndexediv;

#  endif /* GL_VERSION_4_0 */
#  if defined GL_VERSION_4_1

PFNGLRELEASESHADERCOMPILERPROC gload_glReleaseShaderCompiler;
PFNGLSHADERBINARYPROC gload_glShaderBinary;
PFNGLGETSHADERPRECISIONFORMATPROC gload_glGetShaderPrecisionFormat;
PFNGLDEPTHRANGEFPROC gload_glDepthRangef;
PFNGLCLEARDEPTHFPROC gload_glClearDepthf;
PFNGLGETPROGRAMBINARYPROC gload_glGetProgramBinary;
PFNGLPROGRAMBINARYPROC gload_glProgramBinary;
PFNGLPROGRAMPARAMETERIPROC gload_glProgramParameteri;
PFNGLUSEPROGRAMSTAGESPROC gload_glUseProgramStages;
PFNGLACTIVESHADERPROGRAMPROC gload_glActiveShaderProgram;
PFNGLCREATESHADERPROGRAMVPROC gload_glCreateShaderProgramv;
PFNGLBINDPROGRAMPIPELINEPROC gload_glBindProgramPipeline;
PFNGLDELETEPROGRAMPIPELINESPROC gload_glDeleteProgramPipelines;
PFNGLGENPROGRAMPIPELINESPROC gload_glGenProgramPipelines;
PFNGLISPROGRAMPIPELINEPROC gload_glIsProgramPipeline;
PFNGLGETPROGRAMPIPELINEIVPROC gload_glGetProgramPipelineiv;
extern PFNGLPROGRAMPARAMETERIPROC gload_glProgramParameteri;
PFNGLPROGRAMUNIFORM1IPROC gload_glProgramUniform1i;
PFNGLPROGRAMUNIFORM1IVPROC gload_glProgramUniform1iv;
PFNGLPROGRAMUNIFORM1FPROC gload_glProgramUniform1f;
PFNGLPROGRAMUNIFORM1FVPROC gload_glProgramUniform1fv;
PFNGLPROGRAMUNIFORM1DPROC gload_glProgramUniform1d;
PFNGLPROGRAMUNIFORM1DVPROC gload_glProgramUniform1dv;
PFNGLPROGRAMUNIFORM1UIPROC gload_glProgramUniform1ui;
PFNGLPROGRAMUNIFORM1UIVPROC gload_glProgramUniform1uiv;
PFNGLPROGRAMUNIFORM2IPROC gload_glProgramUniform2i;
PFNGLPROGRAMUNIFORM2IVPROC gload_glProgramUniform2iv;
PFNGLPROGRAMUNIFORM2FPROC gload_glProgramUniform2f;
PFNGLPROGRAMUNIFORM2FVPROC gload_glProgramUniform2fv;
PFNGLPROGRAMUNIFORM2DPROC gload_glProgramUniform2d;
PFNGLPROGRAMUNIFORM2DVPROC gload_glProgramUniform2dv;
PFNGLPROGRAMUNIFORM2UIPROC gload_glProgramUniform2ui;
PFNGLPROGRAMUNIFORM2UIVPROC gload_glProgramUniform2uiv;
PFNGLPROGRAMUNIFORM3IPROC gload_glProgramUniform3i;
PFNGLPROGRAMUNIFORM3IVPROC gload_glProgramUniform3iv;
PFNGLPROGRAMUNIFORM3FPROC gload_glProgramUniform3f;
PFNGLPROGRAMUNIFORM3FVPROC gload_glProgramUniform3fv;
PFNGLPROGRAMUNIFORM3DPROC gload_glProgramUniform3d;
PFNGLPROGRAMUNIFORM3DVPROC gload_glProgramUniform3dv;
PFNGLPROGRAMUNIFORM3UIPROC gload_glProgramUniform3ui;
PFNGLPROGRAMUNIFORM3UIVPROC gload_glProgramUniform3uiv;
PFNGLPROGRAMUNIFORM4IPROC gload_glProgramUniform4i;
PFNGLPROGRAMUNIFORM4IVPROC gload_glProgramUniform4iv;
PFNGLPROGRAMUNIFORM4FPROC gload_glProgramUniform4f;
PFNGLPROGRAMUNIFORM4FVPROC gload_glProgramUniform4fv;
PFNGLPROGRAMUNIFORM4DPROC gload_glProgramUniform4d;
PFNGLPROGRAMUNIFORM4DVPROC gload_glProgramUniform4dv;
PFNGLPROGRAMUNIFORM4UIPROC gload_glProgramUniform4ui;
PFNGLPROGRAMUNIFORM4UIVPROC gload_glProgramUniform4uiv;
PFNGLPROGRAMUNIFORMMATRIX2FVPROC gload_glProgramUniformMatrix2fv;
PFNGLPROGRAMUNIFORMMATRIX3FVPROC gload_glProgramUniformMatrix3fv;
PFNGLPROGRAMUNIFORMMATRIX4FVPROC gload_glProgramUniformMatrix4fv;
PFNGLPROGRAMUNIFORMMATRIX2DVPROC gload_glProgramUniformMatrix2dv;
PFNGLPROGRAMUNIFORMMATRIX3DVPROC gload_glProgramUniformMatrix3dv;
PFNGLPROGRAMUNIFORMMATRIX4DVPROC gload_glProgramUniformMatrix4dv;
PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC gload_glProgramUniformMatrix2x3fv;
PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC gload_glProgramUniformMatrix3x2fv;
PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC gload_glProgramUniformMatrix2x4fv;
PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC gload_glProgramUniformMatrix4x2fv;
PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC gload_glProgramUniformMatrix3x4fv;
PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC gload_glProgramUniformMatrix4x3fv;
PFNGLPROGRAMUNIFORMMATRIX2X3DVPROC gload_glProgramUniformMatrix2x3dv;
PFNGLPROGRAMUNIFORMMATRIX3X2DVPROC gload_glProgramUniformMatrix3x2dv;
PFNGLPROGRAMUNIFORMMATRIX2X4DVPROC gload_glProgramUniformMatrix2x4dv;
PFNGLPROGRAMUNIFORMMATRIX4X2DVPROC gload_glProgramUniformMatrix4x2dv;
PFNGLPROGRAMUNIFORMMATRIX3X4DVPROC gload_glProgramUniformMatrix3x4dv;
PFNGLPROGRAMUNIFORMMATRIX4X3DVPROC gload_glProgramUniformMatrix4x3dv;
PFNGLVALIDATEPROGRAMPIPELINEPROC gload_glValidateProgramPipeline;
PFNGLGETPROGRAMPIPELINEINFOLOGPROC gload_glGetProgramPipelineInfoLog;
PFNGLVERTEXATTRIBL1DPROC gload_glVertexAttribL1d;
PFNGLVERTEXATTRIBL2DPROC gload_glVertexAttribL2d;
PFNGLVERTEXATTRIBL3DPROC gload_glVertexAttribL3d;
PFNGLVERTEXATTRIBL4DPROC gload_glVertexAttribL4d;
PFNGLVERTEXATTRIBL1DVPROC gload_glVertexAttribL1dv;
PFNGLVERTEXATTRIBL2DVPROC gload_glVertexAttribL2dv;
PFNGLVERTEXATTRIBL3DVPROC gload_glVertexAttribL3dv;
PFNGLVERTEXATTRIBL4DVPROC gload_glVertexAttribL4dv;
PFNGLVERTEXATTRIBLPOINTERPROC gload_glVertexAttribLPointer;
PFNGLGETVERTEXATTRIBLDVPROC gload_glGetVertexAttribLdv;
PFNGLVIEWPORTARRAYVPROC gload_glViewportArrayv;
PFNGLVIEWPORTINDEXEDFPROC gload_glViewportIndexedf;
PFNGLVIEWPORTINDEXEDFVPROC gload_glViewportIndexedfv;
PFNGLSCISSORARRAYVPROC gload_glScissorArrayv;
PFNGLSCISSORINDEXEDPROC gload_glScissorIndexed;
PFNGLSCISSORINDEXEDVPROC gload_glScissorIndexedv;
PFNGLDEPTHRANGEARRAYVPROC gload_glDepthRangeArrayv;
PFNGLDEPTHRANGEINDEXEDPROC gload_glDepthRangeIndexed;
PFNGLGETFLOATI_VPROC gload_glGetFloati_v;
PFNGLGETDOUBLEI_VPROC gload_glGetDoublei_v;

#  endif /* GL_VERSION_4_1 */
#  if defined GL_VERSION_4_2

PFNGLDRAWARRAYSINSTANCEDBASEINSTANCEPROC gload_glDrawArraysInstancedBaseInstance;
PFNGLDRAWELEMENTSINSTANCEDBASEINSTANCEPROC gload_glDrawElementsInstancedBaseInstance;
PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC gload_glDrawElementsInstancedBaseVertexBaseInstance;
PFNGLGETINTERNALFORMATIVPROC gload_glGetInternalformativ;
PFNGLGETACTIVEATOMICCOUNTERBUFFERIVPROC gload_glGetActiveAtomicCounterBufferiv;
PFNGLBINDIMAGETEXTUREPROC gload_glBindImageTexture;
PFNGLMEMORYBARRIERPROC gload_glMemoryBarrier;
PFNGLTEXSTORAGE1DPROC gload_glTexStorage1D;
PFNGLTEXSTORAGE2DPROC gload_glTexStorage2D;
PFNGLTEXSTORAGE3DPROC gload_glTexStorage3D;
PFNGLDRAWTRANSFORMFEEDBACKINSTANCEDPROC gload_glDrawTransformFeedbackInstanced;
PFNGLDRAWTRANSFORMFEEDBACKSTREAMINSTANCEDPROC gload_glDrawTransformFeedbackStreamInstanced;

#  endif /* GL_VERSION_4_2 */
#  if defined GL_VERSION_4_3

PFNGLCLEARBUFFERDATAPROC gload_glClearBufferData;
PFNGLCLEARBUFFERSUBDATAPROC gload_glClearBufferSubData;
PFNGLDISPATCHCOMPUTEPROC gload_glDispatchCompute;
PFNGLDISPATCHCOMPUTEINDIRECTPROC gload_glDispatchComputeIndirect;
PFNGLCOPYIMAGESUBDATAPROC gload_glCopyImageSubData;
PFNGLFRAMEBUFFERPARAMETERIPROC gload_glFramebufferParameteri;
PFNGLGETFRAMEBUFFERPARAMETERIVPROC gload_glGetFramebufferParameteriv;
PFNGLGETINTERNALFORMATI64VPROC gload_glGetInternalformati64v;
PFNGLINVALIDATETEXSUBIMAGEPROC gload_glInvalidateTexSubImage;
PFNGLINVALIDATETEXIMAGEPROC gload_glInvalidateTexImage;
PFNGLINVALIDATEBUFFERSUBDATAPROC gload_glInvalidateBufferSubData;
PFNGLINVALIDATEBUFFERDATAPROC gload_glInvalidateBufferData;
PFNGLINVALIDATEFRAMEBUFFERPROC gload_glInvalidateFramebuffer;
PFNGLINVALIDATESUBFRAMEBUFFERPROC gload_glInvalidateSubFramebuffer;
PFNGLMULTIDRAWARRAYSINDIRECTPROC gload_glMultiDrawArraysIndirect;
PFNGLMULTIDRAWELEMENTSINDIRECTPROC gload_glMultiDrawElementsIndirect;
PFNGLGETPROGRAMINTERFACEIVPROC gload_glGetProgramInterfaceiv;
PFNGLGETPROGRAMRESOURCEINDEXPROC gload_glGetProgramResourceIndex;
PFNGLGETPROGRAMRESOURCENAMEPROC gload_glGetProgramResourceName;
PFNGLGETPROGRAMRESOURCEIVPROC gload_glGetProgramResourceiv;
PFNGLGETPROGRAMRESOURCELOCATIONPROC gload_glGetProgramResourceLocation;
PFNGLGETPROGRAMRESOURCELOCATIONINDEXPROC gload_glGetProgramResourceLocationIndex;
PFNGLSHADERSTORAGEBLOCKBINDINGPROC gload_glShaderStorageBlockBinding;
PFNGLTEXBUFFERRANGEPROC gload_glTexBufferRange;
PFNGLTEXSTORAGE2DMULTISAMPLEPROC gload_glTexStorage2DMultisample;
PFNGLTEXSTORAGE3DMULTISAMPLEPROC gload_glTexStorage3DMultisample;
PFNGLTEXTUREVIEWPROC gload_glTextureView;
PFNGLBINDVERTEXBUFFERPROC gload_glBindVertexBuffer;
PFNGLVERTEXATTRIBFORMATPROC gload_glVertexAttribFormat;
PFNGLVERTEXATTRIBIFORMATPROC gload_glVertexAttribIFormat;
PFNGLVERTEXATTRIBLFORMATPROC gload_glVertexAttribLFormat;
PFNGLVERTEXATTRIBBINDINGPROC gload_glVertexAttribBinding;
PFNGLVERTEXBINDINGDIVISORPROC gload_glVertexBindingDivisor;
PFNGLDEBUGMESSAGECONTROLPROC gload_glDebugMessageControl;
PFNGLDEBUGMESSAGEINSERTPROC gload_glDebugMessageInsert;
PFNGLDEBUGMESSAGECALLBACKPROC gload_glDebugMessageCallback;
PFNGLGETDEBUGMESSAGELOGPROC gload_glGetDebugMessageLog;
PFNGLPUSHDEBUGGROUPPROC gload_glPushDebugGroup;
PFNGLPOPDEBUGGROUPPROC gload_glPopDebugGroup;
PFNGLOBJECTLABELPROC gload_glObjectLabel;
PFNGLGETOBJECTLABELPROC gload_glGetObjectLabel;
PFNGLOBJECTPTRLABELPROC gload_glObjectPtrLabel;
PFNGLGETOBJECTPTRLABELPROC gload_glGetObjectPtrLabel;
extern PFNGLGETPOINTERVPROC gload_glGetPointerv;

#  endif /* GL_VERSION_4_3 */
#  if defined GL_VERSION_4_4

PFNGLBUFFERSTORAGEPROC gload_glBufferStorage;
PFNGLCLEARTEXIMAGEPROC gload_glClearTexImage;
PFNGLCLEARTEXSUBIMAGEPROC gload_glClearTexSubImage;
PFNGLBINDBUFFERSBASEPROC gload_glBindBuffersBase;
PFNGLBINDBUFFERSRANGEPROC gload_glBindBuffersRange;
PFNGLBINDTEXTURESPROC gload_glBindTextures;
PFNGLBINDSAMPLERSPROC gload_glBindSamplers;
PFNGLBINDIMAGETEXTURESPROC gload_glBindImageTextures;
PFNGLBINDVERTEXBUFFERSPROC gload_glBindVertexBuffers;

#  endif /* GL_VERSION_4_4 */
#  if defined GL_VERSION_4_5

PFNGLCLIPCONTROLPROC gload_glClipControl;
PFNGLCREATETRANSFORMFEEDBACKSPROC gload_glCreateTransformFeedbacks;
PFNGLTRANSFORMFEEDBACKBUFFERBASEPROC gload_glTransformFeedbackBufferBase;
PFNGLTRANSFORMFEEDBACKBUFFERRANGEPROC gload_glTransformFeedbackBufferRange;
PFNGLGETTRANSFORMFEEDBACKIVPROC gload_glGetTransformFeedbackiv;
PFNGLGETTRANSFORMFEEDBACKI_VPROC gload_glGetTransformFeedbacki_v;
PFNGLGETTRANSFORMFEEDBACKI64_VPROC gload_glGetTransformFeedbacki64_v;
PFNGLCREATEBUFFERSPROC gload_glCreateBuffers;
PFNGLNAMEDBUFFERSTORAGEPROC gload_glNamedBufferStorage;
PFNGLNAMEDBUFFERDATAPROC gload_glNamedBufferData;
PFNGLNAMEDBUFFERSUBDATAPROC gload_glNamedBufferSubData;
PFNGLCOPYNAMEDBUFFERSUBDATAPROC gload_glCopyNamedBufferSubData;
PFNGLCLEARNAMEDBUFFERDATAPROC gload_glClearNamedBufferData;
PFNGLCLEARNAMEDBUFFERSUBDATAPROC gload_glClearNamedBufferSubData;
PFNGLMAPNAMEDBUFFERPROC gload_glMapNamedBuffer;
PFNGLMAPNAMEDBUFFERRANGEPROC gload_glMapNamedBufferRange;
PFNGLUNMAPNAMEDBUFFERPROC gload_glUnmapNamedBuffer;
PFNGLFLUSHMAPPEDNAMEDBUFFERRANGEPROC gload_glFlushMappedNamedBufferRange;
PFNGLGETNAMEDBUFFERPARAMETERIVPROC gload_glGetNamedBufferParameteriv;
PFNGLGETNAMEDBUFFERPARAMETERI64VPROC gload_glGetNamedBufferParameteri64v;
PFNGLGETNAMEDBUFFERPOINTERVPROC gload_glGetNamedBufferPointerv;
PFNGLGETNAMEDBUFFERSUBDATAPROC gload_glGetNamedBufferSubData;
PFNGLCREATEFRAMEBUFFERSPROC gload_glCreateFramebuffers;
PFNGLNAMEDFRAMEBUFFERRENDERBUFFERPROC gload_glNamedFramebufferRenderbuffer;
PFNGLNAMEDFRAMEBUFFERPARAMETERIPROC gload_glNamedFramebufferParameteri;
PFNGLNAMEDFRAMEBUFFERTEXTUREPROC gload_glNamedFramebufferTexture;
PFNGLNAMEDFRAMEBUFFERTEXTURELAYERPROC gload_glNamedFramebufferTextureLayer;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERPROC gload_glNamedFramebufferDrawBuffer;
PFNGLNAMEDFRAMEBUFFERDRAWBUFFERSPROC gload_glNamedFramebufferDrawBuffers;
PFNGLNAMEDFRAMEBUFFERREADBUFFERPROC gload_glNamedFramebufferReadBuffer;
PFNGLINVALIDATENAMEDFRAMEBUFFERDATAPROC gload_glInvalidateNamedFramebufferData;
PFNGLINVALIDATENAMEDFRAMEBUFFERSUBDATAPROC gload_glInvalidateNamedFramebufferSubData;
PFNGLCLEARNAMEDFRAMEBUFFERIVPROC gload_glClearNamedFramebufferiv;
PFNGLCLEARNAMEDFRAMEBUFFERUIVPROC gload_glClearNamedFramebufferuiv;
PFNGLCLEARNAMEDFRAMEBUFFERFVPROC gload_glClearNamedFramebufferfv;
PFNGLCLEARNAMEDFRAMEBUFFERFIPROC gload_glClearNamedFramebufferfi;
PFNGLBLITNAMEDFRAMEBUFFERPROC gload_glBlitNamedFramebuffer;
PFNGLCHECKNAMEDFRAMEBUFFERSTATUSPROC gload_glCheckNamedFramebufferStatus;
PFNGLGETNAMEDFRAMEBUFFERPARAMETERIVPROC gload_glGetNamedFramebufferParameteriv;
PFNGLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIVPROC gload_glGetNamedFramebufferAttachmentParameteriv;
PFNGLCREATERENDERBUFFERSPROC gload_glCreateRenderbuffers;
PFNGLNAMEDRENDERBUFFERSTORAGEPROC gload_glNamedRenderbufferStorage;
PFNGLNAMEDRENDERBUFFERSTORAGEMULTISAMPLEPROC gload_glNamedRenderbufferStorageMultisample;
PFNGLGETNAMEDRENDERBUFFERPARAMETERIVPROC gload_glGetNamedRenderbufferParameteriv;
PFNGLCREATETEXTURESPROC gload_glCreateTextures;
PFNGLTEXTUREBUFFERPROC gload_glTextureBuffer;
PFNGLTEXTUREBUFFERRANGEPROC gload_glTextureBufferRange;
PFNGLTEXTURESTORAGE1DPROC gload_glTextureStorage1D;
PFNGLTEXTURESTORAGE2DPROC gload_glTextureStorage2D;
PFNGLTEXTURESTORAGE3DPROC gload_glTextureStorage3D;
PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC gload_glTextureStorage2DMultisample;
PFNGLTEXTURESTORAGE3DMULTISAMPLEPROC gload_glTextureStorage3DMultisample;
PFNGLTEXTURESUBIMAGE1DPROC gload_glTextureSubImage1D;
PFNGLTEXTURESUBIMAGE2DPROC gload_glTextureSubImage2D;
PFNGLTEXTURESUBIMAGE3DPROC gload_glTextureSubImage3D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE1DPROC gload_glCompressedTextureSubImage1D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE2DPROC gload_glCompressedTextureSubImage2D;
PFNGLCOMPRESSEDTEXTURESUBIMAGE3DPROC gload_glCompressedTextureSubImage3D;
PFNGLCOPYTEXTURESUBIMAGE1DPROC gload_glCopyTextureSubImage1D;
PFNGLCOPYTEXTURESUBIMAGE2DPROC gload_glCopyTextureSubImage2D;
PFNGLCOPYTEXTURESUBIMAGE3DPROC gload_glCopyTextureSubImage3D;
PFNGLTEXTUREPARAMETERFPROC gload_glTextureParameterf;
PFNGLTEXTUREPARAMETERFVPROC gload_glTextureParameterfv;
PFNGLTEXTUREPARAMETERIPROC gload_glTextureParameteri;
PFNGLTEXTUREPARAMETERIIVPROC gload_glTextureParameterIiv;
PFNGLTEXTUREPARAMETERIUIVPROC gload_glTextureParameterIuiv;
PFNGLTEXTUREPARAMETERIVPROC gload_glTextureParameteriv;
PFNGLGENERATETEXTUREMIPMAPPROC gload_glGenerateTextureMipmap;
PFNGLBINDTEXTUREUNITPROC gload_glBindTextureUnit;
PFNGLGETTEXTUREIMAGEPROC gload_glGetTextureImage;
PFNGLGETCOMPRESSEDTEXTUREIMAGEPROC gload_glGetCompressedTextureImage;
PFNGLGETTEXTURELEVELPARAMETERFVPROC gload_glGetTextureLevelParameterfv;
PFNGLGETTEXTURELEVELPARAMETERIVPROC gload_glGetTextureLevelParameteriv;
PFNGLGETTEXTUREPARAMETERFVPROC gload_glGetTextureParameterfv;
PFNGLGETTEXTUREPARAMETERIIVPROC gload_glGetTextureParameterIiv;
PFNGLGETTEXTUREPARAMETERIUIVPROC gload_glGetTextureParameterIuiv;
PFNGLGETTEXTUREPARAMETERIVPROC gload_glGetTextureParameteriv;
PFNGLCREATEVERTEXARRAYSPROC gload_glCreateVertexArrays;
PFNGLDISABLEVERTEXARRAYATTRIBPROC gload_glDisableVertexArrayAttrib;
PFNGLENABLEVERTEXARRAYATTRIBPROC gload_glEnableVertexArrayAttrib;
PFNGLVERTEXARRAYELEMENTBUFFERPROC gload_glVertexArrayElementBuffer;
PFNGLVERTEXARRAYVERTEXBUFFERPROC gload_glVertexArrayVertexBuffer;
PFNGLVERTEXARRAYVERTEXBUFFERSPROC gload_glVertexArrayVertexBuffers;
PFNGLVERTEXARRAYATTRIBBINDINGPROC gload_glVertexArrayAttribBinding;
PFNGLVERTEXARRAYATTRIBFORMATPROC gload_glVertexArrayAttribFormat;
PFNGLVERTEXARRAYATTRIBIFORMATPROC gload_glVertexArrayAttribIFormat;
PFNGLVERTEXARRAYATTRIBLFORMATPROC gload_glVertexArrayAttribLFormat;
PFNGLVERTEXARRAYBINDINGDIVISORPROC gload_glVertexArrayBindingDivisor;
PFNGLGETVERTEXARRAYIVPROC gload_glGetVertexArrayiv;
PFNGLGETVERTEXARRAYINDEXEDIVPROC gload_glGetVertexArrayIndexediv;
PFNGLGETVERTEXARRAYINDEXED64IVPROC gload_glGetVertexArrayIndexed64iv;
PFNGLCREATESAMPLERSPROC gload_glCreateSamplers;
PFNGLCREATEPROGRAMPIPELINESPROC gload_glCreateProgramPipelines;
PFNGLCREATEQUERIESPROC gload_glCreateQueries;
PFNGLGETQUERYBUFFEROBJECTI64VPROC gload_glGetQueryBufferObjecti64v;
PFNGLGETQUERYBUFFEROBJECTIVPROC gload_glGetQueryBufferObjectiv;
PFNGLGETQUERYBUFFEROBJECTUI64VPROC gload_glGetQueryBufferObjectui64v;
PFNGLGETQUERYBUFFEROBJECTUIVPROC gload_glGetQueryBufferObjectuiv;
PFNGLMEMORYBARRIERBYREGIONPROC gload_glMemoryBarrierByRegion;
PFNGLGETTEXTURESUBIMAGEPROC gload_glGetTextureSubImage;
PFNGLGETCOMPRESSEDTEXTURESUBIMAGEPROC gload_glGetCompressedTextureSubImage;
PFNGLGETGRAPHICSRESETSTATUSPROC gload_glGetGraphicsResetStatus;
PFNGLGETNCOMPRESSEDTEXIMAGEPROC gload_glGetnCompressedTexImage;
PFNGLGETNTEXIMAGEPROC gload_glGetnTexImage;
PFNGLGETNUNIFORMDVPROC gload_glGetnUniformdv;
PFNGLGETNUNIFORMFVPROC gload_glGetnUniformfv;
PFNGLGETNUNIFORMIVPROC gload_glGetnUniformiv;
PFNGLGETNUNIFORMUIVPROC gload_glGetnUniformuiv;
PFNGLREADNPIXELSPROC gload_glReadnPixels;
PFNGLGETNMAPDVPROC gload_glGetnMapdv;
PFNGLGETNMAPFVPROC gload_glGetnMapfv;
PFNGLGETNMAPIVPROC gload_glGetnMapiv;
PFNGLGETNPIXELMAPFVPROC gload_glGetnPixelMapfv;
PFNGLGETNPIXELMAPUIVPROC gload_glGetnPixelMapuiv;
PFNGLGETNPIXELMAPUSVPROC gload_glGetnPixelMapusv;
PFNGLGETNPOLYGONSTIPPLEPROC gload_glGetnPolygonStipple;
PFNGLGETNCOLORTABLEPROC gload_glGetnColorTable;
PFNGLGETNCONVOLUTIONFILTERPROC gload_glGetnConvolutionFilter;
PFNGLGETNSEPARABLEFILTERPROC gload_glGetnSeparableFilter;
PFNGLGETNHISTOGRAMPROC gload_glGetnHistogram;
PFNGLGETNMINMAXPROC gload_glGetnMinmax;
PFNGLTEXTUREBARRIERPROC gload_glTextureBarrier;

#  endif /* GL_VERSION_4_5 */
#  if defined GL_VERSION_4_6

PFNGLSPECIALIZESHADERPROC gload_glSpecializeShader;
PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC gload_glMultiDrawArraysIndirectCount;
PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC gload_glMultiDrawElementsIndirectCount;
PFNGLPOLYGONOFFSETCLAMPPROC gload_glPolygonOffsetClamp;

#  endif /* GL_VERSION_4_6 */
#  if defined GL_VERSION_ES_CM_1_0

extern PFNGLALPHAFUNCPROC gload_glAlphaFunc;
extern PFNGLCLEARCOLORPROC gload_glClearColor;
extern PFNGLCLEARDEPTHFPROC gload_glClearDepthf;
PFNGLCLIPPLANEFPROC gload_glClipPlanef;
extern PFNGLCOLOR4FPROC gload_glColor4f;
extern PFNGLDEPTHRANGEFPROC gload_glDepthRangef;
extern PFNGLFOGFPROC gload_glFogf;
extern PFNGLFOGFVPROC gload_glFogfv;
PFNGLFRUSTUMFPROC gload_glFrustumf;
PFNGLGETCLIPPLANEFPROC gload_glGetClipPlanef;
extern PFNGLGETFLOATVPROC gload_glGetFloatv;
extern PFNGLGETLIGHTFVPROC gload_glGetLightfv;
extern PFNGLGETMATERIALFVPROC gload_glGetMaterialfv;
extern PFNGLGETTEXENVFVPROC gload_glGetTexEnvfv;
extern PFNGLGETTEXPARAMETERFVPROC gload_glGetTexParameterfv;
extern PFNGLLIGHTMODELFPROC gload_glLightModelf;
extern PFNGLLIGHTMODELFVPROC gload_glLightModelfv;
extern PFNGLLIGHTFPROC gload_glLightf;
extern PFNGLLIGHTFVPROC gload_glLightfv;
extern PFNGLLINEWIDTHPROC gload_glLineWidth;
extern PFNGLLOADMATRIXFPROC gload_glLoadMatrixf;
extern PFNGLMATERIALFPROC gload_glMaterialf;
extern PFNGLMATERIALFVPROC gload_glMaterialfv;
extern PFNGLMULTMATRIXFPROC gload_glMultMatrixf;
extern PFNGLMULTITEXCOORD4FPROC gload_glMultiTexCoord4f;
extern PFNGLNORMAL3FPROC gload_glNormal3f;
PFNGLORTHOFPROC gload_glOrthof;
extern PFNGLPOINTPARAMETERFPROC gload_glPointParameterf;
extern PFNGLPOINTPARAMETERFVPROC gload_glPointParameterfv;
extern PFNGLPOINTSIZEPROC gload_glPointSize;
extern PFNGLPOLYGONOFFSETPROC gload_glPolygonOffset;
extern PFNGLROTATEFPROC gload_glRotatef;
extern PFNGLSCALEFPROC gload_glScalef;
extern PFNGLTEXENVFPROC gload_glTexEnvf;
extern PFNGLTEXENVFVPROC gload_glTexEnvfv;
extern PFNGLTEXPARAMETERFPROC gload_glTexParameterf;
extern PFNGLTEXPARAMETERFVPROC gload_glTexParameterfv;
extern PFNGLTRANSLATEFPROC gload_glTranslatef;
extern PFNGLACTIVETEXTUREPROC gload_glActiveTexture;
PFNGLALPHAFUNCXPROC gload_glAlphaFuncx;
extern PFNGLBINDBUFFERPROC gload_glBindBuffer;
extern PFNGLBINDTEXTUREPROC gload_glBindTexture;
extern PFNGLBLENDFUNCPROC gload_glBlendFunc;
extern PFNGLBUFFERDATAPROC gload_glBufferData;
extern PFNGLBUFFERSUBDATAPROC gload_glBufferSubData;
extern PFNGLCLEARPROC gload_glClear;
PFNGLCLEARCOLORXPROC gload_glClearColorx;
PFNGLCLEARDEPTHXPROC gload_glClearDepthx;
extern PFNGLCLEARSTENCILPROC gload_glClearStencil;
extern PFNGLCLIENTACTIVETEXTUREPROC gload_glClientActiveTexture;
PFNGLCLIPPLANEXPROC gload_glClipPlanex;
extern PFNGLCOLOR4UBPROC gload_glColor4ub;
PFNGLCOLOR4XPROC gload_glColor4x;
extern PFNGLCOLORMASKPROC gload_glColorMask;
extern PFNGLCOLORPOINTERPROC gload_glColorPointer;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC gload_glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC gload_glCompressedTexSubImage2D;
extern PFNGLCOPYTEXIMAGE2DPROC gload_glCopyTexImage2D;
extern PFNGLCOPYTEXSUBIMAGE2DPROC gload_glCopyTexSubImage2D;
extern PFNGLCULLFACEPROC gload_glCullFace;
extern PFNGLDELETEBUFFERSPROC gload_glDeleteBuffers;
extern PFNGLDELETETEXTURESPROC gload_glDeleteTextures;
extern PFNGLDEPTHFUNCPROC gload_glDepthFunc;
extern PFNGLDEPTHMASKPROC gload_glDepthMask;
PFNGLDEPTHRANGEXPROC gload_glDepthRangex;
extern PFNGLDISABLEPROC gload_glDisable;
extern PFNGLDISABLECLIENTSTATEPROC gload_glDisableClientState;
extern PFNGLDRAWARRAYSPROC gload_glDrawArrays;
extern PFNGLDRAWELEMENTSPROC gload_glDrawElements;
extern PFNGLENABLEPROC gload_glEnable;
extern PFNGLENABLECLIENTSTATEPROC gload_glEnableClientState;
extern PFNGLFINISHPROC gload_glFinish;
extern PFNGLFLUSHPROC gload_glFlush;
PFNGLFOGXPROC gload_glFogx;
PFNGLFOGXVPROC gload_glFogxv;
extern PFNGLFRONTFACEPROC gload_glFrontFace;
PFNGLFRUSTUMXPROC gload_glFrustumx;
extern PFNGLGETBOOLEANVPROC gload_glGetBooleanv;
extern PFNGLGETBUFFERPARAMETERIVPROC gload_glGetBufferParameteriv;
PFNGLGETCLIPPLANEXPROC gload_glGetClipPlanex;
extern PFNGLGENBUFFERSPROC gload_glGenBuffers;
extern PFNGLGENTEXTURESPROC gload_glGenTextures;
extern PFNGLGETERRORPROC gload_glGetError;
PFNGLGETFIXEDVPROC gload_glGetFixedv;
extern PFNGLGETINTEGERVPROC gload_glGetIntegerv;
PFNGLGETLIGHTXVPROC gload_glGetLightxv;
PFNGLGETMATERIALXVPROC gload_glGetMaterialxv;
extern PFNGLGETPOINTERVPROC gload_glGetPointerv;
extern PFNGLGETSTRINGPROC gload_glGetString;
extern PFNGLGETTEXENVIVPROC gload_glGetTexEnviv;
PFNGLGETTEXENVXVPROC gload_glGetTexEnvxv;
extern PFNGLGETTEXPARAMETERIVPROC gload_glGetTexParameteriv;
PFNGLGETTEXPARAMETERXVPROC gload_glGetTexParameterxv;
extern PFNGLHINTPROC gload_glHint;
extern PFNGLISBUFFERPROC gload_glIsBuffer;
extern PFNGLISENABLEDPROC gload_glIsEnabled;
extern PFNGLISTEXTUREPROC gload_glIsTexture;
PFNGLLIGHTMODELXPROC gload_glLightModelx;
PFNGLLIGHTMODELXVPROC gload_glLightModelxv;
PFNGLLIGHTXPROC gload_glLightx;
PFNGLLIGHTXVPROC gload_glLightxv;
PFNGLLINEWIDTHXPROC gload_glLineWidthx;
extern PFNGLLOADIDENTITYPROC gload_glLoadIdentity;
PFNGLLOADMATRIXXPROC gload_glLoadMatrixx;
extern PFNGLLOGICOPPROC gload_glLogicOp;
PFNGLMATERIALXPROC gload_glMaterialx;
PFNGLMATERIALXVPROC gload_glMaterialxv;
extern PFNGLMATRIXMODEPROC gload_glMatrixMode;
PFNGLMULTMATRIXXPROC gload_glMultMatrixx;
PFNGLMULTITEXCOORD4XPROC gload_glMultiTexCoord4x;
PFNGLNORMAL3XPROC gload_glNormal3x;
extern PFNGLNORMALPOINTERPROC gload_glNormalPointer;
PFNGLORTHOXPROC gload_glOrthox;
extern PFNGLPIXELSTOREIPROC gload_glPixelStorei;
PFNGLPOINTPARAMETERXPROC gload_glPointParameterx;
PFNGLPOINTPARAMETERXVPROC gload_glPointParameterxv;
PFNGLPOINTSIZEXPROC gload_glPointSizex;
PFNGLPOLYGONOFFSETXPROC gload_glPolygonOffsetx;
extern PFNGLPOPMATRIXPROC gload_glPopMatrix;
extern PFNGLPUSHMATRIXPROC gload_glPushMatrix;
extern PFNGLREADPIXELSPROC gload_glReadPixels;
PFNGLROTATEXPROC gload_glRotatex;
extern PFNGLSAMPLECOVERAGEPROC gload_glSampleCoverage;
PFNGLSAMPLECOVERAGEXPROC gload_glSampleCoveragex;
PFNGLSCALEXPROC gload_glScalex;
extern PFNGLSCISSORPROC gload_glScissor;
extern PFNGLSHADEMODELPROC gload_glShadeModel;
extern PFNGLSTENCILFUNCPROC gload_glStencilFunc;
extern PFNGLSTENCILMASKPROC gload_glStencilMask;
extern PFNGLSTENCILOPPROC gload_glStencilOp;
extern PFNGLTEXCOORDPOINTERPROC gload_glTexCoordPointer;
extern PFNGLTEXENVIPROC gload_glTexEnvi;
PFNGLTEXENVXPROC gload_glTexEnvx;
extern PFNGLTEXENVIVPROC gload_glTexEnviv;
PFNGLTEXENVXVPROC gload_glTexEnvxv;
extern PFNGLTEXIMAGE2DPROC gload_glTexImage2D;
extern PFNGLTEXPARAMETERIPROC gload_glTexParameteri;
PFNGLTEXPARAMETERXPROC gload_glTexParameterx;
extern PFNGLTEXPARAMETERIVPROC gload_glTexParameteriv;
PFNGLTEXPARAMETERXVPROC gload_glTexParameterxv;
extern PFNGLTEXSUBIMAGE2DPROC gload_glTexSubImage2D;
PFNGLTRANSLATEXPROC gload_glTranslatex;
extern PFNGLVERTEXPOINTERPROC gload_glVertexPointer;
extern PFNGLVIEWPORTPROC gload_glViewport;

#  endif /* GL_VERSION_ES_CM_1_0 */
#  if defined GL_ES_VERSION_2_0

extern PFNGLACTIVETEXTUREPROC gload_glActiveTexture;
extern PFNGLATTACHSHADERPROC gload_glAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC gload_glBindAttribLocation;
extern PFNGLBINDBUFFERPROC gload_glBindBuffer;
extern PFNGLBINDFRAMEBUFFERPROC gload_glBindFramebuffer;
extern PFNGLBINDRENDERBUFFERPROC gload_glBindRenderbuffer;
extern PFNGLBINDTEXTUREPROC gload_glBindTexture;
extern PFNGLBLENDCOLORPROC gload_glBlendColor;
extern PFNGLBLENDEQUATIONPROC gload_glBlendEquation;
extern PFNGLBLENDEQUATIONSEPARATEPROC gload_glBlendEquationSeparate;
extern PFNGLBLENDFUNCPROC gload_glBlendFunc;
extern PFNGLBLENDFUNCSEPARATEPROC gload_glBlendFuncSeparate;
extern PFNGLBUFFERDATAPROC gload_glBufferData;
extern PFNGLBUFFERSUBDATAPROC gload_glBufferSubData;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC gload_glCheckFramebufferStatus;
extern PFNGLCLEARPROC gload_glClear;
extern PFNGLCLEARCOLORPROC gload_glClearColor;
extern PFNGLCLEARDEPTHFPROC gload_glClearDepthf;
extern PFNGLCLEARSTENCILPROC gload_glClearStencil;
extern PFNGLCOLORMASKPROC gload_glColorMask;
extern PFNGLCOMPILESHADERPROC gload_glCompileShader;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC gload_glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC gload_glCompressedTexSubImage2D;
extern PFNGLCOPYTEXIMAGE2DPROC gload_glCopyTexImage2D;
extern PFNGLCOPYTEXSUBIMAGE2DPROC gload_glCopyTexSubImage2D;
extern PFNGLCREATEPROGRAMPROC gload_glCreateProgram;
extern PFNGLCREATESHADERPROC gload_glCreateShader;
extern PFNGLCULLFACEPROC gload_glCullFace;
extern PFNGLDELETEBUFFERSPROC gload_glDeleteBuffers;
extern PFNGLDELETEFRAMEBUFFERSPROC gload_glDeleteFramebuffers;
extern PFNGLDELETEPROGRAMPROC gload_glDeleteProgram;
extern PFNGLDELETERENDERBUFFERSPROC gload_glDeleteRenderbuffers;
extern PFNGLDELETESHADERPROC gload_glDeleteShader;
extern PFNGLDELETETEXTURESPROC gload_glDeleteTextures;
extern PFNGLDEPTHFUNCPROC gload_glDepthFunc;
extern PFNGLDEPTHMASKPROC gload_glDepthMask;
extern PFNGLDEPTHRANGEFPROC gload_glDepthRangef;
extern PFNGLDETACHSHADERPROC gload_glDetachShader;
extern PFNGLDISABLEPROC gload_glDisable;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC gload_glDisableVertexAttribArray;
extern PFNGLDRAWARRAYSPROC gload_glDrawArrays;
extern PFNGLDRAWELEMENTSPROC gload_glDrawElements;
extern PFNGLENABLEPROC gload_glEnable;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC gload_glEnableVertexAttribArray;
extern PFNGLFINISHPROC gload_glFinish;
extern PFNGLFLUSHPROC gload_glFlush;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC gload_glFramebufferRenderbuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC gload_glFramebufferTexture2D;
extern PFNGLFRONTFACEPROC gload_glFrontFace;
extern PFNGLGENBUFFERSPROC gload_glGenBuffers;
extern PFNGLGENERATEMIPMAPPROC gload_glGenerateMipmap;
extern PFNGLGENFRAMEBUFFERSPROC gload_glGenFramebuffers;
extern PFNGLGENRENDERBUFFERSPROC gload_glGenRenderbuffers;
extern PFNGLGENTEXTURESPROC gload_glGenTextures;
extern PFNGLGETACTIVEATTRIBPROC gload_glGetActiveAttrib;
extern PFNGLGETACTIVEUNIFORMPROC gload_glGetActiveUniform;
extern PFNGLGETATTACHEDSHADERSPROC gload_glGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC gload_glGetAttribLocation;
extern PFNGLGETBOOLEANVPROC gload_glGetBooleanv;
extern PFNGLGETBUFFERPARAMETERIVPROC gload_glGetBufferParameteriv;
extern PFNGLGETERRORPROC gload_glGetError;
extern PFNGLGETFLOATVPROC gload_glGetFloatv;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC gload_glGetFramebufferAttachmentParameteriv;
extern PFNGLGETINTEGERVPROC gload_glGetIntegerv;
extern PFNGLGETPROGRAMIVPROC gload_glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC gload_glGetProgramInfoLog;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC gload_glGetRenderbufferParameteriv;
extern PFNGLGETSHADERIVPROC gload_glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC gload_glGetShaderInfoLog;
extern PFNGLGETSHADERPRECISIONFORMATPROC gload_glGetShaderPrecisionFormat;
extern PFNGLGETSHADERSOURCEPROC gload_glGetShaderSource;
extern PFNGLGETSTRINGPROC gload_glGetString;
extern PFNGLGETTEXPARAMETERFVPROC gload_glGetTexParameterfv;
extern PFNGLGETTEXPARAMETERIVPROC gload_glGetTexParameteriv;
extern PFNGLGETUNIFORMFVPROC gload_glGetUniformfv;
extern PFNGLGETUNIFORMIVPROC gload_glGetUniformiv;
extern PFNGLGETUNIFORMLOCATIONPROC gload_glGetUniformLocation;
extern PFNGLGETVERTEXATTRIBFVPROC gload_glGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC gload_glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC gload_glGetVertexAttribPointerv;
extern PFNGLHINTPROC gload_glHint;
extern PFNGLISBUFFERPROC gload_glIsBuffer;
extern PFNGLISENABLEDPROC gload_glIsEnabled;
extern PFNGLISFRAMEBUFFERPROC gload_glIsFramebuffer;
extern PFNGLISPROGRAMPROC gload_glIsProgram;
extern PFNGLISRENDERBUFFERPROC gload_glIsRenderbuffer;
extern PFNGLISSHADERPROC gload_glIsShader;
extern PFNGLISTEXTUREPROC gload_glIsTexture;
extern PFNGLLINEWIDTHPROC gload_glLineWidth;
extern PFNGLLINKPROGRAMPROC gload_glLinkProgram;
extern PFNGLPIXELSTOREIPROC gload_glPixelStorei;
extern PFNGLPOLYGONOFFSETPROC gload_glPolygonOffset;
extern PFNGLREADPIXELSPROC gload_glReadPixels;
extern PFNGLRELEASESHADERCOMPILERPROC gload_glReleaseShaderCompiler;
extern PFNGLRENDERBUFFERSTORAGEPROC gload_glRenderbufferStorage;
extern PFNGLSAMPLECOVERAGEPROC gload_glSampleCoverage;
extern PFNGLSCISSORPROC gload_glScissor;
extern PFNGLSHADERBINARYPROC gload_glShaderBinary;
extern PFNGLSHADERSOURCEPROC gload_glShaderSource;
extern PFNGLSTENCILFUNCPROC gload_glStencilFunc;
extern PFNGLSTENCILFUNCSEPARATEPROC gload_glStencilFuncSeparate;
extern PFNGLSTENCILMASKPROC gload_glStencilMask;
extern PFNGLSTENCILMASKSEPARATEPROC gload_glStencilMaskSeparate;
extern PFNGLSTENCILOPPROC gload_glStencilOp;
extern PFNGLSTENCILOPSEPARATEPROC gload_glStencilOpSeparate;
extern PFNGLTEXIMAGE2DPROC gload_glTexImage2D;
extern PFNGLTEXPARAMETERFPROC gload_glTexParameterf;
extern PFNGLTEXPARAMETERFVPROC gload_glTexParameterfv;
extern PFNGLTEXPARAMETERIPROC gload_glTexParameteri;
extern PFNGLTEXPARAMETERIVPROC gload_glTexParameteriv;
extern PFNGLTEXSUBIMAGE2DPROC gload_glTexSubImage2D;
extern PFNGLUNIFORM1FPROC gload_glUniform1f;
extern PFNGLUNIFORM1FVPROC gload_glUniform1fv;
extern PFNGLUNIFORM1IPROC gload_glUniform1i;
extern PFNGLUNIFORM1IVPROC gload_glUniform1iv;
extern PFNGLUNIFORM2FPROC gload_glUniform2f;
extern PFNGLUNIFORM2FVPROC gload_glUniform2fv;
extern PFNGLUNIFORM2IPROC gload_glUniform2i;
extern PFNGLUNIFORM2IVPROC gload_glUniform2iv;
extern PFNGLUNIFORM3FPROC gload_glUniform3f;
extern PFNGLUNIFORM3FVPROC gload_glUniform3fv;
extern PFNGLUNIFORM3IPROC gload_glUniform3i;
extern PFNGLUNIFORM3IVPROC gload_glUniform3iv;
extern PFNGLUNIFORM4FPROC gload_glUniform4f;
extern PFNGLUNIFORM4FVPROC gload_glUniform4fv;
extern PFNGLUNIFORM4IPROC gload_glUniform4i;
extern PFNGLUNIFORM4IVPROC gload_glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC gload_glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC gload_glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC gload_glUniformMatrix4fv;
extern PFNGLUSEPROGRAMPROC gload_glUseProgram;
extern PFNGLVALIDATEPROGRAMPROC gload_glValidateProgram;
extern PFNGLVERTEXATTRIB1FPROC gload_glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC gload_glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB2FPROC gload_glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC gload_glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB3FPROC gload_glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC gload_glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB4FPROC gload_glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC gload_glVertexAttrib4fv;
extern PFNGLVERTEXATTRIBPOINTERPROC gload_glVertexAttribPointer;
extern PFNGLVIEWPORTPROC gload_glViewport;

#  endif /* GL_ES_VERSION_2_0 */
#  if defined GL_ES_VERSION_3_0

extern PFNGLREADBUFFERPROC gload_glReadBuffer;
extern PFNGLDRAWRANGEELEMENTSPROC gload_glDrawRangeElements;
extern PFNGLTEXIMAGE3DPROC gload_glTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC gload_glTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC gload_glCopyTexSubImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC gload_glCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC gload_glCompressedTexSubImage3D;
extern PFNGLGENQUERIESPROC gload_glGenQueries;
extern PFNGLDELETEQUERIESPROC gload_glDeleteQueries;
extern PFNGLISQUERYPROC gload_glIsQuery;
extern PFNGLBEGINQUERYPROC gload_glBeginQuery;
extern PFNGLENDQUERYPROC gload_glEndQuery;
extern PFNGLGETQUERYIVPROC gload_glGetQueryiv;
extern PFNGLGETQUERYOBJECTUIVPROC gload_glGetQueryObjectuiv;
extern PFNGLUNMAPBUFFERPROC gload_glUnmapBuffer;
extern PFNGLGETBUFFERPOINTERVPROC gload_glGetBufferPointerv;
extern PFNGLDRAWBUFFERSPROC gload_glDrawBuffers;
extern PFNGLUNIFORMMATRIX2X3FVPROC gload_glUniformMatrix2x3fv;
extern PFNGLUNIFORMMATRIX3X2FVPROC gload_glUniformMatrix3x2fv;
extern PFNGLUNIFORMMATRIX2X4FVPROC gload_glUniformMatrix2x4fv;
extern PFNGLUNIFORMMATRIX4X2FVPROC gload_glUniformMatrix4x2fv;
extern PFNGLUNIFORMMATRIX3X4FVPROC gload_glUniformMatrix3x4fv;
extern PFNGLUNIFORMMATRIX4X3FVPROC gload_glUniformMatrix4x3fv;
extern PFNGLBLITFRAMEBUFFERPROC gload_glBlitFramebuffer;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC gload_glRenderbufferStorageMultisample;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC gload_glFramebufferTextureLayer;
extern PFNGLMAPBUFFERRANGEPROC gload_glMapBufferRange;
extern PFNGLFLUSHMAPPEDBUFFERRANGEPROC gload_glFlushMappedBufferRange;
extern PFNGLBINDVERTEXARRAYPROC gload_glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC gload_glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC gload_glGenVertexArrays;
extern PFNGLISVERTEXARRAYPROC gload_glIsVertexArray;
extern PFNGLGETINTEGERI_VPROC gload_glGetIntegeri_v;
extern PFNGLBEGINTRANSFORMFEEDBACKPROC gload_glBeginTransformFeedback;
extern PFNGLENDTRANSFORMFEEDBACKPROC gload_glEndTransformFeedback;
extern PFNGLBINDBUFFERRANGEPROC gload_glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC gload_glBindBufferBase;
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC gload_glTransformFeedbackVaryings;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC gload_glGetTransformFeedbackVarying;
extern PFNGLVERTEXATTRIBIPOINTERPROC gload_glVertexAttribIPointer;
extern PFNGLGETVERTEXATTRIBIIVPROC gload_glGetVertexAttribIiv;
extern PFNGLGETVERTEXATTRIBIUIVPROC gload_glGetVertexAttribIuiv;
extern PFNGLVERTEXATTRIBI4IPROC gload_glVertexAttribI4i;
extern PFNGLVERTEXATTRIBI4UIPROC gload_glVertexAttribI4ui;
extern PFNGLVERTEXATTRIBI4IVPROC gload_glVertexAttribI4iv;
extern PFNGLVERTEXATTRIBI4UIVPROC gload_glVertexAttribI4uiv;
extern PFNGLGETUNIFORMUIVPROC gload_glGetUniformuiv;
extern PFNGLGETFRAGDATALOCATIONPROC gload_glGetFragDataLocation;
extern PFNGLUNIFORM1UIPROC gload_glUniform1ui;
extern PFNGLUNIFORM2UIPROC gload_glUniform2ui;
extern PFNGLUNIFORM3UIPROC gload_glUniform3ui;
extern PFNGLUNIFORM4UIPROC gload_glUniform4ui;
extern PFNGLUNIFORM1UIVPROC gload_glUniform1uiv;
extern PFNGLUNIFORM2UIVPROC gload_glUniform2uiv;
extern PFNGLUNIFORM3UIVPROC gload_glUniform3uiv;
extern PFNGLUNIFORM4UIVPROC gload_glUniform4uiv;
extern PFNGLCLEARBUFFERIVPROC gload_glClearBufferiv;
extern PFNGLCLEARBUFFERUIVPROC gload_glClearBufferuiv;
extern PFNGLCLEARBUFFERFVPROC gload_glClearBufferfv;
extern PFNGLCLEARBUFFERFIPROC gload_glClearBufferfi;
extern PFNGLGETSTRINGIPROC gload_glGetStringi;
extern PFNGLCOPYBUFFERSUBDATAPROC gload_glCopyBufferSubData;
extern PFNGLGETUNIFORMINDICESPROC gload_glGetUniformIndices;
extern PFNGLGETACTIVEUNIFORMSIVPROC gload_glGetActiveUniformsiv;
extern PFNGLGETUNIFORMBLOCKINDEXPROC gload_glGetUniformBlockIndex;
extern PFNGLGETACTIVEUNIFORMBLOCKIVPROC gload_glGetActiveUniformBlockiv;
extern PFNGLGETACTIVEUNIFORMBLOCKNAMEPROC gload_glGetActiveUniformBlockName;
extern PFNGLUNIFORMBLOCKBINDINGPROC gload_glUniformBlockBinding;
extern PFNGLDRAWARRAYSINSTANCEDPROC gload_glDrawArraysInstanced;
extern PFNGLDRAWELEMENTSINSTANCEDPROC gload_glDrawElementsInstanced;
extern PFNGLFENCESYNCPROC gload_glFenceSync;
extern PFNGLISSYNCPROC gload_glIsSync;
extern PFNGLDELETESYNCPROC gload_glDeleteSync;
extern PFNGLCLIENTWAITSYNCPROC gload_glClientWaitSync;
extern PFNGLWAITSYNCPROC gload_glWaitSync;
extern PFNGLGETINTEGER64VPROC gload_glGetInteger64v;
extern PFNGLGETSYNCIVPROC gload_glGetSynciv;
extern PFNGLGETINTEGER64I_VPROC gload_glGetInteger64i_v;
extern PFNGLGETBUFFERPARAMETERI64VPROC gload_glGetBufferParameteri64v;
extern PFNGLGENSAMPLERSPROC gload_glGenSamplers;
extern PFNGLDELETESAMPLERSPROC gload_glDeleteSamplers;
extern PFNGLISSAMPLERPROC gload_glIsSampler;
extern PFNGLBINDSAMPLERPROC gload_glBindSampler;
extern PFNGLSAMPLERPARAMETERIPROC gload_glSamplerParameteri;
extern PFNGLSAMPLERPARAMETERIVPROC gload_glSamplerParameteriv;
extern PFNGLSAMPLERPARAMETERFPROC gload_glSamplerParameterf;
extern PFNGLSAMPLERPARAMETERFVPROC gload_glSamplerParameterfv;
extern PFNGLGETSAMPLERPARAMETERIVPROC gload_glGetSamplerParameteriv;
extern PFNGLGETSAMPLERPARAMETERFVPROC gload_glGetSamplerParameterfv;
extern PFNGLVERTEXATTRIBDIVISORPROC gload_glVertexAttribDivisor;
extern PFNGLBINDTRANSFORMFEEDBACKPROC gload_glBindTransformFeedback;
extern PFNGLDELETETRANSFORMFEEDBACKSPROC gload_glDeleteTransformFeedbacks;
extern PFNGLGENTRANSFORMFEEDBACKSPROC gload_glGenTransformFeedbacks;
extern PFNGLISTRANSFORMFEEDBACKPROC gload_glIsTransformFeedback;
extern PFNGLPAUSETRANSFORMFEEDBACKPROC gload_glPauseTransformFeedback;
extern PFNGLRESUMETRANSFORMFEEDBACKPROC gload_glResumeTransformFeedback;
extern PFNGLGETPROGRAMBINARYPROC gload_glGetProgramBinary;
extern PFNGLPROGRAMBINARYPROC gload_glProgramBinary;
extern PFNGLPROGRAMPARAMETERIPROC gload_glProgramParameteri;
extern PFNGLINVALIDATEFRAMEBUFFERPROC gload_glInvalidateFramebuffer;
extern PFNGLINVALIDATESUBFRAMEBUFFERPROC gload_glInvalidateSubFramebuffer;
extern PFNGLTEXSTORAGE2DPROC gload_glTexStorage2D;
extern PFNGLTEXSTORAGE3DPROC gload_glTexStorage3D;
extern PFNGLGETINTERNALFORMATIVPROC gload_glGetInternalformativ;

#  endif /* GL_ES_VERSION_3_0 */
#  if defined GL_ES_VERSION_3_1

extern PFNGLDISPATCHCOMPUTEPROC gload_glDispatchCompute;
extern PFNGLDISPATCHCOMPUTEINDIRECTPROC gload_glDispatchComputeIndirect;
extern PFNGLDRAWARRAYSINDIRECTPROC gload_glDrawArraysIndirect;
extern PFNGLDRAWELEMENTSINDIRECTPROC gload_glDrawElementsIndirect;
extern PFNGLFRAMEBUFFERPARAMETERIPROC gload_glFramebufferParameteri;
extern PFNGLGETFRAMEBUFFERPARAMETERIVPROC gload_glGetFramebufferParameteriv;
extern PFNGLGETPROGRAMINTERFACEIVPROC gload_glGetProgramInterfaceiv;
extern PFNGLGETPROGRAMRESOURCEINDEXPROC gload_glGetProgramResourceIndex;
extern PFNGLGETPROGRAMRESOURCENAMEPROC gload_glGetProgramResourceName;
extern PFNGLGETPROGRAMRESOURCEIVPROC gload_glGetProgramResourceiv;
extern PFNGLGETPROGRAMRESOURCELOCATIONPROC gload_glGetProgramResourceLocation;
extern PFNGLUSEPROGRAMSTAGESPROC gload_glUseProgramStages;
extern PFNGLACTIVESHADERPROGRAMPROC gload_glActiveShaderProgram;
extern PFNGLCREATESHADERPROGRAMVPROC gload_glCreateShaderProgramv;
extern PFNGLBINDPROGRAMPIPELINEPROC gload_glBindProgramPipeline;
extern PFNGLDELETEPROGRAMPIPELINESPROC gload_glDeleteProgramPipelines;
extern PFNGLGENPROGRAMPIPELINESPROC gload_glGenProgramPipelines;
extern PFNGLISPROGRAMPIPELINEPROC gload_glIsProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEIVPROC gload_glGetProgramPipelineiv;
extern PFNGLPROGRAMUNIFORM1IPROC gload_glProgramUniform1i;
extern PFNGLPROGRAMUNIFORM2IPROC gload_glProgramUniform2i;
extern PFNGLPROGRAMUNIFORM3IPROC gload_glProgramUniform3i;
extern PFNGLPROGRAMUNIFORM4IPROC gload_glProgramUniform4i;
extern PFNGLPROGRAMUNIFORM1UIPROC gload_glProgramUniform1ui;
extern PFNGLPROGRAMUNIFORM2UIPROC gload_glProgramUniform2ui;
extern PFNGLPROGRAMUNIFORM3UIPROC gload_glProgramUniform3ui;
extern PFNGLPROGRAMUNIFORM4UIPROC gload_glProgramUniform4ui;
extern PFNGLPROGRAMUNIFORM1FPROC gload_glProgramUniform1f;
extern PFNGLPROGRAMUNIFORM2FPROC gload_glProgramUniform2f;
extern PFNGLPROGRAMUNIFORM3FPROC gload_glProgramUniform3f;
extern PFNGLPROGRAMUNIFORM4FPROC gload_glProgramUniform4f;
extern PFNGLPROGRAMUNIFORM1IVPROC gload_glProgramUniform1iv;
extern PFNGLPROGRAMUNIFORM2IVPROC gload_glProgramUniform2iv;
extern PFNGLPROGRAMUNIFORM3IVPROC gload_glProgramUniform3iv;
extern PFNGLPROGRAMUNIFORM4IVPROC gload_glProgramUniform4iv;
extern PFNGLPROGRAMUNIFORM1UIVPROC gload_glProgramUniform1uiv;
extern PFNGLPROGRAMUNIFORM2UIVPROC gload_glProgramUniform2uiv;
extern PFNGLPROGRAMUNIFORM3UIVPROC gload_glProgramUniform3uiv;
extern PFNGLPROGRAMUNIFORM4UIVPROC gload_glProgramUniform4uiv;
extern PFNGLPROGRAMUNIFORM1FVPROC gload_glProgramUniform1fv;
extern PFNGLPROGRAMUNIFORM2FVPROC gload_glProgramUniform2fv;
extern PFNGLPROGRAMUNIFORM3FVPROC gload_glProgramUniform3fv;
extern PFNGLPROGRAMUNIFORM4FVPROC gload_glProgramUniform4fv;
extern PFNGLPROGRAMUNIFORMMATRIX2FVPROC gload_glProgramUniformMatrix2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3FVPROC gload_glProgramUniformMatrix3fv;
extern PFNGLPROGRAMUNIFORMMATRIX4FVPROC gload_glProgramUniformMatrix4fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X3FVPROC gload_glProgramUniformMatrix2x3fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X2FVPROC gload_glProgramUniformMatrix3x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX2X4FVPROC gload_glProgramUniformMatrix2x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X2FVPROC gload_glProgramUniformMatrix4x2fv;
extern PFNGLPROGRAMUNIFORMMATRIX3X4FVPROC gload_glProgramUniformMatrix3x4fv;
extern PFNGLPROGRAMUNIFORMMATRIX4X3FVPROC gload_glProgramUniformMatrix4x3fv;
extern PFNGLVALIDATEPROGRAMPIPELINEPROC gload_glValidateProgramPipeline;
extern PFNGLGETPROGRAMPIPELINEINFOLOGPROC gload_glGetProgramPipelineInfoLog;
extern PFNGLBINDIMAGETEXTUREPROC gload_glBindImageTexture;
extern PFNGLGETBOOLEANI_VPROC gload_glGetBooleani_v;
extern PFNGLMEMORYBARRIERPROC gload_glMemoryBarrier;
extern PFNGLMEMORYBARRIERBYREGIONPROC gload_glMemoryBarrierByRegion;
extern PFNGLTEXSTORAGE2DMULTISAMPLEPROC gload_glTexStorage2DMultisample;
extern PFNGLGETMULTISAMPLEFVPROC gload_glGetMultisamplefv;
extern PFNGLSAMPLEMASKIPROC gload_glSampleMaski;
extern PFNGLGETTEXLEVELPARAMETERIVPROC gload_glGetTexLevelParameteriv;
extern PFNGLGETTEXLEVELPARAMETERFVPROC gload_glGetTexLevelParameterfv;
extern PFNGLBINDVERTEXBUFFERPROC gload_glBindVertexBuffer;
extern PFNGLVERTEXATTRIBFORMATPROC gload_glVertexAttribFormat;
extern PFNGLVERTEXATTRIBIFORMATPROC gload_glVertexAttribIFormat;
extern PFNGLVERTEXATTRIBBINDINGPROC gload_glVertexAttribBinding;
extern PFNGLVERTEXBINDINGDIVISORPROC gload_glVertexBindingDivisor;

#  endif /* GL_ES_VERSION_3_1 */
#  if defined GL_ES_VERSION_3_2

PFNGLBLENDBARRIERPROC gload_glBlendBarrier;
extern PFNGLCOPYIMAGESUBDATAPROC gload_glCopyImageSubData;
extern PFNGLDEBUGMESSAGECONTROLPROC gload_glDebugMessageControl;
extern PFNGLDEBUGMESSAGEINSERTPROC gload_glDebugMessageInsert;
extern PFNGLDEBUGMESSAGECALLBACKPROC gload_glDebugMessageCallback;
extern PFNGLGETDEBUGMESSAGELOGPROC gload_glGetDebugMessageLog;
extern PFNGLPUSHDEBUGGROUPPROC gload_glPushDebugGroup;
extern PFNGLPOPDEBUGGROUPPROC gload_glPopDebugGroup;
extern PFNGLOBJECTLABELPROC gload_glObjectLabel;
extern PFNGLGETOBJECTLABELPROC gload_glGetObjectLabel;
extern PFNGLOBJECTPTRLABELPROC gload_glObjectPtrLabel;
extern PFNGLGETOBJECTPTRLABELPROC gload_glGetObjectPtrLabel;
extern PFNGLGETPOINTERVPROC gload_glGetPointerv;
extern PFNGLENABLEIPROC gload_glEnablei;
extern PFNGLDISABLEIPROC gload_glDisablei;
extern PFNGLBLENDEQUATIONIPROC gload_glBlendEquationi;
extern PFNGLBLENDEQUATIONSEPARATEIPROC gload_glBlendEquationSeparatei;
extern PFNGLBLENDFUNCIPROC gload_glBlendFunci;
extern PFNGLBLENDFUNCSEPARATEIPROC gload_glBlendFuncSeparatei;
extern PFNGLCOLORMASKIPROC gload_glColorMaski;
extern PFNGLISENABLEDIPROC gload_glIsEnabledi;
extern PFNGLDRAWELEMENTSBASEVERTEXPROC gload_glDrawElementsBaseVertex;
extern PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC gload_glDrawRangeElementsBaseVertex;
extern PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXPROC gload_glDrawElementsInstancedBaseVertex;
extern PFNGLFRAMEBUFFERTEXTUREPROC gload_glFramebufferTexture;
PFNGLPRIMITIVEBOUNDINGBOXPROC gload_glPrimitiveBoundingBox;
extern PFNGLGETGRAPHICSRESETSTATUSPROC gload_glGetGraphicsResetStatus;
extern PFNGLREADNPIXELSPROC gload_glReadnPixels;
extern PFNGLGETNUNIFORMFVPROC gload_glGetnUniformfv;
extern PFNGLGETNUNIFORMIVPROC gload_glGetnUniformiv;
extern PFNGLGETNUNIFORMUIVPROC gload_glGetnUniformuiv;
extern PFNGLMINSAMPLESHADINGPROC gload_glMinSampleShading;
extern PFNGLPATCHPARAMETERIPROC gload_glPatchParameteri;
extern PFNGLTEXPARAMETERIIVPROC gload_glTexParameterIiv;
extern PFNGLTEXPARAMETERIUIVPROC gload_glTexParameterIuiv;
extern PFNGLGETTEXPARAMETERIIVPROC gload_glGetTexParameterIiv;
extern PFNGLGETTEXPARAMETERIUIVPROC gload_glGetTexParameterIuiv;
extern PFNGLSAMPLERPARAMETERIIVPROC gload_glSamplerParameterIiv;
extern PFNGLSAMPLERPARAMETERIUIVPROC gload_glSamplerParameterIuiv;
extern PFNGLGETSAMPLERPARAMETERIIVPROC gload_glGetSamplerParameterIiv;
extern PFNGLGETSAMPLERPARAMETERIUIVPROC gload_glGetSamplerParameterIuiv;
extern PFNGLTEXBUFFERPROC gload_glTexBuffer;
extern PFNGLTEXBUFFERRANGEPROC gload_glTexBufferRange;
extern PFNGLTEXSTORAGE3DMULTISAMPLEPROC gload_glTexStorage3DMultisample;

#  endif /* GL_ES_VERSION_3_2 */
#  if defined GL_SC_VERSION_2_0

extern PFNGLACTIVETEXTUREPROC gload_glActiveTexture;
extern PFNGLBINDBUFFERPROC gload_glBindBuffer;
extern PFNGLBINDFRAMEBUFFERPROC gload_glBindFramebuffer;
extern PFNGLBINDRENDERBUFFERPROC gload_glBindRenderbuffer;
extern PFNGLBINDTEXTUREPROC gload_glBindTexture;
extern PFNGLBLENDCOLORPROC gload_glBlendColor;
extern PFNGLBLENDEQUATIONPROC gload_glBlendEquation;
extern PFNGLBLENDEQUATIONSEPARATEPROC gload_glBlendEquationSeparate;
extern PFNGLBLENDFUNCPROC gload_glBlendFunc;
extern PFNGLBLENDFUNCSEPARATEPROC gload_glBlendFuncSeparate;
extern PFNGLBUFFERDATAPROC gload_glBufferData;
extern PFNGLBUFFERSUBDATAPROC gload_glBufferSubData;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC gload_glCheckFramebufferStatus;
extern PFNGLCLEARPROC gload_glClear;
extern PFNGLCLEARCOLORPROC gload_glClearColor;
extern PFNGLCLEARDEPTHFPROC gload_glClearDepthf;
extern PFNGLCLEARSTENCILPROC gload_glClearStencil;
extern PFNGLCOLORMASKPROC gload_glColorMask;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC gload_glCompressedTexSubImage2D;
extern PFNGLCREATEPROGRAMPROC gload_glCreateProgram;
extern PFNGLCULLFACEPROC gload_glCullFace;
extern PFNGLDEPTHFUNCPROC gload_glDepthFunc;
extern PFNGLDEPTHMASKPROC gload_glDepthMask;
extern PFNGLDEPTHRANGEFPROC gload_glDepthRangef;
extern PFNGLDISABLEPROC gload_glDisable;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC gload_glDisableVertexAttribArray;
extern PFNGLDRAWARRAYSPROC gload_glDrawArrays;
extern PFNGLDRAWRANGEELEMENTSPROC gload_glDrawRangeElements;
extern PFNGLENABLEPROC gload_glEnable;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC gload_glEnableVertexAttribArray;
extern PFNGLFINISHPROC gload_glFinish;
extern PFNGLFLUSHPROC gload_glFlush;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC gload_glFramebufferRenderbuffer;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC gload_glFramebufferTexture2D;
extern PFNGLFRONTFACEPROC gload_glFrontFace;
extern PFNGLGENBUFFERSPROC gload_glGenBuffers;
extern PFNGLGENERATEMIPMAPPROC gload_glGenerateMipmap;
extern PFNGLGENFRAMEBUFFERSPROC gload_glGenFramebuffers;
extern PFNGLGENRENDERBUFFERSPROC gload_glGenRenderbuffers;
extern PFNGLGENTEXTURESPROC gload_glGenTextures;
extern PFNGLGETATTRIBLOCATIONPROC gload_glGetAttribLocation;
extern PFNGLGETBOOLEANVPROC gload_glGetBooleanv;
extern PFNGLGETBUFFERPARAMETERIVPROC gload_glGetBufferParameteriv;
extern PFNGLGETERRORPROC gload_glGetError;
extern PFNGLGETFLOATVPROC gload_glGetFloatv;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC gload_glGetFramebufferAttachmentParameteriv;
extern PFNGLGETGRAPHICSRESETSTATUSPROC gload_glGetGraphicsResetStatus;
extern PFNGLGETINTEGERVPROC gload_glGetIntegerv;
extern PFNGLGETPROGRAMIVPROC gload_glGetProgramiv;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC gload_glGetRenderbufferParameteriv;
extern PFNGLGETSTRINGPROC gload_glGetString;
extern PFNGLGETTEXPARAMETERFVPROC gload_glGetTexParameterfv;
extern PFNGLGETTEXPARAMETERIVPROC gload_glGetTexParameteriv;
extern PFNGLGETNUNIFORMFVPROC gload_glGetnUniformfv;
extern PFNGLGETNUNIFORMIVPROC gload_glGetnUniformiv;
extern PFNGLGETUNIFORMLOCATIONPROC gload_glGetUniformLocation;
extern PFNGLGETVERTEXATTRIBFVPROC gload_glGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC gload_glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC gload_glGetVertexAttribPointerv;
extern PFNGLHINTPROC gload_glHint;
extern PFNGLISENABLEDPROC gload_glIsEnabled;
extern PFNGLLINEWIDTHPROC gload_glLineWidth;
extern PFNGLPIXELSTOREIPROC gload_glPixelStorei;
extern PFNGLPOLYGONOFFSETPROC gload_glPolygonOffset;
extern PFNGLPROGRAMBINARYPROC gload_glProgramBinary;
extern PFNGLREADNPIXELSPROC gload_glReadnPixels;
extern PFNGLRENDERBUFFERSTORAGEPROC gload_glRenderbufferStorage;
extern PFNGLSAMPLECOVERAGEPROC gload_glSampleCoverage;
extern PFNGLSCISSORPROC gload_glScissor;
extern PFNGLSTENCILFUNCPROC gload_glStencilFunc;
extern PFNGLSTENCILFUNCSEPARATEPROC gload_glStencilFuncSeparate;
extern PFNGLSTENCILMASKPROC gload_glStencilMask;
extern PFNGLSTENCILMASKSEPARATEPROC gload_glStencilMaskSeparate;
extern PFNGLSTENCILOPPROC gload_glStencilOp;
extern PFNGLSTENCILOPSEPARATEPROC gload_glStencilOpSeparate;
extern PFNGLTEXSTORAGE2DPROC gload_glTexStorage2D;
extern PFNGLTEXPARAMETERFPROC gload_glTexParameterf;
extern PFNGLTEXPARAMETERFVPROC gload_glTexParameterfv;
extern PFNGLTEXPARAMETERIPROC gload_glTexParameteri;
extern PFNGLTEXPARAMETERIVPROC gload_glTexParameteriv;
extern PFNGLTEXSUBIMAGE2DPROC gload_glTexSubImage2D;
extern PFNGLUNIFORM1FPROC gload_glUniform1f;
extern PFNGLUNIFORM1FVPROC gload_glUniform1fv;
extern PFNGLUNIFORM1IPROC gload_glUniform1i;
extern PFNGLUNIFORM1IVPROC gload_glUniform1iv;
extern PFNGLUNIFORM2FPROC gload_glUniform2f;
extern PFNGLUNIFORM2FVPROC gload_glUniform2fv;
extern PFNGLUNIFORM2IPROC gload_glUniform2i;
extern PFNGLUNIFORM2IVPROC gload_glUniform2iv;
extern PFNGLUNIFORM3FPROC gload_glUniform3f;
extern PFNGLUNIFORM3FVPROC gload_glUniform3fv;
extern PFNGLUNIFORM3IPROC gload_glUniform3i;
extern PFNGLUNIFORM3IVPROC gload_glUniform3iv;
extern PFNGLUNIFORM4FPROC gload_glUniform4f;
extern PFNGLUNIFORM4FVPROC gload_glUniform4fv;
extern PFNGLUNIFORM4IPROC gload_glUniform4i;
extern PFNGLUNIFORM4IVPROC gload_glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC gload_glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC gload_glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC gload_glUniformMatrix4fv;
extern PFNGLUSEPROGRAMPROC gload_glUseProgram;
extern PFNGLVERTEXATTRIB1FPROC gload_glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC gload_glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB2FPROC gload_glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC gload_glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB3FPROC gload_glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC gload_glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB4FPROC gload_glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC gload_glVertexAttrib4fv;
extern PFNGLVERTEXATTRIBPOINTERPROC gload_glVertexAttribPointer;
extern PFNGLVIEWPORTPROC gload_glViewport;

#  endif /* GL_SC_VERSION_2_0 */
#
#  if defined (__cplusplus)

}

#  endif /* __cplusplus */
#
# endif /* OPENGL_IMPLEMENTATION */
#endif /* _gload_h_ */
