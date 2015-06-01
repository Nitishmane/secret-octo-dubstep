package Assignment1.asgn;

import java.sql.DriverManager;
import java.sql.SQLException;

import com.mysql.jdbc.Connection;

/**
 * Hello world!
 *
 */
public class App 
{
    public static void main( String[] args )
    {
        System.out.println( "Hello World!" );
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
    		connection = (Connection) DriverManager.getConnection("jdbc:mysql://localhost:3306/mkyongcom","root", "password");
     
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
      }
    
}