import java.lang.*;
import java.util.Arrays;

public class VectorSum{
	public static void main(String[] args){
			int num_threads = 0;
			int length = 0;
			double[] a;
			double[] b;
					
			if(args.length < 1){
				System.err.println("usage: Sortarray <length of array>");
				System.exit(0);
			}
			
			//Convert cmd line to integer, if possible
			try{
				length = Integer.parseInt(args[0]);
				num_threads = Integer.parseInt(args[1]);
			} 
			catch (Exception ex){
				System.err.println("Cannot Convert argument on command line to integer");
				System.exit(1);
			}
			
			
			
			//populate the arrays
			a = new double[length];
			b = new double[length];
			
			for(int i=0; i<length; i++){
				a[i]= i;
				b[i]= i;
			}
			
			//generate threads
			Runnable add1 = new adder(length, a, b, num_threads);
			Thread[] threads = new Thread[num_threads];
			for(int i=0; i<num_threads; i++){
				threads[i]= new Thread(add1);
				threads[i].start();
			}
			
			//Wait for other threads to finish. 
			for(int i=0; i < num_threads-1; i++)
			{
				try{
					threads[i].join();
				}	 
				catch (Exception ex){
				System.err.println("Error while waiting for thread "+i);
				}
			}
			
			//print
			((adder)add1).print_c();
			
	}
}


class adder implements Runnable{
	public int thread_id = 0;
    private int length; 
	private int threads;
	private double[] a;
	private double[] b;
	private double[] c;
	
	public  int[] c_vec;
	
	
	adder(int length, double[] a, double[] b, int threads)
	{
		this.length = length;
		this.a = a;
		this.b = b;
		this.c = new double[length];
		this.threads=threads;
	}		
	
	
	public void run(){
		int id = 0;
		int myStart;
		int myEnd;
		synchronized(this)
		{
			id = thread_id;
			thread_id++;
		}
		
		myStart = id*length/threads;
		if(id != threads-1){
			myEnd = myStart+length/threads;
		}else{myEnd = length;}
		
		for(int i=myStart; i<myEnd; i++)
		{
			c[i]=a[i]+b[i];
		}
	}
	
	
	public void print_c(){
		System.out.println(Arrays.toString(c));
	}
	
}