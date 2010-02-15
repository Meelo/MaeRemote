package server;

import java.awt.AWTException;

public class Engine {
    private Driver driver;

    
    public Engine() throws AWTException {
        this.driver = new Driver();
    }


    public void log(String string) {
        System.out.println(string);
    }


    public void updatePosition(int dx, int dy) {
        driver.updatePosition(dx, dy);
    }
    
    public void click(int button) {
        driver.click(button);
    }

    public void scroll(int amount) {
        driver.scroll(amount);
    }
    

    public void sendCharacters(String string) {
       driver.sendCharacters(string);
    }

}
