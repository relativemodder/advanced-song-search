#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/MusicDownloadManager.hpp>
#include <Geode/modify/GJSongBrowser.hpp>
#include <utils.hpp>
#include <shared.hpp>
#include <AdvancedSearchFilterLayer.hpp>



class $modify(MusicDownloadManager) {
	CCArray* getDownloadedSongs() {
		auto songs_array = MusicDownloadManager::getDownloadedSongs();

		// Type SongInfoObject*

		CCArray* new_songs_array = CCArray::create();
		CCObject* song_info_object;
		SongInfoObject* song_info;
		gd::string artist;
		gd::string name;

		CCARRAY_FOREACH(songs_array, song_info_object) {
			song_info = (SongInfoObject*)song_info_object;
			artist = song_info->m_artistName;
			name = song_info->m_songName;

			if (!Shared::filter_enabled) {
				new_songs_array->addObject(song_info_object);
				continue;
			}

			if (Utils::compare_to_filter(name, Shared::search_filter)) {
				new_songs_array->addObject(song_info_object);
				continue;
			}

			if (Utils::compare_to_filter(artist, Shared::search_filter)) {
				new_songs_array->addObject(song_info_object);
				continue;
			}
		}

		return new_songs_array;
	}
};


class $modify(CustomGJSongBrowser, GJSongBrowser) {

	bool init() {
		if (!GJSongBrowser::init()) return false;

		auto search_sprite = CCSprite::createWithSpriteFrameName("gj_findBtn_001.png");

		auto search_btn = CCMenuItemSpriteExtra::create(
			search_sprite,
			this, menu_selector(AdvancedSearchFilterLayer::handle_open_search)
		);

		auto menu = CCMenu::create();
		menu->addChild(search_btn);

		menu->setPosition({25, 249});

		m_mainLayer->addChild(menu);

		return true;
	}

	void exitLayer(CCObject* sender) {
		GJSongBrowser::exitLayer(sender);
		Shared::filter_enabled = false;
	}
};