package server;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;


public class ServerThread extends Thread {

    private static final String UPDATE_COMMAND = "U";
    private static final String MESSAGE_COMMAND = "M";
    private static final String CLICK_COMMAND = "C";
    private static final String SCROLL_COMMAND = "S";

    private Socket socket;
    private Engine engine;
    private PrintWriter output;

    public ServerThread(Socket socket, Engine engine) {
        this.socket = socket;
        this.engine = engine;
        engine.log("*** New connection " + socket.getInetAddress().getHostAddress());
        initializeOutput();
    }

    private void initializeOutput() {
        try {
            output = new PrintWriter(new OutputStreamWriter(this.socket.getOutputStream(), "ISO-8859-1"), true);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        try {
            BufferedReader in = new BufferedReader(new InputStreamReader(this.socket.getInputStream(), "ISO-8859-1"));

            String inputLine;
            // Read until the end of input which shouldn't happen unless a client disconnects
            while ((inputLine = in.readLine()) != null) {
                engine.log("Received: " + inputLine);
                parseAndExecuteCommand(inputLine);
            }
            output.close();
            in.close();
            socket.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.err.println("IO Error");
        }
        engine.log("*#* " + socket.getInetAddress().getHostAddress() + " disconnected");
    }

    private void parseAndExecuteCommand(String inputLine) {
        String[] inputArray = inputLine.split(Character.toString((char)255));
        try {
            String command = inputArray[0];
            if (UPDATE_COMMAND.equals(command)) {
                // U;dx;dy
                int dx = Integer.parseInt(inputArray[1]);
                int dy = Integer.parseInt(inputArray[2]);
                engine.updatePosition(dx, dy);
            }
            else if (MESSAGE_COMMAND.equals(command)) {
                // M;character/string
                engine.sendCharacters(inputArray[1]);
            }
            else if (CLICK_COMMAND.equals(command)) {
                // C;button
                engine.click(Integer.parseInt(inputArray[1]));
            }
            else if (SCROLL_COMMAND.equals(command)) {
                // S;amount
                engine.scroll(Integer.parseInt(inputArray[1]));
            }
        }
        catch (Exception e) {
            System.err.println("Error while parsing a command from " + socket.getInetAddress().getHostAddress());
            e.printStackTrace();
        }

    }
}