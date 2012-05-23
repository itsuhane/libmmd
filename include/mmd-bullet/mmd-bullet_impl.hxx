
/**
             Copyright itsuhane@gmail.com, 2012.
  Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENSE_1_0.txt or copy at
            http://www.boost.org/LICENSE_1_0.txt)
**/

inline BulletPhysicsReactor::PoserMotionState::PoserMotionState(Poser& poser, const Model::RigidBody& body, const btTransform& body_transform)
  : poser_(poser),
    passive_(body.GetType()==Model::RigidBody::RIGID_TYPE_KINEMATIC),
    strict_(body.GetType()==Model::RigidBody::RIGID_TYPE_PHYSICS_STRICT),
    ghost_(body.GetType()==Model::RigidBody::RIGID_TYPE_PHYSICS_GHOST),
    target_(BulletPhysicsReactor::GetPoserBoneImage(poser, body.GetAssociatedBoneIndex())),
    body_transform_(body_transform),
    body_transform_inv_(body_transform.inverse())
{
    Reset();
}

inline void BulletPhysicsReactor::PoserMotionState::getWorldTransform(btTransform& transform) const {
    if(passive_) {
        Reset();
    }
    transform = transform_;
}

inline void BulletPhysicsReactor::PoserMotionState::setWorldTransform(const btTransform& transform) {
    if(!passive_) {
        transform_ = transform;
    }
}

inline void BulletPhysicsReactor::PoserMotionState::Synchronize() {
    if(!(passive_||ghost_)) {
        btTransform bt_transform;
        bt_transform = transform_*body_transform_inv_;
        bt_transform.getOpenGLMatrix(target_.skinning_matrix_.v);
    }
}

inline void BulletPhysicsReactor::PoserMotionState::Fix() {
    if(strict_) {
        Matrix4f parent_local_matrix;
        target_.local_matrix_ = target_.global_offset_matrix_inv_*target_.skinning_matrix_;
        if(target_.has_parent_) {
            parent_local_matrix = BulletPhysicsReactor::GetPoserBoneImage(poser_, target_.parent_).local_matrix_;
            target_.local_matrix_ = target_.local_matrix_*parent_local_matrix.Inverse();
        }
        target_.local_matrix_.r.v[3].downgrade.vector3d = target_.total_translation_+target_.local_offset_;
        if(target_.has_parent_) {
            target_.local_matrix_ = target_.local_matrix_*parent_local_matrix;
        }
        target_.skinning_matrix_ = target_.global_offset_matrix_*target_.local_matrix_;
    }
}

inline void BulletPhysicsReactor::PoserMotionState::Reset() const {
    transform_.setFromOpenGLMatrix(target_.skinning_matrix_.v);
    transform_ = transform_*body_transform_;
}


inline BulletPhysicsReactor::BulletPhysicsReactor() : configuration_(NULL), dispatcher_(NULL), broadphase_(NULL), solver_(NULL), world_(NULL), has_floor_(true) {
    configuration_ = new btDefaultCollisionConfiguration();
    dispatcher_ = new btCollisionDispatcher(configuration_);
    broadphase_ = new btDbvtBroadphase();
    solver_ = new btSequentialImpulseConstraintSolver();
    world_ = new btDiscreteDynamicsWorld(dispatcher_, broadphase_, solver_, configuration_);

    btVector3 gravity = world_->getGravity();
    gravity_direction_ = btVector3(btScalar(0.0f), btScalar(-1.0f), btScalar(0.0f));
    gravity_strength_ = gravity.length();

    world_->setGravity(gravity_direction_*gravity_strength_*btScalar(10.0f)); // the world is scaled by 10, since MikuMikuDance is using 0.1m as its unit.
    ground_shape_ = new btStaticPlaneShape(btVector3(btScalar(0.0f), btScalar(1.0f), btScalar(0.0f)), btScalar(0.0f));
    ground_state_ = new btDefaultMotionState();
    btRigidBody::btRigidBodyConstructionInfo bt_info(btScalar(0.0f), ground_state_, ground_shape_, btVector3(btScalar(0.0f), btScalar(0.0f), btScalar(0.0f)));
    bt_info.m_linearDamping = 0.0f;
    bt_info.m_angularDamping = 0.0f;
    bt_info.m_restitution = 0.0f;
    bt_info.m_friction = 0.265f;

    ground_rigid_body_ = new btRigidBody(bt_info);
    ground_rigid_body_->setCollisionFlags(ground_rigid_body_->getCollisionFlags()||btCollisionObject::CF_KINEMATIC_OBJECT);
    ground_rigid_body_->setActivationState(DISABLE_DEACTIVATION);

    world_->addRigidBody(ground_rigid_body_);
}

