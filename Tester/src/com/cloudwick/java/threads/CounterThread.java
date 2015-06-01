package com.cloudwick.java.threads;

public class CounterThread extends Thread {

	private int counter;
	public CounterThread(int num)
	{
		this.counter = num;
		
	}
	public void run()
	{
		int sum = (counter*(counter+1))/2;
		System.out.println(Thread.currentThread()+ "value is : " + sum); 
	}
}
	