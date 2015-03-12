<b>Examples of using cgal-bindings:</b>
Here is a collection of examples illustrating how CGAL modules can be used. All examples are available in Java and in Python, as well as in C++ through a link to the CGAL documentation page.



# Triangulation\_2: Example of a Basic Triangulation #
The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Triangulation_2/Chapter_main.html#Subsection_36.4.2).

## triangulation\_prog1.java ##
```
import CGAL.Kernel.Point_2;
import CGAL.Triangulation_2.Triangulation_2;
import CGAL.Triangulation_2.Triangulation_2_Vertex_circulator;
import CGAL.Triangulation_2.Triangulation_2_Vertex_handle;
import java.util.Vector;

public class triangulation_prog1 {
  public static void main(String arg[]){
    Vector<Point_2> points=new Vector<Point_2>(8);
    points.add( new Point_2(1,0) );
    points.add( new Point_2(3,2) );
    points.add( new Point_2(4,5) );
    points.add( new Point_2(9,8) );
    points.add( new Point_2(7,4) );
    points.add( new Point_2(5,2) );
    points.add( new Point_2(6,3) );
    points.add( new Point_2(10,1) );
      
    Triangulation_2 t=new Triangulation_2();
    t.insert(points.iterator());

    Triangulation_2_Vertex_circulator vc = t.incident_vertices(t.infinite_vertex());
    
    if (vc.hasNext()) {
      Triangulation_2_Vertex_handle done = vc.next().clone();
      Triangulation_2_Vertex_handle iter=null;
      do {
        iter=vc.next();
        System.out.println(iter.point());
      }while(!iter.equals(done));
    }    
  }
}
```
## triangulation\_prog1.py ##
```
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Triangulation_2 import Triangulation_2
from CGAL.CGAL_Triangulation_2 import Triangulation_2_Vertex_circulator
from CGAL.CGAL_Triangulation_2 import Triangulation_2_Vertex_handle

points=[]
points.append( Point_2(1,0) )
points.append( Point_2(3,2) )
points.append( Point_2(4,5) )
points.append( Point_2(9,8) )
points.append( Point_2(7,4) )
points.append( Point_2(5,2) )
points.append( Point_2(6,3) )
points.append( Point_2(10,1) )
  
t=Triangulation_2()
t.insert(points)

vc = t.incident_vertices(t.infinite_vertex())

if vc.hasNext():
  done = vc.next();
  iter=Triangulation_2_Vertex_handle()
  while(1):
    iter=vc.next()
    print iter.point()
    if iter == done:
      break
```

# Triangulation\_3: Basic Example #
The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Triangulation_3/Chapter_main.html#Subsection_38.5.1).

