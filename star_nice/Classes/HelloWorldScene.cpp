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

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    /*
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
*/
    //背景图片
    bg_sprite_1 = Sprite::create("bg1.png");
    
    this->bg_sprite_1_s = bg_sprite_1->getContentSize();
    
    bg_sprite_1->setAnchorPoint(Vec2(0, 0));
    bg_sprite_1->setPosition(Vec2(origin.x,origin.y));
    this->addChild(bg_sprite_1, -10);
    
    bg_sprite_2 = Sprite::create("bg1.png");
    
    this->bg_sprite_2_s = bg_sprite_2->getContentSize();
    
    bg_sprite_2->setAnchorPoint(Vec2(0, 0));
    bg_sprite_2->setPosition(Vec2(bg_sprite_1_s.width + origin.x, origin.y));
    this->addChild(bg_sprite_2, -10);

    
    //前景图片
    
    pic = Sprite::create("pic12.png");
    this->pic_s = pic->getContentSize();
    
    pic->setAnchorPoint(Vec2(0.5,0));
    pic->setPosition(Vec2(visibleSize.width/2,0));
    //this->addChild(pic, -9);
    
    
    
    //clippingnode创建
    clippingNode = ClippingNode::create();
    clippingNode->setContentSize(Size(visibleSize.width, visibleSize.height));
    clippingNode->setAnchorPoint(Vec2(0, 0));
    clippingNode->setPosition(Vec2(origin.x,origin.y));
    
    clippingNode->setInverted(true);
    clippingNode->setAlphaThreshold(0.5f);
    this->addChild(clippingNode,1);
    
    
    //底板
    clippingNode->addChild(pic,1);
    
    
    //模版
    
    zone_num = 9;
    int zone_cut = sqrt(zone_num);
    int p_size_width = 480/zone_cut;
    int p_size_height = 480/zone_cut;
    int radis_max = (480/(2*zone_cut))*0.8;
    int radis_min = (480/(2*zone_cut))*0.2;
    
    
    stencilall = Node::create();
  
    //随机数因子
    timeval psv;
    gettimeofday(&psv, NULL);
    unsigned rand_seed = psv.tv_sec*1000 + psv.tv_usec/1000;
    srand(rand_seed);
    

    for (int i = 0; i < zone_num; i ++) {
        
        auto p_x = (i%zone_cut)*p_size_width+80;//可选择区域的起始位置x
        auto p_y = (i/zone_cut)*p_size_height+80;//可选择区域的起始位置y
        
        //int rand_radis = rand()%(radis_max-radis_min)+radis_min;//生成半径随机数
        int rand_radis = 45;
        int rand_pos_x = rand()%(p_size_width-2*rand_radis);//生成位置x随机数
        int rand_pos_y = rand()%(p_size_height-2*rand_radis);//生成位置x随机数
        //log("%d", rand_pos_x);
        //log("%d", rand_pos_y);
        //log("%d", rand_radis);
        
        int circle_x =rand_pos_x+p_x;//确定这个圆的起始位置x，随机
        int circle_y =rand_pos_y+p_y;//确定这个圆的结束位置y，随机
        //int circle_radis = rand_radis;//确定这个圆的半径，随机
        int circle_radis = 45;
        //downSprites.pushBack(downS);
        //log("%d", circle_x);
        //log("%d", p_x);
        //log("%d", circle_y);
        //log("%d", p_y);
        //挖洞
        
        auto *stencil = Node::create();
        //const int maxTrangle= 360;
        //顶点数组
        //Vec2 circleVec2[maxTrangle];
        //计算圆上面的各个点的坐标
        /*for (int j = 0; j < maxTrangle; j ++)
        {
            float x = cosf( j * (M_PI/180.f)) * circle_radis+ circle_radis+circle_x;
            //log("%f", x);
            float y = sinf( j * (M_PI/180.f)) * circle_radis+ circle_radis+circle_y;
            //log("%f", y);
            circleVec2[j] = Vec2(x, y);
        }
        
        Color4F white = {1, 1, 1, 1};
        stencil->drawPolygon(circleVec2, maxTrangle, white, 1, white);
        
        //模版
        */
        auto ball = Sprite::create("000.png");
        ball->setPosition(Vec2(circle_radis+circle_x,circle_radis+circle_y));
        stencil->addChild(ball);
        //stencilall->addChild(stencil);
        stencilAll.insert(i,stencil);

        
        //圆形的假精灵，用于显示
        //log("%d", circle_x);
        //log("%d", circle_y);
        //log("%d", 640-(circle_y+2*circle_radis));
        //log("aaaaaaa");
        
        auto spritechild = Sprite::create("pic12.png",Rect(circle_x, 640-(circle_y+2*circle_radis), circle_radis*2, circle_radis*2));
        spritechild->setAnchorPoint(Vec2(0.5,0.5));
        auto rotateBy = RotateBy::create(30, 360);
        auto actions = Sequence::create(rotateBy,NULL);
        spritechild->runAction(RepeatForever::create(actions));
        spritechild->setPosition(Vec2(circle_radis,circle_radis));
        //this->addChild(spritechild,20);
        //upfakeSprites.pushBack(spritechild);
        
        std::string str = Value(i).asString();
        upfakeSprites.insert(i,spritechild);
        
        
        //方形的真精灵，用于检测，在假精灵上面，但透明不可见
        auto spritechild_show = Sprite::create("pic12.png",Rect(circle_x, 640-(circle_y+2*circle_radis), circle_radis*2, circle_radis*2));
        spritechild_show->setPosition(Vec2(circle_x,circle_y+560));
        spritechild_show->setAnchorPoint(Vec2(0,0));
        spritechild_show->setVisible(false);
        //upSprites.pushBack(spritechild_show);
        
        this->addChild(spritechild_show,4);
        movableSprites.insert(i,spritechild_show);
        
        
        //下方的洞的方形的真精灵，用于检测，在洞上面，但透明不可见
        auto spritechild_show_down = Sprite::create("pic12.png",Rect(circle_x, 640-(circle_y+2*circle_radis), circle_radis*2, circle_radis*2));
        spritechild_show_down->setPosition(Vec2(circle_x,circle_y));
        spritechild_show_down->setAnchorPoint(Vec2(0,0));
        spritechild_show_down->setVisible(false);
        //upSprites.pushBack(spritechild_show);
        
        this->addChild(spritechild_show_down,4);
        movableSprites_down.insert(i,spritechild_show_down);
        
        Value check_x(circle_x);
        Value check_y(circle_y);
        Value check_y1(circle_y+560);
        Value check_width(2*circle_radis);
        Value check_height(2*circle_radis);

        movable_x.insert(std::make_pair(str,check_x));
        movable_y.insert(std::make_pair(str,check_y));
        movable_y1.insert(std::make_pair(str,check_y1));
        movable_width.insert(std::make_pair(str,check_width));
        movable_height.insert(std::make_pair(str,check_height));
        
        
        //clippingnode创建
        auto clippingNode_cp = ClippingNode::create();
        clippingNode_cp->setContentSize(Size(circle_radis*2, circle_radis*2));
        clippingNode_cp->setAnchorPoint(Vec2(0,0));
        clippingNode_cp->setPosition(Vec2(circle_x,circle_y+560));
        clippingNode_cp->setInverted(false);
        clippingNode_cp->setAlphaThreshold(0.5f);
        this->addChild(clippingNode_cp,3);
        
        
        
        
        //底板
        clippingNode_cp->addChild(spritechild,4);
        
        upClippingNode.insert(i,clippingNode_cp);
        
        
        auto *stencil_cp = CCDrawNode::create();
        
        auto ball1 = Sprite::create("444.png");
        ball1->setPosition(Vec2(circle_radis,circle_radis));
        stencil_cp->addChild(ball1);

        
        /*for (int j = 0; j < maxTrangle; j ++)
        {
            //float x = cosf( j * (M_PI/180.f)) * circle_radis+ circle_radis+circle_x;
            float x = cosf( j * (M_PI/180.f)) * circle_radis+circle_radis;
            //log("%f", x);
            //float y = sinf( j * (M_PI/180.f)) * circle_radis+ circle_radis+circle_y+590;
            float y = sinf( j * (M_PI/180.f)) * circle_radis+circle_radis;

            
            //log("%f", y);
            circleVec2[j] = Vec2(x, y);
        }
        Color4F white = {1, 1, 1, 1};
        stencil_cp->drawPolygon(circleVec2, maxTrangle, white, 1, white);
        //this->addChild(stencil_cp,20);
         */
        
        
        clippingNode_cp->setStencil(stencil_cp);
        
        
    }
    
    
    std::vector<int> mapKeyVec;
    mapKeyVec = stencilAll.keys();
    for(auto key : mapKeyVec)
    {
        stencilall->addChild(stencilAll.at(key));
    }
    clippingNode->setStencil(stencilall);
    
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
  
    //调用scheduleUpdate进行滚动地图处理
    scheduleUpdate();
    
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    Point touchLocation = this->convertTouchToNodeSpace(touch);
    this->selectSpriteForTouch(touchLocation);
    return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    //判断是否选中精灵
    Point touchLocation = this->convertTouchToNodeSpace(touch);
    
    if (selSprite){
    if ( selSprite->getBoundingBox().containsPoint(touchLocation) )
    {
        
    

    Point touchLocation = this->convertTouchToNodeSpace(touch);
    
    Point oldTouchLocation = touch->getPreviousLocation();
    oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);
    
    Point translation = touchLocation - oldTouchLocation;
    this->panForTranslation(translation);
    
    }
    }
}

