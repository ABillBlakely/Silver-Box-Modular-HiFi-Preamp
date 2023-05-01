#include <RuntimeError.h>

static const char * message = "No Error";
static int parameter = -1;
static const char * file = 0;
static int line = -1;


void RuntimeError(const char * m, int p, const char * f, int l)
{    
    message = m;
    parameter = p;
    file = f;
    line = l;
}
