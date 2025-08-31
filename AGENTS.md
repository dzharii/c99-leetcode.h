## Agent Instructions
- Directive 1: Scope and goal. This repository maintains a single header file `c99-leetcode.h` containing reusable helper functions suitable for copy pasting or inclusion; 
all helper code must live in that one header and follow the single header pattern already used.

- Directive 2: Work queue. The only trigger for work is the file to todo.md; if to todo.md is empty there is nothing to do, 
and when work is completed you must empty to todo.md.

- Directive 3: Intake. When to todo.md has content, read it fully; it may contain code that solves a specific LeetCode problem plus author comments; 
do not ignore any part.

- Directive 4: Identify reusable helpers. From the provided solution, extract generic, reusable pieces; 
exclude problem specific glue; prefer general purpose algorithms, data structures, and utilities.

- Directive 5: Integrate into c99-leetcode.h. Insert the reusable pieces into c99-leetcode.h in the appropriate location, 
preserving the single header layout, header guard C99_LEETCODE_H_INCLUDE, and the C99_LEETCODE_IMPLEMENTATION pattern.

- Directive 6: API and naming. Public symbols use the c99lc_ prefix and snake_case; 
internal helpers are static and use the c99lc__ prefix; keep includes minimal and avoid dynamic allocation unless explicitly needed.

- Directive 7: Language and quality. Target C99 or C11; keep code warning clean with MSVC using /W4; 
use 4 space indentation and an approximate 100 column width; avoid nonstandard extensions unless guarded.

- Directive 8: Configuration macros. Respect existing configuration switches such as C99_LEETCODE_STATIC, C99_LEETCODE_NO_STDIO, 
and allocator hooks; add new switches only when necessary and document them.

- Directive 9: Documentation. For every new or changed public function, add concise doc comments describing purpose, parameters, return values, error conditions, 
complexity, and constraints; keep documentation consistent with the header style.

- Directive 10: Tests from solutions. If to todo.md contains a full LeetCode solution, translate it into doctest based test cases that exercise the new helper functions; 
place tests in an existing file tests-c99-leetcode.cpp.

- Directive 11: Tests when no solution provided. If to todo.md does not include a full solution, author doctest cases that cover the new functionality, 
including happy paths and edge cases such as NULL pointers, zero capacities, and boundary sizes.

- Directive 12: Test invariants. Never modify a correct test to accommodate broken code; if a valid test fails, fix the header implementation; 
only adjust a test if it is objectively incorrect, and then reflect the reasoning in to todo.md before clearing it.

- Directive 15: Run tests. Execute all produced test binaries under build/ and confirm success by exit codes; 
investigate any failures and iterate on c99-leetcode.h until tests pass.

- Directive 16: Cleanup. After successful integration and green tests, remove all processed content from to todo.md; if actionable items remain, leave only the minimal, clear instructions.

- Directive 17: Git and safety. Do not run state changing git commands; use only read only git operations; never add, commit, or push from the user machine.

- Directive 18: Nonfunctional constraints. Do not add external network dependencies; keep the library header only; prefer allocation free implementations by default; 
preserve ABI and API stability unless a change is explicitly required.

- Directive 19: Final self check. Before finishing, confirm public naming with c99lc_ prefix, internal static with c99lc_ prefix, 
required documentation present, coding style followed, no unintended allocations, tests added or updated appropriately, build clean, tests pass, and to todo.md emptied.

# Repository Guidelines

## Project Structure & Module Organization
- `c99-leetcode.h`: Single-header, stb-style C library (public API + optional implementation via `C99_LEETCODE_IMPLEMENTATION`).
- `tests-c99-leetcode.cpp`: Doctest-based tests; uses vendored `external/doctest/doctest.h`.
- Build tooling: `do-build.ps1`/`do-build.cmd` compile `nob.c` → `nob.exe`, then build tests into `build/`.
- `build/`: Compiled artifacts (test executables). No runtime assets.

## Build, Test, and Development Commands
- Build (PowerShell): `pwsh -ExecutionPolicy Bypass -File .\do-build.ps1 -Arch x64`
  - Sets up MSVC environment, builds `nob.exe`, and compiles tests into `build\`.
- Quick build (CMD wrapper): ` .\do-build.cmd`
- Run tests: execute produced binaries in `build\` (example: ` .\build\<test>.exe`). Exit code reflects success/failure.

## Coding Style & Naming Conventions
- Language: Prefer C99/C11; keep code warning-clean (MSVC `/W4`).
- Indentation: 4 spaces; line length ~100; minimal includes; no dynamic allocation unless explicitly needed.
- API naming: `c99lc_` prefix for public symbols, `snake_case` (e.g., `c99lc_helloworld_into`).
- Internal/private: `static` with `c99lc__` prefix. Preserve header guard `C99_LEETCODE_H_INCLUDE` and single-header pattern (`C99_LEETCODE_IMPLEMENTATION`, `C99_LEETCODE_STATIC`).

## Testing Guidelines
- Framework: [doctest] via `external/doctest/doctest.h`; tests live in `*.cpp` and include `c99-leetcode.h`.
- Structure: Use `TEST_CASE("...")`; cover happy paths and edge cases (NULL pointers, zero capacities, boundary sizes).
- Naming: Prefer `tests-<area>.cpp` or `<feature>_tests.cpp`.
- Running: Build, then run any `build\*.exe`. If adding new test files, ensure the build (via `nob.exe`) picks them up; update `nob.c` if required.

## Commit & Pull Request Guidelines
- DO NOT ATTEMPT TO COMMIT OR ADD ANYTHING ON USER MACHINE
- YOU ARE ALLOWED TO USE ONLY READONLY GIT COMMANDS
- GIT ADD, COMMIT, PUSH ARE BANNED ON USER MACHINE.


## Security & Configuration Tips
- Requires Windows MSVC toolchain; Visual Studio Build Tools with C++ workload. The script auto-detects `VsDevCmd.bat`; pass `-Arch x64|x86|arm64` as needed.
- No external network dependencies; doctest is vendored. Keep contributions header-only unless justified.

