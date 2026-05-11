<img width="350" height="201" alt="image" src="https://github.com/user-attachments/assets/16204557-1c0e-4623-ae3a-90f8fd27c9e3" />

# Supreme Commander 2 Proxima
This is a working LAN/P2P patch for Supreme Commander 2 to connect without SteamP2P. 

In its current state it should be fully working for private matches. Matchmaking is not planned.

Due to me scavenging code and tools from my previous projects (most notably from IW4x) this might be a bit overengineered. Sorry!

# How it works
SC2 uses the Steam P2P API to connect peers to each other and then handle all communication. One could trivially proxy Steam to replace this API with another STUN/TURN implementation, relayed or not, or even just a simple Winsock TCP socket.

However there is another way.

The UDP Connector used by Supreme Commander: Forged Alliance *is still partially present in the code*, somewhat. It doesn't work out of the box but with a tiny push, it does.

# Getting started
## This library replaces the steam_api.dll in your /bin folder. **Make a backup beforehand**.

- Open game directory from Steam
<img width="423" height="240" alt="image" src="https://github.com/user-attachments/assets/08d917b7-81dc-4d6c-8a4b-5918f022dc16" />

- Browse to the /bin subfolder
<img width="272" height="193" alt="image" src="https://github.com/user-attachments/assets/30b871e0-972f-466d-9e81-b5dd64d08fb1" />

- Rename your existing steam_api.dll to preserve it
<img width="278" height="72" alt="image" src="https://github.com/user-attachments/assets/d247c53e-b706-4417-b6d1-518dba60043a" />

- Grab the latest version of SC2-Proxima at https://github.com/Rackover/sc2-proxima/releases/latest 
<img width="357" height="109" alt="image" src="https://github.com/user-attachments/assets/82ea2ea6-115d-4e85-b37a-3bcc2a282752" />

- Put it in the same folder, next to SupremeCommander2.exe
<img width="617" height="81" alt="image" src="https://github.com/user-attachments/assets/e96b83ff-4016-4c6f-9640-597f28a4008e" />

- You're good to go!

# Hosting a game
### Simply click on "Host game" in the main menu.
Then configure the lobby as you like.
<img width="512" height="365" alt="image" src="https://github.com/user-attachments/assets/8024c2b4-3873-482a-9773-37a272867edb" /> <img width="512" height="365" aalt="image" src="https://github.com/user-attachments/assets/a89f809c-48f6-4800-95fa-aa4df277bd7e" />

# Joining a game
### Select "Join Game" on the main menu
<img width="512" height="365" alt="image" src="https://github.com/user-attachments/assets/2b8289b3-3488-456e-824e-5e18e6330cb8" />

### Then **in the search bar**, type the IP you wanna join. 
- You can also type IP:Port.
- Example, `127.0.0.1`.
- **The default hosting port is 16010. If you specify nothing, the port will be 16010.**
<img width="512" height="365" alt="image" src="https://github.com/user-attachments/assets/6b9905ec-7fdc-4ba0-99f7-c2d03787375b" />

### Click **Search tags**. A single game will appear in the browser. (Game name and map do not matter, its a "fake" game)
<img width="512" height="365" alt="image" src="https://github.com/user-attachments/assets/b63281b0-e924-49d8-8e54-815735b0040a" />

### **Double click** on it.
<img width="512" height="365" alt="image" src="https://github.com/user-attachments/assets/44b35135-12cd-4315-9b09-0cc6a1ac617d" />

# Troubleshooting
This is a very direct approach to peer connection, there is no relay, no tunneling, no punching -  **you will need to open the port on your router and/or firewall for it to work**.
This program is only for the Steam version of SC2 (1.260). Other versions may not be supported.
Only the private match multiplayer experience was my focus, so the rest of the game might be wrecked. Not sure. 

# Changing port and name
If you have launched the game at least once, you will have a file named `PlayerData.txt` in a `Proxima/` directory next to SupremeCommander2.exe
Use it to change your name and to change the default hosting/joining port if you need something else than 16010.

# Credits
Thanks to the incredible efforts of the Goldberg team for reversing almost every version of Steam API out there, this helped tremendously to tailor the proxy to Supreme Commander 2 specifically :)
