#include <AdvancedSearchFilterLayer.hpp>


AdvancedSearchFilterLayer* AdvancedSearchFilterLayer::create() {
    auto ret = new AdvancedSearchFilterLayer();
	if (ret && ret->init()) {
		ret->autorelease();
	} else {
		delete ret;
		ret = nullptr;
	}
	return ret;
}


void AdvancedSearchFilterLayer::handle_close(CCObject* sender) {
    removeFromParent();
    Shared::filter_enabled = false;
}


void AdvancedSearchFilterLayer::handle_open_search(CCObject* sender) {
    auto filter_layer = AdvancedSearchFilterLayer::create();
    filter_layer->show();

    auto casted_sender = (CCMenuItemSpriteExtra*)sender;
    auto sender_parent = casted_sender->getParent();
    auto sender_parent_parent = sender_parent->getParent();
    auto sender_browser = sender_parent_parent->getParent();

    log::info("sender_browser: {}", sender_browser);

    Shared::shared_song_browser = (GJSongBrowser*)sender_browser;
}


void AdvancedSearchFilterLayer::handle_search(CCObject* sender) {
    Shared::filter_enabled = true;
    Shared::search_filter = filter_input->getString();

    removeFromParent();

    Shared::shared_song_browser->removeAllChildren();
    Shared::shared_song_browser->init(); // reloading lol
    Shared::shared_song_browser->setZOrder(9999);
    Shared::shared_song_browser->showLayer(true); // i blame robtop
    
}


void AdvancedSearchFilterLayer::on_name_toggle(CCObject* sender) {
    log::info("on_name_toggle from: {}", sender);
}


void AdvancedSearchFilterLayer::on_artist_toggle(CCObject* sender) {
    log::info("on_artist_toggle from: {}", sender);
}


bool AdvancedSearchFilterLayer::init() {
    FLAlertLayer::init(1);

    runAction(
        CCFadeTo::create(0.1f, 0x80)
    );
	auto winSize = CCDirector::sharedDirector()->getWinSize();


    m_mainLayer->setScale(0.0f);
	m_mainLayer->runAction(CCEaseBackOut::create(CCScaleTo::create(0.15, 1.0f)));

    auto bg_sprite = create_background_sprite();

    auto titleLabel = CCLabelBMFont::create("Set search filter", "bigFont.fnt");
	m_mainLayer->addChild(titleLabel);

	titleLabel->setPosition({winSize.width / 2.0f, winSize.height / 2.f + 50.0f});
	titleLabel->setScale(0.575f);

    auto okspr = ButtonSprite::create("Search", "goldFont.fnt", "GJ_button_05.png");
    auto okBtn = CCMenuItemSpriteExtra::create(okspr, this, menu_selector(AdvancedSearchFilterLayer::handle_search));

    auto cancelspr = ButtonSprite::create("Cancel", "goldFont.fnt", "GJ_button_04.png");
    auto cancelBtn = CCMenuItemSpriteExtra::create(cancelspr, this, menu_selector(AdvancedSearchFilterLayer::handle_close));

	auto mainMenu = CCMenu::create();

	m_buttonMenu = mainMenu;

	mainMenu->addChild(okBtn);
	mainMenu->addChild(cancelBtn);
	m_mainLayer->addChild(mainMenu);

	mainMenu->ignoreAnchorPointForPosition(false);
	mainMenu->setPosition({0., 0.});
	mainMenu->setAnchorPoint({0., 0.});

    okBtn->setPosition({winSize.width / 2.0f + 65.0f, winSize.height / 2.f - 30.0f});
    cancelBtn->setPosition({winSize.width / 2.0f - 65.0f, winSize.height / 2.f - 30.0f});

    filter_input = TextInput::create(300, "Search by name or artist...");
	filter_input->setPosition({winSize.width / 2, winSize.height / 2.f + 10.0f});
	filter_input->setID("ADVANCED_SEARCH_BY_RELATIVE"_spr);

    mainMenu->addChild(filter_input);

    return true;
}


CCScale9Sprite* AdvancedSearchFilterLayer::create_background_sprite() {
	auto winSize = CCDirector::sharedDirector()->getWinSize();

    auto backSprite = CCScale9Sprite::create("GJ_square01.png");
	this->m_mainLayer->addChild(backSprite);
	backSprite->setContentSize(ccp(320, winSize.height / 2.5f));
	backSprite->setScale(0.0f);

	backSprite->setPosition({winSize.width / 2, winSize.height / 2});

	backSprite->runAction(CCEaseBackOut::create(CCScaleTo::create(0.15, 1.0f)));
	this->runAction(CCFadeTo::create(0.2f, 0x64));

	return backSprite;
}