package server;

import java.awt.AWTException;
import java.awt.Robot;
import java.awt.event.KeyEvent;

import javax.swing.JOptionPane;

public class KeyTest {

    private static Engine engine;
    
    private static void keyTest() throws InterruptedException {
        String characters = "!\"#¤%&/()=?+äöÄÖ,.-_<>:;'*@£${[]}\\|";
        for (int i = 0; i < characters.length(); i++) {
            char chara = characters.charAt(i);
            try {
                engine.sendCharacters(String.valueOf(chara));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) throws AWTException, InterruptedException {
        engine = new Engine();
        new Thread() {
            public void run() {
                JOptionPane.showInputDialog("test"); // Won't show scandic characters correctly
            }
        }.start();
        Thread.sleep(1000); // UGLY sleep synchronization for waiting the input dialog to open
        keyTest();
        engine.stop();
    }
}    
     