#ifndef INCLUDE_OPENCGE_FIELDS_POINT_3D_HPP_
#define INCLUDE_OPENCGE_FIELDS_POINT_3D_HPP_

namespace OpenCGE
{
  namespace Field
  {
    struct Point3D
    {
      Point3D(float x, float y, float z)
        : x(x), y(y), z(z) {};
      float x;
      float y;
      float z;
    };
  }
}

#endif /* INCLUDE_OPENCGE_FIELDS_POINT_3D_HPP_ */
