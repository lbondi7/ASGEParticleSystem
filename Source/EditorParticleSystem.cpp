#include "EditorParticleSystem.h"

bool EditorParticleSystem::init(ASGE::Renderer * renderer, ASGE::Input * input_, int density, float e_r)
{

	particle_density = density;
	emission_rate = e_r;
	for (int j = 0; j < particle_density; j++)
	{
		Particle* part = new Particle(renderer);
		particle.push_back(part);
	}
	if (particle_density > 0)
	{
		particle[particle_num]->Active(true);
		particle_num++;
	}
	return false;
}

void EditorParticleSystem::update(float dt)
{
	time += dt;
	float checker = (1.0f / emission_rate);
	if (time > checker && particle_num < particle_density)
	{
		particle[particle_num]->Active(true);
		particle_num++;
		time = 0.0f;
	}
	for (int i = 0; i < particle_num; i++)
	{
		if (particle[i]->Active())
		{
			particle[i]->updateParticle(dt, 0, 0);
		}
	}
}

void EditorParticleSystem::render(ASGE::Renderer * renderer)
{
	for (int i = 0; i < particle_num; i++)
	{
		if (particle[i]->Active())
		{
			particle[i]->render(renderer);
		}
	}
}

Particle* EditorParticleSystem::getParticle(int i)
{
	return particle[i];
}

void EditorParticleSystem::updateParticleSystemValues(ASGE::Renderer * renderer, int density, float e_r)
{
	particle.clear();
	particle_density = density;
	emission_rate = e_r;
	particle_num = 0;
	for (int j = 0; j < particle_density; j++)
	{
		Particle* part = new Particle(renderer);
		//part->alterParticle(texture, width, height, v, m_a, a_o, r_a, l, e_x, e_y, e_l, e_h, t_o, o_c_r, colours, c_c_r);
		particle.push_back(part);
	}
	if (particle_density > 0)
	{
		particle[particle_num]->Active(true);
		particle_num++;
	}
}
