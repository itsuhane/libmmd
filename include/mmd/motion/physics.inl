
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

#ifndef __PHYSICS_HXX_E5336A794110A59D474947C2B9E87EE9_INCLUDED__
#define __PHYSICS_HXX_E5336A794110A59D474947C2B9E87EE9_INCLUDED__

namespace mmd {
    class Poser;

    class PhysicsReactor {
    public:
        virtual ~PhysicsReactor() {}
        virtual void AddPoser(Poser &poser) = 0;
        virtual void RemovePoser(Poser &poser) = 0;
        virtual void Reset() = 0;
        virtual void React(float step) = 0;

        virtual void SetGravityStrength(float strength) = 0;
        virtual void SetGravityDirection(const Vector3f &direction) = 0;

        virtual float GetGravityStrength() const = 0;
        virtual Vector3f GetGravityDirection() const = 0;

        virtual void SetFloor(bool has_floor) = 0;
        virtual bool IsHasFloor() const = 0;
    protected:
        typedef Poser::BoneImage& BoneImageReference;
        static BoneImageReference GetPoserBoneImage(Poser &poser, size_t index);
    };

    inline PhysicsReactor::BoneImageReference PhysicsReactor::GetPoserBoneImage(
        Poser &poser, size_t index
    ) {
        return poser.bone_images_[index];
    }


} /* End of namespace mmd */

#endif /* __PHYSICS_HXX_E5336A794110A59D474947C2B9E87EE9_INCLUDED__ */