inline BulletPhysicsReactor::~BulletPhysicsReactor() {
    while(rigid_bodies_.size()>0) {
        RemovePoser(*(rigid_bodies_.begin()->first));
    }

    delete ground_rigid_body_;
    delete ground_state_;
    delete ground_shape_;

    delete world_;
    delete solver_;
    delete broadphase_;
    delete dispatcher_;
    delete configuration_;
}

inline void BulletPhysicsReactor::SetGravityStrength(float strength) {
    gravity_strength_ = strength;
    world_->setGravity(gravity_direction_*gravity_strength_*btScalar(10.0f));
}

inline void BulletPhysicsReactor::SetGravityDirection(const Vector3f& direction) {
    Vector3f d = direction.Normalize();
    gravity_direction_.setValue(btScalar(d.p.x), btScalar(d.p.y), btScalar(d.p.z));
    world_->setGravity(gravity_direction_*gravity_strength_*btScalar(10.0f));
}

inline float BulletPhysicsReactor::GetGravityStrength() const {
    return float(gravity_strength_);
}

inline Vector3f BulletPhysicsReactor::GetGravityDirection() const {
    Vector3f d;
    d.p.x = gravity_direction_.getX();
    d.p.y = gravity_direction_.getY();
    d.p.z = gravity_direction_.getZ();
    return d;
}

inline void BulletPhysicsReactor::SetFloor(bool has_floor) {
    if(has_floor==has_floor_) {
        return;
    }
    has_floor_ = has_floor;
    if(has_floor_) {
        world_->addRigidBody(ground_rigid_body_);
    } else {
        world_->removeRigidBody(ground_rigid_body_);
    }
}

inline bool BulletPhysicsReactor::IsHasFloor() const {
    return has_floor_;
}

