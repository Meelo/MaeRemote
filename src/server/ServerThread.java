package server;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class ServerThread extends Thread {

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
                engine.addCommand(inputLine);
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
}

