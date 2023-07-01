#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

const int QUEUE_LENGTH = 16;
const int DMA_CHUNK_LENGTH = 16;

bool recalc(int width, int height, std::string bpp) {
    int dawidth = 0;
    if (bpp == "8") {
        dawidth = width / 2;
    } else if (bpp == "4") {
        dawidth = width / 4;
    } else {
        std::cout << "invalid bpp " + bpp + ".txt, aborting" << std::endl;
        exit(EXIT_FAILURE);
    }

    int length = dawidth * height;
    length = length / 2;
    if ((length >= DMA_CHUNK_LENGTH) && (length % DMA_CHUNK_LENGTH)) {
        return false;
    } else {
        return true;
    }
}

void writetex(std::string path, int* tex, int realwidth, int realheight) {
    std::cout << "fixed image " + path << std::endl;
    // Write the tex to a file or perform further processing if needed
}

int main() {
    std::vector<std::string> path;
    for (const auto& entry : std::filesystem::directory_iterator("iso/characters")) {
        if (entry.path().extension() == ".png") {
            path.push_back(entry.path().string());
        }
    }

    for (const auto& curpath : path) {
        // Load the tex image
        std::ifstream file(curpath + ".txt");
        std::string bpp;
        std::getline(file, bpp);
        bpp = bpp.back();

        // Get the realwidth and realheight of the tex image
        int realwidth = 0;
        int realheight = 0;

        // Check if the image needs fixing
        if (recalc(realwidth, realheight, bpp) == true) {
            std::cout << "no need to fix image " + curpath << std::endl;
            continue;
        }
        std::cout << "fixing image " + curpath << std::endl;

        while (realheight % 2 != 0 && realheight < 256) {
            realheight = realheight + 1;
        }

        if (realheight % 2 != 0) {
            std::cout << "failed to fix image " + curpath + " height isn't a multiple of 2" << std::endl;
            exit(EXIT_FAILURE);
        }

        // Try messing with the width
        for (int i = 0; i < 256; i++) {
            if (realwidth > 255) {
                break;
            }
            if (recalc(realwidth + i, realheight, bpp) == true) {
                realwidth = realwidth + i;
                break;
            }
        }

        // Yay fix worked
        if (recalc(realwidth, realheight, bpp) == true) {
            // Perform any necessary processing or write the fixed image to a file
            writetex(curpath, nullptr, realwidth, realheight);
            continue;
        }

        // Try messing with the height if fix didn't work
        for (int i = 0; i < 256; i++) {
            if (realheight > 255) {
                break;
            }
            if (recalc(realwidth, realheight + i, bpp) == true) {
                realheight = realheight + i;
                break;
            }
        }

        // Yay fix worked
        if (recalc(realwidth, realheight, bpp) == true) {
            // Perform any necessary processing or write the fixed image to a file
            writetex(curpath, nullptr, realwidth, realheight);
            continue;
        }

        std::cout << "failed to fix image " + curpath << std::endl;
    }

    return 0;
}
