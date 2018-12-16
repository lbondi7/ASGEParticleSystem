#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem()
{
}

bool ParticleSystem::init(ASGE::Renderer * renderer, ASGE::Input * input_, std::string type, int particle_system_num)
{

	particle_system_id = particle_system_num;

	world_offset[0] = std::unique_ptr<float>(new float(diff[0]));
	world_offset[1] = std::unique_ptr<float>(new float(diff[1]));

	particle_num = 0;
	system_name = type;
	FileSystem file;
	if (file.getTxtFileContent(type))
	{
		particle_density = std::stoi(file.retrieveContent(0));
		emission_rate = std::stof(file.retrieveContent(1));
		for (int j = 0; j < particle_density; j++)
		{
			//Particle part;
			particle.push_back(new Particle);
		}
		for (int j = 0; j < particle_density; j++)
		{
			particle[j]->createParticle(renderer, file);
			particle[j]->Active(false);
		}
		particle[0]->Active(true);
		particle_num++;
		return true;
	}
	//setParticles(type, renderer);
	return false;
}

bool ParticleSystem::setParticles(std::string &type, ASGE::Renderer * renderer)
{
	particle_num = 0;
	FileSystem file;
	if (file.getTxtFileContent(type))
	{
		particle_density = std::stoi(file.retrieveContent(0));
		for (int j = 0; j < particle_density; j++)
		{
			particle[j]->createParticle(renderer, file);
			particle[j]->Active(false);
		}
		particle[0]->Active(true);
		particle_num++;
		return true;
	}
	return false;
}

void ParticleSystem::update(float dt, int sel_part_sys, float x_dif, float y_dif)
{
	if (active)
	{
		if (sel_part_sys == particle_system_id)
		{
			diff[0] += x_dif;
			diff[1] += y_dif;
		}


		world_offset[0] = std::unique_ptr<float>(new float(diff[0]));
		world_offset[1] = std::unique_ptr<float>(new float(diff[1]));

		time += dt;
		float checker = (1.0f / emission_rate);
		if (time > checker && particle_num < particle_density)
		{
			particle[particle_num]->Active(true);
			particle_num++;
			time = 0.0f;
		}
		//if (time > 0.1 && particle_num < particle_density)
		//{
		//	particle[particle_num]->particleActive(true);
		//	particle_num++;
		//	time = 0.0;
		//}
		for (int i = 0; i < particle_num; i++)
		{
			if (particle[i]->Active())
			{
				particle[i]->updateParticle(dt, *world_offset[0], *world_offset[1]);
			}
		}
	}
}

void ParticleSystem::render(ASGE::Renderer * renderer)
{
	if (active)
	{
		for (int i = 0; i < particle_num; i++)
		{
			if (particle[i]->Active())
			{
				particle[i]->render(renderer);
			}
		}
	}
}

void ParticleSystem::setDifference(float x_pos, float y_pos)
{
	x_dif.clear();
	y_dif.clear();

	for (int i = 0; i < particle.size(); i++)
	{
		x_dif.push_back(x_pos - particle[i]->spriteComponent()->getSprite()->xPos());
		y_dif.push_back(y_pos - particle[i]->spriteComponent()->getSprite()->yPos());
	}
	em_x_dif = x_pos - particle[0]->emitterXPos();
	em_y_dif = y_pos - particle[0]->emitterYPos();
}

void ParticleSystem::updateParticleSystemPos(float x_pos, float y_pos)
{
	for (int i = 0; i < particle.size(); i++)
	{
		particle[i]->emitterXPos(x_pos - em_x_dif);
		particle[i]->emitterYPos(y_pos - em_y_dif);
		particle[i]->spriteComponent()->getSprite()->xPos(x_pos - x_dif[i]);
		particle[i]->spriteComponent()->getSprite()->yPos(y_pos - y_dif[i]);
	}
}

void ParticleSystem::setActive(bool value)
{
	active = value;
}

bool ParticleSystem::isActive()
{
	return active;
}

std::string ParticleSystem::systemName()
{
	return system_name;
}

int ParticleSystem::getParticleAmount()
{
	return particle_density;
}

Particle* ParticleSystem::getParticle(int i)
{
	return particle[i];
}
