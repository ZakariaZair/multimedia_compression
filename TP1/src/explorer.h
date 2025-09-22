#pragma once
#include <map>
#include <vector>

class Explorer {
    public:
    Explorer();
    int explore(const char* filename);
    int draw();
    int print();

    private:
        const char* currentFilename_;
        std::map<char, int> frequency_;
        int fCount_;

};
