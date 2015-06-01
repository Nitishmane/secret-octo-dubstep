package com.cloudwick.java.threads;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;


public class CallableManager  {

	public static void main(String[] args) throws InterruptedException, ExecutionException {
		// TODO Auto-generated method stub

		ExecutorService service = Executors.newFixedThreadPool(10);
		List<Future> dataList = new ArrayList<Future>();
		for (int i = 1; i < 501; i++) {
			CounterCallableThread obj = new CounterCallableThread(1000000000+i);
			Future<Long> val = service.submit(obj);
			dataList.add(val);
		}
		for (Future<Long> data: dataList) {
			System.out.println(data.get());
		}
		service.shutdown();
		System.out.println("All threads Done");
	}
}
