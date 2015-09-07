#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void selectSpriteForTouch(cocos2d::Point touchLocation);
    cocos2d::Point boundLayerPos(cocos2d::Point newPos);
    void panForTranslation(cocos2d::Point translation);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    
    void update(float dt);
    
    
    cocos2d::Size bg_sprite_1_s;
    cocos2d::Size bg_sprite_2_s;
    cocos2d::Size pic_s;
    cocos2d::Map<int, cocos2d::Sprite*> movableSprites;
    cocos2d::Map<int, cocos2d::Sprite*> upSprites;
    cocos2d::Map<int, cocos2d::Sprite*> upfakeSprites;
    cocos2d::Map<int, cocos2d::Sprite*> movableSprites_down;

    cocos2d::ValueMap movable_x;
    cocos2d::ValueMap movable_y;
    cocos2d::ValueMap movable_y1;
    cocos2d::ValueMap movable_width;
    cocos2d::ValueMap movable_height;
    

    
    //cocos2d::Map<std::string, cocos2d::Value*> movable_x;
    //cocos2d::Map<std::string, cocos2d::Value*> movable_y;
    //cocos2d::Map<std::string, cocos2d::Value*> movable_width;
    //cocos2d::Map<std::string, cocos2d::Value*> movable_height;
    
    cocos2d::Sprite * selSprite;
    cocos2d::Map<int, cocos2d::ClippingNode *> upClippingNode;
    cocos2d::ClippingNode * clippingNode;
    cocos2d::Map<int, cocos2d::Node *> stencilAll;
    cocos2d::Sprite * sprite_yuan;
    cocos2d::Sprite * sprite_yuan_11;
    cocos2d::Sprite * background;
    cocos2d::Node * stencilall;
    int zone_num;
    
protected:
    cocos2d::Sprite *bg_sprite_1;
    cocos2d::Sprite *bg_sprite_2;
    cocos2d::Sprite *pic;
    

};

#endif // __HELLOWORLD_SCENE_H__
