

/*Write a Java program to find the smallest integer in an array. 
Your program should evenly partition the work among four threads
Note that the master thread should wait for the other thread to find the smallest integer in their partition, 
and then choose the smallest from their results
Your program should generate the initial array by filling it with random numbers
The size of the array should be given on the command line*/



public class FindSmallest{
	public static void main(String[] args){
		int numThreads = 4;
		int length = 0;
		int[] mainArray;
		int[] subresults = new int[4];
		
		if(args.length < 1){
			System.err.println("usage: Sortarray <length of array>");
			System.exit(0);
		}
		
		//Convert cmd line to integer if possible
		try{
			length = Integer.parseInt(args[0]);
		} 
		catch (Exception ex){
			System.err.println("Cannot Convert arguement on command line to integer");
			System.exit(1);
		}
		
		//generate main array
		//if(length < 0){
		mainArray = new int[length]; 
		for(int i=0; i<length; i++){
			mainArray[i]=length-i;
		}
		/*}else{
			System.err.println("Invalid array length provided");
			System.exit(2);
		}*/
		
		//create thread array 
		Thread[] threads = new Thread[numThreads];
		
		//determine number of elements to give to each thread. 
		int sublength = length/4;
		int remainder = length%4;
		
		//generate spawn threads and pass arrays
		for(int i=0; i<numThreads-1; i++)
		{
			threads[i] = new Thread(new sorter(i, mainArray, subresults, sublength));
			threads[i].start();
		}
		
		subresults[3] = mainArray[(numThreads-1)*sublength];
		//sort remainder
		for(int j=0; j<sublength+remainder; j++)
		{
		   if(subresults[3] > mainArray[(numThreads-1)*sublength+j]){
			   subresults[3] = mainArray[(numThreads-1)*sublength+j];
		   }
		}
		
		//Wait for other threads to finish. 
		for(int i=0; i < numThreads-1; i++)
		{
			try{
			    threads[i].join();
			} 
			catch (Exception ex){
				System.err.println("Error while waiting for thread "+i);
			}
		}
		
		System.out.println(subresults[0]+" "+subresults[1]+" "+subresults[2]+" "+subresults[3]);
		
		
		
		
	
	}
}
	
class sorter implements Runnable{
	public int id;
	private int[] array;
	private int[] output;
	private int min;
	private int length;
	//constructor
	sorter(int id_in, int[] inArray, int[] outArray, int lengthIn)
	{
		id=id_in;
		this.array  = inArray;
		this.output = outArray;
		this.length = lengthIn;
	}		
	
	public void run(){
		min = array[id*length];
		for(int i=0; i<length; i++)
		{
		   if(min > array[id*length+i])
		   {
			   min = array[id*length+i];
		   }	
		}
		System.out.println("Thread "+id+" lowest is "+min);
				
		output[id]=min; 
	}
	
}