## simple\_triangulation\_3.java ##
```
import CGAL.Kernel.Point_3;
import CGAL.Triangulation_3.Delaunay_triangulation_3;
import CGAL.Triangulation_3.Delaunay_triangulation_3_Cell_handle;
import CGAL.Triangulation_3.Delaunay_triangulation_3_Vertex_handle;
import CGAL.Triangulation_3.Locate_type;
import CGAL.Triangulation_3.Ref_Locate_type_3;
import CGAL.Kernel.Ref_int;
import java.util.LinkedList;
import java.util.Vector;


public class simple_triangulation_3 {
  public static void main(String arg[]){
    LinkedList<Point_3> L=new LinkedList<Point_3>();
    L.add( new Point_3(0,0,0) );
    L.add( new Point_3(1,0,0) );
    L.add( new Point_3(0,1,0) );
    
    Delaunay_triangulation_3 T= new Delaunay_triangulation_3(L.iterator());
    
    int n=T.number_of_vertices();

    Vector<Point_3> V=new Vector<Point_3>(3);
    V.add(  new Point_3(0,0,1) );
    V.add(  new Point_3(1,1,1) );
    V.add(  new Point_3(2,2,2) );

    n = n + T.insert(V.iterator());
    
    assert n==6;
    assert T.is_valid();

    Ref_Locate_type_3 lt=new Ref_Locate_type_3();
    Ref_int li=new Ref_int();
    Ref_int lj=new Ref_int();
    Point_3 p=new Point_3(0,0,0);
   
    Delaunay_triangulation_3_Cell_handle c = T.locate(p, lt, li, lj);
    assert lt.object() == Locate_type.VERTEX;
    assert c.vertex(li.object()).point().equals(p);
    
    
    Delaunay_triangulation_3_Vertex_handle v = c.vertex( (li.object()+1)&3 );
    Delaunay_triangulation_3_Cell_handle nc = c.neighbor(li.object());

    Ref_int nli=new Ref_int();
    assert nc.has_vertex( v, nli );

    T.write_to_file("output");

    Delaunay_triangulation_3 T1 = new Delaunay_triangulation_3();
    T1.read_from_file("output");

    assert T1.is_valid();
    assert T1.number_of_vertices() == T.number_of_vertices();
    assert T1.number_of_cells() == T.number_of_cells();
  }
}
```
## simple\_triangulation\_3.py ##
```
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Triangulation_3 import Delaunay_triangulation_3
from CGAL.CGAL_Triangulation_3 import Delaunay_triangulation_3_Cell_handle
from CGAL.CGAL_Triangulation_3 import Delaunay_triangulation_3_Vertex_handle
from CGAL.CGAL_Triangulation_3 import VERTEX
from CGAL.CGAL_Triangulation_3 import Ref_Locate_type_3
from CGAL.CGAL_Kernel import Ref_int



L=[]
L.append( Point_3(0,0,0) )
L.append( Point_3(1,0,0) )
L.append( Point_3(0,1,0) )

T=Delaunay_triangulation_3(L)

n=T.number_of_vertices()

V=[]
V.append( Point_3(0,0,1) )
V.append( Point_3(1,1,1) )
V.append( Point_3(2,2,2) )

n = n + T.insert(V)

assert n==6
assert T.is_valid()

lt=Ref_Locate_type_3()
li=Ref_int()
lj=Ref_int()
p=Point_3(0,0,0)

c = T.locate(p, lt, li, lj)
assert lt.object() == VERTEX
assert c.vertex(li.object()).point() == p


v = c.vertex( (li.object()+1)&3 )
nc = c.neighbor(li.object())

nli=Ref_int()
assert nc.has_vertex( v, nli )

T.write_to_file("output")

T1 = Delaunay_triangulation_3()
T1.read_from_file("output")

assert T1.is_valid()
assert T1.number_of_vertices() == T.number_of_vertices()
assert T1.number_of_cells() == T.number_of_cells()

```

# Triangulation\_3: Regular Triangulation #
The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Triangulation_3/Chapter_main.html#Subsection_38.5.7).

## regular\_3.java ##
```
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Weighted_point_3;
import CGAL.Triangulation_3.Regular_triangulation_3;
import java.util.Vector;


public class regular_3 {
  public static void main(String arg[]){

    // generate points on a 3D grid
    Vector<Weighted_point_3> P=new Vector<Weighted_point_3>();

    int number_of_points = 0;

    for (int z=0 ; z<5 ; z++)
      for (int y=0 ; y<5 ; y++)
        for (int x=0 ; x<5 ; x++) {
            Point_3 p = new Point_3(x, y, z);
            double w = (x+y-z*y*x)*2.0; // let's say this is the weight.
            P.add(new Weighted_point_3(p, w));
            ++number_of_points;
        }

    Regular_triangulation_3 T = new Regular_triangulation_3();

    // insert all points in a row (this is faster than one insert() at a time).
    T.insert (P.iterator());

    assert T.is_valid();
    assert T.dimension() == 3;

    System.out.println("Number of vertices : " + T.number_of_vertices());

    // removal of all vertices
    int count = 0;
    while (T.number_of_vertices() > 0) {
        T.remove (T.finite_vertices().next());
        ++count;
    }

    assert count == number_of_points;
  }
}
```
## regular\_3.py ##
```
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Weighted_point_3
from CGAL.CGAL_Triangulation_3 import Regular_triangulation_3

# generate points on a 3D grid
P=[]

number_of_points = 0

for z in range(0,5):
  for y in range(0,5):
    for x in range(0,5):
        p = Point_3(x, y, z)
        w = (x+y-z*y*x)*2.0 # let's say this is the weight.
        P.append(Weighted_point_3(p, w))
        number_of_points+=1

T = Regular_triangulation_3()

# insert all points in a row (this is faster than one insert() at a time).
T.insert (P)

assert T.is_valid()
assert T.dimension() == 3

print "Number of vertices : ", T.number_of_vertices()

#removal of all vertices
count = 0
while T.number_of_vertices() > 0:
  T.remove (T.finite_vertices().next())
  count+=1


assert count == number_of_points
```



# Mesh\_2: Example Using the Global Function #

The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Mesh_2/Chapter_main.html#Subsection_46.2.5).

