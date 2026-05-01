#pragma once
#include "common.hpp"

struct camera {
private:
    // vars for view matrix
    vector3 position{ 0, 0, -2 };
    vector pos_vec{ };
    vector3 rotation{ 0, 0, 0 };

    // vars for projection matrix
    float fov{ 90.f };
    float aspect_ratio{ 1.f };
    float near_z{ 0.1f };
    float far_z{ 3000.f };
    
    matrix view_mat{ DirectX::XMMatrixIdentity() };
    matrix proj_mat{ DirectX::XMMatrixIdentity() };
    bool view_dirty{ true };
    bool proj_dirty{ true };

    const vector VECTOR_FORWARD{ DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f) };
    const vector VECTOR_UP{ DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) };
    
public:
    camera() { this->pos_vec = DirectX::XMLoadFloat3(&this->position); }
    
    [[nodiscard]] vector3 get_position() const {
        return this->position;
    }
    
    [[nodiscard]] vector3 get_rotation() const {
        return this->rotation;
    }

    [[nodiscard]] float get_fov() const {
        return this->fov;
    }
    
    [[nodiscard]] float get_aspect_ratio() const {
        return this->aspect_ratio;
    }
    
    [[nodiscard]] float get_near_z() const {
        return this->near_z;
    }
    
    [[nodiscard]] float get_far_z() const {
        return this->far_z;
    }

    void set_position(const vector3& position) {
        this->position = position;
        this->view_dirty = true;
    }
    
    void set_rotation(const vector3& rotation) {
        this->rotation = rotation;
        this->view_dirty = true;
    }

    void set_fov(const float fov) {
        this->fov = fov;
        this->proj_dirty = true;
    }

    void set_aspect_ratio(const float aspect_ratio) {
        this->aspect_ratio = aspect_ratio;
        this->proj_dirty = true;
    }

    void set_clip(const float near_z, const float far_z) {
        this->near_z = near_z;
        this->far_z = far_z;
        this->proj_dirty = true;
    }

    const matrix& get_view_matrix() {
        if (this->view_dirty) {
            vector3 rotation_radians = {
                DirectX::XMConvertToRadians(this->rotation.x),
                DirectX::XMConvertToRadians(this->rotation.y),
                DirectX::XMConvertToRadians(this->rotation.z),
            };
            
            DirectX::XMMATRIX rot_mat = DirectX::XMMatrixRotationRollPitchYaw(rotation_radians.x, rotation_radians.y, rotation_radians.z);
            vector forward = DirectX::XMVector3TransformCoord(VECTOR_FORWARD, rot_mat);
            forward = DirectX::XMVectorAdd(forward, this->pos_vec);

            vector up = DirectX::XMVector3TransformCoord(VECTOR_UP, rot_mat);

            this->view_mat = DirectX::XMMatrixLookAtLH(this->pos_vec, forward, up);
            this->view_dirty = false;
        }

        return this->view_mat;
    }

    const matrix& get_proj_matrix() {
        if (this->proj_dirty) {
            float fov_radians = DirectX::XMConvertToRadians(this->fov);
            this->proj_mat = DirectX::XMMatrixPerspectiveFovLH(fov_radians, this->aspect_ratio, this->near_z, this->far_z);
            this->proj_dirty = false;
        }

        return this->proj_mat;
    }
};