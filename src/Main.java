public class Main {

    public static void main(String[] args)
    {
        Producer p = new Producer();
        Consumer c = new Consumer();


        p.start();
        c.start();
        try
        {
            p.join();
        } catch (InterruptedException e)
        {
            e.printStackTrace();
        }
        try
        {
            c.join();
        } catch (InterruptedException e)
        {
            e.printStackTrace();
        }

    }
}
