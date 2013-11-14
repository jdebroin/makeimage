#include "Drawing.h"

#include <stdlib.h>

// header
// 42 4d 7a 53 07 00 00 00 00 00 7a 00 00 00 6c 00
// 00 00

// width
//       90 01 00 00

// height
//                   90 01 00 00

// header2
//                               01 00 18 00 00 00
// 00 00 00 53 07 00 13 0b 00 00 13 0b 00 00 00 00
// 00 00 00 00 00 00 42 47 52 73 00 00 00 00 00 00
// 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
// 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
// 00 00 00 00 00 00 00 00 00 00 02 00 00 00 00 00
// 00 00 00 00 00 00 00 00 00 00

// data

// B-G-R red
Drawing::Byte red[] = {
    0x00, 0x00, 0xFF
};
// B-G-R white
Drawing::Byte white[] = {
    0xFF, 0xFF, 0xFF
};
// B-G-R black
Drawing::Byte black[] = {
    0x00, 0x00, 0x00
};
// B-G-R blue
Drawing::Byte blue[] = {
    0xFF, 0x00, 0x00
};
// B-G-R green
Drawing::Byte green[] = {
    0x00, 0xFF, 0x00
};

Drawing::Byte* colors[] = {
    red, white, black, blue, green
};

int colorsSize = sizeof(colors) / sizeof(Drawing::Byte*);

void Drawing::create(unsigned int blockSize) {
    m_blockSize = blockSize;
    m_bufferSize = 0;
    m_buffer = 0;
    m_bufferPosition = 0;
    m_pixelSize = 3 * sizeof(Byte);

    m_width = 4 * m_blockSize;
    m_height = 4 * m_blockSize;

    Byte header[] = {
        0x42, 0x4D, 0x7A, 0x53, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x6C, 0x00,
        0x00, 0x00
    };

    Byte header2[] = {
        0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x53, 0x07, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x47, 0x52, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    unsigned int headerSize = sizeof(header);

    Byte widthHeader[4];
    toSizeHeader(m_width, widthHeader);
    // cout << (int) widthHeader[0] << endl;
    // cout << (int) widthHeader[1] << endl;
    unsigned int widthSize = sizeof(widthHeader);

    Byte heightHeader[4];
    toSizeHeader(m_height, heightHeader);
    // cout << (int) heightHeader[0] << endl;
    // cout << (int) heightHeader[1] << endl;
    unsigned int heightSize = sizeof(heightHeader);

    unsigned int header2Size = sizeof(header2);

    unsigned int dataSize = headerSize + widthSize + heightSize + header2Size + m_width * m_height * m_pixelSize;

    unsigned int paddingSize = 0;

    m_bufferSize = dataSize + paddingSize;
    if (m_buffer) {
        delete [] m_buffer;
    }
    m_buffer = new Byte[m_bufferSize];
    m_bufferPosition = m_buffer;

    append(header, headerSize);
    append(widthHeader, widthSize);
    append(heightHeader, heightSize);
    append(header2, header2Size);

    Byte* dataStart = m_bufferPosition;

    // drawBigBlocks();
    drawRandom();

    // cout << "data size: " << m_bufferPosition - dataStart << endl;
    // cout << "m_width * m_height size: " << m_width * m_height * 3 << endl;
    Byte padding[] = {
        0x00, 0x00, 0x00, 0x00
    };
    if (paddingSize) {
        append(padding, paddingSize);
        // cout << "data + padding size: " << m_bufferPosition - dataStart << endl;
    }
    // cout << "headers + data size: " << m_bufferPosition - m_buffer << endl;
    // cout << "m_buffer size: " << m_bufferSize << endl;
}


void Drawing::drawBigBlocks() {
    // Bottom row comes firts
    for (int i = 0; i < m_blockSize; i++) {
        appendPixels(red, m_blockSize);
        appendPixels(white, m_blockSize);
        appendPixels(red, m_blockSize);
        appendPixels(white, m_blockSize);
    }
    for (int i = 0; i < m_blockSize; i++) {
        appendPixels(blue, m_blockSize);
        appendPixels(green, m_blockSize);
        appendPixels(blue, m_blockSize);
        appendPixels(green, m_blockSize);
    }
    for (int i = 0; i < m_blockSize; i++) {
        appendPixels(black, m_blockSize);
        appendPixels(red, m_blockSize);
        appendPixels(black, m_blockSize);
        appendPixels(red, m_blockSize);
    }
    for (int i = 0; i < m_blockSize; i++) {
        appendPixels(white, m_blockSize);
        appendPixels(blue, m_blockSize);
        appendPixels(white, m_blockSize);
        appendPixels(blue, m_blockSize);
    }
}

void Drawing::drawRandom() {
    for (int i = 0; i < m_width * m_height; i++) {
        int r = rand() % colorsSize;
        Byte* color = colors[r];
        appendPixel(color);
    } 
}

