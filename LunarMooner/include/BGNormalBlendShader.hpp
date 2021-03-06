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

#ifndef LM_BLEND_SHADER_HPP_
#define LM_BLEND_SHADER_HPP_

#include <LMShaderIds.hpp>

namespace lm
{
    static const std::string normalBlendFrag =
        "#version 120\n"
        "uniform sampler2D u_baseTexture;\n"
        "uniform sampler2D u_detailTexture;\n"

        "uniform vec2 u_detailOffset = vec2(0.0);\n"

        "void main()\n"
        "{\n"
        "    vec3 baseColour = texture2D(u_baseTexture, gl_TexCoord[0].xy).rgb * 2.0 + vec3(-1.0, -1.0, 0.0);\n"
        "    vec2 textureOffset = u_detailOffset + (baseColour.rg * 0.35);\n"

        "    vec3 detailColour = texture2D(u_detailTexture, gl_TexCoord[0].xy + textureOffset).rgb * vec3(-2.0, -2.0, 2.0) + vec3(1.0, 1.0, -1.0);\n"
        "    vec3 blended = normalize(baseColour * dot(baseColour, detailColour) / baseColour.b - detailColour);\n"
        "    blended = blended * 0.5 + 0.5;\n"

        "    gl_FragColor = vec4(blended, 1.0);\n"
        "}\n";

    static const std::string materialPrepassFrag =
        "#version 120\n"
        "uniform sampler2D u_distortionTexture;\n"
        "uniform sampler2D u_normalTexture;\n"
        "uniform sampler2D u_diffuseTexture;\n"
        "uniform sampler2D u_maskTexture;\n"

        "uniform vec2 u_detailOffset = vec2(0.0);\n"

        "const float maxDist = 0.49 * 0.49;\n"

        "void main()\n"
        "{\n"
        "    vec2 dir = vec2(0.5) - gl_TexCoord[0].xy;\n"
        "    float dist = dot(dir, dir);\n"
        "    float alpha = 1.0;\n"
        "    if(dist > maxDist) discard;\n"

        "    vec3 distortionVector = texture2D(u_distortionTexture, gl_TexCoord[0].xy).rgb * 2.0 + vec3(-1.0, -1.0, 0.0);\n"
        "    vec2 textureOffset = u_detailOffset + (distortionVector.rg * 0.35);\n"

        "    vec3 normalColour = texture2D(u_normalTexture, gl_TexCoord[0].xy + textureOffset).rgb * vec3(-2.0, -2.0, 2.0) + vec3(1.0, 1.0, -1.0);\n"
        "    vec3 blendedNormal = normalize(distortionVector * dot(distortionVector, normalColour) / distortionVector.b - normalColour);\n"
        "    blendedNormal = blendedNormal * 0.5 + 0.5;\n"

        "    gl_FragData[0] = vec4(blendedNormal, 1.0);\n"
        "    gl_FragData[1] = texture2D(u_diffuseTexture, gl_TexCoord[0].xy + textureOffset);\n"
        "    gl_FragData[2] = texture2D(u_maskTexture, gl_TexCoord[0].xy + textureOffset);\n"
        "}\n";
}

#endif //LM_BLEND_SHADER_HPP_
