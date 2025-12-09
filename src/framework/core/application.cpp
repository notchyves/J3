#include "application.hpp"

#include "framework/service/internet/internet.hpp"
#include "special_folder.hpp"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dup_filter_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/stdout_sinks.h>

alignas(application) char application_buffer[sizeof(application)];

application::application(const HINSTANCE instance) {
    this->instance = instance;
    
    const std::filesystem::path log_folder = special_folder::get(FOLDERID_LocalAppData) / "J3" / "Logs";
    auto dup_filter = std::make_shared<spdlog::sinks::dup_filter_sink_mt>(std::chrono::seconds(2));
    
    const auto msvc_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
    const auto stdout_sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();

    const std::filesystem::path log_file = log_folder / "Current.log";
    const std::filesystem::path previous_logs_folder = log_folder / "Previous";

    // creates all required directories at once
    std::filesystem::create_directories(previous_logs_folder);

    if (std::filesystem::exists(log_file)) {
        const auto creation_time = std::filesystem::last_write_time(log_file).time_since_epoch();
        const auto seconds = std::chrono::duration_cast<std::chrono::seconds>(creation_time);
        std::string time_str = std::to_string(seconds.count());

        std::filesystem::path previous_log_file = previous_logs_folder / (time_str + ".log");
        MoveFile(log_file.c_str(), previous_log_file.c_str());
    }
    
    const auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_file.string());

    dup_filter->add_sink(msvc_sink);
    dup_filter->add_sink(stdout_sink);
    dup_filter->add_sink(file_sink);

    spdlog::default_logger()->sinks().emplace_back(dup_filter);

#ifdef NDEBUG
    spdlog::set_level(spdlog::level::info);
    spdlog::flush_on(spdlog::level::info);
#else // debug
    spdlog::set_level(spdlog::level::debug);
    spdlog::flush_on(spdlog::level::debug);
#endif

    spdlog::info("Application start");

    winrt::init_apartment();
    spdlog::debug("Initialized WinRT apartment");

    // get icon because i don't want to load one from a file
    std::array<wchar_t, MAX_PATH> module_path = {};
    GetModuleFileName(this->instance, module_path.data(), MAX_PATH);
    HICON icon = ExtractIcon(this->instance, module_path.data(), 0);

    // application owns the window class
    WNDCLASSEXW window_class = {};
    window_class.cbSize = sizeof(WNDCLASSEXW);
    window_class.style = CS_HREDRAW | CS_VREDRAW;
    window_class.lpfnWndProc = window_proc;
    window_class.hInstance = this->instance;
    window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
    window_class.hbrBackground = nullptr;
    window_class.hIcon = icon;
    window_class.lpszClassName = WINDOW_CLASS_NAME;

    ATOM atom = RegisterClassEx(&window_class);
    if (atom == 0) {
        spdlog::critical("Registering window class failed with result 0x{:08X}", GetLastError());
        this->quit(-1);
        return;
    }

    spdlog::debug("Window class registered for application");
    spdlog::debug("Application singleton initialized");
}

application& application::get() { return *std::launder(reinterpret_cast<application*>(application_buffer)); }

void application::run() {
    if (this->windows.empty()) {
        // handle error
    }

    this->running = true;

    const auto& main_window = get_main_window();
    main_window->show();

    // window loop
    spdlog::info("Now running");
    MSG message = {};
    while (running) {
        bool has_message = get_message(
            message,
            static_cast<UINT>(Rml::Math::Min(Rml::GetContext("main")->GetNextUpdateDelay(), 10.0) * 1000)
        );

        while (has_message) {
            TranslateMessage(&message);
            DispatchMessage(&message);

            if (message.message == WM_QUIT) {
                this->running = false;
                break;
            }

            has_message = get_message(message, 0);
        }

        // perform updates during dead time
        this->time.update();

        for (const auto& window : this->windows) {
            window->update();
        }
    }

    spdlog::info("Application end");
}

void application::quit(const int exit_code) {
    if (!this->running) {
        spdlog::warn("Exiting immediately");
        exit(exit_code);
    }

    spdlog::debug("Application exit requested");
    PostQuitMessage(exit_code);
}

std::unique_ptr<window>& application::get_main_window() {
    // main window is always the first window
    return this->windows.front();
}

LRESULT application::window_proc(HWND handle, UINT message, WPARAM w_param, LPARAM l_param) {
    // find window with this handle
    auto& app = get();
    auto window_it = std::ranges::find_if(app.windows, [handle](const std::unique_ptr<window>& window) {
        return window->handle == handle;
    });

    if (window_it == app.windows.end()) {
        return DefWindowProc(handle, message, w_param, l_param);
    }

    return (*window_it)->window_proc(message, w_param, l_param) ? 0 : DefWindowProc(handle, message, w_param, l_param);
}

bool application::get_message(MSG& message, UINT timeout) {
    if (timeout != 0) {
        UINT_PTR timer_id = SetTimer(nullptr, 0, timeout, nullptr);
        BOOL result = GetMessage(&message, nullptr, 0, 0);
        KillTimer(nullptr, timer_id);

        if (message.message != WM_TIMER || message.hwnd != nullptr || message.wParam != timer_id) return result;
    }

    return PeekMessage(&message, nullptr, 0, 0, PM_REMOVE);
}
