#define GLOAD_IMPLEMENTATION
#include "./../../gload.h"


int main(void) {
    if (!gloadLoadGL()) { return (1); }

    /* ... */

    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* ... */

    gloadUnloadGL();

    return (0);
}
