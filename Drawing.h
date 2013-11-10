#ifndef _DRAWING_H
#define _DRAWING_H

class Drawing {
    public:
        typedef unsigned char Byte;

        Drawing() : m_buffer(0) {
        }

        ~Drawing() {
            delete [] m_buffer;
        }

        void create(unsigned int blockSize);

        const char* getBuffer() {
            return (const char*) m_buffer;
        }

        unsigned int getBufferSize() {
            return m_bufferSize;
        }

    protected:
        void toSizeHeader(unsigned int size, Byte* sizeHeader)
        {
            sizeHeader[0] = (size & 0x000000FF);
            sizeHeader[1] = ((size >> 8 ) & 0x000000FF);
            sizeHeader[2] = ((size >> 16 ) & 0x000000FF);
            sizeHeader[3] = ((size >> 24 ) & 0x000000FF);
        }

        void drawBigBlocks();
        void drawRandom();

        void append(Byte* source, unsigned int size)
        {
            unsigned int i;
            for(i = 0; i < size; i++) {
                *m_bufferPosition = *source;
                m_bufferPosition++;
                source++;
            }
        }

        void appendPixel(Byte* source)
        {
            append(source, m_pixelSize);
        }

        void appendPixels(Byte* source, int columns)
        {
            int i;
            for (i = 0; i < columns; i++) {
                appendPixel(source);
            }
        }

        unsigned int m_blockSize;
        unsigned int m_pixelSize;
        unsigned int m_width;
        unsigned int m_height;
        unsigned int m_bufferSize;
        Byte* m_buffer;
        Byte* m_bufferPosition;
};

#endif
