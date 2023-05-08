#include <SFML/Graphics.hpp>

using namespace sf;

class Arrow : public ConvexShape
{
public:
	Arrow()
	{
		this->setPointCount(4);
		this->setPoint(0, Vector2f(0, 30));
		this->setPoint(1, Vector2f(8, 20));
		this->setPoint(2, Vector2f(15, 30));
		this->setPoint(3, Vector2f(8, 0));

		this->setOrigin(Vector2f(8, 20));
	}
};

Vector2f getRotationCoordinate(Vector2f center, int radius, int angle)
{
	return Vector2f(center.x + radius * cos((90 - angle) % 360 / 57.3), center.y - radius * sin((90 - angle) % 360 / 57.3));
}

int main()
{
	RenderWindow window(VideoMode(800, 600), "homework1");

	Vector2f center(300, 300);
	int hourLength = 110, minuteLength = 140, secondLength = 170;
	int hourAngle = 0, minuteAngle = 0, secondAngle = 0;

	Time delay = seconds(0.05);

	//objects
	CircleShape clock(200);
	CircleShape clockCenter(10);
	CircleShape mark(10);

	RectangleShape arrowHourBase(Vector2f(5, hourLength));
	RectangleShape arrowMinuteBase(Vector2f(5, minuteLength));
	RectangleShape arrowSecondBase(Vector2f(5, secondLength));

	Arrow arrowHour, arrowMinute, arrowSecond;

	//color
	clock.setFillColor(Color(45, 64, 89));
	clockCenter.setFillColor(Color(234, 84, 85));
	mark.setFillColor(Color(234, 84, 85));
	clock.setOutlineThickness(10);
	clock.setOutlineColor(Color(234, 84, 85));

	//position
	clock.setOrigin(Vector2f(200, 200));
	clock.setPosition(center);

	clockCenter.setOrigin(Vector2f(10, 10));
	clockCenter.setPosition(center);

	mark.setOrigin(Vector2f(10, 10));

	arrowHourBase.setOrigin(Vector2f(3, hourLength));
	arrowHourBase.setPosition(center);
	
	arrowMinuteBase.setOrigin(Vector2f(3, minuteLength));
	arrowMinuteBase.setPosition(center);
	
	arrowSecondBase.setOrigin(Vector2f(3, secondLength));
	arrowSecondBase.setPosition(center);

	arrowHour.setPosition(Vector2f(center.x, center.y - hourLength));
	arrowMinute.setPosition(Vector2f(center.x, center.y - minuteLength));
	arrowSecond.setPosition(Vector2f(center.x, center.y - secondLength));
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			while (Keyboard::isKeyPressed(Keyboard::R)) {

				secondAngle += 5;
				minuteAngle = secondAngle / 60;
				hourAngle = minuteAngle / 12;

				arrowSecondBase.setRotation(secondAngle);
				arrowSecond.setRotation(secondAngle);
				arrowSecond.setPosition(getRotationCoordinate(center, secondLength, secondAngle));

				arrowMinuteBase.setRotation(minuteAngle);
				arrowMinute.setRotation(minuteAngle);
				arrowMinute.setPosition(getRotationCoordinate(center, minuteLength, minuteAngle));

				arrowHourBase.setRotation(hourAngle);
				arrowHour.setRotation(hourAngle);
				arrowHour.setPosition(getRotationCoordinate(center, hourLength, hourAngle));

				window.clear();
				window.draw(clock);
				for (int i = 0; i < 360; i += 30)
				{
					mark.setPosition(getRotationCoordinate(center, 170, i));
					window.draw(mark);
				}
				window.draw(arrowHourBase);
				window.draw(arrowHour);
				window.draw(arrowMinuteBase);
				window.draw(arrowMinute);
				window.draw(arrowSecondBase);
				window.draw(arrowSecond);
				window.draw(clockCenter);
				window.display();

				sleep(delay);
			}

			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				delay = seconds(delay.asSeconds()/2);
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				delay = seconds(delay.asSeconds() * 2);
			}
		}
		window.clear();


		window.draw(clock);

		for (int i = 0; i < 360; i += 30)
		{
			mark.setPosition(getRotationCoordinate(center, 170, i));
			window.draw(mark);
		}

		window.draw(arrowHourBase);
		window.draw(arrowHour);
		window.draw(arrowMinuteBase);
		window.draw(arrowMinute);
		window.draw(arrowSecondBase);
		window.draw(arrowSecond);

		window.draw(clockCenter);


		window.display();
	}
		return 0;
}