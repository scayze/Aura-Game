#include "PolygonBody.h"

PolygonBody::PolygonBody() : Body()
{
	bodyType = Polygon;
	isStatic = true;
}

void PolygonBody::debugDraw(sf::RenderWindow * rW)
{
	Body::debugDraw(rW);
}

void PolygonBody::clearPoints()
{
	points.clear();
}

void PolygonBody::addPoint(sf::Vector2f vec)
{
	points.push_back(vec);

	updateAABB();
}

std::vector<sf::Vector2f>& PolygonBody::getPoints()
{
	return points;
}

void PolygonBody::setPoints(std::vector<sf::Vector2f> vec)
{
	points.clear();
	points = vec;

	updateAABB();
}

void PolygonBody::updateAABB()
{
	float right = 0;
	float down = 0;

	for (unsigned int i = 0; i < points.size(); i++)
	{
		if (points[i].x < aabb.left) aabb.left = points[i].x;
		if (points[i].y < aabb.top) aabb.top = points[i].y;

		if (points[i].x > right) right = points[i].x;
		if (points[i].y > down) down = points[i].y;
	}

	aabb.width = right - aabb.left + 2;
	aabb.height = down - aabb.top + 2;

	aabb.left = aabb.left + pos.x -1;
	aabb.top = aabb.top + pos.y -1 ;


}

bool PolygonBody::testPoint(sf::Vector2f v)
{
	return false;
}

float PolygonBody::rayCast(sf::Vector2f position, sf::Vector2f dir)
{
	sf::Vector2f v1;
	sf::Vector2f v2;
	sf::Vector2f v3 = sf::Vector2f(-dir.y, dir.x);


	//Unreasonable high number
	float closest = std::numeric_limits<float>().max();

	for (unsigned int i = 0; i <= points.size(); i++)
	{
		v1 = position - pos + points[i];

		//v2 = i != points.size() ? pos + points[i + 1] : pos + points[0];
		if (i != points.size())	v2 = pos + points[i + 1];
		else					v2 = pos + points[0];

		float dot = Math::vectorDot(v2, v3);
		float t1 = Math::vectorCross(v2, v1) / dot;
		float t2 = Math::vectorDot(v1, v3) / dot;

		if (t1 >= 0.f && (t2 >= 0.f && t2 <= 1.f))
		{
			if (t1 < closest)
			{
				closest = t1;
			}
		}

	}

	if (closest != std::numeric_limits<float>().max()) return closest;
	else return -1.f;
}

void PolygonBody::updateCenterOfMass()
{

}
