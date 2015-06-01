package com.cloudwick.java.threads;

import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ExecuterManager {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		ExecutorService service = Executors.newFixedThreadPool(1);
		for (int i = 1; i < 501; i++) {
			CounterThread obj = new CounterThread(1000000000+i);
			service.execute(obj);
		}
		service.shutdown();
		do {
			
		} while (!service.isTerminated());
		System.out.println("All threads Done");
	}

}
