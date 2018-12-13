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
					std::string value_1 = new_line.substr(0, (index2));
					std::string value_2 = new_line.substr((index2 + 1), new_line.size());
					int index3 = -1;
					content.push_back(value_1);
					index3 = value_2.find(",");
					if (index3 > 0)
					{
						std::string value_3 = value_2.substr(index3 + 1, value_2.size());
						int index4 = -1;
						value_2 = value_2.substr(0, index3);
						content.push_back(value_2);
						index4 = value_3.find(",");
						if (index4 > 0)
						{
							std::string value_4 = value_3.substr(index4 + 1, value_3.size());
							value_3 = value_3.substr(0, index4);
							content.push_back(value_3);
							content.push_back(value_4);
						}
						else
						{
							content.push_back(value_3);
						}
					}
					else
					{
						content.push_back(value_2);
					}
				}
				else
				{
					content.push_back(new_line);
				}
			}
		}
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

bool FileSystem::createFile(std::string name, std::string texture, int density, float e_r, float width, float height, int m_a, int a_o, int r_a, float v, float l, float e_x, float e_y, float e_l, float e_h, std::vector<float> t_o, std::vector<float> o_c_r, std::vector<ASGE::Colour> colours, std::vector<float> c_c_r)
{
	std::fstream file;
	std::string file_name = "Resources\\TxtFiles\\FilePaths\\" + name + ".txt";
	std::string line;
	file.open(file_name);
	if (!file.is_open())
	{
		std::ofstream new_file(file_name);

		std::string buffer;
		buffer += "{";
		buffer += "\namount:" + std::to_string(density);
		buffer += "\nemission rate:" + std::to_string(e_r);
		buffer += "\ntexture:" + texture;
		buffer += "\ndimensions:" + std::to_string(width) + "," + std::to_string(height);
		buffer += "\nvelocity:" + std::to_string(v);
		buffer += "\nangle:" + std::to_string(m_a);
		buffer += "\nangle offset:" + std::to_string(a_o);
		buffer += "\nrandmise angle:" + std::to_string(r_a);
		buffer += "\nmax_life_time:" + std::to_string(l);
		buffer += "\nemitter pos:" + std::to_string(e_x) + "," + std::to_string(e_y);
		buffer += "\nemitter dim:" + std::to_string(e_l) + "," + std::to_string(e_h);
		buffer += "\nopacity over lifetime:" + std::to_string(t_o[0]) + "," + std::to_string(t_o[1]) + "," + std::to_string(t_o[2]);
		buffer += "\nopacity rate of change:" + std::to_string(o_c_r[0]) + "," + std::to_string(o_c_r[1]);
		buffer += "\ncolour rate of change:" + std::to_string(c_c_r[0]) + "," + std::to_string(c_c_r[1]) + "," + std::to_string(c_c_r[2]) + "," + std::to_string(c_c_r[3]);
		buffer += "\ncolour 1:" + std::to_string(colours[0].r) + "," + std::to_string(colours[0].g) + "," + std::to_string(colours[0].b);
		buffer += "\ncolour 2:" + std::to_string(colours[1].r) + "," + std::to_string(colours[1].g) + "," + std::to_string(colours[1].b);
		buffer += "\ncolour 3:" + std::to_string(colours[2].r) + "," + std::to_string(colours[2].g) + "," + std::to_string(colours[2].b);
		buffer += "\ncolour 4:" + std::to_string(colours[3].r) + "," + std::to_string(colours[3].g) + "," + std::to_string(colours[3].b);
		buffer += "\ncolour 5:" + std::to_string(colours[4].r) + "," + std::to_string(colours[4].g) + "," + std::to_string(colours[4].b);
		buffer += "\n}";

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
