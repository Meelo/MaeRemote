package server;

import java.awt.AWTException;

import javax.swing.JOptionPane;

public class KeyTest {

    private static Engine engine;

    private static void keyTest() throws InterruptedException {
        new Thread() {
            public void run() {
                JOptionPane.showInputDialog("test"); // Won't show scandic characters correctly
            }
        }.start();
        Thread.sleep(1000); // UGLY sleep synchronization for waiting the input dialog to open

        String characters = "!\"#%&/()=?+äöÄÖ,.-_<>:;'*@${[]}\\|";
        for (int i = 0; i < characters.length(); i++) {
            char chara = characters.charAt(i);
            try {
                engine.sendCharacters(String.valueOf(chara));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    private static void arrowKeyTest() {
        new Thread() {
            public void run() {
                engine.addCommand("M" + Engine.CMD_SPLIT_CHAR + "__HOLD_LEFT__");
                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                engine.addCommand("M" + Engine.CMD_SPLIT_CHAR + "__RELEASE_LEFT__");
            }
        }.start();
    }

    public static void main(String[] args) throws AWTException, InterruptedException {
        engine = new Engine();
        keyTest();
        //arrowKeyTest();
    }
}    
