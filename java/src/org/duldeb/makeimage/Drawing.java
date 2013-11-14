package org.duldeb.makeimage;

import java.util.Random;


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


public class Drawing {
	// B-G-R red
	byte red[] = {
			0x00, 0x00, (byte) 0xFF
	};
	// B-G-R white
	byte white[] = {
			(byte) 0xFF, (byte) 0xFF, (byte) 0xFF
	};
	// B-G-R black
	byte black[] = {
			0x00, 0x00, 0x00
	};
	// B-G-R blue
	byte blue[] = {
			(byte) 0xFF, 0x00, 0x00
	};
	// B-G-R green
	byte green[] = {
			0x00, (byte) 0xFF, 0x00
	};

	byte colors[][] = {
			red, white, black, blue, green
	};

	int colorsSize = colors.length;

	private byte buffer[];
	private int bufferSize;
	private int bufferPosition;
	private int pixelSize;
	private int height;
	private int width;
	private int blockSize;

	private static Random random = new Random();

	public Drawing() {
	}

	public void create(int blockSize) {
		this.blockSize = blockSize;
		bufferSize = 0;
		buffer = null;
		bufferPosition = 0;
		pixelSize = 3;

		width = 4 * blockSize;
		height = 4 * blockSize;

		byte header[] = {
				0x42, 0x4D, 0x7A, 0x53, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7A, 0x00, 0x00, 0x00, 0x6C, 0x00,
				0x00, 0x00
		};

		byte header2[] = {
				0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x53, 0x07, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x47, 0x52, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
		};

		int headerSize = header.length;

		byte widthHeader[] = toSizeHeader(width);
		// cout << (int) widthHeader[0] << endl;
		// cout << (int) widthHeader[1] << endl;
		int widthSize = widthHeader.length;

		byte heightHeader[] = toSizeHeader(height);
		// cout << (int) heightHeader[0] << endl;
		// cout << (int) heightHeader[1] << endl;
		int heightSize = heightHeader.length;

		int header2Size = header2.length;

		int dataSize = headerSize + widthSize + heightSize + header2Size + width * height * pixelSize;

		int paddingSize = 0;

		bufferSize = dataSize + paddingSize;

		buffer = new byte[bufferSize];
		bufferPosition = 0;

		append(header, headerSize);
		append(widthHeader, widthSize);
		append(heightHeader, heightSize);
		append(header2, header2Size);

		// int dataStart = bufferPosition;

		// drawBigBlocks();
		drawRandom();

		// cout << "data size: " << bufferPosition - dataStart << endl;
		// cout << "width * height size: " << width * height * 3 << endl;
		byte padding[] = {
				0x00, 0x00, 0x00, 0x00
		};
		if (paddingSize > 0) {
			append(padding, paddingSize);
			// cout << "data + padding size: " << bufferPosition - dataStart << endl;
		}
		// cout << "headers + data size: " << bufferPosition - buffer << endl;
		// cout << "buffer size: " << bufferSize << endl;
	}

	public byte[] getBuffer() {
		return buffer;
	}

	public int getBufferSize() {
		return bufferSize;
	}

	private byte[] toSizeHeader(int size) {
		byte[] sizeHeader = new byte[4];
		sizeHeader[0] = (byte) (size & 0x000000FF);
		sizeHeader[1] = (byte) ((size >> 8 ) & 0x000000FF);
		sizeHeader[2] = (byte) ((size >> 16 ) & 0x000000FF);
		sizeHeader[3] = (byte) ((size >> 24 ) & 0x000000FF);
		return sizeHeader;
	}

	@SuppressWarnings("unused")
	private void drawBigBlocks() {
		// Bottom row comes first
		for (int i = 0; i < blockSize; i++) {
			appendPixels(red, blockSize);
			appendPixels(white, blockSize);
			appendPixels(red, blockSize);
			appendPixels(white, blockSize);
		}
		for (int i = 0; i < blockSize; i++) {
			appendPixels(blue, blockSize);
			appendPixels(green, blockSize);
			appendPixels(blue, blockSize);
			appendPixels(green, blockSize);
		}
		for (int i = 0; i < blockSize; i++) {
			appendPixels(black, blockSize);
			appendPixels(red, blockSize);
			appendPixels(black, blockSize);
			appendPixels(red, blockSize);
		}
		for (int i = 0; i < blockSize; i++) {
			appendPixels(white, blockSize);
			appendPixels(blue, blockSize);
			appendPixels(white, blockSize);
			appendPixels(blue, blockSize);
		}
	}

	private void drawRandom() {
		for (int i = 0; i < width * height; i++) {
			int r = random.nextInt(colorsSize);
			byte color[] = colors[r];
			appendPixel(color);
		}
	}

	private void append(byte[] source, int size) {
		int i;
		for(i = 0; i < size; i++) {
			buffer[bufferPosition] = source[i];
			bufferPosition++;
		}
	}

	private void appendPixel(byte[] source)	{
		append(source, pixelSize);
	}

	private void appendPixels(byte[] source, int columns)
	{
		int i;
		for (i = 0; i < columns; i++) {
			appendPixel(source);
		}
	}

}
