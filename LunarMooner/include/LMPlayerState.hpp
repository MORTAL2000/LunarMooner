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

#ifndef LM_PLAYER_STATE_HPP_
#define LM_PLAYER_STATE_HPP_

#include <SFML/Config.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

namespace lm
{
    enum class SpecialWeapon
    {
        None,
        DualLaser,
        SideLaser,
        DownLaser,
        EMP
    };

    struct PlayerState final
    {
        sf::Uint32 score = 0u;
        sf::Uint32 previousScore = 0u;
        sf::Int8 lives = 3;
        sf::Uint8 level = 1u;
        sf::Uint8 ammo = 0u;
        sf::Uint8 alienCount = 0u;
        sf::Uint8 humansSaved = 0u;
        std::vector<sf::Vector2f> humansRemaining;
        bool startNewRound = false;
        float timeRemaining = 0.f;
        SpecialWeapon special = SpecialWeapon::None;
        float cooldownTime = 0.f;
    };
}

#endif //LM_PLAYER_STATE_HPP_