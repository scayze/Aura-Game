#include "Aura.h"
#include "Figur.h"
#include <iostream>
#include "ParticleSystem\ParticleSystem.h"
#include "ParticleSystem\ShapeEmitter.h"
Aura::Aura(float x, float y) : WorldObject(x,y)
{

	Resources::loadTexture(texture,"Sword.png");
    rotspd = 8;

	delete body;
	body = new EdgeBody();
	body->setCollisionType(t_aura);
	body->addCollisionWith(t_gegner);
	body->setPos(x, y);
	body->setMass(-1);


	sf::RectangleShape * pRect = new sf::RectangleShape;
	pRect->setFillColor(sf::Color(200, 200, 200));
	pRect->setSize(sf::Vector2f(3, 3));
	pRect->setOrigin(1.5f, 1.5f);

	emit1 = new RectangleEmitter(sf::Vector2f(x, y));
	emit1->setShape(pRect);
	emit1->setDensity(0.1f);
	emit1->setLifetime(120);
	emit1->setLifetimeOffset(30);
	emit1->setMaxVelocity(0.f);

	emit2 = new RectangleEmitter(sf::Vector2f(x, y));
	emit2->setShape(pRect);
	emit2->setDensity(0.1f);
	emit2->setLifetime(120);
	emit2->setLifetimeOffset(30);
	emit2->setMaxVelocity(0.f);

	emit3 = new RectangleEmitter(sf::Vector2f(x, y));
	emit3->setShape(pRect);
	emit3->setDensity(0.1f);
	emit3->setLifetime(120);
	emit3->setLifetimeOffset(30);
	emit3->setMaxVelocity(0.f);

}

void Aura::init(Spielfeld * spiel)
{
	WorldObject::init(spiel);
    sprite.setOrigin(-32,sprite.getGlobalBounds().height/2);
	//static_cast<CircleBody*>(body)->setRadius(80);
	static_cast<EdgeBody*>(body)->setP2(sf::Vector2f(body->getPos().x + 80, body->getPos().y));

	spielfeld->getParticleSystem()->addEmitter(emit1);
	spielfeld->getParticleSystem()->addEmitter(emit2);
	spielfeld->getParticleSystem()->addEmitter(emit3);
}

void Aura::tick()
{
	WorldObject::tick();
	sprite.setRotation(sprite.getRotation()+rotspd);
	EdgeBody * b = static_cast<EdgeBody*>(body);

	body->updateAABB();
	b->setP2(Math::vectorRotateAroundPoint(b->getP2(), sf::Vector2f(0,0), rotspd / 180.f * Math::PI()));

	emit1->setPosition(sf::Vector2f(body->getPos() + Math::vectorSetMagnitude(b->getP2(), (sprite.getLocalBounds().width+32) / 5 * 2)));
	emit2->setPosition(sf::Vector2f(body->getPos() + Math::vectorSetMagnitude(b->getP2(), (sprite.getLocalBounds().width+32) / 5 * 3)));
	emit3->setPosition(sf::Vector2f(body->getPos() + Math::vectorSetMagnitude(b->getP2(), (sprite.getLocalBounds().width+32) / 5 * 4)));
}

void Aura::collide(WorldObject * object)
{
	if (object->getBody()->getCollisionType() == t_gegner)
	{
		if (!static_cast<Figur*>(object)->isInvincible()) rotspd = -rotspd;
		static_cast<Figur*>(object)->dealDamage(damage);
	}
}

float Aura::getRotspeed()
{
	return rotspd;
}

void Aura::setRotspeed(float rs)
{
	rotspd = rs;
}