## mesh\_global.java ##
```
import CGAL.Kernel.Point_2;
import CGAL.Mesh_2.Mesh_2_Constrained_Delaunay_triangulation_2;
import CGAL.Mesh_2.Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle;
import CGAL.Mesh_2.Delaunay_mesh_size_criteria_2;
import CGAL.Mesh_2.CGAL_Mesh_2;


public class mesh_global {
  public static void main(String arg[]){
    Mesh_2_Constrained_Delaunay_triangulation_2 cdt=new Mesh_2_Constrained_Delaunay_triangulation_2();
    
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle va = cdt.insert(new Point_2(-4,0));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vb = cdt.insert(new Point_2(0,-1));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vc = cdt.insert(new Point_2(4,0));
    Mesh_2_Constrained_Delaunay_triangulation_2_Vertex_handle vd = cdt.insert(new Point_2(0,1));
    cdt.insert(new Point_2(2, 0.6));

    cdt.insert_constraint(va, vb);
    cdt.insert_constraint(vb, vc);
    cdt.insert_constraint(vc, vd);
    cdt.insert_constraint(vd, va);

    System.out.println("Number of vertices: "+cdt.number_of_vertices());

    System.out.println("Meshing the triangulation...");

    CGAL_Mesh_2.refine_Delaunay_mesh_2(cdt, new Delaunay_mesh_size_criteria_2(0.125, 0.5));

    System.out.println("Number of vertices: "+cdt.number_of_vertices());
  }
}
```
## mesh\_global.py ##
```
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Mesh_2 import Mesh_2_Constrained_Delaunay_triangulation_2
from CGAL.CGAL_Mesh_2 import Delaunay_mesh_size_criteria_2
from CGAL import CGAL_Mesh_2


cdt=Mesh_2_Constrained_Delaunay_triangulation_2()

va = cdt.insert(Point_2(-4,0))
vb = cdt.insert(Point_2(0,-1))
vc = cdt.insert(Point_2(4,0))
vd = cdt.insert(Point_2(0,1))
cdt.insert(Point_2(2, 0.6))

cdt.insert_constraint(va, vb)
cdt.insert_constraint(vb, vc)
cdt.insert_constraint(vc, vd)
cdt.insert_constraint(vd, va)

print "Number of vertices: ", cdt.number_of_vertices()

print "Meshing the triangulation..."

CGAL_Mesh_2.refine_Delaunay_mesh_2(cdt,Delaunay_mesh_size_criteria_2(0.125, 0.5))

print "Number of vertices: ", cdt.number_of_vertices()
```

# Mesh\_2: Making a Triangulation Conforming Delaunay and Then Conforming Gabriel #

The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Mesh_2/Chapter_main.html#Subsection_46.1.3).

## conforming.java ##
```
import CGAL.Kernel.Point_2;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2;
import CGAL.Triangulation_2.Constrained_Delaunay_triangulation_2_Vertex_handle;
import CGAL.Mesh_2.CGAL_Mesh_2;


public class conforming {
  public static void main(String arg[]){
    Constrained_Delaunay_triangulation_2 cdt=new Constrained_Delaunay_triangulation_2();

    // construct a constrained triangulation
    Constrained_Delaunay_triangulation_2_Vertex_handle va = cdt.insert(new Point_2( 5., 5.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vb = cdt.insert(new Point_2(-5., 5.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vc = cdt.insert(new Point_2( 4., 3.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vd = cdt.insert(new Point_2( 5.,-5.));
    Constrained_Delaunay_triangulation_2_Vertex_handle ve = cdt.insert(new Point_2( 6., 6.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vf = cdt.insert(new Point_2(-6., 6.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vg = cdt.insert(new Point_2(-6.,-6.));
    Constrained_Delaunay_triangulation_2_Vertex_handle vh = cdt.insert(new Point_2( 6.,-6.));

    cdt.insert_constraint(va,vb);
    cdt.insert_constraint(vb,vc);
    cdt.insert_constraint(vc,vd);
    cdt.insert_constraint(vd,va);
    cdt.insert_constraint(ve,vf);
    cdt.insert_constraint(vf,vg);
    cdt.insert_constraint(vg,vh);
    cdt.insert_constraint(vh,ve);

    System.out.println("Number of vertices before: "+ cdt.number_of_vertices());

    // make it conforming Delaunay
    CGAL_Mesh_2.make_conforming_Delaunay_2(cdt);

    System.out.println("Number of vertices after make_conforming_Delaunay_2: "+cdt.number_of_vertices());

    // then make it conforming Gabriel
    CGAL_Mesh_2.make_conforming_Gabriel_2(cdt);

    System.out.println("Number of vertices after make_conforming_Gabriel_2: "+cdt.number_of_vertices() );
  }
}
```
## conforming.py ##
```
from CGAL.CGAL_Kernel import Point_2
from CGAL.CGAL_Triangulation_2 import Constrained_Delaunay_triangulation_2
from CGAL.CGAL_Triangulation_2 import Constrained_Delaunay_triangulation_2_Vertex_handle
from CGAL import CGAL_Mesh_2

cdt=Constrained_Delaunay_triangulation_2()

#construct a constrained triangulation
va = cdt.insert(Point_2( 5., 5.))
vb = cdt.insert(Point_2(-5., 5.))
vc = cdt.insert(Point_2( 4., 3.))
vd = cdt.insert(Point_2( 5.,-5.))
ve = cdt.insert(Point_2( 6., 6.))
vf = cdt.insert(Point_2(-6., 6.))
vg = cdt.insert(Point_2(-6.,-6.))
vh = cdt.insert(Point_2( 6.,-6.))

cdt.insert_constraint(va,vb)
cdt.insert_constraint(vb,vc)
cdt.insert_constraint(vc,vd)
cdt.insert_constraint(vd,va)
cdt.insert_constraint(ve,vf)
cdt.insert_constraint(vf,vg)
cdt.insert_constraint(vg,vh)
cdt.insert_constraint(vh,ve)

print "Number of vertices before: ", cdt.number_of_vertices()

#make it conforming Delaunay
CGAL_Mesh_2.make_conforming_Delaunay_2(cdt)

print "Number of vertices after make_conforming_Delaunay_2: ", cdt.number_of_vertices()

#then make it conforming Gabriel
CGAL_Mesh_2.make_conforming_Gabriel_2(cdt)

print "Number of vertices after make_conforming_Gabriel_2: ", cdt.number_of_vertices()
```

