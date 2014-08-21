/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Maratis
// MBParticleSystem.h
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
// Copyright (c) 2003-2011 Anael Seghezzi <www.maratis3d.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================


#include <MEngine.h>
#include "MBParticleSystem.h"
#include <string>

// Shader
std::string particleVertShader =
"#version 140\n"
"uniform mat4 ProjModelViewMatrix;"
"uniform float SizeMultiplier = 100.0f;"
"uniform mat4 NormalMatrix;"
"attribute vec3 Vertex;"
"attribute vec4 Color;"
"varying vec4 Data;"

"const float constAtten  = 0.9;"
"const float linearAtten = 0.6;"
"const float quadAtten   = 0.001;"

"void main(void)"
"{"
    "gl_Position = ProjModelViewMatrix * vec4(Vertex, 1.0);"
    "Data = Color;"
    "float dist = length(gl_Position.xyz);"
    "float attn = Color.x*100.0f * inversesqrt(constAtten+linearAtten*dist + quadAtten*dist*dist);"
    "gl_PointSize = attn;"
"}\n";

std::string particleFragShader =
"#version 140\n"
"uniform sampler2D Texture[5];"
"varying vec4 Data;"

"void main(void)"
"{"
    "gl_FragColor = texture2D(Texture[0], gl_PointCoord);"
    "gl_FragColor.w = min(gl_FragColor.w, Data.y);"
"}\n";

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Init
/////////////////////////////////////////////////////////////////////////////////////////////////////////

MBParticleSystem::MBParticleSystem(MObject3d * parentObject):
MBehavior(parentObject),
m_lifeTime(2000),
m_particlePositions(NULL),
m_particleColors(NULL),
m_speedDivergence(0.0f),
m_lifeDivergence(0),
m_alpha(1.0),
m_alphaDivergence(0.0),
m_size(1.0),
m_sizeDivergence(0.0),
m_emissionDelay(0.0),
m_textureFile(""),
m_texRef(NULL),
m_fx(0),
m_speedMultiplier(1.0),
m_emissionTimer(0)
{}

MBParticleSystem::MBParticleSystem(MBParticleSystem & behavior, MObject3d * parentObject):
MBehavior(parentObject),
m_lifeTime(behavior.m_lifeTime),
m_speedDivergence(behavior.m_speedDivergence),
m_lifeDivergence(behavior.m_lifeDivergence),
m_alpha(behavior.m_alpha),
m_alphaDivergence(behavior.m_alphaDivergence),
m_size(behavior.m_size),
m_sizeDivergence(behavior.m_sizeDivergence),
m_emissionDelay(behavior.m_emissionDelay),
m_particlePositions(NULL),
m_particleColors(NULL),
m_textureFile(""),
m_texRef(NULL),
m_fx(0),
m_speedMultiplier(behavior.m_speedMultiplier),
m_emissionTimer(0)
{}

MBParticleSystem::~MBParticleSystem(void)
{
    SAFE_DELETE(m_particlePositions);
}

void MBParticleSystem::destroy(void)
{
	delete this;
}

MBehavior * MBParticleSystem::getNew(MObject3d * parentObject)
{
    return new MBParticleSystem(parentObject);
}

MBehavior * MBParticleSystem::getCopy(MObject3d * parentObject)
{
    return new MBParticleSystem(*this, parentObject);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Variables
/////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned int MBParticleSystem::getVariablesNumber(void){
    return 13;
}

