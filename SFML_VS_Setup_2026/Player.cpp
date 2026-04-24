#include "Player.h"
#include "SnowBall.h"

#include"Botom.h"
Player::Player()
{
    // texture load karo file se
    if (!playerTexture.loadFromFile("assets/player2.png"))
    {
        // agar texture load na ho to red rectangle banao
        sf::RectangleShape PLAYER;
        PLAYER.setSize(sf::Vector2f(60, 64));
        PLAYER.setFillColor(sf::Color::Red);
    }

    playerSprite.setTexture(playerTexture);
    playerSprite.setScale(
        60.0f / playerTexture.getSize().x,  // auto fit to 60px wide
        64.0f / playerTexture.getSize().y   // auto fit to 64px tall
    );
    playerSprite.setPosition(400, 400);
}

void Player::update(Platform platforms[], int count, Enemy* enemy[], int ecount)
{

    // Left arrow se player left jaye
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        facingRight = false;              // player left dekh raha hai to false
        playerSprite.move(-movement, 0); // left move karo
    }

    // Right arrow se player right jaye
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        facingRight = true;              // player right dekh raha hai to true
        playerSprite.move(movement, 0); // right move karo
    }

    // Sprite Flip Karo
    // left ja raha hai to sprite ulta karo
    float scaleX = 60.0f / playerTexture.getSize().x;
    float scaleY = 64.0f / playerTexture.getSize().y;

    if (!facingRight)
    {
        playerSprite.setScale(-scaleX, scaleY);
        playerSprite.setOrigin(60, 0);
    }
    else
    {
        playerSprite.setScale(scaleX, scaleY);
        playerSprite.setOrigin(0, 0);
    }


    // check karo player chal raha hai ya nahi

    bool moving = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    /* if (moving)
      {
          animTimer++;
          if (animTimer > 8) // har 8 frame bad animation frame badlo
          {
              animFrame = (animFrame + 1) % 4; // 4 frames hain walking ke
              animTimer = 0;                   // timer reset karo
          }
      }
      else
      {
          animFrame = 0; // ruka hua hai to pehla frame
          animTimer = 0; // timer reset karo
      }

       //Texture Frame Set Karo
      // jump, walk, idle ke alag alag frames

      if (!Ground)
          // jump frame
          playerSprite.setTextureRect(sf::IntRect(0, 450, 103, 150));

      else if (moving)
          // walk frames - x badlta rehta hai animation ke liye
          playerSprite.setTextureRect(sf::IntRect(animFrame * 103, 0, 103, 150));

      else
          // idle frame - bilkul pehla frame
          playerSprite.setTextureRect(sf::IntRect(0, 0, 103, 150));
          */

          // Jump
          // up arrow press karo aur ground par ho to jump karo

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && Ground)
    {
        jumpSpeed = jump; // upar ki taraf speed do
        Ground = false;   // ab hawa mein hai
    }


    // player screen se bahar na jaye
    if (playerSprite.getPosition().x < 0)
        playerSprite.setPosition(0, playerSprite.getPosition().y);

    if (playerSprite.getPosition().x > 770) // 800 - 30
        playerSprite.setPosition(770, playerSprite.getPosition().y);


    playerSprite.move(0, jumpSpeed); // vertical movement apply karo
    jumpSpeed += gravity;            // gravity se speed badho


    // player platform par land kare
    Ground = false;

    for (int i = 0; i < count; i++)
    {
        // platform aur player ki boundaries lo
        sf::FloatRect pl_bndry = platforms[i].getBounds();
        sf::FloatRect p_bndry = playerSprite.getGlobalBounds();

        // horizontally overlap check karo
        bool side = (p_bndry.left < pl_bndry.left + pl_bndry.width) && (p_bndry.left + p_bndry.width > pl_bndry.left);

        // player ka neeche wala hissa platform ke upar wale hisse se mile
        bool top = (p_bndry.top + p_bndry.height >= pl_bndry.top) && (p_bndry.top + p_bndry.height <= pl_bndry.top + 25);

        if (side && top)
        {
            // player ko platform ke upar rakh do
            playerSprite.setPosition(playerSprite.getPosition().x, pl_bndry.top - p_bndry.height);
            jumpSpeed = 0;
            Ground = true; // ab ground par hai
        }
    }
    /*=================== SNOW BALL CODE ==========================*/
    // Space press karo to ek naya ball shoot karo
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !fire)
    {
        // dhundo ek inactive ball
        for (int i = 0; i < ballcount; i++)
        {
            if (!ball[i].act()) // agar ye ball inactive hai
            {
                // is ball ko shoot karo             right side se                               left side se                                        // hand level
                ball[i].setfire(facingRight ? playerSprite.getPosition().x + 35 : playerSprite.getPosition().x + 95, playerSprite.getPosition().y + 30);

                ball[i].shoot(facingRight ? 1.0f : -1.0f);  //using tenary for choosing direction pf ma para tha and socha tha kabi kaam nahi ai ge :}
                fire = true; // ek ball shoot ho gaya
                break;       // loop band karo ek hi ball chahiye
            }
        }
    }

    // Space chhod do to dobara shoot kar sako
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        fire = false;

    // sare active balls update karo
    for (int i = 0; i < ballcount; i++)
        ball[i].update();


    for (int i = 0; i < ecount; i++)
    {
        if (!enemy[i]->getZinda()) continue;
        for (int j = 0; j < ballcount; j++)
        {
            if (ball[j].act() && enemy[i]->getBounds().intersects(ball[j].getBounds()))
            {
                enemy[i]->hitByBall();
                ball[j].setact(false);
            }
        }
    }

    // full snow ma pack ha to kick karo
    for (int i = 0; i < ecount; i++)
    {
        if (enemy[i]->getState() == 2 && playerSprite.getGlobalBounds().intersects(enemy[i]->getBounds()))
        {
            float kik = playerSprite.getPosition().x < enemy[i]->getPosition().x ? 1.0f : -1.0f;
            enemy[i]->kick(kik);
        }
    }

	// chain ban jati ha . rolling snowball kisi ko hit kare to wo bhi mar jaaye
    for (int i = 0; i < ecount; i++)
    {
        if (enemy[i]->getState() == 3)
        {
            for (int j = 0; j < ecount; j++)
            {
				if (i != j && enemy[j]->getZinda() && enemy[i]->getBounds().intersects(enemy[j]->getBounds()))//kisi aur ko hit karay to wo bhi mar jaaye
                    enemy[j]->setZinda(false);
            }
        }
    }

	// player kisi enemy se takra jaye to life down karo
    for (int i = 0; i < ecount; i++)
    {
        if (enemy[i]->getZinda() && enemy[i]->getState() == 0 &&
            playerSprite.getGlobalBounds().intersects(enemy[i]->getBounds()))
            lifedown();
        if (hit)
        {
            hitTimer++;
            if (hitTimer > 120) // 2 second baad normal
            {

                lives--;
                playerSprite.setPosition(400, 400);
                hit = false;
                hitTimer = 0;
            }
        }
    }
}


