One big advantage of the current design is the simple way a user can define its own wrapper of classes and functions. It is convenient to have access to the complete C++ API of a CGAL class to write a prototype and quickly get a result. However, as soon as higher performance and code optimization are needed, writing a dedicated small C++ wrapper might be more efficient. In this page, we try to show how easy it is to make such a wrapper.

# Create your Own User Package #
The directory `User_packages` is meant to host packages that are specifically written for one purpose. The idea is to offer a way to easily build your own wrapper that will make a task specific to your application. For that purpose, there is a conditional compilation if a `CMakeLists.txt` is present in the `User_packages` directory. This `CMakeLists.txt` must basically contains one line per user package (`add_subdirectory(Dummy)`).

Here is a step-by-step guide on how to create your own package. In this example, we create a package called `Dummy`.

  1. Create a directory in `CGAL_BINDINGS_ROOT/SWIG_CGAL/User_packages` with the name of your wrapper. Note that if you want your package to be in another SCM repository, a symbolic link to a directory can be used instead.
```
   > cd cgal-bindings
   > mkdir SWIG_CGAL/User_packages/Dummy
```
  1. Create the package `CMakeLists.txt` with the CMake macros indicating for which language the bindings should be generated.
```
> cat SWIG_CGAL/User_packages/Dummy/CMakeLists.txt
     ADD_SWIG_CGAL_JAVA_MODULE  (Dummy)
     ADD_SWIG_CGAL_PYTHON_MODULE  (Dummy)
```
  1. Create the SWIG interface file for your wrapper in the newly created directory, with the same named but prefixed with `CGAL_`.
```
   > touch SWIG_CGAL/User_packages/My_wrapper/CGAL_My_wrapper.i
```
> In this example, we suppose that we want to define a global function that modifies a Polyhedron\_3.
```
> cat -n SWIG_CGAL/User_packages/My_wrapper/CGAL_My_wrapper.i
     1	%module CGAL_Dummy
     2	
     3	%include "SWIG_CGAL/common.i"
     4	Decl_void_type()
     5	SWIG_CGAL_add_java_loadLibrary(CGAL_Dummy)
     6	
     7	
     8	%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"
     9	
    10	%{
    11	  #include <SWIG_CGAL/Polyhedron_3/all_includes.h>
    12	  #include <SWIG_CGAL/Kernel/Point_3.h>
    13	%}
    14	
    15	SWIG_CGAL_import_Polyhedron_3_SWIG_wrapper
    16	
    17	%pragma(java) jniclassimports=%{import CGAL.Polyhedron_3.Polyhedron_3;%}
    18	%pragma(java) moduleimports  =%{import CGAL.Polyhedron_3.Polyhedron_3;%}
    19	
    20	%inline 
    21	%{
    22	  void modify_polyhedron(Polyhedron_3_SWIG_wrapper& polyhedron){
    23	    polyhedron.make_tetrahedron(Point_3::cpp_base(0,0,0),
    24	                                Point_3::cpp_base(0,0,1),
    25	                                Point_3::cpp_base(0,1,0),
    26	                                Point_3::cpp_base(1,1,1));
    27	  }
    28	%}

```
> > Comments:
      * `%module` declares the name of the SWIG module (the package name)
      * line 3 to 5 are import of SWIG and C++ macros. See [this page](Package_organization.md) for more details.
      * `%import "SWIG_CGAL/Polyhedron_3/CGAL_Polyhedron_3.i"` import in SWIG all classes that have been exposed to the target language in the package `Polyhedron_3`. The `C++` style include enclosed in the `%{ %}` block is for the generated wrapper to have access to `C++` types used when wrapping the package `Polyhedron_3`.
      * `SWIG_CGAL_import_Polyhedron_3_SWIG_wrapper` is a call to a SWIG macro that is imported from `CGAL_Polyhedron_3.i`. It makes the identifier `Polyhedron_3_SWIG_wrapper` representing the exposed class `Polyhedron_3` of target languages. That way you don't need to know about the template instantiation of the Polyhedron wrapper, but simply use `Polyhedron_3_SWIG_wrapper`. This is working for any classes exposed in target languages. If a class `Foo` is exposed, then the macro `SWIG_CGAL_import_Foo_3_SWIG_wrapper` is available and defines `Foo_3_SWIG_wrapper`. If the type need to be used inside a typemap, the following SWIG macro `Foo_3_SWIG_wrapper_for_typemap` is also defined after the import of the interface file.
      * The `%pragma` instructions are to place imports specific to Java, so that the class Polyhedron\_3 is known.
      * the `C++` code behind the exposed function `modify_polyhedron` is the one enclosed in the last `%{ %}` block. The `%inline` key word is saying to SWIG to parse the code in the `%{ %}` block and expose what is inside. Note that if you want to put the code in the file "impl.h", you could alternatively add:
```
%include "SWIG_CGAL/User_packages/Dummy/impl.h" //this one is for SWIG
%{
#include <SWIG_CGAL/User_packages/Dummy/impl.h> //this one is for the C++ wrapper
%}
```

---


In Python, you can then do:
```
>>> from CGAL import CGAL_Dummy
>>> from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
>>> p=Polyhedron_3()
>>> p.size_of_vertices()
0
>>> CGAL_Dummy.modify_polyhedron(p)
>>> p.size_of_vertices()
4
```


---


In Java, you can write this for the same output:
```
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Dummy.CGAL_Dummy;

public class test_dummy {
  public static void main(String arg[]){
    Polyhedron_3 p=new Polyhedron_3();
    System.out.println(p.size_of_vertices());
    CGAL_Dummy.modify_polyhedron(p);
    System.out.println(p.size_of_vertices());
  }
};
```