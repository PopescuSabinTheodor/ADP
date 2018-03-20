import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MyQueue
{
    private static MyQueue instance = new MyQueue();
    private static final int SIZE = 10;
    private Lock mutex = new ReentrantLock();
    private Condition notFull = mutex.newCondition();
    private Condition notEmpty = mutex.newCondition();




    private static int occupied;



    public MyQueue()
    {
        occupied = 0;
    }


    public static MyQueue getInstance()
    {
        if (instance == null)
        {
            instance = new MyQueue();
        }
        return instance;
    }

    public void receiveItem()
    {
        mutex.lock();
        try {
            while (occupied == SIZE) {
                try {
                    notFull.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            occupied++;
            notEmpty.signalAll();
            System.out.println("Storing item...   Queue size is: " + occupied);
        }finally {
            mutex.unlock();
        }


    }

    public void presentItem()
    {
        mutex.lock();
        try {
            while (occupied == 0) {
                try {
                    notEmpty.await();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            occupied--;
            notFull.signalAll();
            System.out.println("Giving item...   Queue size is: " + occupied);
        }finally {
            mutex.unlock();
        }
    }

}
