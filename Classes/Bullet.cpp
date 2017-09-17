#include "Bullet.h"
#include "StaticData.h"


enum{
	k_Bullet_Action = 0
};
Bullet::Bullet(void)
{
}


Bullet::~Bullet(void)
{
}


bool Bullet::init()
{
	if (!CCNode::init())
	{
		return false;
	}
	//weapon_bullet_%02d.png
	CCString *fileName = CCString::createWithFormat(STATIC_DATA_STRING("bullet_frame_format"),1);
	_bulletSprite = CCSprite::createWithSpriteFrameName(fileName->getCString());
	_bulletSprite->setAnchorPoint(ccp(0.5,1));
	//_bulletSprite->setDisplayFrame()
	addChild(_bulletSprite);
	return true;
}


float Bullet::getSpeed(int type)
{
	float speed = 640;
	switch(type)
	{
	case 0:
		speed = 640;
		break;
	case 1:
		speed = 640;
		break;
	case 2:
		speed = 460;
		break;
	case 3:
		speed = 440;
		break;
	case 4:
		speed = 650;
		break;
	case 5:
		speed = 410;
		break;
	case 6:
		speed = 390;
		break;
	default:
		break;
	}
	return speed;
}

void Bullet::flyTo(CCPoint targetInWordSpace, int type/*=0*/)
{
	CCPoint startInNodeSpace = CCPointZero;
	this->setPosition(startInNodeSpace);
	CCPoint startInWorldSpace = getParent()->convertToWorldSpace(getPosition());
	
	this->setVisible(true);
	float angle = ccpAngleSigned(ccpSub(targetInWordSpace,startInWorldSpace),CCPointMake(0,1));
	this->setRotation(CC_RADIANS_TO_DEGREES(angle));
	CCString *bulletFrameName = CCString::createWithFormat(STATIC_DATA_STRING("bullet_frame_format"),type + 1);
	_bulletSprite->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(bulletFrameName->getCString()));
	CCPoint targetInNodeSpace = getParent()->convertToNodeSpace(targetInWordSpace);
	
	float duration = ccpDistance(targetInWordSpace,startInWorldSpace) / getSpeed(type);
	CCMoveTo *moveTo = CCMoveTo::create(duration,targetInNodeSpace);
	CCCallFunc *callFunc = CCCallFunc::create(this,callfunc_selector(Bullet::end));
	
	CCSequence *sequence = CCSequence::create(moveTo,callFunc,NULL);
	sequence->setTag(k_Bullet_Action);
	this->runAction(sequence);
}

void Bullet::end()
{
	//_bulletSprite->stopActionByTag(k_Bullet_Action);
	//_bulletSprite->stopAllActions();
	stopActionByTag(k_Bullet_Action);
	this->setVisible(false);
}

CCPoint Bullet::getCollisionPoint()
{
	//return getParent()->convertToWorldSpace(_bulletSprite->getPosition()) ;
	return getParent()->convertToWorldSpace(getPosition()) ;
}