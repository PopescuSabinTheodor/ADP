public class Consumer extends Thread
{
    @Override
    public void run()
    {
        while(true)
        consume();
    }

    public static void consume()
    {

        MyQueue.getInstance().presentItem();
        try
        {
            Thread.sleep(5000);
        } catch (InterruptedException e)
        {
            e.printStackTrace();
        }
    }
}