inline void BulletPhysicsReactor::AddPoser(Poser& poser) {
    const Model& model = poser.GetModel();

    if(rigid_bodies_.count(&poser)>0) {
        return;
    }

    poser.ResetPosing();

    std::vector<btCollisionShape*>& collision_shapes = collision_shapes_[&poser];
    std::vector<PoserMotionState*>& motion_states = motion_states_[&poser];
    std::vector<btRigidBody*>& rigid_bodies = rigid_bodies_[&poser];
    std::vector<btGeneric6DofSpringConstraint*>& constraints = constraints_[&poser];

    for(size_t i=0;i<model.GetRigidBodyNum();++i) {
        const Model::RigidBody& body = model.GetRigidBody(i);
        const Vector3f& body_dimension = body.GetDimensions();

        btCollisionShape* bt_shape = NULL;

        btScalar bt_mass(0.0f);
        btVector3 bt_local_inertia(btScalar(0.0f), btScalar(0.0f), btScalar(0.0f));

        switch(body.GetShape()) {
        case Model::RigidBody::RIGID_SHAPE_SPHERE:
            bt_shape = new btSphereShape(btScalar(body_dimension.p.x)); break;
        case Model::RigidBody::RIGID_SHAPE_BOX:
            bt_shape = new btBoxShape(btVector3(btScalar(body_dimension.p.x), btScalar(body_dimension.p.y), btScalar(body_dimension.p.z))); break;
        case Model::RigidBody::RIGID_SHAPE_CAPSULE:
            bt_shape = new btCapsuleShape(btScalar(body_dimension.p.x), btScalar(body_dimension.p.y)); break;
        }

        if(body.GetType()!=Model::RigidBody::RIGID_TYPE_KINEMATIC) {
            bt_mass = body.GetMass();
            bt_shape->calculateLocalInertia(bt_mass, bt_local_inertia);
        }

        Matrix4f body_transform = YXZToQuaternion(body.GetRotation()).ToRotateMatrix();
        body_transform.r.v[3].downgrade.vector3d = body.GetPosition();

        btTransform bt_body_transform;
        bt_body_transform.setFromOpenGLMatrix(body_transform.v);

        PoserMotionState* bt_motion_state = new PoserMotionState(poser, body, bt_body_transform);

        btRigidBody::btRigidBodyConstructionInfo bt_info(bt_mass, bt_motion_state, bt_shape, bt_local_inertia);
        bt_info.m_linearDamping = body.GetTranslateDamp();
        bt_info.m_angularDamping = body.GetRotateDamp();
        bt_info.m_restitution = body.GetRestitution();
        bt_info.m_friction = body.GetFriction();

        btRigidBody* bt_rigid_body = new btRigidBody(bt_info);

        bt_rigid_body->setActivationState(DISABLE_DEACTIVATION);

        if(body.GetType()==Model::RigidBody::RIGID_TYPE_KINEMATIC) {
            bt_rigid_body->setCollisionFlags(bt_rigid_body->getCollisionFlags()|btCollisionObject::CF_KINEMATIC_OBJECT);
        }

        world_->addRigidBody(bt_rigid_body, (short)(1<<body.GetCollisionGroup()), (short)body.GetCollisionMask().to_ulong());

        collision_shapes.push_back(bt_shape);
        motion_states.push_back(bt_motion_state);
        rigid_bodies.push_back(bt_rigid_body);
    }

    for(size_t i=0;i<model.GetConstraintNum();++i) {
        const Model::Constraint& constraint = model.GetConstraint(i);

        btRigidBody& bt_body_1 = *rigid_bodies[constraint.GetAssociatedRigidBodyIndex(0)];
        btRigidBody& bt_body_2 = *rigid_bodies[constraint.GetAssociatedRigidBodyIndex(1)];

        const Vector3f &position_low_limit = constraint.GetPositionLowLimit();
        const Vector3f &position_high_limit = constraint.GetPositionHighLimit();
        const Vector3f &rotation_low_limit = constraint.GetRotationLowLimit();
        const Vector3f &rotation_high_limit = constraint.GetRotationHighLimit();

        Matrix4f constraint_transform = YXZToQuaternion(constraint.GetRotation()).ToRotateMatrix();
        constraint_transform.r.v[3].downgrade.vector3d = constraint.GetPosition();

        btTransform bt_constraint_transform;
        bt_constraint_transform.setFromOpenGLMatrix(constraint_transform.v);

        btTransform bt_localization_transform_1 = bt_body_1.getWorldTransform().inverseTimes(bt_constraint_transform);
        btTransform bt_localization_transform_2 = bt_body_2.getWorldTransform().inverseTimes(bt_constraint_transform);

        btGeneric6DofSpringConstraint* bt_constraint = new btGeneric6DofSpringConstraint(bt_body_1, bt_body_2, bt_localization_transform_1, bt_localization_transform_2, true);

        bt_constraint->setLinearLowerLimit(btVector3(position_low_limit.p.x, position_low_limit.p.y, position_low_limit.p.z));
        bt_constraint->setLinearUpperLimit(btVector3(position_high_limit.p.x, position_high_limit.p.y, position_high_limit.p.z));

        bt_constraint->setAngularLowerLimit(btVector3(rotation_low_limit.p.x, rotation_low_limit.p.y, rotation_low_limit.p.z));
        bt_constraint->setAngularUpperLimit(btVector3(rotation_high_limit.p.x, rotation_high_limit.p.y, rotation_high_limit.p.z));

        for(int i=0;i<3;++i) {
            bt_constraint->setStiffness(i, constraint.GetSpringTranslate().v[i]);
            bt_constraint->enableSpring(i, true);
            bt_constraint->setStiffness(i+3, constraint.GetSpringRotate().v[i]);
            bt_constraint->enableSpring(i+3, true);
        }

        world_->addConstraint(bt_constraint);
        constraints.push_back(bt_constraint);
    }
}

