public class Hello {
    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.err.println("Usage: Hello <Num Threads>");
            System.exit(0);
        }

        int numThreads = Integer.parseInt(args[0]);

        for (int i = 0; i < numThreads; i++) {
            (new Thread(new HelloWorker())).start();
        }
    }
}

class HelloWorker implements Runnable {
    public void run() {
        System.out.println("Hello world from thread "+Thread.currentThread().getId());
    }
}