Point HelloWorld::boundLayerPos(Point newPos)
{
    Size winSize = Director::getInstance()->getWinSize();
    Point retval = newPos;
    
    /* if(retval.x > 0)
     retval.x = 0;
     if(retval.x < -background->getContentSize().width+winSize.width)
     retval.x = -background->getContentSize().width+winSize.width;  */
    retval.x = MIN(retval.x, 0);
    retval.x = MAX(retval.x, -background->getContentSize().width+winSize.width);
    
    retval.y = this->getPosition().y;
    return retval;
}

void HelloWorld::panForTranslation(Point translation)
{
    if (selSprite)
    {
        Point newPos = selSprite->getPosition() + translation;
        selSprite->setPosition(newPos);
        
        std::vector<int> mapKeyVec;
        mapKeyVec = movableSprites.keys();
        for(auto key : mapKeyVec)
        {
            
            if (selSprite == movableSprites.at(key)) {
                upClippingNode.at(key)->setPosition(newPos);
            }
        }
        
    }
    else
    {
        //Point newPos = this->getPosition() + translation;
        //this->setPosition( this->boundLayerPos(newPos) );
    }
}


void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    Point touchLocation = this->convertTouchToNodeSpace(touch);
    
    
    if (selSprite)
    {
        int flag = -1;
        int flagDown = -1;
        std::vector<int> mapKeyVec;
        mapKeyVec = movableSprites.keys();
        for(auto key : mapKeyVec)
        {
            if (selSprite == movableSprites.at(key))
            {
                flag = key;
                std::vector<int> mapKeyVecDown;
                mapKeyVecDown = movableSprites_down.keys();
                for(auto keyDown : mapKeyVecDown)
                {
                    if (movableSprites_down.at(keyDown)->getBoundingBox().containsPoint(touchLocation))
                    {
                        flagDown = keyDown;
                    }
                }
                
            }
        }
        if((flag!=-1)&&(flag==flagDown))
        {
            /*std::string str = Value(flag).asString();
            int x = movable_x[str].asInt();
            int y = movable_y[str].asInt();
            upClippingNode.at(flag)->setPosition(Vec2(x, y));
            movableSprites.at(flag)->setPosition(Vec2(x, y));*/
            
            stencilall->removeChild(stencilAll.at(flag));
    
            upClippingNode.at(flag)->setVisible(false);
            upClippingNode.erase(flag);
            movableSprites.erase(flag);
            movableSprites_down.erase(flag);
            //upClippingNode.at(flag)->setVisible(false);
            //如果释放点在该精灵的所属区域内，则卡入，并且停止转动
        }else if(((flag!=-1)&&(flagDown!=-1))&&(flag!=flagDown))
        {
            log("out");
            //如果释放点在其他精灵的所属区域内，则结束游戏
        }else if(flag!=-1){
             //如果释放点在不在任何精灵的所属区域内，该精灵回到原位
            std::string str = Value(flag).asString();
            int x = movable_x[str].asInt();
            int y = movable_y1[str].asInt();
            //log("out");
            selSprite->setPosition(Vec2(x,y));
            upClippingNode.at(flag)->setPosition(Vec2(x,y));
        }else{
            
        }
        
    }

    //Point endPos = (Vec2(320,1000));
    //selSprite->setPosition(endPos);
    
}

