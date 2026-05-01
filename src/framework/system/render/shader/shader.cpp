#include "shader.hpp"

void vertex_shader::initialize(const winrt::com_ptr<ID3D11Device>& device, const resource& data) {
    this->shader_data = data.data();
    this->shader_size = data.size();
    
    HRESULT hr = device->CreateVertexShader(data.data(), data.size(), nullptr, this->shader.put());
    LOG_HRESULT(error, "Vertex shader creation failed", hr);
}

winrt::com_ptr<ID3D11VertexShader>& vertex_shader::get() {
    return this->shader;
}

const char* vertex_shader::data() const {
    return this->shader_data;
}

size_t vertex_shader::size() const {
    return this->shader_size;
}

d3d_buffer& vertex_shader::get_constant_buffer() {
    return this->constant_buffer;
}

void pixel_shader::initialize(const winrt::com_ptr<ID3D11Device>& device, const resource& data) {
    this->shader_data = data.data();
    this->shader_size = data.size();
    
    HRESULT hr = device->CreatePixelShader(data.data(), data.size(), nullptr, this->shader.put());
    LOG_HRESULT(error, "Pixel shader creation failed", hr);
}

winrt::com_ptr<ID3D11PixelShader>& pixel_shader::get() {
    return this->shader;
}

const char* pixel_shader::data() const {
    return this->shader_data;
}

size_t pixel_shader::size() const {
    return this->shader_size;
}

d3d_buffer& pixel_shader::get_constant_buffer() {
    return this->constant_buffer;
}
