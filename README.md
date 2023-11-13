# Networks_Team_Project
Implementation of NAT using C

# Workflow
1. Server Initialization:
-The server initializes a socket to listen for incoming connections on a specified port (in this case, port 8080).
-Initial mappings are set up on the server, containing pairs of local and global IP addresses.

2. Client Initialization:
-The client creates a socket to connect to the server.
-The client establishes a connection with the server, specifying the server's IP address and port.

3. Menu Interaction:
-The client presents a menu to the user with two options:
  Option 1: Check IP Mapping
  Option 2: Add New Mapping
  
4. Client Choice:
-The user selects an option by entering the corresponding number.

5. Client Sends Request:
-The client sends the selected option to the server.

6. Server Processes Request:
-The server receives the option and acts accordingly:
  For Option 1: It prompts the client for a local IP address, checks the mappings, and sends the corresponding global address or an error message.
  For Option 2: It prompts the client for a new local and global IP address, adds the mapping, and sends a success or error message.

7. Client Receives and Displays Response
-The client receives the server's response and displays it to the user.

8. Connection Closure:
-The client and server close their respective sockets after the interaction.

# How To Run
1. Compile the server and client programs.
2. Run the server program first.
3. Run the client program once you see the message "Server listening on Port 8080...".
