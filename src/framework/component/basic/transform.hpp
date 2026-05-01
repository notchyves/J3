#pragma once
#include "common.hpp"

struct transform {
private:
    vector3 position{ 0, 0, 0 };
    vector3 scale{ 1, 1, 1 };
    vector3 rotation{ 0, 0, 0 };
    
    bool dirty_matrix{ true };
    matrix mat{ DirectX::XMMatrixIdentity() };

public:
    [[nodiscard]] vector3 get_position() const {
        return this->position;
    }

    [[nodiscard]] vector3 get_scale() const {
        return this->scale;
    }

    [[nodiscard]] vector3 get_rotation() const {
        return this->rotation;
    }

    void set_position(const vector3& position) {
        this->position = position;
        this->dirty_matrix = true;
    }

    void set_scale(const vector3& scale) {
        this->scale = scale;
        this->dirty_matrix = true;
    }

    void set_rotation(const vector3& rotation) {
        this->rotation = rotation;
        this->dirty_matrix = true;
    }

    // update matrix if needed to prevent unnecessary calculations
    const matrix& get_matrix() {
        if (this->dirty_matrix) {
            vector3 rotation_radians = {
                DirectX::XMConvertToRadians(this->rotation.x),
                DirectX::XMConvertToRadians(this->rotation.y),
                DirectX::XMConvertToRadians(this->rotation.z),
            };
            
            this->mat = DirectX::XMMatrixScaling(this->scale.x, this->scale.y, this->scale.z) *
                DirectX::XMMatrixRotationRollPitchYaw(rotation_radians.x, rotation_radians.y, rotation_radians.z) *
                DirectX::XMMatrixTranslation(this->position.x, this->position.y, this->position.z);

            this->dirty_matrix = false;
        }

        return this->mat;
    }
};