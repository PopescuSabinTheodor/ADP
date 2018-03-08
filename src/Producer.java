import java.util.Queue;

public class Producer extends Thread
{
    @Override
    public void run()
    {
        while(true)
        produce();
    }

    public static void produce()
    {
        try
        {
            Thread.sleep(2000);
        } catch (InterruptedException e)
        {
            e.printStackTrace();
        }
        MyQueue.getInstance().receiveItem();
    }
}
