import java.util.concurrent.Semaphore;

public class MyQueue
{
    private static MyQueue instance = new MyQueue();
    private static final int SIZE = 10;
    private Semaphore notFull = new Semaphore(SIZE);
    private Semaphore notEmpty = new Semaphore(0);


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
        try {
            notFull.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        occupied++;
        System.out.println("Storing item...   Queue size is: " + occupied);
        notEmpty.release();

    }

    public void presentItem()
    {
        try {
            notEmpty.acquire();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        occupied--;
        System.out.println("Giving item...   Queue size is: " + occupied);
        notFull.release();

    }

}