# Mesh\_3: 3D Polyhedral Domains #

The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Mesh_3/Chapter_main.html#Subsection_50.3.2).

## mesh\_polyhedral\_domain.java ##
```
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Mesh_3.Mesh_3_Complex_3_in_triangulation_3;
import CGAL.Mesh_3.CGAL_Mesh_3;
import CGAL.Mesh_3.Polyhedral_mesh_domain_3;
import CGAL.Mesh_3.Mesh_3_parameters;
import CGAL.Mesh_3.Default_mesh_criteria;


public class mesh_polyhedral_domain{
  public static void main(String arg[]){
    // Create input polyhedron
    Polyhedron_3 polyhedron=new Polyhedron_3("../data/elephant.off");

    // Create domain
    Polyhedral_mesh_domain_3 domain= new Polyhedral_mesh_domain_3(polyhedron);
    Mesh_3_parameters params=new Mesh_3_parameters();
    
    // Mesh criteria (no cell_size set)
    Default_mesh_criteria criteria = new  Default_mesh_criteria();
    criteria.facet_angle(25).facet_size(0.15).facet_distance(0.008).cell_radius_edge_ratio(3);
    // Mesh generation
    Mesh_3_Complex_3_in_triangulation_3 c3t3=CGAL_Mesh_3.make_mesh_3(domain,criteria,params);

    // Output
    c3t3.output_to_medit("out_1.mesh");

    // Set tetrahedron size (keep cell_radius_edge), ignore facets
    Default_mesh_criteria new_criteria = new Default_mesh_criteria();
    new_criteria.cell_radius_edge_ratio(3).cell_size(0.03);
    
    // Mesh refinement
    CGAL_Mesh_3.refine_mesh_3(c3t3, domain, new_criteria,params);

    // Output
    c3t3.output_to_medit("out_2.mesh");

  }
}
```
## mesh\_polyhedral\_domain.py ##
```
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_Mesh_3 import Mesh_3_Complex_3_in_triangulation_3
from CGAL.CGAL_Mesh_3 import Polyhedral_mesh_domain_3
from CGAL.CGAL_Mesh_3 import Mesh_3_parameters
from CGAL.CGAL_Mesh_3 import Default_mesh_criteria
from CGAL import CGAL_Mesh_3

#Create input polyhedron
polyhedron=Polyhedron_3("../data/elephant.off")

#Create domain
domain = Polyhedral_mesh_domain_3(polyhedron)
params = Mesh_3_parameters()

#Mesh criteria (no cell_size set)
criteria = Default_mesh_criteria()
criteria.facet_angle(25).facet_size(0.15).facet_distance(0.008).cell_radius_edge_ratio(3)
#Mesh generation
c3t3=CGAL_Mesh_3.make_mesh_3(domain,criteria,params)

#Output
c3t3.output_to_medit("out_1.mesh")

#Set tetrahedron size (keep cell_radius_edge), ignore facets
new_criteria = Default_mesh_criteria()
new_criteria.cell_radius_edge_ratio(3).cell_size(0.03)

#Mesh refinement
CGAL_Mesh_3.refine_mesh_3(c3t3, domain, new_criteria,params)

#Output
c3t3.output_to_medit("out_2.mesh")
```