void HelloWorld::selectSpriteForTouch(Point touchLocation)
{
    Sprite * newSprite = NULL;
    std::vector<int> mapKeyVec;
    mapKeyVec = movableSprites.keys();
    for(auto key : mapKeyVec)
    //for (Sprite *sprite : movableSprites)
    {
        
        if ( movableSprites.at(key)->getBoundingBox().containsPoint(touchLocation) )
       {
            newSprite = movableSprites.at(key);
            break;
       }
    }
    if (newSprite != selSprite && NULL != newSprite)
   {
        if (NULL != selSprite)
        {
           selSprite->stopAllActions();
           selSprite->runAction(RotateTo::create(0.1, 0));
        }
        RotateBy * rotLeft = RotateBy::create(0.1, -14.0);
        RotateBy * rotCenter = RotateBy::create(0.1, 0.0);
        RotateBy * rotRight = RotateBy::create(0.1, 14.0);
        Sequence * rotSeq = Sequence::create(rotLeft, rotCenter, rotRight, rotCenter, NULL);
        newSprite->runAction(RepeatForever::create(rotSeq));
        selSprite = newSprite;
   
    }
}


void HelloWorld::update(float dt)
{
    
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 bg_sprite_1_p = bg_sprite_1->getPosition();
    Vec2 bg_sprite_2_p = bg_sprite_2->getPosition();

    
    
    bg_sprite_1->setPosition(Vec2(bg_sprite_1_p.x -4, bg_sprite_1_p.y));
    bg_sprite_2->setPosition(Vec2(bg_sprite_2_p.x -4, bg_sprite_2_p.y));
    
    
    float a = 8;
    
    if (bg_sprite_1_p.x < - this->bg_sprite_1_s.width)
    {
        bg_sprite_1->setPosition(Vec2((this->bg_sprite_1_s.width + origin.x)- a,origin.y));
        
    };
    if (bg_sprite_2_p.x < - this->bg_sprite_2_s.width)
    {
        bg_sprite_2->setPosition(Vec2((this->bg_sprite_2_s.width + origin.x)- a,origin.y));
        
    }
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
