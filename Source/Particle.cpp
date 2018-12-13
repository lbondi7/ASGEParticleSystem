#include "Particle.h"
#include <random>

Particle::Particle()
{

}

Particle::Particle(ASGE::Renderer* renderer)
{
	addSpriteComponent(renderer, "Resources\\Textures\\GRASS.png");
}

Particle::~Particle()
{

}

void Particle::createParticle(ASGE::Renderer* renderer, FileSystem file)
{
	int x = 2;
	if (addSpriteComponent(renderer, file.retrieveContent(x)))
	{
		x++;
		spriteComponent()->getSprite()->width(std::stof(file.retrieveContent(x)));
		x++;
		spriteComponent()->getSprite()->height(std::stof(file.retrieveContent(x)));
		x++;
		velocity = std::stof(file.retrieveContent(x));
		x++;
		max_angle = std::stoi(file.retrieveContent(x));
		x++;
		angle_offset = std::stoi(file.retrieveContent(x));
		x++;
		randomise_angle = std::stoi(file.retrieveContent(x));
		x++;
		max_life_time = std::stof(file.retrieveContent(x));
		x++;
		emitter.x = std::stof(file.retrieveContent(x));
		x++;
		emitter.y = std::stof(file.retrieveContent(x));
		x++;
		emitter.length = std::stof(file.retrieveContent(x));
		x++;
		emitter.height = std::stof(file.retrieveContent(x));
		x++;
		target_opacity[0] = std::stof(file.retrieveContent(x));
		x++;
		target_opacity[1] = std::stof(file.retrieveContent(x));
		x++;
		target_opacity[2] = std::stof(file.retrieveContent(x));
		x++;
		opacity_change_rate[0] = std::stof(file.retrieveContent(x));
		x++;
		opacity_change_rate[1] = std::stof(file.retrieveContent(x));
		x++;
		colour_change_rate[0] = std::stof(file.retrieveContent(x));
		x++;
		colour_change_rate[1] = std::stof(file.retrieveContent(x));
		x++;
		colour_change_rate[2] = std::stof(file.retrieveContent(x));
		x++;
		colour_change_rate[3] = std::stof(file.retrieveContent(x));
		x++;
		int j = 0;
		while (j < 5)
		{
			target_colour[j].r = std::stof(file.retrieveContent(x));
			x++;
			target_colour[j].g = std::stof(file.retrieveContent(x));
			x++;
			target_colour[j].b = std::stof(file.retrieveContent(x));
			x++;
			j++;
		}
		life_time = max_life_time;
		spriteComponent()->getSprite()->colour(target_colour[0]);
		opacity = target_opacity[0];

		std::random_device rd;
		std::uniform_real_distribution<float> x_dist(emitter.x, emitter.x + emitter.length);
		std::uniform_real_distribution<float> y_dist(emitter.y, emitter.y + emitter.height);
		spriteComponent()->getSprite()->xPos(x_dist(rd));
		spriteComponent()->getSprite()->yPos(y_dist(rd));

		resetAngle();
	}
}

void Particle::alterParticle(ASGE::Renderer* renderer, std::string texture, float width, float height, float v, int m_a, int a_o, bool r_a, float l, float e_x, float e_y, float e_l, float e_h, std::vector<float> t_o, std::vector<float> o_c_r, std::vector<ASGE::Colour> colours, std::vector<float> c_c_r)
{
	spriteComponent()->getSprite()->loadTexture(texture);
	spriteComponent()->getSprite()->width(width);
	spriteComponent()->getSprite()->height(height);
	velocity = v;
	max_angle = m_a;
	angle_offset = a_o;
	randomise_angle = r_a;
	max_life_time = l;
	life_time = max_life_time;
	emitter.x = e_x;
	emitter.y = e_y;
	emitter.length = e_l;
	emitter.height = e_h;
	target_opacity = t_o;
	opacity_change_rate = o_c_r;
	target_colour = colours;
	colour_change_rate = c_c_r;
	opacity = target_opacity[0];

	std::random_device rd;
	std::uniform_real_distribution<float> x_dist(emitter.x, emitter.x + emitter.length);
	std::uniform_real_distribution<float> y_dist(emitter.y, emitter.y + emitter.height);
	spriteComponent()->getSprite()->xPos(x_dist(rd));
	spriteComponent()->getSprite()->yPos(y_dist(rd));

	resetAngle();
}

void Particle::resetParticle()
{
	std::random_device rd;
	std::uniform_real_distribution<float> x_dist(emitter.x, emitter.x + emitter.length);
	std::uniform_real_distribution<float> y_dist(emitter.y, emitter.y + emitter.height);
	spriteComponent()->getSprite()->xPos(x_dist(rd));
	spriteComponent()->getSprite()->yPos(y_dist(rd));
	spriteComponent()->getSprite()->colour(target_colour[0]);

	particleLifeTime(0);
	resetAngle();
	opacity = target_opacity[0];
	opacity_index = 0;
	colour_index = 0;
}

