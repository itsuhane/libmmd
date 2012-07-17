
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

//// class Model::Part

//// omember: material
inline const Material&
Model::Part::GetMaterial() const {
    return material_;
}

inline Material&
Model::Part::GetMaterial() {
    return material_;
}

//// vmember: base_shift
inline size_t
Model::Part::GetBaseShift() const {
    return base_shift_;
}

inline void
Model::Part::SetBaseShift(size_t base_shift) {
    base_shift_ = base_shift;
}

//// vmember: triangle_num
inline size_t
Model::Part::GetTriangleNum() const {
    return triangle_num_;
}

inline void
Model::Part::SetTriangleNum(size_t triangle_num) {
    triangle_num_ = triangle_num;
}
