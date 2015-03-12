# Prerequisites #
  * [CGAL](http://www.cgal.org) version 4.0 or newer,
> > Check-out the [CGAL installation manual pages](http://www.cgal.org/Manual/latest/doc_html/installation_manual/contents.html) for more details.
  * [SWIG](http://www.swig.org) version 2.0 or newer,
> > Check-out the [SWIG web site](http://www.swig.org) for more details.
  * [Cmake](http://www.cmake.org) version 2.8 or newer.
  * For compiling the Java bindings, a JDK must be available. One tested is the Sun JDK 6.26.
  * For compiling the Python bindings, Python development tools must be available. It has been tested with Python 2.6.

# Step-By-Step Installation Guide #
  1. Check-out the git repository at https://code.google.com/p/cgal-bindings/
  1. cmake configuration:
    1. Choose between in-source and out-of-source build:
> > > An _in-source_ build indicates the fact that the CGAL bindings are compiled from the root of the project (that is to say from `CGAL_BINDINGS_ROOT`). In that case all temporary files are generated in the source tree. This prevents building the cgal bindings with different compiler options for example. An _out-of-source_ build indicates the fact that the CGAL bindings are compiled from a dedicated directory (for example `CGAL_BINDINGS_ROOT/build/CGAL-3.9_release`). This type of build allows several different builds.
    1. cmake options:
    * CGAL\_DIR
> > > Path to the file CGALConfig.cmake created when installing/compiling CGAL.
> > > For Debian and Ubunto packages, it is `/usr/lib/CGAL` for example.
    * `BUILD_JAVA = [ON/OFF]`:
> > > States whether Java bindings should be generated. The default value is `ON`.
    * `BUILD_PYTHON = [ON/OFF]`:
> > > States whether Python bindings should be generated. The default value is `ON`.
    * `JAVA_OUTDIR_PREFIX`:
> > > Java specific files output directory prefix; Java files and libraries will be respectively generated into `JAVA_OUTDIR_PREFIX/CGAL` and `JAVA_OUTDIR_PREFIX/lib` directories. The default is `CURRENT_PATH/build-java`.
    * `PYTHON_OUTDIR_PREFIX`:
> > > Python specific files output directory prefix; Python files and libraries will be generated into `PYTHON_OUTDIR_PREFIX/CGAL` directory. The default is `CURRENT_PATH/build-python`.
    * `COMMON_LIBRARIES_PATH`:
> > > Path where libraries common to all target languages are generated. The default is `CURRENT_PATH/lib`.
  1. If the cmake configuration step went fine, it only remains to compile.

**Full example:**
```
> git clone https://code.google.com/p/cgal-bindings
> cd cgal-bindings
> mkdir build/CGAL-3.9_release -p
> cd build/CGAL-3.9_release
> cmake -DCGAL_DIR=/usr/lib/CGAL -DBUILD_PYTHON=OFF -DJAVA_OUTDIR_PREFIX=../../examples/java ../..
> make -j 4
> cd ../../examples/java
> javac test_kernel.java
> export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:lib
> java test_kernel
... output of the example test_kernel.java ...
```