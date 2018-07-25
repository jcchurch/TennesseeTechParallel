/*
 * Row-by-Row Time:       0.238211045 seconds
 * Column-by-Column Time: 23.805722613 seconds
 *
 * Compile: javac CacheAwareness
 * Run:     java -Xmx3G CacheAwareness
 */

public class CacheAwareness {
    public static void main(String[] args) {
        final int SIZE = 20000;
        int[] array = new int[SIZE*SIZE];
        
        long start = System.nanoTime(); //get the current time
        
        for(int j = 0; j < SIZE; j++)
            for(int i = 0; i < SIZE; i++)
                array[i*SIZE+j]=0;
            
        long finish = System.nanoTime();

        System.out.println("Time: "+(finish-start)/1e9);
    }
}
