package com.cloudwick.java.io;

import java.nio.file.FileAlreadyExistsException;

public class FileExistException extends Exception {
		 public FileExistException(String msg) {
			super(msg);
		}
}
