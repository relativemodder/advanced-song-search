#pragma once
#include <string>
#include <Geode/binding/GJSongBrowser.hpp>


namespace Shared {
    inline bool filter_enabled = false;
    inline std::string search_filter = std::string("");
    inline GJSongBrowser* shared_song_browser;
}