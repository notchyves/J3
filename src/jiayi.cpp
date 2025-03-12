#include "jiayi.hpp"
#include "core/application.hpp"

alignas(jiayi) char jiayi_buffer[sizeof(jiayi)];

jiayi::jiayi(const HINSTANCE instance, const std::wstring& command_line) {
    new(application_buffer) application(instance);
    auto& app = application::get();
    
    app.create_window(L"J3", { 900, 550 });
    app.run();
}

jiayi& jiayi::get() {
    return *std::launder(reinterpret_cast<jiayi*>(jiayi_buffer));
}

// win32 entry point
// ReSharper disable CppParameterMayBeConst
int WINAPI wWinMain(HINSTANCE inst, [[maybe_unused]] HINSTANCE prev_inst, PWSTR cmd_line, int cmd_show) {
    new(jiayi_buffer) jiayi(inst, cmd_line);

    // after business is done
    jiayi::get().~jiayi();
    return 0;
}
