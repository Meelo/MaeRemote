package server;

import java.awt.AWTException;
import java.awt.DisplayMode;
import java.awt.GraphicsEnvironment;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.Robot;
import java.awt.event.InputEvent;
import java.awt.event.KeyEvent;

public class Driver {

    private static int[] buttons = { InputEvent.BUTTON1_MASK,
        InputEvent.BUTTON2_MASK, InputEvent.BUTTON3_MASK };
    private Point lastLocation;
    private Robot robot;
    private DisplayMode displayMode;
    private static final int MOVE_STEPS = 5;
    private static int[] shiftCharacters = new int[256];
    private static int[] altgrCharacters = new int[256];
    private static int[] scandicCharacters = new int[256];
    
    static {
        shiftCharacters['!'] = KeyEvent.VK_1; 
        shiftCharacters['\"'] = KeyEvent.VK_2;
        shiftCharacters['#'] = KeyEvent.VK_3;
//        shiftCharacters['�'] = KeyEvent.VK_4;
        shiftCharacters['%'] = KeyEvent.VK_5;
        shiftCharacters['&'] = KeyEvent.VK_6;
        shiftCharacters['/'] = KeyEvent.VK_7;
        shiftCharacters['('] = KeyEvent.VK_8;
        shiftCharacters[')'] = KeyEvent.VK_9;
        shiftCharacters['='] = KeyEvent.VK_0;
        shiftCharacters['?'] = KeyEvent.VK_PLUS;
        shiftCharacters['_'] = KeyEvent.VK_MINUS;
        shiftCharacters['>'] = KeyEvent.VK_LESS;
        shiftCharacters[';'] = KeyEvent.VK_COMMA;
        shiftCharacters[':'] = '.'; // No other reason than that I couldn't immediately find a matching key event.
        shiftCharacters['*'] = KeyEvent.VK_QUOTE;
        
        altgrCharacters['@'] = KeyEvent.VK_2;
//        altgrCharacters['�'] = KeyEvent.VK_3;
        altgrCharacters['$'] = KeyEvent.VK_4;
        altgrCharacters['{'] = KeyEvent.VK_7;
        altgrCharacters['['] = KeyEvent.VK_8;
        altgrCharacters[']'] = KeyEvent.VK_9;
        altgrCharacters['}'] = KeyEvent.VK_0;
        altgrCharacters['\\'] = KeyEvent.VK_PLUS;
        altgrCharacters['|'] = KeyEvent.VK_LESS;
        
        scandicCharacters[228] = KeyEvent.VK_A;
        scandicCharacters[196] = KeyEvent.VK_A;
        scandicCharacters[246] = KeyEvent.VK_O;
        scandicCharacters[214] = KeyEvent.VK_O;
    }

    public Driver() throws AWTException {
        robot = new Robot();
        lastLocation = MouseInfo.getPointerInfo().getLocation();
        displayMode = GraphicsEnvironment.getLocalGraphicsEnvironment().getDefaultScreenDevice().getDisplayMode();
    }

    public void updatePosition(int dx, int dy, boolean fastMode) {
        if (fastMode) {
            movePosition(dx, dy);
        }
        else {
            int targetX = validateXCoord(lastLocation.x + dx);
            int targetY = validateYCoord(lastLocation.y + dy);
            int stepsLeft = MOVE_STEPS;
            while (stepsLeft > 0) {
                int xStep = (targetX - lastLocation.x) / stepsLeft;
                int yStep = (targetY - lastLocation.y) / stepsLeft;
                movePosition(xStep, yStep);
                try {
                    Thread.sleep(5);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                stepsLeft--;
            }
        }
    }

    public void click(int button) {
        button = buttons[button - 1];
        robot.mousePress(button);
        robot.mouseRelease(button);
    }

    public void scroll(int amount) {
        robot.mouseWheel(amount);
    }

    public void sendCharacters(String string) {
        for (int i = 0; i < string.length(); i++) {
            char letter = string.charAt(i);
            if (shiftCharacters[letter] != 0) {
                type(shiftCharacters[letter], true);
            }
            else if (altgrCharacters[letter] != 0) {
                type(altgrCharacters[letter], false, true); 
            }
            else if (scandicCharacters[letter] != 0) {
                robot.keyPress(KeyEvent.VK_DEAD_DIAERESIS);
                robot.keyRelease(KeyEvent.VK_DEAD_DIAERESIS);
                type(scandicCharacters[letter], letter <= 214); 
            }
            else {
                char upperCase = Character.toUpperCase(letter);
                boolean shift = letter == upperCase && Character.isLetter(letter);
                if (upperCase == '+') upperCase = KeyEvent.VK_PLUS;
                else if (upperCase == '<') upperCase = KeyEvent.VK_LESS;
                else if (upperCase == '\'') upperCase = KeyEvent.VK_QUOTE;
                type(upperCase, shift);
            }
        }
    }
    public void type(int keyCode, boolean shift) {
        type(keyCode, shift, false);
    }
    
    public void type(int keyCode, boolean shift, boolean altgr) {
        if (shift) {
            robot.keyPress(KeyEvent.VK_SHIFT);
        }
        if (altgr) {
            robot.keyPress(KeyEvent.VK_CONTROL);
            robot.keyPress(KeyEvent.VK_ALT);
        }
        robot.keyPress(keyCode);
        robot.keyRelease(keyCode);
        if (shift) {
            robot.keyRelease(KeyEvent.VK_SHIFT);
        }
        if (altgr) {
            robot.keyRelease(KeyEvent.VK_ALT);
            robot.keyRelease(KeyEvent.VK_CONTROL);
        }
    }
    private void movePosition(int dx, int dy) {
        lastLocation.x = validateXCoord(lastLocation.x + dx);
        lastLocation.y = validateYCoord(lastLocation.y + dy);
        robot.mouseMove(lastLocation.x, lastLocation.y);        
    }

    private int validateXCoord(int x) {
        return validateCoord(x, displayMode.getWidth());
    }

    private int validateYCoord(int y) {
        return validateCoord(y, displayMode.getHeight());
    }

    private int validateCoord(int coord, int limit) {
        if (coord > limit) {
            coord = limit;
        }
        else if (coord < 0) {
            coord = 0;
        }
        return coord;
    }

    public void holdKey(int keycode) {
        System.out.println("Holding " + keycode);
        robot.keyPress(keycode);
    }

    public void releaseKey(int keycode) {
        System.out.println("Releasing " + keycode);
        robot.keyRelease(keycode);
    }

}
