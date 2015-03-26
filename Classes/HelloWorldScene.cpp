#include "HelloWorldScene.h"


USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    //登陆按钮
    auto loginItem = MenuItemImage::create(
                                           "login1.png",
                                           "login2.png",
                                           CC_CALLBACK_1(HelloWorld::menuLoginCallback, this));

    loginItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - loginItem->getContentSize().width / 2,
                                origin.y + visibleSize.height / 2 - 200));
    
    //切换按钮
    switchItem = MenuItemImage::create(
                                       "switch1.png",
                                       "switch2.png",
                                       CC_CALLBACK_1(HelloWorld::menuSwitchCallback, this));
    
    switchItem->setPosition(Vec2(origin.x + visibleSize.width / 2 - switchItem->getContentSize().width / 2,
                                 origin.y + visibleSize.height / 2 - 200));
    
    //支付按钮
//    auto payItem = MenuItemImage::create(
//                                           "pay1.png",
//                                           "pay2.png",
//                                           CC_CALLBACK_1(HelloWorld::menuPayCallback, this));
//
//    payItem->setPosition(Vec2(origin.x + visibleSize.width / 2 + payItem->getContentSize().width / 2,
//                              origin.y + visibleSize.height / 2 - 200));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, loginItem, payItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto back = LayerColor::create(Color4B(116, 196, 249, 255), 960, 640);

    // position the sprite on the center of the screen
//    back->setAnchorPoint(Vec2(0.5, 0.5));
    back->setPosition(Vec2((visibleSize.width - 960) / 2, (visibleSize.height - 640) /2));
    this->addChild(back, 0);

    auto logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(visibleSize.width/2 + origin.x + 30, visibleSize.height/2 + origin.y + 150));
    
    // add the sprite as a child to this layer
    this->addChild(logo, 0);
    
    loadingImg = Sprite::create("logo.png");
    loadingImg->setPosition(Vec2(visibleSize.width/2 + origin.x + 30, visibleSize.height/2 + origin.y + 150));
    this->addChild(loadingImg, 0);
    
    RotateBy* rb = RotateBy::create(0.1f, 30);
    loadingImg->runAction(RepeatForever::create(rb));

    //显示框
    scrollView = cocos2d::ui::ScrollView::create();

    scrollView_height = 200;
    
    scrollView->setSize(Size(600, 200));
    scrollView->setInnerContainerSize(Size(600, scrollView_height));
    scrollView->setBackGroundColor(Color3B(0, 0, 0));
    
    this->addChild(scrollView);
    scrollView->setPosition(Vec2((960 - 600) / 2, 180));
    
    scrollView_line = 0;
    
    showLoading(false);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::addLog(cocos2d::__String str)
{
    Label* label = Label::create();
    
    label->setSystemFontSize(24);
    
    label->setString(str.getCString());
    
    label->setAnchorPoint(Vec2(0, 0));
    
    label->setPosition(Vec2(0, scrollView_line * 26));
    
    scrollView_line ++;
    
    scrollView->addChild(label);
    
    int h = 200;
    if(scrollView_line * 26 > h)
        h = scrollView_line * 26;
    
    scrollView->setInnerContainerSize(Size(600, h));
    
}

void HelloWorld::menuLoginCallback(Ref* pSender)
{
    if(loadingImg->isVisible())
        return;
    
    addLog("点击登陆按钮");
    
    loginItem->setEnabled(false);
}

void HelloWorld::menuPayCallback(Ref* pSender)
{
    if(loadingImg->isVisible())
        return;
    
    int i = arrayOfItems.getIndex((MenuItem*)pSender);
    
    char str[128];
    sprintf(str, "点击充值按钮 %s", mProductIDArray.at(i).asString().c_str());
    addLog(str);
    
    loadingImg->setVisible(true);
}

void HelloWorld::menuSwitchCallback(Ref* pSender)
{
    if(loadingImg->isVisible())
        return;
    
    addLog("点击切换按钮");
}

void HelloWorld::showLoading(bool bShow)
{
    loadingImg->setVisible(bShow);
}



