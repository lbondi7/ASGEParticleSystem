#pragma once
#include <Engine\OGLGame.h>

#include "Particle.h"

class ParticleSystem
{
public:

	ParticleSystem() = default;
	~ParticleSystem();

	bool init(ASGE::Renderer * renderer, ASGE::Input * input, std::string type, int particle_system_num);
	bool setParticles(std::string &type, ASGE::Renderer * renderer);
	void update(float dt, int sel_part_sys, float x_dif, float y_dif);
	void render(ASGE::Renderer* renderer);
	void setDifference(float x_pos, float y_pos);
	void updateParticleSystemPos(float x_pos, float y_pos);
	void setActive(bool value);
	bool isActive();
	std::string systemName();
	int getParticleAmount();
	Particle* getParticle(int i);
private:

	std::vector<Particle*> particle;

	std::vector<float> x_dif;
	std::vector<float> y_dif;

	float diff[2]{ 0, 0 };
	std::unique_ptr<float> world_offset[2];
	float em_x_dif = 0.0f, em_y_dif = 0.0f;
	int particle_type = 0;
	int particle_system_id = 0;
	int max_particles = 500;
	int particle_density = 0;
	float emission_rate = 0.0f;
	float time = 0.0f;
	int particle_num = 0;
	bool active = false;
	std::string system_name = "";

};