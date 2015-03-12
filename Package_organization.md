On this page we give the details of how each module is organized. Addition of new CGAL packages should follow these recommendations.

# Why SWIG #
SWIG has the ability to read C++ code and to automatically generate bindings for several target languages such as Java, Python, C#, ...

SWIG cannot directly parse the template-heavy CGAL code and hand-written wrapper classes are used to generate the bindings. Every wrapper class maps to a specific CGAL class and forwards functions to an internally stored CGAL object. Only the documented interface of a CGAL class is exposed through the wrapper to the target language and internal, yet public, member functions of CGAL classes are inaccessible. This is more convenient than using the SWIG specific ignore directives.


# Common structure recommendation  of a package #

Each CGAL package corresponds to a directory in `SWIG_CGAL`.
For each `FOO` package, we used the following internal structure:

## `CMakeLists.txt` ##
This file indicates how the package should be built. One line in the global `CMakeLists.txt` (`add_subdirectory(SWIG_CGAL/FOO)`) indicates that this package should be considered when building the bindings. Currently only Python and Java build are supported.
CMake macros are provided to ease the building:
  * `ADD_SWIG_CGAL_LIBRARY(CGAL_FOO_cpp file1.cpp file2.cpp ... filen.cpp)`
> This macro creates a target named `CGAL_FOO_cpp` that contains all symbols for objects defined in `file1.cpp`, `file2.cpp`, `...`, `filen.cpp`. These contains objects that are shared between target languages. Note that if few functions that are target language dependent need to be added to such an object, one can use the `%extend` SWIG commands in the main interface file as it is done for example for the class `Polygon_2` in the `Kernel` package.
  * `ADD_SWIG_CGAL_JAVA_MODULE  (FOO CGAL_FOO_cpp CGAL_BAR_cpp)`
> indicates to SWIG that a Java bindings should be created for the package FOO. It creates a target library `CGAL_FOO` that is linked with libraries `CGAL_FOO_cpp` and `CGAL_BAR_cpp`. This is this library that will be loaded from Java.
  * `ADD_SWIG_CGAL_PYTHON_MODULE(FOO CGAL_FOO_cpp CGAL_BAR_cpp)`
> indicates to SWIG that a Python bindings should be created for the package FOO. It creates a target library `CGAL_FOO` that is linked with libraries `CGAL_FOO_cpp` and `CGAL_BAR_cpp`. This is this library that will be loaded from Python.
## `CGAL_FOO.i` ##
This file is the main SWIG interface file that is used to generate the bindings for the package. Here is what the top of this file looks like:
```
%module CGAL_FOO //name of the package

%include "SWIG_CGAL/common.i" //include globally defined SWIG macros
Decl_void_type()              //define C++ macros for exporting symbols (mainly for building shared libraries on Windows)

SWIG_CGAL_add_java_loadLibrary(CGAL_FOO) //SWIG macro to automatically load the library CGAL_FOO when doing an import in Java.

%import  "SWIG_CGAL/Common/Macros.h" //C++ macros that helps wrapping CGAL classes
```

## `typedefs.h` ##
This file contains all the typedef of all CGAL types that are used in the package.
## `all_includes.h` ##
This file contains include directive for all wrapper classes defined for this package.
## `TARGET_extensions.i` ##
TARGET should be replaced by the target language (thus only Python or Java currently). It contains all extensions specially done for a specific target language. Such a file is optional.
## `config.h` ##
This file contains all macros that are responsible for conditional compilation and wrapping. Such a file is optional.