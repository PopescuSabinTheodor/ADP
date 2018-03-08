

public class MyQueue
{
    private static MyQueue instance = new MyQueue();
    private static final int SIZE = 10;
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

    public synchronized void receiveItem()
    {
        if(occupied < SIZE)
        {
            occupied++;
            System.out.println("Storing item...   Queue size is: " + occupied);
            notify();
        }else
        {
            try
            {
                wait();
            } catch (InterruptedException e)
            {
                e.printStackTrace();
            }
            occupied++;
            System.out.println("Storing item...   Queue size is: " + occupied);
            notify();
        }
    }

    public synchronized void presentItem()
    {   if(occupied > 0)
        {
            occupied--;
            System.out.println("Giving item...   Queue size is: " + occupied);
            notify();
        }else
        {
            try
            {
                wait();
            } catch (InterruptedException e)
            {
                e.printStackTrace();
            }
            occupied--;
            System.out.println("Giving item...   Queue size is: " + occupied);
            notify();
        }

    }



}