void Particle::resetAngle()
{
	if (randomise_angle)
	{
		if (max_angle > 0)
		{
			if (angle_offset > 0)
			{
				std::random_device rd;
				std::uniform_real_distribution<float> dist(0, max_angle);
				angle = dist(rd);
				angle = angle - angle_offset;
			}
			else
			{
				std::random_device rd;
				std::uniform_real_distribution<float> dist(0, max_angle);
				angle = dist(rd);
			}
		}
		else
		{
			angle = max_angle;
		}
	}
	else if (!randomise_angle)
	{
		angle = max_angle - angle_offset;
	}

	spriteComponent()->getSprite()->rotationInRadians((angle / RADIAN)* -1);
}

void Particle::updateParticle(float dt_sec, float x_offset, float y_offset)
{
	skip = !skip;

	spriteComponent()->getSprite()->xPos(spriteComponent()->getSprite()->xPos() + ((sin(angle / RADIAN) * velocity) * dt_sec));
	spriteComponent()->getSprite()->yPos(spriteComponent()->getSprite()->yPos() + ((cos(angle / RADIAN) * velocity) * dt_sec));

	if (particleLifeTime() < max_life_time)
	{
		life_time += dt_sec;
		//if (!skip)
		//{
		updateOpacity();
		updateColour();
		//}
	}
	if (particleLifeTime() >= max_life_time)
	{
		resetParticle();
	}
	spriteComponent()->getSprite()->opacity(opacity);
}

void Particle::updateColour()
{
	float colour[3];

	float temp_col[3];
	float temp_tar_col[3];

	if (colour_index < 4)
	{
		colour[0] = lerp(target_colour[colour_index].r, target_colour[colour_index + 1].r, (life_time * colour_change_rate[colour_index]) / max_life_time);
		colour[1] = lerp(target_colour[colour_index].g, target_colour[colour_index + 1].g, (life_time * colour_change_rate[colour_index]) / max_life_time);
		colour[2] = lerp(target_colour[colour_index].b, target_colour[colour_index + 1].b, (life_time * colour_change_rate[colour_index]) / max_life_time);

		for (int i = 0; i < 3; i++)
		{
			temp_col[i] = ((float)((int)(colour[i] * 100))) / 100;
		}
		temp_tar_col[0] = ((float)((int)(target_colour[colour_index + 1].r * 100))) / 100;
		temp_tar_col[1] = ((float)((int)(target_colour[colour_index + 1].g * 100))) / 100;
		temp_tar_col[2] = ((float)((int)(target_colour[colour_index + 1].b * 100))) / 100;
	}
	else
	{
		colour[0] = target_colour[colour_index].r;
		colour[1] = target_colour[colour_index].g;
		colour[2] = target_colour[colour_index].b;
	}

	if (temp_col[0] == temp_tar_col[0] && temp_col[1] == temp_tar_col[1] && temp_col[2] == temp_tar_col[2] && colour_index < 4 - 1)
	{
		colour_index++;
	}

	spriteComponent()->getSprite()->colour(colour);
}

void Particle::updateOpacity()
{
	float temp_op[2];

	if (opacity_index < 3)
	{
		if (target_opacity[opacity_index] > target_opacity[opacity_index + 1])
			opacity = lerp(target_opacity[opacity_index], target_opacity[opacity_index + 1], ((life_time * opacity_change_rate[opacity_index]) / max_life_time));

		else if (target_opacity[opacity_index] < target_opacity[opacity_index + 1])
			opacity = lerp(target_opacity[opacity_index], target_opacity[opacity_index + 1], ((life_time * opacity_change_rate[opacity_index]) / max_life_time));

		temp_op[0] = ((float)((int)(opacity * 10))) / 10;
		temp_op[1] = ((float)((int)(target_opacity[opacity_index + 1] * 10))) / 10;
	}
	else
	{
		opacity = target_opacity[opacity_index];
	}

	if (temp_op[0] == temp_op[1] && opacity_index < 3 - 2)
	{
		opacity_index++;
	}
	//spriteComponent()->getSprite()->opacity(opacity);
}

float Particle::lerp(float start_pos, float end_pos, float percent)
{
	return ((1 - percent) *  start_pos + percent * end_pos);
}

void Particle::particleActive(bool value)
{
	active = value;
}

bool Particle::particleActive()
{
	return active;
}

void Particle::particleLifeTime(float value)
{
	life_time = value;
}

float Particle::particleLifeTime()
{
	return life_time;
}

float Particle::particleMaxLifeTime()
{
	return max_life_time;
}

void Particle::emitterXPos(float value)
{
	emitter.x = value;
}

float Particle::emitterXPos()
{
	return emitter.x;
}

void Particle::emitterYPos(float value)
{
	emitter.y = value;
}

float Particle::emitterYPos()
{
	return emitter.y;
}
