package org.duldeb.makeimage;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class MakeImage {

	public static void main(String[] args) {
		Drawing d = new Drawing();

		String fName = "out.bmp";

		int blockSize = 100;
		//for (int i = 0; i < 1000; i++) {
			d.create(blockSize);
		//}

		FileOutputStream f;
		try {
			f = new FileOutputStream(fName);
			f.write(d.getBuffer());
			f.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
    
        System.out.println("Done!");
	}
}
