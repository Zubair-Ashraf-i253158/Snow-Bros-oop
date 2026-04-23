#include "Player.h"
#include "SnowBall.h"

 
Player::Player()
{
    // texture load karo file se
    if (!playerTexture.loadFromFile("assets/playerSprites.png"))
    {
        // agar texture load na ho to red rectangle banao
        sf::RectangleShape PLAYER;
        PLAYER.setSize(sf::Vector2f(50, 50));
        PLAYER.setFillColor(sf::Color::Red);
    }

    playerSprite.setTexture(playerTexture);
    playerSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
    playerSprite.setPosition(400, 400);
}

void Player::update(Platform platforms[], int count)
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
    if (!facingRight)
    {
        playerSprite.setScale(-1.0f, 1.0f); // horizontally flip karo
        playerSprite.setOrigin(60, 0);      // origin fix karo flip ke liye
    }
    else
    {
        playerSprite.setScale(1.0f, 1.0f);  // normal scale
        playerSprite.setOrigin(0, 0);       // normal origin
    }

    
    // check karo player chal raha hai ya nahi
   
    bool moving = sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

    if (moving)
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
        // jump frame y=64 par hai spritesheet mein
        playerSprite.setTextureRect(sf::IntRect(0, 64, 60, 64));
    
    else if (moving)
        // walk frames - x badlta rehta hai animation ke liye
        playerSprite.setTextureRect(sf::IntRect(animFrame * 60, 0, 60, 64));
    
    else
        // idle frame - bilkul pehla frame
        playerSprite.setTextureRect(sf::IntRect(0, 0, 60, 64));

   
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
        bool top = (p_bndry.top + p_bndry.height >= pl_bndry.top) && (p_bndry.top + p_bndry.height <= pl_bndry.top + 10);

        if (side && top)
        {
            // player ko platform ke upar rakh do
            playerSprite.setPosition(playerSprite.getPosition().x , pl_bndry.top - p_bndry.height);  
            jumpSpeed = 0;
            Ground = true; // ab ground par hai
        }
    }

    //fire
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && fire)
    {
        fire = true; // fire start karo
        for(int i=0 ; i<ballcount ; i++)
        {
            ball[i].setfire(playerSprite.getPosition().x + 30, playerSprite.getPosition().y + 30); // snowball ko player ke thoda aage set karo
            ball[i].shoot(facingRight ? 1.0f : -1.0f);
        }

    }
    for (int i = 0; i < ballcount; i++)
    {
        ball[i].update();
    }
}


void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // player sprite draw karo
    target.draw(playerSprite, states);
	
    for(int i=0 ; i<ballcount ; i++)
    ball[i].draw(target); // snowball draw karo
	
}