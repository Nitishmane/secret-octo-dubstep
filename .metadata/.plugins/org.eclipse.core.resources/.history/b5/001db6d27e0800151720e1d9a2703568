//package Hadoop1.Hadoop1;
package com.mysql.jdbc;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
//import java.sql.Connection;
//import java.sql.DriverManager;
//import java.sql.ResultSet;
//import java.sql.ResultSet;
//import java.sql.SQLException;
//import java.util.Properties;
//
//import javax.print.DocFlavor.URL;
//
//import org.omg.CORBA.portable.InputStream;
//
//import com.mysql.jdbc.Statement;
//
//import com.mysql.jdbc.PreparedStatement;
//import com.mysql.jdbc.Statement;

public class App extends Object
{
	

    private static final String TheClassName = null;

	public static void main( String[] args ) 
    { 
		/*
		System.out.println("-------- MySQL JDBC Connection Testing ------------");
		 
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			System.out.println("Where is your MySQL JDBC Driver?");
			e.printStackTrace();
			return;
		}
	 
		System.out.println("MySQL JDBC Driver Registered!");
		Connection connection = null;
	 
		try {
			connection = DriverManager
			.getConnection("jdbc:mysql://172.17.1.122:3306/Hadoo1","root", "hadoop123");
	 
		} catch (SQLException e) {
			System.out.println("Connection Failed! Check output console");
			e.printStackTrace();
			return;
		}
	 
		if (connection != null) {
			System.out.println("You made it, take control your database now!");
		} else {
			System.out.println("Failed to make connection!");
		}
   */
		
		String fileName = "/Users/nitishmane/Documents/slackspace-mavenprofiles/target/classes/db.properties";

        // This will reference one line at a time
        String line = null;

        try {
            // FileReader reads text files in the default encoding.
            FileReader fileReader = 
                new FileReader(fileName);

            // Always wrap FileReader in BufferedReader.
            BufferedReader bufferedReader = 
                new BufferedReader(fileReader);

            while((line = bufferedReader.readLine()) != null) {
                System.out.println(line);
            }    

            // Always close files.
            bufferedReader.close();            
        }
        catch(FileNotFoundException ex) {
            System.out.println(
                "Unable to open file '" + 
                fileName + "'");                
        }
        catch(IOException ex) {
            System.out.println(
                "Error reading file '" 
                + fileName + "'");                   
            // Or we could just do this: 
            // ex.printStackTrace();
        }
    	
    }
    
    
}