/*=================== Collision And HIT And Kill CODE ==========================*/

void Player::lifedown()
{
    if (!hit) // agar player hit nahi hua hai to hi life down karo
    {
        // life kam karo
        hit = true; // ab player hit ho gaya hai
        hitTimer = 0; // hit timer reset karo
        if (lives==0)
            {
			
            
                // game over screen draw karo
			exit(0);
            // game over loic yaha dalna ha abdullah 
            // for now, bas player ko center par reset kar dete hain
          //  playerSprite.setPosition(200, 400);
           // lives = 2; // life reset karo
		}
    }
}

bool Player::gethit() // getter for hit status
{
    return hit;
}

int Player::getlives() const // getter for lives count
{
    return lives;
}

sf::FloatRect Player::getBounds() const
{
    return playerSprite.getGlobalBounds(); // player ki boundary do
}

sf::FloatRect Player::getBallBounds(int index) const
{
    return ball[index].getBounds(); // ball ki boundary do
}

int Player::getballcount() const
{
    return ballcount; // total balls ki count do
}


void Player::setBallActive(int i, bool a)
{
    ball[i].setact(a); // ball active status set karo
}
bool Player::getBallActive(int i) const
{
    return ball[i].act(); // ball active hai ya nahi
}




void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // player sprite draw karo
    target.draw(playerSprite, states);
	
    for(int i=0 ; i<ballcount ; i++)
    ball[i].draw(target); // snowball draw karo
	
}