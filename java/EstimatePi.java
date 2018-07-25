public class EstimatePi {
    public static void main(String[] args) throws Exception {
        if (args.length != 2) {
            System.err.println("Usage: Hello <Num Threads> <Num Loops Per Thread>");
            System.exit(0);
        }

        int numThreads = Integer.parseInt(args[0]);
        long n = Long.parseLong(args[1]);

        MonteCarloPi[] montes = new MonteCarloPi[numThreads];
        Thread[] threads = new Thread[numThreads];
        for (int i = 0; i < numThreads; i++) {
            montes[i] = new MonteCarloPi(n);
            threads[i] = new Thread(montes[i]);
            threads[i].start();
        }

        long totalN = 0;
        long totalInside = 0;
        for(int i = 0; i < threads.length; i++) {
            threads[i].join();

            totalN += montes[i].getN();
            totalInside += montes[i].getInside();
        }

        double pi = (4.0 * totalInside) / totalN;
        System.out.println("Estimated Pi: " + pi);
    }
}

class MonteCarloPi implements Runnable {
    private long n;
    private long inside;

    public MonteCarloPi(long n) {
        this.n = n; 
        this.inside = 0;
    }

    public long getN() {
        return this.n;
    }

    public long getInside() {
        return this.inside;
    }

    public void run() {
        for (long i = 0; i < this.n; i++) {
            double x = Math.random() * 2 - 1;    
            double y = Math.random() * 2 - 1;    

            if (Math.sqrt(x*x + y*y) <= 1) {
                this.inside++;
            }
        }
    }
}
