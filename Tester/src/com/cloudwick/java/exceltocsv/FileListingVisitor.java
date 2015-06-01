package com.cloudwick.java.exceltocsv;
import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.List;
import org.apache.commons.io.FileUtils; 

public class FileListingVisitor {
 
		public static void main(String[] args) throws IOException {

			File dir = new File("/Users/nitishmane/Documents/workspace/temp1");
			String[] extensions = new String[] { "xlsx" };
			List<File> files = (List<File>) FileUtils.listFiles(dir, extensions, true);
			XlsxToCsv obj = new XlsxToCsv();
			File csvfile = new File("/Users/nitishmane/Documents/workspace/output.csv");
			
			for (File file : files) {
				//System.out.println("file: " + file.getCanonicalPath());
				obj.xlsx(file.getCanonicalFile(),csvfile);
			}
			
			

		}

}
 