#include "HelloWorldScene.h"
#include "LetterAnimationLabel.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    //**********LABELS*********************************************
    auto label1 = RubyLabel::createWithTTF("", "fonts/ipamp.ttf", 24);
    label1->setLineHeight(40);
    label1->setMaxLineWidth(470);
    label1->setString("|国<<くに>>|破<<やぶ>>れて|山河<<さんが>>|在<<あ>>り\n|城<<しろ>>|春<<はる>>にして|草木<<そうもく>>|深<<ふか>>し\n|時<<とき>>に|感<<かん>>じては|花<<はな>>にも|涙<<なみだ>>を|濺<<そそ>>ぎ\n|別<<わか>>れを|恨<<うら>>んでは|鳥<<とり>>にも|心<<こころ>>を|驚<<おどろ>>かす");
    
    label1->setPosition(Vec2(300,600));
    label1->setColor(Color3B::GREEN);
    this->addChild(label1);
    
    auto label2 = TypewriterLabel::createWithTTF("", "fonts/ipamp.ttf", 24);
    label2->setLineHeight(40);
    label2->setMaxLineWidth(470);
    label2->setString("|春<<はる>>はあけぼの。やうやう|白<<しろ>>くなりゆく|山際<<やまぎわ>>、|少<<すこ>>し|明<<あ>>かりて、|紫<<むらさき>>だちたる|雲<<くも>>の|細<<ほそ>>くたなびきたる。");
    label2->setDelayTime(0.08);
    label2->setPosition(Vec2(100,400));
    label2->setColor(Color3B::BLUE);
    this->addChild(label2);
    
    
    auto label3 = FadeinLabel::createWithTTF("", "fonts/ipamp.ttf", 24);
    label3->setLineHeight(40);
    label3->setMaxLineWidth(470);
    label3->setString("|祇園<<ぎおん>>|精舎<<しょうじゃ>>の|鐘<<かね>>の声、|諸行<<しょぎょう>>|無常<<むじょう>>の|響<<ひびき>>きあり。|沙羅<<さら>>|双樹<<そうじゅ>>の花の色、|盛者<<じょうしゃ>>|必衰<<ひっすい>>のことわりをあらはす。奢れる人も久しからず、唯春の夜の夢のごとし。たけき者も遂には滅びぬ、偏に風の前の塵に同じ。");
    label3->setDelayTime(0.08);
    label3->setFadeinTime(1);
    label3->setPosition(Vec2(100,280));
    label3->setColor(Color3B::YELLOW);
    this->addChild(label3);

    
    //****************************************************************
    
    
    //****************BUTTONS***********************************************
    auto l2_run = Label::createWithSystemFont("run", "Arial", 25);
    auto b2_run = MenuItemLabel::create(l2_run, [label2](Ref *pSender){
        label2->run();
    });
    b2_run->setPosition(Vec2(0,0));
    
    auto l2_pause = Label::createWithSystemFont("pause", "Arial", 25);
    auto b2_pause = MenuItemLabel::create(l2_pause, [label2](Ref *pSender){
        label2->pause();
    });
    b2_pause->setPosition(Vec2(100,0));
    
    auto l2_restart = Label::createWithSystemFont("restart", "Arial", 25);
    auto b2_restart = MenuItemLabel::create(l2_restart, [label2](Ref *pSender){
        label2->restart();
    });
    b2_restart->setPosition(Vec2(200,0));
    
    auto l2_showall = Label::createWithSystemFont("showAll", "Arial", 25);
    auto b2_showall = MenuItemLabel::create(l2_showall, [label2](Ref *pSender){
        label2->showAll();
    });
    b2_showall->setPosition(Vec2(100,-50));
    
    auto l2_clear = Label::createWithSystemFont("clear", "Arial", 25);
    auto b2_clear = MenuItemLabel::create(l2_clear, [label2](Ref *pSender){
        label2->clear();
    });
    b2_clear->setPosition(Vec2(200,-50));
    
    
    
    auto l3_run = Label::createWithSystemFont("run", "Arial", 25);
    auto b3_run = MenuItemLabel::create(l3_run, [label3](Ref *pSender){
        label3->run();
    });
    b3_run->setPosition(Vec2(0,-200));
    
    auto l3_pause = Label::createWithSystemFont("pause", "Arial", 25);
    auto b3_pause = MenuItemLabel::create(l3_pause, [label3](Ref *pSender){
        label3->pause();
    });
    b3_pause->setPosition(Vec2(100,-200));
    
    auto l3_restart = Label::createWithSystemFont("restart", "Arial", 25);
    auto b3_restart = MenuItemLabel::create(l3_restart, [label3](Ref *pSender){
        label3->restart();
    });
    b3_restart->setPosition(Vec2(200,-200));
    
    auto l3_showall = Label::createWithSystemFont("showAll", "Arial", 25);
    auto b3_showall = MenuItemLabel::create(l3_showall, [label3](Ref *pSender){
        label3->showAll();
    });
    b3_showall->setPosition(Vec2(100,-250));
    
    auto l3_clear = Label::createWithSystemFont("clear", "Arial", 25);
    auto b3_clear = MenuItemLabel::create(l3_clear, [label3](Ref *pSender){
        label3->clear();
    });
    b3_clear->setPosition(Vec2(200,-250));
    
    Menu* pMenu = Menu::create(b2_run,b2_pause,b2_restart,b2_showall,b2_clear,
                               b3_run,b3_pause,b3_restart,b3_showall,b3_clear,NULL);
    pMenu->setPosition(Vec2(700,400));
    this->addChild(pMenu);
    //***********************************************************************

    return true;
}
