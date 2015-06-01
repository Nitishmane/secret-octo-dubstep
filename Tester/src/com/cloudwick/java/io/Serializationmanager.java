package com.cloudwick.java.io;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class Serializationmanager {

	public static void main(String[] args) throws FileExistException {
		// TODO Auto-generated method stub

	serializedData();
	try {
		deserializedData();
	} catch (ClassNotFoundException | IOException e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
	
	
	
	}
	private static void serializedData() throws FileExistException
	{
		System.out.println(Thread.currentThread());
		FileOutputStream fo = null;
		ObjectOutputStream out = null;
		try {
			
			File f = new File("Serialize.txt");
			if(f.exists())
			{
				
				throw new FileExistException("Possible change filename");
			}
			fo = new FileOutputStream("Serialize.txt");
			out = new ObjectOutputStream(fo);
			User obj = new User();
			obj.setName("Fremont");
			obj.setAge(24);
			out.writeObject(obj);
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		finally{
			if (fo != null) {
				try {
					fo.flush();
					fo.close();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}			
			
		}
		
	}

	private static void deserializedData() throws IOException, ClassNotFoundException
	{
		FileInputStream fo = new FileInputStream("Serialize.txt");
		ObjectInputStream in = new ObjectInputStream(fo);
		User obj  = (User)in.readObject();
		System.out.println("Name: "+obj.getName());
		System.out.println("Age: "+obj.getAge());
	}
}
