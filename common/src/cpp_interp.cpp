#include "cpp_interp.hpp"
#include "rs274ngc_interp.hh"
#include "interp_return.hh"

#include <unistd.h>


namespace {
Interp interp;
bool was_init{false};
ocn::CurvStruct curv;
char buffer[1024];
}

int cpp_interp_loaded() {
    return was_init;
}

int cpp_interp_init(const char* filename) {
    char* path = getcwd(buffer, sizeof(buffer));
    if (!path) {
        fprintf(stderr, "cpp_interp_init: Failed to get current path\n");
        return 0;
    }

    fprintf(stderr, "cpp_interp_init, pwd: '%s', trying to open '%s'\n", buffer, filename);
    if (interp.init() != INTERP_OK) {
        fprintf(stderr, "cpp_interp_init: Failed to open\n");
        return 0;
    }
	was_init = (interp.open(filename) == INTERP_OK);
    
    return was_init;
}

int cpp_interp_read(ocn::CurvStruct* curv_struct) {
    curv.Type = ocn::CurveType_None;
    int status = 0;
    status = interp.read();

    if (status == INTERP_ENDFILE || status == INTERP_EXIT) {
        return 0;
    }
    else if (status > INTERP_MIN_ERROR) {
        fprintf(stderr, "ERROR(read): %s\n", interp.getSavedError());
        return 0;
    }

	status = interp.execute();
    if (status > INTERP_MIN_ERROR) {
        fprintf(stderr, "ERROR(execute): %s\n", interp.getSavedError());
        return 0;
    }
    ocn::CopyCurvStruct(&curv, curv_struct);
    // *curv_struct = curv;
   //printf("cpp_interp_read: type = %d\n", curv_struct->Type);
    return 1;
}

void push_curv_struct(const ocn::CurvStruct* curv_struct) {
    // printf("push_curv_struct: type = %d\n", curv_struct->Type);
    //curv = *curv_struct;
	ocn::CopyCurvStruct(curv_struct, &curv);
}
