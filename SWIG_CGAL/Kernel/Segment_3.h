#ifndef SWIG_CGAL_KERNEL_SEGMENT_3_H
#define SWIG_CGAL_KERNEL_SEGMENT_3_H

#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_3.h>
#include <SWIG_CGAL/Kernel/Line_3.h>


#ifndef SWIG
#define NO_SWIG_OR_PYTHON
#else
#ifdef SWIGPYTHON
#define NO_SWIG_OR_PYTHON
#endif
#endif

class Line_3;

class Segment_3{
  EPIC_Kernel::Segment_3 data;
public:
  #ifndef SWIG
  typedef EPIC_Kernel::Segment_3 cpp_base;
  const cpp_base& get_data() const;
  cpp_base& get_data_ref();
  Segment_3(const cpp_base& s);
  #endif

  Segment_3();
  Segment_3(const Point_3& p1, const Point_3& p2);

  Point_3 source();
  Point_3 target();
  Line_3 supporting_line(); 

  bool equals(const Segment_3&);
  
  std::string toString();

  //the C++ object is shared between target languages
  //and must be mapped only for python
  #ifdef NO_SWIG_OR_PYTHON
  bool __ne__(const Segment_3&);
  #endif
};

#endif //SWIG_CGAL_KERNEL_SEGMENT_3_H