# Polyhedron\_3: Example Using Euler Operators to Build a Cube #

The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Polyhedron/Chapter_main.html#Subsection_25.3.7).

## polyhedron\_prog\_cube.java ##
```
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Halfedge_handle;
import CGAL.Kernel.Point_3;


public class polyhedron_prog_cube{
  
  public static Polyhedron_3_Halfedge_handle make_cube_3(Polyhedron_3 P){
    // appends a cube of size [0,1]^3 to the polyhedron P.
    assert P.is_valid();
    Polyhedron_3_Halfedge_handle h = P.make_tetrahedron( new Point_3( 1, 0, 0),
                                                         new Point_3( 0, 0, 1),
                                                         new Point_3( 0, 0, 0),
                                                         new Point_3( 0, 1, 0));
    Polyhedron_3_Halfedge_handle g = h.next().opposite().next();
    P.split_edge( h.next() );
    P.split_edge( g.next() );
    P.split_edge( g );
    h.next().vertex().set_point( new Point_3( 1, 0, 1) );
    g.next().vertex().set_point( new Point_3( 0, 1, 1) );
    g.opposite().vertex().set_point( new Point_3( 1, 1, 0) );
    Polyhedron_3_Halfedge_handle f = P.split_facet(g.next(),g.next().next().next());
    Polyhedron_3_Halfedge_handle e = P.split_edge(f);
    e.vertex().set_point( new Point_3( 1, 1, 1) );
    P.split_facet( e, f.next().next());
    assert P.is_valid();
    return h;
  }
  
  public static void main(String arg[]){
    Polyhedron_3 P=new Polyhedron_3();
    Polyhedron_3_Halfedge_handle h = make_cube_3(P);
    assert !P.is_tetrahedron(h);
  }
}
```
## polyhedron\_prog\_cube.py ##
```
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3_Halfedge_handle
from CGAL.CGAL_Kernel import Point_3



def make_cube_3(P):
  # appends a cube of size [0,1]^3 to the polyhedron P.
  assert P.is_valid()
  h = P.make_tetrahedron(Point_3( 1, 0, 0),Point_3( 0, 0, 1),Point_3( 0, 0, 0),Point_3( 0, 1, 0))
  g = h.next().opposite().next()
  P.split_edge( h.next() )
  P.split_edge( g.next() )
  P.split_edge( g )
  h.next().vertex().set_point( Point_3( 1, 0, 1) )
  g.next().vertex().set_point( Point_3( 0, 1, 1) )
  g.opposite().vertex().set_point( Point_3( 1, 1, 0) )
  f = P.split_facet(g.next(),g.next().next().next())
  e = P.split_edge(f)
  e.vertex().set_point( Point_3( 1, 1, 1) )
  P.split_facet( e, f.next().next())
  assert P.is_valid()
  return h

P = Polyhedron_3()
h = make_cube_3(P)
assert not P.is_tetrahedron(h)
```

