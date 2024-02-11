#include "ProgressPlataformerBetter.hpp"

int ProgressPlataformerBetter::m_totalPoints = 0;

ProgressPlataformerBetter* ProgressPlataformerBetter::create() {
	auto ret = new ProgressPlataformerBetter();

	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}

	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool ProgressPlataformerBetter::init() {
    if (!cocos2d::CCNode::init()) {
        return false;
    }

    m_clockSprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_timeIcon_001.png");
    m_clockSprite->setPosition({ 12.f, 0.f });
    this->addChild(m_clockSprite);

    m_diamondsSprite = cocos2d::CCSprite::createWithSpriteFrameName("GJ_pointsIcon_001.png");
    m_diamondsSprite->setPosition({ 12.f, -40.f });
    this->addChild(m_diamondsSprite);


    auto timeTextFormat = Utils::getplayLayerA()->m_isPracticeMode ?
        "Current Time: <cj>%.3lf</c> \nBest Time: <cj>%.3f</c> \nEstimated Time: <cj>%.3f</c>" :
        "Current Time: <cg>%.3lf</c> \nBest Time: <cg>%.3f</c> \nEstimated Time: <cg>%.3f</c>";

    auto pointTextFormat = Utils::getplayLayerA()->m_isPracticeMode ?
        "Current Points: <cj>%i</c>\nBest Points: <cj>%i</c>\nTotal Points: <cj>%i</c>" :
        "Current Points: <cg>%i</c>\nBest Points: <cg>%i</c>\nTotal Points: <cg>%i</c>";

    auto bestTimeMilliseconds = Utils::getplayLayerA()->m_level->m_bestTime;
    float bestTimeSeconds = static_cast<int>(bestTimeMilliseconds) / 1000.f;

    auto estimatedTime = Utils::getplayLayerA()->m_level->m_timestamp ?
        (static_cast<int>(Utils::getplayLayerA()->m_level->m_timestamp) / 240.f) :
        BetterInfo::timeForLevelString(Utils::getplayLayerA()->m_level->m_levelString);

    
    m_timeLabelLevel = TextArea::create(
        gd::string(
            cocos2d::CCString::createWithFormat(
                timeTextFormat,
                Utils::from<double>(Utils::getplayLayerA(), 0x2c20),
                bestTimeSeconds,
                estimatedTime
            )->getCString()
        ),
        "goldFont.fnt",
        0.4f,
        350.f,
        { 0.f, 1.f },
        10.f,
        false
    );
    m_timeLabelLevel->setPosition({ 385.f, 5.f });
    this->addChild(m_timeLabelLevel);

    //auto pointsCurrent = GameToolbox::poi


    m_pointsLabelLevel = TextArea::create(
        gd::string(
            cocos2d::CCString::createWithFormat(
                pointTextFormat,
                Utils::from<int>(Utils::getplayLayerA(), 0x5d8),
                Utils::getplayLayerA()->m_level->m_bestPoints,
                ProgressPlataformerBetter::m_totalPoints
            )->getCString()
        ),
        "goldFont.fnt",
        0.4f,
        350.f,
        { 0.f, 1.f },
        10.f,
        false
    );
    m_pointsLabelLevel->setPosition({ 385.f, -35.f });
    this->addChild(m_pointsLabelLevel);

    return true;
}
