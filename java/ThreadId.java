/*
 *  We were told that we can't get the Thread ID from
 *  a Java Thread.
 */

public class ThreadId extends Thread {
    public void run() {
        long threadId = Thread.currentThread().getId();
        System.out.println("Thread #" + threadId + " is doing this task");
    }

    public static void main(String[] args) {
        (new ThreadId()).start();
        (new ThreadId()).start();
        (new ThreadId()).start();
        (new ThreadId()).start();
        (new ThreadId()).start();
    }
}
