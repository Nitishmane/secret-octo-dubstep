package com.cloudwick.java.collections;

import java.util.Comparator;

public class UserComparator implements Comparator<UserCollection>{


	
	
	@Override
	/*public int compare(UserCollection o1, UserCollection o2) {
		// TODO Auto-generated method stub
		return o2.getSsn()-o1.getSsn();
	}*/
	
	public int compare(UserCollection o1, UserCollection o2) {
		// TODO Auto-generated method stub
		return o1.getName().compareTo(o2.getName());
	}

}
