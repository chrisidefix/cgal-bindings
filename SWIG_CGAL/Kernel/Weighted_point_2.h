// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_WEIGHTED_POINT_2_H
#define SWIG_CGAL_KERNEL_WEIGHTED_POINT_2_H

#include <sstream>
#include <SWIG_CGAL/Kernel/typedefs.h>
#include <SWIG_CGAL/Kernel/Point_2.h>

#include <CGAL/Weighted_point.h>

class SWIG_CGAL_KERNEL_DECL Weighted_point_2{
  CGAL::Weighted_point<EPIC_Kernel::Point_2,double> data;
public:
  #ifndef SWIG
  typedef CGAL::Weighted_point<EPIC_Kernel::Point_2,double> cpp_base;
  const cpp_base& get_data() const {return data;}
        cpp_base& get_data()       {return data;}
  Weighted_point_2(const cpp_base& base):data(base){}
  #endif

//Creation
  Weighted_point_2():data(){}
  Weighted_point_2(double x,double y):data(x,y){}
  Weighted_point_2(const Point_2& p,double w):data(p.get_data(),w){}
//Operations
  double weight() const {return data.weight();}
  double x() const {return data.x();}
  double y() const {return data.y();}
  Point_2 point() const {return Point_2(data.point());}
//equality functions
  bool equals(const Weighted_point_2& p){
    return data==p.get_data();
  }
  #if !defined SWIG || defined SWIGPYTHON
  bool __ne__(const Weighted_point_2& p){return !equals(p);}
  #endif
//I/O
  std::string toString(){
    std::stringstream sstr;
    sstr << data;
    return sstr.str();
  }
//Deep copy
  typedef Weighted_point_2 Self;
  Self deepcopy() const {return Self(data);}
  void deepcopy(const Self& other){data=other.get_data();}
};

#endif //SWIG_CGAL_KERNEL_WEIGHTED_POINT_2_H
