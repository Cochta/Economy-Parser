#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "MyImage.h"

struct Reader {
	int ElementCount = 0;
	std::vector<std::vector<std::string>> readCSV(const std::string& fileName);

};
struct Loader {
	MyImage loadImage(const std::string& path, Vector2 size, Offset offset) {
		MyImage image;
		image.Setup(path.c_str(), size, offset);
		return image;
	}
};