MVariable MBParticleSystem::getVariable(unsigned int id)
{
	switch(id)
	{
    case 0:
        return MVariable("LifeTime", &m_lifeTime, M_VARIABLE_FLOAT);
        break;
    case 1:
        return MVariable("ParticlesNumber", &m_particlesNumber, M_VARIABLE_FLOAT);
        break;
    case 2:
        return MVariable("InitialSpeed", &m_initialSpeed, M_VARIABLE_VEC3);
        break;
    case 3:
        return MVariable("Gravity", &m_gravity, M_VARIABLE_VEC3);
        break;
    case 4:
        return MVariable("SpeedDivergence", &m_speedDivergence, M_VARIABLE_FLOAT);
        break;
    case 5:
        return MVariable("LifeDivergence", &m_lifeDivergence, M_VARIABLE_FLOAT);
        break;
    case 6:
        return MVariable("Size", &m_size, M_VARIABLE_FLOAT);
        break;
    case 7:
        return MVariable("SizeDivergence", &m_sizeDivergence, M_VARIABLE_FLOAT);
        break;
    case 8:
        return MVariable("Texture", &m_textureFile, M_VARIABLE_STRING);
        break;
    case 9:
        return MVariable("SpeedMultiplier", &m_speedMultiplier, M_VARIABLE_FLOAT);
        break;
    case 10:
        return MVariable("Alpha", &m_alpha, M_VARIABLE_FLOAT);
        break;
    case 11:
        return MVariable("AlphaDivergence", &m_alphaDivergence, M_VARIABLE_FLOAT);
        break;
    case 12:
        return MVariable("EmissionDelay", &m_emissionDelay, M_VARIABLE_FLOAT);
        break;
	default:
		return MVariable("NULL", NULL, M_VARIABLE_NULL);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Events
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void MBParticleSystem::update(void)
{
	MEngine * engine = MEngine::getInstance();
	MGame * game = engine->getGame();
	MLevel * level = engine->getLevel();
	MScene * scene = level->getCurrentScene();

	MObject3d * parent = getParentObject();
    updateParticles(parent->getTransformedPosition());
}

void MBParticleSystem::draw()
{
    MEngine* engine = MEngine::getInstance();
    MRenderingContext* render = engine->getRenderingContext();
    MGame * game = engine->getGame();

    if(m_particlePositions == NULL || m_particlesNumber == 0)
        return;

    if(m_texRef == NULL)
    {
        if(strcmp(m_textureFile.getSafeString(), "") == 0)
            return;

        char string[256];
        getGlobalFilename(string, engine->getSystemContext()->getWorkingDirectory(), m_textureFile.getSafeString());

        m_texRef = engine->getLevel()->loadTexture(string);

        if(m_texRef == NULL)
        {
            MLOG_ERROR("Could not load particle texture! Setting particle count to 0");
            m_particlesNumber = 0;
            return;
        }
    }

    if(m_fx == 0)
    {
        render->createVertexShader(&m_vertShad);
        render->sendShaderSource(m_vertShad, particleVertShader.c_str());

        render->createPixelShader(&m_pixShad);
        render->sendShaderSource(m_pixShad, particleFragShader.c_str());

        render->createFX(&m_fx, m_vertShad, m_pixShad);
    }

    render->setDepthMask(false);

    if(m_texRef && m_texRef->getTextureId() > 0)
    {
        render->enableTexture();
        //render->setBlendingMode(M_BLENDING_ADD);
        render->enableBlending();
        render->setBlendingMode(M_BLENDING_ALPHA);
        m_texRef->update();
    }

    render->bindFX(m_fx);
    int texIds[4] = { 0, 1, 2, 3 };
    render->sendUniformInt(m_fx, "Textures", texIds, 4);

    // projmodelview matrix
    static MMatrix4x4 ProjMatrix;
    static MMatrix4x4 ModelViewMatrix;
    static MMatrix4x4 ProjModelViewMatrix;

    render->getProjectionMatrix(&ProjMatrix);
    render->getModelViewMatrix(&ModelViewMatrix);
    ProjModelViewMatrix = ProjMatrix * ModelViewMatrix;
    render->sendUniformMatrix(m_fx, "ProjModelViewMatrix", &ProjModelViewMatrix);

    render->sendUniformVec3(m_fx, "Camera", engine->getLevel()->getCurrentScene()->getCurrentCamera()->getTransformedPosition());
    render->setPointSize(m_size);

    render->enableVertexArray();
    render->setVertexPointer(M_FLOAT, 3, m_particlePositions);

    render->enableColorArray();
    render->setColorPointer(M_FLOAT, 4, m_particleColors);

    int vertexAttrib;
    render->getAttribLocation(m_fx, "Vertex", &vertexAttrib);
    render->setAttribPointer(vertexAttrib, M_FLOAT, 3, m_particlePositions);
    render->enableAttribArray(vertexAttrib);

    int colorAttrib;
    render->getAttribLocation(m_fx, "Color", &colorAttrib);
    render->setAttribPointer(colorAttrib, M_FLOAT, 4, m_particleColors);
    render->enableAttribArray(colorAttrib);

    render->drawArray(M_PRIMITIVE_POINTS, 0, m_particles.size());
    render->setDepthMask(true);

    render->disableAttribArray(vertexAttrib);
    render->disableAttribArray(colorAttrib);

    render->disableBlending();
    render->enableDepthTest();
    render->bindFX(0);
    render->bindTexture(0);
}

#define RANDOM 0.5 - 2.0*static_cast<float>(rand()) / static_cast<float>(RAND_MAX)

void MBParticleSystem::updateParticles(MVector3 parentPosition)
{
    MEngine* engine = MEngine::getInstance();
    MSystemContext* system = engine->getSystemContext();

    unsigned long currentTime = system->getSystemTick();
    Particle* particle;
    bool updateColorData = false;

    // Mark dead particles for deletion
    for(int i = 0; i < m_particles.size(); i++)
    {
        particle = &m_particles[i];
        if(particle->time <= currentTime)
            particle->alive = false;
    }

    // Delete dead particles
    for(int i = 0; i < m_particles.size(); i++)
    {
        particle = &m_particles[i];
        if(!particle->alive)
        {
            updateColorData = true;
            m_particles.erase(m_particles.begin() + i);
        }
    }

    if(currentTime < m_emissionTimer)
    {
        applySpeed();
        updateArrays(updateColorData);
        return;
    }

    m_emissionTimer = currentTime + m_emissionDelay;

    // Create missing particles
    Particle newParticle;
    MVector3 divergence;

    for(int i = m_particles.size(); i < m_particlesNumber; i++)
    {
        divergence.x = RANDOM * m_speedDivergence;
        divergence.y = RANDOM * m_speedDivergence;
        divergence.z = RANDOM * m_speedDivergence;

        newParticle.alive = true;
        newParticle.time = currentTime + m_lifeTime + RANDOM * m_lifeDivergence;
        newParticle.speed = m_initialSpeed + divergence;
        newParticle.size = m_size + RANDOM * m_sizeDivergence;
        newParticle.alpha = m_alpha + RANDOM * m_alphaDivergence;
        newParticle.position = parentPosition;
        m_particles.push_back(newParticle);
    }

    applySpeed();
    updateArrays(updateColorData);
}

void MBParticleSystem::updateArrays(bool updateColorData)
{
    Particle* particle;
    // Create vertex buffer
    if(m_particlePositions == NULL)
    {
        m_particlePositions = new MVector3[static_cast<int>(m_particlesNumber)];
    }

    // Create "color" buffer
    if(m_particleColors == NULL)
    {
        m_particleColors = new MVector4[static_cast<int>(m_particlesNumber)];
        updateColorData = true;
    }

    for(int i = 0; i < m_particles.size(); i++)
    {
        m_particlePositions[i] = m_particles[i].position;
    }

    if(updateColorData)
    {
        MVector4* color;
        for(int i = 0; i < m_particles.size(); i++)
        {
            color = &m_particleColors[i];
            particle = &m_particles[i];
            color->x = particle->size;
            color->y = particle->alpha;
            color->z = particle->spin;
        }
    }
}

void MBParticleSystem::applySpeed()
{
    // Update existing positions
    Particle* particle;
    for(int i = 0; i < m_particles.size(); i++)
    {
        particle = &m_particles[i];
        particle->position += particle->speed * m_speedMultiplier;
        particle->speed += m_gravity;
    }
}
