#include "EditorController.h"
#include "../GameObject.h"
#include "../Components/Transform.h"
#include "../Input.h"
#include <math.h>
#include <glm/glm.hpp>

namespace glGame {

    EditorController::EditorController() {
        
    }

    void EditorController::update(float deltatime) {
        if(Input::getMouseKeyDown(MOUSE_BUTTON_LEFT)) {
            getGameObject()->transform->rotation.y += Input::getMouseDeltaX() * 0.1;
        }

        float movementSpeed = deltatime;
        Vector3 movement(0.0, 0.0, 0.0);
        if(Input::getKeyDown(KEY_W)) movement.z -= movementSpeed;
        if(Input::getKeyDown(KEY_S)) movement.z += movementSpeed;
        if(Input::getKeyDown(KEY_A)) movement.x -= movementSpeed;
        if(Input::getKeyDown(KEY_D)) movement.x += movementSpeed;

        Vector3 worldMovement(0.0, 0.0, 0.0);

        float rotationY = glm::radians(-getGameObject()->transform->rotation.y); 
        worldMovement.z = std::cos(rotationY) * movement.z - std::sin(rotationY) * movement.x;
        worldMovement.x = std::cos(rotationY) * movement.x + std::sin(rotationY) * movement.z;

        getGameObject()->transform->move(worldMovement.x, worldMovement.y, worldMovement.z);
    }

}