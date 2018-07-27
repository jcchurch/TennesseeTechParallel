/*
 * Classic Dining Philosophers using the Butler solution.
 * Written in vanilla Java Threads.
 */

public class DiningPhilosopher {
    public static void main(String[] args) {

        String[] names = {"Mercury", "Venus", "Earth", "Mars", "Jupiter"};
        int n = names.length;

        Butler butler = new Butler(n);
        Fork[] forks = new Fork[n];
        Philosopher[] philosophers = new Philosopher[n];

        for (int i = 0; i < names.length; i++) {
            forks[i] = new Fork();
        }

        for (int i = 0; i < names.length; i++) {
            philosophers[i] = new Philosopher(names[i], forks[i], forks[(i+1)%n], butler);
            new Thread(philosophers[i]).start();
        }

        try{ Thread.sleep(10000); } catch (Exception e) { }

        for (Philosopher philosopher : philosophers) {
            philosopher.stop();
        }

        System.out.println("End");
    }
}

class Butler {
    private int numSeated;
    private int numSeats;

    public Butler(int numSeats) {
        this.numSeated = 0;
        this.numSeats = numSeats;
    }

    synchronized public void arise() {
        this.numSeated--;
        this.notifyAll();
    }

    synchronized public void sitDown() {
        while (this.numSeated + 1 == this.numSeats) {
            try{ this.wait(); } catch (Exception e) { }
        }

        this.numSeated++;
    }
}

class Fork {
    private boolean available;

    public Fork() {
        this.available = true;
    }

    synchronized public void pickUp() {
        while (this.available == false) {
            try{ this.wait(); } catch (Exception e) { }
        }

        this.available = false;
        try{ Thread.sleep(50); } catch (Exception e) { }
    }

    synchronized public void putDown() {
        this.available = true;
        this.notifyAll();
    }
    
    public boolean isAvailable() {
        return this.available;
    }
}

class Philosopher implements Runnable {
    private String name;
    private Fork first;
    private Fork second;
    private Butler butler;
    private boolean keepWorking;

    public Philosopher(String name, Fork first, Fork second, Butler butler) {
        this.keepWorking = true;
        this.name = name;
        this.first = first;
        this.second = second;
        this.butler = butler;
    }

    public void run() {
        while (keepWorking) {
            butler.sitDown();
            first.pickUp();
            System.out.println(name+" lifts the first fork.");
            second.pickUp();
            System.out.println(name+" lifts the second fork.");
            try{ Thread.sleep(500); } catch (Exception e) { }
            System.out.println(name+" is eating.");
            second.putDown();
            System.out.println(name+" puts down the second fork.");
            first.putDown();
            System.out.println(name+" puts down the first fork.");
            butler.arise();
            try{ Thread.sleep(500); } catch (Exception e) { }
            System.out.println(name+" is thinking.");
        }
    }

    public void stop() {
        this.keepWorking = false;
    }
}
