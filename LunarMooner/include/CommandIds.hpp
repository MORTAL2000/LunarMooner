/*********************************************************************
Matt Marchant 2016
http://trederia.blogspot.com

LunarMooner - Zlib license.

This software is provided 'as-is', without any express or
implied warranty. In no event will the authors be held
liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute
it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but
is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any
source distribution.
*********************************************************************/

#ifndef COMMAND_IDS_HPP_
#define COMMAND_IDS_HPP_

#include <xygine/MessageBus.hpp>

enum LMCommandID
{
    Mothership = 0x1,
    GameController = 0x2,
    Human = 0x4,
    Player = 0x8,
    Alien = 0x10,
    UI = 0x20,
    Item = 0x40,
    DropShip = 0x80
};

enum LMInputFlags
{
    SteerLeft = 0x1,
    SteerRight = 0x2,
    Thrust = 0x4,
    Shoot = 0x8,
    Start = 0x10
};

enum LMMessageId
{
    GameEvent = xy::Message::Count,
    StateEvent,
    MenuEvent
};

struct LMGameEvent
{
    enum
    {
        PlayerDied,
        PlayerLanded,
        PlayerSpawned,
        PlayerGotAmmo,
        PlayerGotShield,
        HumanRescued,
        HumanPickedUp,
        AlienDied,
        ExtraLife,
        ItemCollected,
        MeteorExploded,
        LaserFired
    }type;
    float posX = 0.f;
    float posY = 0.f;
    sf::Int16 value = 0;
};

struct LMStateEvent
{
    enum
    {
        GameOver,
        SummaryFinished,
        RoundBegin,
        RoundEnd,
        CountDownStarted
    }type;
};

struct LMMenuEvent
{
    sf::Uint32 playerId = 0u;
    sf::Uint32 score = 0u;
};

enum LMParticleID
{
    Thruster = 0,
    RcsLeft,
    RcsRight,
    RoidTrail,
    SmallExplosion
};

enum LMSoundID
{
    Engine,
    RCS,
    Laser,
    Explosion01,
    Explosion02,
    Explosion03,
    Explosion04,
    Nuke,
    Warning
};

#endif //COMMAND_IDS_HPP_
