#pragma once
#include "GameObject.h"

class Particle : public GameObject
{
public:

	Particle();

	Particle(ASGE::Renderer * renderer);
	~Particle();

	void createParticle(ASGE::Renderer * renderer, FileSystem file);

	void alterParticle(std::string texture, float width, float height, float v, int m_a, int a_o, bool r_a, float l, float e_x, float e_y, float e_l, float e_h, std::vector<float> t_o, std::vector<float> o_c_r, std::vector<ASGE::Colour> colours, std::vector<float> c_c_r);

	void setTexture(std::string texture);
		
	void setDimensions(float width, float height);
		
	void setVelocity(float v);
		
	void setAngles(int m_a, int a_o, bool r_a);
		 
	void setLifetime(float l);
		 
	void setOpacity(std::vector<float> t_o, std::vector<float> o_c_r);
		 
	void setColour(std::vector<ASGE::Colour> colours, std::vector<float> c_c_r);
		
	void setEmitterType(int e_t, float donut_width);
		 
	void setEmitterPosDim(float e_x, float e_y, float e_l, float e_h);

	void setEmitter();

	void resetParticle();

	void updateParticle(float dt_sec, float x_offset, float y_offset);

	void updateColour();

	void updateOpacity();

	float lerp(float start_pos, float end_pos, float percent);

	void particleLifeTime(float value);

	float emitterYPos();

	float particleLifeTime();

	float particleMaxLifeTime();

	void emitterXPos(float value);

	float emitterXPos();

	void emitterYPos(float value);

private:

	void resetAngle();

	int max_angle = 0;
	int angle_offset = 0;
	float angle = 0.0f;
	bool randomise_angle = false;
	float velocity = 0.0f;
	float life_time = 0.0f;
	float max_life_time = 0.0f;
	float opacity = 0.0f;
	std::vector<float> target_opacity{ 0.0f, 0.0f, 0.0f };
	std::vector<float> opacity_change_rate{ 0.0f, 0.0f };
	std::vector<ASGE::Colour> target_colour{ ASGE::COLOURS::WHITE, ASGE::COLOURS::WHITE, ASGE::COLOURS::WHITE, ASGE::COLOURS::WHITE, ASGE::COLOURS::WHITE };
	std::vector<float> colour_change_rate{ 1.0f, 1.0f, 1.0f, 1.0f };

	enum EmitterType {
		RECTANGLE = 0,
		CIRCLE = 1,
		DONUT = 2,
		SEMI_CIRCLE = 3
	};
	EmitterType emitter_type = RECTANGLE;
	float donut_width = 0.0f;
	rect emitter;
	int opacity_index = 0;
	int colour_index = 0;

	bool skip = true;

	float offset[2];
};