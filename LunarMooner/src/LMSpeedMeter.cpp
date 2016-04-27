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

#include <LMSpeedMeter.hpp>

#include <xygine/Resource.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

using namespace lm;

namespace
{
    const float radius = 80.f;
}

SpeedMeter::SpeedMeter(xy::MessageBus& mb, float maxVal, xy::TextureResource& tr, sf::Shader& shader)
    :xy::Component  (mb, this),
    m_maxValue      (maxVal),
    m_shader        (shader)
{
    m_mainTexture = tr.get("assets/images/game/console/velocimeter.png");
    m_arrowTexture = tr.get("assets/images/game/console/velocity_marker.png");
    m_normalTexture = tr.get("assets/images/game/console/velocity_normal.png");

    //first 4 verts are red ring
    sf::Vector2f size(m_mainTexture.getSize());
    m_vertices[1].position.x = size.x / 2.f;
    m_vertices[1].texCoords.x = size.x / 2.f;
    m_vertices[2].position = { size.x / 2.f, size.y };
    m_vertices[2].texCoords = m_vertices[2].position;
    m_vertices[3].position.y = size.y;
    m_vertices[3].texCoords.y = size.y;

    //followed by overlay
    //m_vertices[4].position.x = { size.x / 2.f };
    m_vertices[4].texCoords.x = size.x / 2.f;
    m_vertices[5].position.x = size.x / 2.f;
    m_vertices[5].texCoords.x = size.x;
    m_vertices[6].position = { size.x / 2.f, size.y };
    m_vertices[6].texCoords = size;
    m_vertices[7].position.y = size.y;
    m_vertices[7].texCoords = { size.x / 2.f, size.y };

    m_shape.setRadius(radius);
    m_shape.setOrigin(radius, radius);
    m_shape.setPosition(size.x / 4.f, size.y / 2.f);
    m_shape.setTexture(&m_arrowTexture);
}

//public
void SpeedMeter::entityUpdate(xy::Entity&, float) 
{
    //drops down to near zero when no player
    setValue(m_currentValue * 0.9f);
}

void SpeedMeter::setValue(float val)
{
    const float ratio = std::min(val / m_maxValue, 1.f);

    //set alpha of first 4 verts
    sf::Color colour(255, 255, 255, static_cast<sf::Uint8>(ratio * 255.f));
    for (auto i = 0u; i < 4u; ++i)
    {
        m_vertices[i].color = colour;
    }

    m_currentValue = val;
}


//private
void SpeedMeter::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
    states.texture = &m_arrowTexture;
    states.shader = &m_shader;
    rt.draw(m_shape, states);

    states.texture = &m_mainTexture;
    states.shader = nullptr;
    rt.draw(m_vertices.data(), m_vertices.size(), sf::Quads, states);
}