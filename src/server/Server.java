package server;
import java.awt.AWTException;
import java.io.IOException;
import java.net.ServerSocket;


public class Server {

    /**
     * 
     * @param args an optional array which has a port number in its first slot.
     * @throws IOException
     * @throws AWTException 
     */
    public static void main(String[] args) throws IOException, AWTException {
        int port = 6668;
        if (args.length > 0) {
            port = Integer.parseInt(args[0]);
        }
        ServerSocket serverSocket = null;
        boolean listening = true;
        try {
            serverSocket = new ServerSocket(port);
        } catch (IOException e) {
            System.err.println("Could not listen on port: " + port + ".");
            System.exit(-1);
        }
        System.out.println("MaeRemote server online and listening on port: " + port);
        Engine engine = new Engine();
        while (listening) {
            ServerThread serverThread = new ServerThread(serverSocket.accept(), engine);
            serverThread.start();
            
        }
        serverSocket.close();
    }
}

