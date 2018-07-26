public class EstimatePiOMP {
    public static void main(String[] args) throws Exception {
        if (args.length != 1) {
            System.err.println("Usage: Hello <Num Loops Per Thread>");
            System.exit(0);
        }

        long n = Long.parseLong(args[0]);

        long[] timesRun = new long[10];
        long[] insideEach = new long[10];

        // omp parallel threadNum(4)
        for (long i = 0; i < n; i++) {
            double x = Math.random() * 2 - 1;    
            double y = Math.random() * 2 - 1;    

            if (Math.sqrt(x*x + y*y) <= 1) {
                 insideEach[OMP4J_THREAD_NUM]++;
            }
            timesRun[OMP4J_THREAD_NUM] = n;
        }

        long totalN = 0;
        long totalInside = 0;
        for(int i = 0; i < timesRun.length; i++) {
            totalN += timesRun[i];
            totalInside += insideEach[i];
        }

        double pi = (4.0 * totalInside) / totalN;
        System.out.println("Estimated Pi: " + pi);
    }
}

