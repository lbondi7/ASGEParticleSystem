#include "FileSystem.h"
#include <string>
#include <iostream>
#include <fstream>  


FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

void FileSystem::getTxtFiles(int num)
{
	std::vector<std::string> block;

	std::fstream file_paths_txt;
	std::string line;
	file_paths_txt.open("Resources\\TxtFiles\\FilePaths\\filePaths.txt");
	while (getline(file_paths_txt, line)) {

		block.push_back(line);
	}
	file_paths_txt.close();

	std::fstream particle_file_path;
	std::string particle_file_path_line;
	particle_file_path.open(block[num]);
	while (getline(particle_file_path, particle_file_path_line))
	{
		//files.push_back(particle_file_path_line);
	}
	particle_file_path.close();
}

int FileSystem::returnFileAmount(int value)
{
	if (value == 0)
	{
		return 2;
	}
	if (value == 1)
	{
		return 2;
	}
}


bool FileSystem::getTxtFileContent(std::string type)
{
	content.clear();
	std::fstream file;
	std::string line;

	file.open("Resources\\TxtFiles\\FilePaths\\" + type + ".txt");
	if (file.is_open())
	{
		while (getline(file, line)) {
			int finder = line.find("{");
			int finder2 = line.find("~");
			if (finder > -1 || finder2 > -1)
			{
				continue;
			}
			else {
				int index = line.find(':');
				int index2 = -1;
				std::string new_line = line.substr((index + 1), line.size());
				std::string file_data = "";
				for (int i = 0; i < new_line.length(); ++i) {
					if (new_line[i] != ',') {
						file_data += new_line[i];
					}
					else if(new_line[i] == ',') {
						content.push_back(file_data);
						file_data = "";
					}

					if (i == new_line.length() - 1)
					{
						content.push_back(file_data);
						file_data = "";
					}
				}
			}
				//index2 = new_line.find(',');
				//if (index2 > 0)
				//{
				//	std::string value_1 = new_line.substr(0, (index2));
				//	std::string value_2 = new_line.substr((index2 + 1), new_line.size());
				//	int index3 = -1;
				//	content.push_back(value_1);
				//	index3 = value_2.find(",");
				//	if (index3 > 0)
				//	{
				//		std::string value_3 = value_2.substr(index3 + 1, value_2.size());
				//		int index4 = -1;
				//		value_2 = value_2.substr(0, index3);
				//		content.push_back(value_2);
				//		index4 = value_3.find(",");
				//		if (index4 > 0)
				//		{
				//			std::string value_4 = value_3.substr(index4 + 1, value_3.size());
				//			value_3 = value_3.substr(0, index4);
				//			content.push_back(value_3);
				//			content.push_back(value_4);
				//		}
				//		else
				//		{
				//			content.push_back(value_3);
				//		}
				//	}
				//	else
				//	{
				//		content.push_back(value_2);
				//	}
				//}
				//else
				//{
				//	content.push_back(new_line);
				//}
			//}
		}
		file.close();
		return true;
	}
	return false;
}

//void FileSystem::getTxtFileContent(int value)
//{
//
//}

void FileSystem::getTxtFileContent()
{
	std::fstream file;
	std::string file_name = "Resources\\TxtFiles\\particle.txt";
	std::string line;
	file.open(file_name);
	if (file.is_open())
	{
		while (getline(file, line)) {
			if (line == "{")
			{
				continue;
			}
			else if (line == "}")
			{
				file.close();
			}
			else {
				int index = line.find(':');
				int index2 = -1;
				std::string new_line = line.substr((index + 1), line.size());
				index2 = new_line.find(',');
				if (index2 > 0)
				{
					std::string x_value = new_line.substr(0, (index2));
					std::string y_value = new_line.substr((index2 + 1), new_line.size());
					content.push_back(x_value);
					content.push_back(y_value);
				}
				else
				{
					content.push_back(new_line);
				}
			}
		}
	}
}

bool FileSystem::createFile(std::string name)
{
	std::fstream file;
	std::string file_name = "Resources\\TxtFiles\\FilePaths\\" + name + ".txt";
	std::string line;
	file.open(file_name);
	if (!file.is_open())
	{
		std::ofstream new_file(file_name);

		std::string buffer;

		buffer += "{PARTICLE DATA}\n";
		buffer += particle_system_buffer;
		buffer += "~~~~~~~~~~~\n";
		buffer += texture_buffer;
		buffer += "~~~~~~~~~~~\n";
		buffer += dimensions_buffer;
		buffer += "~~~~~~~~~~~\n";
		buffer += velocity_buffer;
		buffer += "~~~~~~~~~~~\n";
		buffer += direction_buffer;
		buffer += "~~~~~~~~~~~\n";
		buffer += lifetime_buffer;
		buffer += "~~~~~~~~~~~\n";
		buffer += opacity_buffer;
		buffer += "~~~~~~~~~~~\n";
		buffer += colour_buffer;

		buffer += "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		buffer += "~~~~~~~~~~~~~~~~~~~~~~~~~\n";
		buffer += "~~~~~~~~~~~~~~~~~~~~~~~~~\n";

		buffer += "{EMITTER DATA}\n";
		buffer += emitter_type_buffer;
		buffer += "~~~~~~~~~~~\n";
		buffer += emitter_position_buffer;
		buffer += "~~~~~~~~~~~\n";
		buffer += emitter_dimensions_buffer;
		buffer += "~~~~~~~~~~~\n";

		new_file << buffer << std::endl;
		new_file.close();
		return true;
	}

	return false;
}

