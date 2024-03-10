#pragma once
#include <Geode/Geode.hpp>
#include <Geode/ui/TextInput.hpp>
#include <shared.hpp>

using namespace geode::prelude;


class AdvancedSearchFilterLayer : public FLAlertLayer {
public:
    TextInput* filter_input;

    static AdvancedSearchFilterLayer* create();

    void handle_close(CCObject* sender);
    void handle_search(CCObject* sender);
    void on_name_toggle(CCObject* sender);
    void on_artist_toggle(CCObject* sender);

	void handle_open_search(CCObject* sender);
    virtual bool init();

    CCScale9Sprite* create_background_sprite();

};