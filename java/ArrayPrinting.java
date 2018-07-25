public class ArrayPrinting {
    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            System.err.println("Usage: ArrayPrinting <Array Length>");
            System.exit(0);
        }

        int numThreads = 4;
        int length = Integer.parseInt(args[0]);
        ArrayPrinter printer = new ArrayPrinter(length);

        Thread[] threads = new Thread[numThreads];
        for (int i = 0; i < numThreads; i++) {
            threads[i] = new Thread(printer);
            threads[i].start();
        }

        for(int i = 0; i < threads.length; i++) {
            threads[i].join();
        }
    }
}

class ArrayPrinter implements Runnable {
    private double[] array;
    private int nextId;

    public ArrayPrinter(int n) {
        this.array = new double[n];
        for (int i = 0; i < n; i++) {
            this.array[i] = Math.random();
        }

        this.nextId = 0;
    }

    public void run() {
        int myId = 0;
        synchronized (this) {
            myId = this.nextId;
            this.nextId++;
        }

        int chunkLength = array.length / 4;
        int start = myId * chunkLength;
        int end = start + chunkLength - 1;

        if (myId == 3) {
            end = array.length - 1;
        }

        for (int i = start; i <= end; i++) {
            System.out.printf("array[%d] = %.5f%n", i, array[i]);
        }
    }
}
