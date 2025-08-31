#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

int main(int argc, char **argv)
{
    NOB_GO_REBUILD_URSELF(argc, argv);
    // All artifacts are placed directly into `build` directory
    const char *build_dir = "build";
    const char *tests_time_out_path = nob_temp_sprintf("%s/tests-c99-leetcode", build_dir);

    mkdir_if_not_exists(build_dir);

    // Build C++ doctest-based unit tests using async procs
    Nob_Procs procs = {0};

    Cmd tcmd = {0};
    nob_cc(&tcmd);
    nob_cc_flags(&tcmd);
#if defined(_MSC_VER) && !defined(__clang__)
    cmd_append(&tcmd, "/std:c++20");
    cmd_append(&tcmd, nob_temp_sprintf("/Fo:%s\\", build_dir));
#else
    cmd_append(&tcmd, "-std=c++20");
#endif
    nob_cc_output(&tcmd, tests_time_out_path);
    nob_cc_inputs(&tcmd, "tests-c99-leetcode.cpp");
    if (!nob_cmd_run(&tcmd, .async = &procs)) return 1;

    if (!nob_procs_flush(&procs)) return 1;

    // Run tests (sequentially); could also use .async similarly
#if defined(_WIN32)
    const char *exe_suffix = ".exe";
#else
    const char *exe_suffix = "";
#endif

    Cmd run = {0};
    cmd_append(&run, nob_temp_sprintf("%s%s", tests_time_out_path, exe_suffix));
    if (!cmd_run(&run)) return 1;

    return 0;
}
