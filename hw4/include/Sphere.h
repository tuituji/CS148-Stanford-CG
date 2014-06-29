#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer148 {
  class Sphere : public Shape {
  public:
      Sphere(Eigen::Vector3d &center, double radius) : c(center), r(radius) {}
  
      virtual HitRecord intersect(const Ray &ray);
      
  private:
      Eigen::Vector3d c;
      double r;
  };
}

#endif
