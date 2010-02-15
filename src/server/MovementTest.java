package server;

import java.awt.AWTException;

public class MovementTest {

    /**
     * @param args
     * @throws AWTException 
     * @throws InterruptedException 
     */
    public static void main(String[] args) throws AWTException, InterruptedException {
        Engine engine = new Engine();
        for (int j = 0; j < 5; j++) {
            engine.scroll(5);
            for (int i = 0; i < 62; i++) {
                engine.scroll(-1);
                int radius = 7*j + i/10;
                engine.updatePosition((int)(Math.sin(i/10.0) * radius), (int)(Math.cos(i/10.0) * radius));
                Thread.sleep(15);
            }
        }
        engine.click(3);
    }

}
