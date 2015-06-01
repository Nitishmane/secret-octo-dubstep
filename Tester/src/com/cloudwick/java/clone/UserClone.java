package com.cloudwick.java.clone;
public class UserClone implements Cloneable{
	
	public String name;
	public Object clone() throws CloneNotSupportedException 
	{
		
		return super.clone();
	}
}
