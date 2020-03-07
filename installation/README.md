# Install LLVM

## Download LLVM from github
git clone https://github.com/llvm/llvm-project.git

## Config and build LLVM and Clang
* ``cd llvm-project``

* ``mkdir build``

* ``cd build``

* ``cmake -G <generator> [options] ../llvm``

  For example, if you want to build only LLVM and Clang on Linux with release version, you can run: 
  * ``cmake -G "Unix Makefiles" -DLLVM_ENABLE_PROJECTS="clang" -DCMAKE_BUILD_TYPE=Release``

  Some common build system generators are:

  * ``Ninja`` --- for generating [Ninja](https://ninja-build.org)
    build files. Most llvm developers use Ninja.
  * ``Unix Makefiles`` --- for generating make-compatible parallel makefiles.
  * ``Visual Studio`` --- for generating Visual Studio projects and
    solutions.
  * ``Xcode`` --- for generating Xcode projects.

  Some Common options:

  * ``-DLLVM_ENABLE_PROJECTS='...'`` --- semicolon-separated list of the LLVM
    sub-projects you'd like to additionally build. Can include any of: clang,
    clang-tools-extra, libcxx, libcxxabi, libunwind, lldb, compiler-rt, lld,
    polly, or debuginfo-tests.

    For example, to build LLVM, Clang, libcxx, and libcxxabi, use
    ``-DLLVM_ENABLE_PROJECTS="clang;libcxx;libcxxabi"``.

  * ``-DCMAKE_INSTALL_PREFIX=directory`` --- Specify for *directory* the full
    path name of where you want the LLVM tools and libraries to be installed
    (default ``/usr/local``).

  * ``-DCMAKE_BUILD_TYPE=type`` --- Valid options for *type* are Debug,
    Release, RelWithDebInfo, and MinSizeRel. Default is Debug.

  * ``-DLLVM_ENABLE_ASSERTIONS=On`` --- Compile with assertion checks enabled
    (default is Yes for Debug builds, No for all other build types).

* ``cmake --build . [-- [options] <target>]`` or your build system specified above
  directly.

  * The default target (i.e. ``ninja`` or ``make``) will build all of LLVM.

  * The ``check-all`` target (i.e. ``ninja check-all``) will run the
    regression tests to ensure everything is in working order.

  * CMake will generate targets for each tool and library, and most
    LLVM sub-projects generate their own ``check-<project>`` target.

  * Running a serial build will be **slow**.  To improve speed, try running a
    parallel build.  That's done by default in Ninja; for ``make``, use the option
    ``-j NNN``, where ``NNN`` is the number of parallel jobs, e.g. the number of
    CPUs you have.