inline void BulletPhysicsReactor::RemovePoser(Poser& poser) {
    if(rigid_bodies_.count(&poser)==0) {
        return;
    }

    std::vector<btGeneric6DofSpringConstraint*>& constraints = constraints_[&poser];
    std::vector<PoserMotionState*>& motion_states = motion_states_[&poser];
    std::vector<btRigidBody*>& rigid_bodies = rigid_bodies_[&poser];
    std::vector<btCollisionShape*>& collision_shapes = collision_shapes_[&poser];

    for(std::vector<btGeneric6DofSpringConstraint*>::iterator i=constraints.begin();i!=constraints.end();++i) {
        world_->removeConstraint(*i);
        delete (*i);
    }
    for(std::vector<btRigidBody*>::iterator i=rigid_bodies.begin();i!=rigid_bodies.end();++i) {
        world_->removeRigidBody(*i);
    }
    for(std::vector<PoserMotionState*>::iterator i=motion_states.begin();i!=motion_states.end();++i) {
        delete (*i);
    }
    for(std::vector<btRigidBody*>::iterator i=rigid_bodies.begin();i!=rigid_bodies.end();++i) {
        delete (*i);
    }
    for(std::vector<btCollisionShape*>::iterator i=collision_shapes.begin();i!=collision_shapes.end();++i) {
        delete (*i);
    }

    constraints_.erase(&poser);
    rigid_bodies_.erase(&poser);
    motion_states_.erase(&poser);
    collision_shapes_.erase(&poser);
}

inline void BulletPhysicsReactor::Reset() {
    for(std::map<Poser*, std::vector<PoserMotionState*>>::iterator i=motion_states_.begin();i!=motion_states_.end();++i) {
        std::vector<PoserMotionState*>& poser_motion_states = i->second;
        for(std::vector<PoserMotionState*>::iterator j=poser_motion_states.begin();j!=poser_motion_states.end();++j) {
            PoserMotionState& motion_state = **j;
            motion_state.Reset();
        }
    }
    for(std::map<Poser*, std::vector<btRigidBody*>>::iterator i=rigid_bodies_.begin();i!=rigid_bodies_.end();++i) {
        std::vector<btRigidBody*>& poser_rigid_bodies = i->second;
        for(std::vector<btRigidBody*>::iterator j=poser_rigid_bodies.begin();j!=poser_rigid_bodies.end();++j) {
            btRigidBody& rigid_body = **j;
            btTransform transform;
            rigid_body.getMotionState()->getWorldTransform(transform);
            rigid_body.setCenterOfMassTransform(transform);
            rigid_body.setInterpolationWorldTransform(transform);
            rigid_body.setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
            rigid_body.setInterpolationAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
            rigid_body.setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
            rigid_body.setInterpolationLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
            rigid_body.clearForces();
        }
    }
    world_->getBroadphase()->resetPool(world_->getDispatcher());
    world_->getConstraintSolver()->reset();
}

inline void BulletPhysicsReactor::React(float step) {
    world_->stepSimulation(step, 60);

    for(std::map<Poser*, std::vector<PoserMotionState*>>::iterator i=motion_states_.begin();i!=motion_states_.end();++i) {
        std::vector<PoserMotionState*>& poser_motion_states = i->second;
        for(std::vector<PoserMotionState*>::iterator j=poser_motion_states.begin();j!=poser_motion_states.end();++j) {
            PoserMotionState& motion_state = **j;
            motion_state.Synchronize();
        }
        for(std::vector<PoserMotionState*>::iterator j=poser_motion_states.begin();j!=poser_motion_states.end();++j) {
            PoserMotionState& motion_state = **j;
            motion_state.Fix();
        }
    }
}