void FileSystem::editFile(std::vector<std::string> file_names)
{
	std::fstream file;
	std::string file_name = "Resources\\TxtFiles\\FilePaths\\particleNames.txt";
	std::string line;
	file.open(file_name);
	if (file.is_open())
	{
		std::string buffer;
		for (int i = 0; i < file_names.size(); i++)
		{
			if (i < file_names.size() - 1)
			{
				buffer += file_names[i] += "\n";
			}
			else
			{
				buffer += file_names[i];
			}
		}
		file << buffer << std::endl;
		file.close();
	}
}


std::string FileSystem::retrieveContent(int content_element)
{
	return content[content_element];
}

int FileSystem::retrieveContentSize()
{
	return content.size();
}


std::string FileSystem::retrieveContent(int content_element, int value)
{
	return 0;
}

bool FileSystem::checkFile(std::string file_name)
{
	std::string filename = "";
	std::fstream file;
	filename = "Resources\\Textures\\" + file_name + ".png";
	file.open(filename);
	if (file.is_open())
	{
		return true;
	}
	filename = "Resources\\TxtFiles\\FilePaths\\" + file_name + ".txt";
	file.open(filename);
	if (file.is_open())
	{
		return true;
	}
	return false;
}

void FileSystem::particleSystemBuffer(int density, float emission_rate)
{
	particle_system_buffer = "{Particle System}\n";
	particle_system_buffer += "amount:" + std::to_string(density) + ";\n";
	particle_system_buffer += "emission rate:" + std::to_string(emission_rate) + ";\n";
}

void FileSystem::textureBuffer(std::string texture)
{
	texture_buffer = "{Texture}\n";
	texture_buffer += "texture:" + texture + ";\n";
}

void FileSystem::dimensionsBuffer(float width, float height)
{
	dimensions_buffer = "{Dimensions}\n";
	dimensions_buffer += "dimensions:" + std::to_string(width) + "," + std::to_string(height) + ";\n";
}

void FileSystem::velocitysBuffer(float velocity)
{
	velocity_buffer = "{Velocity}\n";
	velocity_buffer += "velocity:" + std::to_string(velocity) + ";\n";
}

void FileSystem::directionBuffer(float max_angle, float angle_offset, int randomise_angle)
{
	direction_buffer = "{Direction(Angle)}\n";
	direction_buffer += "angle:" + std::to_string(max_angle) + ";\n";
	direction_buffer += "angle offset:" + std::to_string(angle_offset) + ";\n";
	direction_buffer += "randomise angle:" + std::to_string(randomise_angle) + ";\n";
}

void FileSystem::lifetimeBuffer(float lifetime)
{
	lifetime_buffer = "{Lifetime}\n";
	lifetime_buffer += "max_life_time:" + std::to_string(lifetime) + ";\n";
}

void FileSystem::opacityBuffer(std::vector<float> opacity, std::vector<float> opacity_change_rate)
{
	opacity_buffer = "{Opacity}\n";
	opacity_buffer += "opacity over lifetime:" + std::to_string(opacity[0]) + "," + std::to_string(opacity[1]) + "," + std::to_string(opacity[2]) + ";\n";
	opacity_buffer += "opacity rate of change:" + std::to_string(opacity_change_rate[0]) + "," + std::to_string(opacity_change_rate[1]) + ";\n";
}

void FileSystem::colourBuffer(std::vector<ASGE::Colour> colours, std::vector<float> colour_change_rate)
{
	colour_buffer = "{Colour}\n";
	colour_buffer += "colour rate of change:" + std::to_string(colour_change_rate[0]) + "," + std::to_string(colour_change_rate[1]) + "," + std::to_string(colour_change_rate[2]) + "," + std::to_string(colour_change_rate[3]) + ";\n";
	colour_buffer += "colour 1:" + std::to_string(colours[0].r) + "," + std::to_string(colours[0].g) + "," + std::to_string(colours[0].b) + ";\n";
	colour_buffer += "colour 2:" + std::to_string(colours[1].r) + "," + std::to_string(colours[1].g) + "," + std::to_string(colours[1].b) + ";\n";
	colour_buffer += "colour 3:" + std::to_string(colours[2].r) + "," + std::to_string(colours[2].g) + "," + std::to_string(colours[2].b) + ";\n";
	colour_buffer += "colour 4:" + std::to_string(colours[3].r) + "," + std::to_string(colours[3].g) + "," + std::to_string(colours[3].b) + ";\n";
	colour_buffer += "colour 5:" + std::to_string(colours[4].r) + "," + std::to_string(colours[4].g) + "," + std::to_string(colours[4].b) + ";\n";
}

void FileSystem::emitterTypeBuffer(std::string type, int type_value)
{
	emitter_type_buffer = "{Emitter Type}\n";
	emitter_type_buffer += "emitter type(" + type + "):" + std::to_string(type_value) + ";\n";
}

void FileSystem::emitterPositionBuffer(float emitter_xpos, float emitter_ypos)
{
	emitter_position_buffer = "{Position}\n";
	emitter_position_buffer += "emitter position:" + std::to_string(emitter_xpos) + "," + std::to_string(emitter_ypos) + ";\n";
}

void FileSystem::emitterDimensionsBuffer(float emitter_length, float emitter_height, float donut_width)
{
	emitter_dimensions_buffer = "{Dimensions}\n";
	emitter_dimensions_buffer += "emitter dimensions:" + std::to_string(emitter_length) + "," + std::to_string(emitter_height) + "," + std::to_string(donut_width) + ";\n";
}

void FileSystem::emitterAngleBuffer(float emitter_length, float emitter_height)
{

}