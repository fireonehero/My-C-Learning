#ifndef BIT_STREAM_HPP
#define BIT_STREAM_HPP

#include <fstream>

class BitWriter {
    public:
        BitWriter(std::ofstream* outputStream);
        void writeBit(char bit);
        void flush();

    private:
        std::ofstream* outputStream;
        unsigned char buffer;
        int bitCount;

};

class BitReader {
    public:
        BitReader(std::ifstream* inputStream);
        int readBit();
    private:
        std::ifstream* inputStream;
        unsigned char buffer;
        int bitCount;
};

#endif