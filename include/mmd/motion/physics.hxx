
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
        virtual void AddPoser(Poser& poser) = 0;
        virtual void RemovePoser(Poser& poser) = 0;
        virtual void Reset() = 0;
        virtual void React(float step) = 0;
    protected:
        typedef Poser::BoneImage& BoneImageReference;
        static BoneImageReference GetPoserBoneImage(Poser& poser, size_t index);
    };

    class NullPhysicsReactor : public PhysicsReactor {
    public:
        /*virtual*/ void AddPoser(Poser& poser) {}
        /*virtual*/ void RemovePoser(Poser& poser) {}
        /*virtual*/ void Reset() {}
        /*virtual*/ void React(float step) {}
    };

    inline PhysicsReactor::BoneImageReference PhysicsReactor::GetPoserBoneImage(Poser& poser, size_t index) {
        return poser.bone_images_[index];
    }


} /* End of namespace mmd */

#endif /* __PHYSICS_HXX_E5336A794110A59D474947C2B9E87EE9_INCLUDED__ */
