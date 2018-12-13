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
	void updateParticleSystemValues(ASGE::Renderer * renderer, std::string texture, int density, float e_r, float width, float height, int m_a, int a_o, int r_a, float v, float l, float e_x, float e_y, float e_l, float e_h, std::vector<float> t_o, std::vector<float> o_c_r, std::vector<ASGE::Colour> colours, std::vector<float> c_c_r);

private:

	std::vector<Particle*> particle;

	int particle_density = 0;
	float emission_rate = 0;
	float time = 0.0f;
	int particle_num = 0;
};
