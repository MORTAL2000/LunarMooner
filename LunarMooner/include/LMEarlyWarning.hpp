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

#ifndef LM_EARLY_WARNING_HPP_
#define LM_EARLY_WARNING_HPP_

#include <xygine/components/Component.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace lm
{
    class EarlyWarning final : public sf::Drawable, public xy::Component
    {
    public:
        EarlyWarning(xy::MessageBus&, const sf::Vector2f&);
        ~EarlyWarning() = default;

        xy::Component::Type type() const override { return xy::Component::Type::Drawable; }
        void entityUpdate(xy::Entity&, float) override;

        void onDelayedStart(xy::Entity&) override;

    private:
        float m_initialPosition;
        float m_speed;
        float m_scale;
        sf::Vector2f m_destination;

        sf::CircleShape m_shape;
        void draw(sf::RenderTarget&, sf::RenderStates) const override;
    };
}

#endif //LM_EARLY_WARNING_HPP_