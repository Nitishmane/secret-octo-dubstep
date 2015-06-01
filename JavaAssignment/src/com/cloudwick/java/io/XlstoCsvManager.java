package com.cloudwick.java.io;

import java.io.File;
public class XlstoCsvManager {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		File inputFile = new File("/Users/nitishmane/Documents/workspace/test.xlsx");
        File outputFile= new File("/Users/nitishmane/Documents/workspace/output.csv");
        XlsxtoCsv obj = new XlsxtoCsv();
        obj.converter(inputFile, outputFile);
	}

}
