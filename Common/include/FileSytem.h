#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "MyImage.h"

struct SpriteDefinition {
    std::string filename;
    int x, y, width, height;
};

struct Reader {
	int ElementCount = 0;
	std::vector<std::vector<std::string>> readEconomyCSV(const std::string& fileName);
	std::vector<SpriteDefinition> ReadAtlasMetaData(const std::string& csvPath);

};
struct Loader {
	MyImage loadImage(const std::string& path, Vector2 size, Offset offset) {
		MyImage image;
		image.SetupFromFile(path.c_str(), size, offset);
		return image;
	}
};