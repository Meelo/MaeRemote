package server;

import java.awt.AWTException;

public class MovementTest {

    private static Engine engine;
    
    private static void cmdQueueTest() throws InterruptedException {
        for (int j = 0; j < 5; j++) {
            for (int i = 0; i < 62; i++) {
                int radius = 7*j + i/10;
                engine.addCommand("U" + Engine.CMD_SPLIT_CHAR + (int)(Math.sin(i/10.0) * radius) + Engine.CMD_SPLIT_CHAR + (int)(Math.cos(i/10.0) * radius));
                Thread.sleep(15);
            }
        }
    }
    
    private static void circleDrawTest() throws InterruptedException {
        for (int j = 0; j < 5; j++) {
            engine.scroll(5);
            for (int i = 0; i < 62; i++) {
                engine.scroll(-1);
                int radius = 7*j + i/10;
                engine.updatePosition((int)(Math.sin(i/10.0) * radius), (int)(Math.cos(i/10.0) * radius), false);
                Thread.sleep(15);
            }
        }
    }

    public static void main(String[] args) throws AWTException, InterruptedException {
        engine = new Engine();
        circleDrawTest();
        cmdQueueTest();
        engine.stop();
    }
}
