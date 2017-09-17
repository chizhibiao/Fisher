#include "Fish.h"
#include "StaticData.h"
enum{
	k_Action_Animate = 0
};
Fish::Fish(void)
{
}
Fish::~Fish(void)
{
}

Fish *Fish::create(FishType type /* = k_Fish_Type_SmallFish */)
{
	Fish *fish = new Fish;
	if (fish && fish->init(type))
	{
		fish->autorelease();
		return fish;
	}
	else
	{
		CC_SAFE_DELETE(fish);
		return NULL;
	}
	
}
bool Fish::init(FishType type /* = k_Fish_Type_SmallFish */)
{

	if (!CCNode::init())
	{
		return false;
	}
	if (type < k_Fish_Type_SmallFish || type >= k_Fish_Type_Count)
	{
		type = k_Fish_Type_SmallFish;
	}
	setType(type);
	//_type=type;
	CCString *animationName = CCString::createWithFormat(STATIC_DATA_STRING("fish_animation_format"),_type + 1);
	CCAnimation *animation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
	CCAnimate *animate = CCAnimate::create(animation);
	animate->setTag(k_Action_Animate);
	_fishSprite = CCSprite::create();
	addChild(_fishSprite);
	_fishSprite->runAction(CCRepeatForever::create(animate));
	return true;
}
int getScore()
{
	return 0;
}
int getSpeed()
{
	return 200;
}
CCRect Fish::getCollisionArea()
{
	CCPoint point = getParent()->convertToWorldSpace(getPosition());
	CCSize  size = _fishSprite->getContentSize();
	return CCRectMake(point.x - size.width / 2,point.y - size.height / 2,size.width,size.height);
}