# Polyhedron\_3: partial interface to  Polyhedron\_incremental\_builder #
For more details, see the documentation of the
[Polyhedron\_incremental\_builder](http://www.cgal.org/Manual/3.2/doc_html/cgal_manual/Polyhedron_ref/Class_Polyhedron_incremental_builder_3.html).

What is missing are the functions `add_facet, test_facet, vertex, error, check_unconnected_vertices, remove_unconnected_vertices`. Also the functions `add_vertex, begin_facet, end_facet` have `void` as return type.

## Polyhedron\_incremental\_builder.java ##
```
import CGAL.Kernel.Point_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_modifier;
import CGAL.Polyhedron_3.Modifier_mode;


public class Polyhedron_incremental_builder {
  public static void main(String arg[]){
    //declare a modifier interfacing the incremental_builder
    Polyhedron_modifier m = new Polyhedron_modifier();

    //define a triangle
    m.begin_surface(3,1);
    m.add_vertex(new Point_3(0,0,0));
    m.add_vertex(new Point_3(0,1,0));
    m.add_vertex(new Point_3(1,0.5,0));
    m.begin_facet();
    m.add_vertex_to_facet(0);
    m.add_vertex_to_facet(1);
    m.add_vertex_to_facet(2);
    m.end_facet();


    Polyhedron_3 P = new Polyhedron_3();
    //create the triangle in P
    P.delegate(m);
    System.out.println("(v,f,e) = "+P.size_of_vertices()+" "+P.size_of_facets()+" "+P.size_of_halfedges()/2);
    
    //clear the modifier
    m.clear();

    //define another triangle, reusing vertices in the polyhedron
    m.begin_surface(1,1,0,Modifier_mode.ABSOLUTE_INDEXING);
    m.add_vertex(new Point_3(-1,0.5,0));
    m.begin_facet();
    m.add_vertex_to_facet(1);
    m.add_vertex_to_facet(0);
    m.add_vertex_to_facet(3);
    m.end_facet();

    //append a triangle incident to the existing one
    P.delegate(m);
    System.out.println("(v,f,e) = "+P.size_of_vertices()+" "+P.size_of_facets()+" "+P.size_of_halfedges()/2);
    if (! P.is_valid() )
      throw new AssertionError("Polyhedron is not_valid");
  }
};
```
## Polyhedron\_incremental\_builder.py ##
```
from CGAL.CGAL_Polyhedron_3 import Polyhedron_modifier
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_Polyhedron_3 import ABSOLUTE_INDEXING
from CGAL.CGAL_Kernel import Point_3

#declare a modifier interfacing the incremental_builder
m=Polyhedron_modifier()

#define a triangle
m.begin_surface(3,1)
m.add_vertex(Point_3(0,0,0))
m.add_vertex(Point_3(0,1,0))
m.add_vertex(Point_3(1,0.5,0))
m.begin_facet()
m.add_vertex_to_facet(0)
m.add_vertex_to_facet(1)
m.add_vertex_to_facet(2)
m.end_facet()


P=Polyhedron_3()
#create the triangle in P
P.delegate(m)
print "(v,f,e) = ", P.size_of_vertices(), P.size_of_facets(), P.size_of_halfedges()/2

#clear the modifier
m.clear()

#define another triangle, reusing vertices in the polyhedron
m.begin_surface(1,1,0,ABSOLUTE_INDEXING)
m.add_vertex(Point_3(-1,0.5,0))
m.begin_facet()
m.add_vertex_to_facet(1)
m.add_vertex_to_facet(0)
m.add_vertex_to_facet(3)
m.end_facet()

#append a triangle incident to the existing one
P.delegate(m)
print "(v,f,e) = ", P.size_of_vertices(), P.size_of_facets(), P.size_of_halfedges()/2

assert P.is_valid()
```

# AABB\_tree: Tree of Triangles, for Intersection and Distance Queries #

The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/AABB_tree/Chapter_main.html#Subsection_63.3.1).

## AABB\_triangle\_3\_example.java ##
```
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Triangle_3;
import CGAL.Kernel.Ray_3;
import CGAL.AABB_tree.AABB_tree_Triangle_3_soup;
import java.util.Vector;


public class AABB_triangle_3_example {
  public static void main(String arg[]){

    Point_3 a = new Point_3(1.0, 0.0, 0.0);
    Point_3 b = new Point_3(0.0, 1.0, 0.0);
    Point_3 c = new Point_3(0.0, 0.0, 1.0);
    Point_3 d = new Point_3(0.0, 0.0, 0.0);

    Vector<Triangle_3> triangles = new Vector<Triangle_3>();
    triangles.add(new Triangle_3(a,b,c));
    triangles.add(new Triangle_3(a,b,d));
    triangles.add(new Triangle_3(a,d,c));

    // constructs AABB tree
    AABB_tree_Triangle_3_soup tree = new AABB_tree_Triangle_3_soup(triangles.iterator());

    // counts #intersections
    Ray_3 ray_query =  new Ray_3(a,b);
    System.out.println(tree.number_of_intersected_primitives(ray_query)+" intersections(s) with ray query");

    // compute closest point and squared distance
    Point_3 point_query = new Point_3(2.0, 2.0, 2.0);
    Point_3 closest_point = tree.closest_point(point_query);
    double sqd = tree.squared_distance(point_query);
    System.out.println("squared distance: "+ sqd);
  }
}
```
## AABB\_triangle\_3\_example.py ##
```
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Triangle_3
from CGAL.CGAL_Kernel import Ray_3
from CGAL.CGAL_AABB_tree import AABB_tree_Triangle_3_soup

a = Point_3(1.0, 0.0, 0.0)
b = Point_3(0.0, 1.0, 0.0)
c = Point_3(0.0, 0.0, 1.0)
d = Point_3(0.0, 0.0, 0.0)

triangles = []
triangles.append(Triangle_3(a,b,c))
triangles.append(Triangle_3(a,b,d))
triangles.append(Triangle_3(a,d,c))

# constructs AABB tree
tree = AABB_tree_Triangle_3_soup(triangles)

# counts #intersections
ray_query =  Ray_3(a,b)
print tree.number_of_intersected_primitives(ray_query), " intersections(s) with ray query"

# compute closest point and squared distance
point_query = Point_3(2.0, 2.0, 2.0)
closest_point = tree.closest_point(point_query)
sqd = tree.squared_distance(point_query)
print "squared distance: ", sqd
```


# AABB\_tree: Tree of Polyhedron Triangle Facets for Intersection Queries #

The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/AABB_tree/Chapter_main.html#Subsection_63.3.2).

## AABB\_polyhedron\_facet\_intersection\_example.java ##
```
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Kernel.Plane_3;
import CGAL.Kernel.Segment_3;
import CGAL.Polyhedron_3.Polyhedron_3;
import CGAL.Polyhedron_3.Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.AABB_tree_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.Optional_Object_and_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.Object_and_Polyhedron_3_Facet_handle;
import CGAL.AABB_tree.Object;
import java.util.LinkedList;


public class AABB_polyhedron_facet_intersection_example{
  public static void main(String arg[]){
    Point_3 p=new Point_3(1.0, 0.0, 0.0);
    Point_3 q=new Point_3(0.0, 1.0, 0.0);
    Point_3 r=new Point_3(0.0, 0.0, 1.0);
    Point_3 s=new Point_3(0.0, 0.0, 0.0);
    Polyhedron_3 polyhedron=new Polyhedron_3();
    polyhedron.make_tetrahedron(p, q, r, s);

    // constructs AABB tree
    AABB_tree_Polyhedron_3_Facet_handle tree = new AABB_tree_Polyhedron_3_Facet_handle(polyhedron.facets());

    // constructs segment query
    Point_3 a = new Point_3(-0.2, 0.2, -0.2);
    Point_3 b = new Point_3(1.3, 0.2, 1.3);
    Segment_3 segment_query=new Segment_3(a,b);

    // tests intersections with segment query
    if(tree.do_intersect(segment_query))
      System.out.println("intersection(s)");
    else
      System.out.println("no intersection");

    // computes #intersections with segment query
    System.out.println(tree.number_of_intersected_primitives(segment_query)+" intersection(s)");

    // computes first encountered intersection with segment query
    // (generally a point)
    Optional_Object_and_Polyhedron_3_Facet_handle intersection =
        tree.any_intersection(segment_query);
    if(!intersection.empty())
    {
      // gets intersection object
      Object_and_Polyhedron_3_Facet_handle op = intersection.value();
      Object object = op.getFirst();
      if(object.is_Point_3())
        System.out.println("intersection object is a point");
    }

    // computes all intersections with segment query (as pairs object - primitive_id)
    LinkedList<Object_and_Polyhedron_3_Facet_handle> intersections=new LinkedList<Object_and_Polyhedron_3_Facet_handle>();
    tree.all_intersections(segment_query,intersections);

    // computes all intersected primitives with segment query as primitive ids
    LinkedList<Polyhedron_3_Facet_handle> primitives = new LinkedList<Polyhedron_3_Facet_handle>();
    tree.all_intersected_primitives(segment_query,primitives);

    // constructs plane query
    Vector_3 vec = new Vector_3(0.0,0.0,1.0);
    Plane_3 plane_query = new Plane_3(a,vec);

    // computes first encountered intersection with plane query
    // (generally a segment)
    intersection = tree.any_intersection(plane_query);
    if(!intersection.empty())
    {
      // gets intersection object
      Object_and_Polyhedron_3_Facet_handle op = intersection.value();
      Object object = op.getFirst();
      if(object.is_Segment_3())
        System.out.println("intersection object is a segment");
    }
  }
}
```
## AABB\_polyhedron\_facet\_intersection\_example.py ##
```
from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Kernel import Plane_3
from CGAL.CGAL_Kernel import Segment_3
from CGAL.CGAL_Polyhedron_3 import Polyhedron_3
from CGAL.CGAL_AABB_tree import AABB_tree_Polyhedron_3_Facet_handle

p=Point_3(1.0, 0.0, 0.0)
q=Point_3(0.0, 1.0, 0.0)
r=Point_3(0.0, 0.0, 1.0)
s=Point_3(0.0, 0.0, 0.0)
polyhedron = Polyhedron_3()
polyhedron.make_tetrahedron(p, q, r, s)

#constructs AABB tree
tree = AABB_tree_Polyhedron_3_Facet_handle(polyhedron.facets())

#constructs segment query
a = Point_3(-0.2, 0.2, -0.2)
b = Point_3(1.3, 0.2, 1.3)
segment_query=Segment_3(a,b)

#tests intersections with segment query
if tree.do_intersect(segment_query):
  print "intersection(s)"
else:
  print "no intersection"

#computes #intersections with segment query
print tree.number_of_intersected_primitives(segment_query)," intersection(s)"

#computes first encountered intersection with segment query
#(generally a point)
intersection = tree.any_intersection(segment_query)
if not intersection.empty():
  #gets intersection object
  op = intersection.value()
  object = op[0]
  if object.is_Point_3():
    print "intersection object is a point"


#computes all intersections with segment query (as pairs object - primitive_id)
intersections=[]
tree.all_intersections(segment_query,intersections)

#computes all intersected primitives with segment query as primitive ids
primitives = []
tree.all_intersected_primitives(segment_query,primitives)

#constructs plane query
vec = Vector_3(0.0,0.0,1.0)
plane_query = Plane_3(a,vec)

#computes first encountered intersection with plane query
#(generally a segment)
intersection = tree.any_intersection(plane_query)
if not intersection.empty():
  #gets intersection object
  op = intersection.value()
  object = op[0]
  if object.is_Segment_3():
    print "intersection object is a segment"
```

# Halfedge Data Structures:  Example Using the Halfedge Iterator #

The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/HalfedgeDS/Chapter_main.html#Subsection_26.3.6).

## hds\_prog\_halfedge\_iterator.java ##
```
import CGAL.HalfedgeDS.HalfedgeDS;
import CGAL.HalfedgeDS.HalfedgeDS_decorator;
import CGAL.HalfedgeDS.HDS_Halfedge_handle;

public class hds_prog_halfedge_iterator {
  public static void main(String arg[]){
    HalfedgeDS hds = new HalfedgeDS();
    HalfedgeDS_decorator decorator = new HalfedgeDS_decorator(hds);
    decorator.create_loop();
    decorator.create_segment();
    assert decorator.is_valid();
    
    int n = 0;
    for ( HDS_Halfedge_handle h : hds.halfedges() ){ ++n; }
    assert n == 4;
  }
}
```
## hds\_prog\_halfedge\_iterator.py ##
```
from CGAL.CGAL_HalfedgeDS import HalfedgeDS
from CGAL.CGAL_HalfedgeDS import HalfedgeDS_decorator
from CGAL.CGAL_HalfedgeDS import HDS_Halfedge_handle


hds = HalfedgeDS()
decorator = HalfedgeDS_decorator(hds)
decorator.create_loop()
decorator.create_segment()
assert decorator.is_valid()

n = 0
for h in hds.halfedges():
  n+=1

assert n == 4
```


# Point Set Processing : Outlier Removal #

The cpp version is available [here](http://www.cgal.org/Manual/latest/doc_html/cgal_manual/Point_set_processing_3/Chapter_main.html#Section_58.4).

## remove\_outliers\_example.java ##
```
import CGAL.Kernel.Point_3;
import CGAL.Kernel.Vector_3;
import CGAL.Point_set_processing_3.CGAL_Point_set_processing_3;

import java.util.Vector;



public class remove_outliers_example{
  public static void main(String arg[]){
    
  // Reads a .xyz point set file in points[].
  Vector<Point_3> points = new Vector<Point_3>();
  if ( !CGAL_Point_set_processing_3.read_xyz_points("../data/oni.xyz",points) )
  {
    System.out.println("Error: cannot read file ../data/oni.xyz");
    return;
  }

  // Removes outliers using erase-remove idiom.
  double removed_percentage = 5.0; // percentage of points to remove
  int nb_neighbors = 24; // considers 24 nearest neighbor points
  int new_size=CGAL_Point_set_processing_3.remove_outliers(points.iterator(), nb_neighbors, removed_percentage);
  points.setSize(new_size);
  }
}

```
## remove\_outliers\_example.py ##
```
from sys import exit

from CGAL.CGAL_Kernel import Point_3
from CGAL.CGAL_Kernel import Vector_3
from CGAL.CGAL_Point_set_processing_3 import *

#Reads a .xyz point set file in points[].
points=[];
  
if not read_xyz_points("../data/oni.xyz", points):
  print "Error: cannot read file data/oni.xyz"
  exit()

#Removes outliers using erase-remove idiom.
removed_percentage = 5.0; # percentage of points to remove
nb_neighbors = 24; # considers 24 nearest neighbor points
new_size=remove_outliers(points, nb_neighbors, removed_percentage)
points=points[0:new_size]
```