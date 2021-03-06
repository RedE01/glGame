#include "Physics3d.h"
#include "../Components/RigidBody.h"
#include "../Components/StaticBody.h"
#include "../GameObject.h"
#include "../Components/Transform.h"

#include <glm/glm.hpp>

namespace glGame {

    Physics3d::Physics3d() {
    }

    void Physics3d::init() {
        m_physicsWorld.init();
    }

    void Physics3d::stepSimulation(float deltaTime) {
        for(auto& rb : m_rigidBodies) {
            Vector3& position = rb->getGameObject()->transform->position;
            Quaternion& orientation = rb->getGameObject()->transform->orientation;

            rb->m_rigidBody->position = redPhysics3d::Vector3(position.x, position.y, position.z);
            rb->m_rigidBody->orientation = redPhysics3d::Quaternion(orientation.w, orientation.x, orientation.y, orientation.z);
        }

        m_physicsWorld.stepSimulation(deltaTime);

        for(auto& rb : m_rigidBodies) {
            redPhysics3d::Quaternion orientation = rb->m_rigidBody->orientation;
            redPhysics3d::Vector3& pos = rb->m_rigidBody->position;
            rb->getGameObject()->transform->position = Vector3(pos.x, pos.y, pos.z);
            rb->getGameObject()->transform->orientation = Quaternion(orientation.w, orientation.x, orientation.y, orientation.z);
        }
    }

    void Physics3d::addRigidBody(RigidBody* rigidbody) {
        auto search = m_rigidBodies.find(rigidbody);
        if(search != m_rigidBodies.end()) return;

        m_rigidBodies.insert(rigidbody);
        redPhysics3d::RigidBody* newRigidBody = m_physicsWorld.addRigidBody();
        rigidbody->m_rigidBody = newRigidBody;

        Vector3& position = rigidbody->getGameObject()->transform->position;
        Quaternion& orientation = rigidbody->getGameObject()->transform->orientation;

        newRigidBody->position = redPhysics3d::Vector3(position.x, position.y, position.z);
        newRigidBody->orientation = redPhysics3d::Quaternion(orientation.w, orientation.x, orientation.y, orientation.z);
    }

    void Physics3d::removeRigidBody(RigidBody* rigidbody) {
        auto search = m_rigidBodies.find(rigidbody);
        if(search == m_rigidBodies.end()) return;

        m_physicsWorld.removeRigidBody(rigidbody->m_rigidBody);
        rigidbody->m_rigidBody = nullptr;
        m_rigidBodies.erase(rigidbody);
    }

    void Physics3d::addStaticBody(StaticBody* staticBody) {
        auto search = m_staticBodies.find(staticBody);
        if(search != m_staticBodies.end()) return;

        m_staticBodies.insert(staticBody);
        redPhysics3d::StaticBody* newStaticBody = m_physicsWorld.addStaticBody();
        staticBody->m_staticBody = newStaticBody;

        Vector3& position = staticBody->getGameObject()->transform->position;
        Quaternion& orientation = staticBody->getGameObject()->transform->orientation;

        newStaticBody->position = redPhysics3d::Vector3(position.x, position.y, position.z);
        newStaticBody->orientation = redPhysics3d::Quaternion(orientation.w, orientation.x, orientation.y, orientation.z);
    }

    void Physics3d::removeStaticBody(StaticBody* staticBody) {
        auto search = m_staticBodies.find(staticBody);
        if(search == m_staticBodies.end()) return;

        m_physicsWorld.removeStaticBody(staticBody->m_staticBody);
        staticBody->m_staticBody = nullptr;
        m_staticBodies.erase(staticBody);
    }


}