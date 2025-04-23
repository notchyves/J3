#include "font_resource.hpp"

#include "core/application.hpp"

// begin dumb
size_t read_size = 0;
size_t total_size = 0;

int read_helper(void* dst, int length, void* data) {
    if (read_size + length > total_size)
        return -1;

    memcpy(dst, static_cast<char*>(data) + read_size, length);
    read_size += length;
    return length;
}
// end dumb

font_resource::font_resource(const resource& data) {
    read_size = 0;
    total_size = data.size();

    bool result = artery_font::decode<&read_helper, float, artery_font::StdList, artery_font::StdByteArray,
                                      artery_font::StdString>(font, const_cast<char*>(data.data()));

    if (!result) {
        application::get().log.error("A font failed to load");
        return;
    }
}
