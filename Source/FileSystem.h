#pragma once
#include <vector>
#include <Engine\OGLGame.h>

class FileSystem
{
public:
	FileSystem();
	~FileSystem();

	void getTxtFiles(int num);

	int returnFileAmount(int value);

	bool getTxtFileContent(std::string type);

	void getTxtFileContent();

	bool createFile(std::string file_name);

	void editFile(std::vector<std::string> file_names);

	std::string retrieveContent(int content_element);

	int retrieveContentSize();

	std::string retrieveContent(int content_element, int value);

	bool checkFile(std::string file_name);

	void particleSystemBuffer(int density, float emission_rate);

	void textureBuffer(std::string texture);

	void dimensionsBuffer(float width, float height);

	void velocitysBuffer(float velocity);

	void directionBuffer(float max_angle, float angle_offset, int randonmise_angle);

	void lifetimeBuffer(float lifetime);

	void opacityBuffer(std::vector<float> opacity, std::vector<float> opacity_change_rate);

	void colourBuffer(std::vector<ASGE::Colour> colours, std::vector<float> colour_change_rate);

	void emitterTypeBuffer(std::string type, int type_value);

	void emitterPositionBuffer(float emitter_xpos, float emitter_ypos);

	void emitterDimensionsBuffer(float emitter_length, float emitter_height, float donut_width);

	void emitterAngleBuffer(float emitter_length, float emitter_height);


private:

	std::vector<std::string> content;
	std::string particle_system_buffer = " ";
	std::string texture_buffer = " ";
	std::string dimensions_buffer = " ";
	std::string velocity_buffer = " ";
	std::string direction_buffer = " ";
	std::string lifetime_buffer = " ";
	std::string opacity_buffer = " ";
	std::string colour_buffer = " ";
	std::string emitter_type_buffer = " ";
	std::string emitter_position_buffer = " ";
	std::string emitter_dimensions_buffer = " ";
	std::string emitter_angle_buffer = " ";
};
