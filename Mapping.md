For the moment, no documentation but the one from [the CGAL manual](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/contents.html) is available.
On this page we give general principals and exceptions of how the mapping between C++ and target languages is done.



# Mapping of Types and Functions #
In general all classes and functions in CGAL have template parameters. Since template parameters are not supported in all target languages of SWIG, each instantiation of a template class or function must be named. For principal kernel primitives, the choice that has been made is to propose primitives instantiated with [Exact\_predicates\_inexact\_constructions\_kernel](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Kernel_23_ref/Class_Exact_predicates_inexact_constructions_kernel.html)) and to keep their name in the target languages. For example a Java object of type `Point_2` in Java internally corresponds to a `C++` object of type `Point_2<Exact_predicates_inexact_constructions_kernel>`.  This kernel provides safe and exact predicates but no guarantee for constructions. However, for `intersection` global functions, we use filtered constructions: the intersection is computed with an exact kernel, but an embedding with floating points coordinates is returned.

SWIG has the notion of module that they document like [this](http://swig.org/Doc2.0/SWIGDocumentation.html#Modules_introduction):

_Each invocation of SWIG requires a module name to be specified. The module name is used to name the resulting target language extension module. Exactly what this means and what the name is used for depends on the target language, for example the name can define a target language namespace or merely be a useful name for naming files or helper classes. Essentially, a module comprises target language wrappers for a chosen collection of global variables/functions, structs/classes and other C/C++ types._

Internally, CGAL is organized into packages which basically gather a set of related data structures and algorithms. To increase the flexibility, we choose to represent each CGAL package as a SWIG module (see [this page](Package_wrappers_available.md) for the list of packages currently available).

# Language Independent Mappings #

## Limitations ##
  * SWIG cannot handle nested classes. A nested class in CGAL is exposed as a non-nested class in the bindings with the name prefixed by the name of the containing class, e.g., `Delaunay_triangulation_2_Vertex_handle`.
  * There is no direct support for class iterators, input iterators and output iterators so that for each target language, specific code should be written. This is currently done for Python and Java. A generic solution is provided for non-supported target languages.

## References ##
Since some target languages do not support passing primitive types (such as int, double, enum) by reference, whenever a reference to such a type is required we use a template class `Reference_wrapper<T>` which provides methods `T object()` and `void set(T)` to mimic the passing by reference mechanism. For example, in the package `Kernel` we provide a class `Ref_int` which is an integer wrapped in the aforementioned class.

## `CGAL::Object` ##
<b><a href='http://www.cgal.org/Manual/latest/doc_html/cgal_manual/STL_Extension_ref/Class_Object.html'>CGAL::Object</a></b> are implemented using template functions. As this mechanism is not available in target languages, we explicitly added functions to check the type of object stored and to retrieve it. For each object type `FOO` in the kernel, `bool is_FOO()` and `FOO get_FOO()` are available. Also an important remark is that for technical reason, the AABB\_tree package provides its own `Object` type that has the same API but is not compatible with the one from the Kernel.
> Example in Java:
```
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Segment_3;
import CGAL.Kernel.CGAL_Kernel;
import CGAL.Kernel.Object;

....

Segment_3 seg1=new Segment_3(new Point_3(-1,0,0),new Point_3(1,0,0));
Segment_3 seg2=new Segment_3(new Point_3(0,1,0),new Point_3(0,-1,0));
Object obj=CGAL_Kernel.intersection(seg1,seg2);
assert obj.is_Point_3();
System.out.println(obj.get_Point_3());
```
> Example in Python:
```
from CGAL import CGAL_Kernel
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Kernel import Triangle_2

t1=Triangle_2(Point_2(0,0),Point_2(1,0),Point_2(0,1))
t2=Triangle_2(Point_2(1,1),Point_2(1,0),Point_2(0,1))
object = CGAL_Kernel.intersection(t1,t2)
assert object.is_Segment_2()
print object.get_Segment_2()
```

## `boost::optional<T>` ##
<b><a href='http://www.boost.org/doc/libs/release/libs/optional'>boost::optional&lt;T&gt;</a></b> are usually wrapped to an object `Optional_T` and its API is `bool empty()` and `T value()` that respectively checks that the optional is empty and returns the corresponding value.

# Mappings for Java #
## SWIG Module Mapping ##
The organization into modules implies a specific way to _import_ types in Java. A class wrapped in a SWIG module named `FOO` will be inside the package `CGAL.FOO` in Java. For example, to use the `Point_2` class, one needs to do `import CGAL.Kernel.Point_2;`
Global functions wrapped in a SWIG module named `FOO` are available as static methods of the class `CGAL.FOO.CGAL_FOO`.
Example:
```
import CGAL.Kernel.Point_2;
import CGAL.Kernel.CGAL_Kernel;
  
Point_2 p1=new Point_2(0,0);
Point_2 p2=new Point_2(1,1);
double d= CGAL_Kernel.squared_distance(p1,p2);
```



The organization into modules implies a specific way to _import_ types in Java. A class wrapped in a SWIG module named `FOO` will be inside the package `CGAL.FOO` in Java, and in the module `CGAL.CGAL_FOO` in Python. For example, to use the `Point_2` class, one needs in Java to do `import CGAL.Kernel.Point_2;` and `from CGAL.CGAL_Kernel import Point_2` in Python.
Global functions wrapped in a SWIG module named `FOO` are available as static methods of the class `CGAL.FOO.CGAL_FOO` in Java and in the module `CGAL.CGAL_FOO` in Python.


## Optimization of Functions Returning Objects ##
Since each SWIG generated class has a `finalize()` method, it is costly to collect by the garbage collector. To avoid this overhead, each method returning an object generated by SWIG exits in another version where the first argument takes an already allocated Java object of the correct type and updates it.
> Example:
```
Sphere_3 s = XXX;
//you can write
Point_3 c = s.center();
//or
s.center(c);
```
## Nested Iterators ##
_Pseudo-nested_ iterator on objects of type `ObjectA` is both iterator over `ObjectA` and iterable range of `ObjectA` (that is to say these classes `implements   Iterable<ObjectA>, Iterator<ObjectA>`).
> Example:
```
Delaunay_triangulation_2 dt2=XXX;
for (Point_2 p : dt2.points()){
//do something
}
Delaunay_triangulation_2_Point_iterator points=dt2.points();
while( points.hasNext() ){
Point_2 p=points.next();
//do something
}
```
## Nested Iterators Optimization ##
For efficiency reason, each _pseudo-nested_ iterator on objects of type `ObjectA` uses a private internal member `ObjectA objectInstance` that is returned by the method `ObjectA next()`. When `next()` is called,`objectInstance`. This implies that to keep a copy of a given object during iteration, a deep copy must be done by calling `ObjectA ObjectA.clone()` or `void  ObjectA.clone(ObjectA)`. Note that the method `ObjectA slow_next()` makes such a deep copy of the next element.
> Example:
```
Point_2 escaped=null;
int i=0;
for (Point_2 p : delaunay_triangulation.points() )
{
  i+=1;
  if (i==10) escaped=p.clone();
}
//the 10th point need to be cloned to be correct
System.out.print(escaped);
```
## Output Iterators ##
Output iterator expecting object of type `ObjectA` is mapped to `Collection<ObjectA>` from `java.util`.
> Example:
```
LinkedList<Constrained_Delaunay_triangulation_2_Edge> edge_list=
  new LinkedList<Constrained_Delaunay_triangulation_2_Edge>();
Constrained_Delaunay_triangulation_2 cdt=XXX;
Constrained_Delaunay_triangulation_2_Vertex_handle v=XXX;
//collect all constrained edges incident to a vertex
cdt2.incident_constraints(v,edge_list);
```
## Input Iterators ##
Input iterator range of object of type `ObjectA` is mapped to `Iterator<ObjectA>`.
> Example:
```
List<Point_2> input_points= new LinkedList<Point_2>();
Random rand = new Random();
for (int i=0; i < 1000000; ++i){
  double x=rand.nextDouble();
  double y=rand.nextDouble();
  input_points.add(new Point_2(x,y));
}
Delaunay_triangulation_2 dt2 = new Delaunay_triangulation_2();
//insert a range of points to take advantage of the spatial sorting
dt2.insert(input_points.iterator());
```

## `std::pair<T1,T2>` ##
Getting access to first and second fields of a <b>std::pair<T1,T2></b> in SWIG is done through functions `T1 getFirst()`, `void setFirst(T1)`, `T2 getSecond()` and `void setSecond(T1)`.
Example:
```
Triangulation_2_Edge e=...
Triangulation_2_Face_handle f=e.getFirst();
```

## Enum ##
`C++` `enum` are wrapped to Java `enum`.
Example:
```
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Sphere_3;
import CGAL.Kernel.Bounded_side;

Point_3 p=new Point_3(0,0,0);
Sphere_3 s=new Sphere_3(p,1);
assert s.bounded_side(p)==Bounded_side.ON_BOUNDED_SIDE;
```

## Operators ##
Since operator overloading in java does not exist in the language, the C++ operators are mapped to the following functions in java:
  * `operator+` is mapped to `plus`
  * `operator-` is mapped to `minus`
  * `operator*` is mapped to `times`
  * `operator/` is mapped to `div`
  * `operator+=` is mapped to `iplus`
  * `operator-=` is mapped to `iminus`
  * `operator*=` is mapped to `itimes`
  * `operator/=` is mapped to `idiv`
  * `operator==` is mapped to `equals`
  * `operator!=` is mapped to `not_equals`
  * `operator<` is mapped to `lt`
  * `operator<=` is mapped to `le`
  * `operator>` is mapped to `gt`
  * `operator>=` is mapped to `ge`

# Mappings for Python #
## SWIG Module Mapping ##
The organization into modules implies a specific way to _import_ types in Python.  A class wrapped in a SWIG module named `FOO` will be in the module `CGAL.CGAL_FOO` in Python. For example, to use the `Point_2` class, one needs `from CGAL.CGAL_Kernel import Point_2`. Global functions wrapped in a SWIG module named `FOO` are available in the module `CGAL.CGAL_FOO`.
Example:
```
import CGAL.Kernel.Point_2;
import CGAL.Kernel.CGAL_Kernel;
  
Point_2 p1=new Point_2(0,0);
Point_2 p2=new Point_2(1,1);
double d= CGAL_Kernel.squared_distance(p1,p2);
```

## Nested Iterators ##
_Pseudo-nested_ iterator are mapped to Python iterator.
> Example:
```
dt2=CGAL_Triangulation_2.Delaunay_triangulation_2()
for v in dt2.finite_vertices():
  print v.point()
```
## Output Iterators ##
Output iterators are mapped to Python list.
> Example:
```
edges=[]
cdt2=CGAL_Triangulation_2.Constrained_Delaunay_triangulation_2()
v=CGAL_Triangulation_2.Constrained_Delaunay_triangulation_2_Vertex_handle()
//collect all constrained edges incident to a vertex
cdt2.incident_constraints(v,edges);
```
## Input Iterators ##
Input iterators are mapped to Python iterators and iterable container.
> Example:
```
lst=[]
lst.append(CGAL_Kernel.Point_2(0,0))
lst.append(CGAL_Kernel.Point_2(1,0))
lst.append(CGAL_Kernel.Point_2(1,1))
dt2=CGAL_Triangulation_2.Delaunay_triangulation_2()
//insert a range of points to take advantage of the spatial sorting
dt2.insert(lst)
//or
dt2.insert(lst.__iter()__)
```

## `std::pair<T1,T2>` ##
Getting access to first and second fields of a <b>std::pair<T1,T2></b> in SWIG is done thanks to the tuple interface in Python.
Example:
```
e=Triangulation_3_Edge(....)
#access to the coordinates of the opposite vertex to the edge. 
e[0].vertex(e[1]).point()
```

## Enum ##
`C++` `enum` are wrapped to constant in the module they are defined.
Example:
```
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Sphere_3
from CGAL.CGAL_Kernel import ON_BOUNDED_SIDE

p=Point_3(0,0,0)
s=Sphere_3(p,1)
assert s.bounded_side(p)==ON_BOUNDED_SIDE
```