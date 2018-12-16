#pragma once
#include <Engine\OGLGame.h>

#include "Particle.h"

class EditorParticleSystem
{
public:

	EditorParticleSystem() = default;
	virtual ~EditorParticleSystem() = default;

	bool init(ASGE::Renderer * renderer, ASGE::Input * input, int density, float e_r);
	void update(float dt);
	void render(ASGE::Renderer* renderer);
	Particle * getParticle(int i);
	void updateParticleSystemValues(ASGE::Renderer * renderer, int density, float e_r);

private:

	std::vector<Particle*> particle;

	int particle_density = 0;
	float emission_rate = 0;
	float time = 0.0f;
	int particle_num = 0;
};
