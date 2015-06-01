package com.cloudwick.java.threads;

import java.util.ArrayList;
import java.util.List;


public class ThreadManager {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		List<Thread> threadList = new ArrayList<Thread>(); 
		for (int i = 0; i < 501; i++) {
			
			CounterThread obj = new CounterThread(1000000+i);
			obj.setName("Cloudwick "+i);
			if (i<50 && i<10) {
				obj.setPriority(Thread.MAX_PRIORITY);
			}
			obj.start();
			threadList.add(obj);
			
		}
		int running = 0; 
		do {
			//running=0;
			for (Thread thread:threadList) {
				if(thread.isAlive())
					running++;
				else 
					running--;
			}
			
		} while (running>=0);
		System.out.println("All threads Done");

	}

}
