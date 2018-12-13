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

	bool createFile(std::string file_name, std::string texture, int density, float e_r, float width, float height, int m_a, int a_o, int r_a, float v, float l, float e_x, float e_y, float e_l, float e_h, std::vector<float> t_o, std::vector<float> o_c_r, std::vector<ASGE::Colour> colours, std::vector<float> c_c_r);

	void editFile(std::vector<std::string> file_names);

	std::string retrieveContent(int content_element);

	int retrieveContentSize();

	std::string retrieveContent(int content_element, int value);

	bool checkFile(std::string file_name);

private:

	std::vector<std::string> content;
};
