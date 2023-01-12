#define _GLFW_WAYLAND
#include <glmc/glmc.h>
#include "application.h"


int main(int argc, char *argv[]) {
    t_application *p_application = application_new("particle simulation");
    application_run(p_application);
    application_destroy(p_application);
    return 0;
}
