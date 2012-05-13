
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

/**
  This is ONLY a reference implementation demonstrating how to bind libmmd
  with bulletphysics. Its behavior may different from MikuMikuDance.

  To get more control over physics manipulation, you may need to implement
  your own physics binding.

  See accompanying file mmd-bullet_impl.hxx for implementation detail.
**/
#ifndef __MMD_BULLET_HXX_5912EA0C3602E47B50077FCA6298F8AC_INCLUDED__
#define __MMD_BULLET_HXX_5912EA0C3602E47B50077FCA6298F8AC_INCLUDED__

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4100 4103 4189 4514 4571 4710 4819 4820 4996 )
#ifdef _WIN32
#ifndef WIN32
#define WIN32
#define MMD_BULLET_WIN32_DEFINED
#endif
#endif
#endif

#include <btBulletDynamicsCommon.h>

namespace mmd {
    class BulletPhysicsReactor : public PhysicsReactor {
    public:
        class PoserMotionState : public btMotionState {
        public:
            PoserMotionState(Poser& poser, const Model::RigidBody& body, const btTransform& body_transform);
            /*virtual*/ void getWorldTransform(btTransform& transform) const;
            /*virtual*/ void setWorldTransform(const btTransform& transform);
            void Synchronize();
            void Feedback();
            void Reset() const;
        private:
            Poser& poser_;
            bool passive_;
            bool feedback_;
            BulletPhysicsReactor::BoneImageReference target_;
            mutable btTransform transform_;
            btTransform body_transform_;
            btTransform body_transform_inv_;
        };

        BulletPhysicsReactor();
        virtual ~BulletPhysicsReactor();

        /*virtual*/ void AddPoser(Poser& poser);
        /*virtual*/ void RemovePoser(Poser& poser);
        /*virtual*/ void Reset();
        /*virtual*/ void React(float step);

    private:
        btDefaultCollisionConfiguration* configuration_;
        btCollisionDispatcher* dispatcher_;
        btBroadphaseInterface* broadphase_;
        btSequentialImpulseConstraintSolver* solver_;
        btDiscreteDynamicsWorld* world_;

        std::map<Poser*, std::vector<btCollisionShape*>> collision_shapes_;
        std::map<Poser*, std::vector<PoserMotionState*>> motion_states_;
        std::map<Poser*, std::vector<btRigidBody*>> rigid_bodies_;
        std::map<Poser*, std::vector<btGeneric6DofSpringConstraint*>> constraints_;
    };

#include "mmd-bullet_impl.hxx"
} /* End of namespace mmd */

#ifdef _MSC_VER
#ifdef _WIN32
#ifdef WIN32
#ifdef MMD_BULLET_WIN32_DEFINED
#undef WIN32
#undef MMD_BULLET_WIN32_DEFINED
#endif
#endif
#endif
#pragma warning( pop )
#endif

#endif /* __MMD_BULLET_HXX_5912EA0C3602E47B50077FCA6298F8AC_INCLUDED__ */
