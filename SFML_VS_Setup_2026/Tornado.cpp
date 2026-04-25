#include "Tornado.h"
//ab lag gai na chot bola tha projecvt kar la football khailnay ka shoq tha :)
//Messi ban rha tha 
//suiiiiiiiiiiiii

Tornado::Tornado(float x, float y) : FlyingFooga(x, y)
{
	//enemy.setSize(sf::Vector2f(30, 30));
	//enemy.setFillColor(sf::Color::Yellow);
    enemyTexture.loadFromFile("assets/tor.png");
    enemy.setTexture(enemyTexture);
    enemy.setScale(
        80.0f / enemyTexture.getSize().x,  // auto fit to 60px wide
        84.0f / enemyTexture.getSize().y   // auto fit to 64px tall
    );
    speedE = 2.0f;  
	healthE = 3.0f; //health
	zindaE = true;
	groundE = false;
	directionE = 1.0f; // Start moving right
	
	flyingE = false;    // is flying
	flyy = -2.0f;     //fly ki speed vertical
	flyx = 3.0f;      //fly ki speed horizonatal
	flyTime = 0.0f;  //time jab tak enemy fly karega
	//enemy.setFillColor(sf::Color::White);
	//knife 
    knifeTime = 0.0f;
    zindaK = false;
    knifex = 0.0f;
    knifey = 0.0f;
    knife.setSize(sf::Vector2f(15, 5));
	knife.setFillColor(sf::Color::White);
}
void Tornado::update(Platform platforms[], int count, sf::Vector2f p_pos)
{
    // tornado random speed sa udta ha
    if (!flyingE)
        flyx = (rand() % 5) + 2;
    knifeTime++;
    FlyingFooga::update(platforms, count);
    if (knifeTime > 200) // knife phainknay ka time
    {
        zindaK = true;
        knifeTime = 0;
        knife.setPosition(enemy.getPosition()); //pAHLA TORNADO KA PAS AYE 

        // PLAYER KO NISHANA
        float dx = p_pos.x - enemy.getPosition().x;
        float dy = p_pos.y - enemy.getPosition().y;
        float dist = sqrt(dx * dx + dy * dy);        //calculating distance between player and tornado
        knifex = (dx / dist) * 5.0f; //speed ka sath 
        knifey = (dy / dist) * 5.0f;
    }
    // knife 
    if (zindaK)
    {
        knife.move(knifex, knifey);
        // knife boundaries cross
             //for left                                   for right                                  for top                                    for bottom 
        if (knife.getPosition().x < 0 || knife.getPosition().x > 800 || knife.getPosition().y < 0 || knife.getPosition().y > 600)
            zindaK = false;
    }
}
    /*Knife active needed for collision*/

    void Tornado::setK_Act(bool a)
    {
        zindaK = a;
	}
    bool Tornado::getK_Act() const
    {
        return zindaK;
    }
    sf::FloatRect Tornado::getK_Bounds() const
    {
        return knife.getGlobalBounds();
    }



void Tornado::draw(sf::RenderWindow& window)
{
    if (zindaE)
    {
        window.draw(enemy);
		if (zindaK)
            window.draw(knife);
    }
}