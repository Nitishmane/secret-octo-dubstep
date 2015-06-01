package com.cloudwick.java.clone;

public class CloneManager {

	public static void main(String[] args) throws CloneNotSupportedException {
		// TODO Auto-generated method stub

		UserClone userobj = new UserClone();
		userobj.name = "Nitish";
		System.out.println(userobj.name);
		
		UserClone userobj2 = (UserClone) userobj.clone();
				
		
		System.out.println(userobj2.name);
	}

}
